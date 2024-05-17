/*
# _____     ___ ____     ___ ____
#  ____|   |    ____|   |        | |____|
# |     ___|   |____ ___|    ____| |    \    PS2DEV Open Source Project.
#-----------------------------------------------------------------------
# Copyright ps2dev - http://www.ps2dev.org
# Licenced under Academic Free License version 2.0
# Review ps2sdk README & LICENSE files for further details.
*/

#include "libsnd2_internal.h"

void _SsSetNrpnVabAttr16(s16 vab_id, s16 prog, s16 tone, VagAtr vag_attr, s16 fn_idx, u8 attribute_value)
{
	(void)vab_id;
	(void)prog;
	(void)tone;
	(void)vag_attr;
	(void)fn_idx;
	SsUtSetReverbDepth(attribute_value, attribute_value);
}
