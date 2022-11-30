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
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
*/