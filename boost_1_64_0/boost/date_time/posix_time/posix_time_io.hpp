#ifndef DATE_TIME_POSIX_TIME_IO_HPP__
#define DATE_TIME_POSIX_TIME_IO_HPP__

/* Copyright (c) 2004-2005 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland, Bart Garst
 * $Date$
 */

#include <locale>
#include <iostream>
#include <iterator> // i/ostreambuf_iterator
#include <boost/io/ios_state.hpp>
#include <boost/date_time/time_facet.hpp>
#include <boost/date_time/period_formatter.hpp>
#include <boost/date_time/posix_time/ptime.hpp>
#include <boost/date_time/posix_time/time_period.hpp>
#include <boost/date_time/posix_time/posix_time_duration.hpp>
#include <boost/date_time/posix_time/conversion.hpp> // to_tm will be needed in the facets

namespace boost {
namespace posix_time {


  //! wptime_facet is depricated and will be phased out. use wtime_facet instead
  //typedef boost::date_time::time_facet<ptime, wchar_t> wptime_facet;
  //! ptime_facet is depricated and will be phased out. use time_facet instead
  //typedef boost::date_time::time_facet<ptime, char>     ptime_facet;

  //! wptime_input_facet is depricated and will be phased out. use wtime_input_facet instead
  //typedef boost::date_time::time_input_facet<ptime,wchar_t> wptime_input_facet;
  //! ptime_input_facet is depricated and will be phased out. use time_input_facet instead
  //typedef boost::date_time::time_input_facet<ptime,char>     ptime_input_facet;

  typedef boost::date_time::time_facet<ptime, wchar_t>     wtime_facet;
  typedef boost::date_time::time_facet<ptime, char>         time_facet;

  typedef boost::date_time::time_input_facet<ptime, wchar_t>     wtime_input_facet;
  typedef boost::date_time::time_input_facet<ptime, char>         time_input_facet;

  template <class CharT, class TraitsT>
  inline
  std::basic_ostream<CharT, TraitsT>&
  operator<<(std::basic_ostream<CharT, TraitsT>& os,
             const ptime& p) {
    boost::io::ios_flags_saver iflags(os);
    typedef boost::date_time::time_facet<ptime, CharT> custom_ptime_facet;
    std::ostreambuf_iterator<CharT> oitr(os);
    if (std::has_facet<custom_ptime_facet>(os.getloc()))
      std::use_facet<custom_ptime_facet>(os.getloc()).put(oitr, os, os.fill(), p);
    else {
      //instantiate a custom facet for dealing with times since the user
      //has not put one in the stream so far.  This is for efficiency 
      //since we would always need to reconstruct for every time period
      //if the locale did not already exist.  Of course this will be overridden
      //if the user imbues as some later point.
      custom_ptime_facet* f = new custom_ptime_facet();
      std::locale l = std::locale(os.getloc(), f);
      os.imbue(l);
      f->put(oitr, os, os.fill(), p);
    }
    return os;
  }

  //! input operator for ptime
  template <class CharT, class Traits>
  inline
  std::basic_istream<CharT, Traits>&
  operator>>(std::basic_istream<CharT, Traits>& is, ptime& pt)
  {
    boost::io::ios_flags_saver iflags(is);
    typename std::basic_istream<CharT, Traits>::sentry strm_sentry(is, false);
    if (strm_sentry) {
      try {
        typedef typename date_time::time_input_facet<ptime, CharT> time_input_facet_local;
        std::istreambuf_iterator<CharT,Traits> sit(is), str_end;
        if(std::has_facet<time_input_facet_local>(is.getloc())) {
          std::use_facet<time_input_facet_local>(is.getloc()).get(sit, str_end, is, pt);
        }
        else {
          time_input_facet_local* f = new time_input_facet_local();
          std::locale l = std::locale(is.getloc(), f);
          is.imbue(l);
          f->get(sit, str_end, is, pt);
        }
      }
      catch(...) {
        // mask tells us what exceptions are turned on
        std::ios_base::iostate exception_mask = is.exceptions();
        // if the user wants exceptions on failbit, we'll rethrow our 
        // date_time exception & set the failbit
        if(std::ios_base::failbit & exception_mask) {
          try { is.setstate(std::ios_base::failbit); }
          catch(std::ios_base::failure&) {} // ignore this one
          throw; // rethrow original exception
        }
        else {
          // if the user want's to fail quietly, we simply set the failbit
          is.setstate(std::ios_base::failbit);
        }
      }
    }
    return is;
  }


