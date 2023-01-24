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
ux11S9KsN2fiZ285tD3HpdV5HHukELp9Rz8ircSbOKlzJ6W7lFrl5r6ytV62NjI8RuF9g6UqzGARKiyXHnkKq3Rl+SJJWX7sJRqxXI765auRGjB+qd5IcRLxF8pXgTnyXrOS3xyRSsGIaK04B2b02DJP+BrGKfheoMT/6iJ+AWpFLppNsUnmoroFFv6Y2NyLu0z11Oj1TNPr8cCXMld4JCMPE5u7awezOV2jOP/2Tlh9cSpEBsVLnv6QoUJspI1X5XBvilsI0PKQqvbqkCLvEIbw+OvOpxPyWAGwxXkmWrO+7HkwV1yREqtyGFb1ePSGDOKynAfs28l4KXNV3PT7UWEMLTkM/XBpMwlzZZWVjZhU8IMvGRLoQXodvAfDJMh9FzYnfLwEV/2iyCwLUoJBW262Xl6ifEsy9VIvc30XZe7ekpJQJrOLMqWUsjdW5htm1Fe3iW1OqoEyUo0v+243/i1344VFuJNQ8EDEFv4PR+E41ScIZ/IK9bt0zhnAKEfiXUBBT6QizcWJinQqeoGKJUBFF0fQ9PrSoGIJUJEL62RENawR2fTUF0zGWRbhikAvI2h2432uyFxz/MsKEWoB9owbgB312INqVfJUlvVH/Mqu2CNY+SUzK35LKDaNfaPx8xn6dGdXKGtASl09gVE3C9QvTiIBGtVJTRjzyNdOCQioTbTfUQgbV8QohOj2i0pB9I5Z3UsPJNDvrVRu
*/