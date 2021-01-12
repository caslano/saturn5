
#ifndef BOOST_MPL_AUX_EMPTY_IMPL_HPP_INCLUDED
#define BOOST_MPL_AUX_EMPTY_IMPL_HPP_INCLUDED

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
#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/aux_/traits_lambda_spec.hpp>
#include <boost/type_traits/is_same.hpp>

namespace boost { namespace mpl {

// default implementation; conrete sequences might override it by 
// specializing either the 'empty_impl' or the primary 'empty' template

template< typename Tag >
struct empty_impl
{
    template< typename Sequence > struct apply
        : is_same<
              typename begin<Sequence>::type
            , typename end<Sequence>::type
            >
    {
    };
};

BOOST_MPL_ALGORITM_TRAITS_LAMBDA_SPEC(1,empty_impl)

}}

#endif // BOOST_MPL_AUX_EMPTY_IMPL_HPP_INCLUDED

/* empty_impl.hpp
eHVZv2jZP9vKcun7yKC8E13eF47ujDcgRtsGHH+U4qDWmCPCqXUyX9s1zitvE/YNtBDCo8PU/cJDKfuocK7D5fwdoy+3K4Z499H6+GhD/FdDvMIYfbyjIR6lxmW/lPI5KOXjJvtkBft+McZYPjyKZiijzDyXlkEZ6d7n71vENnKUXH+FoLL8FIflRwVHW7h/Df8r+8lPhvLwGCtxwzdv0iU/neR43pxQj23nE2vNT3frS/87
*/