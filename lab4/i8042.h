#ifndef _LCOM_I8042_H_
#define _LCOM_I8042_H_

#include <lcom/lcf.h>

/** @defgroup i8042 i8042
 * @{
 *
 *
 */

#define IRQ1 1
#define IRQ12 12
#define MAKE_BREAK 0x80



/*PORTS*/
#define OUT_BUFF   0x60
#define STATUS_REG 0x64





#define ESC_KEY    0x81
#define TWO_BYTES  0xE0
#define RCMD       0x20
#define WCMD       0x60
#define DELAY_US   20000

/*Errors*/
#define PARITY       BIT(7)
#define TIMEOUT      BIT(6)
#define IBUFFER_FULL BIT(1)
#define OBUFFER_FULL  BIT(0)



#endif /* _LCOM_I8042_H */
