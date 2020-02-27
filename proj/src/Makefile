PROG=proj

SRCS = proj.c video_graph.c sprite.c keyboard.c timer.c utils.c game.c colision.c mouse.c aim.c ufo.c asteroids.c

# __LCOM_OPTIMIZED__ disables most of the LCF's overhead (and functionality!)
CPPFLAGS += -pedantic -D __LCOM_OPTIMIZED__

DPADD += ${LIBLCF}
LDADD += -llcf

.include <minix.lcom.mk>
