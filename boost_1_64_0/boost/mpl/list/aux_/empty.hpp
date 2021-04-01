
#ifndef BOOST_MPL_LIST_AUX_EMPTY_HPP_INCLUDED
#define BOOST_MPL_LIST_AUX_EMPTY_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/empty_fwd.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/list/aux_/tag.hpp>

namespace boost { namespace mpl {

template<>
struct empty_impl< aux::list_tag >
{
    template< typename List > struct apply
        : not_<typename List::size>
    {
    };
};

}}

#endif // BOOST_MPL_LIST_AUX_EMPTY_HPP_INCLUDED

/* empty.hpp
Sk5TVai3On+JsNpJxmvNsHeIkqyLctWrRcFJmtHC1Sikpn9sjXETPIcLP/hZQfvIdBzTaYc4o1mcaZJNwF0PsUdhE9dNIGOPLuCgfP1Q3zJrMAOKRFPaIWFZglmjuBPnxx3lYNmGp2Jya91JJbvY4ijlDwNJSomeop8e534Z5BKMRPwo95qDt3ouafyWkkcwgJhegHIwqRF9FUSkbkbn2pmQo8JfQtb0rVjnp2G7b98vfDks83Ny6gDoNN0kIS8J9ZFf/vjPpyZQhgkg92ODxQWZGx7M2zty47v44zgB1AeNxdshDVbyRj+kIuvPulavSCAmp5mEG72apmwptEebQ5+TiSYEJGPK1zk7pj1rsApaMr1aCqaORySd3fTDL/iMrO2BL0shFWpUFoT8cmYZF0E5tVP0rA4OZ8r9dQu3La6EC+Zqo/Z6DeRdOa/KysMP5shIM8NBiRAbowXRhPsJtuHJp6xcQXlSA3RGPgo9k026FaQEE21X3LmwcJQaN95Fb4U7L1rhaBoLu6vZ1/1n7NdkW1fz6+hqwTgX6LZwSuNNJKXk7gaqJKCAKQ==
*/