//  Boost common_factor_ct.hpp header file  ----------------------------------//

//  (C) Copyright Daryle Walker and Stephen Cleary 2001-2002.
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  https://www.boost.org/LICENSE_1_0.txt)

//  See https://www.boost.org for updates, documentation, and revision history. 

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

        #ifndef BOOST_BORLANDC
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
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
*/