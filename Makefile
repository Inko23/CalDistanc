CC	= gcc
CFLAGS  = -c -O2
SRCS	= check_arguments.c close_files.c main.c read_map.c read_list.c \
	  print.c initial_setting.c initialize.c cal_all_dist.c maze.c SA.c
OBJS	= $(SRCS:.c=.o)
HEADER	= decs.h
BINNAME = opt_place.exe
BINDIR = ${HOME}/bin/

.SUFFIXES: .o .c

a.out	: ${OBJS}
	${CC} ${OBJS} -o ${BINNAME}

fin	: ${OBJS}
	${CC} ${OBJS} -o ${BINNAME}
	mv ${BINNAME} ${BINDIR}
	rm *.o

.c.o	:
	$(CC) $(CFLAGS) $<

${OBJS}	: ${HEADER}

clean	:
	rm *.o
