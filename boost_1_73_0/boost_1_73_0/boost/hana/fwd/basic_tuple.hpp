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


BOOST_HANA_NAMESPACE_BEGIN
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
    constexpr auto make_basic_tuple = make<basic_tuple_tag>;
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_BASIC_TUPLE_HPP

/* basic_tuple.hpp
1i7VT+PbOEnxeI1+EUz5+xdasf/yACHs6cbqQJsksRWwXRzbQVpkshVgnWC2AoWks7XyOqFr59layWvvzVrxawVbJ4OtQO1Tr2dv1UOlSmryh0/6qnNJ68RXi37fqYn4jDD/csgXS/pE6Md6q7gF+5RvneLDauoGKps1hTsfNe0tfhWBCXX4RTw3UOY4p8JHb9fmTtgbyympEfPFFQo/Q27mPLFvQ9clep8y0zfQCqsgXgq3S0K4JHr5Hc4B0UCH8NqwZ88S54woUnY7Mdwm3OgA49YRJhF1DAnQ3yDGrsksAeYEa9hT1rcTcxTxdtL1cjyWmHRuz18te5QBsyeWdPaK/9ntic4SCTFM/FXswj/Pxe5ut9W/6nBfoGpHVxVIiC3vqvJ6voXPa5VgvgSi3OH9bt78ZLbErRvNjzgz4KWHybkkOMNEKD2PdB1mFCb+K6q4wu+61N8BVS3qh4YuvPE8gNx9J6k/pVoiDlu9NJUPmngx0FuapPpHVC2WmicG/FFjMtaDbgygW3FvEuPrk7w3t7khDDM0wbkdaAZopCMERKnKjkDPAEo65p2FkXKEd/ltmvZmWX6HoltlRx9ouOXGGH9b7b733iUE0rn0wQPgLfPbOwPefI8BoO2FQdVBUbplz52ZDqfDTZqa
*/