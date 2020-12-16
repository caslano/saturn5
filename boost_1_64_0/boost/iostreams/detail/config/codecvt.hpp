// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_DETAIL_CONFIG_CODECVT_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_CONFIG_CODECVT_HPP_INCLUDED

#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>
#include <boost/iostreams/detail/config/wide_streams.hpp>
#include <cstddef>

#if defined(_MSC_VER)
# pragma once
#endif       

//------------------Support for codecvt with user-defined state types---------//

#if defined(__MSL_CPP__) || defined(__LIBCOMO__) || \
    BOOST_WORKAROUND(_STLPORT_VERSION, <= 0x450) || \
    defined(_LIBCPP_VERSION) \
    /**/
# define BOOST_IOSTREAMS_NO_PRIMARY_CODECVT_DEFINITION
#endif

#if defined(__GLIBCPP__) || defined(__GLIBCXX__) || \
    BOOST_WORKAROUND(_STLPORT_VERSION, > 0x450) \
    /**/
# define BOOST_IOSTREAMS_EMPTY_PRIMARY_CODECVT_DEFINITION
#endif

//------------------Check for codecvt ctor taking a reference count-----------//

#if BOOST_WORKAROUND(__MWERKS__, BOOST_TESTED_AT(0x3205)) || \
    BOOST_WORKAROUND(_STLPORT_VERSION, < 0x461) \
    /**/
# define BOOST_IOSTREAMS_NO_CODECVT_CTOR_FROM_SIZE_T
#endif

//------------------Normalize codecvt::length---------------------------------//

#if !defined(__MSL_CPP__) && !defined(__LIBCOMO__) && !defined(__clang__) && \
    (!defined(BOOST_RWSTD_VER) || BOOST_RWSTD_VER < 0x04010300) && \
    (!defined(__MACH__) || !defined(__INTEL_COMPILER))
    /**/
# define BOOST_IOSTREAMS_CODECVT_CV_QUALIFIER const
#else
# define BOOST_IOSTREAMS_CODECVT_CV_QUALIFIER
#endif

//------------------Check for codecvt::max_length-----------------------------//

#if BOOST_WORKAROUND(_STLPORT_VERSION, < 0x461)
# define BOOST_IOSTREAMS_NO_CODECVT_MAX_LENGTH
#endif
                    
//------------------Put mbstate_t and codecvt in std--------------------------//

#ifndef BOOST_IOSTREAMS_NO_LOCALE
# include <locale>
#endif

// From Robert Ramey's version of utf8_codecvt_facet.
namespace std { 

#if defined(__LIBCOMO__)
    using ::mbstate_t;
#elif defined(BOOST_DINKUMWARE_STDLIB) && !defined(__BORLANDC__)
    using ::mbstate_t;
#elif defined(__SGI_STL_PORT)
#elif defined(BOOST_NO_STDC_NAMESPACE)
    using ::codecvt;
    using ::mbstate_t;
#endif

} // End namespace std.

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_CONFIG_CODECVT_HPP_INCLUDED

/* codecvt.hpp
Meswz/XcT94pmrJ0s9wvw7zL+VTu1S+pvt+VfCzPPShU27sSZCRfkWHPmtGUK+b4BqKnQyNlPCM0I71peq/07qzma5neM723cHBqWlISXe5+yTpnYq3b7XNK+l5Q0mmC04h+7sn6ri7b5GFKrf2asMgMJAXbxPmLe5elOhC538/kfmfTMln6G6b96h7JQ2mZ5ZoJ//rQ4U5+7X0LkUs2desiSd8HQ/c5I/xxNX25zqIPgxy3bU8eQp0z1NO/+Cn9i7ZJ4dQOSY3pVTRlXJtw/dk0CXecjuei91kdaoqExjthH2OBK6vjGzN/jh7MIC6zdHy1/MbURkkjUtMy2jdKTcpI6uYpn0a3+8nzXq71Vsh5ROw3MdI5vWZumnC3Da3pczxL96WXdF/Ms+GncAkw9eHpbjg8mTdu+zxhbEvvImEkpWUkpTj2cJrDARJOW53PVl0/JhpORqPl67TPo25TcDPPvyy1UUajNCfmuVVnMiXca9Uefe6smPuUeu8zz4lxW1fjlrq8KOI2jrJF3pi5HN4zSjn7RUvKpnnnWPO+8Cx9t3i+791iO+1TDQr4LtFdl4NO6pzPgjKnDn2umH3pTLsW/F2ilNXk+n13WL3dvDuMOWMs7QRHfmu0b7cKcxT3ynrQ9B30m9GAfbsH69C3Q9beB7C+E0Te2r5b221k/e22rS1G7qv3GU8Sv99xTq2lz1gkMulmz8h5ps9YM4+RHGBOfX7WodM5a//Se1bfiY78ilRHZmEGdWRMb3TE881hHcYBVXXQlaisW3dmnMD9TyRN2hCfdHew1yF9PJ/0MGZrbembf6W8ff/Bg48Hsh+S8YDUU/WVj950P3CSPd2HPWTSPfZ7woDpPuyh4OmOrEn3laT5vScd2nQveujg6X7VIUr36Hj3+OGRAPrr/nH9MM3cObpIupcxd85a/ZnE2/49Uiv4M5HtRbqF7Lqv6WraaO3HRMcAL4p7F2atwtZ8wb+p395rKeuIrXWmkTPfnujcaYCxqv+sSjN3qnGNfu/N/blWFpOGw0bUpGFY07A5aeg87E3DwiULygqta/1aw1SR7WFLPw0nlHCuuZ24H2Z0ppnYM6xzzb3FLcX0Y9LEfvhXSidvGuSNjgh/oG3NnzFHkAbDImmwpIztmeVjg/j5XhPvu0X2Uns51jTwfatg/E4W9+k2/cFv8HkVlbV+X+BbA27y7lHxM9s51N8fuH3HUejazpHEQL6hesbtATeL6vsCXacWlfvcyD2AXDjTL9dW5XqNispdg1xKRgYrEhOFmWdkL3fv3TRRmBepXEby7KRs9+4krl9W61HP9xT67USAOs7WLzXfTtjnlr6RbySi5WHzGD2HT+vVDpjBvcnVRzzlQSvWROVhMbL2d+4ajuo08eCvmfbzf32y5TXn/xr9/a64N7eVB+PX5F0d6lRbHkXSjLj680jj5H2/+9TJkUD76J6pvV3Df5WeNDQVay3peI/Id7SfwWrSxj5+3Cbunazpqn7jxodu5KtcN896su1iz4rfD7wOaSftkcTP973d+EgAH2LkHQ2mH+m025tOZbXXvZ0edWXvsqWRhhPyf8djxuofifubtjTCb/C6Nyrr/xbm85h6tES/mbF/H1Ntq6d17vczCf9V23c6piw0kXT4sWP7xuaA5RubfZY6fm/MtSJd32H/7ma/1utV6Pq9p0Tr1jfcGjO+Xle5nUbuBalZE8l9buQer1Wu27io3J3IpSSUm2Dkbqw1vHIjt65WuZuicpPltk4iueeicschl5QdJ6dzkvKt0lSuTcHot0pS3joHeHduK2/6TVJt7Yn3myDft0gl+q4p/tujA5Zvj/b52qG9xl4q9t3GXqTrv3w=
*/