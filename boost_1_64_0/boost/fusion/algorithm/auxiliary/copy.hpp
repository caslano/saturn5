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
10hQyv8G3NFZoSUOwIbz8TGEdhTImKcXA86xlFGWQPAyd4Qg3LR0SpD7QDRmALVyD6nHKwKXr29a8gWlOnBnSHBhrQYa5SDZPzqEQzxq9DAsI2/coWJDy0H8cgNTn6l2n4sMSBmP3Qoc5vmLUA2ppRw6RiiiH7XEBUj5Rxwt4WvS3Pz+j/7hZNgsh7yJeGdvpMOOfnyI0YdHWBngzGOEHr3gX3gzmL+2v/KI/tRmcSrUZmfWLsFD8g2+yzc2B+SkPiQBIsltOvlTN3wnBgtvjBD9sfF4LXfYLQrGz4j0sqz1OkpEMWxb0ZixyGu6rLnAxy6xLTZndscOOaD26mh1Gn2jo7A1nLT2WtrT6KMQuX7WwyHPlrChykHfsQxHMYc7X3kBa/LvB8KSQv7aZDV+XEGcxjFvVGUfkqFoXYsPpp74dDzLIuT3synP+7K25p7yOc8G1eg64zR/83BL+phwZukT3WUO1JUc0MsaGPZl5on//iKMgo3IXh/ch1CgqE3nYxg0JkiwLE/fY0FE3GRgGq5HvlR4WQDAbOF7xEZG7FHb270dQ14y0l4xhg==
*/