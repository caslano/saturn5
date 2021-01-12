
#ifndef BOOST_MPL_GET_TAG_HPP_INCLUDED
#define BOOST_MPL_GET_TAG_HPP_INCLUDED

// Copyright Sergey Krivonos 2017
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$


#define BOOST_MPL_GET_TAG_DEF(TAG) \
    namespace boost { namespace mpl { \
        template<typename T> \
        struct get_##TAG { \
            typedef typename T::TAG type; \
        }; \
    }}

#endif

/* get_tag.hpp
HIkbMBZfx1m4CV/AzfgKbsGV+Ba+ju/gbtyGX+C7eAC34zH8F+bg+3gZd+Jv+BF2k3cQonEvTsNPcQ1+hu/jF7gb9+NneACP4CHMwcN4E4+gF/sqC/3wK2yC2RiCx7EDnsJeeBoH4Rkcgjk4Cs+iAb/BZDyHz+F5nI/f4QbMxfcxDz/BH/EM/oQXMB9/wsuotK36C/rjVayOv2JdvI5N8Ca2x1s4GP+Nw/E2xuAdTMDCyvmA
*/