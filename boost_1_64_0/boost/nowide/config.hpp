//
//  Copyright (c) 2012 Artyom Beilis (Tonkikh)
//  Copyright (c) 2019 Alexander Grund
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef BOOST_NOWIDE_CONFIG_HPP_INCLUDED
#define BOOST_NOWIDE_CONFIG_HPP_INCLUDED

/// @file

#include <boost/config.hpp>
#include <boost/nowide/replacement.hpp>
#include <boost/version.hpp>

//! @cond Doxygen_Suppress

#if defined(BOOST_ALL_DYN_LINK) || defined(BOOST_NOWIDE_DYN_LINK)
#ifdef BOOST_NOWIDE_SOURCE
#define BOOST_NOWIDE_DECL BOOST_SYMBOL_EXPORT
#else
#define BOOST_NOWIDE_DECL BOOST_SYMBOL_IMPORT
#endif // BOOST_NOWIDE_SOURCE
#else
#define BOOST_NOWIDE_DECL
#endif // BOOST_NOWIDE_DYN_LINK

//
// Automatically link to the correct build variant where possible.
//
#if !defined(BOOST_ALL_NO_LIB) && !defined(BOOST_NOWIDE_NO_LIB) && !defined(BOOST_NOWIDE_SOURCE)
//
// Set the name of our library, this will get undef'ed by auto_link.hpp
// once it's done with it:
//
#define BOOST_LIB_NAME boost_nowide
//
// If we're importing code from a dll, then tell auto_link.hpp about it:
//
#if defined(BOOST_ALL_DYN_LINK) || defined(BOOST_NOWIDE_DYN_LINK)
#define BOOST_DYN_LINK
#endif
//
// And include the header that does the work:
//
#include <boost/config/auto_link.hpp>
#endif // auto-linking disabled

//! @endcond

/// @def BOOST_NOWIDE_USE_WCHAR_OVERLOADS
/// @brief Whether to use the wchar_t* overloads in fstream/filebuf
/// Enabled on Windows and Cygwin as the latter may use wchar_t in filesystem::path
#if defined(BOOST_WINDOWS) || defined(__CYGWIN__)
#define BOOST_NOWIDE_USE_WCHAR_OVERLOADS 1
#else
#define BOOST_NOWIDE_USE_WCHAR_OVERLOADS 0
#endif

/// @def BOOST_NOWIDE_USE_FILEBUF_REPLACEMENT
/// @brief Define to 1 to use internal class from filebuf.hpp
///
/// - On Non-Windows platforms: Define to 1 to use the same class from header <filebuf.hpp>
///   that is used on Windows.
/// - On Windows: No effect, always overwritten to 1
///
/// Affects boost::nowide::basic_filebuf,
/// boost::nowide::basic_ofstream, boost::nowide::basic_ifstream, boost::nowide::basic_fstream
#if defined(BOOST_WINDOWS) || BOOST_NOWIDE_USE_WCHAR_OVERLOADS
#ifdef BOOST_NOWIDE_USE_FILEBUF_REPLACEMENT
#undef BOOST_NOWIDE_USE_FILEBUF_REPLACEMENT
#endif
#define BOOST_NOWIDE_USE_FILEBUF_REPLACEMENT 1
#elif !defined(BOOST_NOWIDE_USE_FILEBUF_REPLACEMENT)
#define BOOST_NOWIDE_USE_FILEBUF_REPLACEMENT 0
#endif

//! @cond Doxygen_Suppress

#if BOOST_VERSION < 106500 && defined(BOOST_GCC) && __GNUC__ >= 7
#define BOOST_NOWIDE_FALLTHROUGH __attribute__((fallthrough))
#else
#define BOOST_NOWIDE_FALLTHROUGH BOOST_FALLTHROUGH
#endif

// MSVC 2015 (1900) has reasonable C++11 support (especially auto-generated move ctors)
// libstdc++ < 5 does not support movable streams
#if(__cplusplus >= 201103L || (defined(BOOST_MSVC) && BOOST_MSVC >= 1900)) \
  && (!defined(BOOST_LIBSTDCXX_VERSION) || BOOST_LIBSTDCXX_VERSION >= 50000)
#define BOOST_NOWIDE_CXX11 1
#else
#define BOOST_NOWIDE_CXX11 0
#endif

//! @endcond

namespace boost {
///
/// \brief This namespace includes implementations of the standard library functions and
/// classes such that they accept UTF-8 strings on Windows.
/// On other platforms (i.e. not on Windows) those functions and classes are just aliases
/// of the corresponding ones from the std namespace or behave like them.
///
namespace nowide {}
} // namespace boost

