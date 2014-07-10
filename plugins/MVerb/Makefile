#!/usr/bin/make -f
# Makefile for DISTRHO Plugins #
# ---------------------------- #
# Created by falkTX
#

# --------------------------------------------------------------
# Project name, used for binaries

NAME = MVerb

# --------------------------------------------------------------
# Files to build

OBJS_DSP = \
	DistrhoPluginMVerb.cpp.o

OBJS_UI  = \
	DistrhoArtworkMVerb.cpp.o \
	DistrhoUIMVerb.cpp.o \
	font/Kh-Kangrey.cpp

# --------------------------------------------------------------
# Do some magic

include ../Makefile.mk

# --------------------------------------------------------------
# Enable all possible plugin types

ifeq ($(LINUX),true)
all: jack ladspa dssi lv2_sep vst
else
all: ladspa dssi lv2_sep vst
endif

# --------------------------------------------------------------
