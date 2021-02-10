/*
  Copyright 2008 Intel Corporation

  Use, modification and distribution are subject to the Boost Software License,
  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
  http://www.boost.org/LICENSE_1_0.txt).
*/
#ifndef BOOST_POLYGON_POLYGON_45_WITH_HOLES_DATA_HPP
#define BOOST_POLYGON_POLYGON_45_WITH_HOLES_DATA_HPP
#include "isotropy.hpp"
#include "polygon_45_data.hpp"
namespace boost { namespace polygon{
struct polygon_45_with_holes_concept;
template <typename T>
class polygon_45_with_holes_data {
public:
  typedef polygon_45_with_holes_concept geometry_type;
  typedef T coordinate_type;
  typedef typename polygon_45_data<T>::iterator_type iterator_type;
  typedef typename std::list<polygon_45_data<coordinate_type> >::const_iterator iterator_holes_type;
  typedef polygon_45_data<coordinate_type> hole_type;
  typedef typename coordinate_traits<T>::coordinate_distance area_type;
  typedef point_data<T> point_type;

  // default constructor of point does not initialize x and y
  inline polygon_45_with_holes_data() : self_(), holes_() {} //do nothing default constructor

  template<class iT>
  inline polygon_45_with_holes_data(iT input_begin, iT input_end) : self_(), holes_() {
    set(input_begin, input_end);
  }

  template<class iT, typename hiT>
  inline polygon_45_with_holes_data(iT input_begin, iT input_end, hiT holes_begin, hiT holes_end) : self_(), holes_() {
    set(input_begin, input_end);
    set_holes(holes_begin, holes_end);
  }

  template<class iT>
  inline polygon_45_with_holes_data& set(iT input_begin, iT input_end) {
    self_.set(input_begin, input_end);
    return *this;
  }

  // initialize a polygon from x,y values, it is assumed that the first is an x
  // and that the input is a well behaved polygon
  template<class iT>
  inline polygon_45_with_holes_data& set_holes(iT input_begin, iT input_end) {
    holes_.clear();  //just in case there was some old data there
    for( ; input_begin != input_end; ++ input_begin) {
       holes_.push_back(hole_type());
       holes_.back().set((*input_begin).begin(), (*input_begin).end());
    }
    return *this;
  }

  // copy constructor (since we have dynamic memory)
  inline polygon_45_with_holes_data(const polygon_45_with_holes_data& that) : self_(that.self_),
                                                                  holes_(that.holes_) {}

  // assignment operator (since we have dynamic memory do a deep copy)
  inline polygon_45_with_holes_data& operator=(const polygon_45_with_holes_data& that) {
    self_ = that.self_;
    holes_ = that.holes_;
    return *this;
  }

  template <typename T2>
  inline polygon_45_with_holes_data& operator=(const T2& rvalue);

  // get begin iterator, returns a pointer to a const coordinate_type
  inline const iterator_type begin() const {
    return self_.begin();
  }

  // get end iterator, returns a pointer to a const coordinate_type
  inline const iterator_type end() const {
    return self_.end();
  }

  inline std::size_t size() const {
    return self_.size();
  }

  // get begin iterator, returns a pointer to a const polygon
  inline const iterator_holes_type begin_holes() const {
    return holes_.begin();
  }

  // get end iterator, returns a pointer to a const polygon
  inline const iterator_holes_type end_holes() const {
    return holes_.end();
  }

  inline std::size_t size_holes() const {
    return holes_.size();
  }

public:
  polygon_45_data<coordinate_type> self_;
  std::list<hole_type> holes_;
};


}
}
#endif

/* polygon_45_with_holes_data.hpp
l4VCFvxXT/sN6Mz5HNYONXJ9TbLJE+pfcteoRX1BEirol21RYivmBEydLTSEzBZeapxWjQE0AMwJXW0nGsePqFRrDXI/aAbiymGmmx2IKTWPJV1iONxdLA2yRwzIZIBVvop1UdVnLQLhZeqDWkI7lrSO+lPC3AmfSgcy9fwqhwydfcLJs6S74MfDh4mJVvv/IV+0v58PW8kTAWkOC6QHmSdzqidnx8eNVYF4jZlJidaftZgxrcaVPCDV7LMb15mnGRKVwuyr/LlHPcgDACCWrdVS48eFX7x4nn1wZD+WS2Pn68hogdQQjhx1DenTGQk/wYLhl53H+3JSwloX7EO86ZRQxyE2v7DJmIsgWuZF4zEyk0XuPY8JK4Mk4yLXBaZxP5Brrei7ljxsF7uG+wGpRocBHNeMvIc0yPn9yTA/YOVrY4c2SOoEYyULhJXYgqnBa4lRppQ7VSO5FjHjQdgII5bfhHPyJutoTt9V4nmhcj+Ro7PlJY7wOboG+QPmSVhLZNPYDDv7Kmo4Qf4HUEsDBAoAAAAIAC1nSlKAKbhqQAQAAC4MAAAhAAkAY3VybC1tYXN0ZXIvdGVzdHMvdW5pdC91bml0MTMwOC5jVVQFAAG2SCRgxVZtb9s2EP6uX3FQgdb21CjpOiBdXjAj
*/