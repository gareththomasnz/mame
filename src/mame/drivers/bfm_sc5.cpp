// license:BSD-3-Clause
// copyright-holders:David Haywood
/*

    Scorpion 5

    Skeleton Driver - For note keeping.

    This system is not emulated.

*/


#include "emu.h"
#include "includes/bfm_sc5.h"

#include "machine/bfm_sc45_helper.h"
#include "machine/mcf5206e.h"
#include "video/awpvid.h"
#include "speaker.h"

#include "bfm_sc5.lh"



WRITE16_MEMBER( bfm_sc5_state::sc5_duart_w )
{
	// clearly a duart of some kind, write patterns are the same as SC4 games
//  logerror("%s: duart_w %1x %04x %04x\n", machine().describe_context(), offset, data, mem_mask);

	if (ACCESSING_BITS_8_15)
	{
		m_duart->write(space,offset,(data>>8)&0x00ff);
	}
	else
	{
		logerror("%s: duart_w %1x %04x %04x\n", machine().describe_context(), offset, data, mem_mask);
	}

}

READ8_MEMBER( bfm_sc5_state::sc5_mux1_r )
{
	switch (offset)
	{
		case 0x20:
			return machine().rand();
	}

	logerror("%s: sc5_mux1_r %1x\n", machine().describe_context(), offset);

	return 0x00;
}


WRITE8_MEMBER( bfm_sc5_state::sc5_mux1_w )
{
	if ((offset&0xf)==0)
	{
		mux_output_w(space, (offset & 0x01f0)>>4, data);
	}
	else
	{
		logerror("%s: sc5_mux1_w %1x %04x\n", machine().describe_context(), offset, data);
	}
}



WRITE8_MEMBER( bfm_sc5_state::sc5_mux2_w )
{
	if ((offset&0xf)==0)
	{
		mux_output2_w(space, (offset & 0x01f0)>>4, data);
	}
	else
	{
		logerror("%s: sc5_mux2_w %1x %04x\n", machine().describe_context(), offset, data);
	}
}


void bfm_sc5_state::sc5_map(address_map &map)
{
	// ROM (max size?)
	map(0x00000000, 0x002fffff).rom();
	// ?
	map(0x01000000, 0x0100ffff).ram();

#if 1
	// dev1
	map(0x01010000, 0x010101ff).rw(this, FUNC(bfm_sc5_state::sc5_mux1_r), FUNC(bfm_sc5_state::sc5_mux1_w)); // guess
#endif

#if 0

	map(0x01010200, 0x01010203).nopw();
	map(0x01010210, 0x01010213).nopw();
	map(0x01010220, 0x01010223).nopw();
	map(0x01010230, 0x01010233).nopw();

	map(0x01010280, 0x01010283).nopw();

	map(0x010102a0, 0x010102a3).nopw();

	map(0x010102c0, 0x010102c3).nopw();

	map(0x010102f0, 0x010102f3).nopw();

	map(0x01010300, 0x01010303).nopw();

	map(0x01010330, 0x01010333).nopw();

	map(0x01010360, 0x01010363).nopw();

	map(0x01010380, 0x01010383).nopw();
	map(0x01010390, 0x01010393).nopw();
#endif

#if 1
	// dev2
	map(0x01020000, 0x010201ff).w(this, FUNC(bfm_sc5_state::sc5_mux2_w)); // guess
#endif

#if 0

	map(0x01020200, 0x01020203).nopw();
	map(0x01020210, 0x01020213).nopw();
	map(0x01020220, 0x01020223).nopw();
	map(0x01020230, 0x01020233).nopw();

	map(0x01020280, 0x01020283).nopw();

	map(0x010202a0, 0x010202a3).nopw();
	map(0x010202b0, 0x010202b3).nopw();
	map(0x010202c0, 0x010202c3).nopw();
#endif
	map(0x010202F0, 0x010202F3).rw(this, FUNC(bfm_sc5_state::sc5_10202F0_r), FUNC(bfm_sc5_state::sc5_10202F0_w));
#if 1
	map(0x01020330, 0x01020333).nopw();

	map(0x01020350, 0x01020353).nopw();
	map(0x01020360, 0x01020363).nopw();
	map(0x01020370, 0x01020373).nopw();

	map(0x01020390, 0x01020393).nopw();
#endif
	map(0x02000000, 0x0200001f).w(this, FUNC(bfm_sc5_state::sc5_duart_w));

	// ram
	map(0x40000000, 0x4000ffff).ram();

	// peripherals
	map(0xffff0000, 0xffff03ff).rw("maincpu_onboard", FUNC(mcf5206e_peripheral_device::dev_r), FUNC(mcf5206e_peripheral_device::dev_w)); // technically this can be moved with MBAR
}

