/*!
@file
Defines an equivalent to the proposed `std::void_t`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_VOID_T_HPP
#define BOOST_HANA_DETAIL_VOID_T_HPP

#include <boost/hana/config.hpp>


BOOST_HANA_NAMESPACE_BEGIN namespace detail {
    template <typename ...>
    using void_t = void;
} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_VOID_T_HPP

/* void_t.hpp
/QWHwBWkdunHZJ6v8byuRlvkbJ/yu07xmm//7G3PsFzKy6M52490ZK385ITf7KbW+gvnN8gbQDUq7Z/ReXXK/+ovR6X2DB+1W7Oy6mdRs0reVdvsiYn5YStQ7c82tDkZ8i5aI1AnAbwIeFGGvAsyL0NeV53PI0fAhRnyDsgi4M9RCxcDfw1sNUeQ4hkipLc4Ib0lbGdLQlvnaKnixXFGtUoKBluifcnIcFueDrFtWkBokgO29q1DIVtlaTyXLZk=
*/