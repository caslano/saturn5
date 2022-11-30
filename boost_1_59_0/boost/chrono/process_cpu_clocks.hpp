//  boost/chrono/process_cpu_clocks.hpp  -----------------------------------------------------------//

//  Copyright 2009-2011 Vicente J. Botet Escriba
//  Copyright (c) Microsoft Corporation 2014

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

//  See http://www.boost.org/libs/system for documentation.

#ifndef BOOST_CHRONO_PROCESS_CPU_CLOCKS_HPP
#define BOOST_CHRONO_PROCESS_CPU_CLOCKS_HPP

#include <boost/chrono/config.hpp>


#if defined(BOOST_CHRONO_HAS_PROCESS_CLOCKS)

#include <boost/chrono/duration.hpp>
#include <boost/chrono/time_point.hpp>
#include <boost/operators.hpp>
#include <boost/chrono/detail/system.hpp>
#include <iosfwd>
#include <boost/type_traits/common_type.hpp>
#include <boost/chrono/clock_string.hpp>

#ifndef BOOST_CHRONO_HEADER_ONLY
#include <boost/config/abi_prefix.hpp> // must be the last #include
#endif

namespace boost { namespace chrono {

    class BOOST_CHRONO_DECL process_real_cpu_clock {
    public:
        typedef nanoseconds                          duration;
        typedef duration::rep                        rep;
        typedef duration::period                     period;
        typedef chrono::time_point<process_real_cpu_clock>    time_point;
        BOOST_STATIC_CONSTEXPR bool is_steady =             true;

        static BOOST_CHRONO_INLINE time_point now() BOOST_NOEXCEPT;
#if !defined BOOST_CHRONO_DONT_PROVIDE_HYBRID_ERROR_HANDLING
        static BOOST_CHRONO_INLINE time_point now(system::error_code & ec );
#endif
    };

#if ! BOOST_OS_WINDOWS || BOOST_PLAT_WINDOWS_DESKTOP
    class BOOST_CHRONO_DECL process_user_cpu_clock {
    public:
        typedef nanoseconds                          duration;
        typedef duration::rep                        rep;
        typedef duration::period                     period;
        typedef chrono::time_point<process_user_cpu_clock>    time_point;
        BOOST_STATIC_CONSTEXPR bool is_steady =             true;

        static BOOST_CHRONO_INLINE time_point now() BOOST_NOEXCEPT;
#if !defined BOOST_CHRONO_DONT_PROVIDE_HYBRID_ERROR_HANDLING
        static BOOST_CHRONO_INLINE time_point now(system::error_code & ec );
#endif
    };

    class BOOST_CHRONO_DECL process_system_cpu_clock {
    public:
        typedef nanoseconds                          duration;
        typedef duration::rep                        rep;
        typedef duration::period                     period;
        typedef chrono::time_point<process_system_cpu_clock>    time_point;
        BOOST_STATIC_CONSTEXPR bool is_steady =             true;

        static BOOST_CHRONO_INLINE time_point now() BOOST_NOEXCEPT;
#if !defined BOOST_CHRONO_DONT_PROVIDE_HYBRID_ERROR_HANDLING
        static BOOST_CHRONO_INLINE time_point now(system::error_code & ec );
#endif
    };
#endif

