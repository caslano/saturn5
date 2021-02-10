
#ifndef BOOST_MPL_SET_AUX_CLEAR_IMPL_HPP_INCLUDED
#define BOOST_MPL_SET_AUX_CLEAR_IMPL_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
// Copyright David Abrahams 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/clear_fwd.hpp>
#include <boost/mpl/set/aux_/set0.hpp>
#include <boost/mpl/set/aux_/tag.hpp>

namespace boost { namespace mpl {

template<>
struct clear_impl< aux::set_tag >
{
    template< typename Set > struct apply
    {
        typedef set0<> type;
    };
};

}}

#endif // BOOST_MPL_SET_AUX_CLEAR_IMPL_HPP_INCLUDED

/* clear_impl.hpp
i8IwEIXvA/0Pg+JpcXPwJqEgRVhZoVlbFxa8xHTcFtukJNFd//2mrVT3kmTCm++9Ybgn55V0FAOv9MmE60y3H2MLF4NIxQKSmqTFnH49bDdZDpw9BJwNPTCFKWZkr2TnrioIuKW2vgWB6z9VU8SwW4vtF3YMfEnf8XjxqA025Jz8JnewB/0agE8NvJBeqpLUuXP6V9zxvW9SV6T93Vf1xWgcQ2vaxYiNAbmWDQ2jDVmeMqC8yqqWx5qCjg1C5Mo0jdTFgFoyNntLs3wjlrOOIdJdznB+wUtwWDpSlnywG3vC856oz/pJtjrdsJsF5cmTRV8SdjvAUjo8EmmcuNL4CfBrrw2I1hpvlKljSFZiFcE+W+96vwjEKstwcI369UTwsd+Ek7NHF2cjij3W/QdQSwMECgAAAAgALWdKUn15i0o4AQAAAgIAAB4ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3Q4NTVVVAUAAbZIJGBNkV9rwjAUxd8v9DtcFB8lD+IYEgpFOiYIZmkd7DFLrmtZ25QkuvntF1upe8ofzvmdk1weyAetPKXA6+5k4/JN1x/rjE9BHMQKtg0phyX9BpB5KeEl2+2PMgfOHkLORi/MYY4FuQu5pa8NAXfUN9co8MOlbk0aKWL/
*/