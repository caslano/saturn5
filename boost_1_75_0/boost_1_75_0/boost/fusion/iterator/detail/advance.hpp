/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_ADVANCE_09172005_1149)
#define FUSION_ADVANCE_09172005_1149

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/fusion/iterator/prior.hpp>

namespace boost { namespace fusion { namespace advance_detail
{
    // Default advance implementation, perform next(i)
    // or prior(i) N times.

    template <typename Iterator, int N>
    struct forward;

    template <typename Iterator, int N>
    struct next_forward
    {
        typedef typename
            forward<
                typename result_of::next<Iterator>::type
              , N-1
            >::type
        type;
    };

    template <typename Iterator, int N>
    struct forward
    {
        typedef typename
            mpl::eval_if_c<
                (N == 0)
              , mpl::identity<Iterator>
              , next_forward<Iterator, N>
            >::type
        type;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type const&
        call(type const& i)
        {
            return i;
        }

        template <typename I>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type
        call(I const& i)
        {
            return call(fusion::next(i));
        }
    };

    template <typename Iterator, int N>
    struct backward;

    template <typename Iterator, int N>
    struct next_backward
    {
        typedef typename
            backward<
                typename result_of::prior<Iterator>::type
              , N+1
            >::type
        type;
    };

    template <typename Iterator, int N>
    struct backward
    {
        typedef typename
            mpl::eval_if_c<
                (N == 0)
              , mpl::identity<Iterator>
              , next_backward<Iterator, N>
            >::type
        type;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type const&
        call(type const& i)
        {
            return i;
        }

        template <typename I>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type
        call(I const& i)
        {
            return call(fusion::prior(i));
        }
    };

}}}

#endif

/* advance.hpp
09rRCpT6NnqhR+drtqlW6I3w0LOei05d27IUOhO4gpsX+ALbugv/nMBGVt+O+v83YjUF3tBsf7DiYY28zB3tkq8dBfZ8DFh3aNwgWAWaS9E8sF2t9Dg6PJLvvEvpiC7m9lUaDYehdTk6XJKvIzo71HJf4PpQS3LAhdm9r8Y/vfHngNAFa6Avl4+O5Bqc+H3r2s9xCPHK+Q8H1Yaa7aFau6NBmt5uVO62fpl/mjKrarZZFpg01ubYLJGqzZR65mXhdKPpO7wMl3D5eIClRZ6muwhedIo5ocOrTJAX3vGD+k9yKcCc7CDlE0woQbHXI3q6nRAJjmo2T3cgFYEjKbSXC8CUhEPnfAOPuzjTF3Zm+cKyHVUXvogzS01n7bahvvjhmv+CV6ucVcu/0LT80/DEnbIyQflQqknFBTyRVkpJd1opEgilyE8kD/DTJsSi+hCBgLho8H3UFEhl4VzUg+Y2yQcvkpaiCyBbaM0D1xj++/E2hLPqJwzPAELQBIYZIk/No93IknoGdWfQgNw65HQH25Vb23ObIkVmYRpKpqNpCulWjHfrb/xhmK4bu0VH2+y1xtjBigmq+yxibiZ3v5TOyOSGxuvEOI3OoTIdwhlUiPLqxWL+QdhwbjaRx+Sf1hCwY1+8JqMdBIM+1UUqrIe+mm2EBaEe2tfu192iCPZY1myvWizsVORUi4EIfOQuJvvnbhr5UpTq30EODjKJ
*/