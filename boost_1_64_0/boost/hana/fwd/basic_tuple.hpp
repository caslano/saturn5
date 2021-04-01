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
42zvzEVxjsZHWPtFUrbpRTgV0iuRE4haZzfyBm7S4Vhmwkk+RElLEpQ9qJpZgYNTKcpSDYgQWluXjicDlyQKBsh2SIXCmb5pHrgG2AGdnJtX2WSrnmk18ZvMwcNisvtraMonWQlBjv7XoTLdCXMPpAIc8V67Drj/o4J3aoBbX44677Hg4SeMGJ3T5O7UEVaw3+TpopxKchIuLsmMpQQ3niC9LEPRrq7v83xKt80eu5ypkLcY4bxsoDuYRqTVmdY6YGAu9OV35vNDKsrii27IXknwqoQQ2CNTu/iyU0HxJQdOU9udxTH+WWu21HFvykrzLXOMfzyFIkc5Dh4mUiFpmLoL8zAVtv7eJk14PSHinUqNdJj2XZw5REuCnMgf31fwgmZWwxx/NySG5Up6CRl+aIp1hkty2ed7HMZfS41GbWi/hZp+3auspdamMI3oShbqTDo+PXAdjMf8W7uK2MeJQAdZYZgb6H9VICQzPauNOVAn+G1pWRIqQ2u6SUcOhO6myGEifgDEAUAzPZBWlPCQBzRe4Q3ZnygYnYt8VKKO9PVLFDvyyNLIe6ux8w==
*/