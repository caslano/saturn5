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
c7iYl1SGj5/dSITRoNenqdgrIYa3tJEq6T9tqV2riXkZZnXwiTEHRuSgADUtHtTQxmYgHdWXkn+5M2w0pAP1sfU7UVMRvZAoNtscxomJye98rl3ydz63YXj0G5+7ZCKoJOBgCE4LYNeCfSIRRGup19MOAeMTDCUPNhKG0QB4Z8vwWNXKEHWOeR/HFL8RuMkCo7yjQG+d/bYfdVGtx/kRFwRm3+GTomQ/jauqYXIMwMBXSJfDHwSASZhv8shit4/+pR4IS8qIwfe/OLK/k9Fl+/+I0f1+lH/n28B/PAP/tdbSl8OcQd7uAdL1uSd0FX5pkyVRg3Pj+W1FUHig/0jMAtKcS01IfqUXK+KcfsqlKgCeGkPvuONLg8lo1EtP12wIfH3fjObsEKj0DLTzJad/o3O9mTgjc/010ckAdwaqVjL4TyaAGoK169g9iZ6Ar5E4T707DX+MHVTX9EhIgrZnbWaf5RF5E3qoZuUUc/a+Do6oJvqE3GcAycKvIqthj+BXDMekS3390UpouYPN/Y+f3NtkdYwQiJXBihgrGCGROb0C7pFcW+HRzCzfj4LmS4hMBdv33O4rUHGPWYoa1DbLzE8kJ1r5wyq31d4biSP2qQya5wOfAdHTj3qmelABHV4tOcXYoUUhlEC+t8/ElNjQFVGUQMCuzqPMdhTUK8Qbt1lBdgUK8sRNWkjfv5yDLwLPiCdJOU3N8NPjLZDr3sVIF0KiqC8TcmJl/F3DwNci2XgjfHdG+/4I+XqqKbN75EirdVApYx6Zrcf+mkLhmZHUKurQfp74QTRFkERPml4htNUzp7huEoNReiUw1pbXgwZIVaYYlMCpOssGaCjFdaUBG8C8hL+ISGIUQvyuwxMP1UnIC/ka5r02vydMlZtb9NWurXa8IwL+LDbf1SqhAoiK9GyV5w1WV4Iaaen8SK1pGKHRCqFVslcGm0WpNcJqtK91kuQLGGwwWICEQoIWJolhOcPS2TT8KoI2ijJnLTECUD+miBEoXCiLAlQ+zxcHz3mgdo3Ct7hFqw4UOzP3l73yn6wYdlvgTXNT3I3M7v5uqOBBNsvdkQ4KDEn49gTcEQHycajfMOZIZ9m7lsipvDtLS9WqtCXKFey5Wwndrd6eZ78fCszIbSiuo8gIC8Bzj1krnsp3Z8Rw25UM+eqhfb+dpohKiRcSgOcV3PPVOfsjBUZ1maaMg6X5kjf/0NlH4o4MVQw8YRu+qCn9pcL/AVJovLTrSwCAQ0vt3QVQHNm+P/DBHUKw4A5Bg7sTNIHgLsEdgrsHd3d3d9egwYNrcHd3yD9E7iZ7s3vv+99Xb/dVPSbd53fO6UlPFUzXTM9nvt3i1yn5LqseZNt0w+BbviwAKUuGwEsCOBBAKporAJ0K9gTw6i/Vuox/o8vQ/jNZAwIFBgGAgX//4tDnoxkYCCgI0O+1Li2vOTKfOwG9pEZYWtm73yfOUsy/KbFvK/jCdJUfmG7+XNT0t8TZ5RgNdkffr7mzdoWySc4dVz+uCz5EVFAFqb1NijM2PCXa7dOSW3q4SevJbhsabzeJiSXJ5+XrjBGE+vmFBbee38Vnq/KRQcbGPdlFMJv+aQKKzTtM5ykNYM6qCjSJX7g88gnAlE3JQzwtU1EUFsCMTcWfEr5aK5gUmPSqE97lRfgShg2dNTcy6xX1i7cGUz1jt3IObtF0r987b82+LzwDotR+F3ozWhOmuA2s0OOJf5FjRhArz1/K0FaP7Z6N8mEX7geqe6TyCYA4iWNcRqGwonErz91h3Z1AKTrBMuX6D6K7D5lFuMxRDdUHFfNb4GyDB/ljc9icp8q65Ajulp8Af9Z7OtDxZCCCQwNw/eKgxTn3T3r5EIr+4SNqJDvupbgoIIWdIgbPkKxbpxD83Sc0Mytj/OoXjSE6ja2+mF0qv6pfVWQdlSE7ST6CXxzvnWXp5kMQ7Qh3sQ02RleoM8VJ+rFr7xfP2/Od8ZLe5q+O1A+qO5JJOZmS1zEUV8TM98qkYPoXi1EUrl2UR5F2LWfOaEZEh2KiAImVmA2IVHaSUuExPRxVF+IjDPzFlXiMH462LQzgUW+lGX35LYBQ93gMFAToFd4y4yGajv0w/OrNR+TkfNiS06kUf0fvzcwzCR3X7I5b6TlmAdJ8T4o7JtLleoPThwTaTqvRrXAJKEz/b7IXOTEeWbOwECXyAi1z9UMGis5DZv8/JC9n5yaJF5AlIQUqwJiSipfhKUwcukIpiIaGIVQaj8r73k43TBgYCQwspmCB7lJzR6cPvyyHMUB1weXhTFqB23w/ENLQffW7gu7o7lHtym8ApTl4o0S2r5kZfha9Y3XeWf2M1Br5XynvqaHfF8J7h5Gu37cfFOAqGO6q4LMXfZeXmTKBf6PTYmhAeubrMm02Ew+1g3VX3lKuT1poed5735OaXDY0S3FDkuRNl/B+mnnRKkcjMPuYSewSm+wr73WBENWKNQjWyGb1bvkrMS8dzd/okpp/innpvmFeEPB/wrz4I4+/YF5zZDQ5jciKB8wb9u9p3lrLoMztP9a87YkmpFJ/qHn3sVYM2H7WvDc/+d3dD7uiYXLkPmRrHfB9LRX8ZcgzVSFu6x1mpGs/At7ePvgOacMJLpAExMaUqB81L+Vvmvf6B817+l/RvAfpqU48XzTvxbAEF94Xzeu4mYv76EfNe/Kj5l3/UfMO/IHmlZOTkRTwAayHLsVSwAMN4LfTyGGBxPN7vy7SHr6UQr2yp/pdS+0n521t+Qg3kfBWoZ5YCX28n8flzW+c96qNu9OPw4HoaDOiOz3OMFspLzr/kaWEZ/xbrLG+S+lnSy+/EF4Il/cv7G7h70Kjjy6xb350u/8IoT1XSN4eLS+4OHGMdel7HGqaRga+/dAoe8qawsnWMkpUEOZ7xWHLUL7fzldO2/2+uNWwxxWeYESC1T043rFUqsF1I46urO85tNvYCNP/yKEdY/u8ww1FNUV5sxrmXCtuHT+LAQoqWLAcUvg0asUsnTS3ytWlMeI+hsJKGtTERLa3EiH1T4U+IhPupwUG+z95v/m58TV6GVhR4behjv8RziAs2sacY+er6R0cJE1y8rHODFsXimnIUxLB0bZ3rI/61lXNzxmF1fIlp9pzULWlL0Il63fBSreb7Yw0geBbdPBokH2V/aT7kYzyzGn9vp4SpXTsLevzo5qApzPwXq1nYDb5KS9pg/Fya6q2rOcGKxVyaC8t/FbMUCUrsWHct6GldDByzWtZY0De4WiOw59m9jJKrLyxpIbw4OjMx976LbLWPkCGfbhsZCb0XUTpBW5RNvbm1JaJ8OueKceQiVH4U2Or6kwa7V3O7p0f6G771p92wE4N097vk/7EeDu+ZdRufsmorf0ufuXnmnguvwhedYszkKUL55fs4859Ywg+D9D3r02lZfwbRXs/AfxerX1RvT+gXjAIsD9EvREVSIQkvOYWZaRS7v8a9Wr/IerlDP9D1Hv+M+q9+gfqjfiOeq++g9yIb0L3Pxz470a9ii7x31DvzrPRb6j3Tuf6F6gXuC80+yOgfJWshoeyDtrkw4Swc6tduyL+BdAKnLbPHEQgY1in7zp+YTClEC2ctrkmq+9XznvecwAELPvTW8zIEffMt9C53JUi6BXJi2UKXOOU3uWsONKV3lystc87i9ZOCSFPtYzZyiZXDHfheDC+2bH5xC95RoZQnuf5Yigu50bRgrzg4JU3qav8bYWckdcDcEqGlhxbdeN6BfZ024IHl9R3kTm5Z3kYC/xkmkOJ0G3ekTRAsCy88wglpfrVmnmhdpmTgN5exJWKETqlOqLijfa9/DfOW9gi9o3zXvedjv4wKEW+R0IuoJrZKVxQGeuRLX2s/9sqPBV1I3rzx3WQahRupGBxb0gvobyO0BpGlwiuq6LrNOlNV1m40MKE+vkD7dUOuziLuXsQvSV/KHqT/lj07vxHohcoZtL0Il0T5jIjH+RZ8ceD5x1on7cGV1dtmPfzfbYcnBuUotruhfRonphTEpOrwQeaBL9R1CGdydkWHvklv13kGb/epAH7Zqznbcad91DxiO0wLcSV0A1cimrmQbomwnHIOUNgTk3+KdmZrCwNEk26hQ6Ujja2WN4lUr9g2B9p3xG6P9K+xgZl2W3fTRXkX5tD+zd6D/4npvfZN9MLCvNPphf1wfSi0coi4RPTaWhqfX4T/h+rXs6xX6re/V+rXmsW7eXqtXwBWZsHxzt4nyg3FyWcX1xSoHKn5ypOYSqaKSsvP17sUtGSzRxe1Jy9jaJwlWVx33UsWzP2ka8Al2FQfWpetPo6IVdWaz2u7wazR3b5O+tdNSOWD/jOesMao9Sov7PeF/9gvTdo2zozWV7TgwoBPwjfXROmBOGgJS1VjKSPeXLDBsXR8QaSwy2jtHQJT5Ohdw8JmL2CLLdtbbKUBbLrlQyyhAQ/AUQfgmbtyDfcERspjVKkG6rIZ6gYR0bFyNmYr+UeYO87eQ543K8Bs7iSHfvLR8cPfJclaU6NS2rfyZm/IaC79wHqfs2ePTqD33+GS2bLxZXalKimoK79cC+v3eWjtpsHBvw1g3b6gQY7oMYFB4ejstKsl+XmHb3bVNJlY1NQOG2P70rP6YZIM4jd3NLQGoU3wvBPwcL9K2EvM83fyMD/AvYCf36+gH6/8OKXDFqQf4a9BJIaYMh0vO5/KntzwvsjUaV9ite+59GSrVYQg0Uu7dS1zhWEPcTK/r6F6qvv/PBF9E5Q+2js81nsl1mxI5jjnsE82hjwu9UWuuPrYD3RdEVH/ASQKIN3mkrpEhG3jsZCpeHWCpdO0vEBC0SYWo3cUNR4pwVyzsrwPXjWwDwu2a3f6mJuZIWeEyh266D2B9iLldZoM0SPvV15fs/Zb5s/Ont5QTtf8MpsZa4MbYWXsP/HdR4K0rZGzjW4jL/fGc3oHQi5wPPrWIN79+CoiYNUFC5BnIws64ZNsFdhPrlbqqbXQNKrGttG5t4SGXMTK7BpQnVFXeh8IebFmJJBb2YCjbzH9LD9cr8vOjp0KV0XFGSR98x1ii9zjpq68rNOUuSDV2SlroYKus3z85w2xldqS5QyHnMm+p/l0xJOv//aiUeGzRWDBpch8QIhR0w0DCVkGccTNM/nifzqenUQpEs7d6am+cd2aR3OmWBeeOGXfgKEKqmQwfnceowsCRtzr76aZbknLamATKk2v32lrovIbbxymdzcT1SCXol2wAH0IbxR94N64yEE34P0dTlpxYYa8UQGYZPQdNMThZWA1R9O+7Mwmr8Q+LLQ/kvgq2rrQQPrTdbJR5FwjrdsbomEeCUFsffpk5kRdK6lgm3Zi/mA5FAuKpH4iXLBIAeiLtaUlfs+uAjjT+sZPrXOJG8bm40wD8Sx5AiiMy+BcCnHeZhfS22pzzXHwi4jGVw0UiUmQNXg+PegFY+f+M0jHlnnTlKls0d3Z91WFiXnQJQKVyQee7/js+9+cRGOdEjsHksUKN4eCX0cgSYvfUQEQpiVL4q0K0GMEHepD0/LQIS4lhbud8cuj04OVrtiKTxSYDhjiqfnCdHHHBBsVkmxf1FV8br0vkKnu2a81jtQPDnsoLwsQwtxOyV0BddOroAgvGI/IJYrJGdCKACs46yc6aheNbHxjOQDsbbZsjSLmNmsw6T0ojQSLs/dm3EHS33OatqjYEGYJEIKjUBdErWaYC8b2Vo2V7yPKe/fR0g7ul8azVYv9Sq4RhE1JKWqb0KFxG8N6ORj70CZLTlNqlowT8+0D3mSEunPq27wac/WhkKwNfdl3L9YmHmGDfd3QsDMrP8aAZd74sEKXLR0qDwOLw33efSIYoJLNzE/UeUk63kNGGoPKwzphx3RdKXheqJJ9ntD4ObHuRPHxu/IDQiPXgNNm7lZzjQN3j4Z1Q1YU9ZOPMK9FcYsvnRMfpbWLE9CRXuI4EUkbis9Vp/NGFE1YcClMfeyDQD7qsKcSKlkblqunyq2emvDNlwDiJZ5kcFemd9jWET8KtTAacwni33AyQXvDDh/I2zOwSBmrUO14wb1WjalDNlTeCiGxcLt3oPEzOiIr5kWr1IgIod9wej1+2y2O1gftoNu0OPFhnLB4OgxcRwTTVa7Hev4cgem1qYs8oOUJi0703dprtrTfOh6Tnar5rlt8Sf2JJAh91Ph9cNveRxGhCp1IoIXKQYw1dDezgDemotWBi6vOhLztWD2xZatCSfcjnw+ckvLO684bYAM9GqqTq0s+hc6H2vxdNF02xN2h/Qm5ewA0fcrU9md37dFUNkHx+Fv6VJjJltFM4S8O0m+uQKKxaWIjIhfZ8tm40oRwsz/9KYxLNLeoq5x5anect0hhVk1V+Sph1Ed1uv7Y7CbKZ+oZ7S7q5ksOM7TJsTP6iteq9OdLK1+5Gu81KI2RO4cctWTqXUqEeMnl5k8UqZsQguvugjrAb8H2WvOf/J38MD0jP+DAbssAqxMLKxMAozMzIwMfEy8fPTMDIwsLMyCNM8FGGkYmLjwOJhpWBkZ6VkZWQUFGJmY6eiYGXlZWRme89MxMPHRf368/z0eGBzv8zIMAIKuAQAhhACAkPMAQOjnACBcJAAQAT8AiDgVAET6HgBELgUAogD5Uw9MS0NL+38e+N/0wKys/ypf11qO3YL4gQM3eGpCGAGIuPqTWObeQ0gs8xhNkhQf78E9WnydeUGZJ1qI8zhFEGR1qHuou5L5cOH64n7laOeAe3GvpuUOyQmTBcLT9RLcskjh7k2kgpsJaL706xJI73VoDaopvVAxS9zjSpa7/RxEn/HBKkpbD4wM/SmNtuP37cenPLFI1ing5Uvc7uSbbSwg7wnlLfuPP8YqK/du3Xj7813VUfbyFDZSL5RzYKnvjcpHsr1aTQp659d4Up0HGWVLrx3Qa0tfJ9w9F8a4EQA1uJUmPboipaM5Na10ZdOVI6zLPtCFHTBaWHrZJ27+rM4woNxO19t2oZf0OHhk8fn8NAs74JX97PLxR9gi98gCXQvaZ3bLTnGjR1lsRgNp7PPFy3AN4w3DcoLKxmBVBw0TbL1yOnqj23uNB2xm3vWE8T37ieu3pwqJ+9uAgbjxLXLg5X5y2yYE1Bxl9KYKlDHUlJubu6PuZyEtmpCvYd0PHGHnnuuQpTwBId8RHgnOjcZuk70MNXr2wjKNIRN6FlWVbAhKilQYidphUDx1dM6krOyV1iIfe2/11DTHxt395QmB7z5okDUbKNWcsYc31gAKBsUEQ56nHKKVBuwba9WMVfJXOybDeojR5NQLELOgdXJcGc10KbzqlEw2Fx/1haZR2RM2Gg9Ag15Bt2k+7op2fETERZKfBWPtIxq+ixknM2qSZyyrYSVm2OrzkjEWAbOgrENLuzwZT1D/076uhyEECqUUKWK20DuysGVuR+EK3WXpXAKSgzQMkOS9Mr8ARs7hVXPBNje2FcvFqQ78csPKHWsRKUmWJYynaF3U2/QATFk2ylDEyakGO0fdSzV/ewowxxsQM59Rn9uprMUlU6uM5fUYL5EDP156rPqt217kNJP+NT89JdrcV8eY12WSegrLkbh0w5fUu84d5jjWYbtEHdappWVLWg6rpyhKy/Q2C2Xrnb4Hg3nourvBZM1NvaSPEYJW4gOAa/BJos1iYJqEtlfCwyY+pfu6mNTXBHlbGOtUqiX5up8f9mO2PhOfEXA4dn0GacurqTU+Pm7vkCGJGi5hy9K9pdln4+zngH9OLtFGW0GhXYwBpN3MKDKpOIk3zUafoJrKyENwtR3Hx82VRjoREoPutPtYf9NuxdK+QkFUrANddI9Q38Emr1/F/mYCu1Sg07bghox/GjOF8A1c4a6nOylmMtC+Hj7ODhbdy0IC0TwgUun5UeuEy7eJZ6BYMkMA2myHp3UjcpxI+/pz2T1jgdMKuy18B4XX0mnJCSWSGvOyMGMLqQ44bxxI2t9ck7uwVDktu/Q9GyfN4/p0c3+JEDMj5/l/TPbffs/O+Ddmsl9+fvxmLvDXkMuH6y6BAsCAQGGAfvhg9WtWrTmBpMUSKBEdPYNGWHr5u+Gj30XEXT/cvtNFgsjw0PNunMcnTYfsvX9Ud1nVeMSF4GBOVFcFbpmB0eNwMBeZGKGPzEPrctiZKc1M3Gk1P0tTPgu+bPYym2BfvkaJabbrItUJe43RLEbZdNJFy04ZABg/NtA5SKb1m9ZWAC+JEN3e3rYsG/IaMN3YEP2n4gXio27f4+d27gS+Ey3jvr5aHfYEHDxhz43Utzue0y5zhOHgCaczlpyZl1WLkCCggry74VvRMg5/iUMJ4Xnu1dU1TRTLoYAAsQdDz4urywSMc2+ODUGsq0+429XKvzBImLpaOADqHDsF6XjVYYUVVTrXA8LY5++dM2MbPmWq7R6/1skvvcfeY8xMxzNgsZyWd560Wlxc7Osvfll7C39Hxr68csh+mnkQENJ6MCJwkHOE0EGkdu366Jbva4eScUwvcXdWf5NjT6M4g2NDd1aId8MIzhp9g51phg2BXcY9Fl+ffTy5MZ+n/1El9vaQmiyeLqQS/JleCbm/v69vFpGp5cw5B0MlYm7TzuWf9RqQTTXsLT0TV3S9zF+UCa6jxbCwDjLpyyP/OCEqNLzaZ2Vf1Gp6g7HtkIcrFEE1vF4D1LBrlLed6YzzskYofg78oKw4J/+0RPQ0/R9/GgR/JWulY/3fFz1L8+jzUwwMGOTHD+ke8Do+ryQSMi3oQ/QsIQOfhXvakpR02O812Knww80QaJJU/7cVNZsEr/mIB0xw5CMV6zSPlSJYNGz91++2PMERXj6hcXjd1tbWFQi9g0FDUajfWlxGavGEQKJugbdRZM4bMpLa9oPZY1t8D2KYpFPMtiMSuRmqSWWV0SwNuwgKE9SdomKDkdJGkajqAOuJSYYtBUPxefVDjTx2e9d33pl7a58A4LTxhjBBb2VARA+eDDCCdbWRA2XZBurGe6xooABGGjqDhWIDsEJoUVlxNElZX/TqqGX/3KAqQp+/8ZBB8sDXCS3RgyTmZSH4xxAhMEXjh7amRZc2GoKGAViKeYjd34ZQtTPbnuInKAeDZ/+6xIKZn5t+tu/6aFHtfL3H1fLSB/iihunFTUqHHAXK2+hJFUZpfiiq4lrDbO/HyqpvxsVgNS7eXinfBnIdplC4hvnMI62ZHUO5EC3EuvL93CAzwk7npLae4sZKjNHrJns=
*/