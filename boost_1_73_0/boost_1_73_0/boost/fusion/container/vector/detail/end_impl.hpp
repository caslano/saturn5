/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_END_IMPL_05042005_1142)
#define FUSION_END_IMPL_05042005_1142

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/vector/vector_iterator.hpp>

namespace boost { namespace fusion
{
    struct vector_tag;

    namespace extension
    {
        template <typename Tag>
        struct end_impl;

        template <>
        struct end_impl<vector_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef typename Sequence::size size;
                typedef vector_iterator<Sequence, size::value> type;

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
QJWJGqM3GOxWj8bGA2LtKGKVrpPBA3BCLi0jmnOgglOZTmFzDE5PgfKtI8GPOEhsTym6DIbEObdV91n9VrdZbKOBg4AXX4G3+4FTr9/aqOnzfDTh5VC2INnTl8AXMNLgCCpUVXN6glojaAHO2Ci3UMs0KcVshcpgq0/LDIk8uHN5MMqxs/vAG/pCLTBPVF3LV12IBIU4XuEAQiqYpBFi0fmatFZWhasGqhzNB3Drj4PdpgjN5fU2hXwZ+eJgQAs=
*/