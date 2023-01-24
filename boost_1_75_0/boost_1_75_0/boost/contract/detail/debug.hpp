
#ifndef BOOST_CONTRACT_DETAIL_DEBUG_HPP_
#define BOOST_CONTRACT_DETAIL_DEBUG_HPP_

// Copyright (C) 2008-2018 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

// Usually, never #defined (so "debug" assertions always in code).
#ifdef BOOST_CONTRACT_DETAIL_NDEBUG
    #define BOOST_CONTRACT_DETAIL_DEBUG(cond) /* nothing */
#else
    #include <boost/assert.hpp>
    // Extra parenthesis around BOOST_ASSERT to be safe because its is a macro.
    #define BOOST_CONTRACT_DETAIL_DEBUG(cond) (BOOST_ASSERT(cond))
#endif

#endif // #include guard


/* debug.hpp
p02M+G/eybbBZLC+JxHgP08t9kIVWwnZefWTZPUHWSjlibmt1heWeWsHE9VgjykK7q6ksR7PiKYypk1Vvp74cbPm+wPvo/ZWLDgzNo+N9T9K699FdppAZIco49mDLsH7h1+4SMjsdlOy2GdM+TbqaN8xsittBoLbDhIMlIe2U6s0eNMPk5Cwrqsk2BdVXUfDG6Qpeif/OqlZ7lgW++26A+1qUzpOXhpdSlEKsBA4yd/AYzqTadZG4tnXkGOcREI1oXNB+unGucdjT2doMYbnq4558EjvcU3RIX8wcfRzr8l+qaZjfNGUURa4v2BN4f4YSycEyzPxhFmvHh8lveoUTb+BMGGx0Fqj621ecH/wAXPudRhSYfUia8OurWO7XzC84npdWk1zyYFho6Ormfce+rsb/NwG0l1cSK5obFaYy9BMP69Zy6RZuoa1QMwAM0aebri/xrOikKjAZROp1DHh6nUE4lPHXAIejPWLYs8ZnDymji2yJD/tKDSsuVHbaOPgCxeqsUlR1tGzBYQ1KhxNb/0E6ekWiOQuv1qw1PcKCQg6sY/z9Mq50uUzY8hRCmeYhfKZKNXsSedbd8jL5JbTuZQf2rD7wQftvuJwNqMHxON9hSffTubtMurmkbY661zNiSUbsBbIOC0wIMCZ4lG9pz4nfQjT3lmU1oJa3YRVmRPeFzmR52ZlYQWar3xeXhy8qbE8SHf8w6NNQCQ4
*/