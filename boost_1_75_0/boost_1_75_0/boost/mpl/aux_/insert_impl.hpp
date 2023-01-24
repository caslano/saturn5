
#ifndef BOOST_MPL_INSERT_IMPL_HPP_INCLUDED
#define BOOST_MPL_INSERT_IMPL_HPP_INCLUDED

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

#include <boost/mpl/reverse_fold.hpp>
#include <boost/mpl/iterator_range.hpp>
#include <boost/mpl/clear.hpp>
#include <boost/mpl/push_front.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/traits_lambda_spec.hpp>
#include <boost/type_traits/is_same.hpp>

namespace boost { namespace mpl {

// default implementation; conrete sequences might override it by 
// specializing either the 'insert_impl' or the primary 'insert' template

template< typename Tag >
struct insert_impl
{
    template<
          typename Sequence
        , typename Pos
        , typename T
        >
    struct apply
    {
        typedef iterator_range<
              typename begin<Sequence>::type
            , Pos
            > first_half_;

        typedef iterator_range<
              Pos
            , typename end<Sequence>::type
            > second_half_;

        typedef typename reverse_fold<
              second_half_
            , typename clear<Sequence>::type
            , push_front<_,_>
            >::type half_sequence_;

        typedef typename reverse_fold<
              first_half_
            , typename push_front<half_sequence_,T>::type
            , push_front<_,_>
            >::type type;
    };
};

BOOST_MPL_ALGORITM_TRAITS_LAMBDA_SPEC(3,insert_impl)

}}

#endif // BOOST_MPL_INSERT_IMPL_HPP_INCLUDED

/* insert_impl.hpp
BcZakgNodatENsVEoEDUP/m6q7YoGAQMw/qhoILykVIDAhLS3TAsqXR3SM7QIB1DCNIp3d0x0jkMSEsM3TB0dw1Dze6e7B7sde1feE/es+eu1OStkxt3Cuq0mA8aTPmqOm8A2v4WmKPQXxruRTg12UpdsBfAmfl2ETd8u+fvyVl+lZUvqoqS1I4iX9jA4aq/JUuDZPB29r442aFG8Xj0e2nkCP9hOyvIbjdQNoP1JdDCX8SItidYXESgxHCaPRdbhDvn2balwJ8l84ycXgXuhKEKEtEVu5gycr8g+YGuGFrb7Otub1ScgBzG1djXV1R/U+fv76YSb78OsPY4blVbhGH0VK89Hr3QFia/byvg2OKxNE+fNob+7ktVT/r8rGsF9z0D2fiLU5YXzNV6LzQaxhUNasl5E3BqtuPOa5N61UNf9WC9tvxsUIutewOqFCcYBCvQdYf7WmnGI4qLOtW0P3rkwZa1k9rhomDal2UMBK8BXpNKESFxzAZ0kg0yG/iyEb3/kJsiRP1pCglp7ZVKeNGgKNPriL+186Fo5fELrkG5Dp0DviX+x29nP1MmNUwpKDdODw/lJnr3JC3bkyaDwneiurmYBP/0k9ZeFxkABTMK1RsrXmhIcRM4hxk0uptbGQhKjVXni2B1h66VyBilu0eRHhWLdw0RcrXyvH1lTj77TBb/o4zY2Q94fbBkRSJpK36/P9GwF7FQcaWv
*/