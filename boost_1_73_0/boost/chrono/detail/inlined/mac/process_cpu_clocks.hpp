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
58MGsA1sBLvCxrCb+u+h9hc79m59nLz25PWxkuajMqwK04NOvayi4Tv79X0V8k4PJ/xwpIXfCf+64fzAzbAR3AJHwrfg1XAr/JPa36H6w3CbcdrzdvodurcN6VqO3li/GzhC9YlwO/pCuAPuhe/a/n3qH+60/fvUP3wPfZHozvnejf6t6nHkfY9898/RL4IfoN+u+nS4F32z6u/Dj+zjDDh6HbgffZDq4+DH6H9TfTk8gH5Y
*/