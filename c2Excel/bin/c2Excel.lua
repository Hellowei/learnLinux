require "lfs"
require "json"
require "lc"-------这个lc.dll有个bug,ansi转utf-8后 会多出ULL三个字符
print(lc.help())
require "luacom"----这个luacom.dll有bug，程序运行结束会崩掉
local Excel = {}

local function readFile(path)--针对普通文件
    local f = assert(io.open(path, 'r'))
    local string = f:read("*all")
    f:close()
    return string
end
local function writeFile(filename,str )--针对普通文件
    local f = assert(io.open(filename, 'w'))
    f:write(str)
    f:close()
end

local function getKeyAndString(string)
	local k = 0;
	local totalLen = string.len(string);
	local keyTable = {};
	local valueTable = {};
	while(1) do
		--查找 [到字母或数字或下划线共1以上再到]再到空白字符任意个再到=再到空白字符任意个再到再到双引号再到任意字符任意个再到双引号
		local a,b = string.find(string,'%[[%a-%d-_]+%]%s*=%s*".-"');
		if (b and a and ( b < totalLen))	then
			local subString = string.sub(string,a,b);
			local error2 = string.find(subString,"\n",2);--存在换行
			if( error2 ) then
				print("error end ",error2,subString);
			else
				k = k + 1;
				local key = string.sub(subString,2,string.find(subString,"%]")-1);
				keyTable[k] = key;
				local c,d = string.find(subString,'".-"');
				if (c and d) then
					local value = string.sub(subString,c+1,d-1);
					valueTable[k] = value;
				else
					valueTable[k] = "";
				end
			end
			string = string.sub(string,b+1,totalLen);
		else
			break;
		end
	end
	return k,keyTable,valueTable;
	
end

local function checkException(fileMessage,tableNum)
	local maxNum = 0;
	local maxFileKey = {};
	local maxFileTh = 0;
	
	-----检测所有文件字符串个数是否一致
	for k = 1,tableNum do
		if(maxNum < fileMessage[k].num )	then
			maxNum = fileMessage[k].num;
			maxFileKey = fileMessage[k].key;
			maxFileTh = k;
		end
		if(fileMessage[1].num ~= fileMessage[k].num)	then
			print(lc.u2a("key个数不一致"),fileMessage[1].fileName,fileMessage[1].num,fileMessage[k].num,fileMessage[k].fileName)--数目不一致
		end
	end
	
	--检测是否有排版不相同的字符串
	for k = 1,maxNum do
		for fileNum = 1,tableNum-1 do
			if(maxFileKey[k] ~= fileMessage[fileNum].key[k]) then
				print(lc.u2a("排版不一致"),maxFileKey[k],fileMessage[maxFileTh].fileName,fileMessage[fileNum].fileName,fileMessage[fileNum].key[k]);--排版有异
			end
		end
	end
	
	
	---检测 是否有重复的字符串
	for fileNum = 1,tableNum do
		local keyTable = fileMessage[fileNum].key;
		local keyNum = fileMessage[fileNum].num;
		for k = 1,keyNum-2 do
			for kk =k+1,keyNum do
				if (keyTable[k] == keyTable[kk]) then
					print(lc.u2a("文件存在相同的key"),keyTable[kk],fileMessage[fileNum].fileName);
				end
			end
		end
	end
	return maxFileTh;
end
--- 
function tran2Excel(fileMessage,maxFileTh,totalTableNum)
	local maxKeyNum = fileMessage[maxFileTh].num;
	local maxKeyTable =  fileMessage[maxFileTh].key;
	local maxValueTable =  fileMessage[maxFileTh].value;
	local  excel = Excel.create();
	Excel.selectSheet(excel, 1)
 	print(lc.u2a("正在为你转换，请稍候"),"")
	for k = 1,maxKeyNum do
		Excel.write(excel, k,1,  maxKeyTable[k]);
		Excel.write(excel, k,2, maxValueTable[k]);
		local column = 3;
		for fileNum = 1,totalTableNum do
			if(fileNum ~= maxFileTh) then
				local curValue = nil;
				if(fileMessage[fileNum].key[k] == maxKeyTable[k]) then --两个不同文件的key相同
					curValue =  fileMessage[fileNum].value[k];
				else
					for i=1,fileMessage[fileNum].num do
						if (maxKeyTable[k] == fileMessage[fileNum].key[i] ) then
							curValue = fileMessage[fileNum].value[i];
							break;
						end
					end
				end
				if(curValue) then
					Excel.write(excel, k,column,curValue);
				else
					print(lc.u2a("找不到key"),fileMessage[fileNum].fileName,maxKeyTable[k]);
				end
				column = column + 1;
			end
		end
	end
	excel.Application.DisplayAlerts = 1
	excel.Application.ScreenUpdating = 1
	--excel.ActiveWorkBook:Save();-- 默认写到D:\我的文档 好像文件名还是book数字.xls
	local outputPath = lfs.currentdir().."\\result.xls"
	excel.ActiveWorkBook:SaveAs(outputPath);--
	Excel.close(excel)
	print(lc.u2a("转换已完成"),outputPath)
end

local function start(path)
	local num = 0
	local fileMessage = {};
	local curDir = lfs.currentdir();
    for fileName in lfs.dir(path) do
        if fileName ~= "." and fileName ~= ".." then
            if string.find(fileName, ".c") ~= nil then--
                local filePath = curDir.."\\"..path .. "\\" .. fileName
                fileName = string.sub(fileName, 1, string.find(fileName, ".c") - 1)
				local string = readFile(filePath);--得到此文件的所有字符串
				local keyNum,key,value = getKeyAndString(string);
                num = num + 1;
				fileMessage[num] = {};
				fileMessage[num].num = keyNum;
				fileMessage[num].key = key;
				fileMessage[num].value = value;
				fileMessage[num].fileName = fileName..".c";
             end
        end
    end
	local maxFileTh = checkException(fileMessage,num);
	tran2Excel(fileMessage,maxFileTh,num);--转为excel
end

---------------------------------

--- 新建Excel文件
function Excel.create()
    local excel = luacom.CreateObject("Excel.Application")
    if not excel then
        return nil, "CreateObject Excel.Application fail"
    end
    assert(luacom.GetType(excel) == "LuaCOM")
    excel.Visible = true--显示EXCEL窗口
	excel.WorkBooks:Add()
    return excel
end
 
--- 选择excel文件中的第几张表格
function Excel.selectSheet(excel, sheet)
    return excel.ActiveWorkbook.Sheets(sheet):Select()
end
 
function Excel.close(excel)
    local alerts = 1
    excel.Application.DisplayAlerts = alerts
    excel.Application.ScreenUpdating = alerts
    excel.Application:Quit()
end
 
function Excel.read(excel, row, column)
    return excel.Activesheet.Cells(row, column).Value2
end
 
function Excel.write(excel, row, column, temp)
    excel.Activesheet.Cells(row, column).Value2 = temp
end
---从这里开始
start("\c")
