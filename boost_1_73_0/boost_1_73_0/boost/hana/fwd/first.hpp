/*!
@file
Forward declares `boost::hana::first`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_FIRST_HPP
#define BOOST_HANA_FWD_FIRST_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Returns the first element of a pair.
    //! @ingroup group-Product
    //!
    //! Note that if the `Product` actually stores the elements it contains,
    //! `hana::first` is required to return a lvalue reference, a lvalue
    //! reference to const or a rvalue reference to the first element, where
    //! the type of reference must match that of the pair passed to `first`.
    //! If the `Product` does not store the elements it contains (i.e. it
    //! generates them on demand), this requirement is dropped.
    //!
    //!
    //! Example
    //! -------
    //! @include example/first.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto first = [](auto&& product) -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename P, typename = void>
    struct first_impl : first_impl<P, when<true>> { };

    struct first_t {
        template <typename Pair>
        constexpr decltype(auto) operator()(Pair&& pair) const;
    };

    constexpr first_t first{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_FIRST_HPP

/* first.hpp
DGfySofIhG3Uzg5YmxDJr0LiSPLSBAd5L7WRSxaSESrGJnzL87L1hqvPK1eGvHxe/kDF1ctKFlzESj7ANRHRoQ2UIWVmWLlK1ymyITzYtEujg8peq2EpW+XOI5AxiYtxmsJT2YRia0+W0tBwxTqmEJwNSWqt3Oq/RPYxsdSttyzEPnBS5djmDC0fJt8ldyt/lth62hn87ta81lvBWS4G/WGBcdHHUgYdMtyM5xfT6zluhrPZcDJfYHqO4WSRyH6PJ6e89ZrFPGjTeAos7qFXjdFUbTU/ruW9PW1L01aEfto8ESi2zUD1ezxRpwvlujh7vip6PdqwHZZ9tyGCV9nykR11sGBeOmLtTM3xO3OQ5T1FfvgvDZLqy8SbV1JK+QtQSwMECgAAAAgALWdKUj8UBdjOBwAATi0AABoACQBjdXJsLW1hc3Rlci9saWIvd2Fybmxlc3MuY1VUBQABtkgkYO1abU/bSBD+zq8YUQklKEeg7fWgR9HlQlyiUlLlpVVPlSwn3uC9Gm/kXQPluP9+s7t2bCd+LWlFT01FHdbz8uwzM7s7xu3dzX22YBdKP6b6MfGDV6Xxzmd/k5nIljbNe9D/UOsTXsuctCFWuTebUK5yDw2lYoZejuV30yxz9Elik/+1peYnU37FEVST
*/