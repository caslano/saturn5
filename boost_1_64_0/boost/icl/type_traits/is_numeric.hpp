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
GQ4b9vGw19+NfMEwO7tv9jTPylMYnnee77zdZ21cwbC6+u/Vf1t08E8Mcfp56Lv7w39huHRpwtIOlzZbyfDll0te3r7+2Y4M77jjwTucJ07+mOGHHz70YVrOn29j6PHc6On/09Zcho888sMjh1wXjmF4+ukLTz/5jjEDGa5aNW7Vijd6tGR42mnVpx0sHfEVw7S0tmldCy71MNyx46wdVYevfZjh4cNvHn7kzL/kMWza1N7U0aFld4YTJkydsL7l7R8xvPHG827cuKN/D4YVFfdU5G17qyvD1q0Hti4fdqqP4S+/vPTLgkGf1jB8//1z3n984Ro/w4su+stFb958+B6G3bsv7z7y0cxODM8664uznn+z6jeG9913/X0pI8ffxPDFF//44qiXLznIsG3b9LaLJ3a9keGyZc2XtVrSZAHD3NweueNmrmrK8Ikn/vrEyxO0Uoaff37F5yfO2HOA4YgRB0f8fW/1FoaXXDLqkjnP/vHvDFesOH/Fa78NGs3wxx9//fHzVt92Yfjkk+89eVtZKJFh+/bZ7VcWnXEFw6SkdUlzV02ZwPDVV2e++saGp5sx/Nvfnv7bzOmvLmUYDN4RnLznnWEMt20bsi347XX3MmzSpFWTxDbNOzOcNMk16fL297/DMD29dfqpWYvPY3jxxR9c/P6tv61meM89t95z+pC8xQz79Lm7T878wjKGTz/9xtMPV8xMYLhlS7ctYz/802UM3e4J7tsb33mI4TvvTH7nwSvuiDA88cSkE6f0PMXN8JZbcm9Z9WrPRgwDgQcCGVv2n8kwJWVbynXfF69lGI2+EL3syU++ZfjDD7//8NEJh05mOHZss7EJaUuzGd5//+X3n3CG6w6GS5actmTEDW0eY9ihQ36H1em9HmX4wQdrPjhnzPtPMTzllCmnrMtNupPh8OGfDH/hleiPDP3+J/2hfa80Z3jCCd1PyOzbzskwHH43fNcDB95k+PjjHz7+58JZIYb79pXte/GJZ05j+OWX13551kU73mC4d2/Hvf3eXvQhwzFjTh7TZ/LCcoYrV05b+ejWvkkM1669d23WSRO/ZNir1+pe5y7Or2Q4fXrF9LdSNlzK8Kefdvx07dlfzmR46aVdL01f23Yrw8Ru2z+5bEOjvMF3vvJ9Tejqghkbb75qTasLB/3hwJtb+43/bfLJs4f85U8Hx701ZVfvhIdXz1z0zLn27/aMalb2cU/nFXfNvW7/r1/NKX23Y8atu/s+2+KBaQsG2I4/x5/jzz/1ZLOipebQzZSVYrlRo3VED7arItiiCUVq6qP/SjdeTy+uKUIgsUrK+hA9SnokDw1U98ObV/omfQjfwTJmCSlhNuQbFLS+Nqr0MFG6rMkMoepESHoC2X4spfZKK8juTfvBnIehmlC/cPTA3nWv5OoegereCSqNl5h7wRNRmZ6lqy6LTVuBy/bgOxPD0AYQShoJQOb6qk2kCJ+bl+siiCQ5FJ1v1mNwSHnRONm5IUc8cj9OlwOP2IPOlfegExzikQolnRPE6cDyeo2UmgbUAzaK6q4HsXk3XE5juq4Do9bDcKUiatMnxqkMzpq7spg2H4f3KImLd+QbhjTHwwRnlqkZgPhTUjWTJmvumPSJfPeNoaZseheRiHQ69YvHKkWFibCe5OHJyXCyW+xFivgM/WAPBzTLxNxKVhWP8EiqRzbBgoh7sFbP+iLAFabWF77BZafykihXNPlAJapAs1ZUAmVObDZweNFIRJWY+EmkgemPxorPIT2kqzGGTJsSd3LcqgdnKW3UwIPSHsEhfpSbIytdpgkWqE2cgoKoGiAzfXzeyUtz5zvo0AICqmliboA6aFx/ejy8bS+zF6evj1Y=
*/