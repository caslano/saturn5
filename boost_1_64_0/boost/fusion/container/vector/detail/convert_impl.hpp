/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_CONVERT_IMPL_09222005_1104)
#define FUSION_CONVERT_IMPL_09222005_1104

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/vector/detail/as_vector.hpp>
#include <boost/fusion/container/vector/vector.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>

namespace boost { namespace fusion
{
    struct vector_tag;

    namespace extension
    {
        template <typename T>
        struct convert_impl;

        template <>
        struct convert_impl<vector_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef typename detail::as_vector<result_of::size<Sequence>::value> gen;
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
esRDJ88rpS/K7jo8qBxvkHT4IQTgBroLgIg73OukE/ISyYHTqsO0OUImoqY1Mb+ExboWN9flaKALYx73ekh8YVW8SseRWmdkxxIJydXU4mnypqpwQDFA6Z8WEau89OLhtS3YWQDSm5OZD94boqffIXN90S73HFOXcihA5u+CIMqUptjld1HE5Ta9WWiSGWQHAsQdGiQPc4+qt8W79KKQNyBbOIjjzuKK8JFTtiQr6dD6PWdF00tNetzsVO0KJ312Bay9dAvh9xS2X+mAfgMrUfzLb3BQgJUnX9fvWsPfxCo595GntormhTArcR+af9mjJ1k6Ttxsud+ndmDHetRJP/Wk6jGQ3h9IHSIjZzbGx5ps1rVIsXQ1trBAaKMO1tQ8Vj3LZpucWxova8c+egipIqg7x8PSPLiBGyjqqxOC+MXFbQAvW1vZICTRZHrS5aJQYS6yLg4s/tNFEsgXtouSCD5kB5Q6zJ4BcYWrXbfJCOrPO6So1aUinKN+ZkHG1koOCN50B3PebYM9zjnEnW+N7ad60tPYV3AeTh3PITxk2+31d2R+eRVBVuZTDA==
*/