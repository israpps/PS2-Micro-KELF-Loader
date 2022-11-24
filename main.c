#include <kernel.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

#ifndef KELFPATH
#define KELFPATH "mc?:/BAEXEC-SYSTEM/osdmain.elf"
#endif

int exist(char *filepath)
{
    int fdn;

    fdn = open(filepath, O_RDONLY);
    if (fdn < 0)
        return 0;

    close(fdn);

    return 1;
}

int main()
{
#ifndef IGNORE_MULTI_MCSLOT_CHECK
    char KELF[64] = KELFPATH;
    if (!strncmp(KELF, "mc?", 3)) // starts with mc?. check on slot 1
    {
        KELF[2] = '1';
        if (!exist(KELF)) // nothing on slot 1
        {
            KELF[2] = '0'; // check slot 0, don't do error handling here, if it doesnt exist on both places, let nature do the trick! we can't make magic.
        }
        
    }
#endif
    char KELFARG[64];
    char *args[4] = {"-m rom0:SIO2MAN", "-m rom0:MCMAN", "-m rom0:MCSERV", KELFARG};
#ifndef IGNORE_MULTI_MCSLOT_CHECK
    sprintf(KELFARG, "-x %s", KELFPATH);
#else
    sprintf(KELFARG, "-x %s", KELF);
    
#endif
    LoadExecPS2("moduleload", 4, args);
   while(1);
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

PS2_DISABLE_AUTOSTART_PTHREAD();

#ifndef KELFPATH
#error please define the KELF path in the KELFPATH macro
#endif