        template <typename Rep>
        struct process_times
            : arithmetic<process_times<Rep>,
            multiplicative<process_times<Rep>, Rep,
            less_than_comparable<process_times<Rep> > > >
        {
              //typedef process_real_cpu_clock::rep rep;
              typedef Rep rep;
            process_times()
                : real(0)
                , user(0)
                , system(0){}

#if ! defined BOOST_CHRONO_DONT_PROVIDES_DEPRECATED_IO_SINCE_V2_0_0
            template <typename Rep2>
            explicit process_times(
                Rep2 r)
                : real(r)
                , user(r)
                , system(r){}
#endif
            template <typename Rep2>
            explicit process_times(
                process_times<Rep2> const& rhs)
                : real(rhs.real)
                , user(rhs.user)
                , system(rhs.system){}
            process_times(
                rep r,
                rep u,
                rep s)
                : real(r)
                , user(u)
                , system(s){}

            rep   real;    // real (i.e wall clock) time
            rep   user;    // user cpu time
            rep system;  // system cpu time

#if ! defined BOOST_CHRONO_DONT_PROVIDES_DEPRECATED_IO_SINCE_V2_0_0
            operator rep() const
            {
              return real;
            }
#endif
            template <typename Rep2>
            bool operator==(process_times<Rep2> const& rhs) {
                return (real==rhs.real &&
                        user==rhs.user &&
                        system==rhs.system);
            }

            process_times& operator+=(
                process_times const& rhs)
            {
                real+=rhs.real;
                user+=rhs.user;
                system+=rhs.system;
                return *this;
            }
            process_times& operator-=(
                process_times const& rhs)
            {
                real-=rhs.real;
                user-=rhs.user;
                system-=rhs.system;
                return *this;
            }
            process_times& operator*=(
                process_times const& rhs)
            {
                real*=rhs.real;
                user*=rhs.user;
                system*=rhs.system;
                return *this;
            }
            process_times& operator*=(rep const& rhs)
            {
                real*=rhs;
                user*=rhs;
                system*=rhs;
                return *this;
            }
            process_times& operator/=(process_times const& rhs)
            {
                real/=rhs.real;
                user/=rhs.user;
                system/=rhs.system;
                return *this;
            }
            process_times& operator/=(rep const& rhs)
            {
                real/=rhs;
                user/=rhs;
                system/=rhs;
                return *this;
            }
            bool operator<(process_times const & rhs) const
            {
                if (real < rhs.real) return true;
                if (real > rhs.real) return false;
                if (user < rhs.user) return true;
                if (user > rhs.user) return false;
                if (system < rhs.system) return true;
                else return false;
            }

            template <class CharT, class Traits>
            void print(std::basic_ostream<CharT, Traits>& os) const
            {
                os <<  "{"<< real <<";"<< user <<";"<< system << "}";
            }

            template <class CharT, class Traits>
            void read(std::basic_istream<CharT, Traits>& is)
            {
                typedef std::istreambuf_iterator<CharT, Traits> in_iterator;
                in_iterator i(is);
                in_iterator e;
                if (i == e || *i++ != '{')  // mandatory '{'
                {
                    is.setstate(is.failbit | is.eofbit);
                    return;
                }
                CharT x,y,z;
                is >> real >> x >> user >> y >> system >> z;
                if (!is.good() || (x != ';')|| (y != ';')|| (z != '}'))
                {
                    is.setstate(is.failbit);
                }
            }
        };
}
template <class Rep1, class Rep2>
struct common_type<
  chrono::process_times<Rep1>,
  chrono::process_times<Rep2>
>
{
  typedef chrono::process_times<typename common_type<Rep1, Rep2>::type> type;
};

template <class Rep1, class Rep2>
struct common_type<
  chrono::process_times<Rep1>,
  Rep2
>
{
  typedef chrono::process_times<typename common_type<Rep1, Rep2>::type> type;
};

template <class Rep1, class Rep2>
struct common_type<
  Rep1,
  chrono::process_times<Rep2>
>
{
  typedef chrono::process_times<typename common_type<Rep1, Rep2>::type> type;
};


namespace chrono
{
  template <class Rep1, class Period1, class Rep2, class Period2>
  inline BOOST_CONSTEXPR
  bool
  operator==(const duration<process_times<Rep1>, Period1>& lhs,
        const duration<process_times<Rep2>, Period2>& rhs)
  {
      return boost::chrono::detail::duration_eq<
          duration<Rep1, Period1>, duration<Rep2, Period2>
        >()(duration<Rep1, Period1>(lhs.count().real), duration<Rep2, Period2>(rhs.count().real));
  }

  template <class Rep1, class Period1, class Rep2, class Period2>
  inline BOOST_CONSTEXPR
  bool
  operator==(const duration<process_times<Rep1>, Period1>& lhs,
        const duration<Rep2, Period2>& rhs)
  {
      return boost::chrono::detail::duration_eq<
          duration<Rep1, Period1>, duration<Rep2, Period2> >()(duration<Rep1, Period1>(lhs.count().real), rhs);
  }

  template <class Rep1, class Period1, class Rep2, class Period2>
  inline BOOST_CONSTEXPR
  bool
  operator==(const duration<Rep1, Period1>& lhs,
        const duration<process_times<Rep2>, Period2>& rhs)
  {
      return rhs == lhs;
  }


  // Duration <

  template <class Rep1, class Period1, class Rep2, class Period2>
  inline BOOST_CONSTEXPR
  bool
  operator< (const duration<process_times<Rep1>, Period1>& lhs,
        const duration<Rep2, Period2>& rhs)
  {
      return boost::chrono::detail::duration_lt<
        duration<Rep1, Period1>, duration<Rep2, Period2> >()(duration<Rep1, Period1>(lhs.count().real), rhs);
  }

  template <class Rep1, class Period1, class Rep2, class Period2>
  inline BOOST_CONSTEXPR
  bool
  operator< (const duration<Rep1, Period1>& lhs,
        const duration<process_times<Rep2>, Period2>& rhs)
  {
      return boost::chrono::detail::duration_lt<
        duration<Rep1, Period1>, duration<Rep2, Period2> >()(lhs, duration<Rep2, Period2>(rhs.count().real));
  }

