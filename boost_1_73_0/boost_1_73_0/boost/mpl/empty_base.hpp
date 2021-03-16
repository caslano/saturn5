
#ifndef BOOST_MPL_EMPTY_BASE_HPP_INCLUDED
#define BOOST_MPL_EMPTY_BASE_HPP_INCLUDED

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

#include <boost/mpl/bool.hpp>
#include <boost/mpl/aux_/config/msvc.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

#include <boost/type_traits/integral_constant.hpp>
#include <boost/type_traits/is_empty.hpp>

namespace boost { namespace mpl {

// empty base class, guaranteed to have no members; inheritance from
// 'empty_base' through the 'inherit' metafunction is a no-op - see 
// "mpl/inherit.hpp> header for the details
struct empty_base {};

template< typename T >
struct is_empty_base
    : false_
{
#if BOOST_WORKAROUND(BOOST_MSVC, < 1300)
    using false_::value;
#endif
};

template<>
struct is_empty_base<empty_base>
    : true_
{
#if BOOST_WORKAROUND(BOOST_MSVC, < 1300)
    using true_::value;
#endif
};

}}

namespace boost {

template<> struct is_empty< mpl::empty_base >
    : public ::boost::integral_constant<bool,true>
{
public:
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(1,is_empty,(mpl::empty_base))
};

}

#endif // BOOST_MPL_EMPTY_BASE_HPP_INCLUDED

/* empty_base.hpp
BTJrBXceaeIe6hxq/b0QzPQ//wuV7kRz5OPR83q+l9evmKxFG6oWsz1IMrQZeeGBveSYaMPyxTyG1h/ampHrXZRrbNVxN7qOVzavQ/x1qruBGvN1HFvP4s1q0yWUj23K1zgc0DsUZx1YhYuilRCtwy6wXDNMNL64znpZmoC3Lt39I/99QlJ8QFrlm/fRk/PNAL1FmRYV6dff4xbVv1jZkDKtrMGAaWWRxZgcfTaQ6RlxRGV74STNMY3D0Oq//1g=
*/