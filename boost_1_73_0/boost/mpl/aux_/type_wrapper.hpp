
#ifndef BOOST_MPL_AUX_TYPE_WRAPPER_HPP_INCLUDED
#define BOOST_MPL_AUX_TYPE_WRAPPER_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
// Copyright Peter Dimov 2000-2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/config/ctps.hpp>

namespace boost { namespace mpl { namespace aux {

template< typename T > struct type_wrapper
{
    typedef T type;
};

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
// agurt 08/may/03: a complicated way to extract the wrapped type; need it 
// mostly for the sake of GCC (3.2.x), which ICEs if you try to extract the 
// nested 'type' from 'type_wrapper<T>' when the latter was the result of a
// 'typeof' expression
template< typename T > struct wrapped_type;

template< typename T > struct wrapped_type< type_wrapper<T> >
{
    typedef T type;
};
#else
template< typename W > struct wrapped_type
{
    typedef typename W::type type;
};
#endif

}}}

#endif // BOOST_MPL_AUX_TYPE_WRAPPER_HPP_INCLUDED

/* type_wrapper.hpp
zxP6BwygmdNH0/wPnk9y2i4VhKifOH3oJSl/9Nr/d67z4/JzbvXsBK0Tqgd3RH0eX8W2KbqSiHZ7Aeql7ONz21cJ11cJ8Q0hnrP9uffccvvZQrs1v3t5oZ8tnHPlT97tLki/UM45Mvoy5Ne3Hj8ubRiD/zOhelD73okglkd5T3UFzqcNW+PzZU1CfMXW32/jxrc7932PaU9iW9SGrLJdjXx+TFhP7liQue3e5H3nT9y4hycd
*/