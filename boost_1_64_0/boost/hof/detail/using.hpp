/*=============================================================================
    Copyright (c) 2016 Paul Fultz II
    using.hpp
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_USING_HPP
#define BOOST_HOF_GUARD_USING_HPP

#include <boost/hof/config.hpp>

#if BOOST_HOF_HAS_TEMPLATE_ALIAS
#define BOOST_HOF_USING(name, ...) using name = __VA_ARGS__
#define BOOST_HOF_USING_TYPENAME(name, ...) using name = typename __VA_ARGS__
#else
#define BOOST_HOF_USING(name, ...) struct name : std::enable_if<true, __VA_ARGS__>::type {}
#define BOOST_HOF_USING_TYPENAME(name, ...) struct name : __VA_ARGS__ {}
#endif

#endif

/* using.hpp
2/7PM9WOV+jxTwJI08NMcmnvdv5cqpicx7SFIaiFmR0m4ZRu4KW9oxSJ9Fp8Z2CzevfN+iQe+XDpldVI5Cxh1XT9S9wWf1jFU0vPJ5HFjxtRwGja1XKkKU2s8UaF65/z18a+GWbKm5vMOlUfO2LHsFwbPJ3/n3UorYlvEcBSm2kMzBnRtU9HEHUyrn5BeIFHLUUJvXZb4ex03MCvozKWGuchutb4Hi/OIqxDhp1KyfMPMVBU36Bqg849TmTpcZE0BkrUjP8zUX5Ki9+Go2HNtCyrAfY8gZTBSmHvLrKQ9/kNxU3WHLxa5fQyW0IsD+zHRQreMgEBHtLibn9xTyEbKIZhammHBZib2WslJCmBOIbASyZEKYlePIr1E/w5aXZ2QxLZhS1Gv7+vzPyEylDM4IRAU9F3Kbzn0HlhH2P0hgen8mxN5lNctKhy1Veaf4i/BHgCchIheStdJWn9YHD5sYW5lWa7F5ICVm1ba5G7h8s1WRqu4QLg4fLYCXD72v2B0MiAeH2qjMagoU3T/D+e1ZjOOecnjVBEANXQhNH/PaJPOgH80ZQSKo5nXA==
*/