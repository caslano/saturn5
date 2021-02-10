/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_BEGIN_IMPL_27122005_1117)
#define BOOST_FUSION_BEGIN_IMPL_27122005_1117

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/adapted/boost_array/array_iterator.hpp>

namespace boost { namespace fusion {

    struct boost_array_tag;

    namespace extension
    {
        template<typename T>
        struct begin_impl;

        template <>
        struct begin_impl<boost_array_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef array_iterator<Sequence, 0> type;

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

/* begin_impl.hpp
XCbw3Y0id54sIDgDd77o8n3156eoDYaoNdDbTU0lsqiBrTcVo/kT8F+66ZaTnMP0MpoFYZIm/oX3zZ1dejCG3mgCXxquhf1bD3oVW+nJw8QZT5whGvRbSoncppIqPWP8opwkZozPYe5eeNbLtMsDHCnKga0pXJOqQTVjkZngOdPBpDLB8WIehLEfW+8Yz6omp3Ci0VrplR8tkzgTaH9Ooq//gf0SRVGhNl4QsKES/EpD730wUKdePI38MPGDuRUS7DlpPZaFj07LIux2h6wpKsPp5t7u2Iq2itHFZKLhqt00SXU90pJInsIIvqAWRseTYSvVh4gbVlU6RSPb1Sa7NpgsG5qxAkePjqq0kM/jYqbB/NTXpPvjPSTpWFbAQW6loiheHQDjQ1jhSrzX1bzHgmumFxl1aA6AdlaQEc6FMiPJicLtWtEtkrA0yS0lNQ5/fOTggccl0wvyjIVpaTpzo89eywPrQApEy9X09sy9nCXW0LyFUZAE02AWW+dJEtpwpn+iJA7bvpz5M8/4eX+7F6F+5oXVTtPo7s9Hs2acqT4OkBV9bdyD/yx4KQVt2EkAbzb07g8xektwsaiTiXUPE2H4YF8PqiH1FkY21n041Fs9+n0yORqPD4dD2B+8DvJIZ7vI2QOAXxxc6KMP
*/