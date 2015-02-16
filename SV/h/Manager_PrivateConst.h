#ifndef ___SV_MANAGER_PRIVATE_CONST_H___
#define ___SV_MANAGER_PRIVATE_CONST_H___


typedef enum svOperatingNormally { svFalse = 0, svTrue };		// マネージャーの正常稼働を表す

/******** マクロ ********/
#define ATTESTATION_NO (rndNo * 13 / 15 % 20)

/*********** 定数 **********/
const int LIMIT_PINGTIME = 60;

#endif