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
FwsxQMWuaQY8dc10yPR5rE6aDbQsgjFYfar90/EyeX3uyyQbpDFY5bn+TWZz2IBQDY8bZ/66kiGI2dxL4yO0yCxoJUM3lP9K+Po6nbMcRnPPHF3VrRvT/Qw06hBWz88qahwlGzONk2LapH5KpAdrGhovXx5bE8RhHt72Lyk3PvuuGCWo54FZpssOkULhnMEMxZ8ehK3EGU/celnIkJWMLKs/svAtVHDayfO/Qea+uzasPAyaqq5bJsGMndWt+ZgeMJHmubZ0ilmOLOnusVICGZWSGcfanqBOwf3pIwdEVNL9qdc98NBWU+sh+2WFbJkfcr8n/Nlq/1JBU9N9/GJBPMzLYSiCm1fl/kYqNB86hr2UJRgRYE23zQ415Is1lyuYrvUYMmc2efRr5VLS9PPxCDGBygCbKzHz2W6bmCcnvRoKQCIzjaJaBulESis1h6d/Z3GRoplUtwd0vYQftV+0MgL4ufZ+o780cW7HSqp7ekp9ORZNeCwmzvSZ6a/dAnf95L47QlQm/etkZ/8HIIal2g68mM4A+K4IEjnJ7muFzU6vrpE4diyAsx63Kg==
*/