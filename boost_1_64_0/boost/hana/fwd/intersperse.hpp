/*!
@file
Forward declares `boost::hana::intersperse`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_INTERSPERSE_HPP
#define BOOST_HANA_FWD_INTERSPERSE_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Insert a value between each pair of elements in a finite sequence.
    //! @ingroup group-Sequence
    //!
    //! Given a finite `Sequence` `xs` with a linearization of
    //! `[x1, x2, ..., xn]`, `intersperse(xs, z)` is a new sequence with a
    //! linearization of `[x1, z, x2, z, x3, ..., xn-1, z, xn]`. In other
    //! words, it inserts the `z` element between every pair of elements of
    //! the original sequence. If the sequence is empty or has a single
    //! element, `intersperse` returns the sequence as-is. In all cases,
    //! the sequence must be finite.
    //!
    //!
    //! @param xs
    //! The sequence in which a value is interspersed.
    //!
    //! @param z
    //! The value to be inserted between every pair of elements of the sequence.
    //!
    //!
    //! Example
    //! -------
    //! @include example/intersperse.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto intersperse = [](auto&& xs, auto&& z) {
        return tag-dispatched;
    };
#else
    template <typename S, typename = void>
    struct intersperse_impl : intersperse_impl<S, when<true>> { };

    struct intersperse_t {
        template <typename Xs, typename Z>
        constexpr auto operator()(Xs&& xs, Z&& z) const;
    };

    constexpr intersperse_t intersperse{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_INTERSPERSE_HPP

/* intersperse.hpp
yuNcuYmRfZmvfQQnj2YOc4AqOC7MU5SIi0kXVpxXmwEKMkP6CAoYxClngoJYqeMPKEdOR27j7kGritr3+UfiYtX9WGfRCPfV24SLUswxZ+KTP4Gx0dYkuSn8n8SVnx1RMyzK4Fmmg+w5ZIH1dyYsXnuBNi6dmJdAdkd3ys3CPwW+eD1jOQ/OZcxi9lO4Mo+3+dp2/orRDUrvZpWy7rtXAlLlDpLzw6/A7HIRhy0yNWSZ+1T2bigRdYxfozp9/s2F3KFvJjqJgfDNRTMd27yNQvcTuoiNyvzQBOICw11yhhNFuJQ4Xiv4neXXJOUbn9rVCpC2CIS1sCARe/UmluBhrUZzBYh6I1BUK/oNG6gIJgvthiyTgeyui9V9+3pekDypLQ/kSk8SXMhYlF+FvfcgeHQxlCbXSt8HKvCWS3ERUM70gkml0xR8/tYUIKfCEkqzZQlwiyPQhQI431kkZcV7vDIwV5W8ST5otJqrbEPvNXU80WobrnCE6qxUJCvlOeVCru5gfU2TtFQTOmYknA2ooQsIL5EaeRUUDCoZSEpkN/F2OL0TjojT61Wo2w==
*/