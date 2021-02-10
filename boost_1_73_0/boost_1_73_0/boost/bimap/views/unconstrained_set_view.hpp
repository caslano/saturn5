// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file views/unconstrained_set_view.hpp
/// \brief Unconstrained view of a bimap.

#ifndef BOOST_BIMAP_VIEWS_UNCONSTRAINED_SET_VIEW_HPP
#define BOOST_BIMAP_VIEWS_UNCONSTRAINED_SET_VIEW_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

namespace boost {
namespace bimaps {
namespace views {

/// \brief Unconstrained view of a bimap.

template< class CoreIndex >
class unconstrained_set_view
{
    public:
    template< class T >
    unconstrained_set_view(const T &) {}

    typedef void iterator;
    typedef void const_iterator;
};

} // namespace views
} // namespace bimaps
} // namespace boost

#endif // BOOST_BIMAP_VIEWS_UNCONSTRAINED_SET_VIEW_HPP

/* unconstrained_set_view.hpp
SGjdvZ7sJ4GuioJbuWU3Ja1TpvewoqqAXUw2ilKMvrVJF7eOSrIWZE7qfCWLWK0NeeCTqEeEJEVkvTUb4oleSbjkVfsHWXGhLxdfwsX1+XDu13drDhORdIAFvdM0dmdUTzwSgirLeLBZFamsF+OyWrEAlKR+Pxb+z+HF59l8GMD7ie8x1hjzpMno1Yd0MPf91d+BENmah1qUETdV+X24+sETM+pSDjwMZ1/hzSeOtG1Y53LtZw9Ve+0NICk1VWJCQk4vUiR1TacBVtG7Z2Xgl/iGBYj9+AJ+cDrp9aCuse5j6U2iTBl8/sipsHvi6jpTVNlewHgEPlWobVo+pVqP37HQ/gtQSwMECgAAAAgALWdKUnI3PZm3BQAATA8AACwACQBjdXJsLW1hc3Rlci9kb2NzL2V4YW1wbGVzL3NmdHB1cGxvYWRyZXN1bWUuY1VUBQABtkgkYK1Xf0/bSBD9P59iLlVPDnIJcKfTldCqgTgQkdpRYg4hIVkbe433zvZGuxsK1/a738zaTgjkCkg1InbW+9782Dezm+7Oz7tasAPPXpH9j/DCu0VMlPybx2b77Cj6BtUfoq7x/pyRLqwh36IOPA/5Bo6FRLWVI3qOoucMXZNv9NEl5HVEjziCMEKeyMW9EjeZAeekA/vv
*/