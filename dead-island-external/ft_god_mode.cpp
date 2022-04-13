#include "ft_god_mode.hpp"

#include "osmium/Includings/modules.hpp"

#include "offsets.hpp"

void ft_god_mode::on_enable()
{
	Modules::g_pProcess->write_to_protected_memory< uint8_t >(Offsets::god_mode + 3, 0xAA);
}

void ft_god_mode::on_disable()
{
	Modules::g_pProcess->write_to_protected_memory< uint8_t >(Offsets::god_mode + 3, 0x8A);
}
