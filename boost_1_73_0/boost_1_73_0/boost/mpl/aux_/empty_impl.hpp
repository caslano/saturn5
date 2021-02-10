
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
p/6slITx4PjIjYul/UTZ0lhVH8lVIbUYyy59IMXjt5CORGWl6+YTrWdvwZTk2bWuEnoo2SeyhiMpshjwhvjH2K0ZS0hreAuZLBQylhnklRmD0OBlraQ1kypFuTjpRHrOdfOCfigUkasFTf0CXXIp3ARP9hgRXWUr4audpFaox0bOlbizWEJCd1qlGAqTigJ+vbzwt97bpLUHE6v0EEIDOZ2D8BzCE++JSLyGSlIzHgudLUQJtAnNxJUTt4e/lE6LSSYx6WE4XgQlgJjz7etfTnhhhpxySjo3lh4UyADtIRS50zbFJhMJbcmAF5sH76Fa9VU2gsC0Ug4zAAOZm0r64oEF32qiLapJbj7bwbNUkHny7mFcAOpn/f2ixn4AUqcmQ226AfILj4J36LYMvXQ9IFc8rG03oEzgpafT6RJbVg1TDXlAeSEemDiAx4wyM9WFERmxIk/0QHyVq1SQ3t4CyUjYETis7m4wzg6D3lSGRhez0Pdd6EYyxGI1WKzYPeQblpW5x7rKEk7Lpyh2JJqH7aAnW+nh4Ojg4Kg1EJ3sMD/CVERZO+q0OiJq5c3jgRBp1slykaVyPx9kh+12O8oGrQH6NwfNNfyEPyGeLErNwlg8pMu+Rb2iYE5qUhVzTiRhAGUlc2wlnaLleD/o
*/