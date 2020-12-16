/*=============================================================================
    Copyright (c) 2001-2013 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_MOVE_01192013_2225)
#define FUSION_MOVE_01192013_2225

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

#include <utility> // for std::move

#if defined (BOOST_MSVC)
#  pragma warning(push)
#  pragma warning (disable: 4100) // unreferenced formal parameter
#endif

namespace boost { namespace fusion
{
    namespace detail
    {
        template <typename Seq1, typename Seq2>
        struct sequence_move
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
                *dest = std::move(*src);
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
        struct move
            : enable_if<mpl::and_<
                  traits::is_sequence<Seq1>,
                  traits::is_sequence<Seq2>
              > > {};
    }

    template <typename Seq1, typename Seq2>
    BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::move<Seq1, Seq2>::type
    move(Seq1&& src, Seq2& dest)
    {
        BOOST_STATIC_ASSERT(
            result_of::size<Seq1>::value <= result_of::size<Seq2>::value);

        detail::sequence_move<
            Seq1, Seq2>::
            call(fusion::begin(src), fusion::begin(dest));
    }
}}

#if defined (BOOST_MSVC)
#  pragma warning(pop)
#endif

#endif

/* move.hpp
Z2fpeWq21kcXwMfhHPgMvBDWwLnwJXgRXAsvhh/CS7QeKYeGcpeqH34HB8Dfw2PhPDgeXgbPhZfDEngFXADnw6XwSrgcXgVfgFfDD+ACuBleAz+F18JWtMF1cBysgBPgH9R+N8BseBOcBxfBa+EtsALeCne0YNy2SvK1aZ3kS0UmIIZ9dBmsbB3dPno+m2dVyKrPsQUl/QZkyVJsGauj+81cvdS0m14d4T9z3dLdY0O9Zen/hh31zvjR3LE0fnvqTsuwrV0Wu0/NYctit6+esMy0sfYva9jOunyZaWtduWzn7a1XLms8X5trlyXmb7NumWmHvX1Z4/ndbFMduz12SvV/l032mGrTLhv/DZ622dnVO2efvbU1ebdJ8g1AMpG5SBWyBtmM+PZJ8qUgw5BCpAJZhWxEfPvyf8gwpBCZh1Qja5GtSPJ+Sb7BSAaSj8xHliA1yGbEl8zvkXSkEFmIrEQ2Ir79k3w9kXTEjyxEViF1SJu26IuMadtkW970afo0fZo+TZ+mT9PH+7ML4/9N9RcXljZm/L9ePQL298PHTRg5YuTJ+O/LOG3MyJNHDrfa4HeTvX95IG0gwaSRY0ecFrK976a86gP/j4YFUy/IzZuWM7OwjP8O+gt4lZdVyYeYvz/9NyeOCeSRkzulbEph2KdAhVsalSM92AQx0vxm/PBxY0+bMPLk4ZH/7w/8f/D/xg0fof8O+ja82hLHsGszp03uYuOcbq2xj+LSKHH6Cbi8v9Mmd5GXnwCvMuP0FZDew9smd4eLr4DbqW/yGx5lx+EvYJDKyHfxF1BFGWmBMsxOiX422N6WzTqYbdlPZW3w8BWwotZeFg0Rc/ut6Olt4z7AxUfAndStPLJuRqvFUDdr3lUu/gFub48+wbzNiy7q+Uh7u1W6+Ado18K93cprI8qK0x68pod32/ld/APcZdhjRtYvATvwrR71qVF9HBNODHUyfKRs52BFdmA+4tRhXkkR1eLHdnvFyS52/UMMu4s3I8pOoO+O7eD0j7FuT/e6VkTWNYH+qz3E2z/GABd7/rvpv+zIesbZh+Hxv5ezHe8h/4pA/uZkH28s2YfbuYz/lu5tWFVrLyveGLJpDcwd/pbO9ltq3Gsi6pdI7NhesrdPJqOusoOrJm/fXwN5Bw40Bzsoa+xpw4ZnBQzjfNHtnpz2keb50dWBdi0qzs1T7EAPu7dU+K9jA+dxcyLtW6ul9+nq8zHIK/wje11A7yy8+mKU3v/oUB90ctNU569lnyk7Kn6pvwHfTA/b+2EutvfLjT5ZF7a9d94T47C5vjcB2/vQeNngotuD5JfyVli38P0mlntNSKf7d0KnwtZOnR4mP7+pkzmPx6HTQwnoFJqXmrdx6rSS/GpsOmluilOvRxLQK9RWi1z0epz8kt8O6xW+5uOJlfxYAjqFxnuKi239E8Yc/nbIrn3nxvvl/WPzMVDlosdT6FEV1iOxsd2sQ2zlp7jY9z9N+XXh8hMbx5Ux+jhY4lL+s8a1vT5UfuJj9tgY26Dnfk4d/mSMhbAOiY3Ph9vF5ttgu8pfp/MKryPPU37Gn03fBnklZTxMRrcx9/IjL/sHjUsjq/hs/j18+qif/QVF04pt9ugLZDc/rbnsMeELxrgOtmlRcVnB1LwIX0SLvOol25Jv3uO3FtuSv+i7bEsCOlW52JBUh21IZlJusI4rzLrkDCzGiYrSznaxw84Pj6XzZuYUqi3D/UuWap+MiPZJc7Hr2UFfD6NCRl17v2Pa9WTqmiW/kjwS05bh9PNJfzAJP7akz1adjPJL9Te/PQ+HnU+ufAR8pnH+EfKSca1tCvYJP8oitxh8A7TY/81NlrZX//jet/SPdMwK6og=
*/