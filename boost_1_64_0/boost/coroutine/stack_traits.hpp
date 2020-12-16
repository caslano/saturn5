
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COROUTINES_STACK_TRAITS_H
#define BOOST_COROUTINES_STACK_TRAITS_H

#include <cstddef>

#include <boost/config.hpp>

#include <boost/coroutine/detail/config.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace coroutines {

struct BOOST_COROUTINES_DECL stack_traits
{
    static bool is_unbounded() BOOST_NOEXCEPT;

    static std::size_t page_size() BOOST_NOEXCEPT;

    static std::size_t default_size() BOOST_NOEXCEPT;

    static std::size_t minimum_size() BOOST_NOEXCEPT;

    static std::size_t maximum_size() BOOST_NOEXCEPT;
};

}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_COROUTINES_STACK_TRAITS_H

/* stack_traits.hpp
ThLknQmBt+L4u63Us+TvUuZIfUH+PsyY07tL+2OCoV6cTi5n3JXPle1TPFaYLV9XMEfL12cZ0/J1JWBavq5iHPPVztgXeQxp3GpQw5S8fFn0XK5QH+21ta8RFp2hCs6cfEPj8FRUzkoTx0qXzkby9R2D0d4AJe/V7zVWrhlKJLd3NvcO8f6Q09X31sk5iqiP/IGaLyMBfPlpHOVdkmuVvBgtpGldF+NWAzC2v544teUl0b/0VZiHjPR/gRwpR6vrs8b7pzau+kXGGmJ8xhjXEG9cF+O4J30T4Q7D9VdMI+ZgGjcrMrAPf2I74mHfhJjfN93iy8W+ieJp9zr99Ytfr9M4fr/9m3Xsb9VbDYQ3wghPLg+W6uZBhVKZX2xrT/t1xukEbp3mTqLXP5rvumHWneAkIuj1Nu6fgvoR3fzV4oC5fP0dMNC7pH8X43H527w7DGNV8rwC36l7uG/KytM/GNfy9E/AtDz9m3EtT6xPmR8ndQK28B/u/2xNJBUhefovY1IL0J7nrWfMDFHrXHZIp0SpLIS24vnmhTaech66PuDIyq7Tw8NDDvcDnCeZ45sysj3IPkd06ZfKcpAfj/Lc0plc6lOK1A1qfcp/1DHe1w4xuqnbjrK3f8d2ytEI3d0d6d6wDe5HZvFazdtMY09TGX/OW6rNIx9Juk2utvZQhmi7gz6i3Zt7w7VNjeP3DQcsVTjB+Ocx620binmO87j11qZn4+QSW5vWOVi3alqtfj/IzstaXT8K9Anvixl99tCOzNDILtf549q7j+M9/wODuHD/j+MG9hyM0Z+wHvdZzI4AvEW2HuPytV+7DdRvulGZY6k8Htdo+eAypOkcEsavSzplTOfQiBen8xQsTzRXASxcI2c7Q10ivojxrH2ixYBr+0BHMS7pQ/0fzfablfaxjGelvRRwLe1ljEvaLdwjtPZcyndG+5OHq7a8cj30R33dnbysJXgn4fXlpQBvtX2VyGWP1r6e5uXJ22fZuNFshvb0Dm8c6hscYb8AcL9gPe4DJwNHjsL3ZECWymN7kn2QpTovXFNdy3YR58+leTxzVHkg61mJ7vOaLOF0sy3Mlt5G5qjp4btuCW9a58G+2Wb7LY6TVO4hbSHudFZZW7fbcryvvhxtxPlHY7s06z8mWit+G21ak4pvn041rYH1vk95s9iYYoPrw3VMp5shq0eAwQkO2N6IzmNnOPCO+PxozZSWD/J16FuU/FBBwQfjpQciHr/PtjMzL1z1oJeT1ofrkK7sp2TI4e5/32U3p+Gg7M9br72PaRQEYwaVQx8dsG3yy457EPUGHRjO1+C5cBjvXkxcCvfOPK8+QMJyG4Z7u4c2bslt3D6Y29Tvvlvnczyj+ERnLe9dlDP2lLao/eVZ8913dnjHhpGhXm0+GnNwPvqC9TFuzFTeQiK8XBDfPFLWl3e68FydFlMn3fd/3NZHJBbf8p9QOWwlXv6VO72wd1xaH+PhvcE965N1cZrCxI/BpOWZkrlPucAO2G18mP+E6eAd94rV01gZ5iCncpixrXY/jP3dh1xKOY7frJWc3mqq3mJ/Gw2VZxtOOI7Wy7V/+2nr7f7oYfOoH+S7hC/isCNMWAu+Jqx9Vwuxj+AXONuGsr90vdU5xWiTewtJHVUKxXrdhFtjgTivJJzWo5I4HWkbobDBoYGTd9kL1uYj5b/XC33E2bNxW79LZsub18Y/u70yd4CtZ6YfjIPPkbzygrMyF0Ec5yKvCeJye5F8vI7HMZl5gXHkG/7H3nnAR1HlcfzNDEivCkoRkS41jU4QUoBACCEN0MCabDbJmmSTbAlFFD2KikpRkSaIKAIqimc7EQtgpSiIAoooHIKIiICo2PA=
*/