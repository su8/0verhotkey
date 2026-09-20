#   Copyright 09/20/2026 https://github.com/su8/0verlaunch
#   This program is free software; you can redistribute it and/or modify
#   it under the terms of the GNU General Public License as published by
#   the Free Software Foundation; either version 2 of the License, or
#   (at your option) any later version.

#   This program is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#   GNU General Public License for more details.

#   You should have received a copy of the GNU General Public License
#   along with this program; if not, write to the Free Software
#   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
#   MA 02110-1301, USA.

CFLAGS+=-Wall -Wextra -O2 -std=c99 -pipe -pedantic -Wundef -Wshadow -W -Wwrite-strings -Wcast-align -Wstrict-overflow=5 -Wconversion -Wpointer-arith -Wstrict-prototypes -Wformat=2 -Wsign-compare -Wendif-labels -Wredundant-decls -Winit-self
SRCS=hotkey.c printev.c
PROGS=hotkey printev
BIN_DIR=/usr/bin

all: $(PROGS)

%: %.c
	$(CC) $(CFLAGS) -o $@ $<

install: 
	install -D -s -m 755 hotkey $(BIN_DIR)/hotkey
	install -D -s -m 755 printev $(BIN_DIR)/printev

uninstall:
	rm -f $(BIN_DIR)/hotkey
	rm -f $(BIN_DIR)/printev

clean:
	rm -f hotkey
	rm -f printev

.PHONY: all install clean uninstall