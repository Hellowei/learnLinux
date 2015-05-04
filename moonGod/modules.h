
#ifndef MODULES_H
#define MODULES_H



typedef struct
{

} MODULEEXISTINFO;


void ShowListBox( UINT16 top_ctrl_id, UINT16 ctrl_id, BOOL fill_flag);
void ShowSpinBox( UINT16 top_ctrl_id, UINT16 ctrl_id, BOOL fill_flag);

extern MODULEEXISTINFO gModuleInfo;

#endif
