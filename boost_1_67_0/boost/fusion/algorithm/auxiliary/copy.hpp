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