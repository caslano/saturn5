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