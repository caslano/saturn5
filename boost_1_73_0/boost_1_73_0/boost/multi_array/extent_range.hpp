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
yaxEs8+QolVrEvEG5K++m7A5q1/KX/2WCVpOV1vXtfD6xhiF/jIafwEEJ5FSV+cVX0eYskmRyCWSQjq5l+A4C56Bd2E2zk4k+y61XCi8fXni3Yz35CSXKbp13U4qvq8T9FAEQCdjC6hpn1ebdp2/ph3TzjS0nbDoM/LD9+avfhHHVyY5q/kwIHPA2lr08/JjBhFCvcLCOZpneclEc/Di57GDsDxaHpnMlREx/GK0dtGlXtSuhBlXjOKEkwYzjww=
*/