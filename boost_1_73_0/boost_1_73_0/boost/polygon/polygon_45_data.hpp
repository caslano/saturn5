/*
  Copyright 2008 Intel Corporation

  Use, modification and distribution are subject to the Boost Software License,
  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
  http://www.boost.org/LICENSE_1_0.txt).
*/
#ifndef BOOST_POLYGON_POLYGON_45_DATA_HPP
#define BOOST_POLYGON_POLYGON_45_DATA_HPP
#include "isotropy.hpp"
namespace boost { namespace polygon{
struct polygon_45_concept;
template <typename T> class polygon_data;
template <typename T>
class polygon_45_data {
public:
  typedef polygon_45_concept geometry_type;
  typedef T coordinate_type;
  typedef typename std::vector<point_data<coordinate_type> >::const_iterator iterator_type;
  typedef typename coordinate_traits<T>::coordinate_distance area_type;
  typedef point_data<T> point_type;

  inline polygon_45_data() : coords_() {} //do nothing default constructor

  template<class iT>
  inline polygon_45_data(iT input_begin, iT input_end) : coords_(input_begin, input_end) {}

  template<class iT>
  inline polygon_45_data& set(iT input_begin, iT input_end) {
    coords_.clear();  //just in case there was some old data there
    coords_.insert(coords_.end(), input_begin, input_end);
    return *this;
  }

  // copy constructor (since we have dynamic memory)
  inline polygon_45_data(const polygon_45_data& that) : coords_(that.coords_) {}

  // assignment operator (since we have dynamic memory do a deep copy)
  inline polygon_45_data& operator=(const polygon_45_data& that) {
    coords_ = that.coords_;
    return *this;
  }

  template <typename T2>
  inline polygon_45_data& operator=(const T2& rvalue);

  inline bool operator==(const polygon_45_data& that) const {
    if(coords_.size() != that.coords_.size()) return false;
    for(std::size_t i = 0; i < coords_.size(); ++i) {
      if(coords_[i] != that.coords_[i]) return false;
    }
    return true;
  }

  inline bool operator!=(const polygon_45_data& that) const { return !((*this) == that); }

  // get begin iterator, returns a pointer to a const Unit
  inline iterator_type begin() const { return coords_.begin(); }

  // get end iterator, returns a pointer to a const Unit
  inline iterator_type end() const { return coords_.end(); }

  inline std::size_t size() const { return coords_.size(); }

public:
  std::vector<point_data<coordinate_type> > coords_;
};


}
}
#endif

/* polygon_45_data.hpp
6s6osOxQFAgquEUOzt4fWx7kWLhcjAImFvPqZ49PapW/KgQGlwC7hplej05/2q/cpAVlpriQ8FZlbmSlUzD8NCw1enXU772EwoeDd5VKG9pNovTDk7e9wcGbUfgpZ2GnJDo5jYU7JdFh7+g4nLuPwJBtqBLq4y4jCa1cRZoloaqqWoGOj07OfgXlDw9fvyed5W6nIOm/OTockN1CakSuVhUtfPYsW1J6s2wVtQIoUbKASpK3g4XGKpDCtE2YjFkPVrb4tpNLjyyx810ucb0h0mKyyhW7lkNsNoEWZl3jUQCMcX8BJzLBAmHRgBE5FyzwQIJYNvVJfU4FuBR3v5AsXYZ7IVO5K2DyBAtHwJzZTydNlLlIlwfB+ZA8D+tp18nYp9YnJsAjXbmCLuUQJ+Qvo35eP7/9y5CzybgD0HYss9PZMXeePFFzGv8fpf4BVtS0eNheJ0PyplGRXUoM04Qc6rjEQCXRFLhpRAg0mwKR6JHxV1mdIt4QBZZkejyUqN3ENQhU2wICb5a2FjhjCwTG+GcQqT1Rhq49h6ge+i3BuwSVJCeAVVvo92ivUF170OafmD02MzYiehqNCSFdnGJ0PyKUIuS81/yIaXKg2Zg1CEu3Meed5lMM8kRTjyfN3dsj0OFxB4jm7RHobCkZ
*/