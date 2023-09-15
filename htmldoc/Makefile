#
# Makefile for HTMLDOC, an HTML document processing program.
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
# Object files...
#

COMMONOBJS =	\
		file.o \
		htmllib.o \
		image.o \
		iso8859.o \
		md5.o \
		progress.o \
		snprintf.o \
		string.o \
		toc.o \
		util.o
HTMLDOCOBJS =	\
		gui.o \
		epub.o \
		html.o \
		htmldoc.o \
		htmlsep.o \
		license.o \
		markdown.o \
		mmd.o \
		ps-pdf.o \
		rc4.o \
		zipc.o
OBJS	=	$(COMMONOBJS) $(HTMLDOCOBJS)

CSRCS	=	\
		file.c \
		md5.c \
		mmd.c \
		rc4.c \
		snprintf.c \
		string.c \
		zipc.c
CXXSRCS	=	\
		epub.cxx \
		gui.cxx \
		html.cxx \
		htmldoc.cxx \
		htmllib.cxx \
		htmlsep.cxx \
		image.cxx \
		iso8859.cxx \
		license.cxx \
		markdown.cxx \
		progress.cxx \
		ps-pdf.cxx \
		testhtml.cxx \
		toc.cxx \
		util.cxx


#
# Make everything...
#

all:	libhtmldoc.so htmldoc$(EXEEXT)


#
# Install everything...
#

install:	all
	$(INSTALL_DIR) $(BUILDROOT)$(bindir)
	$(INSTALL_DIR) $(BUILDROOT)$(libdir)
	$(INSTALL_BIN) libhtmldoc.so $(BUILDROOT)$(libdir)
	$(INSTALL_BIN) htmldoc$(EXEEXT) $(BUILDROOT)$(bindir)


#
# Clean out object and executable files...
#

clean:
	$(RM) $(OBJS) libhtmldoc.so htmldoc$(EXEEXT)


#
# Update dependencies...
#

depend:
	$(CC) -MM $(CFLAGS) $(CSRCS) | sed -e '1,$$s/ \/usr\/include\/[^ ]*//g' -e '1,$$s/ \/usr\/local\/include\/[^ ]*//g' >Dependencies
	$(CXX) -MM $(CXXFLAGS) $(CXXSRCS) | sed -e '1,$$s/ \/usr\/include\/[^ ]*//g' -e '1,$$s/ \/usr\/local\/include\/[^ ]*//g' >>Dependencies


#
# htmldoc
#

libhtmldoc.so:	$(COMMONOBJS) $(HTMLDOCOBJS) ../Makedefs
	echo Linking $@...
	$(CXX) $(LDFLAGS) -shared -Wl,-soname,$(notdir $@) -o libhtmldoc.so $(COMMONOBJS) $(HTMLDOCOBJS) $(LIBS)

htmldoc$(EXEEXT):	libhtmldoc.so $(HTMLDOCOBJS) ../Makedefs
	echo Linking $@...
	$(CXX) $(LDFLAGS) -o htmldoc$(EXEEXT) $(HTMLDOCOBJS) $(LIBS) libhtmldoc.so
	if test `uname` = Darwin; then \
		$(MAKE) -$(MAKEFLAGS) htmldoc.app || exit 1; \
	fi

htmldoc.app:	htmldoc
	echo Creating application bundle...
	$(RM) -r htmldoc.app
	$(MKDIR) htmldoc.app
	$(MKDIR) htmldoc.app/Contents
	$(CP) ../desktop/htmldoc.plist htmldoc.app/Contents/Info.plist
	$(MKDIR) htmldoc.app/Contents/MacOS
	$(CP) htmldoc htmldoc.app/Contents/MacOS
	$(MKDIR) htmldoc.app/Contents/Resources
	$(CP) ../desktop/htmldoc.icns htmldoc.app/Contents/Resources
	$(CP) ../doc/help.html htmldoc.app/Contents/Resources
	$(MKDIR) htmldoc.app/Contents/Resources/data
	$(CP) ../data/cp-* htmldoc.app/Contents/Resources/data
	$(CP) ../data/iso-* htmldoc.app/Contents/Resources/data
	$(CP) ../data/koi8-r htmldoc.app/Contents/Resources/data
	$(CP) ../data/prolog.ps htmldoc.app/Contents/Resources/data
	$(CP) ../data/psglyphs htmldoc.app/Contents/Resources/data
	$(MKDIR) htmldoc.app/Contents/Resources/fonts
	$(CP) ../fonts/*.afm htmldoc.app/Contents/Resources/fonts
	$(CP) ../fonts/*.pfa htmldoc.app/Contents/Resources/fonts


#
# testhtml
#

#
# Dependencies...
#

$(OBJS):	../Makedefs
tls.o:		tls-darwin.c tls-gnutls.c tls-sspi.c
include Dependencies
