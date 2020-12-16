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
GHPk0ro5sjFHvofmyHf3WdvidPe5O2846L31m91f/Iw1p0mnP3L1zFGHLLf8Zu762AN7H1qx+z9vjpxl1un7b8i/5aH47584GJf7yZ4Fz7f4z5w7ZwgeS2mMBcjA2Fr04UoddwW2Al8MfJToPJ4BN2U5E3ArlmsMPjdwE+AUnlOnUdqQ53EGz1cI+WSOza0HHMdz9URKG/L8vGI8CSGfyvwNgZvy3L4tp5erqrnTgW2R55w/bX0Y85xumA8A9gMwn6oxlxp4adV86g7gTYC9gJjWKBPYN78a2z30HGsB6OsA+lzrDPSh+RbSx4BHoWMHz7s2XXb2uVfvHuAHzgceBrwe2DcPO/WJScxGmcHzseWgnelRPS+b3jP83CyhV9X8rAfwIeCtkM3vhXzAGaT3ztXOOWc79JxWq3nbocthx97In6fRHG5Ub9ABqwHP9A6c0+1HOqZP1dwuCzh4fvdun9BzPE9f1BmQ2Tf0fO9Q35pzvnrQp94VsMsVtZ//OdbDnpnV88CY7YjrA/QGjNp+YeaBdVfdVXfVXXXX/9f1r13/516w9f/mR6vX/7l+6/+MWqz/U4PX/7kd27a7QOv/IyNrt/4H31nX/ypw/U/8wetq7y9cX57v+r905LnX/6Uh9Ez6J67/146s3foffGdb/yM/cP3/5Mizr/+3Id9Y/7N88Po/5Re2T936//zX/2/R+v/hw90m/Djow+/FpV8tHXGyc6O69f8/a/2f+g+u/4+M/GXr/9KRv2z9v3bkL1v/79n+n7X+P5+1/6H25v/49f9n2yPr9gCMPYDA9f8p2CZhR6RoBeixo279X3fVXXVX3VV3nf/1r1n/+3n/f+EZAH39f6Mec77J3//fbwSKpbyFyDsQkFc+eWJRDu0NpPvtDTh4jbuE15MzAbfq5batilUd2HNAHwj35XV82HX6+8Q/tDrOndJeij1dVo/WjZQ3wMhLN9aYn1G6ANyDXEf0dTdoTbzQzep1mDvpdRjscnPeVuQl63nm8UT3rTObgmZ1136d6bfmN+LSoSdoeQHviezC6+0neY79EOAO8JW2C7BPP+wFBNeV7PIb4ruB7eKT60i8KylGNgt3603vKExDHWNQmb2A5nodVTOHKVFz2wvsFRaLIyNO1wE8C5C/B9DC4HGY3RaTIy6iylY6eLmsg4CWOp+thcXmsNr1PN1GWaFtdDkqDd0uRqyzbgvJ8aiGbYz3Ka6kdFbAN+GbmQVdb/H6fJveluAb3z7AVsN5jyLIXmQf5r3E6Bv3UvrG8PEKlD/MiCl/i9IdhF0kcyyzT6awoNivv95GfDdROssopx3dx0S7X5OL/WObV1H+bX7vPJ4wubBQGHHad1L+vfQe02Leb7uVaBbhNmTKK3LKJ0GR6njiD4knyojJ/4LSl1E5Xm6Upe35/a5Ek1U25nrHIUqz+hkA1GKvhc9lGG0aap/FG7DPUm0/am/ei0pPEHQdShLQGO0NfLv+bHSg9vYNPHkYs8oKysuN9qZxAqpMgszLxLsyyXg+KD2A2vMqpJ+m9K+T6qvX4t3cNhJjWkner8ohTuVQ/HRHOreRRP3AVw406y67JlbvXaEOLDMe+H3iWZhEfcCQ2WecNehBZVqr2w99Iq+soKiguAI0/oYVydyctEYsTNTbzMWG3kH0RLpXqd42VFbHJN0Ga+rpZU0Vg8HvZv5RXfT8H7Dx2kT2wJt+p6pL5QtahlTmbnKgpZ1cZu0s37Z1kHGRXeQYeyd5r6Or/EtUO9nAeam8NqaT3OTqKduhPA+X9zu630xPZ7zp7A9qgOpuLlV7rNepoZHF6o+OQpXjvFZ94Zql/PvZTQPpfBf1vXimPdqpql+38Xs=
*/