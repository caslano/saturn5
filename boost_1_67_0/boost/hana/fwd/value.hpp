/*!
@file
Forward declares `boost::hana::value`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_VALUE_HPP
#define BOOST_HANA_FWD_VALUE_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Return the compile-time value associated to a constant.
    //! @ingroup group-Constant
    //!
    //! This function returns the value associated to a `Constant`. That
    //! value is always a constant expression. The normal way of using
    //! `value` on an object `c` is
    //! @code
    //!     constexpr auto result = hana::value<decltype(c)>();
    //! @endcode
    //!
    //! However, for convenience, an overload of `value` is provided so that
    //! it can be called as:
    //! @code
    //!     constexpr auto result = hana::value(c);
    //! @endcode
    //!
    //! This overload works by taking a `const&` to its argument, and then
    //! forwarding to the first version of `value`. Since it does not use
    //! its argument, the result can still be a constant expression, even
    //! if the argument is not a constant expression.
    //!
    //! @note
    //! `value<T>()` is tag-dispatched as `value_impl<C>::%apply<T>()`, where
    //! `C` is the tag of `T`.
    //!
    //! @note
    //! `hana::value` is an overloaded function, not a function object.
    //! Hence, it can't be passed to higher-order algorithms. If you need
    //! an equivalent function object, use `hana::value_of` instead.
    //!
    //!
    //! Example
    //! -------
    //! @include example/value.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    template <typename T>
    constexpr auto value = []() -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename C, typename = void>
    struct value_impl : value_impl<C, when<true>> { };

    template <typename T>
    constexpr decltype(auto) value();

    template <typename T>
    constexpr decltype(auto) value(T const&)
    { return hana::value<T>(); }
#endif

    //! Equivalent to `value`, but can be passed to higher-order algorithms.
    //! @ingroup group-Constant
    //!
    //! This function object is equivalent to `value`, except it can be passed
    //! to higher order algorithms because it is a function object. `value`
    //! can't be passed to higher-order algorithms because it is implemented
    //! as an overloaded function.
    //!
    //! @note
    //! This function is a simple alias to `value`, and hence it is not
    //! tag-dispatched and can't be customized.
    //!
    //!
    //! Example
    //! -------
    //! @include example/value_of.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto value_of = [](auto const& c) -> decltype(auto) {
        return hana::value(c);
    };
#else
    struct value_of_t {
        template <typename T>
        constexpr decltype(auto) operator()(T const&) const
        { return hana::value<T>(); }
    };

    constexpr value_of_t value_of{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_VALUE_HPP

/* value.hpp
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
*/