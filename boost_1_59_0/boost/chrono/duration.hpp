//  duration.hpp  --------------------------------------------------------------//

//  Copyright 2008 Howard Hinnant
//  Copyright 2008 Beman Dawes
//  Copyright 2009-2011 Vicente J. Botet Escriba

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

/*

This code was derived by Beman Dawes from Howard Hinnant's time2_demo prototype.
Many thanks to Howard for making his code available under the Boost license.
The original code was modified to conform to Boost conventions and to section
20.9 Time utilities [time] of the C++ committee's working paper N2798.
See http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2008/n2798.pdf.

time2_demo contained this comment:

    Much thanks to Andrei Alexandrescu,
                   Walter Brown,
                   Peter Dimov,
                   Jeff Garland,
                   Terry Golubiewski,
                   Daniel Krugler,
                   Anthony Williams.
*/


#ifndef BOOST_CHRONO_DURATION_HPP
#define BOOST_CHRONO_DURATION_HPP

#include <boost/chrono/config.hpp>
#include <boost/chrono/detail/static_assert.hpp>

#include <climits>
#include <limits>


#include <boost/mpl/logical.hpp>
#include <boost/ratio/ratio.hpp>
#include <boost/type_traits/common_type.hpp>
#include <boost/type_traits/is_arithmetic.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/type_traits/is_floating_point.hpp>
#include <boost/type_traits/is_unsigned.hpp>
#include <boost/chrono/detail/is_evenly_divisible_by.hpp>

#include <boost/cstdint.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/detail/workaround.hpp>
#include <boost/integer_traits.hpp>

#if !defined(BOOST_NO_CXX11_STATIC_ASSERT) || !defined(BOOST_CHRONO_USES_MPL_ASSERT)
#define BOOST_CHRONO_A_DURATION_REPRESENTATION_CAN_NOT_BE_A_DURATION        "A duration representation can not be a duration"
#define BOOST_CHRONO_SECOND_TEMPLATE_PARAMETER_OF_DURATION_MUST_BE_A_STD_RATIO "Second template parameter of duration must be a boost::ratio"
#define BOOST_CHRONO_DURATION_PERIOD_MUST_BE_POSITIVE "duration period must be positive"
#define BOOST_CHRONO_SECOND_TEMPLATE_PARAMETER_OF_TIME_POINT_MUST_BE_A_BOOST_CHRONO_DURATION "Second template parameter of time_point must be a boost::chrono::duration"
#endif

#ifndef BOOST_CHRONO_HEADER_ONLY
// this must occur after all of the includes and before any code appears:
#include <boost/config/abi_prefix.hpp> // must be the last #include
#endif

//----------------------------------------------------------------------------//
//                                                                            //
//                        20.9 Time utilities [time]                          //
//                                 synopsis                                   //
//                                                                            //
//----------------------------------------------------------------------------//

namespace boost {
namespace chrono {

    template <class Rep, class Period = ratio<1> >
    class duration;

    namespace detail
    {
    template <class T>
      struct is_duration
        : boost::false_type {};

    template <class Rep, class Period>
      struct is_duration<duration<Rep, Period> >
        : boost::true_type  {};

    template <class Duration, class Rep, bool = is_duration<Rep>::value>
    struct duration_divide_result
    {
    };

    template <class Duration, class Rep2,
        bool = (
                    ((boost::is_convertible<typename Duration::rep,
                        typename common_type<typename Duration::rep, Rep2>::type>::value))
                &&  ((boost::is_convertible<Rep2,
                        typename common_type<typename Duration::rep, Rep2>::type>::value))
                )
        >
    struct duration_divide_imp
    {
    };

    template <class Rep1, class Period, class Rep2>
    struct duration_divide_imp<duration<Rep1, Period>, Rep2, true>
    {
        typedef duration<typename common_type<Rep1, Rep2>::type, Period> type;
    };

    template <class Rep1, class Period, class Rep2>
    struct duration_divide_result<duration<Rep1, Period>, Rep2, false>
        : duration_divide_imp<duration<Rep1, Period>, Rep2>
    {
    };

///
    template <class Rep, class Duration, bool = is_duration<Rep>::value>
    struct duration_divide_result2
    {
    };

