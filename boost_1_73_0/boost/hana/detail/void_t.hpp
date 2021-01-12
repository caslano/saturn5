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
nFWg+BOC/+GctGC7jyAW97a54L+fg/MR2EZ+Sxr+6SH32Oo8hNuNUcNVmGVnk6YEjrO5iwnZShqFsG0SJto4f5oWFjtF1pcSyZkyOWJNov62lt09Mx02JY+nOR6DZHdyGK/eHhbDxSh7I7iR+OvvPUJrs51FSMHZgxgivJbYpFlm5XKc+LmzXQC+mWMYuystQK+5Cfbz5Cks/ZEsowLOd7f+wdoadnwXIPZ3csyl+Kk2do+N
*/