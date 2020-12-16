/*!
@file
Forward declares `boost::hana::equal`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_EQUAL_HPP
#define BOOST_HANA_FWD_EQUAL_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>
#include <boost/hana/detail/nested_to_fwd.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Returns a `Logical` representing whether `x` is equal to `y`.
    //! @ingroup group-Comparable
    //!
    //! The `equal` function can be called in two different ways. First, it
    //! can be called like a normal function:
    //! @code
    //!     equal(x, y)
    //! @endcode
    //!
    //! However, it may also be partially applied to an argument by using
    //! `equal.to`:
    //! @code
    //!     equal.to(x)(y) == equal(x, y)
    //! @endcode
    //!
    //! In other words, `equal.to(x)` is a function object that is equivalent
    //! to `partial(equal, x)`. This is provided to enhance the readability of
    //! some constructs, especially when using higher order algorithms.
    //!
    //!
    //! Signature
    //! ---------
    //! Given a Logical `Bool` and two Comparables `A` and `B` that
    //! share a common embedding, the signature is
    //! @f$ \mathtt{equal} : A \times B \to Bool @f$.
    //!
    //! @param x, y
    //! Two objects to compare for equality.
    //!
    //!
    //! Example
    //! -------
    //! @include example/equal.cpp
    //!
    //!
    //! > #### Rationale for the arity of `equal`
    //! > It is a valid question whether `equal` should accept more than 2
    //! > arguments and have semantics matching those of Python's `==`. This
    //! > is not supported right now for the following reasons:
    //! > - It was implemented in the MPL11, but it was not shown to be useful
    //! >   so far.
    //! > - It does not make sense for `not_equal` to have an arity of more
    //! >   than 2, only `equal` could maybe have those semantics, which would
    //! >   break symmetry.
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto equal = [](auto&& x, auto&& y) {
        return tag-dispatched;
    };
#else
    template <typename T, typename U, typename = void>
    struct equal_impl : equal_impl<T, U, when<true>> { };

    struct equal_t : detail::nested_to<equal_t> {
        template <typename X, typename Y>
        constexpr auto operator()(X&& x, Y&& y) const;
    };

    constexpr equal_t equal{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_EQUAL_HPP

/* equal.hpp
n95PgWe2Bv+QbuHneOXAWd3Cy+P/l+T6X06pP0e5Wq+f8T8lfWNK+sFKaVL6eSnpT/woOb1NOSMpfV5K+paU8s9UXvtr4vg9rLe/b7fjR/EiLJ5e2ZPbo/+FW7XydvbptjyKj6SkV9b1XB7oUYr9y35J9i9Bf5LjtyTH70/N/8Pk+NtT869Ijl+WGu9Njnenxk9Kjt+WWn92cjzmd3J8hy0pfnOX9ifH16fm35Icj/mb0v7keMy3lPYnx29Ijfcmx0/s0v6keMyf1PYnx2O+pLQ/Myke8yOl/cnxmA8p7U+Ob+nS/qR44HNq+5Pjb02N9+rxOn7qR6K1w1MlxIyfevzCrvH7E/MXd42/PTF/Ttf4ZYnxJ4Z1iXcnxr/cNX5bYv0Pp8Yzfsbjb+4avzmp/cnxOn7q7U+O1/FTb39yvI6fevuT43X81Nuf0yV+YlL7k+N1/NTbnxyv46fe/q7xjYnxtcnxOn7q7e8a35LU/uR4HT/19ifH6/ipt39oajzvL8Ul7iDM6fOZnI/3R5CoyD6LGQpUpGcoV5KkeQm2qkgMrt0dyFAueqUzFk1T7H/qZO09skGoWnQY0oT9VVWMAtkYFdniiLpkil/pcO3EtWxsWRx0fj/VEZiESxXOoqdr35crSe6WJ/z6DpXeZrf5Px3oEI7QvgaudhM4as3Dcg0su57anjXxwzej1qcXw3JHcbq9gcS48goH3YNej0fcsIe5KTqzE8eEVnmFTTaYd5iPCLX64AVtRiMrjJ7ojIXTSc3YPwswMufdLjjvIxAJa+7a1I11bFLTPLqeXqW8gj2/EPG+qnrqd0Jj5f2cBAUYCsd1gJaP3zb6qGaHy2U6h7iY3ZLJy9G+wAS0zRQokFdkmd8NjPKvZKhR967DvEkRdcOCkPixnqpEQK1vAtdXQPWJU9yzOkpQ3VDIDs2tgSxxqqidnJZw6d0Xzvazkd/LBbpJZiHgL2f4LxbwTwnVWQ3BCZohb7KkHZsEDYJnqxwGXFyj22oZhMIpFrxPoVupPVT/cq7fH6+/huu/XNQ/18f+abU+lKEJR7cLpO9ogbhVkM47e0ISFgX5hJnyCYCQjhHqLOhk/XQT8acog6EeZmOibtgTlS2mSPfjMYzBHxwfDxuPRzqPB1kc7bX8EqvZGOl+fBBvRf1Uldkhm8J9k/YXP0vmxxcmv8flWTxgy0zalcSh7D87aJ1aYeH+wpC6lb07WJrxEQIy9KpFojqVoLlb/hxxgt+8PNbZTTy3FXQJvWVBU4yqvsPZcilTrjZjDJ+IbOAYG2KsiJFLgFHdgyRg2TOoJ36VbcNr+g98ZT0E3ehBbHfcrjzWBrJSYVFRBpj13kDdDhQwKRY4n52ak+H484TOlzpjmypNNcK4vI8ir27jSf1xBHvx/rA+mEZ4GWMNn45pNivExSBdZQbywvJtlrZb3czqXPs4vWjD23N/JPN/pmT+MjU+Ozme8+vr36Cu639ifE6XeKUTsm0e5N3Q390LPYvwgER4lStPfGQ8j5fcn1VggPpVHSVZxgAcVliTVBaVlUAu8d5LhzN9kQuBAWm8QuAA4+F3CQIeY4h2WTBu30TqJAMIDxqN02AqeUMnd7tXuR6JYU8daXWT6ubIgp5rZPjp7lCm8t4LYs0KVGLqqX4TlNu4YF7auJVjSEQvWnmG8lBGQisJYZXref3SQ3onW3r9GYrxQ6qfRHypX69SHWP1+q4Fsa+HQp7Aac+pos2gUQi6OfTa1o88u2jel0KP3uf31PkYmITJthyNo9nz8AH6tSoDgfH+UVLhLaSKlqf8EnIN/zn86lV+zEKOvF7nlj+LM/jzlXdMcX2NbBE4TfoN8wyMAt3ra8A=
*/