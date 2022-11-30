/*
  Copyright 2008 Intel Corporation

  Use, modification and distribution are subject to the Boost Software License,
  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
  http://www.boost.org/LICENSE_1_0.txt).
*/
#ifndef BOOST_POLYGON_POLYGON_WITH_HOLES_DATA_HPP
#define BOOST_POLYGON_POLYGON_WITH_HOLES_DATA_HPP
#include "isotropy.hpp"
#include "polygon_data.hpp"
namespace boost { namespace polygon{
  struct polygon_with_holes_concept;
  template <typename T>
  class polygon_with_holes_data {
public:
  typedef polygon_with_holes_concept geometry_type;
  typedef T coordinate_type;
  typedef typename polygon_data<T>::iterator_type iterator_type;
  typedef typename std::list<polygon_data<coordinate_type> >::const_iterator iterator_holes_type;
  typedef polygon_data<coordinate_type> hole_type;
  typedef typename coordinate_traits<T>::coordinate_distance area_type;
  typedef point_data<T> point_type;

  // default constructor of point does not initialize x and y
  inline polygon_with_holes_data() : self_(), holes_() {} //do nothing default constructor

  template<class iT>
  inline polygon_with_holes_data(iT input_begin, iT input_end) : self_(), holes_() {
    set(input_begin, input_end);
  }

  template<class iT, typename hiT>
  inline polygon_with_holes_data(iT input_begin, iT input_end, hiT holes_begin, hiT holes_end) : self_(), holes_() {
    set(input_begin, input_end);
    set_holes(holes_begin, holes_end);
  }

  template<class iT>
  inline polygon_with_holes_data& set(iT input_begin, iT input_end) {
    self_.set(input_begin, input_end);
    return *this;
  }

  // initialize a polygon from x,y values, it is assumed that the first is an x
  // and that the input is a well behaved polygon
  template<class iT>
  inline polygon_with_holes_data& set_holes(iT input_begin, iT input_end) {
    holes_.clear();  //just in case there was some old data there
    for( ; input_begin != input_end; ++ input_begin) {
       holes_.push_back(hole_type());
       holes_.back().set((*input_begin).begin(), (*input_begin).end());
    }
    return *this;
  }

  // copy constructor (since we have dynamic memory)
  inline polygon_with_holes_data(const polygon_with_holes_data& that) : self_(that.self_),
                                                                  holes_(that.holes_) {}

  // assignment operator (since we have dynamic memory do a deep copy)
  inline polygon_with_holes_data& operator=(const polygon_with_holes_data& that) {
    self_ = that.self_;
    holes_ = that.holes_;
    return *this;
  }

  template <typename T2>
  inline polygon_with_holes_data& operator=(const T2& rvalue);

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
  polygon_data<coordinate_type> self_;
  std::list<hole_type> holes_;
  };


}
}
#endif

/* polygon_with_holes_data.hpp
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
*/