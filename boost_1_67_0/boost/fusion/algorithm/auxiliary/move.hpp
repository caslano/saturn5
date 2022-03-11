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