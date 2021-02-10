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
DpMi62K4aP9OPBLZcsh6Xy9km/J/6Tww+38JFx9IXmVKTpB2Q+JUM7mHeKAfRU8aRPbcaSICOZRm9MBsohJzXmo5gQMvScTM9ht86GgDyHxtC1IIoWMAwJtPSgybSMTSXGw+FCtxYWmpHqOA7dmhyvBcm6Zsehni7V1ADk8n1Tll4mvt+qf9y7NXZ5dnFy/OrvZpD1/ZuCAdwzbBtdnsMw6eCkaLYctsY2kSssoOrrzPmO+w9pdUJo1qtUXPFiQMGHPmaejKa5a87NHdTFDgJ1xVnRZWUY3RIRT3fH7t7jCaoLnhHdyEyI20QTRNftUt5oS3c3OyzsxuBVUFUjCeV4tn0kbkxdvrs4495UdjEKfJCEJMgLVBTgANJGeV9aamoXIn51a1Qzq3oKqYI04ADTJFILRG2v2VzrHTTyWfubuawL0LNgKAyuAR5FAPbcUd+gtzkEQpTGNmfhjac3iRmL8rMDV/hdnJH48PoT0DxXo+EbmDF0gpZAgiv54c702p8l1xsoBw9WqZFKZmWVyY0rYGel6Q+GNRRP2yjJkadn325t2iiPHafPhzJcwuqHaUP8MXGB7MRzARsu/pdk4/ijs8XKZZ9Eja2ILCzBYZYfPA1i7+0FxY/xq7K4wvW1rIfQ4GYuE7zzgf8J68
*/