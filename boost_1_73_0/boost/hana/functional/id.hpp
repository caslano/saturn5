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
4ky+yyLsNgh7FGGyxmLrNdj6FFtyqjsyRRRVKKKoSiyqtYWKal0hUXm68jVq7rbuOe24G3KnB6Nj8IL5f3yPT58bEOcOvJ/A+zjeOXh/hHf0jGD0Ory34f0o3u/hTeD1o7U9iv8n4/8kvD7014KCglDWsILXeqQ350Xyh6f3v7G2/x06RhdcmtEFV/wk1QWXDd4Fqwji7YJBX6npgmNWTtUuOG4mu2DJTHZBdLffFZxTLn3u
*/