//  duration.hpp  --------------------------------------------------------------//

//  Copyright 2008 Howard Hinnant
//  Copyright 2008 Beman Dawes
//  Copyright 2009-2012 Vicente J. Botet Escriba

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


#ifndef BOOST_CHRONO_TIME_POINT_HPP
#define BOOST_CHRONO_TIME_POINT_HPP

#include <boost/chrono/duration.hpp>

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

  template <class Clock, class Duration = typename Clock::duration>
    class time_point;


} // namespace chrono


// common_type trait specializations

template <class Clock, class Duration1, class Duration2>
  struct common_type<chrono::time_point<Clock, Duration1>,
                     chrono::time_point<Clock, Duration2> >;


//----------------------------------------------------------------------------//
//      20.9.2.3 Specializations of common_type [time.traits.specializations] //
//----------------------------------------------------------------------------//


template <class Clock, class Duration1, class Duration2>
struct common_type<chrono::time_point<Clock, Duration1>,
                   chrono::time_point<Clock, Duration2> >
{
  typedef chrono::time_point<Clock,
    typename common_type<Duration1, Duration2>::type> type;
};



namespace chrono {

    // time_point arithmetic
    template <class Clock, class Duration1, class Rep2, class Period2>
    inline BOOST_CONSTEXPR
    time_point<Clock,
        typename common_type<Duration1, duration<Rep2, Period2> >::type>
    operator+(
            const time_point<Clock, Duration1>& lhs,
            const duration<Rep2, Period2>& rhs);
    template <class Rep1, class Period1, class Clock, class Duration2>
    inline BOOST_CONSTEXPR
    time_point<Clock,
        typename common_type<duration<Rep1, Period1>, Duration2>::type>
    operator+(
            const duration<Rep1, Period1>& lhs,
            const time_point<Clock, Duration2>& rhs);
    template <class Clock, class Duration1, class Rep2, class Period2>
    inline BOOST_CONSTEXPR
    time_point<Clock,
        typename common_type<Duration1, duration<Rep2, Period2> >::type>
    operator-(
            const time_point<Clock, Duration1>& lhs,
            const duration<Rep2, Period2>& rhs);
    template <class Clock, class Duration1, class Duration2>
    inline BOOST_CONSTEXPR
    typename common_type<Duration1, Duration2>::type
    operator-(
            const time_point<Clock, Duration1>& lhs,
            const time_point<Clock,
            Duration2>& rhs);

    // time_point comparisons
    template <class Clock, class Duration1, class Duration2>
    inline BOOST_CONSTEXPR
    bool operator==(
          const time_point<Clock, Duration1>& lhs,
          const time_point<Clock, Duration2>& rhs);
    template <class Clock, class Duration1, class Duration2>
    inline BOOST_CONSTEXPR
    bool operator!=(
          const time_point<Clock, Duration1>& lhs,
          const time_point<Clock, Duration2>& rhs);
    template <class Clock, class Duration1, class Duration2>
    inline BOOST_CONSTEXPR
    bool operator< (
          const time_point<Clock, Duration1>& lhs,
          const time_point<Clock, Duration2>& rhs);
    template <class Clock, class Duration1, class Duration2>
    inline BOOST_CONSTEXPR
    bool operator<=(
          const time_point<Clock, Duration1>& lhs,
          const time_point<Clock, Duration2>& rhs);
    template <class Clock, class Duration1, class Duration2>
    inline BOOST_CONSTEXPR
    bool operator> (
          const time_point<Clock, Duration1>& lhs,
          const time_point<Clock, Duration2>& rhs);
    template <class Clock, class Duration1, class Duration2>
    inline BOOST_CONSTEXPR
    bool operator>=(
          const time_point<Clock, Duration1>& lhs,
          const time_point<Clock, Duration2>& rhs);

    // time_point_cast
    template <class ToDuration, class Clock, class Duration>
    inline BOOST_CONSTEXPR
    time_point<Clock, ToDuration> time_point_cast(const time_point<Clock, Duration>& t);

//----------------------------------------------------------------------------//
//                                                                            //
//      20.9.4 Class template time_point [time.point]                         //
//                                                                            //
//----------------------------------------------------------------------------//

