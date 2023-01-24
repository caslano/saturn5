/*
 [auto_generated]
 boost/numeric/odeint/algebra/detail/extract_value_type.hpp

 [begin_description]
 Extract true value type from complex types (eg. std::complex)
 [end_description]

 Copyright 2013 Karsten Ahnert
 Copyright 2013 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_NUMERIC_ODEINT_ALGEBRA_DETAIL_EXTRACT_VALUE_TYPE_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_ALGEBRA_DETAIL_EXTRACT_VALUE_TYPE_HPP_INCLUDED

#include <boost/utility.hpp>
#include <boost/mpl/has_xxx.hpp>

BOOST_MPL_HAS_XXX_TRAIT_DEF(value_type)

namespace boost {
namespace numeric {
namespace odeint {
namespace detail {

template< typename S , typename Enabler = void >
struct extract_value_type {};

// as long as value_types are defined we go down the value_type chain
// e.g. returning S::value_type::value_type::value_type

template< typename S >
struct extract_value_type<S , typename boost::disable_if< has_value_type<S> >::type >
{
    // no value_type defined, return S
    typedef S type;
};

template< typename S >
struct extract_value_type< S , typename boost::enable_if< has_value_type<S> >::type >
{
    // go down the value_type
    typedef typename extract_value_type< typename S::value_type >::type type;
};

} } } }

#endif

/* extract_value_type.hpp
vXsVreuvH8fhfZ0WnVJUzmOcRuIzrG8A37i44wu3stWXVpLjK9VDji8TTfsuvcGNL6NjM5A1w8MPasDg8igNe/YJk3Czivtb0dk+0evcGeirR36gt52cmNNjvO3T0TFCJyec3865TlZSzkfpgm/M7OpVvBr9qsYQ5NgtVpf6FNA4uWExgSCGJtPdpNe453VGPHRLjpt4ru8MHrdLR7LQv9ouKAVTLUb9qwBaAAg1acsTIk+UZn/zhGgot9qdNQhr2GQRPWfx7je/zH3EK01Yr5fnrP75BPmLs6KwO7+bdS53yNa/wpFABUbbBtY6OWPXv0Lncmnw9WmRn6V7d+qnXkwv0W8xqXx2Dr8oqEw/7NP9Ni4usPZ2XM3XF9+gcwOhw9mYD4ht9TgqJKUwRbMf+cNEVaOSKOGb+t+HjNxAHeq0H8IS8ZgJ8TP6ekxPzf4ufk1GR7AXpucpqwu4NbsHVp58iTOSDzYerpH38TfVwgw4fazWpxSYN/YggfCZZp9BTXTXz4fgq2FHp1nOVe9DbUae6cWHK7jzN2+3IVtRM/Nj9aCvpPUuE+c7XIlWR72AnG8ICwnlGZgsf/Dli1gKmB/XwhEh+f85QLGc3uMvlb7ApfJasZhfm8QXM50zWbwFITHi8a0x8uT+rA1RQJ/8QgDquY5G8Vde3hcHkjavppw0xvJ8PiC20r8SMf9+nMazqZzkDsesCEterVZn
*/