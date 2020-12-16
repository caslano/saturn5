//  Boost common_factor_ct.hpp header file  ----------------------------------//

//  (C) Copyright Daryle Walker and Stephen Cleary 2001-2002.
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history. 

#ifndef BOOST_INTEGER_COMMON_FACTOR_CT_HPP
#define BOOST_INTEGER_COMMON_FACTOR_CT_HPP

#include <boost/integer_fwd.hpp>  // self include
#include <boost/config.hpp>  // for BOOST_STATIC_CONSTANT, etc.

namespace boost
{
namespace integer
{

//  Implementation details  --------------------------------------------------//

namespace detail
{
    // Build GCD with Euclid's recursive algorithm
    template < static_gcd_type Value1, static_gcd_type Value2 >
    struct static_gcd_helper_t
    {
    private:
        BOOST_STATIC_CONSTANT( static_gcd_type, new_value1 = Value2 );
        BOOST_STATIC_CONSTANT( static_gcd_type, new_value2 = Value1 % Value2 );

        #ifndef __BORLANDC__
        #define BOOST_DETAIL_GCD_HELPER_VAL(Value) static_cast<static_gcd_type>(Value)
        #else
        typedef static_gcd_helper_t  self_type;
        #define BOOST_DETAIL_GCD_HELPER_VAL(Value)  (self_type:: Value )
        #endif

        typedef static_gcd_helper_t< BOOST_DETAIL_GCD_HELPER_VAL(new_value1),
         BOOST_DETAIL_GCD_HELPER_VAL(new_value2) >  next_step_type;

        #undef BOOST_DETAIL_GCD_HELPER_VAL

    public:
        BOOST_STATIC_CONSTANT( static_gcd_type, value = next_step_type::value );
    };

    // Non-recursive case
    template < static_gcd_type Value1 >
    struct static_gcd_helper_t< Value1, 0UL >
    {
        BOOST_STATIC_CONSTANT( static_gcd_type, value = Value1 );
    };

    // Build the LCM from the GCD
    template < static_gcd_type Value1, static_gcd_type Value2 >
    struct static_lcm_helper_t
    {
        typedef static_gcd_helper_t<Value1, Value2>  gcd_type;

        BOOST_STATIC_CONSTANT( static_gcd_type, value = Value1 / gcd_type::value
         * Value2 );
    };

    // Special case for zero-GCD values
    template < >
    struct static_lcm_helper_t< 0UL, 0UL >
    {
        BOOST_STATIC_CONSTANT( static_gcd_type, value = 0UL );
    };

}  // namespace detail


//  Compile-time greatest common divisor evaluator class declaration  --------//

template < static_gcd_type Value1, static_gcd_type Value2 > struct static_gcd
{
    BOOST_STATIC_CONSTANT( static_gcd_type, value = (detail::static_gcd_helper_t<Value1, Value2>::value) );
};  // boost::integer::static_gcd

#if !defined(BOOST_NO_INCLASS_MEMBER_INITIALIZATION)
template< static_gcd_type Value1, static_gcd_type Value2 > static_gcd_type const static_gcd< Value1, Value2 >::value;
#endif

//  Compile-time least common multiple evaluator class declaration  ----------//

template < static_gcd_type Value1, static_gcd_type Value2 > struct static_lcm
{
    BOOST_STATIC_CONSTANT( static_gcd_type, value = (detail::static_lcm_helper_t<Value1, Value2>::value) );
};  // boost::integer::static_lcm

#if !defined(BOOST_NO_INCLASS_MEMBER_INITIALIZATION)
template< static_gcd_type Value1, static_gcd_type Value2 > static_gcd_type const static_lcm< Value1, Value2 >::value;
#endif

}  // namespace integer
}  // namespace boost


#endif  // BOOST_INTEGER_COMMON_FACTOR_CT_HPP

