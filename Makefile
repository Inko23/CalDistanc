CC	= gcc
CFLAGS  = -c -O2
SRCS	= check_arguments.c close_files.c main.c read_map.c read_list.c \
	  print.c initial_setting.c initialize.c cal_all_dist.c maze.c
OBJS	= $(SRCS:.c=.o)
HEADER	= decs.h
BINDIR = ${HOME}/bin/

.SUFFIXES: .o .c

a.out	: ${OBJS}
	${CC} ${OBJS}

fin	: ${OBJS}
	${CC} ${OBJS} -o ${BINNAME}
	mv ${BINNAME} ${BINDIR}
	rm *.o

.c.o	:
	$(CC) $(CFLAGS) $<

${OBJS}	: ${HEADER}

clean	:
	rm *.o
