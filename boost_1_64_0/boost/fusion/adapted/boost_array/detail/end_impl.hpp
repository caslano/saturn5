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
VpccUdgILuWXHP6arOc6kisaT916PX40TPXjXPt0x68Kl6x2fg3Kc4lePHacTtLen+a/d70dFUrEwbhNpDiXThkaGk6RJvbuiAtuNgy+4qzVc52HHKwYOH9sTmux71LnGRXykN79ZFbwwkOVWg9T8E94a88ygtM6eksZwbETfvEM4OaImvQ8XY1cVBDkIDZmArRFtJsK9YVx6gVnT6uDu/U//HKnsZ5he4Z7jcf7yvSd0hifaIF5XrR8fULUnqBwH1u1wJj2w6TD2gO4KUg/7f2oyeUjTY7zJG3R7NF1ekpnPgTpYcPZK2muOCrqh1yPkAlzWY1VKw0E2djRAy/OZoap1eq4lwQPJ9uQbG9naDcCbiYmUbrEFsjen+SmhAy0crMPrlE6q6onARGSFosVm0r7mSIbZGq7qokoeCbzzRxR7DioS9AOkeIyapSAERJO9/7MNyPMN13hhkE6/IDq338Tp9ab6Cm6KNEd1H+jksOTtIbD1tEUazAUHuJwxH2pGeq6VbCdN4NRAWDtWUPcnm6nmySMuc+7rflDnearnGRnr5N3o3p7pvPTQg==
*/