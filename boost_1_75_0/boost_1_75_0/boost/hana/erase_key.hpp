/*!
@file
Defines `boost::hana::erase_key`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_ERASE_KEY_HPP
#define BOOST_HANA_ERASE_KEY_HPP

#include <boost/hana/fwd/erase_key.hpp>

#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Set, typename ...Args>
    constexpr decltype(auto) erase_key_t::operator()(Set&& set, Args&& ...args) const {
        return erase_key_impl<typename hana::tag_of<Set>::type>::apply(
            static_cast<Set&&>(set),
            static_cast<Args&&>(args)...
        );
    }
    //! @endcond

    template <typename T, bool condition>
    struct erase_key_impl<T, when<condition>> : default_ {
        template <typename ...Args>
        static constexpr auto apply(Args&& ...) = delete;
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_ERASE_KEY_HPP

/* erase_key.hpp
BSybV5g9XifDfeUwWWCeQv3Brh+sCVYAq6BkUX+NuDTtjxIBaCH1Mvy7RVze9d7r7by5LOWLHnlg39PRThgtyvX0TJP5ar1R6fomIPwTfdPoRPhN+/3HpYnw9vXHQx2RHo+1x0NMkR4k6d9fdpZ5oE7ZRY1+N+qyDLpW0jj5zRGo49UcnCNoZQtV1Y3spDRaq/fK1Cggu6xOmgpwuYg3y3A3r5g3cPR2qmySaGpaUXaJ9cleiAwdDsJHhk3XpjnLGfcsVZwUu6xw+PbT2fM3/TaS9Tc6mnasUzCdnnT0ty8cPJMp9HKc0nz41r6yjdA5QbWjyP6RFu7Ge+6Aql6e4uO6ukcN/P6ERIWzhwBDpf8RF+6WMYUy/94bH8X5uHqyMSjr1EswGQtGv5Qwc6qacr6/Mg8Ut/+AknGFn4Cd6FFoWyi4m3NZBjqKfqONGXU/2cnltTEVwL3bm4cia+4cBjeh9gqAYZCpC7BIqAft3VW7iSj284Pqk4jSheEzyuZ88YkPORUKCTV77bfLOKJ+vrfEtduLelG+ZDQK1t+b/+iU3+QJoW8NoH/uyRt+UgrZB6P9g/Q9pQ7bvv9zufy/XGx/eC/04R9/XYClzX+ulQcYG/qiJlPIVt2PxSOvnOlFtI5YNbNVo6w7vLKX6v9wsagpOEPrf4hFBVpXDidWqtC1/DSJD2syFhIx/T0Y8VEvcSbWkTW0Xj4vpD7l
*/