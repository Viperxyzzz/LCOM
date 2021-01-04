#ifndef RTC_H
#define RTC_H

#include <lcom/lcf.h>


typedef struct
{
    uint8_t year,month,day,hours,minutes,seconds;
}Date;





#define RTC_IRQ      8
#define RTC_ADDR_REG 0x70
#define RTC_DATA_REG 0x71
#define RTC_SECONDS  0
#define RTC_MINUTES  2
#define RTC_HOURS    4
#define RTC_DAY      7
#define RTC_MONTH    8
#define RTC_YEAR     9



int(rtc_subscribe_int)();
int(read_rtc)(uint32_t address,uint8_t* input);
uint8_t (bcd_to_dec)(uint8_t input);
void (get_date)(Date* date);
int(rtc_unsubscribe_int)();


#endif
