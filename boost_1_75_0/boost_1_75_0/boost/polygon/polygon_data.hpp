/*
  Copyright 2008 Intel Corporation

  Use, modification and distribution are subject to the Boost Software License,
  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
  http://www.boost.org/LICENSE_1_0.txt).
*/
#ifndef BOOST_POLYGON_POLYGON_DATA_HPP
#define BOOST_POLYGON_POLYGON_DATA_HPP
namespace boost { namespace polygon{
struct polygon_concept;
template <typename T>
class polygon_data {
public:
  typedef polygon_concept geometry_type;
  typedef T coordinate_type;
  typedef typename std::vector<point_data<coordinate_type> >::const_iterator iterator_type;
  typedef typename coordinate_traits<T>::coordinate_distance area_type;
  typedef point_data<T> point_type;

  inline polygon_data() : coords_() {} //do nothing default constructor

  template<class iT>
  inline polygon_data(iT input_begin, iT input_end) : coords_(input_begin, input_end) {}

  template<class iT>
  inline polygon_data& set(iT input_begin, iT input_end) {
    coords_.clear();  //just in case there was some old data there
    coords_.insert(coords_.end(), input_begin, input_end);
    return *this;
  }

  // copy constructor (since we have dynamic memory)
  inline polygon_data(const polygon_data& that) : coords_(that.coords_) {}

  // assignment operator (since we have dynamic memory do a deep copy)
  inline polygon_data& operator=(const polygon_data& that) {
    coords_ = that.coords_;
    return *this;
  }

  template <typename T2>
  inline polygon_data& operator=(const T2& rvalue);

  inline bool operator==(const polygon_data& that) const {
    if(coords_.size() != that.coords_.size()) return false;
    for(std::size_t i = 0; i < coords_.size(); ++i) {
      if(coords_[i] != that.coords_[i]) return false;
    }
    return true;
  }

  inline bool operator!=(const polygon_data& that) const { return !((*this) == that); }

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

/* polygon_data.hpp
9vU27ZZ0CU92UkGupPWmQUiNPwC9ReWifZcgCqCNbp1XBd5r8Xf/z4BuKhlHyub+kOE/AZwc1yY4rZF0ONqPaOuHtjrJXgiWyyofczTrdwa/Cf00oujSocWOgRGzeokt+oVPim3NuAzh5uHiPXqoIx4rpsG+u3/1bSC0D/r8TFLlucjGEvrpzRV5HiUxf/bHwi5nbz09j5SzoZnUBmFa2lxFR7aib13vzV0UAk0Ujv+UTw3OdDPGqIZ/Elz3j2RhcvPwWV5Flf57hqWltdWaJ/tFH6SjO1LD6YIqqRjp2BdERZ393cP0AZs1AxFgBnLH8999H9XFPGoB0K3RFKz2v1RfT69ZfNHrvP9H3hZ9y5KP3tZ223NoNFdcZrZlKvN9yhPKOFOaZ7+qNmYXdlONSQnVA76UMtG0iDB0PMh4PLoGFU653A48XDfTribVtngBu6nfhAYU8okKpATdm0g5qdh5S8CDJTgY5I/TZUjDkRXlipkcAZrDty1aiFRNkDI0fNjmm3lVqPnRVzN9jZyeAsiPnp6C21svQ1NTqBJENy/v7+o/QICKskzvyFhtLsb5yGnOE8Y/JlnmJZcVZkQ1V2Aw2YpFe2m7X//Jmx3Br9ypfzA5lzZnUp/LyYkTJicnj4+P72Ay1ExXSh9QToxu8dL8x2l+3Wf89tt0s2P1Y2Cgiu43YCWtxEx61gr79EFambZcuJ2rj2lBbf+7
*/