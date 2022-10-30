/*
 * RTC.h
 *
 *  Created on: Oct 6, 2022
 *      Author: hugop
 */
#include "main.h"


#ifndef SRC_RTC_H_
#define SRC_RTC_H_

#define SECOND_COUNTER_ADDR          0x02
#define MINUTE_COUNTER_ADDR          0x03
#define HOUR_COUNTER_ADDR            0x04
#define YEAR_DATE_COUNTER_ADDR       0x05
#define WEEKDAY_MONTH_COUNTER_ADDR   0x06

#define READ_SALVE_ADDR              0xA1
#define WRITE_SALVE_ADDR             0xA0

typedef enum
{
	LUNDI,
	MARDI,
	MERCREDI,
	JEUDI,
	VENDREDI,
	SAMEDI,
	DIMANCHE,
} weekday_t;

typedef struct
{
	uint8_t   second;
	uint8_t   minute;
	uint8_t   hour;
	weekday_t weekday;
	uint8_t   date;
	uint8_t   month;
	uint8_t   year;
} date_s;

typedef enum
{
	STATE_IDLE,
	STATE_REQ_SEC,
	STATE_REQ_MIN,
	STATE_REQ_HOUR,
} state_t;

void RTC_setup(void);

date_s RTC_get_date(void);

void RTC_start_date_request(void);

void RTC_resume_date_request(void);

#endif /* SRC_RTC_H_ */