/* common_factor_ct.hpp
iLroiEh0QTyGIB/lqMe5uA534BE8h0/xF1rU8zMSMRxTcTauwt14FgfxJ05qsAYGIh/lOANLcTm24L/Yj0/xByJnREf0whCUYjrmYDVux3Y8iRfxBr7CMTQ/Q2xwOhKQiVJU4ywsx3rcjkfwPN7AF/gVJ5wpVuiJAcjBRMzAf3AZbsF27MQ+HMA3+AWNZkZHnIpO6I1UZKAANViMdTPNxx68j1/RfFZ0xGlIwUhMxAycg4txEx7DaziMiNn2KXohHWWYgcWzjcd6bMZ9eAov4i18hF/QfI78QixGYCLqcTZW4WbcjafxJr7ArzhlrhxDLwxBMarnmoeLcR3uxMPYi9fxLU44y3oYgDxMxkKchzW4BlvwOF7GAXyBn/AvTprHP+iJAchECeqxBBdjLTbiYezG+/gax9B8vrxAL/THyPl0wMz5dMDq+XTALbhvPj3w3Hz64zsct4C/0RtpKMA0nLXAfFyHe/EU3sSXOIYWC+mNOAxDDsYsNBczsQSX4kbchYexC/vwAb7FUfyLFov4EHEYhGxMQAXOwNk4HxdjLTbiTjyK3XgFB/A5fsBfOOFsMpGAdIzGZMzAIqzABtyJHdiLd/ElfsHJi6MjuiEew1GMaZiB+ViGy3At7sYuvI9v0egcMUE/5GMSzsDF2IjteB6v4iC+wk9o8p/oiJbogjikYzQmYgYW4kKsxa3Yjt14G9/gD5yyJDqiM5KRjxoswEW4DvfhKbyKT3AEx53rnoo+GIx8VGIRrsRGbMF27MBuvIoP8BWOIGKpOCIaXZGAYcjGeExDA+ZgCVbjclyNm7ANj2IfPsIvOPE8sjAYJajHAizHjXgYr+AQGi+TjxiIMZiKeizESlyODbgND2IPPsZh/IrG56tviEZ3JGEoCjERM3AO1mErHsOLeA9f4VeceIHYoS8yMB6VmIXFuBhXYyO2YDsex168h0P4HScsl7vohgRkYDTGYjrmYCUuxfXYiu3YiZdwEF/hFzRZER3RCp3RA7EYhAyMxwz8B8uxBmuxEffiMTyP1/EFjiBipZqF05CIYSjCZMzGElyIjXgE+/ERvsOfaL3KPQyxGIARKEI1FmENbsOTeBc/46QL1TcMxzQswCW4D6/iGzRZLW7IQjVW4A7swWGcdJE1MRpn4lJsxz58hxMujo6IwQCMQhWW4Bo8iNfwA05dIy4YjAmYj6uwEffgWXyE39D0Er5HX6ShFNVYijVYh1twH57Ei/gIv+PUS/kJKRiOfFRiEVbjJtyHHXgTn+EIjrvMfR7xGI48lGM21mALduE9HMUJl/MbhqMcNZiPNdiK3fgcf6PjFfYFinAmVmMtbseDeAHv4Uv8gZOulMfojWRkoBATsBCrcA22YCfewmE0vcpzBlJQiAmoxTwsxw14CHtwAEfQdK2aizgMxRjUYDHWYBO24Tl8jN/Rdh0/IRcVWITLcTt24nUcxt+IWq8+YgjGYBZWYCO2YzfexY9ofrX9hkTkYDLOxmW4E0/hfXyPP3DKNXIKqRiNeizFdbgPz+ANHMLfOPVadRFpKEMlzsIyXIZNeAIH8Atab/B8gaEowwwsw3rcgcexDx/hKJpcR38MQD6mYTHW4kHsxvv4Ho2vFyv0xWAUYypm42LcgZ3Yh3fxDf5A5A1yA4nIQy1WYgt24T38ijY3yk1MxlxchJvxEF7GB/gJjW+Sn4hFGkZhCmbiAlyCDbgTj2M/vsAfaHkze9EPg5CFMlRiHlZiPTbhATyNV/A+fkDTje6fiEU6ijEF9ZiDxbgI12ErHsU+vIUv8BfablKfkYRhKMRUzMIKrMUm3IPH8Qo+wTFE3iJ/kIoinIElWI2bcD9240McQeNbxQyDkI8=
*/