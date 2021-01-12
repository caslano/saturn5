/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_END_IMPL_09242011_1744)
#define BOOST_FUSION_END_IMPL_09242011_1744

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/adapted/std_tuple/std_tuple_iterator.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <tuple>

namespace boost { namespace fusion
{
    struct std_tuple_tag;

    namespace extension
    {
        template<typename T>
        struct end_impl;

        template <>
        struct end_impl<std_tuple_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef typename remove_const<Sequence>::type seq_type;
                static int const size = std::tuple_size<seq_type>::value;
                typedef std_tuple_iterator<Sequence, size> type;

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
AX6q/RjmVGVACeQb2w3aHyRo8ndAx8P/hJfAL3VcfAgOgYfhlfBrOBYegTPgNzr+/Q4ugcfhSngC3gdPwq3we7gT/gjfgKfgLviTjot/hl/DX6ATz2dheWjHM28BfTANRsF20A+Hwmg4GgbgYpgEN8FUuBlWgq/CpvADeDH8FjaHx2F76Ixvq8JE6KhrwDTYGTaAI1R/JmwJi2AreBNsA+/Q5048j7D12zl+v6f5pSHSX+N5
*/