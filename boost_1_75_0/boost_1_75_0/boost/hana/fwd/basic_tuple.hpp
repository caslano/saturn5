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
iukKsZP+QBqLAaOHn5iEm2Tq5tbBSehGOzDRy/fCGw6QBxSJdM7rVxsgf/VL2mo5waq5f6BQo8JJ2YKTsmIYBpfKIHWRgbn3yN3wTCxQNSIzM+W2ftCMcb2ZVp5MBlrnA3cK83RleGl8lg448N2BxIHkBV4Kr8ObxddhG1rLUVmFzcDWjYSjEO52+bK3QhN/go1Nb1dsbJE9sNQtcgEvfXJ1jlIS36gm9k1MlDDxqiVIWzbgJfYtdfTEy9q7M/BKbWGXNxJuuog15b+4qRsvLh6levN1N5EGlLQFC4lE9lLGrRfQY3Qd2pYhvJEppawI3RF3KWOnm0bNpBGp9SaYKV/F0WYnAqEtDWknQZ2nc/GO61ExQQqXUTGVdPUaKyRqTNKktKX8AhqheBKe7/XCm5Zo0FZLdy6fvaDevnxeeZPCL+GF7BGZwv38k+SZ3Vpejt7owi9CFCG+Ba+UM6XUBoEKGq7vPa72cNzl5e9CFWJGL88HMIkRA4dGNkk075uieX1I8o+R+L6rEl8dAx6AJns9eaGdsimvP5gPm3oHUZgG+o//zZBPrRF5Dpt6kTL4i1KAn7eVU/k0C/SBJYypLJDv4odeweZR8mEbL4o8h8RexMxueVudyDK2JsyQ7DD7PiJvSzaUi9ucZGzmjootmCDmZmdCO7E8DRoBIfREPyOah3ZiVo24/CXgqNH4Tr4FFcCCHfhBPE58DivO
*/