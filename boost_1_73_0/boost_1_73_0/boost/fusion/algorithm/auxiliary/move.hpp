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
VaeweaE0qj3y6AJdrOMdF8yfPgQMRkYsPIm39GBPS+SmDkrrsA3DwO6uqIMCmvAGN2EaVbWyv7D6WEo1SKGhFwjLd1HaJoUQtiATusOsi+MCJlU3WbRTVGlnGIxy6iNMwaZgi+UUNbZWjkZWUWHNyXcT1feDZ9Nh+X7fCn/vTKwyeWUdJJmyPi9wD9ij6zLKKjC5cEVZ0TjV+sAaWs+iTE727It1KN9hPMY6lHcnYI8iaK0ft0uMYZcXbo8FlZY/n+UU45PFYdK1hE57EGb1Jnd4dLbxI2ktM+VWbCgbaV7vOGx7b0bA7vEEDRRdDKeoFm24tKsCRlbn3pTA2IfGRi+y5YsND6h9kWeVYUsTb1un17XRvuZnlyGIrMPcWU6a2D3SHukMw+NGYvbIx55eIWkK1nsUL0nzJ0NJPCat2h2NtNpEv7tIqaB3jDUboXBX0ZnsMK9zTAsLOsdsVJjQKHxXkUVGWbv7PKm0wphYVpQXjVChdKJoDhMVVYWJigphMDUV3cjVc65gdBfXsO6oqBLSlhQj60EoG2KsC04uuXYWL6YoV1c+i6u6VNwVvMlq86x0OVdUwKz3E4BSy1tsAt7e4QK4RPZ4qmZTmmF5DRu4UOJ4OQPV0s6glbZ6s7KJI2H57mT9BVyt4F3m
*/