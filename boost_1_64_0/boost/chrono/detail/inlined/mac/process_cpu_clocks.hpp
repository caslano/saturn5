//  boost process_cpu_clocks.cpp  -----------------------------------------------------------//

//  Copyright Beman Dawes 1994, 2006, 2008
//  Copyright Vicente J. Botet Escriba 2009

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

//  See http://www.boost.org/libs/chrono for documentation.

//--------------------------------------------------------------------------------------//

#include <boost/chrono/config.hpp>
#include <boost/chrono/process_cpu_clocks.hpp>
#include <boost/assert.hpp>

#include <sys/time.h> //for gettimeofday and timeval
#include <sys/times.h> //for times
# include <unistd.h>

namespace boost
{
  namespace chrono
  {
    namespace chrono_detail
    {

      inline long tick_factor() // multiplier to convert ticks
      //  to nanoseconds; -1 if unknown
      {
        long factor = 0;
        if (!factor)
        {
          if ((factor = ::sysconf(_SC_CLK_TCK)) <= 0)
            factor = -1;
          else
          {
            BOOST_ASSERT(factor <= 1000000000l); // doesn't handle large ticks
            factor = 1000000000l / factor; // compute factor
            if (!factor)
              factor = -1;
          }
        }
        return factor;
      }
    }


    process_real_cpu_clock::time_point process_real_cpu_clock::now() BOOST_NOEXCEPT
    {
#if 1
      tms tm;
      clock_t c = ::times(&tm);
      if (c == clock_t(-1)) // error
      {
        BOOST_ASSERT(0 && "Boost::Chrono - Internal Error");
      } else
      {
        long factor = chrono_detail::tick_factor();
        if (factor != -1)
        {
          return time_point(nanoseconds(c * factor));
        } else
        {
          BOOST_ASSERT(0 && "Boost::Chrono - Internal Error");
        }
      }
      return time_point();
#else
      clock_t c = ::clock();
      if (c == clock_t(-1)) // error
      {
        BOOST_ASSERT(0 && "Boost::Chrono - Internal Error");
      } else
      {
        long factor = chrono_detail::tick_factor();
        if (factor != -1)
        {
          return time_point(nanoseconds(c * factor));
        } else
        {
          BOOST_ASSERT(0 && "Boost::Chrono - Internal Error");
        }
      }
      return time_point();
#endif
    }

#if !defined BOOST_CHRONO_DONT_PROVIDE_HYBRID_ERROR_HANDLING
    process_real_cpu_clock::time_point process_real_cpu_clock::now(system::error_code & ec)
    {

#if 1
      tms tm;
      clock_t c = ::times(&tm);
      if (c == clock_t(-1)) // error
      {
        if (::boost::chrono::is_throws(ec))
        {
          boost::throw_exception(system::system_error(errno, ::boost::system::system_category(), "chrono::process_real_cpu_clock"));
        } else
        {
          ec.assign(errno, ::boost::system::system_category());
          return time_point();
        }
      } else
      {
        long factor = chrono_detail::tick_factor();
        if (factor != -1)
        {
          if (!::boost::chrono::is_throws(ec))
          {
            ec.clear();
          }
          return time_point(nanoseconds(c * factor));
        } else
        {
          if (::boost::chrono::is_throws(ec))
          {
            boost::throw_exception(system::system_error(errno, ::boost::system::system_category(), "chrono::process_real_cpu_clock"));
          } else
          {
            ec.assign(errno, ::boost::system::system_category());
            return time_point();
          }
        }
      }
#else
      clock_t c = ::clock();
      if (c == clock_t(-1)) // error
      {
        if (::boost::chrono::is_throws(ec))
        {
          boost::throw_exception(system::system_error(errno, ::boost::system::system_category(), "chrono::process_real_cpu_clock"));
        } else
        {
          ec.assign(errno, ::boost::system::system_category());
          return time_point();
        }
      } else
      {
        long factor = chrono_detail::tick_factor();
        if (factor != -1)
        {
          if (!::boost::chrono::is_throws(ec))
          {
            ec.clear();
          }
          return time_point(nanoseconds(c * factor));
        } else
        {
          if (::boost::chrono::is_throws(ec))
          {
            boost::throw_exception(system::system_error(errno, ::boost::system::system_category(), "chrono::process_real_cpu_clock"));
          } else
          {
            ec.assign(errno, ::boost::system::system_category());
            return time_point();
          }
        }
      }
#endif

    }
#endif

#if !defined BOOST_CHRONO_DONT_PROVIDE_HYBRID_ERROR_HANDLING
    process_user_cpu_clock::time_point process_user_cpu_clock::now(system::error_code & ec)
    {
      tms tm;
      clock_t c = ::times(&tm);
      if (c == clock_t(-1)) // error
      {
        if (::boost::chrono::is_throws(ec))
        {
          boost::throw_exception(system::system_error(errno, ::boost::system::system_category(), "chrono::process_user_cpu_clock"));
        } else
        {
          ec.assign(errno, ::boost::system::system_category());
          return time_point();
        }
      } else
      {
        long factor = chrono_detail::tick_factor();
        if (factor != -1)
        {
          if (!::boost::chrono::is_throws(ec))
          {
            ec.clear();
          }
          return time_point(nanoseconds((tm.tms_utime + tm.tms_cutime) * factor));
        } else
        {
          if (::boost::chrono::is_throws(ec))
          {
            boost::throw_exception(system::system_error(errno, ::boost::system::system_category(), "chrono::process_user_cpu_clock"));
          } else
          {
            ec.assign(errno, ::boost::system::system_category());
            return time_point();
          }
        }
      }
    }
#endif

