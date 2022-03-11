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