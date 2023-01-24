#ifndef BOOST_CONFIG_HEADER_DEPRECATED_HPP_INCLUDED
#define BOOST_CONFIG_HEADER_DEPRECATED_HPP_INCLUDED

//  Copyright 2017 Peter Dimov.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//
//  BOOST_HEADER_DEPRECATED("<alternative>")
//
//  Expands to the equivalent of
//    BOOST_PRAGMA_MESSAGE("This header is deprecated. Use <alternative> instead.")
//
//  Note that this header is C compatible.

#include <boost/config/pragma_message.hpp>

#if defined(BOOST_ALLOW_DEPRECATED_HEADERS)
# define BOOST_HEADER_DEPRECATED(a)
#else
# define BOOST_HEADER_DEPRECATED(a) BOOST_PRAGMA_MESSAGE("This header is deprecated. Use " a " instead.")
#endif

#endif // BOOST_CONFIG_HEADER_DEPRECATED_HPP_INCLUDED

/* header_deprecated.hpp
ZL72fdjhzfhsYA7TaGVdJuFnmGyxmCKH6WeKKVEBBcFWHlA+9OCY0EF/2NK32R+lPcaX7BTuYRiNLr2prA/YImf4ZSqLozKGX6aYYfXUnFSVXFbBwLES89+7VNjB6Gy6lOs5mpmQGJpZzNCMjaEZznsOcIzCkRfrhM2sZBMfms+qTFg/fdZvtrFvnmLfPGH95s0M3QwwnLqZ41T+zdxicDN8M6uavTKHVTKH4x3GGs8xI9pUD6TCJ5l1IktTiDbTA6ZPn2CfvpT9LM42Y1gb3o0ncYXQLcZhynqVKnW5ts8JqPGA2+M67PG4It5hV6O+AAAcLOPTGz6fYZT6DaMrUGEUBxPGxtz8UHWubhTp2xxebRPFAgEtP68oXBpZFf083xcz8ksLjPySQiO/ragvvzvxlD2/IV6c/0ZxV6KipKpiqHJ/RUX5aImeKMjXo7siW7VXq/ctvwXX7qvz1B5OemrzGoZrG2vON/qajMbSZqOxq6Wisbg10bixLb99WZveWFSzbZm3+tWORGdRV1F3Wc+63lN9vn6jr3Sl0VeyyuhrW93X17Wmc6hq3fD6nesqRkaH9DXRPr13S1/DYKLvKtz5ilIBjFRE7Ip0aUc6t9NP6MIFKClqAhBWQS3kNFxew2lozrhWpCW0Sl9FOOEs1iLOsJYHbNhyaq/d6GswAA87B7XV2jptvW+dscbZE+gGxNapdaRkDTq6Yo9V
*/