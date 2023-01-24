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
YfF8T31hQT0VPYHaOuDW+aTVlTIHwcLFLPbqlKOyraNDi5cvhWH1wVdXj3NzZZTXoe7QCkPbvxmMcnBVPoNcntQZx53JquoVN1tsGh/yMtIqLspFdJ/yTaasX0RHiU/iwe3aUh2VY4i4+NM4VUDrDaej6JJfyMwPY+1UTe10fSOjDLBxSnyeZqkLNdpfbSMRMrCaSbvfvUoviMc3+UaQTXpMN2+vosAC428dH7yweDO5AncCug1GPV6obOno7ARC2bRCOGLEKyuzVVUd0aSVPT3NdXU1LS3l3S9bNk3tdQj/2iv2FrnzRlcn/O5zHT77U5qw6FrFdxMUB+k3/dZo0yg+K5AB+PBa21flZ0Fe20xh0yjhwMT7b+FGnNUpEaEAwEIV2V8dIHvUwjluzWoCm688LtOdbrxl2uGrY0TQHfsKxPSK87YACklPJ/Pad4rdcIi9/KnJfOVGBhQNpo0gSj8+mV6NjAkBg6MFoNnc0IH4d39VNj/jBk6+YnA/s7AKI2v1i8NZ3xY74uM7mpmdXv3r5K8Y9oQ8Y/1yPb989HGXpKMwoTAj9ZsUkduDEF1NGW71TbReekerjvKX1WKRkfWioFcY8v0te6SOQKjrQqJnesYEFPekAH/7jRbAlDDWwSY9bDxReJ/Y5cc0yysGi8NnADmqrb2GQLIS3VnZlL9BYmlfmYlXXXpx8cqE/xL5AozvNshSSqnB4hmb
*/