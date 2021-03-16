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
Ck9dVV/Hzc/iKbxWCa/i6wBx0d5EZQR4r1/X977SJ9unRmx1QMB0FB2HmOpGDu6OQQnW9fVv7MPbNix8rGBnrCs60JPGi1iV4AjC62KbLFg1Pa7gOfsivf2dES3FgPU4qAmg9SjqIkkKOtWCTiRS1xKI9nX2xJI1WFgAQHUHkvH0JlH6jv7+dfEYKx3ow9OKSy2tLCUjpAMEikPrBKYT7pKAdM0lAYdrCRwKqiVyxmkJ96LEGpm9YUqidrWXJBw=
*/