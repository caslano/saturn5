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
QPOq6sOhq+C6OwKHpEfLJUuosXph6KGV1JTtrlTbHUOEtQ9UtI3EdAgL2uUKgXehlTlvrL0FYsjSo2wh/0rLnmrPQUmsCkZ+AmEygg3TQrtwFS7P4tUSrvzFwp8t1xCfgj9b9/HOw9kH5IbArA3w+7rhGqtoQGzrSvB8J/l3nXTHW57BdLWI4vkynS6i0zAK4C2MDo/hz1YirQ9/GsGoEhvqOxx5b4+8A1ygbyln+iHV3FCH8Y1k0hgvOYOZfxE4L4Ne74OueYadBwZT3hhRiIxhrxf8VuEHdIcIUbRo2zDJehbPkzBxfhAyq9qcwzvK21GwfO/YFJnC9ZfljGkH3pRIjgo58qIU5GHJGnhDifZ+s6k+BMl0Ec6XYTxz5gyxZ70NkYSBbKtqn6ghJKMOU6/lDUi2pQeD6yKkYNfFHO6wh0QeJ1OSjie7kyGjMDuMcYjnwQUUqtkys9cPxjDa2TNUblkl8s7XlMw4KsNDIs9am9lSO4mQKlimvEF2OlcllxYIouOmFdUwdjBLEuLSR9kuo8Ql346zEucEBxSthCyqlsuM28Do4/T11ohFNyklr+qhzlvedGVSdXWjMmTrUMFAlcciLCBxzSXVq9u6Vo1x4dPPB8fpZXoa+R+pLen0LJie0zA7r+6kfhRZ
*/