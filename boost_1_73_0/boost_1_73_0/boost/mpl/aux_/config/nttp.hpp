
#ifndef BOOST_MPL_AUX_CONFIG_NTTP_HPP_INCLUDED
#define BOOST_MPL_AUX_CONFIG_NTTP_HPP_INCLUDED

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

#include <boost/mpl/aux_/config/msvc.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

// MSVC 6.5 ICE-s on the code as simple as this (see "aux_/nttp_decl.hpp"
// for a workaround):
//
//    namespace std {
//    template< typename Char > struct string;
//    }
//
//    void foo(std::string<char>);
//
//    namespace boost { namespace mpl {
//    template< int > struct arg;
//    }}

#if    !defined(BOOST_MPL_CFG_NTTP_BUG) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE) \
    && BOOST_WORKAROUND(BOOST_MSVC, < 1300)

#   define BOOST_MPL_CFG_NTTP_BUG

#endif

#endif // BOOST_MPL_AUX_CONFIG_NTTP_HPP_INCLUDED

/* nttp.hpp
RuQaAc3FrkBAzb9pK9Gb7B2whErFdT9Vwuz1/GuTnIw/8XytkxCcoGW0jEWSKsBPLjQgu5oOFHSNwliNIqjXwUiVRYF5x6AFLCtbXcocr1tMq/ZWtR6w5loBRcczAY8pZ2nOMYZCJDPNYSXFpvZmWYoEm0oQ27afVcOxbZh8/CPl/04k9yjSeH4u0MVeoYZpwxqpsMf/r4n+hTLtS4O3/cBje97UDbffA0334SJomnhgJFoXaH64RitOsd85bpKL+Xw6NpjcFVqgxekFRDnd8KYBYItKw+z9TTcgAaDeKPfz3XTsCfSyGjeImNhsaB43wUPLuhxN5ovxNLysEKeT2cJy7ICAWUJV6xK5hdWhGiYwzbhGR0ZHGDzu08J077lMVzuo1AC60jiolVKVPyRU4UTjFLdVInTbiJ5qWwQopNCCiWxg4IKFJvyh3lh5oXQIP7FsGV+QmjlcY+gQWCkz6/L+bjYfTz63jCFjvMDHV9ZVVbUXwf56oVQ6VAo2E1DdsNl/cyZKmfbbdfzaRxUiV2hzHTPfd3x/Rajju91lz+25hARdbxk4JPZ81wuWvcChPRK4ZLl0bO4x7voBXzm+HTjx2bTth+0lqkTWSfjIOlbDOv0X/gBQSwMECgAAAAgALWdKUn9zfB7SAgAA
*/