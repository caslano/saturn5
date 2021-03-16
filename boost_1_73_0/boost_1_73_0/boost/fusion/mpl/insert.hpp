/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_INSERT_10022005_1837)
#define FUSION_INSERT_10022005_1837

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/insert.hpp>
#include <boost/fusion/support/tag_of.hpp>
#include <boost/fusion/algorithm/transformation/insert.hpp>
#include <boost/fusion/sequence/convert.hpp>

namespace boost { namespace mpl
{
    template <typename Tag>
    struct insert_impl;

    template <>
    struct insert_impl<fusion::fusion_sequence_tag>
    {
        template <typename Sequence, typename Pos, typename T>
        struct apply
        {
            typedef typename
                fusion::result_of::insert<Sequence, Pos, T>::type
            result;

            typedef typename
                fusion::result_of::convert<
                    typename fusion::detail::tag_of<Sequence>::type, result>::type
            type;
        };
    };
}}

#endif


/* insert.hpp
wh//0p0mZ73hj9/4bmH881QzOWMLVHqZh9iLE38L6P/3cvY4/T8mZ7w3x1mSxssOXV6vYqvpXCK32s45kFj2IJaTiCXFaWLhDeB0LDwvRcciizPk7Cq+KrHwEn4dy1SniWUeYlnk1Hn2qqecYrOM2CqE2IkQnyPEUYTgYan2EoLNVugQnS0TgoeldIgBltHLKJyxpTi3lNel9IuYbamFv4jLLXvnApJ3ZRoqL+LJUwuLMM+bX8S8WQJvJqN/a1c=
*/