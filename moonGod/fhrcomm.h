#ifndef FHR_COMM_H
#define FHR_COMM_H

#define FETAL_MODULE_ID		0x83

#define FHR_RTN_CMD_ID		0x01
#define FHR_RTN_DATA_ID		0x00

typedef enum _fhr_rtn_data_index
{
	FHR_RTN_DATA_INDEX_CMD,
	FHR_RTN_DATA_INDEX_DATA,
	FHR_RTN_DATA_INDEX_MAX
}FHR_RTN_DATA_INDEX;

#ifndef FHRCOMM_GLOBALS
#define FHRCOMM_EXT extern
#else
#define FHRCOMM_EXT
#endif

FHRCOMM_EXT BOOL InitFhrModule(VOID);
FHRCOMM_EXT VOID FetalSetMoudle(BOOL zero);
FHRCOMM_EXT VOID FetalSendPack(PACKETFRAME *pack);
FHRCOMM_EXT VOID FetalPacketFound(PACKETFRAME *pack);


#endif