    process_user_cpu_clock::time_point process_user_cpu_clock::now() BOOST_NOEXCEPT
    {
      tms tm;
      clock_t c = ::times(&tm);
      if (c == clock_t(-1)) // error
      {
        BOOST_ASSERT(0 && "Boost::Chrono - Internal Error");
      } else
      {
        long factor = chrono_detail::tick_factor();
        if (factor != -1)
        {
          return time_point(nanoseconds((tm.tms_utime + tm.tms_cutime)
              * factor));
        } else
        {
          BOOST_ASSERT(0 && "Boost::Chrono - Internal Error");
        }
      }
      return time_point();
    }
    process_system_cpu_clock::time_point process_system_cpu_clock::now() BOOST_NOEXCEPT
    {
      tms tm;
      clock_t c = ::times(&tm);
      if (c == clock_t(-1)) // error
      {
        BOOST_ASSERT(0 && "Boost::Chrono - Internal Error");
      } else
      {
        long factor = chrono_detail::tick_factor();
        if (factor != -1)
        {
          return time_point(nanoseconds((tm.tms_stime + tm.tms_cstime)
              * factor));
        } else
        {
          BOOST_ASSERT(0 && "Boost::Chrono - Internal Error");
        }
      }
      return time_point();
    }

#if !defined BOOST_CHRONO_DONT_PROVIDE_HYBRID_ERROR_HANDLING
    process_system_cpu_clock::time_point process_system_cpu_clock::now(system::error_code & ec)
    {
      tms tm;
      clock_t c = ::times(&tm);
      if (c == clock_t(-1)) // error
      {
        if (::boost::chrono::is_throws(ec))
        {
          boost::throw_exception(system::system_error(errno, ::boost::system::system_category(), "chrono::process_system_cpu_clock"));
        } else
        {
          ec.assign(errno, ::boost::system::system_category());
          return time_point();
        }
      } else
      {
        long factor = chrono_detail::tick_factor();
        if (factor != -1)
        {
          if (!::boost::chrono::is_throws(ec))
          {
            ec.clear();
          }
          return time_point(nanoseconds((tm.tms_stime + tm.tms_cstime) * factor));
        } else
        {
          if (::boost::chrono::is_throws(ec))
          {
            boost::throw_exception(system::system_error(errno, ::boost::system::system_category(), "chrono::process_system_cpu_clock"));
          } else
          {
            ec.assign(errno, ::boost::system::system_category());
            return time_point();
          }
        }
      }
    }
#endif

    process_cpu_clock::time_point process_cpu_clock::now() BOOST_NOEXCEPT
    {
      tms tm;
      clock_t c = ::times(&tm);
      if (c == clock_t(-1)) // error
      {
        BOOST_ASSERT(0 && "Boost::Chrono - Internal Error");
      } else
      {
        long factor = chrono_detail::tick_factor();
        if (factor != -1)
        {
          time_point::rep
              r(c * factor, (tm.tms_utime + tm.tms_cutime) * factor, (tm.tms_stime
                  + tm.tms_cstime) * factor);
          return time_point(duration(r));
        } else
        {
          BOOST_ASSERT(0 && "Boost::Chrono - Internal Error");
        }
      }
      return time_point();
    }

#if !defined BOOST_CHRONO_DONT_PROVIDE_HYBRID_ERROR_HANDLING
    process_cpu_clock::time_point process_cpu_clock::now(system::error_code & ec)
    {

      tms tm;
      clock_t c = ::times(&tm);
      if (c == clock_t(-1)) // error
      {
        if (::boost::chrono::is_throws(ec))
        {
          boost::throw_exception(system::system_error(errno, ::boost::system::system_category(), "chrono::process_clock"));
        } else
        {
          ec.assign(errno, ::boost::system::system_category());
          return time_point();
        }
      } else
      {
        long factor = chrono_detail::tick_factor();
        if (factor != -1)
        {
          time_point::rep
              r(c * factor, (tm.tms_utime + tm.tms_cutime) * factor, (tm.tms_stime
                  + tm.tms_cstime) * factor);
          return time_point(duration(r));
        } else
        {
          if (::boost::chrono::is_throws(ec))
          {
            boost::throw_exception(system::system_error(errno, ::boost::system::system_category(), "chrono::process_clock"));
          } else
          {
            ec.assign(errno, ::boost::system::system_category());
            return time_point();
          }
        }
      }

    }
#endif

  }
}

