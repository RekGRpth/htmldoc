/*
 * Header file for HTMLDOC, a HTML document processing program.
 *
 * Copyright 2011-2023 by Michael R Sweet.
 * Copyright 1997-2010 by Easy Software Products.  All rights reserved.
 *
 * This program is free software.  Distribution and use rights are outlined in
 * the file "COPYING".
 */

/*
 * Include necessary headers.
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "html.h"
#include "image.h"
#include "debug.h"
#include "progress.h"

#ifdef HAVE_LIBFLTK
#  include "gui.h"
#endif /* HAVE_LIBFLTK */

#ifdef WIN32	    /* Include all 8 million Windows header files... */
#  include <windows.h>
#endif /* WIN32 */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/*
 * Macro to get rid of "unreferenced variable xyz" warnings...
 */

#define REF(x)		(void)x;


/*
 * Output type...
 */

enum
{
  OUTPUT_BOOK,
  OUTPUT_CONTINUOUS,
  OUTPUT_WEBPAGES
};


/*
 * PDF constants...
 */

enum	/* PDF page mode */
{
  PDF_DOCUMENT,
  PDF_OUTLINE,
  PDF_FULLSCREEN
};

enum	/* PDF page layout */
{
  PDF_SINGLE,
  PDF_ONE_COLUMN,
  PDF_TWO_COLUMN_LEFT,
  PDF_TWO_COLUMN_RIGHT
};

enum	/* PDF first page */
{
  PDF_PAGE_1,
  PDF_TOC,
  PDF_CHAPTER_1
};

enum	/* PDF transition effect */
{
  PDF_NONE,
  PDF_BOX_INWARD,
  PDF_BOX_OUTWARD,
  PDF_DISSOLVE,
  PDF_GLITTER_DOWN,
  PDF_GLITTER_DOWN_RIGHT,
  PDF_GLITTER_RIGHT,
  PDF_HORIZONTAL_BLINDS,
  PDF_HORIZONTAL_SWEEP_INWARD,
  PDF_HORIZONTAL_SWEEP_OUTWARD,
  PDF_VERTICAL_BLINDS,
  PDF_VERTICAL_SWEEP_INWARD,
  PDF_VERTICAL_SWEEP_OUTWARD,
  PDF_WIPE_DOWN,
  PDF_WIPE_LEFT,
  PDF_WIPE_RIGHT,
  PDF_WIPE_UP
};

enum	/* PDF document permissions */
{
  PDF_PERM_PRINT = 4,
  PDF_PERM_MODIFY = 8,
  PDF_PERM_COPY = 16,
  PDF_PERM_ANNOTATE = 32
};


/*
 * Globals...
 */

#ifdef _HTMLDOC_CXX_
#  define VAR
#  define VALUE(x)	=x
#  define NULL3		={0,0,0}
#else
#  define VAR		extern
#  define VALUE(x)
#  define NULL3
#endif /* _HTML_DOC_CXX_ */

VAR int		Verbosity	VALUE(-1);	/* Verbosity */
VAR int		OverflowErrors	VALUE(0);	/* Show errors on overflow */
VAR int		StrictHTML	VALUE(0);	/* Do strict HTML checking */
VAR int		CGIMode		VALUE(0);	/* Running as CGI? */
VAR int		Errors		VALUE(0);	/* Number of errors */
VAR int		Compression	VALUE(9);	/* Non-zero means compress PDFs */
VAR int		TitlePage	VALUE(0),	/* Need a title page */
		TocLevels	VALUE(0),	/* Number of table-of-contents levels */
		TocLinks	VALUE(0),	/* Generate links */
		TocNumbers	VALUE(0),	/* Generate heading numbers */
		TocDocCount	VALUE(0);	/* Number of chapters */
VAR int		OutputType	VALUE(OUTPUT_WEBPAGES);
						/* Output a "book", etc. */
VAR char	OutputPath[1024] VALUE("");	/* Output directory/name */
VAR int		OutputFiles	VALUE(0),	/* Generate multiple files? */
		OutputColor	VALUE(1);	/* Output color images */
VAR int		OutputJPEG	VALUE(0);	/* JPEG compress images? */
VAR int		PDFVersion	VALUE(14);	/* Version of PDF to support */
VAR int		PDFPageMode	VALUE(PDF_DOCUMENT),
						/* PageMode attribute */
		PDFPageLayout	VALUE(PDF_SINGLE),
						/* PageLayout attribute */
		PDFFirstPage	VALUE(PDF_PAGE_1),
						/* First page */
		PDFEffect	VALUE(PDF_NONE);/* Page transition effect */
VAR double	PDFEffectDuration VALUE(1.0),	/* Page effect duration */
		PDFPageDuration	VALUE(10.0);	/* Page duration */
VAR int		Encryption	VALUE(0),	/* Encrypt the PDF file? */
		Permissions	VALUE(-4);	/* File permissions? */
VAR char	OwnerPassword[33] VALUE(""),	/* Owner password */
		UserPassword[33] VALUE("");	/* User password */
VAR int		EmbedFonts	VALUE(0);	/* Embed fonts? */
VAR int		PSLevel		VALUE(0),	/* Language level (0 for PDF) */
		PSCommands	VALUE(0),	/* Output PostScript commands? */
		XRXComments	VALUE(0);	/* Output Xerox comments? */
