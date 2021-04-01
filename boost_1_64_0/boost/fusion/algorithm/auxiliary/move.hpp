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
h9/I1U39koRiJ+uMKus4fxJogRtR9m1nmP9gI0wd/wgntITamisbstCsrmusxd0fIs52QrGGlMi9oZnk421Etri31fFHfI41WZzPz83JJqKOA+yqDp1vXpFFOsPnQaLBvt1ZLIpcVKhFtIKcC7//QgWWXezdGeaFu1OA0vrhJmcy5J8nFB0A9BEb3IClhIM+fEfcy96zI1HVlSsy/WdPI/bj7rSBgVDJ9dg05FFkuNXlu2JGuTlsyS2g2DVFgUDM08GiKUv6CoJhRgF+0MWmrGsb8CTzmM/MaLCf0LrfJwl7jRBqP5P8dIgdeg3iwzgqW+joWcHJ5nDQinY8gXj1SIb+JHH/krxRcndVcy3CbkmSS8yBEqZqsfBqxdaZLSJ4dqnEznxCMLYWvgBLt/AtA6EhBVXQsjtmbU05JaSVM/8vH0FFjuFXO5pk1mvhZ+IVWOfIv1nMiwcliwLflUlLY+T2EG7nzQvK8WQnooeqmQxTqKfjj1oNM+K73xQhCYpBbPODheAxjX5zaWQ5ZpAQbhc8O6fU6+imTBDRaB6vVd8Ap2HPSvMa7xCGcg==
*/