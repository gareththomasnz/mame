// license:BSD-3-Clause
// copyright-holders:David Haywood
/* Early Maygay HW
 I believe this is 'Triple M' or 'MMM' hardware

 Z80 based Fruit Machine
*/


#include "emu.h"
#include "cpu/z80/z80.h"
#include "machine/z80ctc.h"
#include "sound/ay8910.h"
#include "speaker.h"

class mmm_state : public driver_device
{
public:
	mmm_state(const machine_config &mconfig, device_type type, const char *tag)
		: driver_device(mconfig, type, tag),
			m_maincpu(*this, "maincpu"),
			m_ctc(*this, "ctc"),
			m_inputs(*this, "IN%u", 0)
	{ }

	DECLARE_WRITE8_MEMBER(strobe_w);
	DECLARE_READ8_MEMBER(inputs_r);
	DECLARE_WRITE8_MEMBER(ay_porta_w);

	void mmm(machine_config &config);
	void io_map(address_map &map);
	void mem_map(address_map &map);
private:
	required_device<cpu_device> m_maincpu;
	required_device<z80ctc_device> m_ctc;
	required_ioport_array<8> m_inputs;
	u8 m_strobe;
};


WRITE8_MEMBER(mmm_state::strobe_w)
{
	m_strobe = data;
}

READ8_MEMBER(mmm_state::inputs_r)
{
	u8 result = 0xff;
	for (int i = 0; i < 8; i++)
		if (BIT(m_strobe, i))
			result &= m_inputs[i]->read();
	return result;
}

WRITE8_MEMBER(mmm_state::ay_porta_w)
{
	logerror("Writing %02X to AY-3-8910 port A\n", data);
}

void mmm_state::mem_map(address_map &map)
{
	map(0x0000, 0x3fff).rom();
	map(0x4000, 0x40ff).ram();
}

void mmm_state::io_map(address_map &map)
{
	map.global_mask(0xff);
	map(0x00, 0x00).w(this, FUNC(mmm_state::strobe_w));
	map(0x03, 0x03).w("aysnd", FUNC(ay8910_device::address_w));
	map(0x04, 0x04).w("aysnd", FUNC(ay8910_device::data_w));
	map(0x05, 0x05).r("aysnd", FUNC(ay8910_device::data_r));
	map(0x06, 0x06).select(0x30).lrw8("ctc_rw",
									  [this](address_space &space, offs_t offset, u8 mem_mask) {
										  return m_ctc->read(space, offset >> 4, mem_mask);
									  },
									  [this](address_space &space, offs_t offset, u8 data, u8 mem_mask) {
										  m_ctc->write(space, offset >> 4, data, mem_mask);
									  });
	map(0x07, 0x07).r(this, FUNC(mmm_state::inputs_r));
}


static INPUT_PORTS_START( mmm )
	PORT_START("IN0")
	PORT_BIT( 0x01, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x02, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x04, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x08, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x10, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x20, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x40, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x80, IP_ACTIVE_LOW, IPT_UNKNOWN )

	PORT_START("IN1")
	PORT_BIT( 0x01, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x02, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x04, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x08, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x10, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x20, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x40, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x80, IP_ACTIVE_LOW, IPT_UNKNOWN )

	PORT_START("IN2")
	PORT_BIT( 0x01, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x02, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x04, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x08, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x10, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x20, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x40, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x80, IP_ACTIVE_LOW, IPT_UNKNOWN )

	PORT_START("IN3")
	PORT_BIT( 0x01, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x02, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x04, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x08, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x10, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x20, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x40, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x80, IP_ACTIVE_LOW, IPT_UNKNOWN )

	PORT_START("IN4")
	PORT_BIT( 0x01, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x02, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x04, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x08, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x10, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x20, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x40, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x80, IP_ACTIVE_LOW, IPT_UNKNOWN )

	PORT_START("IN5")
	PORT_BIT( 0x01, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x02, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x04, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x08, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x10, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x20, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x40, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x80, IP_ACTIVE_LOW, IPT_UNKNOWN )

	PORT_START("IN6")
	PORT_BIT( 0x01, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x02, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x04, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x08, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x10, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x20, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x40, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x80, IP_ACTIVE_LOW, IPT_UNKNOWN )

	PORT_START("IN7")
	PORT_BIT( 0x01, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x02, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x04, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x08, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x10, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x20, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x40, IP_ACTIVE_LOW, IPT_UNKNOWN )
	PORT_BIT( 0x80, IP_ACTIVE_LOW, IPT_UNKNOWN )
INPUT_PORTS_END


static const z80_daisy_config mmm_daisy_chain[] =
{
	{ "ctc" },
	{ nullptr }
};


MACHINE_CONFIG_START(mmm_state::mmm)
	/* basic machine hardware */
	MCFG_DEVICE_ADD("maincpu", Z80,2000000)         /* ? MHz */
	MCFG_DEVICE_PROGRAM_MAP(mem_map)
	MCFG_DEVICE_IO_MAP(io_map)
	MCFG_Z80_DAISY_CHAIN(mmm_daisy_chain)

	MCFG_DEVICE_ADD("ctc", Z80CTC, 2000000)
	MCFG_Z80CTC_INTR_CB(INPUTLINE("maincpu", INPUT_LINE_IRQ0))

	/* sound hardware */
	MCFG_SPEAKER_STANDARD_MONO("mono")
	MCFG_DEVICE_ADD("aysnd", AY8910, 1000000)
	MCFG_AY8910_PORT_A_WRITE_CB(WRITE8(*this, mmm_state, ay_porta_w))
	MCFG_SOUND_ROUTE(ALL_OUTPUTS, "mono", 0.30)
MACHINE_CONFIG_END


ROM_START( mmm_ldip )
	ROM_REGION( 0x10000, "maincpu", 0 )
	ROM_LOAD( "ld1.bin", 0x0000, 0x1000, CRC(5a3c2402) SHA1(4972d309e6aabef4f9277ea851e45981d0cb3dbb) )
	ROM_LOAD( "ld2.bin", 0x1000, 0x1000, CRC(ff82643b) SHA1(0e47cdc9c0eb6f05a420d2ffeb2ebf22acbda15b) )
	ROM_LOAD( "ld3.bin", 0x2000, 0x1000, CRC(9e7158ae) SHA1(7f3b8730add127ed0608365875be3042fb2e3e7a) )
	ROM_LOAD( "ld4.bin", 0x3000, 0x1000, CRC(970b749f) SHA1(fe6da7abc699db69c0761304f588b5bed899c674) )
ROM_END


GAME( 198?,  mmm_ldip,  0,  mmm,  mmm, mmm_state,  0,  ROT0,  "Maygay",    "Lucky Dip (Maygay)",    MACHINE_IS_SKELETON_MECHANICAL)