/* process_cpu_clocks.hpp
uoyFNhqBE5/4aASkDJS9TgDxfXUCETtLrxNAWh+dQNTO0+sEKu/8c3UC7vKKshnLn7fTSycwAm3aLLAzHM+/ykYvMGNn6fUCiFuiXuCWneemF3DfN/Noy12Dc9YAF4ELELfQlVfXPZM1YuzkSQWZ+dlTMtGr5OCrutX3bqapp79ffyr+OYZ5DeWkMMwC9Xy/3in7Z8v+WNkva23KGumtOfdEFMLDFc6KLnJkgad8Xt6FtMhFkupilodsmySshopFDxCP8HiGfybhDokbz357hxmGkBDEriTHMCTuTgl/WGyTHVS67MM9LWmKZd8NsvpTN9R2vOos7e91Cf8HrMMVEObuI1hSXvdWC4mXotNVFX9f4zGkNG2ga3CSFWG4DrFlLolsEBbujA0LccbDuBWbGBWKf2KDNVxlVeAuq+5sR+UlfMLEa73a0XVyjvoSLx3h7n5nmLLacLHSJ7aNGyj3jyF9UJ7FN33UF/xSX3pejSgJ89RVks/96S4PjtXeRbt9ZY6lo78Cv/dn0l+J/on0V6O//W6XfyLT96W/gt9Yu4t4g3ejViHdrVWQ+Gzf2fj5zbfRK0i8Zr56BQmL1/YU44xtV1k+eWxejnOBO9FXkAuwZ/aHnjxStmN13yGe71qPG8U/11nkcNrpdpimvu1aj2/L/kec7zgiaV9iGvu1Hrm/rtbtrBL/U86PHKH87ZB2OzF73MS8gswpWWL7wb0wGlwncec7/fQ9ur9bv821PlIl6n2WS/znnfeYmgdUwAeOWOXXz2gb6csSd4lzryPE6v6U+3EYWGO7ay2kSJVZ4n08T+JV1+muF39F9BHRkodUT1+m7/WhEqclUkVbHjuJx2ok8bJxRT3VKHWoxLidJW5fI1w1wTfAV+Tc1d3nZry0wHh6LqMitNstpkOB7oLbBvcp3Ba2Z9wrp9VNndjhq5uaDb9bNzVlh9Y2pSmGXaPDWrRxh+V4wlq7w5QnrKk77MftWgul037uCdParI88YVqbVeQJa+IO64kw/3lEvtkWOGfIF56wFu6wVZ4wfbxbdFhTfbypnrBW7rA8T5g+R1NPmL7ee7YFrvtZ3xOm09bwhOn8oc7dYfp4oZ54Os/HPgyc02TaDl+N2TC//n+0CtSY5VlozKb6acwq+aT17QeS5Dx+vxX24frZL9X9O3QOx6juPgZ/my7Y7vvbctF239+myfQP5v47/PY33+GbfqD2+/42hcd43lli4Aa41yX82KvfFymd9W/TconXw/u3iWnjZW6E1uVwj5vOfJ6oJutfdsejhDNUKe/fLi/NS+nWYLT4LdPPkwd5Ta3hovnOWBPlkv6p1zVBepc5vmBy5sQpOfmjReqi+26DfTevh+niLdcFjjPzK/srqFDllGc2dx89UsKd+jq3JJZey1NO2oPkw6e+Cvmk3ZH11Yb1leFVX5Rj+euxdJ0Nl7gNVRVdZ0yPGFbPyd2xf7LsT9TXcrwUdSTXYj/PByJY67nSvJ85RNJlr+lCXHtNl+y313SN+dCj6VqBtIvjzlzT1eXDkjVd6R8Garq2nWdNl7s8ExP5zsf3qFCDc3Bs9ZSnyLqsn+EYr5V+dzop/gN2a1AyfnOt3/xR/Idt1p9kfL6bTYD/qPiPS/z3KoleNCcnX7972a5TOfIDmYMnsK3y2fMrOe6PTK/rRI6LMtXPHhtQD7sTsZdzhL0Ff3O4Hayf0WfwfjLb7/dpngrUhC1UPpowXZ+4doTJtft9T5B8S/9dRq4ZWnb254Ppr8P+/gX68yv5vlunl1eyTeU9Nkm53q1nf+rTJibl+LxaW7YPpqlJv6GcYjcOtayHDMR/SuKn06/j2zzXdpZ3w8OSprqUf+szmFM=
*/