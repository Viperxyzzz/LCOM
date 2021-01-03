#include "rtc.h"


static int hook_id = RTC_IRQ;



int (rtc_subscribe_int)()
{
    return sys_irqsetpolicy(RTC_IRQ,IRQ_REENABLE,&hook_id);
}

int (read_rtc)(uint32_t address,uint16_t* input)
{
    uint32_t val = 0;
    sys_outb(RTC_ADDR_REG,address);
    sys_inb(RTC_DATA_REG,&val);
    *input = (uint16_t)val;
    return 0;
}

uint16_t bcd_to_decimal(uint16_t x) {
    return x - 6 * (x >> 4);
}

void (get_date)(Date* date)
{
    uint16_t seconds = 0;
    read_rtc(RTC_SECONDS,&seconds);
    date->seconds = seconds;


    uint16_t minutes = 0;
    read_rtc(RTC_MINUTES,&minutes);
    date->minutes = minutes;

    uint16_t hours = 0;
    read_rtc(RTC_HOURS,&hours);
    date->hours = hours;

    uint16_t day = 0;
    read_rtc(RTC_DAY,&day);
    date->day = day;

    uint16_t month = 0;
    read_rtc(RTC_MONTH,&month);
    date->month = month;

    uint16_t year = 0;
    read_rtc(RTC_YEAR,&year);
    date->year = year;
    
}


int (rtc_unsuscribe_int)()
{
    return sys_irqrmpolicy(&hook_id);
}