    template <class Rep, class Duration,
        bool = (
                    ((boost::is_convertible<typename Duration::rep,
                        typename common_type<typename Duration::rep, Rep>::type>::value))
                &&  ((boost::is_convertible<Rep,
                        typename common_type<typename Duration::rep, Rep>::type>::value))
                )
        >
    struct duration_divide_imp2
    {
    };

    template <class Rep1, class Rep2, class Period >
    struct duration_divide_imp2<Rep1, duration<Rep2, Period>, true>
    {
        //typedef typename common_type<Rep1, Rep2>::type type;
        typedef double type;
    };

    template <class Rep1, class Rep2, class Period >
    struct duration_divide_result2<Rep1, duration<Rep2, Period>, false>
        : duration_divide_imp2<Rep1, duration<Rep2, Period> >
    {
    };

///
    template <class Duration, class Rep, bool = is_duration<Rep>::value>
    struct duration_modulo_result
    {
    };

    template <class Duration, class Rep2,
        bool = (
                    //boost::is_convertible<typename Duration::rep,
                        //typename common_type<typename Duration::rep, Rep2>::type>::value
                //&&
    boost::is_convertible<Rep2,
                        typename common_type<typename Duration::rep, Rep2>::type>::value
                )
        >
    struct duration_modulo_imp
    {
    };

    template <class Rep1, class Period, class Rep2>
    struct duration_modulo_imp<duration<Rep1, Period>, Rep2, true>
    {
        typedef duration<typename common_type<Rep1, Rep2>::type, Period> type;
    };

    template <class Rep1, class Period, class Rep2>
    struct duration_modulo_result<duration<Rep1, Period>, Rep2, false>
        : duration_modulo_imp<duration<Rep1, Period>, Rep2>
    {
    };

} // namespace detail
} // namespace chrono


// common_type trait specializations

template <class Rep1, class Period1, class Rep2, class Period2>
struct common_type<chrono::duration<Rep1, Period1>,
                     chrono::duration<Rep2, Period2> >;


namespace chrono {

    // customization traits
    template <class Rep> struct treat_as_floating_point;
    template <class Rep> struct duration_values;

    // convenience typedefs
    typedef duration<boost::int_least64_t, nano> nanoseconds;    // at least 64 bits needed
    typedef duration<boost::int_least64_t, micro> microseconds;  // at least 55 bits needed
    typedef duration<boost::int_least64_t, milli> milliseconds;  // at least 45 bits needed
    typedef duration<boost::int_least64_t> seconds;              // at least 35 bits needed
    typedef duration<boost::int_least32_t, ratio< 60> > minutes; // at least 29 bits needed
    typedef duration<boost::int_least32_t, ratio<3600> > hours;  // at least 23 bits needed

//----------------------------------------------------------------------------//
//                          duration helpers                                  //
//----------------------------------------------------------------------------//

namespace detail
{

    // duration_cast

    // duration_cast is the heart of this whole prototype.  It can convert any
    //   duration to any other.  It is also (implicitly) used in converting
    //   time_points.  The conversion is always exact if possible.  And it is
    //   always as efficient as hand written code.  If different representations
    //   are involved, care is taken to never require implicit conversions.
    //   Instead static_cast is used explicitly for every required conversion.
    //   If there are a mixture of integral and floating point representations,
    //   the use of common_type ensures that the most logical "intermediate"
    //   representation is used.
    template <class FromDuration, class ToDuration,
              class Period,
              bool PeriodNumEq1,
              bool PeriodDenEq1>
    struct duration_cast_aux;

    // When the two periods are the same, all that is left to do is static_cast from
    //   the source representation to the target representation (which may be a no-op).
    //   This conversion is always exact as long as the static_cast from the source
    //   representation to the destination representation is exact.
    template <class FromDuration, class ToDuration, class Period>
    struct duration_cast_aux<FromDuration, ToDuration, Period, true, true>
    {
        BOOST_CONSTEXPR ToDuration operator()(const FromDuration& fd) const
        {
            return ToDuration(static_cast<typename ToDuration::rep>(fd.count()));
        }
    };

