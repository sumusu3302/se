/*  Copyright (C) 2006 yopyop
    yopyop156@ifrance.com
    yopyop156.ifrance.com

	Copyright (C) 2009 DeSmuME team

    This file is part of DeSmuME

    DeSmuME is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    DeSmuME is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with DeSmuME; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#include "../addons.h"
#include "../mem.h"
#include "../MMU.h"
#include <string.h>

void (*FeedbackON)(BOOL enable) = NULL;

BOOL RumblePak_init(void) { return (TRUE); };

void RumblePak_reset(void)
{
};

void RumblePak_close(void) {};

void RumblePak_config(void) {};

void RumblePak_write08(u32 adr, u8 val)
{
};

void RumblePak_write16(u32 adr, u16 val)
{
	if (!FeedbackON) return;

	// CrazyMax 17/01/2009
	// i don't know how send to feedback (PC) impulse with small latency.
	if (adr == 0x08000000) 
		FeedbackON(val);
	if (adr == 0x08001000) 
		FeedbackON(val);
};

void RumblePak_write32(u32 adr, u32 val)
{
};

u8   RumblePak_read08(u32 adr)
{
	return (0);
};

u16  RumblePak_read16(u32 adr)
{
	u16 val = ( (adr & 0x1FFFF) >> 1 ) & 0xFFFD;
	if (adr == 0x0801FFFE) val = 0x005D;	// hack!!! anybody have docs for RumblePak?

	return ((u16)val); 
};

u32  RumblePak_read32(u32 adr)
{
	return (0);
};

void RumblePak_info(char *info) { strcpy(info, "NDS Rumble Pak (need joystick)"); };

ADDONINTERFACE addonRumblePak = {
				"Rumble Pak",
				RumblePak_init,
				RumblePak_reset,
				RumblePak_close,
				RumblePak_config,
				RumblePak_write08,
				RumblePak_write16,
				RumblePak_write32,
				RumblePak_read08,
				RumblePak_read16,
				RumblePak_read32,
				RumblePak_info};