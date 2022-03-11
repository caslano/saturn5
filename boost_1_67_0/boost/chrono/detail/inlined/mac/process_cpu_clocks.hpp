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