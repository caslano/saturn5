/*!
@file
Forward declares `boost::hana::symmetric_difference`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_SYMMETRIC_DIFFERENCE_HPP
#define BOOST_HANA_FWD_SYMMETRIC_DIFFERENCE_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    // Note: This function is documented per datatype/concept only.
    //! @cond
    template <typename S, typename = void>
    struct symmetric_difference_impl : symmetric_difference_impl<S, when<true>> { };
    //! @endcond

    struct symmetric_difference_t {
        template <typename Xs, typename Ys>
        constexpr auto operator()(Xs&&, Ys&&) const;
    };

    constexpr symmetric_difference_t symmetric_difference{};
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_SYMMETRIC_DIFFERENCE_HPP

/* symmetric_difference.hpp
m2fmLLqFKb/KoWdRj58TlLPrvWXg5BdJtqCWWYSHBTnliyxe+peMT0Pi+ibLowKeniduwys/L+DTmo3bmwIKRVVFgwtLTqWvCpYv82xZKOTF0xWfen97fvbhf974AUv/JzZ134dn/gysYD+D/LvPAmigZywIXIsshe6G/3O6oGn46CtvobxdMkP9dYYAqkzCaz9VLvIV+3pA8+dJyc56W3f02HPdIH7m2rH2zNT8+Jmn+cEzPXLCCFYtCkxnQO9Pn/T2//5mwfK+7tPVZ3aD0PHP8yTMsyKLy+dhNj8IXFa+8kvW1yHxyjPVfKZbF5r7Rwv/t55DY2kIcv7fId0+ffIO1fp6/YkBB356SAcvlss0CdFgtujr5W2FQ+XFP1c5U84gS/mcV1E+5FnJQl77EFb9UjIIcPQ/b89fX/zPW1ZeZRGteewez4tVmVH3YbPLc7YokjK5TsrbfdjiQvZlni4KEZDzS025KsvlH//whyK8YnO/eN7inD9kcZyE7A8k03/QVdXgV3O0NVv6S5bfwMhA9fDrK2hoUkNQU6lQSLjK66uyvgr41eWqLFmu0jqcApikBVI3SZTdhGWezuJyEfxj5gM5URbOSujFz/PsmhWquBZ0KJPFpTaLsgVIMQ9YVNwWMXQsLARLb7PF9TxVG29TlI780kfPeYxW2TUUJxoEhhI8Z8CGNiuusptl6ofsKksj8YXI5HKR5Wye
*/