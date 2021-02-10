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
tD+ErcrFmq5IES5W9aoUpghvwkKHMu8rDYaXZQOHpoIbnwKHpGErpJ1QYfTC0sUoacjbVaG2dzYirQ3QutYS3SEtuC9XSHwItcy5dvsdEQcvDcuO8m+U7Cb2HJTEqKAVJTBMWrBiRpgQLobp2WSewkU0m0Xj9BImpxCNLxu898PxCWpDoFcN/FOlucEoNIhtVQqe33H+XTs96KVnMJjPRpNpujxL0mQWRyen8/EgHU7G8BxaT19Awiun7xa0SrEiAcDL3ssXPVqgX0vOzH5puKVS4xdVZRA4OYNxdB4HX0VfHKNEWQ4ZK8sVyz7CGjOmXVAoY41DSC7Hk2kyTIIfhMzKOufwhlx6GRZvA4eOJpnCRwVaEWKbFqFLYYWAdalxIrlAaQOXVu+hi3ch7JTIoYvS1FXnZ4/lgO5n1QAWKLYSNfe1jMLrCBCNoo9/n8az4Xk8TqNRcMFQeHLz2vfgmjNbe+1wpss9OMekZlzZMv3R9y1qgWuxxaBxasAQ80BpKVnugxUHLqk7c1jtaR9ODWERyGLToB8ElGuxIR9XqCtYrN8dH3uLYwpzsZ72XJOiggOW74TxLSGVxSkiKh8mDp1KqxwZxKrCimOJuOuN24EBTgkce9himm/VzukVsz+Jk8FsOCVmgilDQTOo
*/