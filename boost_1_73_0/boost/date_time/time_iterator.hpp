#ifndef DATE_TIME_TIME_ITERATOR_HPP___
#define DATE_TIME_TIME_ITERATOR_HPP___

/* Copyright (c) 2002,2003 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland, Bart Garst
 * $Date$
 */


namespace boost {
namespace date_time {


  //! Simple time iterator skeleton class
  template<class time_type>
  class time_itr {
  public:
    typedef typename time_type::time_duration_type time_duration_type;
    time_itr(time_type t, time_duration_type d) : current_(t), offset_(d) {}
    time_itr& operator++()
    {
      current_ = current_ + offset_;
      return *this;
    }
    time_itr& operator--()
    {
      current_ = current_ - offset_;
      return *this;
    }
    time_type operator*() {return current_;}
    time_type* operator->() {return &current_;}
    bool operator<  (const time_type& t) {return current_ < t;}
    bool operator<= (const time_type& t) {return current_ <= t;}
    bool operator!=  (const time_type& t) {return current_ != t;}
    bool operator== (const time_type& t) {return current_ == t;}
    bool operator>  (const time_type& t) {return current_ > t;}
    bool operator>= (const time_type& t) {return current_ >= t;}

  private:
    time_type current_;
    time_duration_type offset_;
  };



} }//namespace date_time


#endif

/* time_iterator.hpp
8i9id/P9LJe1z8WQtvucrt4yNmucxt+VJ1OFJu+13m/3kPSLpN4XNWSTJX/PTU2m3vPGeVUx87huG5585SVuxU1FHoo0zI0Em+wZ513rmPOrLm+Pypggrh3WdLpZ/FTPjtWLRX6geeBXjHMvSgybxYnn7DHGdeuLj5Ivpa5oZqrHuicyzh1pdjLe/SA13zPefUX8+Y+MeeuqS8okbC1sPlog8o5al0TT4pBIshkYvD/YNuHt
*/