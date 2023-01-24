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
fznR3jliAXGRZV3F2pqnG9wdWE6Ckoslvsbe88NWQc1P0g9+vcQJnGoUx3SBEU8rqaMbJIPGTKEbBMl8daUzohnOxycLypDAnGhENQGGOt+O63dHhcQ61VaQVsbUZz7lI0pB2HLfMW3rgPGgxKnyklWBbOCsJFzaGycuzm8+hpyqMzgb3vlZK5bjZqP2lnDVpq2xEgEEzM59JeczKcoiHWmtAfpT2j/5c1a+ttIiEujxJVb6j5nWBVnrzC+PYUVe+X36IfSeYKTvOz8tjEOHYwwLOZHJA4YOO6PnJxm9qlDIaRujXsFC4Lhla0X7AYHrOSNDHolTM3JdYptjIl1qVvq+1GVBsJ0vnD9djudkWN9/NmYrW+RAXlSEGOAdxY2mZHGSqk4torEiHbgPGKSBa9LMSkWpR7gqvQ0ZMOXK6VrD3/xP/T9h7wlE8b7jRZnf7Kq7HruM7oJEv3mFmd0KVk2YE2VV4fuhwlt0X0raufoNsfe1CovJ5ajBL+5dN7T84UYiXVy7tGLXtGW6hbzpovNxtWcew59bvpIRlJUaBkISBzkHsNPe6jCVjD1g78UsL6abZ3Di5AutxJIyJwOkfCRk8DXnEKEjZ1rCaXJCH43ay0QxMCelenuxxJfS6MVfo2uvzAfPabpT46pUTs0XYqJyrCd/cB8r3pNmdLWecASHmMVVjNjy/6bRxG0tiwYujp/bCrYeru5M6UU0
*/