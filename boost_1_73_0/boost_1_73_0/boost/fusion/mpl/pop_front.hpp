/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_POP_FRONT_10022005_1800)
#define FUSION_POP_FRONT_10022005_1800

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/pop_front.hpp>
#include <boost/fusion/support/tag_of.hpp>
#include <boost/fusion/algorithm/transformation/pop_front.hpp>
#include <boost/fusion/sequence/convert.hpp>

namespace boost { namespace mpl
{
    template <typename Tag>
    struct pop_front_impl;

    template <>
    struct pop_front_impl<fusion::fusion_sequence_tag>
    {
        template <typename Sequence>
        struct apply
        {
            typedef typename
                fusion::result_of::pop_front<Sequence>::type
            result;

            typedef typename
                fusion::result_of::convert<
                    typename fusion::detail::tag_of<Sequence>::type, result>::type
            type;
        };
    };
}}

#endif


/* pop_front.hpp
chnJhSRXkbzXobc/vo/k60ryGXib5GKHto16P8ldSsz9BL61w/MXE31dBnipIX1DBnh/lbUOvSMVNRWBwbabF2Mt5fzZbt4WeR2nS/IfJNeTpCPwGskNJGtJ0tsscDbppoZke5IbSfJyxjdJsmV68hP4I8lNDm3LdDPJh0huIXmY5FaHtln6Dkn+UYPamMAYkjtITiS5iyS/E95z6A4Jm7PRHRI+0x0SzUaBzQSbDVYFthBsBdhKMLZGqZnfYdg=
*/