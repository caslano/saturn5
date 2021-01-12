/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_VALUE_OF_IMPL_07202005_0900)
#define FUSION_VALUE_OF_IMPL_07202005_0900

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/value_of.hpp>
#include <boost/fusion/iterator/prior.hpp>

namespace boost { namespace fusion
{
    struct reverse_view_iterator_tag;

    namespace extension
    {
        template <typename Tag>
        struct value_of_impl;

        template <>
        struct value_of_impl<reverse_view_iterator_tag>
        {
            template <typename Iterator>
            struct apply
            {
                typedef typename
                    result_of::value_of<
                        typename result_of::prior<
                            typename Iterator::first_type
                        >::type
                    >::type
                type;
            };
        };
    }
}}

#endif



/* value_of_impl.hpp
fbnP1DQPydAVbAB2QHV2ZtjpRzwnDdw803puahntf2UBlb2AUWzhKEpVz2hVrYk8WW+SukJ0c1TYuWfdS+epHkIHfWxknmj7WCTRZM2iOjvK5WBTGYOOl6Wxj35ygHBQ9K5YTGzqjGjseKzgr6wwzD1EjRWWB5WoDmdpCJXosXPXOHYgMRvCp42+7BeP3k/OdwonC/0YAZYljef1mhZdxcZQ20FT9/GeSdlff5DL8iPUl2/j
*/