  template <class Rep1, class Period1, class Rep2, class Period2>
  inline BOOST_CONSTEXPR
  bool
  operator< (const duration<process_times<Rep1>, Period1>& lhs,
        const duration<process_times<Rep2>, Period2>& rhs)
  {
    return boost::chrono::detail::duration_lt<
        duration<Rep1, Period1>, duration<Rep2, Period2>
      >()(duration<Rep1, Period1>(lhs.count().real), duration<Rep2, Period2>(rhs.count().real));
  }


  typedef process_times<nanoseconds::rep> process_cpu_clock_times;
#if ! BOOST_OS_WINDOWS || BOOST_PLAT_WINDOWS_DESKTOP
    class BOOST_CHRONO_DECL process_cpu_clock
    {
    public:

        typedef process_cpu_clock_times times;
        typedef boost::chrono::duration<times,  nano>                duration;
        typedef duration::rep                       rep;
        typedef duration::period                    period;
        typedef chrono::time_point<process_cpu_clock>  time_point;
        BOOST_STATIC_CONSTEXPR bool is_steady =           true;

        static BOOST_CHRONO_INLINE time_point now() BOOST_NOEXCEPT;
#if !defined BOOST_CHRONO_DONT_PROVIDE_HYBRID_ERROR_HANDLING
        static BOOST_CHRONO_INLINE time_point now(system::error_code & ec );
#endif
    };
#endif

    template <class CharT, class Traits, typename Rep>
    std::basic_ostream<CharT, Traits>&
    operator<<(std::basic_ostream<CharT, Traits>& os,
        process_times<Rep> const& rhs)
    {
        rhs.print(os);
        return os;
    }

    template <class CharT, class Traits, typename Rep>
    std::basic_istream<CharT, Traits>&
    operator>>(std::basic_istream<CharT, Traits>& is,
        process_times<Rep>& rhs)
    {
        rhs.read(is);
        return is;
    }

    template <typename Rep>
    struct duration_values<process_times<Rep> >
    {
        typedef process_times<Rep> Res;
    public:
        static Res zero()
        {
            return Res();
        }
        static Res max BOOST_PREVENT_MACRO_SUBSTITUTION ()
        {
          return Res((std::numeric_limits<Rep>::max)(),
                      (std::numeric_limits<Rep>::max)(),
                      (std::numeric_limits<Rep>::max)());
        }
        static Res min BOOST_PREVENT_MACRO_SUBSTITUTION ()
        {
          return Res((std::numeric_limits<Rep>::min)(),
                      (std::numeric_limits<Rep>::min)(),
                      (std::numeric_limits<Rep>::min)());
        }
    };

    template<class CharT>
    struct clock_string<process_real_cpu_clock, CharT>
    {
      static std::basic_string<CharT> name()
      {
        static const CharT
            u[] =
                { 'p', 'r', 'o', 'c', 'e', 's', 's', '_', 'r', 'e', 'a', 'l', '_', 'c', 'l', 'o', 'c', 'k' };
        static const std::basic_string<CharT> str(u, u + sizeof(u)
            / sizeof(u[0]));
        return str;
      }
      static std::basic_string<CharT> since()
      {
        const CharT
            u[] =
                { ' ', 's', 'i', 'n', 'c', 'e', ' ', 'p', 'r', 'o', 'c', 'e', 's', 's', ' ', 's', 't', 'a', 'r', 't', '-', 'u', 'p' };
        const std::basic_string<CharT> str(u, u + sizeof(u) / sizeof(u[0]));
        return str;
      }
    };

#if ! BOOST_OS_WINDOWS || BOOST_PLAT_WINDOWS_DESKTOP
    template<class CharT>
    struct clock_string<process_user_cpu_clock, CharT>
    {
      static std::basic_string<CharT> name()
      {
        static const CharT
            u[] =
                { 'p', 'r', 'o', 'c', 'e', 's', 's', '_', 'u', 's', 'e', 'r', '_', 'c', 'l', 'o', 'c', 'k' };
        static const std::basic_string<CharT> str(u, u + sizeof(u)
            / sizeof(u[0]));
        return str;
      }
      static std::basic_string<CharT> since()
      {
        const CharT
            u[] =
                { ' ', 's', 'i', 'n', 'c', 'e', ' ', 'p', 'r', 'o', 'c', 'e', 's', 's', ' ', 's', 't', 'a', 'r', 't', '-', 'u', 'p' };
        const std::basic_string<CharT> str(u, u + sizeof(u) / sizeof(u[0]));
        return str;
      }
    };

