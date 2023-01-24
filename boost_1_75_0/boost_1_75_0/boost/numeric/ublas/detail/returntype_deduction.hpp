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
4a3H7O+/vd18HVzd5+7zO03GXmQ2MP2vgI8rVM1BlDMixlxD7p9sL5cvyPeRIYLH2N1syy7FUPLf5ZPPpaaR5oSdGSflAt3Nx7/evpipKjsVXbmp1rcDeyttXgjtjmlIvR7tux7NlvyTK47vRgU8vrKmqbtMN7MC9LhwTKWJ19opOaU0xefNldcWas7xkGiRYySMnusdh9i9C3xxnjIowOW7Vvsar+7DUwVckW/eO0T3fbw3d1EqDBUWFuvsEIex5VtLZZE6C1dRiAp63b3WGfm+eWhIqWGjXeaYW8sFGYW5/pcpEHO8rU2cwM0DKy5MGenDk9O97X0EXdfTH+VSd3Ahl29rlA/jk7H4i+5yW3tSRqTZZD/vLZA7UnplLrVSKhFitf6Zaagz5vJGVmlv8uSn9WP9eRbrqeRybsQ767Eo3xWxtw3Rp3PGqBYlunFvq4el9UUnb0ILeCk95Cs9RWhieQm3UxlMb1AN7FR4DHL1eVEvm6XUuQ7f7icu3eqCxCAHkPHv82Avb6uBVS1FmdSjsPDoU+9nnRC84m89QFwdStINirCKBJeTNguP7va1rty2s3obRaqftqB9rq3JG0pc0irwh5XM390rLZ3PuG5pVnl2yEpo/KDjKHktaUf3q9DTwaBHw3eLWaVXjSHZbvpPczu0Osl8BzcVvNxHdHkeF14i3rYZLAFtSLVf/fMCl74nhcm09J2s7y7Z
*/