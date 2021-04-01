
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
HoxVHRSdP/cw+p0SSLsLMYZzb3pMi/ZvAzQxehH4w8mZS6KuMQqlEYcyGGvRG4qWQnEW01TKmg0huuu7Nv/+0R08OeoCUW+kJbmEvz0FIO5bEpjJXqOk5f7OP52HTn7Vk9Va3m8jjGbHd/U5YMnoP8CFOtRGBEnOZwrEoJOY/vo80zmmGOQbpW7r0nXOOIjZn7CbYnDZ3KE0+MzDlo7ZpvbvHEVsWf2pmOO96xSYew7C1FJc4bel6jNcqgiMH7OscJOxsgI3w0MqSAyfBh2IU0ldHrSbZddtCZ3UlHG6/RXRfnd21kpuzxhBAx7fIMLbKvlWXNDO5F6l/un8z/WMyORQVcgFFEd0sSCvT0Um1xh0gE3Dygu1QlH2GcLKo0Ar2n0ng6p8VJUDlTLHHZqm0Iq8kjTFIrix/43GhuSVKrisYrTVAvABldU2csWVIvNLS2n+S63BQAGYk2f+NhWHJSEQsdHha+hHffXvGoSe851KKFffOy7kLWi0UlZqznLQkcsTFBfvURuAU+HJJ1T9kWe0OUGNg2v/MbyNeK2npkVCkBJ4W0TS64RtmQ==
*/