#endif // boost/nowide/config.hpp

/* config.hpp
NlEIpv+NyHPSoF3IGjHL1jzZgrqQhcL0vxG5T9nEZmYJJRvMx1x3mo6NMP06um6yzDD9OrphBukiDNLFkI3i8eXza4HyztjELrO091scN+W9Em0saRa/sVtOpDtnE2+EtKkpTV/IdfJtYgWzRZkKf4f974JN/P6dtF5ZGnRHnn/bRGFWXnSNrQdRl3/Sjz3hH4PxQpZeuyQb5OlKSj+dOyn9dGEG6SLIAmH639ziDCyRLImZs5s5EDHctonnzPbu6iy/WXrXJraZpf3oN9wq3z9Kv7x4Mpe3tNmZ+0SiLk/pXNFLWujcpynYj5JtIpeA6dduN7AEspXMPPmt45EuxSaq8v2vTu8k7O9kx1h8nV+8fYK6vDGoC1knk7RrE1fI9c/e0Xkyn0NCd8SjPd/bxCUtXTj9rZHpa1f07Ucb7uWl5d34o7cZ9onmCWZdaz2fhvYka8ksOal+W+wrqTYxg1nimbXymplsmLe0IV+i5ZroZjuOcR1pw8Ci67dhXHvZxThmY67O7oF+J6ulWQd1DRtvO34X/Q9tWJrL9RFtRjaR2Zb96zPgOO1jF9mYtau/rDLak+yUWVr2o0XWY3/4zk7tIm352ZpFUBdfuyhtkhbufLUKsVvsYhBLVzNwjwvlWe3CCtP/nuPmpvzOFcJN+d0pjJvyG5iHm/I7VwQ35fe4aLJazBpdjQrCmCdzwpTnHG12MZXZpU+hA9G3ZMuYHQu+nory7HbRj1nl3R/kNbrDLgryfuj+wIx2IZvPLDi1uVzz1qnPs2E8/VezGLK8zHzF7YeYC8iKMds04sku5OmyCwezraKhXAOFLAuzETEzR6CeZMOZvTDPks8ykh1lduFkJV+Yn12MYda0+IxQtFkmytMs7f5T112M3ax2EcX7Peefcixls4vfWbpjB9csRR/lsIu2Jmn7XWFmjKVcdlFESEtt3m45yiObwezgBI/8tmpufR9NqHAtAX2bxy48fMyXCCmDPiJ7r1n7tGugVlbs74kBdlGImaNi0Q3oo0Da35k1LW0aiT4i68usW8qsWMSupJszbfxMlEdWgdnv2SfnQ55BdlGYWaZ+VR8hdrL/MEs41XU28iRzMGufu5Jc04KsMre5N03ov7z6dJN3Bu9CH5EFMVtVfYNcv5wsO7NPu/bsRexkFphyLqzYyBkPJiIGbsrv9klk603S2h1/j9hFAbsIZOkebd69FfMgWT9mG7IEy9+ZyWpr1i5t3j1SfCP6oaBdHGFWtUjTpbBCdvHSLM35JTgFMRS1iz+YFbySS17DlrSLUUJaN/vqcegjsuXMjnXYKtfFKUVzK0w/zydyU54FSOKmPAuQzE2Z50VpZupaUGThzE6PYfeFycKY7e494RrydOutq60hyosgQ3nK8SiaLIRZ5MyYD4hdSffml1N2xE7WgVnvlDvVMa6/Z+nU4xg35TmPaLK6zOasNct7QWQWmH7sJpOVNknbNPXybJQXTOcFfAz6WiogT7JmzDqunCbnwbK038L0a3JFkPG2/vzgP0+RJ1ljZsdXBN+X32BmeSprh3nI8rAYnh3dhD5KLMfSKcexZLI4Zh/9XqCeCeXtwh+mfwYriSw3TP/8kqtC+mM+iGwWs7odHmK/TSTjY/dZtC/2v7CKdB7JLLbiy7uIgWwEs0PXekXJd6/omMrsZPmkdZh7KtPxiFnSB7N895GsOm/rF3Fy/6tiFyOZVWt4tDuOjWRRzAIfHiqK/qtqF8OYTVlZUqA9yYYwO99tUyjGSzW76M1syba3k1CX6nbRn1mdrIPrInbFHnm/fIN+CEl/f3CTDWR2rvTUShgTZOeZDazXYgT6r4a+XXIOrPgEMdSkeZfZ0ZdRN2A=
*/