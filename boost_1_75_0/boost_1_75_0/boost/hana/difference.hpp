/*!
@file
Defines `boost::hana::difference`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DIFFERENCE_HPP
#define BOOST_HANA_DIFFERENCE_HPP

#include <boost/hana/fwd/difference.hpp>

#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/erase_key.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename Ys>
    constexpr auto difference_t::operator()(Xs&& xs, Ys&& ys) const {
        using S = typename hana::tag_of<Xs>::type;
        using Difference = BOOST_HANA_DISPATCH_IF(difference_impl<S>,
            true
        );

        return Difference::apply(static_cast<Xs&&>(xs), static_cast<Ys&&>(ys));
    }
    //! @endcond

    template <typename S, bool condition>
    struct difference_impl<S, when<condition>> : default_ {
        template <typename ...Args>
        static constexpr auto apply(Args&& ...) = delete;
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DIFFERENCE_HPP

/* difference.hpp
/CrGV6z8iJqB/HZ/2R99GLxp3z7IvNJlPQlBi2CKY9Zi0bUIOnB1jpcTkUTnQvxCi2COY9RiKjP/ssXls1kp7/WkLisX+u0z4e3vkHMOSRxthRd+ljKKFlQECiRafWLTFi9L8vHF80mFf7PUkud+p1/Cm5KnInF7FfeLIzv0yg3tw/uNi9sV7YmAbmPLaIktQlhZcuvNzU/F8pjc5VjDQr5eTR9CWCgfc5MV2QUfPW0eZZOqU0iXEu/ILXb0+lsjwiVQAU4qO4Ng/kSR/Zne2kLaJq5J6FRfpaocW0Rn7fNz9HXEE0dqDbs6vmS7las0v7nZx9rOgK7OoEqUwReIu1f3+IP450+7KYm6b0w4+O5coRUIUz11zXyKOXnQaV2blyhM+dgL/cY07sav0OfZb9OPeht3lC9lb2qKcrfuRNNSoV38iXASp+LGMAar5X0FT3I0LpRxdP+dX1HIohm+fZH3BnADSCydHj7128k+pGWT907wfbfj54KYLu3z/VQOFz6cB3M5rt43nXEBS9rJFcn2CPuEI+azjnnR8LqLatcYZaqjqHWlRHmzXotZ/aC9+9z0PxIw/baxwNgze5t1o6tb94wLOPF8ZMlV6SKF9OPTzEgccM3eUhv4sIfKv6rnlXZ3VQHa5Flv/eUs+i/Zm4GhkQ29hOmihI9vSe2+5zBOvlRgnHwmYZxEKctmP+S8dNfyoe+/35BgRICp
*/