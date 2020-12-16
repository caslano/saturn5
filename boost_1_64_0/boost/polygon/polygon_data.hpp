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
PodoaRvbS0MZsbVsLy0pyn6RaGO+EiuR5e1F+67lzfZW74KQ+Tl+bGt+3LE3Li3pomJJifbH5i3bCLkYbM/bK6N5S6yAaeZ/ZF/RxigckvkPkvmHUcop+2b6+atBOn9knpo4HTXPnDIByZloGSMjuftbyHbXxLTfpK+TtIZseH9wuzOti2Qb7yiowHBNF5nilQJadPM3NkNov8DYcL02MEU5Uma+XRyYCbnO1HbRxo+8bWoHeV9AN2kHP8p+JZeduT7RMYYU02Rgy+J+189GPM7mDOaXlMH8AsKjstTm2nm2Ni1jvvRt3rgkbf6JaZ6vp73lvGCrvdWcuw8kh/9NdMGzWLEU7W2sS0iUMWG8ssmp+13DvJnNuZe7aP3P1ZidDPNL6pUyTBcKso+o+4w5d6e9MZ6L+sdYv3uaY76E+3CPn/7uMs1gWo4VFxqh0w8L6Bcd2D8iNFIv833+0pjDUCfvrJa8sfQz5ENn1sZ+SWnGvH1yLWLM05eW/r0Bp9Kscien2c5bmZYmOXilOzXNFFskuf3S0sdePaff3xwZRnL9XZdph0oiSWV+KdKPDIv9wuKU7URiuWR6+ii9DJurqG8+hivAMin9F5tzn++VYcnTKE0tuR1lnATGiefvMUvN8UxnTcsZFRIKam7HmgnGYSqxUSndXp9a5sK9/KllLtzolZZ/9/tMzdVr8X6DkfJ+g2GUQrL+P1Zyaa8xx5fJkTHTsYOyj6pxbnrjNmXrXUrqfuMpOcYnSa7qofgh9Ug010N23GF6tkxDXXSZzFWt5KZ22mqZm1rpN+ELQz/JbJ+5/amE6ZzDDLncGRISYPxLYdmvPOzN5yZXzbnJSbMf6UJDB5mmlZzBdVaCVY7rK6bhKJIP0yLPa7x0m3JRr7eRg/i6VS7qFKt3bGymO7dyTgky1u2s9bWd1DlJ+mvXh7JNj2Vbimcj2qPcMl5rzie915S7MzpYzWXN+Gpu2ET5e0iMXtkm1GmlMq3cTOTDdeZ9aqeMG6K8BZ+E3KYYxENKf3vprzkGrTZNm/70spi+O9tYI6WuG6Wu8i6Lm8qxMizKYtjZhY0xbhM2meuyX22/0Gh9AHMINuYtX6ntT2WGhIYbpuPBNOIpS5RrkS0yT4l/bMrGIrm1Lea7U+pY5hvz8PO0dZTjQ/MvjH//VXJxz9lgmZv7+QbLv9/aZPn3jpuN3ax/Q/e3X8vwVscLnZwpN+fieIHrsbJyXbXDaj+NzEwMqu3zqsRdW1zfsaotcsjyfh6OSubzlnpOiQoP0eTcln1Atn91n8k4LjfVFIs6SC/xpenzdN9S+0Ua2urCTjX/vqG7yy7L7rG7jd0bXSy/G6VJW74jx962lDcZJ36vdV5y9VI9IFbH1XMW3m8nOXPV9tDbOPbuZwTl00DJm4LVcFox9j+ph3rBIju7Mu/EP5In2PYxVc2Bvdd4jRJgamdnzfGzDN19ZX3F6MLDeJ0e61+9CpFc+pbHyDirY2QvNe7YOt9/nOl6R32fgFwvWbyLiHO+MRc0f1vPglZV8mzt077rxPp8b/s9AX7q8TOCN1sxrlwrFSiV/posnP5W12TqPv/sW3UftbjmT5T3PlyTmPHL+BbTHnvQan2qZ/bMvyMlK9easg7V62TJAS/rJP1zBE5WvycwDcNyVjpksf9IbHfGMdy2Y7UzjhW2HYObUQxx1mO+/8HencBFVe0BHEfFFVRUVMQFcM8V3HFFwR0VhRQVHbZRkG1kcU9x3xX3vVCxtFzwpYZFxXtpWllRz3xWmtjyMjMjU7M0fb+B/wx3hhlkiJb33tzP5/RtcM49/3vu3Htn7vzPmd87h9t0jrv5XHbTudqW56ZbmqNsOoc=
*/