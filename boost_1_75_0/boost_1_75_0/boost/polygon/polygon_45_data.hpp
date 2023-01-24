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
NzSXdr25gALbkUzGl7HLLsxd5LTr+euAYWZAr/gv8YjzVgNAxDkfHZxNzf+Nsb87MT7Md/tpMaq5HIOfL+ONDXOwoHSIIebth74XvE84bcb9oNdCSoWEF6lCT8p4XT+C23P0t8fWdzI6UmuqMttTN9xaB/K3tfbWNmvYnTt72N1jKz4kjt+VnW+RdmBvtngD82SpAoYhGKxsg9perCytoR7Lnug9tucDdw4EfhdXG03YzQvgoQ2PxKM7Cj92cqC/6QxdnO0PqTj7osQ5V53Q/UDwKDfJT0BZ4QCdKHp8K0Os62aIsg2MjmVd5kc/WPdUwaaOh1zO1rrhUEXgywHpLynD0P08dkVi49XMP6c9/ScmNRMiVfm42Dh37lw9H+AlnrC2VKYVuZyB92lh+MGpweqSFy/IH99dIImhmjuRpzeOXnC5jS/TeEXwPdlRULAER6LmTQ+CbJjXfre8GjNVbyuX0PmEUtuehn4oWtiOI8L+ys3QTon7m5VRansBJvYRI1tFmuDrbpXf7mzfhb7IHHzL3o8a1N56XH/s+cq+/sqYOVh0fHDp+oIIWS57+qZ9NGQYZby/PTL91ZfbTJo/zq8A2q82e5DkVmSA0b40E69ZXrNYui87bDlOgHiiVsla3iifmzUuV/9K9l3xU9WPC6CNU51crGv+FVJtvoCp9bli7f19q/R81ri+lB4XLW+6OVmbIabO5NEykwqD
*/