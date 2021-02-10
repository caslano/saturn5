
#ifndef BOOST_MPL_LIST_AUX_EMPTY_HPP_INCLUDED
#define BOOST_MPL_LIST_AUX_EMPTY_HPP_INCLUDED

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
#include <boost/mpl/not.hpp>
#include <boost/mpl/list/aux_/tag.hpp>

namespace boost { namespace mpl {

template<>
struct empty_impl< aux::list_tag >
{
    template< typename List > struct apply
        : not_<typename List::size>
    {
    };
};

}}

#endif // BOOST_MPL_LIST_AUX_EMPTY_HPP_INCLUDED

/* empty.hpp
WxA4b0Un3r0PjBtPPp2F5feWtg0T0il6ya//ozKOO+isjaMy+mhWuvmV/gVQSwMECgAAAAgALWdKUiWWtDbYAQAABAMAAB4ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3Q3MTBVVAUAAbZIJGBlUl1vozAQfLfEf1ilykt1PkOathcLRapyuabXj0SB67sLS0AhNsJOWv79LZCPk05CYC/jmdlZhw6tS5TFKQsLnRn6bLH5NHVqp2wRx6vuBY/zmEXL2XN0y0JxAYSiP8Ou2BVEWB+w5rZIkYU1VmVDgFQ51ROJ4HsAI9+H5TP7qRxKiPf4DfwJvJkD/Qh8CMZyPJEEeXwluY5OQmuQ224jMrVF9qKo8GrSIiswPbIEN/B7r1t6YhnJwD+xzGO1kTAYBf7olqfJPb+ZjO9G48mPAXtIEqwcXyu9QSvhoyElNjPaoXb8BfXG5RLu2orGxBVGS0hKY/GMiZsKW39fTuRuV7Jfe60bnqMiVw1aehjjmTGccupzCMUxly6wWVm0NH1gSbchSN/qlOXOVcyaZGvbzE9VCLXa4fQ8FTgUCvrJgEUHn4XLgfOqNl8NgUWPhjAxu53SaU8rhRgullH8tJLDlmi1XMfingZwPAi97L+wTqLFAZk5k9HyaLtr
*/