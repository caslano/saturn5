/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_ITERATOR_RANGE_05062005_1224)
#define FUSION_ITERATOR_RANGE_05062005_1224

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/detail/access.hpp>
#include <boost/fusion/support/sequence_base.hpp>
#include <boost/fusion/support/category_of.hpp>
#include <boost/fusion/iterator/distance.hpp>
#include <boost/fusion/iterator/mpl/convert_iterator.hpp>
#include <boost/fusion/view/iterator_range/detail/begin_impl.hpp>
#include <boost/fusion/view/iterator_range/detail/end_impl.hpp>
#include <boost/fusion/view/iterator_range/detail/at_impl.hpp>
#include <boost/fusion/view/iterator_range/detail/size_impl.hpp>
#include <boost/fusion/view/iterator_range/detail/value_at_impl.hpp>
#include <boost/fusion/view/iterator_range/detail/is_segmented_impl.hpp>
#include <boost/fusion/view/iterator_range/detail/segments_impl.hpp>
#include <boost/fusion/adapted/mpl/mpl_iterator.hpp>
#include <boost/config.hpp>

#if defined (BOOST_MSVC)
#  pragma warning(push)
#  pragma warning (disable: 4512) // assignment operator could not be generated.
#endif

namespace boost { namespace fusion
{
    struct iterator_range_tag;
    struct fusion_sequence_tag;

    template <typename First, typename Last>
    struct iterator_range : sequence_base<iterator_range<First, Last> >
    {
        typedef typename convert_iterator<First>::type begin_type;
        typedef typename convert_iterator<Last>::type end_type;
        typedef iterator_range_tag fusion_tag;
        typedef fusion_sequence_tag tag; // this gets picked up by MPL
        typedef mpl::true_ is_view;

        typedef typename traits::category_of<begin_type>::type category;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        iterator_range(First const& in_first, Last const& in_last)
            : first(convert_iterator<First>::call(in_first))
            , last(convert_iterator<Last>::call(in_last)) {}

        begin_type first;
        end_type last;
    };
}}

#if defined (BOOST_MSVC)
#  pragma warning(pop)
#endif

#endif



/* iterator_range.hpp
yWXNxNfWOf4n8o6q42qoNxB1dJjUJyb9kfgm2nb8J7clT/WWPdV6P2lB+iDLn1h0Ze79Od0R357otUUdihZ0vp3UH6fb85Q9cHrr//e2v5zjnS7vJY1qAbPllfxcMsE38Xvk/7P3HOBRFVsPipSHKIpPAduKIqAhhI5AICGbRkiREIqAISQbEkkzmwQCoohURapKU2mKCEhVpCkoqIioCIqoqCi8JyI+EFF5+vT/77Sdcmfu3k02Zgm5fAQyd2buzJkzZ845c8rFTT9pVAcZ0ph+tpPgi2kKpJCZhDZmIOjiPsoG/yBE5fIAs4srRFZgMHN5MbJurPz1qXh8r+Z27HI7cNX5s7iIcAD0uxhz7WCem7zPJBy77lzmefhU5fjwl/PILkjTzpW362SaRhZd7sLGbzNkmC5ejlZrPlflOjJey9KTG2FhMbIswDp2TI2GoVVmOCda1FZF+q6HuxhFV8cjtwHtQSfjL8wQ2RH9X4R8LuolG2ne4f1jOqCeR5RLzQBUAy9aNpvtmS82+PNRacsO/2xEhavhXzb8p9Fs/YX/btKfHtqOixbefPRgf+G7d3gzDrFqnp+q6OfmE1S+Adfhr6ihtANV4FUTieU17MGRUeX5GRZdvGzrIeJ32dYDjkevFxZjMmLdDvXYwvoEGBHvPsLnUn1PEoLwcOT12gfBilkNXfj2Zfr1lOM3qqzIRE2evKa8hk93JvT1
*/