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
CB6uCdgHwDsfTJB3Nh9eJPqviex8uBtf+43M416EHd/zru/N1vuMfgCAOZjh1SpsFsa3xeg+fFuKP5kxeI/o+zL80WOHFrIJEIoMwyde6OUE0aUc9rV+cYZbSQasShOVLai73Rux+oOZ5dbOfnrKGb5emxnrrECZ3GH2vJkAyJBbimDvBlRe9kDcufy02SZHQt0gDLzljCfrXC8c9qv81AK5UHvj8y0YTEvRPND+ME3ZcbFA
*/