    template <class Clock, class Duration>
    class time_point
    {
        BOOST_CHRONO_STATIC_ASSERT(boost::chrono::detail::is_duration<Duration>::value,
                BOOST_CHRONO_SECOND_TEMPLATE_PARAMETER_OF_TIME_POINT_MUST_BE_A_BOOST_CHRONO_DURATION, (Duration));
    public:
        typedef Clock                     clock;
        typedef Duration                  duration;
        typedef typename duration::rep    rep;
        typedef typename duration::period period;
        typedef Duration                  difference_type;

    private:
        duration d_;

    public:
        BOOST_FORCEINLINE BOOST_CONSTEXPR
        time_point() : d_(duration::zero())
        {}
        BOOST_FORCEINLINE BOOST_CONSTEXPR
        explicit time_point(const duration& d)
            : d_(d)
        {}

        // conversions
        template <class Duration2>
        BOOST_FORCEINLINE BOOST_CONSTEXPR
        time_point(const time_point<clock, Duration2>& t
                , typename boost::enable_if
                <
                    boost::is_convertible<Duration2, duration>
                >::type* = 0
        )
            : d_(t.time_since_epoch())
        {
        }
        // observer

        BOOST_CONSTEXPR
        duration time_since_epoch() const
        {
            return d_;
        }

        // arithmetic

#ifdef BOOST_CHRONO_EXTENSIONS
        BOOST_CONSTEXPR
        time_point  operator+() const {return *this;}
        BOOST_CONSTEXPR
        time_point  operator-() const {return time_point(-d_);}
        time_point& operator++()      {++d_; return *this;}
        time_point  operator++(int)   {return time_point(d_++);}
        time_point& operator--()      {--d_; return *this;}
        time_point  operator--(int)   {return time_point(d_--);}

        time_point& operator+=(const rep& r) {d_ += duration(r); return *this;}
        time_point& operator-=(const rep& r) {d_ -= duration(r); return *this;}

#endif

        time_point& operator+=(const duration& d) {d_ += d; return *this;}
        time_point& operator-=(const duration& d) {d_ -= d; return *this;}

        // special values

        static BOOST_CHRONO_LIB_CONSTEXPR time_point
        min BOOST_PREVENT_MACRO_SUBSTITUTION ()
        {
            return time_point((duration::min)());
        }
        static BOOST_CHRONO_LIB_CONSTEXPR time_point
        max BOOST_PREVENT_MACRO_SUBSTITUTION ()
        {
            return time_point((duration::max)());
        }
    };

//----------------------------------------------------------------------------//
//      20.9.4.5 time_point non-member arithmetic [time.point.nonmember]      //
//----------------------------------------------------------------------------//

    // time_point operator+(time_point x, duration y);

    template <class Clock, class Duration1, class Rep2, class Period2>
    inline BOOST_CONSTEXPR
    time_point<Clock,
        typename common_type<Duration1, duration<Rep2, Period2> >::type>
    operator+(const time_point<Clock, Duration1>& lhs,
            const duration<Rep2, Period2>& rhs)
    {
      typedef typename common_type<Duration1, duration<Rep2, Period2> >::type CDuration;
      typedef time_point<
          Clock,
          CDuration
      > TimeResult;
        return TimeResult(lhs.time_since_epoch() + CDuration(rhs));
    }

    // time_point operator+(duration x, time_point y);

    template <class Rep1, class Period1, class Clock, class Duration2>
    inline BOOST_CONSTEXPR
    time_point<Clock,
        typename common_type<duration<Rep1, Period1>, Duration2>::type>
    operator+(const duration<Rep1, Period1>& lhs,
            const time_point<Clock, Duration2>& rhs)
    {
        return rhs + lhs;
    }

    // time_point operator-(time_point x, duration y);

