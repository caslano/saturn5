/*
  Copyright 2008 Intel Corporation

  Use, modification and distribution are subject to the Boost Software License,
  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
  http://www.boost.org/LICENSE_1_0.txt).
*/
#ifndef BOOST_POLYGON_POLYGON_90_DATA_HPP
#define BOOST_POLYGON_POLYGON_90_DATA_HPP
namespace boost { namespace polygon{
struct polygon_90_concept;
template <typename T>
class polygon_90_data {
public:
  typedef polygon_90_concept geometry_type;
  typedef T coordinate_type;
  typedef typename std::vector<coordinate_type>::const_iterator compact_iterator_type;
  typedef iterator_compact_to_points<compact_iterator_type, point_data<coordinate_type> > iterator_type;
  typedef typename coordinate_traits<T>::area_type area_type;

  inline polygon_90_data() : coords_() {} //do nothing default constructor

  // initialize a polygon from x,y values, it is assumed that the first is an x
  // and that the input is a well behaved polygon
  template<class iT>
  inline polygon_90_data& set(iT begin_point, iT end_point) {
    return set_compact(iterator_points_to_compact<iT, typename std::iterator_traits<iT>::value_type>(begin_point, end_point),
                       iterator_points_to_compact<iT, typename std::iterator_traits<iT>::value_type>(end_point, end_point));
  }

  template<class iT>
  inline polygon_90_data& set_compact(iT input_begin, iT input_end) {
    coords_.clear();  //just in case there was some old data there
    while(input_begin != input_end) {
       coords_.insert(coords_.end(), *input_begin);
       ++input_begin;
    }
    return *this;
  }

  // copy constructor (since we have dynamic memory)
  inline polygon_90_data(const polygon_90_data& that) : coords_(that.coords_) {}

  // assignment operator (since we have dynamic memory do a deep copy)
  inline polygon_90_data& operator=(const polygon_90_data& that) {
    coords_ = that.coords_;
    return *this;
  }

  template <typename T2>
  inline polygon_90_data& operator=(const T2& rvalue);

  // assignment operator (since we have dynamic memory do a deep copy)
  inline bool operator==(const polygon_90_data& that) const {
    return coords_ == that.coords_;
  }

  // get begin iterator, returns a pointer to a const Unit
  inline iterator_type begin() const { return iterator_type(coords_.begin(), coords_.end()); }

  // get end iterator, returns a pointer to a const Unit
  inline iterator_type end() const { return iterator_type(coords_.end(), coords_.end()); }

  // get begin iterator, returns a pointer to a const Unit
  inline compact_iterator_type begin_compact() const { return coords_.begin(); }

  // get end iterator, returns a pointer to a const Unit
  inline compact_iterator_type end_compact() const { return coords_.end(); }

  inline std::size_t size() const { return coords_.size(); }

private:
  std::vector<coordinate_type> coords_;
};


}
}
#endif

/* polygon_90_data.hpp
cVajiR3YCopgGQRaoiyutCiQVJxs2X/fHSW/DUndZRmmIJZF3nPPcy88Oey83OVBB7ZesfuP8cK7Q1xq9RtP7OPWcfwA9R+ibvC+jSSEFeQhbsN2yAO0HCRuWA7pexxvI7ohbfQREvImpq+4gjBCnqjyXotpbqF10oa9Dx/24S282323G8ApKwSXMLa8mHA9DeAwdSs/5ezubsfw4wC4BSZ3GldRLgwYldk50xzwuxQJLwxPgRlIuUm0mOCDKMDmHDIhOZwML6/7g58DmOciycnJvarA5KqSKeTsloPmCRe3tY+SaQsqQzg6T4Wx6LCyQhU7yM3Bcj0z5IPomTQK2C0Tkk2QiFnIrS3Nj2GYVFqi+jBViQmTRfg7uZ0tI7lGETN2D6q0YBVUhgdAlgHMVCoyumNCcLGsJlKYPFipQaoiDZUGw6UkX4gT3NSyOYyb9ARkBiUqFpZuRhWGqOa5mm0YYh7JS1bpAokwD2iUKkxzAFWRcu2MXeQLiianLsFPlmalNwVVoBjwu2Poj32YMCNMAJ/70cfhVQSfu6NRdxBdw/AMuoNrcvapPzjF0gsk08DvSs0NkmsQs1IKnjacL3eF3itRJLJKOfhUvCTnyZed3PdW64e0Xlc2P/Y8Y5kVCZxcjc4ThdtVIWxs
*/