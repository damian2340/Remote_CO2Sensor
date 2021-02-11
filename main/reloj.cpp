#include "reloj.h"

//#define TZ_STRING TZ_America_Argentina_Buenos_Aires

extern "C" int clock_gettime(clockid_t unused, struct timespec *tp);

//time_t now;

static int time_machine_days = 0; // 0 = now
static bool time_machine_running = false;

uint32_t sntp_startup_delay_MS_rfc_not_less_than_60000()
{
    //info_sntp_startup_delay_MS_rfc_not_less_than_60000_has_been_called = true;
    return 25000; // 25s (or lwIP's original default: (random() % 5000))
}

uint32_t sntp_update_delay_MS_rfc_not_less_than_15000()
{
    //info_sntp_update_delay_MS_rfc_not_less_than_15000_has_been_called = true;
    return 15000; // 15s
}

void timeZoneConfig()
{
    configTime("PSTR(\"<03>-3\")", "pool.ntp.org");
}

time_t timeNow()
{
    return time(nullptr);
}

void timeFormat4y2M2d2h2m2s(time_t valorFecha, char *fechaDeSalida)
{
    // formato yyyyMMddhhmmss
    const tm *tmData = localtime(&valorFecha);
    sprintf(fechaDeSalida, "%4d%02d%02d%02d%02d%02d", (tmData->tm_year) + 1900, (tmData->tm_mon) + 1, tmData->tm_mday, tmData->tm_hour, tmData->tm_min, tmData->tm_sec);
}
