//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_DETAIL_STRING_HPP
#define BOOST_BEAST_DETAIL_STRING_HPP

#include <boost/beast/core/string_type.hpp>

namespace boost {
namespace beast {

namespace detail {

// Pulling in the UDL directly breaks in some places on MSVC,
// so introduce a namespace for this purprose.
namespace string_literals {

inline
string_view
operator"" _sv(char const* p, std::size_t n)
{
    return string_view{p, n};
}

} // string_literals

inline
char
ascii_tolower(char c)
{
    return ((static_cast<unsigned>(c) - 65U) < 26) ?
        c + 'a' - 'A' : c;
}
} // detail
} // beast
} // boost

#endif

/* string.hpp
KJeeDwP2Ay4DJhvpmM8RwLHAo5WnnMeQ/+XAPYDHA+cCTwDOZ7pi+kuBJwPLjXCWp0Bx/zZwIsuzHXAOy7OE/JWzXEuBscBKfp/rBqbTPxp4CHAnYAVwvBHO+9Qp7pHmHu4G7uNe5X0IMP8c8j2d3+/OBsKpOcCFwH14VtoMfre7N22c5wKXA/OAlwPzgXcCC4CrgQuBj9P/FHA/4DcM/wm4P3AHF/ozsB9wIcu9THFPMfByyiccWMZyn4h2YuAKYG/6+wBPA44AngEcC1wJLASeDSyifwn9FcBzgMcBzwVeCDyP7S9XcQ+uqR13A07h/S9kO74YOAh4CTAVeClwJPAK4M7AK9mur2K+6XC1zDeE+QYDBzDfr5SHr6+BXYCQlS5PHdPl2JRnP5envcwDJhhyBe4CnA/cFZjPchwInEY/8+V+VPBrk29/5psMjAamANOBA4AZwEHAnYADeb9BpnwLmO9km3x3Zb4TgL2AuwFHAbOAY4w0lN8k4AT6vfmuaaG8XZlvN5Y3lOXdjuUNZ3nDWF742R+5DxO4l01/3MT++L3ylHczzwT4gf3lZ46LPypPeZv4vftPwGzGe+/j5n2KbO6zgOVfyPIVs/4WA3dneA5wETAXWATMI10B6Xgf7jVEm7C5zxDeZyjlM5zyGQEcz/AsYBpwKnAYcC/S7UM63od7+rDvwuY+03if3Vm/e7J+c4C7MXwyMBuYDdwDmEu6PNLxPtw7Z89PD94nkvz0JD8x5CeS/ESRn2jy05P8xOj2Bbee47JN+3qP92ngOPM++fqQfH3EdvsB7wu/fi7WMd9dbZ6L65jvS8A0YD0wnf5M+jl+cM8Txg2b8eNIjotHAYOAR5uep5FMl27zPC1m+17M595BwIHAEmAqsJTP1YNMthxzmd89zM9sy/E05RkfTwfuCDwTOAR4FvvDStp4vByYCzwHOMtIz+fn+XzuXMDnzYXAQ4AXAc8CXgxcBbwEeB3zuQV4GfB2+sk39+lAJjZ8r3F5nn+Pcdx+kv3ucY47TwDLGK7fl5jf4Tb53cf8VvP95iHW3/3M90FgKcOZH/c32Od3G/O7nfndxfzqmN+dzA/h7Cdc9wf2tekno/h8GQPsBhwL7A7MBEYAxwGjgLvTLsgEvv9NAyYwnPfhGjzKanOfFLanAcxnR2AMMJX5DQQOpX8EcLDi8wS4E8N5H66L24+X0H8lv1kcT2YDJxrxwD2A+3C8nAucS7o8hs9juJbbO873ied9+vA+CbxPX95nB94nETiXdHkMn8dwzQ/vs9jmPmN4n7HMfyeOj5nMfxzHrZ2BeaSbx/D5DNf8vOvMz++shz9on0Xxfi7yE8T7BQPnki6P4fMYzvGS61v27yWvcVx7HRgL3MDx8S3K8W2gQfumvJfAz3wz9foQZMh8uwDTmO9bbF9vs129A4yj35s+nekTbdJvZPoGPs/fpzzgZ7/kGoeD/pHG9MOof6RT/xjOdj0COIzhut6ZX7ZNfRzM98mlLr7fA5OA1XweHMb+vww4muFZDJ/EcJYbzLFf2pS7luW+huP7Kpb7Rpb3BvY/+HV+ucxvlE1+z7B+1wKTgc8DjXyf4/vws8DhDOcZzZzLlTakGnzOaL6D48xd1Dfv5nvWPcBxwHuBhcAH+Vx4lGcurQEeDnwSuBL4NPAS4FqevfQsz25+Hngb8AXgOuCLwFeALwHXA18GfgR8FfgZ8DXgl8A3gI3A9ZRLkuJcJjBWSf+U3zHkY19lase0m7TAph1eC7kkAq/j8+d69u+bgGld2meLeEUbbBVteK9z7RXF7db+85u6bOwY+0XpG/1sGG2zM5yagGZ7RvM3/jPOcjp947Y9z+mWje0=
*/