/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_CONTAINER_SET_DETAIL_BEGIN_IMPL_HPP
#define BOOST_FUSION_CONTAINER_SET_DETAIL_BEGIN_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/basic_iterator.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct begin_impl;

    template <>
    struct begin_impl<set_tag>
    {
        template <typename Seq>
        struct apply
        {
            typedef
                basic_iterator<
                    set_iterator_tag
                  , typename Seq::category
                  , Seq
                  , 0
                >
            type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(Seq& seq)
            {
                return type(seq,0);
            }
        };
    };
}}}

#endif

/* begin_impl.hpp
EtgTLofHwdWwN7xV/T2s9n1aPrgBtfTHJej7Bofo27Ph32AD+BnMgJ/D5vAL2Abugz3hl3Ag/Frl29/M/aS98tAX8yf8OfwAJsAPYRL8MwzBj1z36XON52VMzH0S/U4Oi2AiLIYpsBSKnibYF14ET4Lz4AC4AA6Bi+BwuBSOhctgHlwBJ8PL4HR4BSyHV8F5cBVcDO+Hl8Hr4OXwRlgNb4I3wPVwvfrbBDfBe+Fd8AF4D9wG
*/