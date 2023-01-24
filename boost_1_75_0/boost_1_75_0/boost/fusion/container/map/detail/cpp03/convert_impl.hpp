/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_CONVERT_IMPL_09232005_1340)
#define FUSION_CONVERT_IMPL_09232005_1340

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/map/detail/cpp03/as_map.hpp>
#include <boost/fusion/container/map/detail/cpp03/map.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>

namespace boost { namespace fusion
{
    struct map_tag;

    namespace extension
    {
        template <typename T>
        struct convert_impl;

        template <>
        struct convert_impl<map_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef typename
                    detail::as_map<
                        result_of::size<Sequence>::value
                      , is_base_of<
                            associative_tag
                          , typename traits::category_of<Sequence>::type>::value
                    >
                gen;
                typedef typename gen::
                    template apply<typename result_of::begin<Sequence>::type>::type
                type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type call(Sequence& seq)
                {
                    return gen::call(fusion::begin(seq));
                }
            };
        };
    }
}}

#endif

/* convert_impl.hpp
YI0oScu2gZbtfmgFvHagbDBnhVUSfPqUDsIITJUr9Tn5asmpwzFVrtcpkOo7Jb0VwrUi+xQMD6wdv5fXRryzvC/msXMXdxh8mYFQQztKpUnaYXDDeiGN/49MTDLcNwL1E/xapGQq40n8PtRh4Me6QZDc3/FgLxYHu3GjnZVJ96srsinseSMesMkUXEDBuRQ4KXBQYKXghBeDQxT8SsGPFHxLwV4KdlKwhYL1FKyiYCkF71HwJgWvUjCPgmcoeIqCUgomU1BEwQQK7qUgj4JbvCadAbKDV/IrvY/a7nlNl3U6hrvkl2BCCIUe8lAbAraKaReTGYk8w4xEHu4XBSzYUWdhBqh0Y7+VH1OHm7XugEUo9WGlGqnm6icqryKTDmWoQFZJKmWVq1ml0DZuYJyhrRcqGQWrQ+qFm4WjbsbesWI8vgClXo3yUbLVZT3iQiQCklhEqtaii0jNj2pOCr6iR5iIVAFLCTwSRc1SreuzA7aRu0CcaL24wrE40RazONGWosdhXAvpwekDH2qso9wn9FWdk6M/U5OU3s8XxaEkVAoD8sdFLCFgUsLacFF4z4Dg2Hg6VJJlqfiO7MLQG5jJUrqoQKf5UN0RJBcaKylUjupTOo+ndCFPKUo4ugouQs+JSSC8LGWJuEu98u0W6edLyqSQvT+YEIV8QKPlwAPQCRJZmWkyTH/+ReAGcz7GKLw+9yWTFoR0KW3XXIeT
*/