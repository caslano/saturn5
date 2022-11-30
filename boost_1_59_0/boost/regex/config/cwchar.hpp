/*
 *
 * Copyright (c) 1998-2002
 * John Maddock
 *
 * Use, modification and distribution are subject to the 
 * Boost Software License, Version 1.0. (See accompanying file 
 * LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 *
 */
 
 /*
  *   LOCATION:    see http://www.boost.org for most recent version.
  *   FILE         boost/regex/config/cwchar.hpp
  *   VERSION      see <boost/version.hpp>
  *   DESCRIPTION: regex wide character string fixes.
  */

#ifndef BOOST_REGEX_CONFIG_CWCHAR_HPP
#define BOOST_REGEX_CONFIG_CWCHAR_HPP

#include <cwchar>
#include <cwctype>
#include <boost/config.hpp>

#if defined(__STD_RWCOMPILER_H__) || defined(_RWSTD_VER)
// apparently this is required for the RW STL on Linux:
#undef iswalnum
#undef iswalpha
#undef iswblank
#undef iswcntrl
#undef iswdigit
#undef iswgraph
#undef iswlower
#undef iswprint
#undef iswprint
#undef iswpunct
#undef iswspace
#undef iswupper
#undef iswxdigit
#undef iswctype
#undef towlower
#undef towupper
#undef towctrans
#undef wctrans
#undef wctype
#endif

namespace std{

#ifndef BOOST_NO_STDC_NAMESPACE
extern "C"{
#endif

#ifdef iswalnum
inline int (iswalnum)(wint_t i)
{ return iswalnum(i); }
#undef iswalnum
#elif defined(BOOST_NO_STDC_NAMESPACE)
using ::iswalnum;
#endif

#ifdef iswalpha
inline int (iswalpha)(wint_t i)
{ return iswalpha(i); }
#undef iswalpha
#elif defined(BOOST_NO_STDC_NAMESPACE)
using ::iswalpha;
#endif

#ifdef iswcntrl
inline int (iswcntrl)(wint_t i)
{ return iswcntrl(i); }
#undef iswcntrl
#elif defined(BOOST_NO_STDC_NAMESPACE)
using ::iswcntrl;
#endif

#ifdef iswdigit
inline int (iswdigit)(wint_t i)
{ return iswdigit(i); }
#undef iswdigit
#elif defined(BOOST_NO_STDC_NAMESPACE)
using ::iswdigit;
#endif

#ifdef iswgraph
inline int (iswgraph)(wint_t i)
{ return iswgraph(i); }
#undef iswgraph
#elif defined(BOOST_NO_STDC_NAMESPACE)
using ::iswgraph;
#endif

#ifdef iswlower
inline int (iswlower)(wint_t i)
{ return iswlower(i); }
#undef iswlower
#elif defined(BOOST_NO_STDC_NAMESPACE)
using ::iswlower;
#endif

#ifdef iswprint
inline int (iswprint)(wint_t i)
{ return iswprint(i); }
#undef iswprint
#elif defined(BOOST_NO_STDC_NAMESPACE)
using ::iswprint;
#endif

#ifdef iswpunct
inline int (iswpunct)(wint_t i)
{ return iswpunct(i); }
#undef iswpunct
#elif defined(BOOST_NO_STDC_NAMESPACE)
using ::iswpunct;
#endif

#ifdef iswspace
inline int (iswspace)(wint_t i)
{ return iswspace(i); }
#undef iswspace
#elif defined(BOOST_NO_STDC_NAMESPACE)
using ::iswspace;
#endif

#ifdef iswupper
inline int (iswupper)(wint_t i)
{ return iswupper(i); }
#undef iswupper
#elif defined(BOOST_NO_STDC_NAMESPACE)
using ::iswupper;
#endif

#ifdef iswxdigit
inline int (iswxdigit)(wint_t i)
{ return iswxdigit(i); }
#undef iswxdigit
#elif defined(BOOST_NO_STDC_NAMESPACE)
using ::iswxdigit;
#endif

#ifdef towlower
inline wint_t (towlower)(wint_t i)
{ return towlower(i); }
#undef towlower
#elif defined(BOOST_NO_STDC_NAMESPACE)
using ::towlower;
#endif

#ifdef towupper
inline wint_t (towupper)(wint_t i)
{ return towupper(i); }
#undef towupper
#elif defined(BOOST_NO_STDC_NAMESPACE)
using :: towupper;
#endif

#ifdef wcscmp
inline int (wcscmp)(const wchar_t *p1, const wchar_t *p2)
{ return wcscmp(p1,p2); }
#undef wcscmp
#elif defined(BOOST_NO_STDC_NAMESPACE)
using ::wcscmp;
#endif

#ifdef wcscoll
inline int (wcscoll)(const wchar_t *p1, const wchar_t *p2)
{ return wcscoll(p1,p2); }
#undef wcscoll
#elif defined(BOOST_NO_STDC_NAMESPACE) && !defined(UNDER_CE)
using ::wcscoll;
#endif

#ifdef wcscpy
inline wchar_t *(wcscpy)(wchar_t *p1, const wchar_t *p2)
{ return wcscpy(p1,p2); }
#undef wcscpy
#elif defined(BOOST_NO_STDC_NAMESPACE)
using ::wcscpy;
#endif

#ifdef wcslen
inline size_t (wcslen)(const wchar_t *p)
{ return wcslen(p); }
#undef wcslen
#elif defined(BOOST_NO_STDC_NAMESPACE)
using ::wcslen;
#endif

#ifdef wcsxfrm
size_t wcsxfrm(wchar_t *p1, const wchar_t *p2, size_t s)
{ return wcsxfrm(p1,p2,s); }
#undef wcsxfrm
#elif defined(BOOST_NO_STDC_NAMESPACE)
using ::wcsxfrm;
#endif


#ifndef BOOST_NO_STDC_NAMESPACE
} // extern "C"
#endif

} // namespace std

#endif


/* cwchar.hpp
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
*/