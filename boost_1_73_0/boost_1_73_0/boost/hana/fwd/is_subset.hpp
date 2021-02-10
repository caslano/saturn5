/*!
@file
Forward declares `boost::hana::is_subset`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_IS_SUBSET_HPP
#define BOOST_HANA_FWD_IS_SUBSET_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>

#include <boost/hana/functional/infix.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Returns whether a structure contains a subset of the keys of
    //! another structure.
    //! @ingroup group-Searchable
    //!
    //! Given two `Searchable`s `xs` and `ys`, `is_subset` returns a `Logical`
    //! representing whether `xs` is a subset of `ys`. In other words, it
    //! returns whether all the keys of `xs` are also present in `ys`. This
    //! method does not return whether `xs` is a _strict_ subset of `ys`; if
    //! `xs` and `ys` are equal, all the keys of `xs` are also present in
    //! `ys`, and `is_subset` returns true.
    //!
    //! @note
    //! For convenience, `is_subset` can also be applied in infix notation.
    //!
    //!
    //! Cross-type version of the method
    //! --------------------------------
    //! This method is tag-dispatched using the tags of both arguments.
    //! It can be called with any two `Searchable`s sharing a common
    //! `Searchable` embedding, as defined in the main documentation
    //! of the `Searchable` concept. When `Searchable`s with two different
    //! tags but sharing a common embedding are sent to `is_subset`, they
    //! are first converted to this common `Searchable` and the `is_subset`
    //! method of the common embedding is then used. Of course, the method
    //! can be overriden for custom `Searchable`s for efficieny.
    //!
    //! @note
    //! While cross-type dispatching for `is_subset` is supported, it is
    //! not currently used by the library because there are no models
    //! of `Searchable` with a common embedding.
    //!
    //!
    //! @param xs
    //! The structure to check whether it is a subset of `ys`.
    //!
    //! @param ys
    //! The structure to check whether it is a superset of `xs`.
    //!
    //!
    //! Example
    //! -------
    //! @include example/is_subset.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto is_subset = [](auto&& xs, auto&& ys) {
        return tag-dispatched;
    };
#else
    template <typename S1, typename S2, typename = void>
    struct is_subset_impl : is_subset_impl<S1, S2, when<true>> { };

    struct is_subset_t {
        template <typename Xs, typename Ys>
        constexpr auto operator()(Xs&& xs, Ys&& ys) const;
    };

    constexpr auto is_subset = hana::infix(is_subset_t{});
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_IS_SUBSET_HPP

/* is_subset.hpp
x1Rjrz/svumeOmb4ujQLeTjsvrZaUIsSVm3gVW9ozRMqRIP1wLw7GnadgLJFCauCQg5bIGTMUKk4G3719+7RcNR73e0Pe8c9JpWuqoJGV9t1gUurXDBh8BkNe2+7FqhsSFi1I2+6fWDQSe8f3ddFcG/WBpeb0v1/OCftmHK/Zy4/kwCVT+fsdynN7vJLDYVaUW3NZWuraeXBcdM9tLPgjfy4q4zympPIyIarXHXDkQ/nDKgjI57LfTrS4CU5cCsV+rq/JAVeamUnkUx2lhSYT5ZurPDST8se48rRJY9pOZHhDekoxxwqZu3CnU7hzk7Bi0rn2ouaYeg3iUgiDgRcPacrc9abiuTXlUPf6/CkrkpnOZ0Hs3ZuGWtDTr9Sexg0QuUmt9eB9vDKnmWnQvkWgZzQIjgEsry1lH3WKaQrG3rSd7bjAEdrbgFmk1QBfxRg7iyBiQXyIIllgONOBm8JBOACoJUN9oxRy0IB7jshyHu4wlvqnx8G0yClbWnq0wOXI1VHd1zxUrUr3FkG+uzTOmRS1HpWGRdXQURSaVr5tNBMUxEPdzgddQDlCVYVhKwG3NxRzjV/Doq1sCSG4fDdIAq8FJ0aBEPbGAxBywckrwwpP/EeFpLc/MG0XYgZOynq6hO6Zn/virTLiKSP
*/