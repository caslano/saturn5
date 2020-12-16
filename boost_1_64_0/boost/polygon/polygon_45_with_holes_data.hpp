/*
  Copyright 2008 Intel Corporation

  Use, modification and distribution are subject to the Boost Software License,
  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
  http://www.boost.org/LICENSE_1_0.txt).
*/
#ifndef BOOST_POLYGON_POLYGON_45_WITH_HOLES_DATA_HPP
#define BOOST_POLYGON_POLYGON_45_WITH_HOLES_DATA_HPP
#include "isotropy.hpp"
#include "polygon_45_data.hpp"
namespace boost { namespace polygon{
struct polygon_45_with_holes_concept;
template <typename T>
class polygon_45_with_holes_data {
public:
  typedef polygon_45_with_holes_concept geometry_type;
  typedef T coordinate_type;
  typedef typename polygon_45_data<T>::iterator_type iterator_type;
  typedef typename std::list<polygon_45_data<coordinate_type> >::const_iterator iterator_holes_type;
  typedef polygon_45_data<coordinate_type> hole_type;
  typedef typename coordinate_traits<T>::coordinate_distance area_type;
  typedef point_data<T> point_type;

  // default constructor of point does not initialize x and y
  inline polygon_45_with_holes_data() : self_(), holes_() {} //do nothing default constructor

  template<class iT>
  inline polygon_45_with_holes_data(iT input_begin, iT input_end) : self_(), holes_() {
    set(input_begin, input_end);
  }

  template<class iT, typename hiT>
  inline polygon_45_with_holes_data(iT input_begin, iT input_end, hiT holes_begin, hiT holes_end) : self_(), holes_() {
    set(input_begin, input_end);
    set_holes(holes_begin, holes_end);
  }

  template<class iT>
  inline polygon_45_with_holes_data& set(iT input_begin, iT input_end) {
    self_.set(input_begin, input_end);
    return *this;
  }

  // initialize a polygon from x,y values, it is assumed that the first is an x
  // and that the input is a well behaved polygon
  template<class iT>
  inline polygon_45_with_holes_data& set_holes(iT input_begin, iT input_end) {
    holes_.clear();  //just in case there was some old data there
    for( ; input_begin != input_end; ++ input_begin) {
       holes_.push_back(hole_type());
       holes_.back().set((*input_begin).begin(), (*input_begin).end());
    }
    return *this;
  }

  // copy constructor (since we have dynamic memory)
  inline polygon_45_with_holes_data(const polygon_45_with_holes_data& that) : self_(that.self_),
                                                                  holes_(that.holes_) {}

  // assignment operator (since we have dynamic memory do a deep copy)
  inline polygon_45_with_holes_data& operator=(const polygon_45_with_holes_data& that) {
    self_ = that.self_;
    holes_ = that.holes_;
    return *this;
  }

  template <typename T2>
  inline polygon_45_with_holes_data& operator=(const T2& rvalue);

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
  polygon_45_data<coordinate_type> self_;
  std::list<hole_type> holes_;
};


}
}
#endif

/* polygon_45_with_holes_data.hpp
bIA9sRG+h13xL9gd+2AfDMBg7IuDMRDjMBgnYAjGYyjOwn5ofKZZvgthWWk37TPNiTloN9yGZXG7bK+7sCruxja4BzvitzgQj+EW5VkqTMZkPIMn8Bz+iD/jKbyDP+EDPI121OEsFsZzWBTPozG2X76j4DiKziq2v5Fsf42xDDZFT2yGTbA5tsCW2AlbYR9sjcOwDY5GX5mfaw5jT4XHsj8rxxsH2a7u21FPTMPi+Aw98TlWx5f4Lr5CPdrJdUsunIL2OB/z4UosiJvQAbdhIdyLRfBndMTb6IRP0RlLUpfiWAZdsBq6YkN0w67ojiFYDvVYASehJy7AirgK38Cd+CYmYXU8gTUxFb3xHvqgq/1vxrvJ+w2z32n4z8a9ZSXm7T853i37nYZZi3F7HfFtrzO2bWF/4tMoVygOA4j9o/SijKQkUPZTHlDcw7Ljy7I//52fP/X+f3DQa7v//5P6jj/zNa6z3JdwohR34XjAxQD/BUdFct8z0pifPSB08O/mYNPmNlff8SfdQRRtHuJlNt7hV4J5O7ranHdAPbvMv0/uN+avLruHHGpcZP7FZdm9bM2//+/nn8vMvE3LnpDT9rL72Z73a1v2xjJ/51zWuagpzF9na/5hMQHDQ6OjsvI+P6mDRXvHyzzLyzw9pL0TbM0zXJ/lef1Ge7NzWr2vUZY3yda8I2KC/uiymuY328Y7/NyV/crW/GJCw0ODf395ndT5Gd+lBrLMlm3gmME6ryr3xN2lTm6UMsr+VjLDOmVquzPVy8NGvTy09ZLuIKv7zUlyn20nI7jil3iSyjUtqblXHxQst0blprnUq2EuzfH3d+5TplRMf28n2c14z8xJc88tIiSA227sj6a2VPsFxIQNDzXmLpf7vpJF29DPVfrJLXXD+zLcZV0o/QJ04bExyr0w42TsqvB3D1t/N/5DFxgSwrHbOLBSF0+Zvja2QpnHGzINc/8Abgv215viR6qijsJuTFsO8TE8t0z/li8M9wRZNhle6mXI4fucvxnvcxnvnsXIvdXn6v0uwzR81WkYBzNMQubbjb/95Kb8TYJnZL7O9D9r6C9hBNGBQ025XqvyNw9Hw99YLcbh7elnWr7QSFZEv34xzN6Yt1nqabpX3EGGDZPuhtI9UKb/hnQHhelZIuopcTTByv03ZqC0uqn/6pfG/v3ComP0xsUz1Kce07hgrL+eDMsxymulTMvmYZy+bBfm9VCev9Xlb8p6kMZmdQSF9VeWKCwwUl1+uQ9LVZQNztDPS21jY+sq87GTfkMCoxk7OFRWkmH4JGmTMEIq4gKCDNuIowxv2ACUhZSqmeabbDFOIPMwx+dIfYOG6UNjTMu5X4bX7BcBsdLmnjKvQTLsKdOwgXHK1i0Tkvezyd+Yh6GeDi/M2x0bTbSePUCWzZAr2UvJS5ff+K6c22XZn2Vd5ZPxoshUrYRtyX1UdZwOBdjxOeceK8c4praW9WuYvEynhbL9GfYV2Z4Djf2bW/cPMuZunk1dfAsYczLVLW+uT1l1eBqbrSdY+pex7q+raWiHrtJfjo1qvmY7WcYLkq/Zw8Oye7RV909W3W+Ws+weY9W9uYJl9xHpPiv5oFub8uPLPf8Queffl3KRYbzetDhGy8HZdKiOidXpyBIcGpLpe/9yPLZ817PMe6jEI8XgGYZLNM6bVxHVDIgIqW0+mGQh1iCXfYbHf/V+/2XmxfQt6hQn8QfNJG62ESp1in/LXCeu5muaK/V66mTK23yVeSnTt7M6x3vKO03Xy3pKpCj10lW3qJd37TrmmmUlduv36pZG3a4xP+M8rN4rZFXXpEIyA1mvo2W99q1hUdfaNb3/vLreYH7GeWRUV3nPXRE=
*/