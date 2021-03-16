/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_BEGIN_IMPL_09242011_1744)
#define BOOST_FUSION_BEGIN_IMPL_09242011_1744

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/adapted/std_tuple/std_tuple_iterator.hpp>

namespace boost { namespace fusion
{
    struct std_tuple_tag;

    namespace extension
    {
        template<typename T>
        struct begin_impl;

        template <>
        struct begin_impl<std_tuple_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef std_tuple_iterator<Sequence, 0> type;

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

/* begin_impl.hpp
Z1dltHzAdzuJM8Ir517k+JTvMFqOoLpR7FrsPaxzl12o0wTd+slSXTxGWavJxzc3CFLJbwd0MbsDF4vNGn1DPDu0Ib6uOMQgyyG6UCD6BH6f9g3zRLTZ3tF6fMI/fuVERfDPc8eL1tXTpLXoHTU53La70HSoiJ+93D+gydEDPMB1r7iB//Es1a9PiNfzaOkzcbwB4orz6Fibxe8szz8Re1KboSd0YnK6XxQHydLUMKMR4iTXJI5Kknc2TBzzRx4=
*/