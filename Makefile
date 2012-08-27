OBJS=schm.o schemed.o
CPPFLAGS=-s -O2
schemed: $(OBJS)
	$(CC) -o $@ $(OBJS)