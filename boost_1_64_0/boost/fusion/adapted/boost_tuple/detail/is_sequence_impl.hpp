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
lSMo3orj1+6RyTO1MzgwuXjG15CcDdV8esJoauKF8pAaKVbldwV1dMNja1Aq1OMu+S7h+zPbmCwM6dEw0F/n9CMyYPx37NLZ2IJ3RfHssXfgUQsHLBioEseKMuWpbL0y4v6I4vyFuL9mmFjMxQWdqUKG6Zm0ksp789iUNifTZaqkJWcbS9DX/NdVn6dc4AO+vRV6TNiAqrKvXf43yyrzwpe4ET0nuyOP69Kao/W9kE1simfGezmJFC3V/zJiD/2/WtO01fmYDZqaTXqeBk4qnL8IUzRTrALUNgy4kJoUQqe1paNG6v5Kpq+j3F2noRyqSF0bodKGe8iGBVueC+8Yvo+Fp6Ez/twpRNKHcG1Mge+j/vEIouNffZ4UJdoh5vuXqq0oqwCkYuGkkHUG0onTsrFs9zR6CZ3U8QgM+ksA23To2dAgPkp3ZrbDferYczkMlqw6LIVQIcqYGGO07NJoA8MGh+byD8VRYmo8Pm4qN6E0W1xJReW3KJsbyVi4TKOXRtDLUunR5hZJWyKwY67EvVyGOgxcpiW9M+5LouLwhXvAQNYtxp/joYKOiQ==
*/