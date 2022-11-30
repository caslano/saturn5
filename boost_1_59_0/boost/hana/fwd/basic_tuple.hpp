/*!
@file
Forward declares `boost::hana::basic_tuple`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_BASIC_TUPLE_HPP
#define BOOST_HANA_FWD_BASIC_TUPLE_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/fwd/core/make.hpp>


namespace boost { namespace hana {
    //! @ingroup group-datatypes
    //! Stripped down version of `hana::tuple`.
    //!
    //! Whereas `hana::tuple` aims to provide an interface somewhat close to a
    //! `std::tuple`, `basic_tuple` provides the strict minimum required to
    //! implement a closure with maximum compile-time efficiency.
    //!
    //! @note
    //! When you use a container, remember not to make assumptions about its
    //! representation, unless the documentation gives you those guarantees.
    //! More details [in the tutorial](@ref tutorial-containers-types).
    //!
    //!
    //! Modeled concepts
    //! ----------------
    //! `Sequence`, and all the concepts it refines
    template <typename ...Xs>
    struct basic_tuple;

    //! Tag representing `hana::basic_tuple`.
    //! @relates hana::basic_tuple
    struct basic_tuple_tag { };

#ifdef BOOST_HANA_DOXYGEN_INVOKED
    //! Function object for creating a `basic_tuple`.
    //! @relates hana::basic_tuple
    //!
    //! Given zero or more objects `xs...`, `make<basic_tuple_tag>` returns a
    //! new `basic_tuple` containing those objects. The elements are held by
    //! value inside the resulting tuple, and they are hence copied or moved
    //! in. This is analogous to `std::make_tuple` for creating `basic_tuple`s.
    //!
    //!
    //! Example
    //! -------
    //! @include example/basic_tuple/make.cpp
    template <>
    constexpr auto make<basic_tuple_tag> = [](auto&& ...xs) {
        return basic_tuple<std::decay_t<decltype(xs)>...>{forwarded(xs)...};
    };
#endif

    //! Alias to `make<basic_tuple_tag>`; provided for convenience.
    //! @relates hana::basic_tuple
    //!
    //!
    //! Example
    //! -------
    //! @include example/basic_tuple/make.cpp
    BOOST_HANA_INLINE_VARIABLE constexpr auto make_basic_tuple = make<basic_tuple_tag>;
}} // end namespace boost::hana

#endif // !BOOST_HANA_FWD_BASIC_TUPLE_HPP

/* basic_tuple.hpp
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
*/