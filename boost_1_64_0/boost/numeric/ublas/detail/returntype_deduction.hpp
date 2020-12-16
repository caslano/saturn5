/*
 *  Copyright (c) 2001-2003 Joel de Guzman
 *
 *  Use, modification and distribution is subject to the Boost Software
 *  License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
 *    http://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef _BOOST_UBLAS_NUMERICTYPE_DEDUCTION_
#define _BOOST_UBLAS_NUMERICTYPE_DEDUCTION_

// See original in boost-sandbox/boost/utility/type_deduction.hpp for comments

#include <boost/mpl/vector/vector20.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/utility/enable_if.hpp>

namespace boost { namespace numeric { namespace ublas {

struct error_cant_deduce_type {};

  namespace type_deduction_detail
  {
    typedef char(&bool_value_type)[1];
    typedef char(&float_value_type)[2];
    typedef char(&double_value_type)[3];
    typedef char(&long_double_value_type)[4];
    typedef char(&char_value_type)[5];
    typedef char(&schar_value_type)[6];
    typedef char(&uchar_value_type)[7];
    typedef char(&short_value_type)[8];
    typedef char(&ushort_value_type)[9];
    typedef char(&int_value_type)[10];
    typedef char(&uint_value_type)[11];
    typedef char(&long_value_type)[12];
    typedef char(&ulong_value_type)[13];
    
    typedef char(&x_value_type)[14];
    typedef char(&y_value_type)[15];

    typedef char(&cant_deduce_type)[16];

    template <typename T, typename PlainT = typename remove_cv<T>::type>
    struct is_basic
        : mpl::or_<
          typename mpl::or_<
              is_same<PlainT, bool>
            , is_same<PlainT, float>
            , is_same<PlainT, double>
            , is_same<PlainT, long double>
          > ::type,
          typename mpl::or_<
              is_same<PlainT, char>
            , is_same<PlainT, signed char>
            , is_same<PlainT, unsigned char>
            , is_same<PlainT, short>
            , is_same<PlainT, unsigned short>
            > ::type,
          typename mpl::or_<
              is_same<PlainT, int>
            , is_same<PlainT, unsigned int>
            , is_same<PlainT, long>
            , is_same<PlainT, unsigned long>
            > ::type
        > {};

    struct asymmetric;

    template <typename X, typename Y>
    cant_deduce_type
    test(...); // The black hole !!!

    template <typename X, typename Y>
    bool_value_type
    test(bool const&);

    template <typename X, typename Y>
    float_value_type
    test(float const&);
    
    template <typename X, typename Y>
    double_value_type
    test(double const&);

    template <typename X, typename Y>
    long_double_value_type
    test(long double const&);

    template <typename X, typename Y>
    char_value_type
    test(char const&);

    template <typename X, typename Y>
    schar_value_type
    test(signed char const&);

    template <typename X, typename Y>
    uchar_value_type
    test(unsigned char const&);

    template <typename X, typename Y>
    short_value_type
    test(short const&);

    template <typename X, typename Y>
    ushort_value_type
    test(unsigned short const&);

    template <typename X, typename Y>
    int_value_type
    test(int const&);

    template <typename X, typename Y>
    uint_value_type
    test(unsigned int const&);

    template <typename X, typename Y>
    long_value_type
    test(long const&);

    template <typename X, typename Y>
    ulong_value_type
    test(unsigned long const&);

    template <typename X, typename Y>
    typename boost::disable_if<
        is_basic<X>, x_value_type
    >::type
    test(X const&);

    template <typename X, typename Y>
    typename boost::disable_if<
        mpl::or_<
            is_basic<Y>
          , is_same<Y, asymmetric>
          , is_same<const X, const Y>
        >
      , y_value_type
    >::type
    test(Y const&);

    template <typename X, typename Y>
    struct base_result_of
    {
        typedef typename remove_cv<X>::type x_type;
        typedef typename remove_cv<Y>::type y_type;

        typedef mpl::vector16<
            mpl::identity<bool>
          , mpl::identity<float>
          , mpl::identity<double>
          , mpl::identity<long double>
          , mpl::identity<char>
          , mpl::identity<signed char>
          , mpl::identity<unsigned char>
          , mpl::identity<short>
          , mpl::identity<unsigned short>
          , mpl::identity<int>
          , mpl::identity<unsigned int>
          , mpl::identity<long>
          , mpl::identity<unsigned long>
          , mpl::identity<x_type>
          , mpl::identity<y_type>
          , mpl::identity<error_cant_deduce_type>
        >
        types;
    };

}}} } // namespace boost::numeric::ublas ::type_deduction_detail

#endif

/* returntype_deduction.hpp
Awb0y7ft+DlZ8g+/2Jjjv/wnzvf1OA86uCv9cDspwS/HTpjIyBxs/5GZdEo/eBR4QEWwSQ9FhtTj4V7Phsts6c7Vc+jk2romcp87BTSJ9hTVXiL/TUoFYldSnVtU5xXplxPO/ZB5bvALoYI98UI7gQ07meUZBW7mR3z5i9gw8l8mdk1VOBbOnkt8oUbtxIrkoX2PVZP5ek1906qJ6vc0qNVmkYb1iy9kC+tqFyxdyN9rP5fyd96ChiaZnrR/iuThW6yT1f6ockN6Frj1f24cmyZ8w4v2VVznprlQcN6bzopflLpYHoLvB5dItSVz+VhnMt+eTuQuQiLwc+1Ix9iC2mUX+8fP9Ckr+VOmLp4ffSlrw4baeATfNOOgjnbje+DajD1t/sp8gX0qF6ayOH4+slid8zbP+xBfFgzlBjVONxsHWRdOuzUtaaTXUUQ9mFtfd0Fd/UxuXrpgSd0caFy8qH65aZ9LwQ7sgXn6pP7OSM4o5nSkeIK2i9q6GceHNGwzjk8W5IxqpnQThUeZqAnhbQS9MkN2ampQrmumniHeKZjMLRPPmAYbz5caBJ4c0FYoM7UZZBHpqoxkRnSUGbESToFdO1ObYbnDbrtPIwHDrgXmYk+1oyMVJwHTTgKiPSM33ZYJF7PdOV2djRJO9PDrHcxzGLTevmjxojpyl+NJxzRjhEV49J4Zlz9EWI+ddWMkWkV2PZcx7RVbCu2R+ZAfFNijmEeY9uolcD/IkF8Be7Xhvuu9kajyhwec6/fwy/VW4Jfrq8Qv18PfFeV4/g5lO34PIT1iUbcH9kOVHR5sgD2iziFUs7WbYD9YuFMqbYU9SqJCwXbYjya7SMl9FE6y0/M07EMM+yuwjyb9YnYy6gPCv0iFPNcB+yAuL+3jAjvlzzSSF/Yqc40JfHO2U2/Zl1n2hGXPWPYey77Osm+Avdqwb7bc77Tct1vueyz3Fyz70A8W2sfBzvH3vseLToG5nuxIoau86DKYe6S9AfYNMG+S9i2wb4b5Xq4P9lnrvOgOmGd1CveNsD8Cu6oJj8C+D/ZnJH7C1V70NZiHbpLysI8hs5B/EvYawz7hGi86Dfb5IB/lBd8DjzbAfIm0r4U9IeVrYL8X9h7Y15N7JZuw3oveDPOdZIc77Nth3qXcr/Oie2F+WrnD/oqh70nYq2+SdshH3+tFR8Few4lqOf0zp8ZRY7pLZb5w1l1RuMY0yzZEjP+UBspOJq+URar/woeP0ybpMZnotWvJQr96oNYkzvUswZmaZJ73p52Z/Jp52XhbJ46k5ISuOd1tZJqL8zZZIS/8oHMqDdkkXszEO2tJ0d814igQlEBocVdjsivZls6n4twa9LXzm/C2XgfJ183VNnqWduXircn6ZFu8ZU0YukGeR2pMvqMbwyimzKmsULBYhqOLbnSazKQZR4cmmuYYbNrME6KZ4kg8fqyIZJUh2ZJoj+V0IAlH6aXvV8ogDeS6IoU8lrWCbroJCD9G1ZVsgQ6lM6sTLoY/0qDd3FAehnw2xW1NqbaueL47m5zd0YYXN/PtnTnhnmqLdyB6lId01sghqe+QimkIYbrhaw5u9CvyrCGexSggjxNnMoywJWIkITB0/qwpn0WyUb5l0/l0S7qD5h+pLtPKOlNdsYzpHu8pdI/3FLgvpkTKGWeeFqYTSRlWPuJuTbXE84LRArvwP7UKvPONc2+y/C7oak3PS3UofHs81TV3dkM83y7wwp4he+BOAMO9lew6PIGCVWTXCrQ7KQjcSUGQP+Ru2rU+O+UT7RluL2J+lO5qNeZH4/xV8Y7u5EyKQ2eCfuOZDL1d66e6/PZ4VyLXHl/JA0Fu+XwShdPPp/FiMA7a+fJAIJc=
*/