    // When the numerator of FromPeriod / ToPeriod is 1, then all we need to do is
    //   divide by the denominator of FromPeriod / ToPeriod.  The common_type of
    //   the two representations is used for the intermediate computation before
    //   static_cast'ing to the destination.
    //   This conversion is generally not exact because of the division (but could be
    //   if you get lucky on the run time value of fd.count()).
    template <class FromDuration, class ToDuration, class Period>
    struct duration_cast_aux<FromDuration, ToDuration, Period, true, false>
    {
        BOOST_CONSTEXPR ToDuration operator()(const FromDuration& fd) const
        {
            typedef typename common_type<
                typename ToDuration::rep,
                typename FromDuration::rep,
                boost::intmax_t>::type C;
            return ToDuration(static_cast<typename ToDuration::rep>(
                              static_cast<C>(fd.count()) / static_cast<C>(Period::den)));
        }
    };

    // When the denominator of FromPeriod / ToPeriod is 1, then all we need to do is
    //   multiply by the numerator of FromPeriod / ToPeriod.  The common_type of
    //   the two representations is used for the intermediate computation before
    //   static_cast'ing to the destination.
    //   This conversion is always exact as long as the static_cast's involved are exact.
    template <class FromDuration, class ToDuration, class Period>
    struct duration_cast_aux<FromDuration, ToDuration, Period, false, true>
    {
        BOOST_CONSTEXPR ToDuration operator()(const FromDuration& fd) const
        {
            typedef typename common_type<
              typename ToDuration::rep,
              typename FromDuration::rep,
              boost::intmax_t>::type C;
            return ToDuration(static_cast<typename ToDuration::rep>(
                              static_cast<C>(fd.count()) * static_cast<C>(Period::num)));
        }
    };

    // When neither the numerator or denominator of FromPeriod / ToPeriod is 1, then we need to
    //   multiply by the numerator and divide by the denominator of FromPeriod / ToPeriod.  The
    //   common_type of the two representations is used for the intermediate computation before
    //   static_cast'ing to the destination.
    //   This conversion is generally not exact because of the division (but could be
    //   if you get lucky on the run time value of fd.count()).
    template <class FromDuration, class ToDuration, class Period>
    struct duration_cast_aux<FromDuration, ToDuration, Period, false, false>
    {
        BOOST_CONSTEXPR ToDuration operator()(const FromDuration& fd) const
        {
            typedef typename common_type<
              typename ToDuration::rep,
              typename FromDuration::rep,
              boost::intmax_t>::type C;
            return ToDuration(static_cast<typename ToDuration::rep>(
               static_cast<C>(fd.count()) * static_cast<C>(Period::num)
                 / static_cast<C>(Period::den)));
        }
    };

    template <class FromDuration, class ToDuration>
    struct duration_cast {
        typedef typename ratio_divide<typename FromDuration::period,
              typename ToDuration::period>::type Period;
        typedef duration_cast_aux<
            FromDuration,
            ToDuration,
            Period,
            Period::num == 1,
            Period::den == 1
        > Aux;
        BOOST_CONSTEXPR ToDuration operator()(const FromDuration& fd) const
        {
            return Aux()(fd);
        }
    };

} // namespace detail

//----------------------------------------------------------------------------//
//                                                                            //
//      20.9.2 Time-related traits [time.traits]                              //
//                                                                            //
//----------------------------------------------------------------------------//
//----------------------------------------------------------------------------//
//      20.9.2.1 treat_as_floating_point [time.traits.is_fp]                        //
//      Probably should have been treat_as_floating_point. Editor notifed.    //
//----------------------------------------------------------------------------//

    // Support bidirectional (non-exact) conversions for floating point rep types
    //   (or user defined rep types which specialize treat_as_floating_point).
    template <class Rep>
    struct treat_as_floating_point : boost::is_floating_point<Rep> {};

//----------------------------------------------------------------------------//
//      20.9.2.2 duration_values [time.traits.duration_values]                //
//----------------------------------------------------------------------------//

namespace detail {
    template <class T, bool = is_arithmetic<T>::value>
    struct chrono_numeric_limits {
        static BOOST_CHRONO_LIB_CONSTEXPR T lowest() BOOST_CHRONO_LIB_NOEXCEPT_OR_THROW {return (std::numeric_limits<T>::min)  ();}
    };

