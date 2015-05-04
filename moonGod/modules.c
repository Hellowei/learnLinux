#include "includes.h"




MODULEEXISTINFO gModuleInfo;

/*  
Name:		CheckModuleExistState
Description: See if there are modules changed since last time, if so,
			 just return an indicator.
			 Compliance problem, 
Parameters:  mod_id: module ID.
Return:	  1, change from non-existing to existing.
			 2, change from existing to non-exsiting.
			 3, still exist, but the slot number is changed.
			 0, not changed.
Test and revision:
			 Ason. 2001.9 <E>
			 Inspection. 2001.9.25
			 test. 2001.9.25
*/
INT16 GetModuleExistState( INT16 mod_id )
{
	INT16 i;
	INT16 return_value;
	
	for ( i = 0; i < MID_MAX; i++ )
	{
		if (   TRUE == MonitorConfig.moduleInfo[i].OnLine && mod_id == MonitorConfig.moduleInfo[i].Id )
			break;
	}
	
	// now, "i" is the slot number of module "mod_id".
	
	if ( MID_MAX == i )
	{
		// this module now do not exist.
		switch( mod_id )
		{

		default:
			return_value = 0;
			
		}
	}
	else
	{
		// say, this module now exist.
		switch( mod_id )
		{
		default:
			return_value = 0;
		}
	}

	return( return_value );
}

void GetParaModuleInfo( INT16 *exist_module_count, INT16 * exist_module_name,
					INT16 *onlaod_module_count, INT16 *onload_module_name,
					INT16 *unload_module_count, INT16 *unload_module_name )
{
	INT16 module_state = 0;

	const INT16 total_module_count = 0;
	const static INT16 module_id[0];
	// 请保持这两个数组一致
	const static INT16 module_name[0];

	INT16 i;
	
	*exist_module_count = 0;
	*onlaod_module_count = 0;
	*unload_module_count = 0;

	for (  i = 0; i < total_module_count; i ++ )
	{
		module_state = GetModuleExistState( module_id[i] );

		if ( 1 == module_state )
		{
			onload_module_name[(*onlaod_module_count) ++] = module_name[i];
		}

		if ( 2 == module_state )
		{
			unload_module_name[(*unload_module_count) ++] = module_name[i];
		}
	}
//	if ( gModuleInfo.ModuleEcgExist )
//	{
//		exist_module_name[(*exist_module_count) ++] = module_ECG;
//	}
//
}

