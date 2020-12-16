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
Z1YF78Z7nlhAHiiOh27qOQ8xX3xNvtidHnOcOblH8LxAgpo4Np44SJ4Qmse+WvEBfekVEEvEqdToce6/ll7kfGj9sie1COsej9xXohvYchTe+neD8wCx9q/YGjxM3wjdt+IrN/THjugp1FBXXEQt/imfd6Jj96BH5CGeG7ogU3wH84SexueSx6ffR3ehzfPUAPo26M01+OS95D7ohucb/AtnYP6XuEYNlcKfie7kZPZ7xrdA13Hs/3fsezK6EGa/9PHSK/GlFnIjN/KvZQ1kmPk9uXiMPO4F6F2IXmzG78SLsRFqsrXMA06C96BV8Uxg2pbXicT3xexpFb8XUbv0xv9+RE6NHKLdsNsLkR29BxEhTuFjfGOxWezAWo//YW+pN5H3HnjfGx6/Ngo9o3bjTCD19WhiAnnqYnzPAPzRHvT7CHrF/yLfuYq8m7zE88lQ+svwdCvyuIh7tmPDD/I3eZb4BTntQeQJq5HhzeguebpvKTRCXwJfGTsaG3tqLDk4+Th9eWH3cuawJj42Mw6e7EAutw+jBsTmy9gv8opTP6Q+pk5E5mlsMnMYtroHPtnrLB3OWRH3XoW+oS/Wu9gVvdM463sv4b5VxDF4mDmaNe6Fn+h3bCgxMDKE9xrRd4a++AnYyfP41A34uifJs35WRP3DvJei99i+tQUfshE534Qe2rydiF9Bhy3sINWFOFU3ntxrGDEWPV6PruDHq16HNruvtRb8qyzeBYWe8X0B63z405f8tY285cXerAsfd9I/vYYYYOf707BHzvzRP3w7etJzCPkN+wshh3ruQyc9+FIxkbW7YdPc76c2RO/p0w3Fd8PjldQ77X09eNfmEekt+MfjBlNr4C/xk2nqg/g0fAU1QLKNvIa6Kr4cfxMYhM/i7InvycTgY+oN6qsn0eXxyARZWrPQ48P4+07kip9LTyXePk5cOQ8ariMPPRw/sAk9gZbQOZx38kxRag76eprd80Iv/0itS00dgx4LmxBPYwtXECvHoqMz4R9+M7qDXK6W63vwN+zN+o77zxzFM4zgHEhPtHww8oKOMubYMJDzGWz9j/iSSeRY2ESiFB5sxfel6ety3hP/AB/6V3LfbQOoS3tgg9A+gRzi8tGMxKw0Ocx64Bb7Pp/f3tBHPhjvNRh6qHXYWxxaU9iEtQo7wn4zy9ExfITnTXwF/t0PXmotfvYM7HkdsbCa/oud0+9l/TrskOffvdCa/gd+vxt1FT4mtoQ6nb5a6ELwT2RNnoFLc9aVgUd+7NRzFPpzA/qXZl3sSpyFTl1AfFjKXH9m7vvJXbrAf+r50HbOczfQC7yRe8lvYvjvFP4i9APyxG+ldpNvo4uxgeggPjyxBftBnsmjiaHMYX3OczqfYyPH2jqMnIb1xw6xv3HsYy35wAvkyD3HEyeI+eug9bf4Knjgvxu8fujYUb2xZXz3J/joZ8gbpvflvHAUtTt5HnmSZwV6voi8EVurSuGHxAh0Gt5ehL7vxz1fFNFHGU7/HFuLoU9cy+xHfUEOlFiNr7KIMYN7CYhF9sTw7YPJ0dCPqdgN66dPQx9uQY9/O4Q4hx+gF5GhR5LiGQ1BTI51Yh/XYkvk0enXoGHKQJ4NwS8Q/9LEufQg9jeI67eQU6ag6W74eE8xvhTePQSdK9HLCPGEui55DfK+Dfgr+IOv4N0L/LJPH9dFkj4B/E+B5z1+HHuDLs76rIP7c941Ct6AY/eeX0KHsLXYneSzx/P5hSG8exbdaSBnOYs6mVo3swm5P4HPPIU8LUOufQH0f8Te2K+fHCARHI0/wHduRIeOKIbPyBC9ip8ODznbCpFrWpzHpDPUtV+h4+hubBm8fBbfRo4llrC3O9E=
*/