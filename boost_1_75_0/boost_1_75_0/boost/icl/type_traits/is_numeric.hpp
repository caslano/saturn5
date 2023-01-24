/*-----------------------------------------------------------------------------+
Copyright (c) 2010-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_IS_NUMERIC_HPP_JOFA_100322
#define BOOST_ICL_TYPE_TRAITS_IS_NUMERIC_HPP_JOFA_100322

#include <limits>
#include <complex>
#include <functional>
#include <boost/type_traits/is_floating_point.hpp>
#include <boost/type_traits/is_integral.hpp>

namespace boost{ namespace icl
{

template <class Type> struct is_fixed_numeric
{
    typedef is_fixed_numeric type;
    BOOST_STATIC_CONSTANT(bool, value = (0 < std::numeric_limits<Type>::digits));
};

template <class Type> struct is_std_numeric
{
    typedef is_std_numeric type;
    BOOST_STATIC_CONSTANT(bool, 
        value = (std::numeric_limits<Type>::is_specialized));
};

template <class Type> struct is_std_integral
{
    typedef is_std_integral type;
    BOOST_STATIC_CONSTANT(bool, 
        value = (std::numeric_limits<Type>::is_integer));
};

template <class Type> struct is_numeric
{
    typedef is_numeric type;
    BOOST_STATIC_CONSTANT(bool, value = 
        (mpl::or_< is_std_numeric<Type>
                 , boost::is_integral<Type> 
                 , is_std_integral<Type> >::value) );
};

template <class Type> 
struct is_numeric<std::complex<Type> >
{
    typedef is_numeric type;
    BOOST_STATIC_CONSTANT(bool, value = true);
};

//--------------------------------------------------------------------------
template<class Type, class Compare, bool Enable = false>
struct numeric_minimum
{
    static bool is_less_than(Type){ return true; }
    static bool is_less_than_or(Type, bool){ return true; }
};

template<class Type> 
struct numeric_minimum<Type, std::less<Type>, true>
{
    static bool is_less_than(Type value)
    { return std::less<Type>()((std::numeric_limits<Type>::min)(), value); }

    static bool is_less_than_or(Type value, bool cond)
    { return cond || is_less_than(value); }
};

template<class Type> 
struct numeric_minimum<Type, std::greater<Type>, true>
{
    static bool is_less_than(Type value)
    { return std::greater<Type>()((std::numeric_limits<Type>::max)(), value); }

    static bool is_less_than_or(Type value, bool cond)
    { return cond || is_less_than(value); }
};

//--------------------------------------------------------------------------
template<class Type> 
struct is_non_floating_point
{
    typedef is_non_floating_point type;
    BOOST_STATIC_CONSTANT(bool, value = 
        (mpl::not_< is_floating_point<Type> >::value));
};

}} // namespace boost icl

#endif



/* is_numeric.hpp
l5rMHaQvIehz2MJACL2lXxt7hMa4COHIx4JUVQSZ/KbvsL3NdM9B+tMeXwni0brDlz3Y09Yvj19Dv8IeLmlOwP1TKR94/bddTAnZOHH5kebGOPmUp2v2vcUNWiB7XoewrHfGDvhVygDl+dF2aLT7ZBUZydltejtGI8X3wx2FMu/tQxO9JtDD7/ZGKsrz5h6sno7tw8bcfDe8+m+oN6IL+Kv/FmC19izmuU4VKomabeGRIHkGBsyap7h0tFCbfVpGZVW2YCrLK0lUW0gDOp8+v881KtRhQ8jiFyJ2yPlFjlADt+34TId9O7RNNPzEq1AzJK8nffyNe6VJ9vZP+uqwDtQN50ZEQUvHEizh6qSFxi2wM7i37me/mwZm6ros9jDUJBjsNm3tsOPGgHJA2jrsuLT3kN+3bdTBO2otqhEF9gk7OEsgWA+WCxefg69S4tu5iUXZ5AIWJiDYjdC+uM81slEFc0QfUOLxKJUgGMp/Z58LswpwcNjxHduixNsrtawtCm/B+jvAs1kXTii4amlDqgM5Ec0HsYO2/83eoYe2f6S0agfVbO8IGpTIZjdzYPSqMTK+shjIYSw8f9or16gydVt6MdRQQFLGovxJKZdk5av6vx7zlEykTn5+5ZGNKR+3S92yvxN+/pPD7VbmcbnsV+RnH45fwZuhZzoROoXkqGOjJ9vUedbZsdFQr0apOmlZmuDsfu66kO+H577R
*/