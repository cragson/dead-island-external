#include <iostream>

#include "osmium/Includings/modules.hpp"

#include "dead_cheat.hpp"

int main()
{
    SetConsoleTitleA("osmium: Dead Island Definitive Edition");

    printf("[>] Waiting for the game..");

    while (!Modules::g_pProcess->setup_process(L"DeadIslandGame.exe"))
        Sleep(420);

    printf("done!\n");

    printf("[>] Preparing the cheat..");

    const auto cheat = std::make_unique< dead_cheat >();

    while (!cheat->setup_offsets())
        Sleep(420);

    while (!cheat->setup_features())
        Sleep(420);

    printf("done!\n");

    cheat->print_offsets();

    cheat->print_features();

    printf("Have fun! ;-)\n");

    while (0xDEAD != 0xAFFE)
    {
        if (GetAsyncKeyState(VK_END) & 0x8000)
            break;

        cheat->run();

        Sleep( 3 );
    }

    cheat->shutdown();

    printf("Goodbye!\n");

    Sleep(5000);

    return EXIT_SUCCESS;
}
