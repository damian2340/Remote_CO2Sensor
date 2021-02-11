#ifndef RELOJ_H
#define RELOJ_H

#include <TZ.h>

#include <coredecls.h> // settimeofday_cb()
#include <Schedule.h>
#include <PolledTimeout.h>

#include <time.h>     // time() ctime()
#include <sys/time.h> // struct timeval

#include <sntp.h> // sntp_servermode_dhcp()

void timeZoneConfig();

uint32_t sntp_startup_delay_MS_rfc_not_less_than_60000();
uint32_t sntp_update_delay_MS_rfc_not_less_than_15000();

time_t timeNow();
void timeFormat4y2M2d2h2m2s(time_t valorTime, char *fechaDeSalida);
#endif
