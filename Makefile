#
#   khn, invoker the viwer of KwikINF on-line documents
#   Copyright (C) 2013 by KO Myung-Hun <komh@chollian.net>
#
#   This program is free software; you can redistribute it and/or modify it
#   under the terms of the GNU Lesser General Public License as published by
#   the Free Software Foundation; either version 2.1 of the License, or
#   (at your option) any later version.
#
#   This program is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
#   GNU Lesser General Public License for more details.
#
#   You should have received a copy of the GNU Lesser General Public License
#   along with this program; if not, write to the Free Software Foundation,
#   Inc., 51 Franklin Street, Fifth Floor, Boston MA 02110-1301, USA.
#

##### Configuration parts that you can modify
CXX      = g++
CXXFLAGS = -Wall -DOS2EMX_PLAIN_CHAR=1 -IKPMLib
LD       = g++
LDFLAGS  = -Zomf
LIBS     =

ifdef RELEASE
CFLAGS   += -O3
CXXFLAGS += -O3
STRIP     = lxlite /B- /L- /CS
else
CFLAGS   += -O0 -g -DDEBUG
CXXFLAGS += -O0 -g -DDEBUG
LDFLAGS  += -g
STRIP     = echo
endif

RC      = rc
RCFLAGS = -n

RM = rm -f

PROGRAM     = khn
PROGRAM_EXT = .exe

# define to 1 if you don't use RC file
NO_USE_RC  = 1
# define to 1 if you don't use DEF file
#NO_USE_DEF = 1

OBJ_EXT = .o

CXXSRCS = khn.cpp \
          KHNClient.cpp \
          KHelpNdx.cpp \
          KHelpNdxFile.cpp

SUBDIRS = KPMLib

include Makefile.common

$(PROGRAM)$(PROGRAM_EXT) : KPMLib/KPMLib.a
