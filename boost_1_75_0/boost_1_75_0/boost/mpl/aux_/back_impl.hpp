
#ifndef BOOST_MPL_AUX_BACK_IMPL_HPP_INCLUDED
#define BOOST_MPL_AUX_BACK_IMPL_HPP_INCLUDED

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

#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/next_prior.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/aux_/traits_lambda_spec.hpp>

namespace boost { namespace mpl {

// default implementation, requires at least bi-directional iterators;
// conrete sequences might override it by specializing either the 
// 'back_impl' or the primary 'back' template

template< typename Tag >
struct back_impl
{
    template< typename Sequence > struct apply
    {
        typedef typename end<Sequence>::type end_;
        typedef typename prior<end_>::type last_;
        typedef typename deref<last_>::type type;
    };
};

BOOST_MPL_ALGORITM_TRAITS_LAMBDA_SPEC(1, back_impl)

}}

#endif // BOOST_MPL_AUX_BACK_IMPL_HPP_INCLUDED

/* back_impl.hpp
JE5VUBTlICZj0hvjmU1Vyj5L647VuQycSl6qAstZ19OKKkFLL8yHn6g8U0D1OjB+o974S+At+TMr3GlJN/0AL55zF89a87X3xee19yaqU3afIFL21/lDVfqjHICkR54rIb3kOoSXme2uwts9ZpTds76gvcVwqEYEKlB6HSejCb6S1IaN7lQDS0RohGshtW7CNU5/iC3+HqzDqZzDc5MjSdU4XD33qYWBEhqSrlMIa/Q71bNqJqb27bCbBR2o5+u5srsDnwmuE1dtMVeE9LpbI9Js4XO/SwuGpvhsnM6caqRY+jBbdDq1OtMi7LoQcP0sT5uljS27l8PQFcQdTA6ByF8L2Ajo9xjhAjuQQhDsCxr3COrz265tUcFaRO4lVy6i55Ji25ANMV9qHeKXunobGxcEsI3t8YOJUrAG5ZJr7V4iZo7tDetid4DiMAQ/zCiPA+118QfsImwXaAwZU8d6zXbu++PRROJaFASz7jR+AG8GWMQiOuVAcpsQqMLwH491KNrWj2N3QWUH67XoRn5dB914vmTD7+V4H2+6U+NCgohGunmzENWtRRta51qOFkYhs8MNf7PaiLB7P5n8PV8HeUXUY/xfPc7/yNf/wX5z/StfBzj8g/2GvSZK/c1yItzYXWop38ga3eYFU7WJ3g2YkjmJWZBL+SInxprA8vVsh7K7jfG7tiE1JVOrRlPj2m+4OG7s9J9KSRTmgsqb
*/