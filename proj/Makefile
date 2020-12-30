PROG=proj

SRCS = proj.c utils.c videocard.c timer.c keyboard.c mouse.c bricks.c sphere.c background.c animate_sprite.c sprite.c game.c menu.c

# __LCOM_OPTIMIZED__ disables most of the LCF's overhead (and functionality!)
CPPFLAGS += -pedantic -D __LCOM_OPTIMIZED__ 
#CPPFLAGS += -pedantic 

DPADD += ${LIBLCF}
LDADD += -llcf

.include <minix.lcom.mk>
