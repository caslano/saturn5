//
// Copyright 2012 Christian Henning, Andreas Pokorny, Lubomir Bourdev
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_TOOLBOX_METAFUNCTIONS_IS_BIT_ALIGNED_TYPE_HPP
#define BOOST_GIL_EXTENSION_TOOLBOX_METAFUNCTIONS_IS_BIT_ALIGNED_TYPE_HPP

#include <boost/gil/bit_aligned_pixel_reference.hpp>

#include <type_traits>

namespace boost{ namespace gil {

/// is_bit_aligned metafunctions
/// \brief Determines whether the given type is bit_aligned.

template< typename PixelRef >
struct is_bit_aligned : std::false_type {};

template <typename B, typename C, typename L, bool M>
struct is_bit_aligned<bit_aligned_pixel_reference<B, C, L, M>> : std::true_type {};

template <typename B, typename C, typename L, bool M>
struct is_bit_aligned<bit_aligned_pixel_reference<B, C, L, M> const> : std::true_type {};

template <typename B, typename C, typename L>
struct is_bit_aligned<packed_pixel<B, C, L>> : std::true_type {};

template <typename B, typename C, typename L>
struct is_bit_aligned<packed_pixel<B, C, L> const> : std::true_type {};

}} // namespace boost::gil

#endif

/* is_bit_aligned.hpp
83UF8MgxiKJx9vkpIrPBWOSoOg4SI0d/UbePCgB7GUzf3I7t5GwMhMJ/rrj7sYDUf9xuVh3rHvb51G6/78YLRJ7XSLHn96hVUQeh2eAhj2PiNoMk1twDAu/ejUDejy8CRGG67NGVEtO25LDs+yXEuRnXlcs7Mtdub3f+3t3h2g5NES6xOCsllBdZEFeR9F6rc8TmHJZPZF4EaIv+Thgr9HxbnlEto/5+WY6lZNPXceOnYQBC2lH7Y/7kJdKEoDpz0fDH7yNp6tlW04ETa9gkVCZaQO53YYDJKqu/OetlBMum9OBkGVxcoEDCZrKYkeUX4vqrDkREqv5RpbyoyfffQH+1S6mvJpxxV7eGsaJw1bkxOQfgm/1fck4PbOuBU7Kg5Qpih40uaYiL3hPHaafu6rPWoHnNLjawI5YHdnGTlynnZzj1dud096MSssZhc+4bhLDZqUUc8XbOCFHEYqkBUl2sDVopTBhhAG6cj7Qq/bwCfnRgF9jXFl8ZLD66o+AYMIVfmSx6q6R6/BDkLi22DbMcKGa00h/JWri+TjqdXr1ZFZbNjPwr8qt9py0Ay/fr8u7SF980s0lmD+qY9I09QyQNIbw53c7Gyv8aWFUXcuHSffZd9d3ZDkAfI26PwCdclEYiFlYSpTelpFdl3P0d4RuBQanRqULlSc3oWZ0+CPpAjrup8eoQslxt55x5yaYKmMAuVDfHESCuLqp7
*/