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


namespace boost { namespace hana {
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

    BOOST_HANA_INLINE_VARIABLE constexpr value_of_t value_of{};
#endif
}} // end namespace boost::hana

#endif // !BOOST_HANA_FWD_VALUE_HPP

/* value.hpp
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
*/