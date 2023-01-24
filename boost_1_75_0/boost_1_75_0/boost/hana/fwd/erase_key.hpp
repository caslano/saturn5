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
RurqO+R7clLLipir2jOkr48w9JA/9Q7hdYt4t0WKpc9yvD29tP8pmt6Xi9JQULyHOGsHzvZhvmozigbxKlY0hxz3BNHP1LkTUUQRf+2wohwRgQ04FbUabOBCII0B0Ka0wXW194hT6OpTtLYPazivI1GzoQ9Rkzy/rS8uhExgWlrTy9QUUm6byL6CVkQvO/HzZBQChTJ0dDa7E3Qvoo4J9PJYKH9aw8L1i647lhU/3skSp1jSjgW1w6/Xst96dBJ35Z6EyBC6STlx3ITG22702FH+lIS9KNzZc4xuux3m31oOvJFEt608Zwu+8cm3ISyUYJ2481IJuyF2Jk2e3TlN7qpMk393jB6xfSFnfR8/9indBOlXtfQquw9yz3l5dsgNd5720y05OFugOyTf9X1BjUJaJt8WTpus2cxTScyH3UWeSmxVGLJl37hN/Y6JCO/jt7LY4Ps5Aa4K8XYWERJSUKooKFHU7gZm6WHpl6Ac4yjMPeXLplLEXoooU1L7TvzUh6eVaYrpf9pdXfJc5nQfFYdpg2EktXd9SlzJt6nQJ01ujtgjT5PnVUkedLWD1M/U/gpSwXJpM5bnKRgvrjfMhxFrFktqT7J7fuaZ0XWh8/+d5yF2Szzfeep4rx/EAQfySz+bPYnNgj0KcEN9R9WFPvLcwq+8CWTy23qSqGKQNfeRL6PzYgv2SMBY7T9XdvbUFx6SF2aD6pWPSAov
*/