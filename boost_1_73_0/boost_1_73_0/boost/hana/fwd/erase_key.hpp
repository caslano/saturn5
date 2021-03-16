/*!
@file
Forward declares `boost::hana::erase_key`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_ERASE_KEY_HPP
#define BOOST_HANA_FWD_ERASE_KEY_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    // Note: This function is documented per datatype/concept only.
    //! @cond
    template <typename T, typename = void>
    struct erase_key_impl : erase_key_impl<T, when<true>> { };
    //! @endcond

    struct erase_key_t {
        template <typename Set, typename ...Args>
        constexpr decltype(auto) operator()(Set&& set, Args&& ...args) const;
    };

    constexpr erase_key_t erase_key{};
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_ERASE_KEY_HPP

/* erase_key.hpp
SXjhEPSsVN9A1nxY4SR1MGviVDb2M/FopLdCWZPcO/3/Tg1ppHOh1YJrrALzHyUTryyU6Wjfb4NpG1Ra9jGOmJ1S4Hq25l5P5oH2nck8Cvcm4BmAu3R2eiuZHdC8ncwjn/CRyX0efE6aOHsfcDvgB8m8mOVDQOgzq4+S+YTVjwHxnXyim2m3SbK9jZJojXDrhDt8x2VQzx2Dem6wp0vNpFj0O5HD3ok57J3Yw96JO+ydelHvUILz6xYsXyvp6lQ=
*/