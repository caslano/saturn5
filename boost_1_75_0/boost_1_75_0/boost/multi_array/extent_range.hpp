// Copyright 2002 The Trustees of Indiana University.

// Use, modification and distribution is subject to the Boost Software 
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Boost.MultiArray Library
//  Authors: Ronald Garcia
//           Jeremy Siek
//           Andrew Lumsdaine
//  See http://www.boost.org/libs/multi_array for documentation.

#ifndef BOOST_MULTI_ARRAY_EXTENT_RANGE_HPP
#define BOOST_MULTI_ARRAY_EXTENT_RANGE_HPP

#include <utility>

namespace boost {
namespace detail {
namespace multi_array {

template <typename Extent, typename SizeType>
class extent_range : private std::pair<Extent,Extent> {
  typedef std::pair<Extent,Extent> super_type;
public:
  typedef Extent index;
  typedef SizeType size_type;

  extent_range(index start, index finish) :
    super_type(start,finish) { }

  extent_range(index finish) :
    super_type(0,finish) { }

  extent_range() : super_type(0,0) { }

  index start() const { return super_type::first; }

  index finish() const { return super_type::second; }

  size_type size() const { return super_type::second - super_type::first; }
};

} // namespace multi_array
} // namespace detail 
} // namespace boost


#endif

/* extent_range.hpp
tkRdHpKdt+DMPXZjJGMiV3NnwxsGHEZYl1GaHuhAK6dCatt4O/vEd3LlFjQ8y660LajkvTzXRhEkxrvQfHC+1/xyfUMf8jKbbjS33BnNiaikqh/eY5OqLwlvy6WWogZvQyNSDLendEoI3toYpohcpoiq650ijcfYUCpuc+oUSpXf6h4WQmQ/E3EQoQqhKTZdfPSxITlcBn/VOPzTwxaWZzVUAuPzPwxSyEsXZca6dDRJilcGm4p+DORq8W23kqSYXkmS4pPnmZXT1OtHGEU/drmNoh/V3eonRzjayUxdycppQVOLwrIg2DT3iJxGlL5bdEcNmGfcvBiQxfmhDjynToAmGbAAvNoIqZX16RCYvzUwfxoPd92wMK2vJc1UDTwWFXpsfvhjlO6xocdahR7zhj/2gqQnZ+gbfnMpse0u9Zloqe6t4hIj/8LzHevkX1gxTCeptIaz8eQhSa2fyZKl0BzsbZIsP0pISt/CX/VL/PMp/tmNfz7CPx/Cnw2YD0R9RyIaM9fOFESG1qRpNQaRyUxkuM0/Zo83OHwPjv07d8P08KsUlhUD5rHsRujhIwPyJN+VXZScDR76iwH7SVYYYJ8woL4p/GapgHqCqz7Up4fyH7nrQD02+zxQJwPUwBmhEPvEBuT5XZoFoF4Af9VJ+Gc8/hkNf0y2KaM+KcK37e+RJmvdV1jzMjB8m9c/aT/ap/ZT/cMO5gKQiVKS
*/