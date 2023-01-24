/*!
@file
Forward declares `boost::hana::remove`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_REMOVE_HPP
#define BOOST_HANA_FWD_REMOVE_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Remove all the elements of a monadic structure that are equal to some
    //! value.
    //! @ingroup group-MonadPlus
    //!
    //! Given a monadic structure `xs` and a `value`, `remove` returns a new
    //! monadic structure equal to `xs` without all its elements that are
    //! equal to the given `value`. `remove` is equivalent to `remove_if`
    //! with the `equal.to(value)` predicate, i.e.
    //! @code
    //!     remove(xs, value) == remove_if(xs, equal.to(value))
    //! @endcode
    //!
    //!
    //! Signature
    //! ---------
    //! Given a MonadPlus `M` and a value of type `T`, the signature is
    //! \f$
    //!     \mathrm{remove} : M(T) \times T \to M(T)
    //! \f$
    //!
    //! @param xs
    //! A monadic structure to remove some elements from.
    //!
    //! @param value
    //! A value that is compared to every element `x` of the structure.
    //! Elements of the structure that are equal to that value are removed
    //! from the structure. This requires every element to be Comparable
    //! with `value`. Furthermore, in the current version of the library,
    //! comparing `value` with any element of the structure must yield a
    //! compile-time Logical.
    //!
    //!
    //! Example
    //! -------
    //! @include example/remove.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto remove = [](auto&& xs, auto&& value) {
        return tag-dispatched;
    };
#else
    template <typename M, typename = void>
    struct remove_impl : remove_impl<M, when<true>> { };

    struct remove_t {
        template <typename Xs, typename Value>
        constexpr auto operator()(Xs&& xs, Value&& value) const;
    };

    constexpr remove_t remove{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_REMOVE_HPP

/* remove.hpp
CNBGYBOwBWgC7nPjYZub3/lv7t8nqXQaIRPkkEJhMpBblC6eCkqmLYgYry0eHy811gv+9+Tl/vy6yu/d7vqp/ResEuVjiuT5aZSSlACpQvYJaHEBGlmC45COslFC/mOYgfL7sxqdVaDTJ8vHIp/rjfXtDxyKrLrLBamefIyPCT5GViv/RUAhT35vzwfB7tDb4TXLL7v/TwNXs/3v7U2F46GZp74R2r8GGzSuQX4nMOYvkt9zI7xrbfIZn4t4TK1WPk/v1nvyvxra3b8/8Frg7dDBwPa+HwUfK0uLLZBfR3IuXK38caLsuurJfyg4E7oRvhQuTzqfc8u3/6/kyefrOQ8FvpZzG651/t9MufmfrwV8LeFrwP3AA8CDwEPAduBh4BGSY2AH0AzsBHYBjwItwG7iY5toD/A48ASwF9gHtAL7gTagHegADpBcbw4iPwR0Ad3AYeBJoAc4Ahwl/mxD1AscA/qAABAEQgAfhnzSOg5wV5xw2z2JfAAYBIaAU8AwMOJeH3Pz08g/7ZafcfPnkJ91y+cpty7OuOVJ5FEgBmjABWAKmAZ0t84s8jiQAPh8aAJzgOVet5E7QBK4CKSASwCfzeeBF4DP5Mn2MKQmtDF1Mq4NmrFkXAvpatycGkvPaUEznkwYIc2OWvqco5tGX5Qfg6YR03lh2DLnNMtJP/PsGT3mTEc0fWra6XMcS59MOpo9pl1y+jXVSVra
*/