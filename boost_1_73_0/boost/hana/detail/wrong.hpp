/*!
@file
Defines `boost::hana::detail::wrong`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_WRONG_HPP
#define BOOST_HANA_DETAIL_WRONG_HPP

#include <boost/hana/config.hpp>

#include <type_traits>


BOOST_HANA_NAMESPACE_BEGIN namespace detail {
    //! @ingroup group-detail
    //! Equivalent to a type-dependent `std::false_type`.
    //!
    //! This is useful for making a static assertion that would otherwise
    //! always fire up dependent on some template parameters.
    //!
    //!
    //! Example
    //! -------
    //! @include example/detail/wrong.cpp
    template <typename ...>
    struct wrong : std::false_type { };
} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_WRONG_HPP

/* wrong.hpp
zZY9BS1ZreUXZmoROdWpEgwdlsA/vcVLINJk7N6jxt4ssX9mx+xdjG2pJ925hu3uN72skttiOfmrsuJ8rPKH/thvOPZOt+BMWoqWvCWzyEyrPjNgCKxUpRfSC20fZCu9KoWy7EK5eppjNG2O8JDJec+i/AGo1Jso3M3OB3VegdaG6fDwKooNi0Fh7YVn6PFjAW9iCsTWV3GfnlpkGeansEQJ2V9F5HKK22fD2al1TkJpfcDn
*/