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
xt0uhbO3fWi7SsJButKzPWncBUcV11DmQTujjnFuwt/F29ZBm8FlTnJIQhsur1Q4MIaFttmZQ7GxJn7fRD55mHQ5RsTmM7lqE+4Xqd2985MrKJp8+mNQSjlcT/MYSLUvoEFvdHEU+EdatYNvNR7Jij5O36aZ7Y5gzwNmEqSxr1RXePy8KB/y6Y6juNPYh/NjX3DQTQEdNTABFjrGiW7qNZSh1c6jjVgpRF5M9CTsqfERL8Eh+zJks4BYL5sFZZX55e1kzSS8lbHa7+U6mDGbECOo+ktU4HByARuMQwotByXwdOIy0clvtzgkAAeW4hF4Es2BiiI6+nDKriWfI9XLl00H0CC4pl0ZfW9ce8EQvm00HOAqntVl+tjlJfz1zNTq5GxgZvvxxfz4yjC37apTtSmBMNXzZTzwgS/ZzBxWB0p4AGoC09dQBdxVmGzk/M2fOOKJNUF+7367IUlx/AYdjKenWpEcVqAXbG4qIgt8PkzkFyhIIDAts0baAWemOw23A5bNVwoj1mwOorrEwRNmrXUCq5kSd4094SACy3mVJUHkKJziNREpAWaArg==
*/