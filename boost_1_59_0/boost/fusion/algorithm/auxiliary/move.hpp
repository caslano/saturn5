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
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
*/