/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_INSERT_RANGE_10022005_1838)
#define FUSION_INSERT_RANGE_10022005_1838

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/insert_range.hpp>
#include <boost/fusion/support/tag_of.hpp>
#include <boost/fusion/algorithm/transformation/insert_range.hpp>
#include <boost/fusion/sequence/convert.hpp>

namespace boost { namespace mpl
{
    template <typename Tag>
    struct insert_range_impl;

    template <>
    struct insert_range_impl<fusion::fusion_sequence_tag>
    {
        template <typename Sequence, typename Pos, typename Range>
        struct apply
        {
            typedef typename
                fusion::result_of::insert_range<Sequence, Pos, Range>::type
            result;

            typedef typename
                fusion::result_of::convert<
                    typename fusion::detail::tag_of<Sequence>::type, result>::type
            type;
        };
    };
}}

#endif


/* insert_range.hpp
CXoYpZTU62OGTlJDxZP6xrnK3kKajgjqhVjslDKJThaeuDhzgQ3riYDvVIyLbXzOedtGsMB3hygzhP6c7xzUbMN/6TYlQ2wlkImdWQFnfYZ5yM/0UkDW3m40t+dRct0tOgO7vgBvfUg68vMDYX8rRDnywwj3uKTNJfWvx0gI6i2XoWP2mOuoFenpGIk7Q9nOeVyZmGmVcS89g81JQn4k4EUNUxa3nkxCjt0u/+kHQ+EUpnh8B4/hYaLwyyVdTZ4pRYTw5tpqKzprRCdA3D31vNTTAL1iMfm7OmzZ7CaXNiKfNtFGwvoMq3RDMyTvm8sjUmNm6yM9TOTFDspTiETGNjXqCsX4Ia1AO006PwuUWOC7wLupAucUnWAQjrgutWRImquqynX+IH77laxBFCfTZMo6JjdxWd3z2syRlUzq9B/DACPHUiihJNo11sVkcZMYnSNBgHiEwuArwbINCjIpzVJIma0yLI4UtHfDoFqLwHSGytrQIKVO/ACMklOSq78PcsrY8N7kjXA13JG0u6y7FvzK8GlhGS8JXb0UJ7CB62RRe6RwmrbM3iRPAA==
*/