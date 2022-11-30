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
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
*/