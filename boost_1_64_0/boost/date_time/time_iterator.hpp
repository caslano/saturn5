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
dJ/wD0nQj7JCD3YM/R0VhXPed4dAWTn0HRtQ2TKCqTwSoLAs9knjLpa1Uum/e8i5pnxTuvShPJm2JmYf2dqF9LVp0vMI2TpFm5+VjY0+IfO9CAGUYHLUXsWa84WRCcsn/WSGAEWD6A45g+VKaa+lKJcpApAiIA1VeG0hPgL0kbn6PiN+te1UrqjkrKl4wSvnkViYTUzImTkGifN3+FQLUYkHxqar6ZyXKEwXj3XGjv1NLV+CREFxI5Katb1INbWkyVYN0v880SAZIZzGP/XzkzOYir08FUvXnVseUVPx+eb8F5RT8RcdTcWHpJCWecJzdDYR35E0EctLEI4mRGZbEXFJRGLnySroc7DXvJgEbstUvDSrkhMAL6wV6A6TM3QSuot+5Pk5sRGzT8mgEYtEI67jRsz7rWrECxTtNh8lG/HbHZGn7J014z3JzbiRUZn/MDejBZVKiUos1KE8VdRRW9bItqzJQNq67MdrTX08CmZejZ9B16bO4z1p4v2bkvW5alHzeq11UYNkCMiVzWsHd7ohbi0OS4Mz5XmmrjJ9etDrbEpb//JNneQv3tQ5/EGb0uC7z8ZNKebH1hP1Hf1WniikQsHLa3og0El1NHPQLVwo39pRedDEwsejD5Dy4ODLQXnwDajBko/c8TqXbtnnCGnEtoPmYLr+j/Fn4eeW6aIZM+Efz0xK1KxU2ZKGf0qm4hFM5U0eyY+uVUxlphrJPz9CMhU8c5wBG8nqIhv5Cxc+mgqfbS38m8r0bMST8ZTQGRtZ+GOykYT9oi8nUoNG3t8fRYWCtTeBF/qXhsP7s87b4B0fCDZOheAWDv5sMgRnsEmk9bflXEgHsrq/MmUH5A53AmeFEVPtMHDEzIXiIwVTyDdEfth5IXwiCU0v1NpCaRA392W/UUuT6ab/44D0iFlaHS4YDGDoQgNh8Flwcuv+RmTlZHa7a3rOLNvxZtLoMf94qpRaibx/n1yJTD1b0CKNPiuYRl9V3nV9liU+kCbelybemya+aEf0cRYH/xUTBA33ZRreci+smWsw5pI9LbsKoQEkPdPBGJdFkHZlLsx3PP8E2Wwp4/TlXUzv72L6QBfT+7qY3tvF9EVdTO/pKD03+5E1zK+ePwQb2XlW7TBgRGNOgx++zcnLc6XkuqqBO+R/xzK8W2GENzuLERwOvwzkaULnUc6uGew90A9C9MMaPs1KbW9kez5hrwf7buY542zaDimNvZLS/vNw3dBvH1+X7Cg7xf+rn1nsPbV6RAozrEdVfsb1OH+KXo9T9tuhenS0vi7hqrCRz9pcRqqKCjAX8wd/Fycb+wxkqKT9benT4anxSUaIdbpPxnpZQLwN38DwrnghGd5NcLDhXTHML00GG94VOZxoePdOlpMN7xCqaRtt2JTDh/G55t69L/J0b9Ou2mdILIS9ZfTzLL5Ozc9ZbxfEiL6J4XTzmXvRRADNh8sv/yXnV77L0BX+bTY+X7TatOb2RJ45wyzVY2jawyIoCF82evi4oOmSdXbk3qHc6KoE8kaBfshWcxnXrpYK3+kCfp2wKI3+xmAkbY3jKlvu5uRTV+vuwkZClsqWezhqHERxoWv6mxrLIh1k7FSEZ28sFCdnXAvbXMLNlStWiXFZjcUC/JKV2NxzT5GVRsjBZgqN9cOkjka3GRPuAYdcYgMZfB8Ffus2CT56sl2QPCRLzzdLz4/JPPlmnvzovpBHw5/fVXk+01Ma7Wt7RbdxypQQ0wDLHAtR/2gTkSgXh4bj62wyJk3aDfLj5rlLc1noZc5K1/kt1cBAfxoq+1Ojj7tYyMuQ5ZKgXDovqwV1dPRfsmXTJv8Pe0cCHUWR7ZnMhMlBEo4Q0EgCRhyNRwQ=
*/