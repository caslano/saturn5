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
bc9DXnQ/Lkbbr6y3t31FfeO3/TCXdWRaRNtnW9ef5nrcbGfHflXwuUF9az7b/of4fXE/Lx1/jHD388///X5f3P3iNJ4/mP8Wvy+TA+ern1lzwPato75bXvDnqzov7tI/LbHz1SkIZwQ8/b6M3cP0/8G7fU+/L2PC6fQuHnaPkl/aP73LTQunQ7Z6l3u8JV25o1z3/FY0UG66Nb8G6jvCkq7eLNczv1U+vb/Ve13SBdLcr3SbSdcRboG94eewP/wCngi/hBPgVpgN/wanw7/Dq+FX8HZYD9+BX8PP4DdwG/wH3A6/hT/B7+D+6LEddoffw77wB5gKd8CB8Cdru233brdJlnSpDfTXRGu7Kb/u3vkR017vN+HxardOxjkQpXtN5/9rYQp8Qz7934T94F/hMXAdzIJvwxK4Hl6jmPkLFTP/JsXMX6yY+XcpZv5Tipn/Dnwfvgc/gP+EdbAten0Iu8GPYArcDA+Fn8K+8HM4CH4BB8MvYbhdf1D9olwvvh+VLsq4zXCkc78Oqsx0nu2f6dP7L1iodFb7i8NJlwL7wCPgEXA4PAqOg6kat/3hFDhI4/YY5V+O1EuPvyj/fWCZ8j9K/dsP9pQdRxocKDuPQXAiPEb2HYPlk/84eCMcon4cCh+Vn6c18vP0Ckwz+0HvnSgj2rzlSOcxfzjSufdDjZnOsx8qEL0H4f2IM6ZBLekOhm/APnAdHA/fgrnwbTgLroe/gxvgLfAdeA98F66B78FauBH+DW6CLSjvA9gK1sH94IdQ/p70zoJ3GS7+nlZJryek15NwEHwKngpXw0z4NJwJn4Hl8Fm4GNbAavgn+AJ8Dr4Bn4f1cA38Eb4AO1H+y/As+AqcDV+FgXcr0tfv0zsK8L7auzXMlb7VpAv4AIW/gvfBEXA5zIH3w6nwQXgefAguhyvg8/BhuA4+qnl4Zfg60vsEeKvLdbRY5d4B02CVrpc74UXwLngtvBtWwCXwRniPZXzUKf/kyPGhGBoHw1Wwt2JnTIdPKWbFargEPg2Xw2fgY7AGvgj/pPnvec1/a+BHimHyrWKX7Gm0P2wNXwnFMNlDe/ja269C+hpzic4rDpM/sOGy3xohv2Dp8HQ4EhYqVkwZHC17rjHwdpgBq+U/bAUcB5+E4+FbcALcBH8D96DMidJvEuwJz4T94VkwDU6GY+Bv4RnwbDgDZkE/zIXXwjz4CJwOH4cF8Al4DqyBhfBVeC78ChbDr2EJ/BmWwr1pizLYGs6EB8Dz4cFwFuwHZ8MB8AJ4EpwDx8OL4Jmw3NAPXgrnwt/BS+Hv1f71Pr0DgOM0Lg401hsuMWRS4M2wF1yk++YtipFyKxwBb1O/VMIz4GJ4Mbxd8+0dsApWwQcUc2YVvEv9skTj5h74PVwKO6LXMtgZVsMD4X3wILgc9ob3wz7wAZgKH9R99GE4Ej4CT4WPWv3z7Wn6taMdPf3aZShdnyjpKpSud5R0tUpHu7K+sqdba41tYurXQDpkL+kXJV12jOmqlK53lHR1e3nrd4+Zjr1PlRslXUaM6SqUrneD6bSfJ/2SI+6bI8107L+p3Cjp0pSut3c6JhHtV2kfqwox1j1lms++0nxWr/nsa81n3+h6+iccCb+DY+F2zWc/aB7+Ed4Bf9L18jN8Dv4LvgQpuPx9A7r/NdO6Pknr+ubQmP9bwC5wT63vW8KecG84GraCGbA1nALbwOlwHzgH7gsvgfvB+TAZ3gr3h5WwLXwIHgCfgO3gU7ADfBd2hBthJ/g32Bn+CLvA5sYeFNwbHgSTYQocAHvAE+AhMB32hJPgofAs+Cvd79Bde1fsaakfDjPuJ+qHc3U/LYKHwhJ4FCyFx8AyOBTO1Hr0fN0=
*/