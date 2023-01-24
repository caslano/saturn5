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
DO3KH5sg20evJMPwu6h/bAwOW/uPEbhlxyZwQiNDWI6Z15g2ZStMVEOHh4+zK2qQDs+7keO2592IBcgjaJ0970bQERIwyGl980hep4RbgMaRgQU0E7Gmm8DUQXYT7XiEHCJ5MkJgrEGdlvvITtIPnP3A7yHHyAAcD4NkiIwCl2R1/R4yDBJdexxiVZi2AXME5FRnM/A2QT0P1iagHIOY5ABa3gDUOFocQRmz3K5bvghsDMP/xBbq/J1A7yNkvo7fRY5DC2H9C3bgwgHqMPxvFKTU7yAh3TqStnEc5Pvgf0PQyiHO8iGyF1tJe0A8NxI/Ci0dBhRtOSmnre9H+9TiIHCPEeLbhNmdp17/rkUf+NH2dffW3F8063+Kf08CKUlSw34ixWJQxOMBIsfjcV+KSFRS2uRPSUVFSkqWi9QOhchFRXW1cl1tgNaKsKxViA/K2iDx0wOQoKWuipSXbpXK1ZSUIIp2kJVQUDE4C+DgU9RaWQnICZqSk0ub0JtU5CMk5KsDZkqW4BCSiyVogFQshQJwKCqS6wIBaiUk1/nluqBcp8h1YbkOyKhcF5HrYnJdXC4OhFOSrLmj1hME/KVIKEBI6Ym3gOmiotITbwtBY0/cBBUQwVkC8Q6fdigKEdRJYA8VY28kSBlhJvkyRFglQA+RYvDGi5EbAKtSiVpLT1BGjh/LIJYKlmEsQ1hGsYxhGYcL4/dDodAkaSgE
*/