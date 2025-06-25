#include <stdio.h>
#include "Util/util.h"
#include "Menu/menuConsole.h"
#include "Entities/administrador.h"

int main() {

#ifdef _WIN32
    system("chcp 65001");
#endif    

    init_random();
    inicializar_adm_padrao();
    iniciar_menu_console();
        
    return 0;
}