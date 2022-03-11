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