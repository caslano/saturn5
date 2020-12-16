/*=============================================================================
    Copyright (c) 2007 Tobias Schwinger

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !defined(BOOST_FUSION_REPETITIVE_VIEW_END_IMPL_HPP_INCLUDED)
#define BOOST_FUSION_REPETITIVE_VIEW_END_IMPL_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/view/repetitive_view/repetitive_view_fwd.hpp>

namespace boost { namespace fusion
{
    struct repetitive_view_tag;

    template <typename Sequence, typename Pos>
    struct repetitive_view_iterator;

    namespace extension
    {
        template<typename Tag>
        struct end_impl;

        template<>
        struct end_impl<repetitive_view_tag>
        {
            template<typename View>
            struct apply
            {
                typedef typename View::sequence_type sequence_type;

                typedef repetitive_view_iterator<sequence_type,
                    typename result_of::end<sequence_type>::type > type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type call(View const& v)
                {
                    return type(v.seq,end(v.seq));
                }
            };
        };

    }

}}

#endif


/* end_impl.hpp
62lvt43ac4M4lxJ2bVXCceqjjVaoxMrr0KH+bqrLJjyXIlN/ztGJ9pRZ7F7zBrov/927RW4W81aYvtCgSNpzoUUy+zb7rwHy861WOMssYsGmJWRb8RrH7Hzrn8spT7R3zBKyz21L/bfNCq+YHZp+rhTFtx3v3Zi98liz0NjdYYUYZv2yB2alvkV7yKzOAs8hqstOK8xldrxVuqLUf7us0JnZvdpTI6gfdqvbrD2+Z5piR7vOLI/n8VNal/ZY4Rhvl9PvF5Htxesfmfr3ETxowWTq31y377NCFmniHeWizdDySlP/XitaUTL1fI/fp5rTqvmepFFewH7v5Tn3ey8vcr/38hL2ey/Po5Gn/cD/mvystPc8IzXSJXi1/u3goBVWCdsA/Tsv/5KT3hGZiHbZKG38guNknmNibyFM9W7J41aIY+nyF2p4TzH7WSsc1Esb/qVCFsViLljxeaq0u+W7nVEs6aKIQZiMofgwxyUrfX53I77v8Erasw0Vc6OVZNZuSJmcisWjDWd2e1CfQMVciVZIyyzlvVsiz1R2tVvWQorFpLKU92eJ8tBqMvtctGwnxQIuW6EPs9VPW/9B73pE26yXNmnKRYoBrlrhrU5avgkfV1I9r1uhrEHaqC/vg+ndkres8MUkzfHatJPyfGgFI8vTZ0k2K7XLIytEgbQzXb/spXSPrdCVpTs9etx0xRKeiH2qsKppbkdR7E9xTDAbUfPuLcrz33ivz/LM/O075el4ZoWFIG0x3p7R+zjRnjOLtf1eUjH7Cyt0AdaekKETtTXaJGYNcg+vQrG/tMLfBjZeXvyk2J1vrXACpM0zR3wheyf2VcKsN0+dpDGhYfZ/xB5dWOU9u2gsed6LfaqwMsE9GlA9P4jnK0oMwXv20Zj4aIXXLM8sZSeWpjw/i3MiYcUMFppHCV+s8IBZW0vanpTuq1g/haWsn6Jvv4k1UljKGinq+c17ukiNdAloWZilrIOiLt806vJdrCHC+Bri+u69vJjv3suL/+69PI9GefYf3i3sh/e6xP3wXpeEH97rkqSRLuCn93TOn97rGfnTWz0H90r4KeffJjyrnPrXpljFksAGD5iNr13DX7EAvQ3qMOvgv6KOYm60VcwulVgTopjTYIO+zLbn3FxPsUS0pjppZ77OaaxYpMkGvzDzfEhooJjd14b3n9IGlM/8kcrzs4FLLy0h4z63Yg5/G8SBtLQPO6dRDKw2eMmscsW/C1E6mw3KsLq07F7nHLVnGhu8Bmn2R+/WUnumtcFqlu719qF7qLz0NrCweq5ce2OgYjEZbdAQpPVtenYR5Ynm8JE29vBvAxSLz2mD4SAtPnf2moq5ctmgO7Oixwb5UD+gzWH1bPa00yuyPDYYAdI+5V9O48Vtt8E9Zjkti7NTDHlt4GZ5lpt6db9iYYE26AHSJhr+nqyYBy0vs5QxL8ZgfhsEMePj2pXfe7pIjXQJGumSNNI5CtigKLOU+SfapYD3POM00nkKeCuv23B7QZnn7zB4oCNDWqNiLjQdM8ucfno6r0NzCduc6uwwEU05Q9qSfJ6li6QzOWchG6RhlrI3FHmiVWZWMPxgOL07E20us179dH0Ucxe2wSJm/WYVKURneUFq8y1/cTudf6KlZcbf1xxQxAY2Ziln9+LMCk3Zq22FiIjFf45tTudSRW0whtnArBVL0+c10MKYvRj8sTCddRWzQV1mW6vH3qMzK7Q0OmnPX5f5h+pSQp3nXFf3+vSuTrROLF2xKf8YqDyHDUIpnfrdmYlo55mtmrz9IFkpG1RntnOWozudAZYWY1AYP6t0a1g8Wllm3V80za8YBIvxKSxlzIvygjXKU5u6PA1LQguSJs4=
*/