    template <class T>
    struct chrono_numeric_limits<T,true> {
        static BOOST_CHRONO_LIB_CONSTEXPR T lowest() BOOST_CHRONO_LIB_NOEXCEPT_OR_THROW {return (std::numeric_limits<T>::min)  ();}
    };

    template <>
    struct chrono_numeric_limits<float,true> {
        static BOOST_CHRONO_LIB_CONSTEXPR float lowest() BOOST_CHRONO_LIB_NOEXCEPT_OR_THROW
        {
            return -(std::numeric_limits<float>::max) ();
        }
    };

    template <>
    struct chrono_numeric_limits<double,true> {
        static BOOST_CHRONO_LIB_CONSTEXPR double lowest() BOOST_CHRONO_LIB_NOEXCEPT_OR_THROW
        {
            return -(std::numeric_limits<double>::max) ();
        }
    };

    template <>
    struct chrono_numeric_limits<long double,true> {
        static BOOST_CHRONO_LIB_CONSTEXPR long double lowest() BOOST_CHRONO_LIB_NOEXCEPT_OR_THROW
        {
            return -(std::numeric_limits<long double>::max)();
        }
    };

    template <class T>
    struct numeric_limits : chrono_numeric_limits<typename remove_cv<T>::type>
    {};

}
template <class Rep>
struct duration_values
{
    static BOOST_CONSTEXPR Rep zero() {return Rep(0);}
    static BOOST_CHRONO_LIB_CONSTEXPR Rep max BOOST_PREVENT_MACRO_SUBSTITUTION ()
    {
        return (std::numeric_limits<Rep>::max)();
    }

    static BOOST_CHRONO_LIB_CONSTEXPR Rep min BOOST_PREVENT_MACRO_SUBSTITUTION ()
    {
        return detail::numeric_limits<Rep>::lowest();
    }
};

}  // namespace chrono

//----------------------------------------------------------------------------//
//      20.9.2.3 Specializations of common_type [time.traits.specializations] //
//----------------------------------------------------------------------------//

template <class Rep1, class Period1, class Rep2, class Period2>
struct common_type<chrono::duration<Rep1, Period1>,
                   chrono::duration<Rep2, Period2> >
{
  typedef chrono::duration<typename common_type<Rep1, Rep2>::type,
                      typename boost::ratio_gcd<Period1, Period2>::type> type;
};


//----------------------------------------------------------------------------//
//                                                                            //
//         20.9.3 Class template duration [time.duration]                     //
//                                                                            //
//----------------------------------------------------------------------------//


namespace chrono {

    template <class Rep, class Period>
    class BOOST_SYMBOL_VISIBLE duration
    {
    //BOOST_CHRONO_STATIC_ASSERT(boost::is_integral<Rep>::value, BOOST_CHRONO_A_DURATION_REPRESENTATION_MUST_BE_INTEGRAL, ());
    BOOST_CHRONO_STATIC_ASSERT(!boost::chrono::detail::is_duration<Rep>::value,
            BOOST_CHRONO_A_DURATION_REPRESENTATION_CAN_NOT_BE_A_DURATION, ());
    BOOST_CHRONO_STATIC_ASSERT(boost::ratio_detail::is_ratio<typename Period::type>::value,
            BOOST_CHRONO_SECOND_TEMPLATE_PARAMETER_OF_DURATION_MUST_BE_A_STD_RATIO, ());
    BOOST_CHRONO_STATIC_ASSERT(Period::num>0,
            BOOST_CHRONO_DURATION_PERIOD_MUST_BE_POSITIVE, ());
    public:
        typedef Rep rep;
        typedef Period period;
    private:
        rep rep_;
    public:

#if  defined   BOOST_CHRONO_DURATION_DEFAULTS_TO_ZERO
        BOOST_FORCEINLINE BOOST_CONSTEXPR
        duration() : rep_(duration_values<rep>::zero()) { }
#elif  defined   BOOST_NO_CXX11_DEFAULTED_FUNCTIONS
        BOOST_CONSTEXPR duration() {}
#else
        BOOST_CONSTEXPR duration()  = default;
#endif
        template <class Rep2>
        BOOST_SYMBOL_VISIBLE BOOST_FORCEINLINE BOOST_CONSTEXPR
        explicit duration(const Rep2& r
        , typename boost::enable_if <
                    mpl::and_ <
                        boost::is_convertible<Rep2, rep>,
                        mpl::or_ <
                            treat_as_floating_point<rep>,
                            mpl::and_ <
                                mpl::not_ < treat_as_floating_point<rep> >,
                                mpl::not_ < treat_as_floating_point<Rep2> >
                            >
                        >
                    >
                >::type* = 0
            ) : rep_(r) { }
#if  defined   BOOST_NO_CXX11_DEFAULTED_FUNCTIONS
        duration& operator=(const duration& rhs)
        {
            if (&rhs != this) rep_= rhs.rep_;
            return *this;
        }
#else
        duration& operator=(const duration& rhs) = default;
#endif
        // conversions
        template <class Rep2, class Period2>
        BOOST_FORCEINLINE BOOST_CONSTEXPR
        duration(const duration<Rep2, Period2>& d
        , typename boost::enable_if <
                    mpl::or_ <
                        treat_as_floating_point<rep>,
                        mpl::and_ <
                            chrono_detail::is_evenly_divisible_by<Period2, period>,
                            mpl::not_ < treat_as_floating_point<Rep2> >
                        >
                    >
                >::type* = 0
        )
            : rep_(chrono::detail::duration_cast<duration<Rep2, Period2>, duration>()(d).count()) {}

