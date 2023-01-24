/*=============================================================================
    Copyright (c) 1999-2003 Jaakko Jarvi
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_GREATER_05052005_0432)
#define FUSION_GREATER_05052005_0432

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>
#include <boost/fusion/sequence/comparison/enable_comparison.hpp>

#if defined(FUSION_DIRECT_OPERATOR_USAGE)
#include <boost/fusion/sequence/comparison/detail/greater.hpp>
#else
#include <boost/fusion/sequence/comparison/less.hpp>
#endif

namespace boost { namespace fusion
{
    template <typename Seq1, typename Seq2>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline bool
    greater(Seq1 const& a, Seq2 const& b)
    {
#if defined(FUSION_DIRECT_OPERATOR_USAGE)
        return detail::sequence_greater<Seq1 const, Seq2 const>::
            call(fusion::begin(a), fusion::begin(b));
#else
        return (b < a);
#endif
    }

    namespace operators
    {
        template <typename Seq1, typename Seq2>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        inline typename
            boost::enable_if<
                traits::enable_comparison<Seq1, Seq2>
              , bool
            >::type
        operator>(Seq1 const& a, Seq2 const& b)
        {
            return fusion::greater(a, b);
        }
    }
    using operators::operator>;
}}

#endif

/* greater.hpp
jpNN1NjskRXIZi/0VGJiK23cTDoM7qgDqxXM4KkKYvks+ecL4bORC4nPbspsy2dfBjQ+i20JWe2uGZQZ0WC0WQt50ESdzXx5HbJZu3Hw0H8uBL43FxB8r2a0hW9IIDoORLmQr+Er/ZRdBJYXUfj2L2gN3z9yO4BPuaGHoq7YoW2K7/4pydgU1w5/Qq/D3dCNN16C19oBUDTKc/eCSZXkgIHxAZJoyfq+L2aX/F5sEnfJ9XgPOjNrp4ru/clg5nYCTuPFV+aTeHv+Coqy8zyPY/K8cg10vt4o8Nx6bsp2zQu6AnA7E2pcgrIPYdyYcIkm+170acJC48GP53NRwbnwb9fz/knlNsVGU4w9FM/e8CPGYqbImp0U9km0VIqBIzcFxUxM1ZxfOd2iimRuLXDBYix3hDwwIXC6YNo1mxAhDGkZCGWJ2RTqwVKjZLgQy9uy0F5v+Vouq1T+SituVFkDDQkBtWDaNCTpWFQyMOKvO/SfTkLvApOQatG+Ey4amSWkjkkVLro5V0gdkQ73EtznwH2xMpl2OqoKAtWV7sB/zP4aPE8rRS5nP0uhnzpRFpxdSkG0EKX8VVAqFQD0doRXvjkLINVCfEx3mkw8kgelAOJ2nw5yoxXFns1f8ON8TumZEZ3SjRQps9f3z9pMbHa8k91rc7L7k9ntqU42O83JbukpCTVSqAYjgMFCb7gtelsBt6nRW1j0DU+L3sLa
*/