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
koH8AexBpPtiS787bQRle8zJVC7PJ2kLQ5TUqUYF08uerwh4wwfNctbOn9fMK+sevtaWSX5om2LS0GVVnddRO5INxwNT3pqVZVAfMVsdMQANFLNTmRe//Aa/lHNvz1sYGrV6zYkI2iTQp+N/5Uis05QxSoKdAmegszAX5hn/yq5iBhtxxyACDqhzhHIz8BNZ/HoNOxhd1QkWlyc72FRr5KhG3+yGy6b8jMdZUXJ53mTkNXdddyOo6KDXeDnLKFy5cs/ZTX9bnpSI8ar/d+Uisw4ALOwAQ3B9EoNRc+zMbk/agSmh5wk/063eb0zd3aF/Wa4CAYLlMXOToU4WQeWOPfA/Vz20RJXsseCJgk2GNE87Ah+6mzj33ksstK+aWH5Dz+0R6yTrkkQCn6p0rOeOFuEe+KenUuu+y6N0X9xlWdFJfuK+lsyFMOX+somN3vdM2/s4FbDnPRQG0MgwKBmmrGA53SlFAeWFYnXjkR2Cjz2YSj/428O+uSfjIry1oPggHhc2XXIe4YrYkrFnttvCV+LMY1vQiOR1qicbPhBnotBSiVIJRAicOligRg==
*/