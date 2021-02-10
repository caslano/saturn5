
#ifndef BOOST_MPL_AUX_MSVC_TYPE_HPP_INCLUDED
#define BOOST_MPL_AUX_MSVC_TYPE_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/config/eti.hpp>
#include <boost/mpl/aux_/is_msvc_eti_arg.hpp>

namespace boost { namespace mpl { namespace aux {

#if defined(BOOST_MPL_CFG_MSVC_70_ETI_BUG)

template< bool > struct msvc_type_impl
{
    template< typename T > struct result_
    {
        typedef typename T::type type;
    };
};

template<> struct msvc_type_impl<true>
{
    template< typename T > struct result_
    {
        typedef result_ type;
    };
};

template< typename T > struct msvc_type
    : msvc_type_impl< is_msvc_eti_arg<T>::value >
        ::template result_<T>
{
};

#else // BOOST_MPL_CFG_MSVC_70_ETI_BUG

template< typename T > struct msvc_type 
{
    typedef typename T::type type;
};

template<> struct msvc_type<int>
{
    typedef int type;
};

#endif

}}}

#endif // BOOST_MPL_AUX_MSVC_TYPE_HPP_INCLUDED

/* msvc_type.hpp
3nev9mykou3bm3gh9Ujr14vdlFz7N/eLeIyPRpg8JgRt236vl3Xcbb/X6LrnF33bqTgN4htcA00IMS+kvFTALNwsvJ5bIQuXPDufgGKzuKOnlyCiYEp0uhAaqOzLxwyaft0aACSkKEOuipZ3k83NjHHFmY4w8iPZyirYbpJ5leC+iUbb5J4TBWuHMUjx0Sf7k07k9eWXk2ixDWCUhHbY1LQe4Uaw6u2kRMYi6hQXprPp5ksObh1Bq+VQB7YaVTpoOQ2n3qhVW8EWazTrQbM+KK5ww3mWG2Zb8g8vb/2jy9s/vxw3zPXnkLmnnRXm3P9I/anyL0HdvUvd/YZ61XWcmgOIsNl0nHq15bQG0MKbTdZ0KxRWUa+9FHX3t5vByJ/88eXsdoW5+vcIsi7ZeZl59qL27PxD6T9QSwMECgAAAAgALWdKUrkU9zP3BAAAcxgAAB8ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QyMDI3VVQFAAG2SCRg5Vnbbts4EH0XkH+Yuii2LeLo7tvKAYImbQOkbVB7N48FRY0sbWTRpeik3q/foehrbut0myLpAoFtWjOcOXPOkDQTKawUZxXuW1FepoLeznF2KWRS7Vvvh8PT+gXeHQ3Nh8N8RA7ApiqzIntlGtnG
*/