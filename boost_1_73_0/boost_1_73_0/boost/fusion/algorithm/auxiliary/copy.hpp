/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_COPY_02162011_2308)
#define FUSION_COPY_02162011_2308

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>
#include <boost/fusion/sequence/comparison/detail/equal_to.hpp>
#include <boost/fusion/support/is_sequence.hpp>
#include <boost/config.hpp>
#include <boost/static_assert.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/mpl/and.hpp>

#if defined (BOOST_MSVC)
#  pragma warning(push)
#  pragma warning (disable: 4100) // unreferenced formal parameter
#endif

namespace boost { namespace fusion
{
    namespace detail
    {
        template <typename Seq1, typename Seq2>
        struct sequence_copy
        {
            typedef typename result_of::end<Seq1>::type end1_type;
            typedef typename result_of::end<Seq2>::type end2_type;

            template <typename I1, typename I2>
            BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static void
            call(I1 const&, I2 const&, mpl::true_)
            {
            }

            template <typename I1, typename I2>
            BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static void
            call(I1 const& src, I2 const& dest, mpl::false_)
            {
                *dest = *src;
                call(fusion::next(src), fusion::next(dest));
            }

            template <typename I1, typename I2>
            BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static void
            call(I1 const& src, I2 const& dest)
            {
                typename result_of::equal_to<I1, end1_type>::type eq;
                return call(src, dest, eq);
            }
        };
    }

    namespace result_of
    {
        template <typename Seq1, typename Seq2>
        struct copy
            : enable_if<mpl::and_<
                  traits::is_sequence<Seq1>,
                  traits::is_sequence<Seq2>
              > > {};
    }

    template <typename Seq1, typename Seq2>
    BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::copy<Seq1 const, Seq2>::type
    copy(Seq1 const& src, Seq2& dest)
    {
        BOOST_STATIC_ASSERT(
            result_of::size<Seq1>::value <= result_of::size<Seq2>::value);

        detail::sequence_copy<
            Seq1 const, Seq2>::
            call(fusion::begin(src), fusion::begin(dest));
    }
}}

#if defined (BOOST_MSVC)
#  pragma warning(pop)
#endif

#endif

/* copy.hpp
XchHUIlNSRMtLyWC8rGcbtd4t1ITVaxWkBMRoSYaPF7XJSrOPrfvSuRn4tWJxLC6JpGyel2XqK8TSzQx9vHqwhKtRxPZBGLkXSqe7tO5kAiGqtJNlxMpVbqQSPMROcwe72iJ6qI7gjT7qEnFhr7oTXGPwQatyeZYnXL9jmMnUx/zWMnW6U1Lhp2ASXZP8QUsywkzhlXQfzDGnuIRzGohUSorOht1qfaJdrsd2L412NI00Xqot8fESaqOWTcqEYf0dI/BwCpzqRlPllQ9yL2UqC7VPWk8EdhrJnKGvlipweC5VTBasHHMHlWcFaw7IodhZa0FZ73YHddj4VxZYkO+k1h/CuuEIrDbVEArLaKSH6KDAbahWJOBWSe9eAMG5hEsuL1vjWObW4ypIRIEs2pHPyqF/gf72IpgReHNcKrFBPtUw9pwDhCiHxzmDFj4QY4Y7wDvsDyLE9e6TXYyNcFuCSYK1lWBCRPl0orWnyd3y3845LMck6ZhrT0mWa0mBHbG1OyCvN7kGpfGtAG7nZEWyR8SQ04a+4YjTRJHdSQcu1h7Gyjkhx2h8kYflSRHA+qZG3Btt+IOg3KBazlgDfWnozqO6x24WM5qSJTtfyWZlrfWioxt56GAFfUMay9R3sLJu8P6qSz95aRcPcWb
*/