  template <class CharT, class TraitsT>
  inline 
  std::basic_ostream<CharT, TraitsT>&
  operator<<(std::basic_ostream<CharT, TraitsT>& os,
             const boost::posix_time::time_period& p) {
    boost::io::ios_flags_saver iflags(os);
    typedef boost::date_time::time_facet<ptime, CharT> custom_ptime_facet;
    std::ostreambuf_iterator<CharT> oitr(os);
    if (std::has_facet<custom_ptime_facet>(os.getloc())) {
      std::use_facet<custom_ptime_facet>(os.getloc()).put(oitr, os, os.fill(), p);
    }
    else {
      //instantiate a custom facet for dealing with periods since the user
      //has not put one in the stream so far.  This is for efficiency 
      //since we would always need to reconstruct for every time period
      //if the local did not already exist.  Of course this will be overridden
      //if the user imbues as some later point.
      custom_ptime_facet* f = new custom_ptime_facet();
      std::locale l = std::locale(os.getloc(), f);
      os.imbue(l);
      f->put(oitr, os, os.fill(), p);
    }
    return os;
  }

  //! input operator for time_period
  template <class CharT, class Traits>
  inline
  std::basic_istream<CharT, Traits>&
  operator>>(std::basic_istream<CharT, Traits>& is, time_period& tp)
  {
    boost::io::ios_flags_saver iflags(is);
    typename std::basic_istream<CharT, Traits>::sentry strm_sentry(is, false);
    if (strm_sentry) {
      try {
        typedef typename date_time::time_input_facet<ptime, CharT> time_input_facet_local;
        std::istreambuf_iterator<CharT,Traits> sit(is), str_end;
        if(std::has_facet<time_input_facet_local>(is.getloc())) {
          std::use_facet<time_input_facet_local>(is.getloc()).get(sit, str_end, is, tp);
        }
        else {
          time_input_facet_local* f = new time_input_facet_local();
          std::locale l = std::locale(is.getloc(), f);
          is.imbue(l);
          f->get(sit, str_end, is, tp);
        }
      }
      catch(...) {
        std::ios_base::iostate exception_mask = is.exceptions();
        if(std::ios_base::failbit & exception_mask) {
          try { is.setstate(std::ios_base::failbit); }
          catch(std::ios_base::failure&) {}
          throw; // rethrow original exception
        }
        else {
          is.setstate(std::ios_base::failbit);
        }
      }
    }
    return is;
  }


  //! ostream operator for posix_time::time_duration 
  //  todo fix to use facet --  place holder for now...
  template <class CharT, class Traits>
  inline
  std::basic_ostream<CharT, Traits>&
  operator<<(std::basic_ostream<CharT, Traits>& os, const time_duration& td)
  {
    boost::io::ios_flags_saver iflags(os);
    typedef boost::date_time::time_facet<ptime, CharT> custom_ptime_facet;
    std::ostreambuf_iterator<CharT> oitr(os);
    if (std::has_facet<custom_ptime_facet>(os.getloc()))
      std::use_facet<custom_ptime_facet>(os.getloc()).put(oitr, os, os.fill(), td);
    else {
      //instantiate a custom facet for dealing with times since the user
      //has not put one in the stream so far.  This is for efficiency 
      //since we would always need to reconstruct for every time period
      //if the locale did not already exist.  Of course this will be overridden
      //if the user imbues as some later point.
      custom_ptime_facet* f = new custom_ptime_facet();
      std::locale l = std::locale(os.getloc(), f);
      os.imbue(l);
      f->put(oitr, os, os.fill(), td);
    }
    return os;
  }

  //! input operator for time_duration
  template <class CharT, class Traits>
  inline
  std::basic_istream<CharT, Traits>&
  operator>>(std::basic_istream<CharT, Traits>& is, time_duration& td)
  {
    boost::io::ios_flags_saver iflags(is);
    typename std::basic_istream<CharT, Traits>::sentry strm_sentry(is, false);
    if (strm_sentry) {
      try {
        typedef typename date_time::time_input_facet<ptime, CharT> time_input_facet_local;
        std::istreambuf_iterator<CharT,Traits> sit(is), str_end;
        if(std::has_facet<time_input_facet_local>(is.getloc())) {
          std::use_facet<time_input_facet_local>(is.getloc()).get(sit, str_end, is, td);
        }
        else {
          time_input_facet_local* f = new time_input_facet_local();
          std::locale l = std::locale(is.getloc(), f);
          is.imbue(l);
          f->get(sit, str_end, is, td);
        }
      }
      catch(...) {
        std::ios_base::iostate exception_mask = is.exceptions();
        if(std::ios_base::failbit & exception_mask) {
          try { is.setstate(std::ios_base::failbit); }
          catch(std::ios_base::failure&) {}
          throw; // rethrow original exception
        }
        else {
          is.setstate(std::ios_base::failbit);
        }
      }
    }
    return is;
  }

} } // namespaces
#endif // DATE_TIME_POSIX_TIME_IO_HPP__

