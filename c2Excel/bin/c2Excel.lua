require "lfs"
require "json"
require "lc"-------这个lc.dll有个bug,ansi转utf-8后 会多出ULL三个字符
print(lc.help())
require "luacom"----这个luacom.dll有bug，程序运行结束会崩掉


local function readFile(path)--针对普通文件
    local f = assert(io.open("bin\\string_greek.c", 'r'))
    local string = f:read("*all")
    f:close()
    return string
end
local function writeFile(filename,str )--针对普通文件
    local f = assert(io.open(filename, 'w'))
    f:write(str)
    f:close()
end
--[STR_TOUCH_CAL_REMIND_1] = "ΑΒΓΔΕΖΗΘΙΚ∧ΜΝΞΟ∏Ρ∑ΤΥΦΧΨΩ",
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
				k = k +1;
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

local Excel = {}
local function start(path)
	local string = readFile(path);
    local num,key,value = getKeyAndString(string); 
	local  excel = Excel.create();
	Excel.selectSheet(excel, 1)
	for k = 1,num do
		Excel.write(excel, k,1,  key[k]);
		Excel.write(excel, k,2, value[k]);
	end
	excel.Application.DisplayAlerts = 1
	excel.Application.ScreenUpdating = 1
	excel.ActiveWorkBook:Save();-- 默认写到D:\我的文档 好像文件名还是book数字.xls
	Excel.close(excel)
end

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
start("\excel")
