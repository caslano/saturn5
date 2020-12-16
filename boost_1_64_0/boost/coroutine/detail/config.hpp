
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COROUTINES_DETAIL_CONFIG_H
#define BOOST_COROUTINES_DETAIL_CONFIG_H

#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>

#ifdef BOOST_COROUTINES_DECL
# undef BOOST_COROUTINES_DECL
#endif

#if (defined(BOOST_ALL_DYN_LINK) || defined(BOOST_COROUTINES_DYN_LINK) ) && ! defined(BOOST_COROUTINES_STATIC_LINK)
# if defined(BOOST_COROUTINES_SOURCE)
#  define BOOST_COROUTINES_DECL BOOST_SYMBOL_EXPORT
#  define BOOST_COROUTINES_BUILD_DLL
# else
#  define BOOST_COROUTINES_DECL BOOST_SYMBOL_IMPORT
# endif
#endif

#if ! defined(BOOST_COROUTINES_DECL)
# define BOOST_COROUTINES_DECL
#endif

#if ! defined(BOOST_COROUTINES_SOURCE) && ! defined(BOOST_ALL_NO_LIB) && ! defined(BOOST_COROUTINES_NO_LIB)
# define BOOST_LIB_NAME boost_coroutine
# if defined(BOOST_ALL_DYN_LINK) || defined(BOOST_COROUTINES_DYN_LINK)
#  define BOOST_DYN_LINK
# endif
# include <boost/config/auto_link.hpp>
#endif

#define BOOST_COROUTINES_UNIDIRECT
#define BOOST_COROUTINES_SYMMETRIC

#endif // BOOST_COROUTINES_DETAIL_CONFIG_H

/* config.hpp
t5r2zqydkKY/kjMihYPPMemDbYnxGfGJcqP+IUAemOT/Dvpw/oCaxN5ySgaPpQZqxEVGBP5goY3pBpo3P9eWatAZWXK0v/fg38xFv6IfvR6WNiLZYDrciEvgaHUKr5/Q5wED4uL9HOZh3PgUvcG4+IzwMGOM+gDgUnoyHPdfSYwOF/J8K3A2bEJYj7CIIDUhXif1DjNao0a4vz3Gn0ptfUVHJMUl+Bd5CHxIJCUaWFpbTHpCYtzwgbFDEpLibbbojNi0ESMSU+PCu6ekDfe3EReXoK9UKvdGB/6LHnr513tIQmBFh8fxhf/gX6kJw9MT9UWxpHEAaJB0YdSIlGEDU0akszji5Cl5vsZy+Kv5uxuWkGxLGFSx+ST/uuuXk+JH2VLjhvmnNWIQDzzzwfvA7PwMiIlPG+j/Y9BofTr+Dw+jDv4KepI4Oi4O3YoMj4ihTrpf0eKTMmyD+OIf/BoTneLwkt0N3I9gJrETnDomSX/pCfJKexkDE9Pj9Q4GF6G88UM8+v+h58PjIKWi7/Y+4/WXqNm8/r9zi92pdoIieY0Hp3Th/3JadhmfExXWvbv/N7x7hP83Iiw88Bse5f/tGRG43rtHmPEbuN4jLDLwG9HT/9srspf/N6p7D+O3p/FbTu8d6K839w9KyMnJznK5HDld8/mv2ECNHpGMuJBSwi2DB1EmMq1k3Xx583kekVxPrr6nzmPVHu4Ij4ro0T3wGxUR+O0eFfjt1dOfb67SuJZ+BjiMeJFSQCmkFFFclGJKCaWU4qZ4KEnwyMtvoJnePfy/kWiA/7dXL/9v96je/t8e4YHf3mHdjV/q5/lImzMM3UiONvaOHLSYS8mj5FN8YfL+W9/++l7F4NQhAXAfa+zvm7m/aIvrAf8mzDr99Tr6k7E+/9vjjaMrfGzU6QiJX3PL4ypiwZXteMderSBNjmlzLeLXXIs4MtciJsutHGsZtB4XHvPkeYwJGPsAEh9vk/gYGkvmhcarJm2AQdsp1ZN5k2fBmzwL3uRZ8CYvNI43aQn0u4v2MkSQNsygFUk0ma95FvF5nkV8nhcSd0tjNmiN6wVp8jrlWcTOeRZrl3fRa+d26GeKQtdunrx2pvyO8csvh+49DlOKczGDPiPfacq40a4tz2Nc1vf8jOvXmNeNlzj71UCqZ+4PmPUqdybvPWf3P3e9eOl92znUI6nnhWyjktvhCmTQ9eeB2lnUYVuvzFns85RXMs/TU6daezhTBQ4ZazDFoLE0Jm2GQQuXaHMM2mNKkLbIoLVUg7QVBu126d5nDNoB/d4LzIfo62x8EtuTmVvo9Xkw5YTbzEXKGfxDSYGLSzX8h+UM/h3x8j8h8v17w11RHiNeeExrEZJmunJKrMO1JIKEYEh3EUFfSBdlngsOCOXrOovOfc1jN3vGpp011966cuH5WnIYU/rPCP4vtJ4Zwev6f8nfmy/4B8J/i3W+CClJ+CekBiplBEQwhvxnJwf+DvX+Qx3mqdfz5R/+OI0gz/fcGYX/nTSCNN8/zij8D2QRJLt2AQmF/7k0gpwTskwp/M8lEqQcyblSClRLCeQR0pL/F3IJ+rNi5Axq689DGTmDlZRVlNWUxylPUJ6krKE8RXmaslavC6+e4fdc6Yh/PJ8Q43QxncC3mOV4aoURT/2ZEhrPOi3iWae5jx6ol907SHu2P3MhFvhcMWly3GvSnqfeg9R7XARpf4G2A9rNEk2Oj52h8bFJ22nQdktj2WbQLu8TpMkxktMiRnJaxEhOixjJaREjOS1iJGdojGTSXoVWtYP+7tMgbYcx5rulMb9Ove7Uayy1t9uoN1aq94bB01ukPt7pb+YDTNoWg1ZHom01aPUk2k9Xc+Y=
*/