INPUT_PORTS_START( bfm_sc5 )
INPUT_PORTS_END

READ8_MEMBER( bfm_sc5_state::sc5_10202F0_r )
{
	switch (offset)
	{
		case 0x0:
		case 0x1:
		case 0x2:
		case 0x3:
			logerror("%s: sc5_10202F0_r %d\n", machine().describe_context(), offset);
			return machine().rand();
	}

	return 0;
}

WRITE8_MEMBER( bfm_sc5_state::sc5_10202F0_w )
{
	switch (offset)
	{
		case 0x0:
			bfm_sc45_write_serial_vfd((data &0x4)?1:0, (data &0x1)?1:0, (data&0x2) ? 0:1);
			if (data&0xf8) logerror("%s: sc5_10202F0_w %d - %02x\n", machine().describe_context(), offset, data);
			break;
		case 0x1:
		case 0x2:
		case 0x3:
			logerror("%s: sc5_10202F0_w %d - %02x\n", machine().describe_context(), offset, data);
			break;
	}
}


WRITE_LINE_MEMBER(bfm_sc5_state::bfm_sc5_duart_irq_handler)
{
	logerror("bfm_sc5_duart_irq_handler\n");
}

WRITE_LINE_MEMBER(bfm_sc5_state::bfm_sc5_duart_txa)
{
	logerror("bfm_sc5_duart_tx\n");
}

READ8_MEMBER(bfm_sc5_state::bfm_sc5_duart_input_r)
{
	logerror("bfm_sc5_duart_input_r\n");
	return 0xff;
}

WRITE8_MEMBER(bfm_sc5_state::bfm_sc5_duart_output_w)
{
	logerror("bfm_sc5_duart_output_w\n");
}

MACHINE_CONFIG_START(bfm_sc5_state::bfm_sc5)
	MCFG_DEVICE_ADD("maincpu", MCF5206E, 40000000) /* MCF5206eFT */
	MCFG_DEVICE_PROGRAM_MAP(sc5_map)
	MCFG_MCF5206E_PERIPHERAL_ADD("maincpu_onboard")

	/* sound hardware */
	MCFG_SPEAKER_STANDARD_MONO("mono")

	MCFG_DEVICE_ADD("duart68681", MC68681, 16000000/4) // ?? Mhz
	MCFG_MC68681_SET_EXTERNAL_CLOCKS(16000000/2/8, 16000000/2/16, 16000000/2/16, 16000000/2/8)
	MCFG_MC68681_IRQ_CALLBACK(WRITELINE(*this, bfm_sc5_state, bfm_sc5_duart_irq_handler))
	MCFG_MC68681_A_TX_CALLBACK(WRITELINE(*this, bfm_sc5_state, bfm_sc5_duart_txa))
	MCFG_MC68681_INPORT_CALLBACK(READ8(*this, bfm_sc5_state, bfm_sc5_duart_input_r))
	MCFG_MC68681_OUTPORT_CALLBACK(WRITE8(*this, bfm_sc5_state, bfm_sc5_duart_output_w))

	MCFG_BFMBDA_ADD("vfd0",0)

	MCFG_DEFAULT_LAYOUT(layout_bfm_sc5)

	MCFG_DEVICE_ADD("ymz", YMZ280B, 16000000) // ?? Mhz
	MCFG_SOUND_ROUTE(ALL_OUTPUTS, "mono", 1.0)
MACHINE_CONFIG_END

#include "bfm_sc5sw.hxx"