    template<class CharT>
    struct clock_string<process_system_cpu_clock, CharT>
    {
      static std::basic_string<CharT> name()
      {
        static const CharT
            u[] =
                { 'p', 'r', 'o', 'c', 'e', 's', 's', '_', 's', 'y', 's', 't', 'e', 'm', '_', 'c', 'l', 'o', 'c', 'k' };
        static const std::basic_string<CharT> str(u, u + sizeof(u)
            / sizeof(u[0]));
        return str;
      }
      static std::basic_string<CharT> since()
      {
        const CharT
            u[] =
                { ' ', 's', 'i', 'n', 'c', 'e', ' ', 'p', 'r', 'o', 'c', 'e', 's', 's', ' ', 's', 't', 'a', 'r', 't', '-', 'u', 'p' };
        const std::basic_string<CharT> str(u, u + sizeof(u) / sizeof(u[0]));
        return str;
      }
    };

    template<class CharT>
    struct clock_string<process_cpu_clock, CharT>
    {
      static std::basic_string<CharT> name()
      {
        static const CharT u[] =
        { 'p', 'r', 'o', 'c', 'e', 's', 's', '_', 'c', 'l', 'o', 'c', 'k' };
        static const std::basic_string<CharT> str(u, u + sizeof(u)
            / sizeof(u[0]));
        return str;
      }
      static std::basic_string<CharT> since()
      {
        const CharT
            u[] =
                { ' ', 's', 'i', 'n', 'c', 'e', ' ', 'p', 'r', 'o', 'c', 'e', 's', 's', ' ', 's', 't', 'a', 'r', 't', '-', 'u', 'p' };
        const std::basic_string<CharT> str(u, u + sizeof(u) / sizeof(u[0]));
        return str;
      }
    };
#endif

} // namespace chrono
} // namespace boost

namespace std {

    template <typename Rep>
    struct numeric_limits<boost::chrono::process_times<Rep> >
    {
        typedef boost::chrono::process_times<Rep> Res;

        public:
        static const bool is_specialized = true;
        static Res min BOOST_PREVENT_MACRO_SUBSTITUTION ()
        {
          return Res((std::numeric_limits<Rep>::min)(),
                      (std::numeric_limits<Rep>::min)(),
                      (std::numeric_limits<Rep>::min)());
        }
        static Res max BOOST_PREVENT_MACRO_SUBSTITUTION ()
        {
          return Res((std::numeric_limits<Rep>::max)(),
                      (std::numeric_limits<Rep>::max)(),
                      (std::numeric_limits<Rep>::max)());
        }
        static Res lowest() BOOST_NOEXCEPT_OR_NOTHROW
        {
            return (min)();
        }
        static const int digits = std::numeric_limits<Rep>::digits+
                        std::numeric_limits<Rep>::digits+
                        std::numeric_limits<Rep>::digits;
        static const int digits10 = std::numeric_limits<Rep>::digits10+
                        std::numeric_limits<Rep>::digits10+
                        std::numeric_limits<Rep>::digits10;
        static const bool is_signed = Rep::is_signed;
        static const bool is_integer = Rep::is_integer;
        static const bool is_exact = Rep::is_exact;
        static const int radix = 0;
        //~ static Res epsilon() throw() { return 0; }
        //~ static Res round_error() throw() { return 0; }
        //~ static const int min_exponent = 0;
        //~ static const int min_exponent10 = 0;
        //~ static const int max_exponent = 0;
        //~ static const int max_exponent10 = 0;
        //~ static const bool has_infinity = false;
        //~ static const bool has_quiet_NaN = false;
        //~ static const bool has_signaling_NaN = false;
        //~ static const float_denorm_style has_denorm = denorm_absent;
        //~ static const bool has_denorm_loss = false;
        //~ static Res infinity() throw() { return 0; }
        //~ static Res quiet_NaN() throw() { return 0; }
        //~ static Res signaling_NaN() throw() { return 0; }
        //~ static Res denorm_min() throw() { return 0; }
        //~ static const bool is_iec559 = false;
        //~ static const bool is_bounded = true;
        //~ static const bool is_modulo = false;
        //~ static const bool traps = false;
        //~ static const bool tinyness_before = false;
        //~ static const float_round_style round_style = round_toward_zero;

    };
}

#ifndef BOOST_CHRONO_HEADER_ONLY
#include <boost/config/abi_suffix.hpp> // pops abi_prefix.hpp pragmas
#else
#include <boost/chrono/detail/inlined/process_cpu_clocks.hpp>
#endif
#endif

#endif  // BOOST_CHRONO_PROCESS_CPU_CLOCKS_HPP

/* process_cpu_clocks.hpp
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
*/