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

FILES_DSP = \
	DistrhoPluginMVerb.cpp

FILES_UI  = \
	DistrhoArtworkMVerb.cpp \
	DistrhoUIMVerb.cpp

# --------------------------------------------------------------
# Do some magic

FILE_BROWSER_DISABLED = true
include ../../dpf/Makefile.plugins.mk

# --------------------------------------------------------------
# Enable all possible plugin types

ifeq ($(HAVE_JACK),true)
TARGETS += jack
endif

ifeq ($(BUILD_LADSPA),true)
TARGETS += ladspa
endif

ifeq ($(BUILD_LV2),true)
TARGETS += lv2_dsp
ifeq ($(HAVE_DGL),true)
TARGETS += lv2_sep
endif
endif

ifeq ($(BUILD_VST),true)
TARGETS += vst2
TARGETS += vst3
endif

ifeq ($(BUILD_DSSI),true)
TARGETS += dssi_dsp
ifeq ($(HAVE_DGL),true)
ifeq ($(HAVE_LIBLO),true)
TARGETS += dssi_ui
endif
endif
endif

all: $(TARGETS)

# --------------------------------------------------------------
