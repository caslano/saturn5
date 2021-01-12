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
+Z4kQNFVrUEMkW86yd2qb3Cx3rlJ3H1pZB5dK/pjzB6eCS1kX4/u10Uikehbs1IYtK9biHvXJqdF1jxulvuPs98pjp0GAftaRrPoWkb79Kp1WrZGF/nXGIqae3aeN2vB/SVcp1vXjjPR3S5+vmtbUzdhKxM/2zIsfpjdmX3ErxLSlhQuWhLZI8yam3e+Ywv6Sor9P/ArKdA+3I01zxbhE/g7KdybFdzmwajcpG+956VZ8kDX
*/