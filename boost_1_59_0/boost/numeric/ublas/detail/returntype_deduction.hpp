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
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
*/