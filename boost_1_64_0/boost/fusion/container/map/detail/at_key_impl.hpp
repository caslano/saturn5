/*=============================================================================
    Copyright (c) 2001-2013 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_MAP_DETAIL_AT_KEY_IMPL_02042013_0821)
#define BOOST_FUSION_MAP_DETAIL_AT_KEY_IMPL_02042013_0821

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/detail/access.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/utility/declval.hpp>

namespace boost { namespace fusion
{
    struct map_tag;

    namespace extension
    {
        template <typename Tag>
        struct at_key_impl;

        template <>
        struct at_key_impl<map_tag>
        {
            template <typename Sequence, typename Key>
            struct apply
            {
                typedef
                    decltype(boost::declval<Sequence>().get(mpl::identity<Key>()))
                type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& m)
                {
                    return m.get(mpl::identity<Key>());
                }
            };

            template <typename Sequence, typename Key>
            struct apply<Sequence const, Key>
            {
                typedef
                    decltype(boost::declval<Sequence const>().get(mpl::identity<Key>()))
                type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence const& m)
                {
                    return m.get(mpl::identity<Key>());
                }
            };
        };
    }
}}

#endif

/* at_key_impl.hpp
Kul3U7edKSX9XpJ+iKTfW9Lvo1re0F4vfZT0W0n6rSX9Nqrlw9rrp3+PpB8h6Y+T9McjfZza9rlg7W/hsH4fC2X2r+CgbwVHfSqU1p9CuftS4D6vuu+E6+43Qb/PBG1/CbZ9JSj3Py9y/9Lbj/udhChCDmEX4QLBuwH9XhDiCSsIewkXCN4NGU9IJ6whHG7ougfqGlyDa3ANrsE1uAbX4Bpcg2twDX/W8Ic//x8TGZ2YGHtTnv+vyL1/ub9i7T+4HZrb46OPD9ed2pivC0gGI6NjY5X0I829EJjfTZpevmcXL2HBdTw76Pj66B//TOHf/dnBmUOV8ZEPTdkYW5C8v32Dd+ftOXG8k94zf3/8s4b/a88OPh9jXs91hvz+0Jw5HXIeurxizRU/0/U9I7jHTb4n8v3JqaDtA7emPOPig/XkOmxz9MWecj02FOvjGPTD++R6/QJshI/JdfoNcp3+VfSXZ/GaYaFcj/8aA/AXuR7vSX7uRB9sjY2xDbbGtph+Hc+62F7rm5FeUe9Zlz/sORfrMy438HxLbnrFP/wZl4PpFW/acy7X+4yLzvMtf7tnW/5fnmvZ1ch1ndY1uAbX4Bpcg2v4fxr+nPP/mJty/l/Bwfn/zMqcW+M0VM7/o5o6Ov+XFpqu83/X+f/f9Pz/XIx5vd1aad7Lr9e8+Pi4dHfT/rcDr+/8/5SHfE/k+8P5P+/PY516qM//tX1VNJfrAO3RF++S6wBDpF3WPXI9IF6uA2RIu73Zcj1gmbTfWyPXBXbJdYEj0rfFabku8J1cF6hM5gKwNrbAptgSu8n1gRHYCqPkOkGSXCeYi0Zci22lr5ogPIDt8Ay2xy+wA17DLlhVeXcz1sXu2AzvwnbYC4MxBAdjbxyLfTAV++JCHIiP4yDciKG4EwfjfhyCJ3EofoMjpC+bkehFfRuFt+NobIJ3YxsMx+44BkfiWEzEezAbI3ANjpO+QKLxdZyA72IMfoSxeAHjUNnxT0RfnIRGnIz/wEQciEl4NyZjLKbgDDThCrwPt2EqHsSZ+D4+iJ9gFv++wll4BWdjRb6Lc7AmZmMjnIuBOB+74ALsiwtxBC7CKFyMmbgE5+JSXIvLcDcuxwP4EL6HD+NZfAS/xBV4GR9Fpd++x9AbH8cGuApb4mrshGuwN67FCFyHCfgkzsJcXIVP4WZcjy/gBszHjXgUN+EZ3Ixf4Ba8hHno7kmfVVgdt2F93I4B+Cx2wOdwMO7AsbgTU/F5XIgv4OO4CzfibtyJL+J+fBnfwVfwFL6K/8a9+D3uw2u4H6t68UwH+mM+dsfXcQAewNH4T4zBg2jCN/ABfBMX4iFcj4fxFXwLD+HbeALfwX/hEfwGj+Kv+C56sT96Dw1YgJ3xfeyDx3A4HsdI/BAT8TROw7Nocl0fvGnXB13XBl3XBsu6Nhja3HVt0DW4hr/r8Ief/09ISIlMmXzD5//13KrWKOBExFj3Fs7PlefEUmLTiJhsm68N/NDQzdrfsL9cG7DsmTwJfTh5KapjPufpNWBo5ES6Gk5MiJ6QGFeOZ9+4HsA5xG2a9w4MI9SUZ1reUv7wNccdmcZTqnHJ7dq6Sby+DqM1EG9JnwL+5n7EWVLGyTM5jCMqSb+1pL+8gsSA/uiFh1gvpuL0zQ8hc5XDnPZKx2UKISLWe9caWeY03EmzYo3YeixPlBPiUlPdpN/1XFxlztsEyavl2dL0RLC+v2B7QEk/zLU1/bUnxcqjk9IXufTZrOqjPxjP1JE+wG3WdeYtsq7dZV2jUlZDfVVZ6WK8PH3cK2W8x8++jGHXWUZV//XFr5mQ8f46ZTdqyq7dpuEe1r4vOcdmwOdIr6A4v4kpyZPSpkabyrw=
*/