/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_VALUE_AT_IMPL_05052005_0232)
#define FUSION_VALUE_AT_IMPL_05052005_0232

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/at.hpp>

namespace boost { namespace fusion
{
    struct vector_tag;

    namespace extension
    {
        template <typename Tag>
        struct value_at_impl;

        template <>
        struct value_at_impl<vector_tag>
        {
            template <typename Sequence, typename N>
            struct apply
            {
                typedef typename mpl::at<typename Sequence::types, N>::type type;
            };
        };
    }
}}

#endif

/* value_at_impl.hpp
IH9tbC9mpx2PdjUAGfkboSjPCAYNhtSEV9l8Z0cbVpezM6LHf6MWeZKXOUNldByV0bDhbmgelaeBYVOkfcwiH2laTi8Ww1id0XUEX64eMuSRsk2YmnyKbI3A7831v+9MrM15dSvGvvbAuKVjHS+/eCSoRScekazP47B6bKpx29DkSmfCJirdjo9MY9so/+kLPAUArOFtyKq3qbJOqBWOcYgiOXBYdd5T2+QR+DmJHR7rPHGHjjYw4ji7iL8GJwJCxM78xsrruWOKtBKK/Eghb2J8TqJQWdqifLZ+GxPHx20TONIMAVOC9AHC+FXLXFsTwAA8utHBp0Az10OG0RlAkdBtPV5x1EEWSI6ZDJ7yIO0S+ptRUof9UZDWtDx2E3T8kBpXTb3Eld+tpYmjdAI+TQGOIcz2Afbrprwwitz0IhV2SehctCJp/2AGQ/ljJgEBGbABE20QXhfPlnuvphOt6FO0kI2SketuKStejwAL5HoDHtVVDiwuYk8xB12fOJNucxuCW8RQIwCSUHAsQtQ4uJfCW1V7OVQIgYvo8+Q2FImXM/qPoJ3+Xpd+wQ==
*/