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
Eft/N/GJ3qWcT5yWXZxm7LijCQGMEzN+RRIe4PQ+itVbjoqBM6nCwkd/w306/wvOYNmiYNnSoH9FcOJyeFUgBF7qZDKhfPSwiS8Qq+5ysVOBQ4ILRmvgiCDJQ2ViEeYZtk6Ux5yBV2y8vA4pANBvFkM1lzgdodAPiU7HZpHVhmoTRLY7tO1iACUUtojwRx7T4mQTl8KHTstmHMZfAJYWJ9SxfaTZ+RmMuKqMokUoJUI13aEuTTCEuGCAIXr0SRyim1EsxD/Ndo204EcW13wnK1rqsijQLyAPoDOAYXCQ7nA5tpOoEOUZZsc2EWSxBRgV20cjnNxTQ8jZCxC6WUfICbQN1V7C8XLUEkLbcPwjQvUaQooFsZRvbnFZQvAdsJomfWBU1xNOxIrOYeu4CHAG4TIqdLzLSeoALSXZ3gOwGmlJ/ouT+UHgAIzeRSKCnUKiZy8Jt62ccx1V8MYJ2ODA3Dacjf9sHYgcj1wG3RACwEHg4bcIEaDgsZzyyF0JSbZtJHPa17VBCfEBrAAbQgvQAayQ5JYQiTFAA356rXMFEzSBJsp3m5FAugQrWs5FGhepJMuYdxHHa4SM1Er+C4MRhyIMBJkk+9c5zd6lLASSzG055qjHqzj8k+Fd4XCtyHDN57KMjR+2jlBi23VsNHoRKr3aonIu6hAiwCz2dcQoRF9AZg9OEJ1APpIU4bOCIU52iBnbdAI9vpwTiBNn
*/