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
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
*/