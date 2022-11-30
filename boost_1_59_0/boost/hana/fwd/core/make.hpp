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


namespace boost { namespace hana {
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
    BOOST_HANA_INLINE_VARIABLE constexpr make_t<Tag> make{};
#endif
}} // end namespace boost::hana

#endif // !BOOST_HANA_FWD_CORE_MAKE_HPP

/* make.hpp
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
*/