//
// Copyright 2017 Peter Dimov.
// Copyright 2019 Mateusz Loskot <mateusz at loskot dot net>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_DETAIL_MP11_HPP
#define BOOST_GIL_DETAIL_MP11_HPP

#include <boost/mp11.hpp>
#include <boost/mp11/mpl.hpp> // required by dynamic_image and boost::variant (?)

namespace boost { namespace gil { namespace detail {

template<typename L>
using mp_back = ::boost::mp11::mp_at_c<L, ::boost::mp11::mp_size<L>::value - 1>;

template<typename L>
using mp_pop_back = ::boost::mp11::mp_take_c<L, ::boost::mp11::mp_size<L>::value - 1>;


}}}  // namespace boost::gil::detail

#endif

/* mp11.hpp
gjru5uCakwRK8anf1LEm8kLVMVjP3FOAJyVCmRQm1xjTRgWmsX3RzJ52rou6WZ6HQTJqWDZfu97Y+va7693u3otvv/v+hx9/Cm7DoRz1fn191H+z377ZCDeSWgWYNu0agcZRw3TIAacLg9kqxqlo4LWpp3CN6pr1K1LzjXJzG5EDWOL6WMl30o0WLBDUdFUdg/tb1/91o1a0ZAHOItarFsGE6KJ3Jd9YtN6dHb2AbaEMiZulSQUrjDUXeXyizZriR1YAnr95vffDi70dPjFAas4oAmQ6PttROOm4yvWygFdrEvCCpoYu1jmY/JeWMk9j2tu35j9WOoyjwuzbVNPSNHUUMlcs0mSUH9jH+BUjvj/cWID9mqUPOXlqQPeL0F8wDKZ8BKCtrHXl1AlT6JMN3wR0sOguKnL26xtqIqeh6zQjjC3YtUIeDjTVURAIUK3RM0SxWuoYpQW2131pvULlw9Dk2xiGkqP0S0u8Hmeoz2Cri2AUZBHptUozbK/pXo7IKoXiSAeqSB8ZKz+PUo9AtpAPAVUkTLq4Yy0jTtPPOguafwIdzEeXGMZf1umJRaR1tS3X3Rsnmchuaf333XopncAyYnFoxYvY159/7R0Nzk7PLwcnVx9+7Z97EhBHPL6gDIKGM3KzkmjmOjLo
*/