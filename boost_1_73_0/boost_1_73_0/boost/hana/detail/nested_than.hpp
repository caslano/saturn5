/*!
@file
Defines `boost::hana::detail::nested_than`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_NESTED_THAN_HPP
#define BOOST_HANA_DETAIL_NESTED_THAN_HPP

#include <boost/hana/detail/nested_than_fwd.hpp>

#include <boost/hana/config.hpp>
#include <boost/hana/functional/flip.hpp>
#include <boost/hana/functional/partial.hpp>


BOOST_HANA_NAMESPACE_BEGIN namespace detail {
    //! @cond
    template <typename Algorithm>
    template <typename X>
    constexpr decltype(auto) nested_than_t<Algorithm>::operator()(X&& x) const
    { return hana::partial(hana::flip(Algorithm{}), static_cast<X&&>(x)); }
    //! @endcond
} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_NESTED_THAN_HPP

/* nested_than.hpp
mwkqqu/HZXfgPXeV17B29Uf3zketJs0uCtajVag1QT0pH3s2v1V21FpGuQq58uyqhdnaSV5j2dxkpnSUhL41xpX2G+VuhMKH3OZFaHNpGSsC1513c/BrVkrDmrllepBTIO3NVP3mVvXxpwyYmfGnzLjVxm9WyjPk5o4/ZR4QBb6WWFEM7QxzYZHGapi8aokoczMPx64oV9dzuYO+QSbAArVYnApq7WfalUWMVmTgHNmOPKVRoXeUGCXC6yTxdvBieBQsVzBIKWE1xKXRbblktw1DEzf9FhnqVrCkw0WO/squu9fD9pnTbw6aV+V7TyoKj4eC5fJeDyWEpmsazkVr8KE/Au3uN3bbQtrrr8JPKiwmRypCoLKSU6HmhJKKK9aXVJWCGv+L7TqDYdM5L8mpSVDwZG0fZLr6L+LpsAMitMzgbZCcyPHW6XZGJnxvvGDA8alDViMtp86H32ACLWpLpJIDDwP7qJHp1Q+uL20Jqg0gZEysik1VSEbGlh9B0fYDZ+l5K2e5Hn/07h9l365o0K3WGNflRbxzH1qccgjFWnlEJCk9SSG0jVnjBCaH/DxRSwyLSUW4TORHyYFSHMo4PsRHU9pwEtJseOn0O6DtnvWvX79tf+j2RldN0JJlyxjtB6MT3eK5NR1H49n5
*/