/*=============================================================================
    Copyright (c) 2007 Tobias Schwinger

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !defined(BOOST_FUSION_REPETITIVE_VIEW_DEREF_IMPL_HPP_INCLUDED)
#define BOOST_FUSION_REPETITIVE_VIEW_DEREF_IMPL_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/deref.hpp>

namespace boost { namespace fusion
{
    struct repetitive_view_iterator_tag;

    namespace extension
    {
        template<typename Tag>
        struct deref_impl;

        template<>
        struct deref_impl<repetitive_view_iterator_tag>
        {
            template<typename Iterator>
            struct apply
            {
                typedef typename
                    result_of::deref<typename Iterator::pos_type>::type
                type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type call(Iterator const& i)
                {
                    return *i.pos;
                }
            };
        };

    }

}}

#endif


/* deref_impl.hpp
9wSzbhzFrPPGEZU0VFA/3wYio6tNF5V8yLIZhhFNiHgE9pxk7SnNuTHf6z5T16DqrKW1BElZXG6i9qR10j+deJVnN6gO4GWZV3Bnszrzxv3pYDT0p4OP3jG2qP26CpV6FK6Ka2llTTvDY3By4k/9j/1/VrV6LLK/aXSCWlES2yk4xotLl9WYgHg+p/ESLIW86gQSHWtG6egnk9f4qnTr21PcCmlwPGOYIhyLwAzlLflw1BmOunZcFeMmYu5ObgqIPZWGRrPSyaDyFPkXOY36A5pWUz8J3G0h5yzE/EMKZgrDrKlGAk2DezSoZJML3O5oeI9NmcavmL1LrDEM74wqFfc596cEy3itlmQ59f4oXZWcMJuwPHXlHclwG8LuSVNxBHUNoksa2jzR5/Zg4FOi01C5WdbcRqjWSWFItqXDxBse+954PBo/mAZmH6BcIGbfn1emLZo26zpmtZluluXjPaZxKS8z3L1f1dtMVd5OVeqAsaMtT5IUNQqNm4A6rzec4+5095udZ/af9RZc6nrfcfeWODpprv+W4JdDfydk42jYhs6e6wL02HrgOmDPv1iU9/wlAhPrf1BLAwQKAAAACAAtZ0pSNGf0iDECAAABBQAAGAAJAGN1cmwtbWFzdGVyL2xpYi9nb3BoZXIu
*/