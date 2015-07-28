# Created with genmake.pl v1.1 on Wed Mar 29 14:51:21 2006
# genmake.pl home: http://muquit.com/muquit/software/
# Copryright: GNU GPL (http://www.gnu.org/copyleft/gpl.html)
##----------------------------------------------------------------------------
rm=/bin/rm -f
CC= g++ -O2 -Wall -g -ansi
DEFS=  
PROGNAME= connect4
INCLUDES=  
LIBS=


DEFINES= $(INCLUDES) $(DEFS) 
CFLAGS= $(DEFINES)

SRCS = state.cc \
	simulate.cc \
	main.cc \
	human.cc \
	random.cc \
	simple.cc \
	get_player.cc \
	offensive.cc \
	better_random.cc \
	thmmqc_main.cc \
	thmmqc_circle.cc \
	thmmqc_find_must_moves.cc \
	thmmqc_find_pattern.cc \
	thmmqc_count_pattern.cc \
	thmmqc_stretch.cc \
	thmmqc_find_winner.cc \
	thmmqc_play_piece.cc \
	thmmqc_print_board.cc \
	thmmqc_read_board.cc \
	thmmqc_count_death_spots.cc
OBJS = state.o \
	simulate.o \
	main.o \
	human.o \
	random.o \
	simple.o \
	get_player.o \
	offensive.o \
	better_random.o \
	thmmqc_main.o \
	thmmqc_circle.o \
	thmmqc_find_must_moves.o \
	thmmqc_find_pattern.o \
	thmmqc_count_pattern.o \
	thmmqc_stretch.o \
	thmmqc_find_winner.o \
	thmmqc_play_piece.o \
	thmmqc_print_board.o \
	thmmqc_read_board.o \
	thmmqc_count_death_spots.o
.cc.o:
	$(rm) $@
	$(CC) $(CFLAGS) -c $*.cc

all: $(PROGNAME)

$(PROGNAME) : $(OBJS)
	$(CC) $(CFLAGS) -o $(PROGNAME) $(OBJS) $(LIBS)

clean:
	$(rm) $(OBJS) $(PROGNAME) core *~ $(PROGNAME).exe