    template <class Clock, class Duration1, class Rep2, class Period2>
    inline BOOST_CONSTEXPR
    time_point<Clock,
        typename common_type<Duration1, duration<Rep2, Period2> >::type>
    operator-(const time_point<Clock, Duration1>& lhs,
            const duration<Rep2, Period2>& rhs)
    {
        return lhs + (-rhs);
    }

    // duration operator-(time_point x, time_point y);

    template <class Clock, class Duration1, class Duration2>
    inline BOOST_CONSTEXPR
    typename common_type<Duration1, Duration2>::type
    operator-(const time_point<Clock, Duration1>& lhs,
            const time_point<Clock, Duration2>& rhs)
    {
        return lhs.time_since_epoch() - rhs.time_since_epoch();
    }

//----------------------------------------------------------------------------//
//      20.9.4.6 time_point comparisons [time.point.comparisons]              //
//----------------------------------------------------------------------------//

    // time_point ==

    template <class Clock, class Duration1, class Duration2>
    inline BOOST_CONSTEXPR
    bool
    operator==(const time_point<Clock, Duration1>& lhs,
             const time_point<Clock, Duration2>& rhs)
    {
        return lhs.time_since_epoch() == rhs.time_since_epoch();
    }

    // time_point !=

    template <class Clock, class Duration1, class Duration2>
    inline BOOST_CONSTEXPR
    bool
    operator!=(const time_point<Clock, Duration1>& lhs,
             const time_point<Clock, Duration2>& rhs)
    {
        return !(lhs == rhs);
    }

    // time_point <

    template <class Clock, class Duration1, class Duration2>
    inline BOOST_CONSTEXPR
    bool
    operator<(const time_point<Clock, Duration1>& lhs,
            const time_point<Clock, Duration2>& rhs)
    {
        return lhs.time_since_epoch() < rhs.time_since_epoch();
    }

    // time_point >

    template <class Clock, class Duration1, class Duration2>
    inline BOOST_CONSTEXPR
    bool
    operator>(const time_point<Clock, Duration1>& lhs,
            const time_point<Clock, Duration2>& rhs)
    {
        return rhs < lhs;
    }

    // time_point <=

    template <class Clock, class Duration1, class Duration2>
    inline BOOST_CONSTEXPR
    bool
    operator<=(const time_point<Clock, Duration1>& lhs,
             const time_point<Clock, Duration2>& rhs)
    {
        return !(rhs < lhs);
    }

    // time_point >=

    template <class Clock, class Duration1, class Duration2>
    inline BOOST_CONSTEXPR
    bool
    operator>=(const time_point<Clock, Duration1>& lhs,
             const time_point<Clock, Duration2>& rhs)
    {
        return !(lhs < rhs);
    }

//----------------------------------------------------------------------------//
//      20.9.4.7 time_point_cast [time.point.cast]                            //
//----------------------------------------------------------------------------//

    template <class ToDuration, class Clock, class Duration>
    inline BOOST_CONSTEXPR
    time_point<Clock, ToDuration>
    time_point_cast(const time_point<Clock, Duration>& t)
    {
        return time_point<Clock, ToDuration>(
                duration_cast<ToDuration>(t.time_since_epoch()));
    }

} // namespace chrono
} // namespace boost

#ifndef BOOST_CHRONO_HEADER_ONLY
// the suffix header occurs after all of our code:
#include <boost/config/abi_suffix.hpp> // pops abi_prefix.hpp pragmas
#endif

#endif // BOOST_CHRONO_TIME_POINT_HPP

