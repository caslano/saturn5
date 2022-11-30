//  ratio.hpp  ---------------------------------------------------------------//

//  Copyright 2008 Howard Hinnant
//  Copyright 2008 Beman Dawes
//  Copyright 2009 Vicente J. Botet Escriba

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

/*

This code was derived by Beman Dawes from Howard Hinnant's time2_demo prototype.
Many thanks to Howard for making his code available under the Boost license.
The original code was modified to conform to Boost conventions and to section
20.4 Compile-time rational arithmetic [ratio], of the C++ committee working
paper N2798.
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

// The way overflow is managed for ratio_less is taken from llvm/libcxx/include/ratio

#ifndef BOOST_RATIO_RATIO_HPP
#define BOOST_RATIO_RATIO_HPP

#include <boost/ratio/config.hpp>
#include <boost/ratio/detail/mpl/abs.hpp>
#include <boost/ratio/detail/mpl/sign.hpp>
#include <boost/ratio/detail/mpl/gcd.hpp>
#include <boost/ratio/detail/mpl/lcm.hpp>
#include <cstdlib>
#include <climits>
#include <limits>
#include <boost/cstdint.hpp>
#include <boost/type_traits/integral_constant.hpp>
#include <boost/core/enable_if.hpp>
#include <boost/integer_traits.hpp>
#include <boost/ratio/ratio_fwd.hpp>
#include <boost/ratio/detail/overflow_helpers.hpp>
#ifdef BOOST_RATIO_EXTENSIONS
#include <boost/rational.hpp>
#include <boost/ratio/mpl/rational_c_tag.hpp>
#endif

//
// We simply cannot include this header on gcc without getting copious warnings of the kind:
//
// boost/integer.hpp:77:30: warning: use of C99 long long integer constant
//
// And yet there is no other reasonable implementation, so we declare this a system header
// to suppress these warnings.
//
#if defined(__GNUC__) && (__GNUC__ >= 4)
#pragma GCC system_header
#endif

namespace boost
{


//----------------------------------------------------------------------------//
//                                                                            //
//                20.6.1 Class template ratio [ratio.ratio]                   //
//                                                                            //
//----------------------------------------------------------------------------//

template <boost::intmax_t N, boost::intmax_t D>
class ratio
{
    static const boost::intmax_t ABS_N = mpl::abs_c<boost::intmax_t, N>::value;
    static const boost::intmax_t ABS_D = mpl::abs_c<boost::intmax_t, D>::value;
    BOOST_RATIO_STATIC_ASSERT(ABS_N >= 0, BOOST_RATIO_NUMERATOR_IS_OUT_OF_RANGE, ());
    BOOST_RATIO_STATIC_ASSERT(ABS_D > 0, BOOST_RATIO_DENOMINATOR_IS_OUT_OF_RANGE, ());
    BOOST_RATIO_STATIC_ASSERT(D != 0, BOOST_RATIO_DIVIDE_BY_0 , ());
    static const boost::intmax_t SIGN_N = mpl::sign_c<boost::intmax_t,N>::value
      * mpl::sign_c<boost::intmax_t,D>::value;
    static const boost::intmax_t GCD = mpl::gcd_c<boost::intmax_t, ABS_N, ABS_D>::value;
public:
    BOOST_STATIC_CONSTEXPR boost::intmax_t num = SIGN_N * ABS_N / GCD;
    BOOST_STATIC_CONSTEXPR boost::intmax_t den = ABS_D / GCD;

#ifdef BOOST_RATIO_EXTENSIONS
    typedef mpl::rational_c_tag tag;
    typedef boost::rational<boost::intmax_t> value_type;
    typedef boost::intmax_t num_type;
    typedef boost::intmax_t den_type;
    ratio()
    {}
    template <boost::intmax_t _N2, boost::intmax_t _D2>
    ratio(const ratio<_N2, _D2>&,
        typename enable_if_c
            <
                (ratio<_N2, _D2>::num == num &&
                ratio<_N2, _D2>::den == den)
            >::type* = 0)
    {}

    template <boost::intmax_t _N2, boost::intmax_t _D2>
        typename enable_if_c
        <
            (ratio<_N2, _D2>::num == num &&
            ratio<_N2, _D2>::den == den),
            ratio&
        >::type
    operator=(const ratio<_N2, _D2>&) {return *this;}

    static value_type value() {return value_type(num,den);}
    value_type operator()() const {return value();}
#endif
    typedef ratio<num, den> type;
};

#if defined(BOOST_NO_CXX11_CONSTEXPR)
template <boost::intmax_t N, boost::intmax_t D>
const    boost::intmax_t ratio<N, D>::num;
template <boost::intmax_t N, boost::intmax_t D>
const    boost::intmax_t ratio<N, D>::den;
#endif

//----------------------------------------------------------------------------//
//                                                                            //
//                20.6.2 Arithmetic on ratio types [ratio.arithmetic]         //
//                                                                            //
//----------------------------------------------------------------------------//

template <class R1, class R2>
struct ratio_add
: boost::ratio_detail::ratio_add<R1, R2>::type
{
};

template <class R1, class R2>
struct ratio_subtract
: boost::ratio_detail::ratio_subtract<R1, R2>::type
{
};

template <class R1, class R2>
struct ratio_multiply
: boost::ratio_detail::ratio_multiply<R1, R2>::type
{
};

template <class R1, class R2>
struct ratio_divide
: boost::ratio_detail::ratio_divide<R1, R2>::type
{
};

//----------------------------------------------------------------------------//
//                                                                            //
//                20.6.3 Comparision of ratio types [ratio.comparison]        //
//                                                                            //
//----------------------------------------------------------------------------//

// ratio_equal

template <class R1, class R2>
struct ratio_equal
    : public boost::integral_constant<bool,
                               (R1::num == R2::num && R1::den == R2::den)>
{};

template <class R1, class R2>
struct ratio_not_equal
    : public boost::integral_constant<bool, !ratio_equal<R1, R2>::value>
{};

// ratio_less

template <class R1, class R2>
struct ratio_less
    : boost::integral_constant<bool, boost::ratio_detail::ratio_less<R1, R2>::value>
{};

template <class R1, class R2>
struct ratio_less_equal
    : boost::integral_constant<bool, !ratio_less<R2, R1>::value>
{};

template <class R1, class R2>
struct ratio_greater
    : boost::integral_constant<bool, ratio_less<R2, R1>::value>
{};

template <class R1, class R2>
struct ratio_greater_equal
    : boost::integral_constant<bool, !ratio_less<R1, R2>::value>
{};

template <class R1, class R2>
struct ratio_gcd :
    ratio<mpl::gcd_c<boost::intmax_t, R1::num, R2::num>::value,
        mpl::lcm_c<boost::intmax_t, R1::den, R2::den>::value>::type
{
};

    //----------------------------------------------------------------------------//
    //                                                                            //
    //                More arithmetic on ratio types [ratio.arithmetic]           //
    //                                                                            //
    //----------------------------------------------------------------------------//

#ifdef BOOST_RATIO_EXTENSIONS
template <class R>
struct ratio_negate
    : ratio<-R::num, R::den>::type
{
};
template <class R>
struct ratio_abs
    : ratio<mpl::abs_c<boost::intmax_t, R::num>::value, R::den>::type
{
};
template <class R>
struct ratio_sign
    : mpl::sign_c<boost::intmax_t, R::num>
{
};

template <class R>
struct ratio_inverse
    : ratio<R::den, R::num>::type
{
};


template <class R1, class R2>
struct ratio_lcm :
    ratio<mpl::lcm_c<boost::intmax_t, R1::num, R2::num>::value,
        mpl::gcd_c<boost::intmax_t, R1::den, R2::den>::value>::type
{
};

template <class R1, class R2>
struct ratio_modulo :
    ratio<(R1::num * R2::den) % (R2::num * R1::den), R1::den * R2::den>::type
{
};

namespace detail {
  template <class R1, class R2, bool r1ltr2>
  struct ratio_min : R1 {};
  template <class R1, class R2>
  struct ratio_min<R1,R2,false> : R2 {};

  template <class R1, class R2, bool r1ltr2>
  struct ratio_max : R2 {};
  template <class R1, class R2>
  struct ratio_max<R1,R2,false> : R1 {};
}

template <class R1, class R2>
struct ratio_min : detail::ratio_min<R1, R2, ratio_less<R1,R2>::value>::type
{
};

template <class R1, class R2>
struct ratio_max : detail::ratio_max<R1, R2, ratio_less<R1,R2>::value>::type
{
};

template<typename R, int p>
struct ratio_power :
  ratio_multiply<
    typename ratio_power<R, p%2>::type,
    typename ratio_power<typename ratio_multiply<R, R>::type, p/2>::type
  >::type
{};

template<typename R>
struct ratio_power<R, 0> : ratio<1>::type {};

template<typename R>
struct ratio_power<R, 1> : R {};

template<typename R>
struct ratio_power<R, -1> : ratio_divide<ratio<1>, R>::type {};

#endif
}  // namespace boost


#endif  // BOOST_RATIO_RATIO_HPP

/* ratio.hpp
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
*/