#include "dead_cheat.hpp"

#include "osmium/Includings/modules.hpp"

#include "offsets.hpp"
#include "ft_infinite_money.hpp"
#include "ft_infinite_stamina.hpp"
#include "ft_infinite_xp.hpp"
#include "ft_unbreakable_weapons.hpp"
#include "ft_god_mode.hpp"
#include "utils.hpp"

#include <Windows.h>

bool dead_cheat::setup_features()
{
	auto inf_money = std::make_unique< ft_infinite_money >();
	inf_money->set_name(L"Infinite Money");
	inf_money->set_print_status(true);
	inf_money->set_activation_delay(420);
	inf_money->disable_drawing();
	inf_money->set_virtual_key_code(VK_NUMPAD1);

	this->m_features.push_back(std::move(inf_money));

	auto inf_stam = std::make_unique< ft_infinite_stamina >();
	inf_stam->set_name(L"Infinite Stamina");
	inf_stam->set_print_status(true);
	inf_stam->set_activation_delay(420);
	inf_stam->disable_drawing();
	inf_stam->set_virtual_key_code(VK_NUMPAD2);

	this->m_features.push_back(std::move(inf_stam));

	auto inf_xp = std::make_unique< ft_infinite_xp >();
	inf_xp->set_name(L"Infinite XP");
	inf_xp->set_print_status(true);
	inf_xp->set_activation_delay(420);
	inf_xp->disable_drawing();
	inf_xp->set_virtual_key_code(VK_NUMPAD3);

	this->m_features.push_back(std::move(inf_xp));

	auto unb = std::make_unique< ft_unbreakable_weapons >();
	unb->set_name(L"Unbreakable Weapons");
	unb->set_print_status(true);
	unb->set_activation_delay(420);
	unb->disable_drawing();
	unb->set_virtual_key_code(VK_NUMPAD4);

	this->m_features.push_back(std::move(unb));

	auto god = std::make_unique< ft_god_mode >();
	god->set_name(L"God Mode");
	god->set_print_status(true);
	god->set_activation_delay(420);
	god->disable_drawing();
	god->set_virtual_key_code(VK_NUMPAD5);

	this->m_features.push_back(std::move(god));

    return true;
}

bool dead_cheat::setup_offsets()
{
	if (!Modules::g_pProcess->does_image_exist_in_map(L"gamedll_x64_rwdi.dll"))
		return false;

	const auto gamedll = Modules::g_pProcess->get_image_ptr_by_name(L"gamedll_x64_rwdi.dll");

	if (!gamedll)
		return false;

	const auto inf_money = gamedll->find_pattern( L"8B 90 C8 0B 00 00", false );

	if (!inf_money)
		return false;

	Offsets::infinite_money = inf_money;


	const auto inf_stam = gamedll->find_pattern(L"F3 0F 11 83 BC 0D 00 00 0F 87", false);

	if (!inf_stam)
		return false;

	Offsets::infinite_stamina = inf_stam;


	const auto inf_xp = gamedll->find_pattern(L"8B 90 80 00 00 00 2B", false);

	if (!inf_xp)
		return false;

	Offsets::infinite_xp = inf_xp;


	const auto unb_weap = gamedll->find_pattern(L"F3 0F 11 73 04 48 8B 5C 24 40", false);

	if (!unb_weap)
		return false;

	Offsets::unbreakable_weapons = unb_weap;


	const auto god = gamedll->find_pattern(L"F3 0F 11 8A 2C 0D 00 00 C3", false);

	if (!god)
		return false;

	Offsets::god_mode = god;

    return true;
}

void dead_cheat::run()
{
	for (const auto& feature : this->m_features)
	{
		// before tick'ing the feature, check first if the state will eventually change
		if (GetAsyncKeyState(feature->get_virtual_key_code()) & 0x8000)
			feature->toggle();

		// let the feature tick() when active
		if (feature->is_active())
			feature->tick();
	}
}

void dead_cheat::shutdown()
{
	// disable every feature here
	for (const auto& feature : this->m_features)
		if (feature->is_active())
			feature->disable();

	// clear image map here
	if (Modules::g_pProcess)
		Modules::g_pProcess->clear_image_map();
}

void dead_cheat::print_offsets()
{
	printf("\n");

	const auto msg = [](const std::string& name, const std::uintptr_t value)
	{
		printf("[>] %-35s -> 0x%llX\n", name.c_str(), value);
	};

	msg("Infinite Money", Offsets::infinite_money);
	msg("Infinite Stamina", Offsets::infinite_stamina);
	msg("Infinite XP", Offsets::infinite_xp);
	msg("Unbreakable Weapons", Offsets::unbreakable_weapons);
	msg("God Mode", Offsets::god_mode);

	printf("\n");
}

void dead_cheat::print_features()
{
	printf("\n");

	printf("Feature-Name -> Feature-Hotkey\n");

	for (const auto& feature : this->m_features)
		printf("[>] %-25ws -> %s\n", feature->get_name().c_str(), utils::virtual_key_as_string(feature->get_virtual_key_code()).c_str());

	printf("\n");
}