/* time_point.hpp
qOydSF9OZbdK1+tTyfH4On8/bveP0ugcBsVYDmDaQTP1j+QExN1eJpfLLxQ8EIhr3GiOl29ZbpNzbC3k9ojfyjn2LnhDxEPy+uhG8gnnJnmd61L5qvt+Oc/TVe6Je1DeGN9RvpZwmyxPaigvRvmDufwDpOPwRqXiZnzHvostwv6cOhz1hTods1cdif1Kyfg/KJH0hTKn/FZ91GC6pstmsexu0m1RfbfYrD5RG9Vq8y41xXZQTbcfUnOiP1aFrh/VTA/+jn9PFSd9RHHfI1j2Iqsu+6VKFBsU2wD2QB9sVPW+/6t0GzDNbNFpU5JSREdZhuiGz9VmtcH8jJpnK5BnIgrlPPs1MiIqXy6IvlL+6MyXK1E7a+x4OddTICO8+fKu+CEyMnGYbIIyB3KZX1K9H2s0GW27QH6oKkxbVS+rSS6x7U1qA75BzPeOXef7FDHzr6mTqOUR8zfquO1rddL+ufo++qg649pH+g9m/ucbkj0phnEI05ZSXZ9ATMRM24O2E+q39r+oddHfqy2ug+oRz2GSH8q800w6b6kgWzHtBYdOeyt+jvjOS3bhGO2HqNxDyZ0QC/Olek5tN6+U461d5WbbSjk2sq980n6LHB7VR26JXi3Hx1whn3MtlCNjh8o3PJWywNtXvhj/jLozqZ9M0tuUy+wVoZf5RnxXRG2eVrd6qB6cN4/aYUd8J5Fn+63tC9Tjz+oh1ONx1wH1O9SjL3ivYt7jZN81jcaIgfKIjJRl2h0qxbJWvWnbpdbbD6j10V+pDa7P1W88J9Tv4g+qLUnfqm0pT6iZqfEUSzOSy3miEdWddOzH8cl5Nvq2Sny0KIj+dfR+Gz0vnDeH+uTjyZGilxwnR8s31BWyuam7nGmeJA9bhsmrEJv0YUSRHG6fKfc7Jsmh0eXyHWeRvMo1X37uLpAjPbPkl3E5cmT8fPlNQoEcm9Sf4ugGcflrqXynoDZn2kJ6bi8lWhbTHiS9c4g2hGn70ikWCeMg7MS0Q2TTWXhNzxOIb92h1pvfUStsx9Vq+4dqafQPapXrO3W/54haF/+caqL3E5ZzU788jZijneobdQj98pA6avvWfDL6EJ0lGM58P1I7PNNoqFgrR6qchr3YVqnIO6nIVmmaeBGxVM+rJebn1FDbK6qp/TvVOPpn1cr1rUrzWLW28cdVm6SvVFLK8+qLBi9T+YO4DDuVsbNRH3iLGstVabm6DTjvbrLVRnz+vjd+mWaolxENlKjtUO+aS9QAW7Z41Ha3GmzPFpvtd6gh0Tniiejb1JWun9Rwz2jxO89KNSp+NJ6a1WpY0pXioaQi5U3pL/JSehvPC8XrxVfF7c8ELVNyzLBGMan1EA9uqjC1FxtNhZZ69stFrn2h/NbRW3SM+kTUi+4mxkSvlCed3UQnxMI3dHUT4103ycPuHqJd7E+ivaeVyPXcIc/E9cB3iN4XyfE9xLj4jdKemCG6J34vOiRliIlJt2N47+Ebw+nes6ndNcxEYGemZWlEw/TvC3UYln7K/IKaa9unhtqFNiJaaWNcP6trPH9To+MtWl7SZ6p/yjaKax7I8reQ/JfKLj5UNDYx3UTjwof4bPwf1MfqhPrUfET90faz+tp+WO2Ptmifuz6jthrM/JdH6vzfx/cRJ8UEWe5NQ14W5zWhtkqpb4MX1IFo6He1ZfH5ydtIfgTzOKmtn0zrKb6PHGHvifGMbE7+mw3pVfWm/sW0LRo9F2lR4l31mXpDbTXvVrNsn6lc+2k1LvqEGumyabmek2psvF27NukjdUXKOvVtgy6qvq4Xl9GS7jkqzSbuxy/Mb9VY8+l6um2HcP6L9Pw0StHEX+GvfU2+rl5Xd5v/om7AOLsQdpg=
*/