/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_CONTAINER_SET_DETAIL_END_IMPL_HPP
#define BOOST_FUSION_CONTAINER_SET_DETAIL_END_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/basic_iterator.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct end_impl;

    template <>
    struct end_impl<set_tag>
    {
        template <typename Seq>
        struct apply
        {
            typedef
                basic_iterator<
                    set_iterator_tag
                  , typename Seq::category
                  , Seq
                  , Seq::size::value
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

/* end_impl.hpp
SiiFgK2lQuHYLHdFH4XqSmgQQ7H0xUMmzbZuF2SSYk09wY0taljdN5qmMpYB6CjnAFTMZgMOPTNwtJcBNGWU6K5iNXIbTDckWKFY4lCZBakr2Pb0HdWaoEBiIYLO3K2GbTdmiAQiTsMkdRXMj8uTDeRZszPOZ1vbqERmGQ894ctiPumDABAvAeeGSRA74qsazJWT3FnN9ORHjIacRXXimEF7Z4AzRIWOMKCeM/nNjDE268bto4dIqghD1Q180dU=
*/