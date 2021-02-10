
#ifndef BOOST_MPL_SET_AUX_KEY_TYPE_IMPL_HPP_INCLUDED
#define BOOST_MPL_SET_AUX_KEY_TYPE_IMPL_HPP_INCLUDED

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

#include <boost/mpl/key_type_fwd.hpp>
#include <boost/mpl/set/aux_/tag.hpp>

namespace boost { namespace mpl {

template<>
struct key_type_impl< aux::set_tag >
{
    template< typename Set, typename T > struct apply
    {
        typedef T type;
    };
};

}}

#endif // BOOST_MPL_SET_AUX_KEY_TYPE_IMPL_HPP_INCLUDED

/* key_type_impl.hpp
BzliAzfuaPwNE19jLUG01nijTDUtMhgfw8gH69XDPA+VVotFqMNoswkfMFrhOl9hqCPMA1p4dgAaMWAvb8/ZYO4VTfALBb++wP9QSwMECgAAAAgALWdKUnTA6K+IAQAAewIAAB4ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3Q4NjVVVAUAAbZIJGBdUlFP4zAMfrfU/2CBeEJT4AYDVVFFNYE23XQrW5mAt5C6rEebVEkK6v36S9uxTbzEduzv8+c43JF1UliKgBcq1958UPulTWYjSJbJGNbxetEfGD+lM0wW8fwPrB6mlzfjq85eTS4nnb2+8DFnBzRnAyGcwimuyXySGdkiI+CG6rL1Bba/lFUWwTH3fbJ4GZqdfwezzb/X53ksf23+ympzgefL37jQ74VC20hJ1uZN6RseEfJMOBHBg9FViBXdWV3R15YMBZDqEHPxQXdK724CeNNZ29nRKADEVjfGoi2U9OnSJzgb6Djbae+HmpYFKbcbSvbBfqoIal2P95oiQK5ERcOjYl0Kr100busxhRSu0MpXsKEEudRVJVQ2kISMnc2W63SehGcdOlmuUnY7ucZRg42nDy1JQ8732sO8u5PTC92QKfIWuxlQ5I4M+sbYrR63wuIbkcITu9XuBPhn
*/