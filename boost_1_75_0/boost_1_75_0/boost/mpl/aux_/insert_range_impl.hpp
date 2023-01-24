
#ifndef BOOST_MPL_AUX_INSERT_RANGE_IMPL_HPP_INCLUDED
#define BOOST_MPL_AUX_INSERT_RANGE_IMPL_HPP_INCLUDED

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

#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/insert.hpp>
#include <boost/mpl/clear.hpp>
#include <boost/mpl/joint_view.hpp>
#include <boost/mpl/iterator_range.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/iter_push_front.hpp>
#include <boost/mpl/aux_/traits_lambda_spec.hpp>
#include <boost/mpl/aux_/config/forwarding.hpp>

#include <boost/type_traits/same_traits.hpp>

namespace boost { namespace mpl {

// default implementation; conrete sequences might override it by 
// specializing either the 'insert_range_impl' or the primary 
// 'insert_range' template


template< typename Tag >
struct insert_range_impl
{
    template<
          typename Sequence
        , typename Pos
        , typename Range
        >
    struct apply
#if !defined(BOOST_MPL_CFG_NO_NESTED_FORWARDING)
        : reverse_fold<
              joint_view<
                  iterator_range<typename begin<Sequence>::type,Pos>
                , joint_view<
                      Range
                    , iterator_range<Pos,typename end<Sequence>::type>
                    >
                >
            , typename clear<Sequence>::type
            , insert<_1, begin<_1>, _2>
            >
    {
#else
    {
        typedef typename reverse_fold<
                joint_view<
                    iterator_range<typename begin<Sequence>::type,Pos>
                  , joint_view<
                        Range
                      , iterator_range<Pos,typename end<Sequence>::type>
                      >
                  >
              , typename clear<Sequence>::type
              , insert<_1, begin<_1>, _2>
              >::type type;
#endif
    };
};

BOOST_MPL_ALGORITM_TRAITS_LAMBDA_SPEC(3,insert_range_impl)

}}

#endif // BOOST_MPL_AUX_INSERT_RANGE_IMPL_HPP_INCLUDED

/* insert_range_impl.hpp
laD8XlZDXaqvFQd1kAJJkAEZE6p7zT4Ca2Nz8UnKPOhF5lxCOJ6HTENDHfGbp9g1dM5kZPpkp/nkZWTEZGScrLldUDFEyTcQC3md/exK20+p37/k1YCUlTADgTljdDJZIG4D5dfKPqLEiUIGKRy1Vkk6OpZujoJSDeZC2VjHjy9k/HAUKrp3bsxnJtK4ngW2v8R0fCmOwpJWT6I8F4r/9ZKJy5OsV6s48MJTJpxYLLyLS0ANuv414R9TTMusY8/8qQ1gH6WEBldYmQjhSu5dZsMmDM4OzD/XOb67i4VYpHK+ccaL17GP7yIL//ypiyBU9YV1cJCP/e9XyxuvmP5O7m/RFVFg/SRmMh7asMHxgp7slNkaTEF5SvpZONzmQ4vhYFV5kR9ARm0UCdsgSdszOccWWVdBY2H5sFd7PZ99RqCnp9rHakT+MUx4iHlSPAAsO5jiHOdiHP5BJ0xPqf4lyozLTIZfOfCbCuLVxOw6pP1e1iib2QDJ4ZR0T+7CSlDPuDnbv21Ho6W12bx1S/JqVO52t+QsU/SVldUA6xmlxC1+C5XKw8Rm1+JlXGpIDHrS/Zgytd1zFa8DCHnI7aC9mzDeGX2zPH93U7qLeOhATZYyFYpRTPJmKTmYaPuJHXQ15jtO4QvjjYJd5D+lu6s6Y3ayQ31TxNsuZaaaoy7lfXVHE3d3wvzK376+3bQ3VKzhvkplor+vdhXnKnXg
*/