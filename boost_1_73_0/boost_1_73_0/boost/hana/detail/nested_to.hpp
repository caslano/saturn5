/*!
@file
Defines `boost::hana::detail::nested_to`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_NESTED_TO_HPP
#define BOOST_HANA_DETAIL_NESTED_TO_HPP

#include <boost/hana/detail/nested_to_fwd.hpp>

#include <boost/hana/config.hpp>
#include <boost/hana/functional/partial.hpp>


BOOST_HANA_NAMESPACE_BEGIN namespace detail {
    //! @cond
    template <typename Algorithm>
    template <typename X>
    constexpr decltype(auto) nested_to_t<Algorithm>::operator()(X&& x) const
    { return hana::partial(Algorithm{}, static_cast<X&&>(x)); }
    //! @endcond
} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_NESTED_TO_HPP

/* nested_to.hpp
uUEajW2UCG2JTibuPWwx//BWobjXKqKec8/1AL1KEFU7KkzkPLnVJpMZIFtVE4csVYOjXqJxZJWNKlO0oZ6R2hx1wU1B1qIMUIjrmgCKJpzGA/9/ShOaYuiZZnngjXD1UXj5o1UgXPk3PloKrvzgzTvYb25ljHmxyl5/GLV39GgKHCDs7wwwXaOeQe3h5fgilDOulhnutRVgu/EoLP4t13/TXb7xqNe+u3IXstuLvoMEjRfxBQzAZ58mVFk0TU8N0q4KI7/yYYNSoyv2i7aeSlvFnbxkgL81LxPCpaMvbYmVgW7j3pxgEpX0zAPxLrznFEbvVEmkN61kWuMUymaJi1B06x49//FxzJs+G3Jw+qQ6U7Bs0iGvRG5lpHVmNiVB+gnNJ90kle09KgtGsz1ssFbz8o0zvGg6UKVMgeceGgoYWECOtP1FtTLNuJpig912uuc9suQbNiKOCW6+8YVEKGAtzA0H4Bv+SNLuqxmApUn6lBjhPwkIkF9Eqyoah6blbLOvDR4NA6DkKwsqDK/7fVLmaARftIe6Nt6Q7rawo2lIG7uTjyBwEdLqvIxubGxY0UUgyOxSafuhpQqyFP4yVUWYCu1VxEthdEC0BWHgcWJ0Jp8ztSTjwnepfqRXS7Yj3KBlvBmzju6w1kjX
*/