        // observer

        BOOST_CONSTEXPR
        rep count() const {return rep_;}

        // arithmetic

        BOOST_CONSTEXPR
        duration  operator+() const {return duration(rep_);;}
        BOOST_CONSTEXPR
        duration  operator-() const {return duration(-rep_);}
        duration& operator++()      {++rep_; return *this;}
        duration  operator++(int)   {return duration(rep_++);}
        duration& operator--()      {--rep_; return *this;}
        duration  operator--(int)   {return duration(rep_--);}

        duration& operator+=(const duration& d)
        {
            rep_ += d.count(); return *this;
        }
        duration& operator-=(const duration& d)
        {
            rep_ -= d.count(); return *this;
        }

        duration& operator*=(const rep& rhs) {rep_ *= rhs; return *this;}
        duration& operator/=(const rep& rhs) {rep_ /= rhs; return *this;}
        duration& operator%=(const rep& rhs) {rep_ %= rhs; return *this;}
        duration& operator%=(const duration& rhs)
        {
            rep_ %= rhs.count(); return *this;
        }
        // 20.9.3.4 duration special values [time.duration.special]

        static BOOST_CONSTEXPR duration zero()
        {
            return duration(duration_values<rep>::zero());
        }
        static BOOST_CHRONO_LIB_CONSTEXPR duration min BOOST_PREVENT_MACRO_SUBSTITUTION ()
        {
            return duration((duration_values<rep>::min)());
        }
        static BOOST_CHRONO_LIB_CONSTEXPR duration max BOOST_PREVENT_MACRO_SUBSTITUTION ()
        {
            return duration((duration_values<rep>::max)());
        }
    };

//----------------------------------------------------------------------------//
//      20.9.3.5 duration non-member arithmetic [time.duration.nonmember]     //
//----------------------------------------------------------------------------//

    // Duration +

    template <class Rep1, class Period1, class Rep2, class Period2>
    inline BOOST_CONSTEXPR
    typename common_type<duration<Rep1, Period1>, duration<Rep2, Period2> >::type
    operator+(const duration<Rep1, Period1>& lhs,
          const duration<Rep2, Period2>& rhs)
    {
      typedef typename common_type<duration<Rep1, Period1>,
        duration<Rep2, Period2> >::type common_duration;
      return common_duration(common_duration(lhs).count()+common_duration(rhs).count());
    }

    // Duration -

    template <class Rep1, class Period1, class Rep2, class Period2>
    inline BOOST_CONSTEXPR
    typename common_type<duration<Rep1, Period1>, duration<Rep2, Period2> >::type
    operator-(const duration<Rep1, Period1>& lhs,
          const duration<Rep2, Period2>& rhs)
    {
      typedef typename common_type<duration<Rep1, Period1>,
            duration<Rep2, Period2> >::type common_duration;
      return common_duration(common_duration(lhs).count()-common_duration(rhs).count());
    }

    // Duration *

