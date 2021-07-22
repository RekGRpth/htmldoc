#
# Makefile for HTMLDOC font files.
#
# Copyright 2011-2017 by Michael R Sweet.
# Copyright 1997-2010 by Easy Software Products.
#
# This program is free software.  Distribution and use rights are outlined in
# the file "COPYING".
#

#
# Include common definitions...
#

include ../Makedefs


#
# Standard fonts...
#

FONTS	=	\
		Dingbats \
		NimbusMonoPS-Bold \
		NimbusMonoPS-BoldItalic \
		NimbusMonoPS-Italic \
		NimbusMonoPS-Regular \
		NimbusSans-Bold \
		NimbusSans-BoldItalic \
		NimbusSans-Italic \
		NimbusSans-Regular \
		NimbusRoman-Bold \
		NimbusRoman-BoldItalic \
		NimbusRoman-Italic \
		NimbusRoman-Regular \
		Symbol


#
# Make everything...
#

all:


#
# Install everything...
#

install:
	echo "Installing font files in $(datadir)/htmldoc/fonts..."
	$(INSTALL_DIR) $(BUILDROOT)$(datadir)/htmldoc/fonts
	for font in $(FONTS); do \
		$(INSTALL_DATA) $$font.afm $(BUILDROOT)$(datadir)/htmldoc/fonts; \
		$(INSTALL_DATA) $$font.pfa $(BUILDROOT)$(datadir)/htmldoc/fonts; \
	done


#
# Uninstall everything...
#

uninstall:
	echo "Uninstalling font files from $(datadir)/htmldoc/fonts..."
	for font in $(FONTS); do \
		$(RM) $(BUILDROOT)$(datadir)/htmldoc/fonts/$$font.afm; \
		$(RM) $(BUILDROOT)$(datadir)/htmldoc/fonts/$$font.pfa; \
	done
	-$(RMDIR) $(BUILDROOT)$(datadir)/htmldoc/fonts


#
# Clean out object and library files...
#

clean:
