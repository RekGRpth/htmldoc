/*
 * ISO-8859-1 conversion routines for HTMLDOC, an HTML document
 * processing program.
 *
 * Copyright 2011-2024 by Michael R Sweet.
 * Copyright 1997-2010 by Easy Software Products.  All rights reserved.
 *
 * This program is free software.  Distribution and use rights are outlined in
 * the file "COPYING".
 */

#include <stdio.h>
#include <stdlib.h>

#include "html.h"
#include "types.h"


/*
 * Lookup table structure...
 */

typedef struct
{
  uchar	name[12];
  int	value;
} lut_t;

static lut_t	iso8859_numbers[] =
		{
		  { "AElig",	198 },
		  { "Aacute",	193 },
		  { "Acirc",	194 },
		  { "Agrave",	192 },
		  { "Alpha",	913 },
		  { "Aring",	197 },
		  { "Atilde",	195 },
		  { "Auml",	196 },
		  { "Beta",	914 },
		  { "Ccedil",	199 },
		  { "Chi",	935 },
		  { "Dagger",	8225 },
		  { "Delta",	916 },
		  { "ETH",	208 },
		  { "Eacute",	201 },
		  { "Ecirc",	202 },
		  { "Egrave",	200 },
		  { "Epsilon",	917 },
		  { "Eta",	919 },
		  { "Euml",	203 },
		  { "Gamma",	915 },
		  { "Iacute",	205 },
		  { "Icirc",	206 },
		  { "Igrave",	204 },
		  { "Iota",	921 },
		  { "Iuml",	207 },
		  { "Kappa",	922 },
		  { "Lambda",	923 },
		  { "Mu",	924 },
		  { "Ntilde",	209 },
		  { "Nu",	925 },
		  { "OElig",	338 },
		  { "Oacute",	211 },
		  { "Ocirc",	212 },
		  { "Ograve",	210 },
		  { "Omega",	937 },
		  { "Omicron",	927 },
		  { "Oslash",	216 },
		  { "Otilde",	213 },
		  { "Ouml",	214 },
		  { "Phi",	934 },
		  { "Pi",	928 },
		  { "Prime",	8243 },
		  { "Psi",	936 },
		  { "Rho",	929 },
		  { "Scaron",	352 },
		  { "Sigma",	931 },
		  { "THORN",	222 },
		  { "Tau",	932 },
		  { "Theta",	920 },
		  { "Uacute",	218 },
		  { "Ucirc",	219 },
		  { "Ugrave",	217 },
		  { "Upsilon",	933 },
		  { "Uuml",	220 },
		  { "Xi",	926 },
		  { "Yacute",	221 },
		  { "Yuml",	376 },
		  { "Zeta",	918 },
		  { "aacute",	225 },
		  { "acirc",	226 },
		  { "acute",	180 },
		  { "aelig",	230 },
		  { "agrave",	224 },
		  { "alefsym",	8501 },
		  { "alpha",	945 },
		  { "amp",	38 },
		  { "and",	8743 },
		  { "ang",	8736 },
		  { "aring",	229 },
		  { "asymp",	8776 },
		  { "atilde",	227 },
		  { "auml",	228 },
		  { "bdquo",	8222 },
		  { "beta",	946 },
		  { "brvbar",	166 },
		  { "bull",	8226 },
		  { "cap",	8745 },
		  { "ccedil",	231 },
		  { "cedil",	184 },
		  { "cent",	162 },
		  { "chi",	967 },
		  { "circ",	710 },
		  { "clubs",	9827 },
		  { "cong",	8773 },
		  { "copy",	169 },
		  { "crarr",	8629 },
		  { "cup",	8746 },
		  { "curren",	164 },
		  { "dArr",	8659 },
		  { "dagger",	8224 },
		  { "darr",	8595 },
		  { "deg",	176 },
		  { "delta",	948 },
		  { "diams",	9830 },
		  { "divide",	247 },
		  { "eacute",	233 },
		  { "ecirc",	234 },
		  { "egrave",	232 },
		  { "empty",	8709 },
		  { "emsp",	8195 },
		  { "ensp",	8194 },
		  { "epsilon",	949 },
		  { "equiv",	8801 },
		  { "eta",	951 },
		  { "eth",	240 },
		  { "euml",	235 },
		  { "euro",	8364 },
		  { "exist",	8707 },
		  { "fnof",	402 },
		  { "forall",	8704 },
		  { "frac12",	189 },
		  { "frac14",	188 },
		  { "frac34",	190 },
		  { "frasl",	8260 },
		  { "gamma",	947 },
		  { "ge",	8805 },
		  { "gt",	62 },
		  { "hArr",	8660 },
		  { "harr",	8596 },
		  { "hearts",	9829 },
		  { "hellip",	8230 },
		  { "iacute",	237 },
		  { "icirc",	238 },
		  { "iexcl",	161 },
		  { "igrave",	236 },
		  { "image",	8465 },
		  { "infin",	8734 },
		  { "int",	8747 },
		  { "iota",	953 },
		  { "iquest",	191 },
		  { "isin",	8712 },
		  { "iuml",	239 },
		  { "kappa",	954 },
		  { "lArr",	8656 },
		  { "lambda",	955 },
		  { "lang",	9001 },
		  { "laquo",	171 },
		  { "larr",	8592 },
		  { "lceil",	8968 },
		  { "ldquo",	8220 },
		  { "le",	8804 },
		  { "lfloor",	8970 },
		  { "lowast",	8727 },
		  { "loz",	9674 },
		  { "lrm",	8206 },
		  { "lsaquo",	8249 },
		  { "lsquo",	8216 },
		  { "lt",	60 },
		  { "macr",	175 },
		  { "mdash",	8212 },
		  { "micro",	181 },
		  { "middot",	183 },
		  { "minus",	8722 },
		  { "mu",	956 },
		  { "nabla",	8711 },
		  { "nbsp",	160 },
		  { "ndash",	8211 },
		  { "ne",	8800 },
		  { "ni",	8715 },
		  { "not",	172 },
		  { "notin",	8713 },
		  { "nsub",	8836 },
		  { "ntilde",	241 },
		  { "nu",	957 },
		  { "oacute",	243 },
		  { "ocirc",	244 },
		  { "oelig",	339 },
		  { "ograve",	242 },
		  { "oline",	8254 },
		  { "omega",	969 },
		  { "omicron",	959 },
		  { "oplus",	8853 },
		  { "or",	8744 },
		  { "ordf",	170 },
		  { "ordm",	186 },
		  { "oslash",	248 },
		  { "otilde",	245 },
		  { "otimes",	8855 },
		  { "ouml",	246 },
		  { "para",	182 },
		  { "part",	8706 },
		  { "permil",	8240 },
		  { "perp",	8869 },
		  { "phi",	966 },
		  { "pi",	960 },
		  { "piv",	982 },
		  { "plusmn",	177 },
		  { "pound",	163 },
		  { "prime",	8242 },
		  { "prod",	8719 },
		  { "prop",	8733 },
		  { "psi",	968 },
		  { "quot",	34 },
		  { "rArr",	8658 },
		  { "radic",	8730 },
		  { "rang",	9002 },
		  { "raquo",	187 },
		  { "rarr",	8594 },
		  { "rceil",	8969 },
		  { "rdquo",	8221 },
		  { "real",	8476 },
		  { "reg",	174 },
		  { "rfloor",	8971 },
		  { "rho",	961 },
		  { "rlm",	8207 },
		  { "rsaquo",	8250 },
		  { "rsquo",	8217 },
		  { "sbquo",	8218 },
		  { "scaron",	353 },
		  { "sdot",	8901 },
		  { "sect",	167 },
		  { "shy",	173 },
		  { "sigma",	963 },
		  { "sigmaf",	962 },
		  { "sim",	8764 },
		  { "spades",	9824 },
		  { "sub",	8834 },
		  { "sube",	8838 },
		  { "sum",	8721 },
		  { "sup",	8835 },
		  { "sup1",	185 },
		  { "sup2",	178 },
		  { "sup3",	179 },
		  { "supe",	8839 },
		  { "szlig",	223 },
		  { "tau",	964 },
		  { "there4",	8756 },
		  { "theta",	952 },
		  { "thetasym",	977 },
		  { "thinsp",	8201 },
		  { "thorn",	254 },
		  { "tilde",	732 },
		  { "times",	215 },
		  { "trade",	8482 },
		  { "uArr",	8657 },
		  { "uacute",	250 },
		  { "uarr",	8593 },
		  { "ucirc",	251 },
		  { "ugrave",	249 },
		  { "uml",	168 },
		  { "upsih",	978 },
		  { "upsilon",	965 },
		  { "uuml",	252 },
		  { "weierp",	8472 },
		  { "xi",	958 },
		  { "yacute",	253 },
		  { "yen",	165 },
		  { "yuml",	255 },
		  { "zeta",	950 },
		  { "zwj",	8205 },
		  { "zwnj",	8204 }
		};
static lut_t	*iso8859_names[256];

static int	compare_lut(lut_t *, lut_t *);


/*
 * 'iso8859()' - Return the 8-bit character value of a glyph name.
 */

uchar					/* O - ISO-8859-1 equivalent */
iso8859(uchar *name)			/* I - Glyph name */
{
  lut_t	key,				/* Lookup table key */
	*match;				/* Matching entry pointer */
  int	ch;				/* Character */


  if (strlen((char *)name) == 1)
    return (name[0]);
  else if (name[0] == '#')
  {
    // Return a decimal or hex character...
    if (name[1] == 'x')
      ch = strtol((char *)name + 2, NULL, 16);
    else
      ch = strtol((char *)name + 1, NULL, 10);

    if (ch > 0xffff || ch <= 0)
      return (0);
  }
  else
  {
    strlcpy((char *)key.name, (char *)name, sizeof(key.name));
    match = (lut_t *)bsearch(&key, iso8859_numbers,
                             sizeof(iso8859_numbers) / sizeof(iso8859_numbers[0]),
                             sizeof(iso8859_numbers[0]),
                             (int (*)(const void *, const void *))compare_lut);

    if (match == NULL)
      return (0);
    else
      ch = match->value;
  }

  if (ch > 0x7f && _htmlUTF8)
  {
    // Map Unicode value...
    ch = htmlMapUnicode(ch);
  }
  else if (ch > 0x7f)
  {
    // Lookup Unicode value in the current charset...
    const char *glyph;
    char uniglyph[32];
    int newch;

    if (!_htmlInitialized)
      htmlSetCharSet("utf-8");

    if ((glyph = _htmlGlyphsAll[ch]) == NULL)
    {
      snprintf(uniglyph, sizeof(uniglyph), "uni%04x", ch);
      glyph = uniglyph;
    }

    for (newch = 128; newch < 256; newch ++)
      if (_htmlGlyphs[newch] && !strcmp(_htmlGlyphs[newch], glyph))
	break;

    if (newch >= 256)
    {
      // Not part of the standard charset, see if we have room for a
      // few extras...
      for (newch = 128; newch < 256; newch ++)
        if (!_htmlGlyphs[newch])
	{
	  // Yes, assign this character to it...
	  if (glyph == uniglyph)
	    _htmlGlyphsAll[ch] = _htmlGlyphs[newch] = strdup(glyph);
	  else
	    _htmlGlyphs[newch] = glyph;

          _htmlUnicode[newch] = ch;

          // Update font widths...
          for (int typeface = 0; typeface < TYPE_MAX; typeface ++)
	  {
	    for (int style = 0; style < STYLE_MAX; style ++)
	    {
	      if (_htmlWidthsLoaded[typeface][style])
	      {
	        _htmlWidths[typeface][style][newch] = _htmlWidthsAll[typeface][style][ch];
	      }
	    }
	  }

	  // Return the new character...
	  return ((uchar)newch);
	}

      // No room, return nul...
      return (0);
    }
    else
      ch = newch;
  }

  return ((uchar)ch);
}


/*
 * 'iso8859()' - Return the glyph name of an 8-bit character value.
 */

uchar *			/* O - Glyph name */
iso8859(uchar value)	/* I - ISO-8859-1 equivalent */
{
  int		i;		/* Looping var */
  int		ch;		/* Current character */
  static int	first_time = 1;	/* First time called? */
  static uchar	buf[255];	/* Character buffer */


  if (first_time)
  {
    memset(iso8859_names, 0, sizeof(iso8859_names));

    for (i = 0; i < (int)(sizeof(iso8859_numbers) / sizeof(iso8859_numbers[0])); i ++)
      if ((ch = iso8859_numbers[i].value) < 128)
	iso8859_names[ch] = iso8859_numbers + i;
      else
      {
	// Lookup Unicode value in the current charset...
	const char *glyph;
	char uniglyph[32];

        if ((glyph = _htmlGlyphsAll[ch]) == NULL)
	{
	  snprintf(uniglyph, sizeof(uniglyph), "uni%04x", ch);
	  glyph = uniglyph;
	}

	for (ch = 128; ch < 256; ch ++)
	  if (_htmlGlyphs[ch] && !strcmp(_htmlGlyphs[ch], glyph))
	  {
	    iso8859_names[ch] = iso8859_numbers + i;
	    break;
	  }
      }

    first_time = 0;
  }

  if (iso8859_names[value] == NULL)
  {
    if (value < 127)
    {
      // ASCII...
      buf[0] = value;
      buf[1] = '\0';
    }
    else if (_htmlUTF8)
    {
      // UTF-8...
      int unich = _htmlUnicode[value];	// Unicode character

      if (unich < 0x400)
      {
        buf[0] = 0xc0 | (unich >> 6);
        buf[1] = 0x80 | (unich & 0x3f);
        buf[2] = '\0';
      }
      else if (unich < 0x10000)
      {
        buf[0] = 0xe0 | (unich >> 12);
        buf[1] = 0x80 | ((unich >> 6) & 0x3f);
        buf[2] = 0x80 | (unich & 0x3f);
        buf[3] = '\0';
      }
      else
      {
        buf[0] = 0xf0 | (unich >> 18);
        buf[1] = 0x80 | ((unich >> 12) & 0x3f);
        buf[2] = 0x80 | ((unich >> 6) & 0x3f);
        buf[3] = 0x80 | (unich & 0x3f);
        buf[4] = '\0';
      }
    }
    else
    {
      // Character-set neutral way to map to Unicode...
      snprintf((char *)buf, sizeof(buf), "&#%d;", _htmlUnicode[value]);
    }
  }
  else
  {
    snprintf((char *)buf, sizeof(buf), "&%s;", iso8859_names[value]->name);
  }

  return (buf);
}


