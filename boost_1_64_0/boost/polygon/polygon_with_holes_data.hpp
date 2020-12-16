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
USIoWykZlByKA5OjuS+zjj2zLtbFulgX62JdDJY/I/8/L/tDsg5LKf//Kwcb/W8IJMp9/zTJ40il9NF+iRinyD3JD0WCkJ8Q+A1zvitz/pRztidERE5K1OVdyBz65PMY5KGEST6VLv5O8nZlq8S/kXKP9ftpCsefn7+oCotQh0XZlGL8t03E/+Ax8XeQPJpLuvmisCqexL7a/Pup+XPthyQmJIV26RSqtiCXU9vuNA/Jn9I97lCQH1hL8gt1cTXhcbT8e67usYdyrnzzOR6mc13M536YzpmxPKfF0lyR3zsHprRySEznxlies2E6V8R8Dozp3CRzOUill+tyKy/XpeZ7WTtiIq9mRn1ZPSoxyH6/5TktpnOoLM8Ryr83Juc/TDNxb6yn3Ivqg07YF9thP+yE3tgdfdAL++NEHIiTcRDOwcE4F4fgEhyKq9AXU3E45scj5zPcaiKeFhJPK4mnjcTTVuJph0OwPY5EDxyLHVCFHVGNnXAadsZZ2BXXYjfciJ76eOT8JOct43iqSzy15LtcR/mOtQ52xnr4JDrjRKyPc7EBLsZGuBld8Bl0xUPohiewCZ7Epmhja+6+lvLeV+nd45rTuexvus/1V7jHle5Txnqfy3qfq9Tvc/2R97g0y5hbiXLKer/KulgX6/InLbaU0N/l878mb/hI3kf+UvjMf83BRn6DsSDXz0nGOtahaD9T5UTlfebUaMeoFHd8e035zGk0tkXf1kFpa4x8PvenDKQtm+iCtoo7rr2OtKUbhyofi/Wfy8vxdxnaqb+vYC6uALlsLJe4FlMGE5dG4srrfNWkyFhLxtDyQDM1P05703HqY9IOjjQeQzspLonmDOIkv6TwvhpKnK4xBnGysx6/r4zjVI63TCkn339LfxylDKMdL4N2ImMTGP5m0b0TacvMmFzZ9vzf6zPZRzIWUJsjtooYh/N4ZV5Mcp/I6L6KcpselCv8u97D2Sb3WOU2EU18SGJcfMn6T7efwuWF21L6rynFrz7FoC1e6MV4nevuH5lqJ0cq9pB2ulL8aSfFsB167vHt6I7dkfUL9kk1Rf9zj8ig7UHyO/1VpD8rSX/mGLStHc362/rylLTjIdvYVtrJNWwnTlPMvixopxjnBckD7SVte2r/pn3NxCnb1s4+YPl5weS8Jcp7gxz/iTbW+27W+26//323J+pp//4w/nSPHd7Pze815dqbu8r4fPfn3ndzt5H3IOhkYuyOm4zdaYx1sIk+d17eT8AYZe6Y0ZgpR3TD2tgC62BrdMJe6IwDsL5i7JQ/NpJ2UigaaWe5tFMdF0k7amlnMjpiJDbAKeiK0dgTY3AUxmIgxuE4nIpBmIjxmIQzcDrOxRm4AGfhYpyN0m+8HzDdb8Zj0upge6mXRfGSeselXm08JvU6yPZ0xtrYBRtiV2yG3bEL9sCh2AeD0QsnYV+MQ29MQh+chwNwGQ7C1TgY1+JQ3IS+uA2H4Q4cgfvQDw/jKDyK/vrtp8Sa/43BubL987A6Jku9bhQ/qddS6tliG6nXXLa/BbrhE9gUW6H+txqkfg8Tv9WwUOovwfq4FF1wBbbAldgJV2NXXIP640DWW8XE9oyW7RmDlTBQkduYK/U8TOQ2jpd4gmR/TpT9qcJWGIJtMVR/XMl1D3sZHVfKsULrZX0bsAFuwsa4WY6vLbKdW7ELbkNP3I6Z5Yp3/9bkvVqz92nl/uyfdG/W1H1Z9+Vli3VvttB92VK8J2vp/dhVlFPFuAf7V7j3Wlr3XQvuucr9VuW9VuP7rKV4j7Xw/dU/PodQd2/Vi9dqECWRkkI5SDlLuUaxXcFc9ZSelMAV1nuv1sW6WBfrYl2si3WxLtbFulgX62I=
*/