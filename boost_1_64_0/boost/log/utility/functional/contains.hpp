/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   contains.hpp
 * \author Andrey Semashev
 * \date   30.03.2008
 *
 * This header contains a predicate for checking if the provided string contains a substring.
 */

#ifndef BOOST_LOG_UTILITY_FUNCTIONAL_CONTAINS_HPP_INCLUDED_
#define BOOST_LOG_UTILITY_FUNCTIONAL_CONTAINS_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

//! The \c contains functor
struct contains_fun
{
    typedef bool result_type;

    template< typename T, typename U >
    bool operator() (T const& left, U const& right) const
    {
        typedef typename T::const_iterator left_iterator;
        typedef typename U::const_iterator right_iterator;

        typename U::size_type const right_size = right.size();
        if (left.size() >= right_size)
        {
            const left_iterator search_end = left.end() - right_size + 1;
            const right_iterator right_end = right.end();
            for (left_iterator it = left.begin(); it != search_end; ++it)
            {
                left_iterator left_it = it;
                right_iterator right_it = right.begin();
                for (; right_it != right_end; ++left_it, ++right_it)
                {
                    if (*left_it != *right_it)
                        break;
                }
                if (right_it == right_end)
                    return true;
            }
        }

        return false;
    }
};

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_UTILITY_FUNCTIONAL_CONTAINS_HPP_INCLUDED_

/* contains.hpp
YvXN0TZJ9E5FvyR6p8JrAa/7s0fN/Nsb37tb8O96yEsTdEzksvwrw2szXixKNjijm0zXsFe43AaHv7TCFuexzx0RsMULScbnoQ4k0DXT90nG56EiFmr2fNoqZmFLpmOKfzIdUyoWav620QxfvJRA8cWfkii+OJpA8cVfkuidilu8zMAj4JAtLO9UxKfQcScVeXbxPuciPu5UXrCKVzybSLHFI4l03DmbbLyX8V6y8Z2K87x8uXJNTXsZ1wxs810yHXO6lmkyC62wxV7U3y6MORsSjbHFm8l0LljDy/E/8keO91SLvjIwlY4Tw1NpX1EXc5scOWoVr9iSROMV+1KM8UVpEu0rp1I0fCHuf/Dy5SMlNd3RvphC+//vkecn7utxmcqRaWYY4yFWH+EOUgrFGPcl0bXp0ykUY7Rbwuvx3Du1iVk0T6Nrny7I8xH3Kbjc4Of2mWGMg2jXJwWM4ZlA7+D6pxlgDHx3iRQozRRs+Np0ijEexbyLQL8kMa6yVKt7khXGeDGV3tM+jrx7BHnlXJ7yXA9VCTLFF3+dTuu4NpXii3en0zGvHPOJcZebWj2OPu3EFw4LfLE/zRhfbEszvl8RvUyTXVIbfPFmGu2/l9IMvv/kkhtphS/WptBYxXbG05f7UBprP/23S1IovtiSRvFFFubzFPSLXK7pF6bKiun9inkoL0hYMyxLo/cwN3B5/lUba3MW6vMZtJ/9dQbFGNc0Paum1bQGOzzD4PvnM+g5lMgVmsy7appvCmbQs1DLZ9CYxUouU6lymK2/YmdQfDETeeLZvCtclv+xeXxOaW6F12bSef7iTIovEu/jc8qxAVYxixj0l0phnu+cQs8l9MIyCsg8P2wmwxduOLTqPq3db9cGX0ycSds+fSad68NWanK/sIpbDME6fCrM9V2R11hR3fBF1EyKL/K0co6nWMUtjqQbnPNLp354xiWv5nN+6dS37zOQWf9+LvPYJzXFLXqn07hFdDqNW6Rymcox0ztEDdLpXkQX5E0UvwvMZfk/H6EGhJrqtjKD1nc98rzEdd4qJq/B8e+sMMUnM2i84ly6cbzi1Ay6TlIyjDHFslWaDU9YYYqgDIqVG2VQTHGLy1OO7zLDFO/OoJjih3SKKV6bQefXn9Lp/lDMam6TEw1rE7MozqRnG0oy6Rr2Apfb4PlPrWIWL82kuKICeZ7CePM2ttdcqOVUwTZfIT+DfGeo2Rpum+e31BSzuJVB71h4Z1L7rOQyledXmmGKKtTdVxhnnkDeCNlb6iRgiqtY7lRx/Odl+J+08TNQVnsEU2bRvpIwi9oj8QE+/p94wwpT7EMfqRAwxUlsixLIN1k8M5hO+8q7mcb3Kyp5+fKJtTVhiq8yKab4Hnl+4r7eWm6PEwVmmGI7q4/wfYlMiik2sLoI5wYz6fxcxsuUT35aG0zRLYuudQZmUUzRbB2TG3zymBmmeBnt+oSAKUJm0PX2PVkUU+yZZRy3+DCNYop9s7S4hfj9g3Va3bNVbx9Y51l882oWteE55IWJ63uXzKEW35ZFbOFhUNetsyi2+DyN2vKpWTR2EbOel/3CqZpiF8ezjLHFwSzjOxZ7ueyAF1bhgXY/62/LfpxF/42ELxhPOLf1oKZztBW2qMiksYsjjKcvd0MWjV2UZlJscSCLYouFmfSOxQaun/JCdzNcsSqLrhceQd5Ecf3PZQWe2qU6wi2/sfZNNll3wcsG3396iLffqUxcd9U3l3k6m46tr2UbfP/JJbNVbda2Zdl0bfsQkyt8/4nLVU4Fm629srPpWahZ2fQsVI+H+bxyWopagTf36kHkwtwfc2jdPzNozxNcbijIHeecWSTT2MWMTBq7GJrpvoc=
*/