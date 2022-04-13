#include "ft_unbreakable_weapons.hpp"

#include "osmium/Includings/modules.hpp"

#include "offsets.hpp"

void ft_unbreakable_weapons::on_enable()
{
	Modules::g_pProcess->nop_bytes(Offsets::unbreakable_weapons, 5);
}

void ft_unbreakable_weapons::on_disable()
{
	Modules::g_pProcess->write_to_protected_memory< uint32_t >(Offsets::unbreakable_weapons, 0x73110FF3);

	Modules::g_pProcess->write_to_protected_memory< uint8_t >(Offsets::unbreakable_weapons + 4, 0x04);
}
