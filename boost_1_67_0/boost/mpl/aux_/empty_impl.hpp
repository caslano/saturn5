
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
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
*/