/*
 * 'xhtml_entity()' - Return the UTF-8 character or XHTML entity.
 */

const uchar *                           /* O - XHTML string */
xhtml_entity(uchar ch)                  /* I - Character */
{
  static uchar	buf[5];                 /* UTF-8 character buffer */


  if (ch == '&')
    return ((uchar *)"&amp;");
  else if (ch == '<')
    return ((uchar *)"&lt;");
  else if (ch == '>')
    return ((uchar *)"&gt;");
  else if (ch == '\"')
    return ((uchar *)"&quot;");
  else if (ch >= ' ' && ch < 0x7f)
  {
    // US ASCII
    buf[0] = ch;
    buf[1] = '\0';

    return (buf);
  }
  else
  {
    // Unicode -> UTF-8
    int unich = _htmlUnicode[ch];

    if (unich < 0x80)
    {
      // 1-byte US ASCII
      buf[0] = (uchar)unich;
      buf[1] = '\0';
    }
    else if (unich < 0x800)
    {
      // 2-byte UTF-8
      buf[0] = (uchar)(0xc0 | (unich >> 6));
      buf[1] = (uchar)(0x80 | (unich & 0x3f));
      buf[2] = '\0';
    }
    else if (unich < 0x10000)
    {
      // 3-byte UTF-8
      buf[0] = (uchar)(0xe0 | (unich >> 12));
      buf[1] = (uchar)(0x80 | ((unich >> 6) & 0x3f));
      buf[2] = (uchar)(0x80 | (unich & 0x3f));
      buf[3] = '\0';
    }
    else
    {
      // 4-byte UTF-8
      buf[0] = (uchar)(0xf0 | (unich >> 18));
      buf[1] = (uchar)(0x80 | ((unich >> 12) & 0x3f));
      buf[2] = (uchar)(0x80 | ((unich >> 6) & 0x3f));
      buf[3] = (uchar)(0x80 | (unich & 0x3f));
      buf[4] = '\0';
    }

    return (buf);
  }
}


/*
 * 'compare_lut()' - Compare two glyphs.
 */

static int		/* O - 0 if equal, -1 if a<b, 1 if a>b */
compare_lut(lut_t *a,	/* I - First glyph */
            lut_t *b)	/* I - Second glyph */
{
  return (strcmp((char *)a->name, (char *)b->name));
}
