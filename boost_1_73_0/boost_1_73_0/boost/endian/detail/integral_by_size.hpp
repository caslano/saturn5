#ifndef BOOST_ENDIAN_DETAIL_INTEGRAL_BY_SIZE_HPP_INCLUDED
#define BOOST_ENDIAN_DETAIL_INTEGRAL_BY_SIZE_HPP_INCLUDED

// Copyright 2019 Peter Dimov
//
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt

#include <boost/cstdint.hpp>
#include <boost/config.hpp>
#include <cstddef>

namespace boost
{
namespace endian
{
namespace detail
{

template<std::size_t N> struct integral_by_size
{
};

template<> struct integral_by_size<1>
{
    typedef uint8_t type;
};

template<> struct integral_by_size<2>
{
    typedef uint16_t type;
};

template<> struct integral_by_size<4>
{
    typedef uint32_t type;
};

template<> struct integral_by_size<8>
{
    typedef uint64_t type;
};

#if defined(BOOST_HAS_INT128)

template<> struct integral_by_size<16>
{
    typedef uint128_type type;
};

#endif

} // namespace detail
} // namespace endian
} // namespace boost

#endif  // BOOST_ENDIAN_DETAIL_INTEGRAL_BY_SIZE_HPP_INCLUDED

/* integral_by_size.hpp
a4rOdlchqx+MVogiKAvchX7JVtiLlDxjRE/9EYdnmfUyVHXlOGDWqweHDHUh25Wkf7W0VtVWpxAUhUP1mrYSkaxl4e87fKCIXvDh6dGymBmITpjYox9chy/kdvQ7sBsUU7g6hVVjXoEix8Uh9RaLw076JFqz2JDT03HtzqeJFcynU2OYRWESTsJpbLl6A9Hi/eF+nU09y6kLqyPcAP36zThYzdQQCcZNaPE/YDdlSTPsUZ5brBhq5yP42wI4cBrRJyVIhkSe44//GbE27EeLNxsGuxOJPhHcEupkfD1AdAwfj/ZS65nH+fFW7Gvq0Efjt8FedPRj30iHsY/CY6fgYt31tsN/pGbYfVdmaAeqB/JA9JHO+WEZu6Hv6/h21ljIC1cI94/lFMxMyL1z/al76U/9ZGG5ed79ZZw5J8fOqXGIvGQeBXDnTueeFVGFB6E06b00vAXWnXmdkvSRJtum4QJRukO2c5wHt0F4H6Sh2R0dVHPViWgQex640zjEQ+AyeuHvzosuw9iDAYoYp/Zij5MrL4p2ZutfUEsDBAoAAAAIAC1nSlITwqqDTwMAABQHAAA0AAkAY3VybC1tYXN0ZXIvZG9jcy9saWJjdXJsL29wdHMvQ1VSTE9QVF9QUk9HUkVTU0RBVEEuM1VU
*/