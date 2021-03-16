/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SEGMENTED_ITERATOR_EQUAL_TO_HPP_INCLUDED)
#define BOOST_FUSION_SEGMENTED_ITERATOR_EQUAL_TO_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/fusion/iterator/equal_to.hpp>

namespace boost { namespace fusion
{
    struct nil_;

    namespace detail
    {
        template <typename Stack1, typename Stack2>
        struct segmented_equal_to
          : mpl::and_<
                segmented_equal_to<
                    typename Stack1::cdr_type,
                    typename Stack2::cdr_type
                >
              , result_of::equal_to<
                    typename Stack1::car_type::begin_type,
                    typename Stack2::car_type::begin_type
                >
            >
        {};

        template <>
        struct segmented_equal_to<fusion::nil_, fusion::nil_>
          : mpl::true_
        {};
    }
}}

#endif

/* segmented_equal_to.hpp
crkoUhEVP8RVROcIRRRGtvsXWU0bVsV0yUGBushWRYm4d5MqCtR0UkdwfUgkVUyPrQ4ddIV7TXR1cL0oEi8fxFLHBLlcEkUdi89MHXOP/kZ1WLY6LrPVIQs3Va6l1VGg9pFK+pAqnqOjCaliJh37YqtEB2/t6eiOWUPYShj/xhxDJT/J5WgqaX+GKplTr5LJZ6KSByQHBbJUgVWySNzrg1RSoIY5hqpXSCWtSBUVdHxJxzArplp0FAs8S6KrhWs=
*/