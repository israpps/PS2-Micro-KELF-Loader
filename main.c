#include <kernel.h>
#include <stdio.h>

#define KELFPATH "mc?:/PS2BBL/PS2BBL.KELF"

int main()
{
    char KELFARG[64];
    char *args[4] = {"-m rom0:SIO2MAN", "-m rom0:MCMAN", "-m rom0:MCSERV", KELFARG};
    sprintf(KELFARG, "-x %s", KELFPATH);
    LoadExecPS2("moduleload", 4, args);
   
   return 0;
}

#if defined(DUMMY_TIMEZONE)
   void _ps2sdk_timezone_update() {}
#endif

#if defined(DUMMY_LIBC_INIT)
   void _ps2sdk_libc_init() {}
   void _ps2sdk_libc_deinit() {}
   void _ps2sdk_args_parse(int argc, char ** argv) {}
#endif

#ifndef KELFPATH
#error please define the KELF path in the KELFPATH macro
#endif