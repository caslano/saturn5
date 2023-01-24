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
iYf6ZAW+75jWKmzO33mqeX3txkjzeiJsXp+IhDMg5pp6SQzO7Ux31s0ppV4xw8vbnOE3Ws5wZqQZvvxBbYbdZ+AMzxYzPEcgCg/dhMO0gfWOB+Z6c64vKXSuN9/QnrnOd7Q51zPuw/m9VzzU8x/QcHUrc+346lRzfdkNkeb6cNhcL4wAw3PUL6JwnmGGV/zTGXZGmuFvKrUZ/skRMsNloTNcFnmG77i+PTMc6NXmDKd6cVY7ekEvoBzfLV6DXrbkoWB+63cY5zfi+VfYMkw80NulTMVmaFQs8j63u5UFulCAh4spuT59nHML2zPO6F7EQHhwkPpdzeBSHNS+6S15HcPR/uMXxqNds2OrFwxPPfTBEnFgQVvlULxijDA4W3V/OPaVD0DMki/jaWc9C5Iecv+B7F4ufZupX4adQOD6mCQ1QaDgNUu5BVJlWhM8fUzSHYxje4jYRZ5GmBblMarli1Ixm1EQzpB0pjPzfNgtH/YGr60NvCf3WfQsX8yv337HZBsFG8c1KwlE5/p6a4vzw9j2HPfFPckoBJyCih1zbyY7d5A83iNTcZEGlxFj2n8GPfu2fuZfuP1Ue/3qsf/7efXTyaT/2/PqULm21//sGXJeOdVv5rZ2Xs0b0x7IT+jR5g6/eArO7QDxUH8herfvlFbndd/WU83rn9f+7/O64O//43l94n5tXp/vETKvmWpVeWvzOuDa9szr293a
*/