    template <class Rep1, class Period, class Rep2>
    inline BOOST_CONSTEXPR
    typename boost::enable_if <
        mpl::and_ <
        boost::is_convertible<Rep1, typename common_type<Rep1, Rep2>::type>,
        boost::is_convertible<Rep2, typename common_type<Rep1, Rep2>::type>
        >,
        duration<typename common_type<Rep1, Rep2>::type, Period>
    >::type
    operator*(const duration<Rep1, Period>& d, const Rep2& s)
    {
      typedef typename common_type<Rep1, Rep2>::type common_rep;
      typedef duration<common_rep, Period> common_duration;
      return common_duration(common_duration(d).count()*static_cast<common_rep>(s));
    }

    template <class Rep1, class Period, class Rep2>
    inline BOOST_CONSTEXPR
    typename boost::enable_if <
        mpl::and_ <
        boost::is_convertible<Rep1, typename common_type<Rep1, Rep2>::type>,
        boost::is_convertible<Rep2, typename common_type<Rep1, Rep2>::type>
        >,
        duration<typename common_type<Rep1, Rep2>::type, Period>
    >::type
    operator*(const Rep1& s, const duration<Rep2, Period>& d)
    {
        return d * s;
    }

    // Duration /

    template <class Rep1, class Period, class Rep2>
    inline BOOST_CONSTEXPR
    typename boost::disable_if <boost::chrono::detail::is_duration<Rep2>,
      typename boost::chrono::detail::duration_divide_result<
        duration<Rep1, Period>, Rep2>::type
    >::type
    operator/(const duration<Rep1, Period>& d, const Rep2& s)
    {
      typedef typename common_type<Rep1, Rep2>::type common_rep;
      typedef duration<common_rep, Period> common_duration;
      return common_duration(common_duration(d).count()/static_cast<common_rep>(s));
    }

    template <class Rep1, class Period1, class Rep2, class Period2>
    inline BOOST_CONSTEXPR
    typename common_type<Rep1, Rep2>::type
    operator/(const duration<Rep1, Period1>& lhs, const duration<Rep2, Period2>& rhs)
    {
        typedef typename common_type<duration<Rep1, Period1>,
                                   duration<Rep2, Period2> >::type common_duration;
        return common_duration(lhs).count() / common_duration(rhs).count();
    }

    #ifdef BOOST_CHRONO_EXTENSIONS
    template <class Rep1, class Rep2, class Period>
    inline BOOST_CONSTEXPR
    typename boost::disable_if <boost::chrono::detail::is_duration<Rep1>,
      typename boost::chrono::detail::duration_divide_result2<
        Rep1, duration<Rep2, Period> >::type
      >::type
    operator/(const Rep1& s, const duration<Rep2, Period>& d)
    {
      typedef typename common_type<Rep1, Rep2>::type common_rep;
      typedef duration<common_rep, Period> common_duration;
      return static_cast<common_rep>(s)/common_duration(d).count();
    }
    #endif
    // Duration %

    template <class Rep1, class Period, class Rep2>
    inline BOOST_CONSTEXPR
    typename boost::disable_if <boost::chrono::detail::is_duration<Rep2>,
      typename boost::chrono::detail::duration_modulo_result<
        duration<Rep1, Period>, Rep2>::type
    >::type
    operator%(const duration<Rep1, Period>& d, const Rep2& s)
    {
      typedef typename common_type<Rep1, Rep2>::type common_rep;
      typedef duration<common_rep, Period> common_duration;
      return common_duration(common_duration(d).count()%static_cast<common_rep>(s));
    }

    template <class Rep1, class Period1, class Rep2, class Period2>
    inline BOOST_CONSTEXPR
    typename common_type<duration<Rep1, Period1>, duration<Rep2, Period2> >::type
    operator%(const duration<Rep1, Period1>& lhs,
          const duration<Rep2, Period2>& rhs) {
        typedef typename common_type<duration<Rep1, Period1>,
                                 duration<Rep2, Period2> >::type common_duration;

      return common_duration(common_duration(lhs).count()%common_duration(rhs).count());
    }


//----------------------------------------------------------------------------//
//      20.9.3.6 duration comparisons [time.duration.comparisons]             //
//----------------------------------------------------------------------------//

namespace detail
{
    template <class LhsDuration, class RhsDuration>
    struct duration_eq
    {
      BOOST_CONSTEXPR bool operator()(const LhsDuration& lhs, const RhsDuration& rhs) const
        {
            typedef typename common_type<LhsDuration, RhsDuration>::type common_duration;
            return common_duration(lhs).count() == common_duration(rhs).count();
        }
    };

