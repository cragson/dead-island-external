#include "ft_infinite_stamina.hpp"

#include "osmium/Includings/modules.hpp"

#include "offsets.hpp"

void ft_infinite_stamina::on_enable()
{
	Modules::g_pProcess->nop_bytes(Offsets::infinite_stamina, 8);
}

void ft_infinite_stamina::on_disable()
{
	Modules::g_pProcess->write_to_protected_memory< uint64_t >(Offsets::infinite_stamina, this->m_bytes);
}

void ft_infinite_stamina::on_first_activation()
{
	this->m_bytes = Modules::g_pProcess->read< uint64_t >(Offsets::infinite_stamina);
}
