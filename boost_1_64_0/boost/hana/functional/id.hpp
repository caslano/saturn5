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
FXAr8bLvwQHpTzfb3QqRxCZ2GlT7Xb/6U6wkfjDzRobsHq4Tb9dxe5Rzk3FVc6DZdslKeCbA9OSdwRsvRY003TxaU51jHGGu3CC3Ucjf9f4+UxQ4vKgr1SJ5VPWwRbZqzeeGRrhUUKSo0Ng/ioUb2HSvy1recqWBPIBkZU4DQcRDG9VOwnZSlU7ruAZE5BiMlvoJK8wXMVbEHy7ZW3MMpY2uk1nEtd6aZt1mnQCyr4mEAlPouWGHHyAv4T9L6NvCIUHfMieAt7FCawmoTX6xPUronSrNQ9cHmCjHOriui1HnvTYqzl/EnR9YsJkXNDVwF7sTxsMZBkuxOQCVNdBP5vw77LVL3onS1q02/oLYOUHgL2gLZik7LpcN2gjIuWU9e0Eb22piwduGwnxfLySc9osOmKRTy9K7FvbbcUWqLx39F4xaWnDy1ZdUMFeI20tMLvsbYqOgTieOd+kuAsSZup+dZErRRsJ4OpkG5OUNP1ujUu/jrS83+ckFPVSH6UBtuOOqbSsHsiZAhc+XP2ucBfDwMHAKXLU5JhWMV2J2OOFuBDB90512LUsQSg==
*/