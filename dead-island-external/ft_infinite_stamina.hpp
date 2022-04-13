#pragma once

#include "osmium/Cheat/Feature/feature.hpp"

class ft_infinite_stamina : public feature
{
public:

	ft_infinite_stamina() : feature(), m_bytes( uint64_t() ) {}

	void tick() override {}

	void on_enable() override;

	void on_disable() override;

	void on_first_activation() override;

	void on_render() override {}

private:

	uint64_t m_bytes;
};