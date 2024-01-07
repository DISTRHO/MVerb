#!/usr/bin/make -f
# Makefile for DISTRHO Plugins #
# ---------------------------- #
# Created by falkTX
#

PREFIX ?= /usr/local
LIBDIR ?= lib
BINDIR ?= bin

include dpf/Makefile.base.mk

all: dgl plugins gen

# --------------------------------------------------------------

dgl:
ifeq ($(HAVE_OPENGL),true)
	$(MAKE) -C dpf/dgl opengl FILE_BROWSER_DISABLED=true
endif

plugins: dgl
	$(MAKE) all -C plugins/MVerb

ifneq ($(CROSS_COMPILING),true)
gen: plugins dpf/utils/lv2_ttl_generator
	@$(CURDIR)/dpf/utils/generate-ttl.sh
ifeq ($(MACOS),true)
	@$(CURDIR)/dpf/utils/generate-vst-bundles.sh
endif

dpf/utils/lv2_ttl_generator:
	$(MAKE) -C dpf/utils/lv2-ttl-generator
else
gen:
endif

# --------------------------------------------------------------

clean:
	$(MAKE) clean -C dpf/dgl
	$(MAKE) clean -C dpf/utils/lv2-ttl-generator
	$(MAKE) clean -C plugins/MVerb
	rm -rf bin build

# --------------------------------------------------------------

install: all
	install -d $(DESTDIR)$(PREFIX)/$(LIBDIR)/ladspa \
		$(DESTDIR)$(PREFIX)/$(LIBDIR)/lv2 \
		$(DESTDIR)$(PREFIX)/$(LIBDIR)/vst \
		$(DESTDIR)$(PREFIX)/$(LIBDIR)/vst3 \
		$(DESTDIR)$(PREFIX)/$(LIBDIR)/dssi \
		$(DESTDIR)$(PREFIX)/$(BINDIR)
	install -d $(DESTDIR)$(PREFIX)/$(LIBDIR)/lv2/MVerb.lv2
	install -m 644 bin/MVerb.lv2/* $(DESTDIR)$(PREFIX)/$(LIBDIR)/lv2/MVerb.lv2/
	cp -r bin/MVerb.vst3 $(DESTDIR)$(PREFIX)/$(LIBDIR)/vst3/
	install -m 755 bin/MVerb$(APP_EXT) $(DESTDIR)$(PREFIX)/$(BINDIR)/
	install -m 644 bin/*-ladspa$(LIB_EXT) $(DESTDIR)$(PREFIX)/$(LIBDIR)/ladspa/
	install -m 644 bin/*-vst$(LIB_EXT) $(DESTDIR)$(PREFIX)/$(LIBDIR)/vst/
	install -m 644 bin/*-dssi$(LIB_EXT) $(DESTDIR)$(PREFIX)/$(LIBDIR)/dssi/

uninstall:
	rm -rf $(DESTDIR)$(PREFIX)/$(LIBDIR)/lv2/MVerb.lv2
	rm -rf $(DESTDIR)$(PREFIX)/$(LIBDIR)/vst3/MVerb.vst3
	rm -f $(DESTDIR)$(PREFIX)/$(LIBDIR)/ladspa/MVerb-ladspa$(LIB_EXT)
	rm -f $(DESTDIR)$(PREFIX)/$(LIBDIR)/vst/MVerb-vst$(LIB_EXT)
	rm -f $(DESTDIR)$(PREFIX)/$(LIBDIR)/dssi/MVerb-dssi$(LIB_EXT)
	rm -f $(DESTDIR)$(PREFIX)/$(BINDIR)/MVerb

# --------------------------------------------------------------

.PHONY: plugins