VAR int		PageWidth	VALUE(595),	/* Page width in points */
		PageLength	VALUE(842),	/* Page length in points */
		PageLeft	VALUE(36),	/* Left margin */
		PageRight	VALUE(36),	/* Right margin */
		PageTop		VALUE(36),	/* Top margin */
		PageBottom	VALUE(36),	/* Bottom margin */
		PagePrintWidth,			/* Printable width */
		PagePrintLength,		/* Printable length */
		PageDuplex	VALUE(0),	/* Adjust margins/pages for duplexing? */
		Landscape	VALUE(0),	/* Landscape orientation? */
		NumberUp	VALUE(1);	/* Number-up pages */

VAR int		PreIndent	VALUE(36);	/* Indentation of PRE content */

VAR typeface_t	HeadFootType	VALUE(TYPE_SANS);
						/* Typeface for header & footer */
VAR style_t	HeadFootStyle	VALUE(STYLE_NORMAL);
						/* Type style */
VAR double	HeadFootSize	VALUE(11.0f);	/* Size of header & footer */

VAR char	*Header[3]	NULL3,		/* Header for regular pages */
		*Header1[3]	NULL3,		/* Header for first pages */
		*TocHeader[3]	NULL3,		/* Header for TOC pages */
		*Footer[3]	NULL3,		/* Regular page footer */
		*TocFooter[3]	NULL3,		/* Footer for TOC pages */
		TocTitle[1024]	VALUE("Table of Contents");
						/* TOC title string */

VAR char	TitleImage[1024] VALUE(""),	/* Title page image */
		Letterhead[1024] VALUE(""),	/* Letterhead image */
		LogoImage[1024]	VALUE(""),	/* Logo image */
		BodyColor[255]	VALUE(""),	/* Body color */
		BodyImage[1024]	VALUE(""),	/* Body image */
		LinkColor[255]	VALUE("");	/* Link color */

VAR char	HFImage[MAX_HF_IMAGES][1024]	/* Header/footer images */
#  ifdef _HTMLDOC_CXX_
= { "" }
#  endif /* _HTMLDOC_CXX_ */
;

VAR int		LinkStyle	VALUE(1);	/* 1 = underline, 0 = plain */
VAR int		Links		VALUE(1);	/* 1 = generate links, 0 = no links */
VAR char	Path[2048]	VALUE(""),	/* Search path */
		Proxy[1024]	VALUE("");	/* Proxy URL */

VAR const char	*PDFModes[3]			/* Mode strings */
#  ifdef _HTMLDOC_CXX_
= { "document", "outline", "fullscreen" }
#  endif /* _HTMLDOC_CXX_ */
;
VAR const char	*PDFLayouts[4]			/* Layout strings */
#  ifdef _HTMLDOC_CXX_
= { "single", "one", "twoleft", "tworight" }
#  endif /* _HTMLDOC_CXX_ */
;
VAR const char	*PDFPages[3]			/* First page strings */
#  ifdef _HTMLDOC_CXX_
= { "p1", "toc", "c1" }
#  endif /* _HTMLDOC_CXX_ */
;
VAR const char	*PDFEffects[17]			/* Effect strings */
#  ifdef _HTMLDOC_CXX_
= { "none", "bi", "bo", "d", "gd", "gdr", "gr", "hb", "hsi", "hso",
    "vb", "vsi", "vso", "wd", "wl", "wr", "wu" }
#  endif /* _HTMLDOC_CXX_ */
;

#ifdef HAVE_LIBFLTK
VAR GUI		*BookGUI	VALUE(NULL);	/* GUI for book files */
#  ifdef WIN32					/* Editor for HTML files */
VAR char	HTMLEditor[1024] VALUE("notepad.exe \"%s\"");
#  elif defined(__APPLE__)
VAR char	HTMLEditor[1024] VALUE("bbedit %s");
#  elif defined(__linux)
VAR char	HTMLEditor[1024] VALUE("gedit %s");
#  else
VAR char	HTMLEditor[1024] VALUE("nedit %s");
#  endif /* WIN32 */
VAR int		Tooltips	VALUE(0);	/* Show tooltips? */
#endif /* HAVE_LIBFLTK */


/*
 * Prototypes...
 */

extern int	pspdf_export(tree_t *document, tree_t *toc);
extern int	pspdf_export_out(tree_t *document, tree_t *toc, FILE *out);

extern int	epub_export(tree_t *document, tree_t *toc);

extern int	html_export(tree_t *document, tree_t *toc);

extern int	htmlsep_export(tree_t *document, tree_t *toc);

extern tree_t	*toc_build(tree_t *tree);

extern void	get_color(const uchar *c, float *rgb, int defblack = 1);
extern const char *get_fmt(char **formats);
extern void	get_format(const char *fmt, char **formats);
extern int	get_measurement(const char *s, float mul = 1.0f);
extern void	set_page_size(const char *size);

extern void	prefs_load(void);
extern void	prefs_save(void);
extern void	prefs_set_paths(void);

extern char	*format_number(int n, char f);

#ifdef __cplusplus
}
#endif /* __cplusplus */
