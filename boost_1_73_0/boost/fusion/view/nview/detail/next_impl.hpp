/*=============================================================================
    Copyright (c) 2009 Hartmut Kaiser

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !defined(BOOST_FUSION_NVIEW_NEXT_IMPL_SEP_24_2009_0116PM)
#define BOOST_FUSION_NVIEW_NEXT_IMPL_SEP_24_2009_0116PM

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/next.hpp>

namespace boost { namespace fusion
{
    struct nview_iterator_tag;

    template <typename Sequence, typename Pos>
    struct nview_iterator;

    namespace extension
    {
        template <typename Tag>
        struct next_impl;

        template <>
        struct next_impl<nview_iterator_tag>
        {
            template <typename Iterator>
            struct apply
            {
                typedef typename Iterator::first_type first_type;
                typedef typename Iterator::sequence_type sequence_type;

                typedef nview_iterator<sequence_type,
                    typename result_of::next<first_type>::type> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& i)
                {
                    return type(i.seq);
                }
            };
        };
    }

}}

#endif

/* next_impl.hpp
ydvPz8V27ChI7MJxPWtdTZKH9uIiZpLrTPYjOH5fkSde6eYFyUYvbPL6eFH2PMkjjB6pVfKyP1nIw/RPvXufM3m7SN7zZNnzDLVoO1Z5gOXvpJCH0LYgtv2KyZug9vBqjp2qoixMcGDeGi4NB32ex1NCJnBl5tglk4leqdXnaY7NrapKcNIS7XKxv76wtqS7ISb7k0J24hVuhIkwkw1jarFf4djMKlwvwpukgbW6op4JdfGu
*/