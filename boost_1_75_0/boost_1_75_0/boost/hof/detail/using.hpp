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
+3uB3VQvl38KFNNkSDbkEWN96vvr/JdxyN5MF3SGxBGWjl38gh+VnVcg8AyhuQG1M+EFJdEcESuvtvPZK6JzxsRK5cbEIG9Ql55cgcYs4+/+2p3Tuy31uqr36IgkMGaVPSCXVBbVomR+1P3nV3uvgEjH6aAwJVsyHXEyRAISdlUZeIKkDXCQJAdgXmzl36aaTuQ/U2SZ5dz+DKmI7jTPc9lXQl1e6jaQT/Ymx9rfOfhVdvyM/gqy+DAe8tGNtrL7ZXPjPCKRP+5Dm/1TU+a3KIpY3QGxYJxkITkj2Hi5PupjDeAosMXXPSdyB4bXjLdKMOOsVsZRreSWPbHPiFX+q13cBMwKvsCJJ/mErGKGXDLs9zkit81StJjc+SsoeIEOowHikC4pN05e/kDGRV4g8ybvSg+aNRyvKXe3WlbwPhlbxi3i+HlSATVWSu+R860L5Z5VLGWEct1EflU7X0NY0xithk/kWhofNaT/xAIuwH1OoLMU2X+tlMfmxXXu6Wtitx4E8nqwDrJfe9olNsFqeT+LDwR4OTyKhc5HHIT9TVq/4kd4AbQN5BSwWkCRby/1nFa6z+Gs8i7jF4R/Vh+tBfzIUbxmxfuvnYwbLscOLX4xpFE+vMzJo/6AThw44DI5nrk6rJAjv0oCdVA4wljNlIr0+iRLY+jYWjLQMNz53uZEtZkOY1XOlP6xKdQmdxQ5GefTESOhq0TuI4+2
*/