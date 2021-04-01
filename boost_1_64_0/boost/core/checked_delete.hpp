#ifndef BOOST_CORE_CHECKED_DELETE_HPP
#define BOOST_CORE_CHECKED_DELETE_HPP

// MS compatible compilers support #pragma once

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <boost/config.hpp>

//
//  boost/checked_delete.hpp
//
//  Copyright (c) 2002, 2003 Peter Dimov
//  Copyright (c) 2003 Daniel Frey
//  Copyright (c) 2003 Howard Hinnant
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//  See http://www.boost.org/libs/core/doc/html/core/checked_delete.html for documentation.
//

namespace boost
{

// verify that types are complete for increased safety

template<class T> inline void checked_delete(T * x) BOOST_NOEXCEPT
{
    // intentionally complex - simplification causes regressions
    typedef char type_must_be_complete[ sizeof(T)? 1: -1 ];
    (void) sizeof(type_must_be_complete);
    delete x;
}

template<class T> inline void checked_array_delete(T * x) BOOST_NOEXCEPT
{
    typedef char type_must_be_complete[ sizeof(T)? 1: -1 ];
    (void) sizeof(type_must_be_complete);
    delete [] x;
}

template<class T> struct checked_deleter
{
    typedef void result_type;
    typedef T * argument_type;

    void operator()(T * x) const BOOST_NOEXCEPT
    {
        // boost:: disables ADL
        boost::checked_delete(x);
    }
};

template<class T> struct checked_array_deleter
{
    typedef void result_type;
    typedef T * argument_type;

    void operator()(T * x) const BOOST_NOEXCEPT
    {
        boost::checked_array_delete(x);
    }
};

} // namespace boost

#endif  // #ifndef BOOST_CORE_CHECKED_DELETE_HPP

/* checked_delete.hpp
gXBINvzxi1x7dz9H36ikTLvJ/9MakmoZevZGjbBswQ6vB24sNrW23ph8n1e5WkBbelvEZ4E6zz1oxsOESJOao8fHPFIDvcvNgcAfKNWffQE0V+p0PbwuW6GpVopkpnU0srjtr6BD9OL5CjaQ75e2esMzMJ2t9byYHmymWMWBTmK76auukmaF0mAfYp3Gw20lKjydAWS9yImdYoBSFbc5ynfW7u0ZBXjG7eo8c5WbA2h9NBK49d/0cWka9aa9UfMQMpcLaUIy2rDu5Qr+9v0XSHkHQ3nzhKdoldFm3qvKobaWxuuuLB/GNPKOzauO33UNLQEIJRDcyMqrEEMUmJvcCf8zWQqq/x2ptlHJxM+XlMTaN7Qqd08BuzraYFxUGDh7qTZR6D953xVJLOzR2dQ4a8St7RJW3TSTKkd2xwpng+1c3dFMW1iJ6ZS4x47Fjzn9UIDPOn0OMXhsuI60tCBRFwr5zZl6GY/k7R0e336FhrDDwbY5VVFj8typN2CwCt4W37srgheXRpS4ZKgAUOww5hvGIKMuHPoxubyDrwSgQkW60ncqlq9lTqpSfw==
*/