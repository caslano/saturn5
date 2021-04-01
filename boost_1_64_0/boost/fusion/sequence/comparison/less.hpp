/*=============================================================================
    Copyright (c) 1999-2003 Jaakko Jarvi
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_LESS_05052005_0432)
#define FUSION_LESS_05052005_0432

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>
#include <boost/fusion/sequence/comparison/detail/less.hpp>
#include <boost/fusion/sequence/comparison/enable_comparison.hpp>

namespace boost { namespace fusion
{
    template <typename Seq1, typename Seq2>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline bool
    less(Seq1 const& a, Seq2 const& b)
    {
        return detail::sequence_less<Seq1 const, Seq2 const>::
            call(fusion::begin(a), fusion::begin(b));
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
        operator<(Seq1 const& a, Seq2 const& b)
        {
            return fusion::less(a, b);
        }
    }
    using operators::operator<;
}}

#endif

/* less.hpp
UgYoqdWavrd0GqNN/rwMu3ngW4Za+R8YiFQaoQwKSnYm4gkj5NwbBhwYF9uMXFVSTmp8Y2VTofR0cIY4vkGT4dPxWyUTXIMMKeCXVHNkTGovCh9HxfTvyNjtSfnzbj4pTO20qj0C3h1W0C+prl1xLX0d1bY9siR7VP+tDcXmuOr866mvF2/U71QYe/CaVa7Llr1BdfHaM1qVsWVonOoCJt8GobIwCk0TDz6/5KGdfZMVxkyAY48oiGpFYf83poVo5zrqTSXmagh/XqHuPhOQ9qukYkD+/56qrP+uzjc8H2C6L90IYp/w6gnO0U4T3S2Kna+zVfx6x3JpD4X/N0+GqM5OoqPSM1V31Jh8JERbu3yUji1Bl/op6iUlULpNNVFE2nrwMJYGQEg/pXAz4sTnLC23RUuX3Jll6xogodHnq80+fDU/rpqNH5qBI0bSS0CDkZi4B2TuzdxV7JurXGtXgMj9cF9bh+GzszM2FNH0ZlzGsJBTXo5e3l5LF1S+EPoVhK9gD55bglkbGKWPQRf1U6Pi1n6S+t87E5ioTMMR+BsD2NxnL58WFb1ThQ==
*/