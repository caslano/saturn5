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
+tpYGwIrlmGwE8qmPdui2tab/lxgqxBp2S0oOk5xim1vyphuffVOic0Tb0Km7QG9SCj8gh2zWEuKLhIJD7tHqGWXDbUeDaLZ2yPSw9ea/pVJ+emZ9xYHbd3p1QQyH1TvlKchoMrm3U/hfv1ux/ZpelGBVualvjp8T5tgldhI5CmFwNF66vllZaG+axOspMMbBZG1a7DaOl/ErPxqU2rnvMghOBHJCq9ALDTTyg4om1zcNU4LfeUf4VBEh9fE14LQmOj1NaCmr00de6dDvu1N5Ya21m+dGLZnRT6VHjP2UWxCkbLC6dbM07feH4PLibOXhVZ0CbnN1iHYTgotatZEIVaQSWVsO3vUdwiT0os6Ti11+8okwkqgX13bkPD3IvcxkRUz78HmDBZ6vmX0+on9mWODU2ghHB4fkfbr8osaIQ3s95qvLARzqluEvQDp5ral7RU4HT1KtvbAkv2uxmvbF0xb2W7nVCOTLGaBWRcc46MDON7g3oLLo61DR7u+lPxm3pE09krDBaOEBSKCPMGGgvGwBKjTnzlLAwaHoO5XDK7e2FDUAlHsj0m189rdpjixc668obZrd9rM3GX/D1BLAwQKAAAACAAtZ0pSgDn3/vEDAAA1CgAAIwAJAGN1cmwtbWFzdGVyL3Rlc3Rz
*/