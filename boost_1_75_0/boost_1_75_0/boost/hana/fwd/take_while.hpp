/*!
@file
Forward declares `boost::hana::take_while`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_TAKE_WHILE_HPP
#define BOOST_HANA_FWD_TAKE_WHILE_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Take elements from a sequence while the `predicate` is satisfied.
    //! @ingroup group-Sequence
    //!
    //! Specifically, `take_while` returns a new sequence containing the
    //! longest prefix of `xs` in which all the elements satisfy the given
    //! predicate.
    //!
    //!
    //! @param xs
    //! The sequence to take elements from.
    //!
    //! @param predicate
    //! A function called as `predicate(x)`, where `x` is an element of the
    //! sequence, and returning a `Logical` representing whether `x` should be
    //! included in the resulting sequence. In the current version of the
    //! library, `predicate` has to return a `Constant Logical`.
    //!
    //!
    //! Example
    //! -------
    //! @include example/take_while.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto take_while = [](auto&& xs, auto&& predicate) {
        return tag-dispatched;
    };
#else
    template <typename S, typename = void>
    struct take_while_impl : take_while_impl<S, when<true>> { };

    struct take_while_t {
        template <typename Xs, typename Pred>
        constexpr auto operator()(Xs&& xs, Pred&& pred) const;
    };

    constexpr take_while_t take_while{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_TAKE_WHILE_HPP

/* take_while.hpp
4X03Xzx9cnHFCqakSchgLhQ4aPNC8XOm+AvFv8wZm8NOKAErbxhbNCbDXmb5MsvFNNh3Wa4EfsEiBTc3lMZQbrMV2rxmJ3jElCzeYvNjQDhQ1p4+SUrAFMdJmvglK74HbBGN8LkC4G8Vf7lMb5UyU8orphBwNwQ/zatFih9k14yXq1CTFtm6hr+4XePkGCBWyy9Hg6gULL8GEQsFxFgtaS6rUGJcN4E6UdiXkC1LAezuJhnK0jwXCmZgjCv/mh2FiHKZ7EgA/ShKiNf4dG9jDJDI+8SzYILnR9WPdde7NaQ22ICXD2vAH1579pAj9JfFsTXLWcxVHc2+QSPcJOUVCdymQj3hhbgIkThy/BZQqml281xSXSyu52dYrMm/Thpr/f7S9mFIBOIudB4KtvZ8VvpBZ3CAkXI+bR6y22DYBqtuHOI3MJin3c6zbMVT5HxPhNrJs9TaxoyCXMk2nm0JoyjSy7gTWXNr7vKIfCm9vRcX5N29ePdK+YQg4ePZTz9fnD8f6HDusMJibfte0fg7WH7u3yoJRZ1pyo3uqmDcZopTWcgvCLNlQkYrbltfOBIQmVyJGDdqd6txjyl7nFMwiMo9r1aBDqCgusae3pSwLtmqD4LdNAb3JF/ouS1fck/BmFhqL4ouxsVGdUQk1/RutUdRMg92zj+cvjx7ffZyDFftHe1QwWq1Vi2c3Wrt5fu3H96/O31HEjuMTfVj
*/