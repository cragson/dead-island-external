#include "ft_infinite_xp.hpp"

#include "osmium/Includings/modules.hpp"

#include "offsets.hpp"

void ft_infinite_xp::on_enable()
{
	Modules::g_pProcess->write_to_protected_memory< uint16_t >(Offsets::infinite_xp, 0xA809);
}

void ft_infinite_xp::on_disable()
{
	Modules::g_pProcess->write_to_protected_memory< uint16_t >(Offsets::infinite_xp, 0x908B);
}
