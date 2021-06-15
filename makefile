.SUFFIXES:

all: minmail

clean:; rm -rf minmail all.c pieces

CFLAGS := `pkg-config --cflags gmime-3.0 --libs gmime-3.0`

ifneq ($(GMIME_SRC),)
CFLAGS := -I $(GMIME_SRC) -L $(GMIME_SRC)/gmime/.libs -Wl,-rpath,$(GMIME_SRC)/gmime/.libs $(CFLAGS)
endif

minmail: all.c _usage.c
	gcc -Wall -g -o $@ $< $(CFLAGS)

all.c: makefile $(filter-out all.c, $(wildcard *.c))
	for i in [^_]*.c; do case $$i in all*) continue ;; esac; \
	echo '#include "'$$i'"'; done >$@

_usage.c: usage.txt makefile
	perl -lpe 's/"/\\"/g; s/\A/"/; s/\Z/\\n"/;' $< >$@.tmp
	mv $@.tmp $@

test: minmail
	find /tmp/minmail.tmp -type f | xargs ./minmail --wreak-havok -v -v

valgrind: minmail
	find /tmp/minmail.tmp -type f | xargs valgrind ./minmail -v
