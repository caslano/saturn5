/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_IS_SEQUENCE_IMPL_09272006_0726)
#define BOOST_FUSION_IS_SEQUENCE_IMPL_09272006_0726

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace fusion 
{
    struct boost_tuple_tag;

    namespace extension
    {
        template<typename Tag>
        struct is_sequence_impl;

        template<>
        struct is_sequence_impl<boost_tuple_tag>
        {
            template<typename Sequence>
            struct apply : mpl::true_ {};
        };
    }
}}

#endif

/* is_sequence_impl.hpp
jdt0dcttlxSK81herXey9H2Y+sZgMbdn1ljQ1R6Tyc2mfMkROwnS/7WP5+zZYxhTknV/bZNZmhGkIPf5ncI8HabRRPSlmnfmi1LfdvdvFFO7dNpKltkz2Pk9JWFPq7W38C7RNRNdjsbPbtG1sLJdewv/LLrelvOOzdX+hIDRUw/gfou5P5k7r/fQi7Q90SkvFq93esMa6TgFuce9XrFy3rSSWDnb62TTL2f6sKvyxYrZq7Cb
*/