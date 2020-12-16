// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2016-2018 Oracle and/or its affiliates.
// Contributed and/or modified by Vissarion Fisikopoulos, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_ENVELOPE_HPP
#define BOOST_GEOMETRY_STRATEGIES_ENVELOPE_HPP

#include <boost/mpl/assert.hpp>

namespace boost { namespace geometry
{


namespace strategy { namespace envelope { namespace services
{

/*!
\brief Traits class binding a default envelope strategy to a coordinate system
\ingroup util
\tparam Tag tag of geometry
\tparam CSTag tag of coordinate system
\tparam CalculationType \tparam_calculation
*/
template <typename Tag, typename CSTag, typename CalculationType = void>
struct default_strategy
{
    BOOST_MPL_ASSERT_MSG
        (
            false, NOT_IMPLEMENTED_FOR_THIS_TYPE
            , (types<Tag, CSTag>)
        );
};

}}} // namespace strategy::envelope::services


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_ENVELOPE_HPP


/* envelope.hpp
WAg8HjgMOAJYBBwJHA0cAywGjgOeApwIDAEnAUuBU4Bh4OnAMuA0YAQ4HTgDeC6wHDgTOAt4EbACeDFwLnA+sBJ4KXAhcBGwCrgYWAO8AlgHvBq4BHgdsB54A3AZ8CZgI3A58Gbg14ErgLcB7wB+C7gS+B3gXcB7gKuA9wMfAK4GrgE+BHwY+AhwLfBR4GPAdcAW4AbgE8Angdur0f7xvAW4VdyBzwKfB74I3AHcCXwF+CpwF/C3wN8DXwO2At8Avgl8CxgFvg18B/gecA9wL/AD4IfAfcD9wI+BB4CerzB6gRnATGAA2BmYDewKzAN2A/YA9gLmA/sC+wEHAIPAQcAC4BBgIfB44DDgCGARcCRwNHAMsBg4DngKcCIwBJwELAVOAYaBpwPLgNOAEeB04AzgucBy4EzgLOBFwArgxcC5wPnASuClwIXARcAq4GJgDfAKYB3wauAS4HXAeuANwGXAm4CNwOXAm4FfB64A3ga8A/gt4Ergd4B3Ae8BrgLeD3wAuBq4BvgQ8GHgI8C1wEeBjwHXAVuAG4BPAJ8EbgQ+BdwC3ArcDnwW+DzwReAO4E7gK8BXgbuAvwX+HvgasBX4BvBN4FvAKPBt4DvA94B7gHuBHwA/BO4D7gd+DDwA9Cxi9AIzgJnAALAzMBvYFZgH7AbsAewFzAf2BfYDDgAGgYOABcAhwELg8cBhwBHAIuBI4GjgGGAxcBzwFOBEYAg4CVgKnEKYavY3f37uwGVKv+k7eWVNPQrKmmYVBKaO+l0ZCT3mlw3dMTV30svzypr7DebDf1PHv7y3uvf8kqVvePZMveW7nj2kf2KrD861fy1rptjNFJsmp3l7Dz47Tc2PpDzwBJjv/A3J3QKy7Li3oC1+KPZqMqlydSVPQ+s+s+KShZS4b4p65SKfL8jqfU4oA2sekXvHYpr0V3/0m/CcZ8LHbkJMrWCUaWRY5vBqJV/5J2pa6dlXEsBiy6Vyh9WNhXwFubnrNvJNDcZlYzQDjnzN/kpwsCR5E69Q+NajtGMR7NHiYW3xz2Dt5WgP43O+4fd69tL1uJs25c3/aFM8vrfWu3dzeNMzebunDGqLJ8Q0L3DUM/Ge11/kFX57vGc2PcZ7zifc0CnDQ0vL7fGekYu8h+SUa3rF63t7WKYxiHVZFnQ8v/AFkpj+XcBLO5Q+o0/H/1QnonqLaP8LkH0625v9P6QfsvWj4Kh1eg6S0zb/h1leD2dpm38PPVHzIrf9eHIoh6WE9pIbK431utybcxZnMOGyjKB2tMjxHO1IEV8qIpnuXkM+uQ5Ip+GqhRpVOs+XSoRJV79Ul2cgqiuAW6S3o75+SMWIZio9oIVUC7cFpL4KVX0NCqC+rgmgvt7J5Dramanr6PlMXUevZibX0Yvkxjx41qBL1l+fQCXvN7jtkLest2+MKnV3OzhugClYSBWM8xgdbtkNYX2WuyGcloWC3Z+FgnVHwdr8umB/80txwK65Ik+xAwPCMxLnrld05l4pvp35Onja2OR/meI5q+A5P6ogxFWQ6nINjjeWfqsHNSu9hfFNzc8Ql+Y2isgsoMhpzRms5P7Z2LNE7o4RFsvYHpnGc5Dvq06z6OM9T5vpdXDZ6/fxD5dY3QQRUdfEHE/BHNykmhKb0XaL4p4W8VOFiztveKghxe4igtxVvHm+1/NJWPAp8t90fsr8R5jLZ95GiN+GnAL3XnsJiqZvRo/3PJMoOJh3NV9yFa3CFK0yddHCeI1ctHIuWieiFvPSv8ZPUEDT/k1HSLQ5pQJRWV7IP1ZNHv94a8bxj69mQmwyKlaprOUyj1XbqllbKZNWzM8/Hqj2ij5jsZKs6Kyj2+I0AsVyoz/D0yfjMbk=
*/