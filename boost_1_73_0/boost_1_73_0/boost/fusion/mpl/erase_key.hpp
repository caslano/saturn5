/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_ERASE_KEY_10022005_1907)
#define FUSION_ERASE_KEY_10022005_1907

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/erase_key.hpp>
#include <boost/fusion/support/tag_of.hpp>
#include <boost/fusion/algorithm/transformation/erase_key.hpp>
#include <boost/fusion/sequence/convert.hpp>

namespace boost { namespace mpl
{
    template <typename Tag>
    struct erase_key_impl;

    template <>
    struct erase_key_impl<fusion::fusion_sequence_tag>
    {
        template <typename Sequence, typename Key>
        struct apply
        {
            typedef typename
                fusion::result_of::erase_key<Sequence, Key>::type
            result;

            typedef typename
                fusion::result_of::convert<
                    typename fusion::detail::tag_of<Sequence>::type, result>::type
            type;
        };
    };
}}

#endif


/* erase_key.hpp
RuRPZxgqlaW48Oai6cWFk8aNnlIkt9quJmGVJE0FD51VZ/JGAmn+Th5XUqJsqlGqONTEovqJh2niU09R4/Nm4ubd6RJlhMeM+KRkqgaqTePQahM0+tE7yCMXK7xSTHTaOx859Q5Gk5y6ErD7siB3O1SKdnJz8sFGgS0CWwK2DOxpsONgp8DEnMOfRlzHphxyqr8OsebQL+PHvlVdFMjCK/lOZld/MmChrP3jRQbVyZVby3yDqtb0YHLoXO2zeos=
*/