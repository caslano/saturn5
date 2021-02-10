// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

// Borrowed from <boost/archive/add_facet.hpp>

#ifndef BOOST_IOSTREAMS_DETAIL_ADD_FACET_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_ADD_FACET_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif

#include <boost/config.hpp>  // BOOST_DINKUMWARE_STDLIB.
#include <boost/detail/workaround.hpp>

//------------------Definition of add_facet-----------------------------------//

// Does STLport uses old Dinkumware locale?
#if (defined(__SGI_STL_PORT) || defined(_STLPORT_VERSION)) && \
    defined(_STLP_NO_OWN_IOSTREAMS) \
    /**/
#  if (defined(_YVALS) && !defined(__IBMCPP__)) || defined(_CPPLIB_VER)
#    define BOOST_IOSTREMS_STLPORT_WITH_OLD_DINKUMWARE
#  endif
#endif

namespace boost { namespace iostreams { namespace detail {

template<class Facet>
inline std::locale add_facet(const std::locale &l, Facet * f)
{
    return
        #if BOOST_WORKAROUND(BOOST_DINKUMWARE_STDLIB, == 1) || \
            defined(BOOST_IOSTREMS_STLPORT_WITH_OLD_DINKUMWARE) \
            /**/
            std::locale(std::_Addfac(l, f));
        #else
            // standard compatible
            std::locale(l, f);
        #endif
}

} } } // End namespaces detail, iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_ADD_FACET_HPP_INCLUDED

/* add_facet.hpp
2HXj30p5NEfQRMTMyvE6AQgcYwXwckR5eYHWaeHXVb6FcThZhXCm4fEUgQMfOFpZXM8LEOqY5BRYxknHUIVk7FDS5YeAE0CZIUwBmQhDqJkX2Fcb3fQI53LCaLz4Mxs8VlFYx6klU7PI1PU5Jx5BExEzaxOuOgACx1gBPBHR9vchAtstVRY1o/HieVjlWEVhHaeWTM2SU8/rCRROa76uQrn+kcZTBA58hOufdLieFyDUMckpsPMC+fpHOUjGDp0dgOsfMgwoh2CKybDzBDyeIiCChs4WwuF6XoBQxySgEOkKlfK1d9WyJebRgjK3wNwtQBXry2S1fr3AxFa3TWz5938uzW6G8hD25/f0FWkJNL1NFM+aTsUsmX0GfdlFiJ2E2hMWDjwdXB6gCWDTA11m6ifkZEEtzTVSOVvg+loSlbwrVTDpUqG9QSiFyKRHfDzE+LC6QwoJrzIlCpzdxg03VVUZat5DuVUFakpNMJ67pL0G9eCVXm4GpDViKUTHHaiSR+QwYZFbAg29N0wslLTw+YEnglETdp2tt6CzhfWod2Hk5xylkam6Uw2XPiWc9z8UKrNecTKR48TsFDE03Oq0aPB2nhIAc2W1wUX6qbKuUF2FKQX6IG03sSbhLd3RLIhv90qgOcy+SpZTd0mv
*/