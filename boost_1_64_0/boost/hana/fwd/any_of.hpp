/*!
@file
Forward declares `boost::hana::any_of`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_ANY_OF_HPP
#define BOOST_HANA_FWD_ANY_OF_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Returns whether any key of the structure satisfies the `predicate`.
    //! @ingroup group-Searchable
    //!
    //! If the structure is not finite, `predicate` has to be satisfied
    //! after looking at a finite number of keys for this method to finish.
    //!
    //!
    //! @param xs
    //! The structure to search.
    //!
    //! @param predicate
    //! A function called as `predicate(k)`, where `k` is a key of the
    //! structure, and returning a `Logical`.
    //!
    //!
    //! Example
    //! -------
    //! @include example/any_of.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto any_of = [](auto&& xs, auto&& predicate) {
        return tag-dispatched;
    };
#else
    template <typename S, typename = void>
    struct any_of_impl : any_of_impl<S, when<true>> { };

    struct any_of_t {
        template <typename Xs, typename Pred>
        constexpr auto operator()(Xs&& xs, Pred&& pred) const;
    };

    constexpr any_of_t any_of{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_ANY_OF_HPP

/* any_of.hpp
Vr3DUP1ot9zW7ZyQJ/T+G/60enAeCdep1WdvVyrIrvs5aA30fwxrnfkVYDXQd8uJrTCz2SN8vFSGaxvTW+cPxK9uCNMqc4f20gOdMieDJUvrgRz76X4/o8fOMgNc+Byovvki/vbauwpMWk+oeGQktI7Z9JY4t6F4qJGoUUIBW8udj+VebQ3oEJ7lopXuJ+l+gLAMik/R82jtmSnJodlEvBTkYXqiyeKQDooUzkBCknE6rM0+ehjOzjmQdANgR/EOTzCRMPp6s526LYUyrJ7K8fTRdvEYfNW7RAzn6HUtd6LEAK7ZE9yLnUklwzQ5rTXNTjSlVOtDuN7NsFZ7dP5nNIi6Ytq4OHMpis0fcDLR7i5eQMo7t77wSjxZAD8BlQV2eRG5vBiNZpNWM7C2SL4o2erSKsLNeJ7LEhde3EWN0Nru3iTSaCGIeuD/ruzae6QP3Cse4o6Al6KHIPWBbseaVhoqxgAiAjxqxCGBXaosioocb/Fs/kG4L2ZG3iPzCFiX+15eBCL7OmnEsRMXCMBv55DOo3ZB2hCLchjCT5aF2ZNJBMFCeWSFjUizdg==
*/