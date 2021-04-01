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
U6AVEYcEG1+Iaku4IivApIeMtOtAx2quO95UVzOSqu9SfM2EvpM9h6U2lElTotnQmIHewmE4KFG3zGBceBmjl1HLzohL+vbHcscBwfv3SoTJ9uR4br6YxTebCzJYXjUceL1kYesCyaWaMb4UUC9MufLqPF5m2mCOpH3Bp08jkbY29uqizB+9K0LVVmkChAccwx4FUw1S+/bmiievtzlObzcCp2lnj4ndbREvVP//pbBWcIj9tTT5RXhS2x8B8AfxkqKZyLv0uhTFT22E/wFPzz0daNveOLqfgxT+1TYcNjA4xrxXyLac64Dh8F7cvd3Bir0Pbp574+kQO5GbqCg40x7AIUaoBaMhSGIXEHLCQuVHjpkpb2zQQZkl8WnZHl4Rh+0A82IvteOU4K2TKt+DkTMXbEY0C3eIgPbl7v5zuQuGXnRhATpfPz6j+684E3lhtQ98A3XgyEVTqFEgq7z1PV6Wmla2xqmko/Wmd35u5fmOA5Utn1XCxKH92xV2QUp+qJ7FoxwN9uj0oXUcy7iiM7O9tel7FP/0qusbCSU0qEiUoBj6m/2QGkscvg==
*/