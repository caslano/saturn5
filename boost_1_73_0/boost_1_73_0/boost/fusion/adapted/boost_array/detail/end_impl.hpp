/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_END_IMPL_27122005_1120)
#define BOOST_FUSION_END_IMPL_27122005_1120

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/adapted/boost_array/array_iterator.hpp>

namespace boost { namespace fusion {

    struct boost_array_tag;

    namespace extension
    {
        template <typename Tag>
        struct end_impl;

        template <>
        struct end_impl<boost_array_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef array_iterator<Sequence, Sequence::static_size> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& v)
                {
                    return type(v);
                }
            };
        };
    }
}}

#endif

/* end_impl.hpp
UgC7YzxnS6JjCjKl1vL3fj+uypwy6Scilv14VworU6sXWc0pmhXbglgrUAIqiSZoexNWIuGpXqlEdLiuljmXmbkPiwiLpC9KkJjnLRy5cpRNCghBWy1TW8KaoudKL1IUUrNtMrF6ZkhlbYHSqiyIjspCdomgwptQFQmWtX1diB1LW+W65K+0bB97AqKgqKBjB+AGHVgyyaUJX93wyrsJ4as9m9nTcA7eJdjTeYv32Z1ekDY4sZaA9+sSJUVRAl+tc47JM/JfOumGFV7B+GY28fwwCt1r54s9uXGiiT375MAIOkfH8Bclo+XdgU7Ol7r/cGIdn1kDOtBvETK5jSQq3Wn6kqgk4QZXMLWvHeNn4ItDai9Jg68Q7lhekbIp4VgUCdcQLK8hgvnU8wM3MH7jRZxXCcK55mxkmH0wavhY0PnLULr6HzjISCA56eQnYZiNn0jTSOkweu9r2gsnGM9cP3S9qeEz6gV7ardIXTJdpH47WWyFpBurVUUzgUts9KTTi0VVqHoODYk6Q7KidBCGdXGHZyeDRsiPHhue5xqiks3gs31hapQ1xjwlYZChynQ8T9Mbe9MLV4feHfUoSMsw9IjTzKVYoqZdotogFs1l0HSspn+BU5epwdASr4PbrtFop4OVt9UKC2WBV4Dc
*/