/*
  Copyright 2008 Intel Corporation

  Use, modification and distribution are subject to the Boost Software License,
  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
  http://www.boost.org/LICENSE_1_0.txt).
*/
#ifndef BOOST_POLYGON_POLYGON_90_WITH_HOLES_DATA_HPP
#define BOOST_POLYGON_POLYGON_90_WITH_HOLES_DATA_HPP
namespace boost { namespace polygon{
#include "isotropy.hpp"
#include "polygon_90_data.hpp"
struct polygon_90_with_holes_concept;
template <typename T>
class polygon_90_with_holes_data {
public:
  typedef polygon_90_with_holes_concept geometry_type;
  typedef T coordinate_type;
  typedef typename polygon_90_data<T>::iterator_type iterator_type;
  typedef typename polygon_90_data<T>::compact_iterator_type compact_iterator_type;
  typedef typename std::list<polygon_90_data<coordinate_type> >::const_iterator iterator_holes_type;
  typedef polygon_90_data<coordinate_type> hole_type;
  typedef typename coordinate_traits<T>::area_type area_type;
  typedef point_data<T> point_type;

  // default constructor of point does not initialize x and y
  inline polygon_90_with_holes_data() : self_(), holes_() {} //do nothing default constructor

  // initialize a polygon from x,y values, it is assumed that the first is an x
  // and that the input is a well behaved polygon
  template<class iT>
  inline polygon_90_with_holes_data& set(iT input_begin, iT input_end) {
    self_.set(input_begin, input_end);
    return *this;
  }

  // initialize a polygon from x,y values, it is assumed that the first is an x
  // and that the input is a well behaved polygon
  template<class iT>
  inline polygon_90_with_holes_data& set_compact(iT input_begin, iT input_end) {
    self_.set_compact(input_begin, input_end);
    return *this;
  }

  // initialize a polygon from x,y values, it is assumed that the first is an x
  // and that the input is a well behaved polygon
  template<class iT>
  inline polygon_90_with_holes_data& set_holes(iT input_begin, iT input_end) {
    holes_.clear();  //just in case there was some old data there
    for( ; input_begin != input_end; ++ input_begin) {
       holes_.push_back(hole_type());
       holes_.back().set_compact((*input_begin).begin_compact(), (*input_begin).end_compact());
    }
    return *this;
  }

  // copy constructor (since we have dynamic memory)
  inline polygon_90_with_holes_data(const polygon_90_with_holes_data& that) : self_(that.self_),
                                                                  holes_(that.holes_) {}

  // assignment operator (since we have dynamic memory do a deep copy)
  inline polygon_90_with_holes_data& operator=(const polygon_90_with_holes_data& that) {
    self_ = that.self_;
    holes_ = that.holes_;
    return *this;
  }

  template <typename T2>
  inline polygon_90_with_holes_data& operator=(const T2& rvalue);

  // get begin iterator, returns a pointer to a const coordinate_type
  inline const iterator_type begin() const {
    return self_.begin();
  }

  // get end iterator, returns a pointer to a const coordinate_type
  inline const iterator_type end() const {
    return self_.end();
  }

  // get begin iterator, returns a pointer to a const coordinate_type
  inline const compact_iterator_type begin_compact() const {
    return self_.begin_compact();
  }

  // get end iterator, returns a pointer to a const coordinate_type
  inline const compact_iterator_type end_compact() const {
    return self_.end_compact();
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

private:
  polygon_90_data<coordinate_type> self_;
  std::list<hole_type> holes_;
};
}
}
#endif

/* polygon_90_with_holes_data.hpp
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
*/