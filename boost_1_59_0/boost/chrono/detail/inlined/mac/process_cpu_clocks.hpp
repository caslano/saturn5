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
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
*/