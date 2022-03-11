/*!
@file
Forward declares `boost::hana::make`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_CORE_MAKE_HPP
#define BOOST_HANA_FWD_CORE_MAKE_HPP

#include <boost/hana/config.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @ingroup group-core
    //! Create an object of the given tag with the given arguments.
    //!
    //! This function serves the same purpose as constructors in usual C++.
    //! However, instead of creating an object of a specific C++ type, it
    //! creates an object of a specific tag, regardless of the C++ type
    //! of that object.
    //!
    //! This function is actually a variable template, so `make<T>` can be
    //! passed around as a function object creating an object of tag `T`.
    //! Also, it uses tag-dispatching so this is how it should be customized
    //! for user-defined tags.
    //!
    //! Finally, the default implementation of `make` is equivalent to calling
    //! the constructor of the given tag with the corresponding arguments.
    //! In other words, by default,
    //! @code
    //!     make<T>(args...) == T(args...)
    //! @endcode
    //!
    //! Note that the arguments are perfectly forwarded and the form of
    //! construction which is used is exactly as documented, i.e. `T(args...)`.
    //! However, if `T(args...)` is not a valid expression, a compilation
    //! error is triggered. This default behavior is useful because it makes
    //! foreign C++ types that have no notion of tag constructible with `make`
    //! out-of-the-box, since their tag is exactly themselves.
    //!
    //!
    //! Example
    //! -------
    //! @include example/core/make.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    template <typename Tag>
    constexpr auto make = [](auto&& ...x) -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename Tag, typename = void>
    struct make_impl;

    template <typename Tag>
    struct make_t {
        template <typename ...X>
        constexpr decltype(auto) operator()(X&& ...x) const {
            return make_impl<Tag>::apply(static_cast<X&&>(x)...);
        }
    };

    template <typename Tag>
    constexpr make_t<Tag> make{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_CORE_MAKE_HPP

/* make.hpp
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
*/