    template <class LhsDuration>
    struct duration_eq<LhsDuration, LhsDuration>
    {
      BOOST_CONSTEXPR bool operator()(const LhsDuration& lhs, const LhsDuration& rhs) const
        {
            return lhs.count() == rhs.count();
        }
    };

    template <class LhsDuration, class RhsDuration>
    struct duration_lt
    {
      BOOST_CONSTEXPR bool operator()(const LhsDuration& lhs, const RhsDuration& rhs) const
        {
            typedef typename common_type<LhsDuration, RhsDuration>::type common_duration;
            return common_duration(lhs).count() < common_duration(rhs).count();
        }
    };

    template <class LhsDuration>
    struct duration_lt<LhsDuration, LhsDuration>
    {
      BOOST_CONSTEXPR bool operator()(const LhsDuration& lhs, const LhsDuration& rhs) const
        {
            return lhs.count() < rhs.count();
        }
    };

} // namespace detail

    // Duration ==

    template <class Rep1, class Period1, class Rep2, class Period2>
    inline BOOST_CONSTEXPR
    bool
    operator==(const duration<Rep1, Period1>& lhs,
          const duration<Rep2, Period2>& rhs)
    {
        return boost::chrono::detail::duration_eq<
            duration<Rep1, Period1>, duration<Rep2, Period2> >()(lhs, rhs);
    }

    // Duration !=

    template <class Rep1, class Period1, class Rep2, class Period2>
    inline BOOST_CONSTEXPR
    bool
    operator!=(const duration<Rep1, Period1>& lhs,
          const duration<Rep2, Period2>& rhs)
    {
        return !(lhs == rhs);
    }

    // Duration <

    template <class Rep1, class Period1, class Rep2, class Period2>
    inline BOOST_CONSTEXPR
    bool
    operator< (const duration<Rep1, Period1>& lhs,
          const duration<Rep2, Period2>& rhs)
    {
        return boost::chrono::detail::duration_lt<
          duration<Rep1, Period1>, duration<Rep2, Period2> >()(lhs, rhs);
    }

    // Duration >

    template <class Rep1, class Period1, class Rep2, class Period2>
    inline BOOST_CONSTEXPR
    bool
    operator> (const duration<Rep1, Period1>& lhs,
          const duration<Rep2, Period2>& rhs)
    {
        return rhs < lhs;
    }

    // Duration <=

    template <class Rep1, class Period1, class Rep2, class Period2>
    inline BOOST_CONSTEXPR
    bool
    operator<=(const duration<Rep1, Period1>& lhs,
          const duration<Rep2, Period2>& rhs)
    {
        return !(rhs < lhs);
    }

    // Duration >=

    template <class Rep1, class Period1, class Rep2, class Period2>
    inline BOOST_CONSTEXPR
    bool
    operator>=(const duration<Rep1, Period1>& lhs,
          const duration<Rep2, Period2>& rhs)
    {
        return !(lhs < rhs);
    }

//----------------------------------------------------------------------------//
//      20.9.3.7 duration_cast [time.duration.cast]                           //
//----------------------------------------------------------------------------//

    // Compile-time select the most efficient algorithm for the conversion...
    template <class ToDuration, class Rep, class Period>
    inline BOOST_CONSTEXPR
    typename boost::enable_if <
      boost::chrono::detail::is_duration<ToDuration>, ToDuration>::type
    duration_cast(const duration<Rep, Period>& fd)
    {
        return boost::chrono::detail::duration_cast<
          duration<Rep, Period>, ToDuration>()(fd);
    }

} // namespace chrono
} // namespace boost

#ifndef BOOST_CHRONO_HEADER_ONLY
// the suffix header occurs after all of our code:
#include <boost/config/abi_suffix.hpp> // pops abi_prefix.hpp pragmas
#endif

#endif // BOOST_CHRONO_DURATION_HPP

/* duration.hpp
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
*/