/* posix_time_io.hpp
4GfXYowYk3erYP6VSwkltekow3SbS0odHmpoOxCz+oYrel1X/UAxeEUsHgWfBixW4G7xDFgrpS8ETTGhnp217C7ysEdoAhrb/RU6v9qe78nPD9jzvZxf9ZAqkJfl4yw9yY7u8ojT940QDJ0EpJYCjTRrsSvs2/sgh+pwKGhbQD4EcJ9WR92GMz4/45O8GJRGZ/d+OPRtY2D4PmL7K06yQK/5tRL7fVqJ/cQd4/hqtRajxP65hUrsSzy2UPJJaLu6c0b2EiRWVqgr/0b0yM7h5EAu2WeSR3AM7rDqBohZnpomgrxPQ5Ka80mKIUkY84cuDq5Mj5pISxBtc2mSe3aYyb9t4q8fIMOo0nPAPGMcJvYC9PNt8kCqdSCsftS61myocFvJSshkeuWv9S53XyKqQu835w/HtX+Y/SBnquWCKjDTStXqAk9Vbe/PXdp2w98VFCj6Lg6bwclTVKrcN5pGFakpeN3Fp8b4OmO9/o7RnpxegUEx5RIFjrPmNu8bAWzkQL7N+7s+FCDAlBgJkCYodjcU6wR1KmGIz8IVivq6GQmnLJ5kKhzWp+V7ElAnQY0DsYtgi6WLYh6jo5V5o5Zr84DYwOKTH6k2knNsHWt1LB+NFjWGMJ/34h3EAUiqxhJgaD5427b+zGVqUQkwq6vW7K0f4+oxoB8b+6vW/MujHz1VN7xJj9aSUbCmiIHyoGl/lEpRLL0Y0+OQHqd07XHBXtUp7VWd+nEf5cVmqb9tU6Cx+KTs5dfomExvfAFjMn30dojJdNZtEJOJvG2i1APzDUN/8xvN0GZgaDMwdJtCCMVnKRTL9qKneNXaddDtqqq6E1KP8eb0Lw9g/nV7ZCYy93GT+WXIJHcf6BMgpGOe6p8tHc+SoWs0jMswTC5oCYQSRbrgSDUlZjqJpi19TNIJBushHs5jiqaZvFHvBEWjYe0BL7AOgHNt89DTBFHfO4lR3wy1RCmKQx3MAQ/EoHedMDz4FmCgdNIC8e6VTmdU0+GP3xEt5qvaDyW1+UAb/PJW7RYYZGZMnKMEIOxs3vt6pV39OcZXa0X710h9wuMx7CRrqfoqwW4M91Hfhl/lfbfBV/nkzfBVxuwXrMOuSXqQfW0MqagUvA0AbzEpsJIVoFigkUClYW/KCgOZ1y7y2m15N4o8eGY8VZ2+MsuiIclTcFC5h53sdVSe+un+R+OiHEI6QTKFFjlEX0dhhy0bePMKrLHBEYuw93fDnlPQtqQss8kjbp4cBBUJQ0WCqUjkUeEZDBUNggrvIKgQcdWZimQeFd7BUPGoUPP4BkGFCC/OVMzLo8JXOhXebESMFans5oEFaVeLNHjOfFVFI8+NuHqPGXGgD6rqPAAS1BNJOprOZ6uRONuTGgN/vKmz4I+vauU6gPeM+s/J9LgO0JmvjN3pCvAUig/07Bs0IG/2/QNuyvKVCqVULuYYeJIZj9I+Wyo+0XyvZ4j4+PBQ8XHRrvNRQDmkVJ5mHlSao8xrfikCoywCD7eLwHb+4HzwgcE2yHxqYfzUGs2n1sifWqO78AvLT63X1oplynApe6ck/PMN/vmMf36+2BsM/sOl2CsJf5PB38T4m/IF3mDwPygFXkn4zzX4z2X85+aLutLxC1FH9uJ2MXja3QbU96SoW5sv6qJVaw/IJcBKk0QdOR2PgT9a1MVKF3Xt4ptwbU0poq4kQEVFXSEopXIxx8Dioq4kqksRdSUCKi7qSgJUVNSVCOWQUnmKog6/l/eEZ/me3//jz9kf0QP27/5teGhuJa66Ob5DVE0FKdJ9p0BFBFMC+uFEPHpDJGUKJuprBOi6g83pHT5U0sTzZvAolDMG0yhUhSQw/JqKT+iKiYWqss+n72s=
*/