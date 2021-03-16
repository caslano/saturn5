/*!
@file
Defines `boost::hana::id`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FUNCTIONAL_ID_HPP
#define BOOST_HANA_FUNCTIONAL_ID_HPP

#include <boost/hana/config.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @ingroup group-functional
    //! The identity function -- returns its argument unchanged.
    //!
    //! ### Example
    //! @include example/functional/id.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto id = [](auto&& x) -> decltype(auto) {
        return forwarded(x);
    };
#else
    struct id_t {
        template <typename T>
        constexpr T operator()(T&& t) const {
            return static_cast<T&&>(t);
        }
    };

    constexpr id_t id{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FUNCTIONAL_ID_HPP

/* id.hpp
DueimXxv5e3TblKpU7MzTCgmOyit6HqnZn2L7iAjPHZqNlh5FypoZtFjR/iq3w62E7HW5ILDOk90ZxjxGgL37Yb2UlhGhq8CTwP+0pg9fgWkaP4mLHfsvx6WZz9+G5ZnU98Ky6XpW8My9fpjWJ7z+BPwI+DbwDyk9w5wNPDPQB4n+UtYruj5a1gWGt4Fso7eC4t4rnHiuUaz+jpHe8jR+p39671qephzCRmiWntM62a/7j83ykEox6A7deCTGTg=
*/