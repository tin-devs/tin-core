if DEBUG
  AM_CFLAGS = -I$(top_srcdir)/src \
	      -Wall -Werror -fstack-protector-all -O0 -g
else
  AM_CFLAGS = -I$(top_srcdir)/src \
	      -Wall -Werror -fstack-protector-all -O3
endif

AM_CFLAGS += $(TOXCORE_CFLAGS)

lib_LTLIBRARIES = libtincore.la
libtincore_la_SOURCES = tin_api.c tin_api.h \
                        tincore.c tincore.h \
                        friends.c friends.h \
                        groups.c groups.h \
                        util.c util.h

otherincludedir = $(includedir)/tincore
otherinclude_HEADERS = tin_api.h

libtincore_la_LIBADD = $(TOXCORE_LIBS)
