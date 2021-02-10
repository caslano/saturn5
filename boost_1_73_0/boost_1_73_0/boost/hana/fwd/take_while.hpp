/*!
@file
Forward declares `boost::hana::take_while`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_TAKE_WHILE_HPP
#define BOOST_HANA_FWD_TAKE_WHILE_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Take elements from a sequence while the `predicate` is satisfied.
    //! @ingroup group-Sequence
    //!
    //! Specifically, `take_while` returns a new sequence containing the
    //! longest prefix of `xs` in which all the elements satisfy the given
    //! predicate.
    //!
    //!
    //! @param xs
    //! The sequence to take elements from.
    //!
    //! @param predicate
    //! A function called as `predicate(x)`, where `x` is an element of the
    //! sequence, and returning a `Logical` representing whether `x` should be
    //! included in the resulting sequence. In the current version of the
    //! library, `predicate` has to return a `Constant Logical`.
    //!
    //!
    //! Example
    //! -------
    //! @include example/take_while.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto take_while = [](auto&& xs, auto&& predicate) {
        return tag-dispatched;
    };
#else
    template <typename S, typename = void>
    struct take_while_impl : take_while_impl<S, when<true>> { };

    struct take_while_t {
        template <typename Xs, typename Pred>
        constexpr auto operator()(Xs&& xs, Pred&& pred) const;
    };

    constexpr take_while_t take_while{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_TAKE_WHILE_HPP

/* take_while.hpp
htEF9apFOhwXw4l4s5C1Te8o1bsenP9y1ts76O+96TH9GIRODiZV7vLdv/ODo8PXEDnS89sVvkvYEuNDP947PyTI/X54fHDyu+VJdMkcFmbpkuCrlkuC+r67l5aztiRK6hNWCduaLjvaHXhvsWIiktrm+yMiv5WmwIjmzkptAHuW5KEERFt0PQxakr5tLzWakMZScAPeEBIeD/ude6ERPH86Y/Rx9jW0YbYv3QpnOSUAs4RwoTK7SpNrSlEyQovINs23QMoYRotZUTzmliP75j2VrtPCQV0o0fSKYrbYaKQXKfxHjJ3tToRprtCHyvE0u7CXLjgynfsfaXk5KpOG22R5WbyyFj8aZto3DfIySReL2eLVvfpn32cTQoI4/6m+gzr4pS7+vb93sHe+l3wuhlI7k2SNFPTL4aJcztfe7f3a+/3k7GBte2N7fSP5gchqRz30V/olK9e215tWvk/zcTZpNLkipkzLtR/YqNiUKrL/SWeTNfaDdakm+8GTIb2LhX+3Ye9wcPz+Xe/scP+Xk/65SXB4lRH3JpJvSFDSP+3tG4SoWeguQMQoDJRT9fbeNYIMukSd/ve3tl882ST/27rPVK60/2GYrcuArfHKf/2VfEdKJHAYLFvrr5Knj5IJ4f7Jo6dNh01YWotG
*/