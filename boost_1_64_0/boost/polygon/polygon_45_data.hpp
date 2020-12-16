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
I2mHL/WVpimr/fGjENuE7fvetcc8uX6qE+NooASNcpdjWmk0PS9q1JQpNt1oSJ6c9CB1pte226fbPvuZkq62ZZv9xi0pW0+pr+6keazb/HS1bKYjVWHqyH47PeShv50q5fop3XYbbDrJ/H2nr205z9eQckoddsXdjBM0yVLOUFpc3KQoN1eeIS7lGTNZPd45bYOm82HmyTmonHPLsPQIZZDNOUJKYpqySDZtk2E2zyOnTrKeQzxchb8rJ/d254Mh8n7//rKt9SbtVc5/JluXMzbUmByaQhEK0VbkXF8tX1u5pq/d14yV9/LXlDr2xX1KHWeoeUfHJSSwdXPRPjSVrT05sTDvs9fbxgmDxWvTbeITUa40Tttt39NP5arPcpunSzKYTuzld85Y6i2E8i/i+z+U8qLtfkLWl9wbCGZSqXubfV2uvNt/kdx/mY8HfBk+Ra2DGHa3qcq+VmJz8a5/pSZdexf96an3P89yR2k7ap1o25e3pk6U3x+hyojqPRXNfQ+plzDqZI2f+X19N6Y41otRPa+VekqLZ47mfK5L22aYZG/b5hmu/jZTtt0007JxjJJntd9Tv9ueJ8fKu/4XSBt/ipSrtPFpDnVsbuYu3YNjm55uX7eyvSba/8ZlnurvUMdtke3B5n38N6Sc10jvUM7s6frlDI1MpzG7tv+Z+qRDWeXeuLnu86WOTbMMjU4Ij0mT9aRdBvktpf0trr9Mat3nyjItcpP2TXqXZcp7UrNMxlCaUDJ7/djEloXYx6jbt+Y8lRm1tC9DQF3HGISvKucTM9QypCWnqufPXF0u+Le70t6WyzPRH3i72cTrWl9XP15XjjL+H4zXtVvy3G/XH0G/34Hz58D1+xcU/rl6/f4Lzp/z1++n4Px5eP3+C877C+j3Uyj88/P6z+0770eg39/BWf+Fwvcv0O+nUPjn+Qvb70O/f4ez/g6Fj6O2t7Iy/Hb/y2vn3Qh+4sk9Tw0KGNt5mPN+Lua4NfLcFjYm7bGLW7O+DM/x4washBuxKm7C+rgZ1Xf5ynwqkxrYxfnpW0LzLl8Zz7OA8fJdnJ/HAOt4XYs7fzdwgIxXRsZz+i5fdX73Hy/MhfECSJkyXm3SHrv4Oh3LyjsasRZ2RkscoByZLkym08YBWubOesHl6IUrsRmuxk64BrvgizgA/4aDcAOOwi04FrfiTUwpJs+pyPMr5GdqDwZ5nu5eOfLDf6EX1ixPfwashV3QD3thbeyDdXAQ1sXhWA9DsT7GY0Ncio1wAzbFPGyOJzAA48m7FaZgG5yBbfFZDMQ12B43YAfchp1xN3bBXOyBp7EnnsM+WIxlG4aP4HDsiCOwO47EPhiCo3EUhuEYnIXj8GkMw00YjtswAt/BSDyM0fgZxuA5jMOLOAG/wnik3vmtK8+vILeRqHfzsW6N5d1q0j6qYwWsgQ2xJvbFWmhEP1yGdXET+uMBrI8fYEO8io3wYfJpijWwOTbEFtgSW+NgbINjsC1GYaC0y3ml5DkYeS5GKe82/j2tlPzGY7xy2Au9sA92xn7YAwfgMByII3EwRuMQnIRBOBWH4QIcjovxcVyNI/BFHI0bcAxuxbG4HcfhRzgeT2EYXsZwvIYRWIrCR6I7RmFrjMFhGIvjMQ6jMR6nYgIuwERcgsm4ElPxDUzDvTgJj+BkPIHT8DOcgV9gJv6KM1Fph7PRA+egN87FFvgUBuI87IPzcRAuwGB8Bp/AxTgDl+J8XIEbcCVux1W4F5/Hv+NqPIQv4Ce4Br/EtajsmNbhw5iNLfFvOAhfwmBcjyNwAxpxI07FTZiJr+JC3ILL/s3efcDXdPYBHA9iBxEhEUEQtGpEYtbeMUqsir6ILISMK7k=
*/