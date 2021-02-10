
#ifndef BOOST_MPL_AUX_RANGE_C_EMPTY_HPP_INCLUDED
#define BOOST_MPL_AUX_RANGE_C_EMPTY_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/empty_fwd.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/aux_/range_c/tag.hpp>

namespace boost { namespace mpl {

template<>
struct empty_impl< aux::half_open_range_tag >
{
    template< typename Range > struct apply
        : equal_to<
              typename Range::start
            , typename Range::finish
            >
    {
    };
};

}}

#endif // BOOST_MPL_AUX_RANGE_C_EMPTY_HPP_INCLUDED

/* empty.hpp
aKelN45/I8BnEdY1FbExWSaFJ7mO2HspsaOlXb4bsakRrS3pBbnwviGW6dp3f9ZMM6+d8kLxUpsm9m54B/8kc8Qu7juqxxSGSRL7G6p2jr70jsuI/T3tGxbnylIVqFDVjyh4l4+2SoV1sfWI89N75fTyHh34YyNG3dfxrYvYWxrlX2ajl3h4JhFLfJPxjfAZfzA837zuvwFQSwMECgAAAAgALWdKUgl8Xl/VAgAA5gYAAB4ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3Q2NjhVVAUAAbZIJGDNVV1P2zAUfbeU/3DVCrFVFCcM0BpCpQnQQBMDjWgv0ya5yQ2xSOzIdoHs1+86pnTaxtgDD4uquDc+9/jcryRzaF0hLM5ZJlWlabnB/k6b0s7ZaZ5fDje4vLjKw7/zs/OTYGZ8jcx4cGZjNoYrNLdoplaWyDKDXdMToBROBEaebCewE8dw8SFix8JhCvkStyCewUd9SztJDMluujtLCfP+PI9YIEzBa53aweCVuEGwd7ZotMWIHWmlsHBSqxTWjxwqN837Dr3vveO1a5uIRazGptEkOogatBU1Fjf/pcAHZRl/SCVl+KiR3jFkuBgMAoSD56x2riP4yhyD07oBaeGuFo4MWFoEqaxDUYKuYLNY
*/