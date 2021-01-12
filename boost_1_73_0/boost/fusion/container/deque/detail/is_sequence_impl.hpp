/*=============================================================================
    Copyright (c) 2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_CONTAINER_DEQUE_DETAIL_IS_SEQUENCE_IMPL_HPP
#define BOOST_FUSION_CONTAINER_DEQUE_DETAIL_IS_SEQUENCE_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace fusion
{
    struct deque_tag;

    namespace extension
    {
        template<typename T>
        struct is_sequence_impl;

        template<>
        struct is_sequence_impl<deque_tag>
        {
            template<typename Sequence>
            struct apply : mpl::true_ {};
        };
    }
}}

#endif

/* is_sequence_impl.hpp
zWM5t2U593623GSbOsma82JZttAGUW7pbaDvZIu5q5XQyphK8B51K+oKqKSFUOlDO37M62l20+aaW/H7XqAWZnHTmlh8tESLi5ZuidAOW3JpvzA3Plb2dCLW6qwlWt+06Odbp1imdZ9tV661nQ9Rv7JrtjYd09KT+qnGZOUYLuuLoX6jzTUNNrNM7eshOb2Pbe+w17Xje1KTNoScjLqvfNQw3mGPsdIa0UBTDUtBo37d08dU
*/