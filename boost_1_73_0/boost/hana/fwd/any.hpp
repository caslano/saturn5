/*!
@file
Forward declares `boost::hana::any`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_ANY_HPP
#define BOOST_HANA_FWD_ANY_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Returns whether any key of the structure is true-valued.
    //! @ingroup group-Searchable
    //!
    //! The keys of the structure must be `Logical`s. If the structure is not
    //! finite, a true-valued key must appear at a finite "index" in order for
    //! this method to finish.
    //!
    //!
    //! Example
    //! -------
    //! @include example/any.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto any = [](auto&& xs) {
        return tag-dispatched;
    };
#else
    template <typename S, typename = void>
    struct any_impl : any_impl<S, when<true>> { };

    struct any_t {
        template <typename Xs>
        constexpr auto operator()(Xs&& xs) const;
    };

    constexpr any_t any{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_ANY_HPP

/* any.hpp
BNHUDP00lKN6Rpvx0qideTdFonIskbjvK4xBFlqU7aoH+lnNYbvc533cHclF/DdRxhTCQIUp5BrQlH48srd8n1IWobz42+r8pGuYtm8pqSOwTYyw6jrB3nJHn5qgPtJyj8SwS5nLsKrA4QJgJM39j5k023Aa0bS/v+u3ZgQ4wA7oGSWGP8oR4CRbAK21BxCcWM7ko0YFRsOFiFu+jQCe0eMHX9G4dsHeWrkNwYkLvXGR5112
*/