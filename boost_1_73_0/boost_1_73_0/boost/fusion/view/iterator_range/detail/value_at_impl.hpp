/*=============================================================================
    Copyright (c) 2007 Tobias Schwinger

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !defined(BOOST_FUSION_ITERATOR_RANGE_VALUE_AT_IMPL_HPP_INCLUDED)
#define BOOST_FUSION_ITERATOR_RANGE_VALUE_AT_IMPL_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/advance.hpp>
#include <boost/fusion/iterator/value_of.hpp>

namespace boost { namespace fusion
{
    struct iterator_range_tag;

    namespace extension
    {
        template <typename Tag>
        struct value_at_impl;

        template <>
        struct value_at_impl<iterator_range_tag>
        {
            template <typename Seq, typename N>
            struct apply
            {
                typedef typename Seq::begin_type begin_type;
                typedef typename result_of::advance<begin_type,N>::type pos;
                typedef typename result_of::value_of<pos>::type type;
            };
        };
    }
}}

#endif


/* value_at_impl.hpp
O+G0bbhk23BTkgw3I8lw0Y1HUFnOnuyLlX4fN9faXxjZVWh01FN1O6uXDo+cE4zsKaj5mz3c3lc4b7/R7UPXR1IpqCloj0uJvBFcOyZ3yiunAmt0ZG8wMhyOv09ZE9SgsdLZ0DXVVrAGDmxHBbypLSqZp+AjjmfV7LS1zTprHrKNFmrWrVV0Syt0Ri1YH0x3zRmGojobRMWWIqiL6nHKw8oiNpYr6QgjGlht/I1wLyijoGHnxAqaUbewOfsd2TA=
*/