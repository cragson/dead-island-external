#include "ft_infinite_money.hpp"

#include "osmium/Includings/modules.hpp"

#include "offsets.hpp"

void ft_infinite_money::on_enable()
{
	Modules::g_pProcess->nop_bytes(Offsets::infinite_money + 1, 5);

	Modules::g_pProcess->write_to_protected_memory< uint8_t >(Offsets::infinite_money + 1, 0xD5);
}

void ft_infinite_money::on_disable()
{
	Modules::g_pProcess->write_to_protected_memory< uint8_t >(Offsets::infinite_money + 1, 0x90);
	Modules::g_pProcess->write_to_protected_memory< uint32_t >(Offsets::infinite_money + 2, 0x00000BC8);
}
