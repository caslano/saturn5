/*!
@file
Forward declares `boost::hana::not_equal`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_NOT_EQUAL_HPP
#define BOOST_HANA_FWD_NOT_EQUAL_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>
#include <boost/hana/detail/nested_to_fwd.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Returns a `Logical` representing whether `x` is not equal to `y`.
    //! @ingroup group-Comparable
    //!
    //! The `not_equal` function can be called in two different ways. First,
    //! it can be called like a normal function:
    //! @code
    //!     not_equal(x, y)
    //! @endcode
    //!
    //! However, it may also be partially applied to an argument by using
    //! `not_equal.to`:
    //! @code
    //!     not_equal.to(x)(y) == not_equal(x, y)
    //! @endcode
    //!
    //! In other words, `not_equal.to(x)` is a function object that is
    //! equivalent to `partial(not_equal, x)`. This is provided to enhance
    //! the readability of some constructs, especially when using higher
    //! order algorithms.
    //!
    //!
    //! Signature
    //! ---------
    //! Given a Logical `Bool` and two Comparables `A` and `B` that
    //! share a common embedding, the signature is
    //! @f$ \mathtt{not\_equal} : A \times B \to Bool @f$.
    //!
    //! @param x, y
    //! Two objects to compare for inequality.
    //!
    //!
    //! Example
    //! -------
    //! @include example/not_equal.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto not_equal = [](auto&& x, auto&& y) {
        return tag-dispatched;
    };
#else
    template <typename T, typename U, typename = void>
    struct not_equal_impl : not_equal_impl<T, U, when<true>> { };

    struct not_equal_t : detail::nested_to<not_equal_t> {
        template <typename X, typename Y>
        constexpr auto operator()(X&& x, Y&& y) const;
    };

    constexpr not_equal_t not_equal{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_NOT_EQUAL_HPP

/* not_equal.hpp
qOFOSSJzOONLhJD6GMrPN8ui2V4TyC00M6OjvRBa+xH3bIQuRcJ0hNwCZjWu2JoOmnNNfAQIcQ4Jg+KKEYeQT54FfbdGphcUc0LC74ffmolOQ5riyFxbqU/spOljpCjT5xWf0GOpKKg9EDXbyeAfeZq5m6+q/x45A7jrOW8gk7bxWtXCCoNG/2BHR5Yu8KeG0HlB0qYLU4Yo6gYxUyOFFkIz3VMvtoGH9Agl41ujlr5cNTy7Pnd32rCNXlJtIyMmW+uLvWLaGUfyrchoj2VpNV+lGBxv3YpovzcyosBLoG7/5oBxh9TI3L1zTkGwvF/WX8zRC83oU7P3ItK6PXfv3D/4AALwu5/BuAo/XZ2AJzwd/j1Z/DHG/9AzEhNWqDuR/AKvQbgzxNdPMcnji5C313veZnyNqSlLqmmu25VqdIUq94qaUf0sydtq6utEateGmveX2YYMy31vQRPtTnWuu5Y4+Tj8SSvYuOej5G0nbhjYgBQHuxyr9s2JLmdcJADZrJU9SGXRMWrbxefNzOnt6Xu1m8oS8ktdZwD90LXQPxLl4PRwoRt9OBm3Qlm84lUIZr7x0GV2PGxQ32etPDo6xyXevQ9yfI5bXNXIqTrUY2pry7l88/13Fa3ak1xZzu2x66QHnAJVzEZF9Wymopyi6RNZ5MX3sew2a5RcmaqRIaa5K9XuOO1daQbSdla6SPOKznCK0a8YWmGn5xO1r/00sb6PX9oKf+DSMhgQMN1HL6rbg9LnjiB2wCbU/tO6OCOFdr9XfPiiIW+qjoqe6RcHdvIrLnikC40qWJvbCO3LL8oeVgmb1A2Xsr4r/nBlF2c3APyafzu316728cmJ9U/XEt+dUxLfr5iU+L6iogW9WqQf3xI/Ld53TmqRvwX9vy1LfN89IfF9Rov4nImJ7/1bxC9vEX9vi/YOmpr4vvWSxPeSFu1z/yzxfSLeW/W/k4xuFJ2TIaYJYk+cxbCdfjPFGVL9LW+b6Wontajfgqkt8NXifejkFvRq8e5o8W6/LPE9s8V7OulJL37E6gvOWcXO0WWj4Me9T7pQ19fvY/dpemD36QhCDSNUJruYs/3BhmCH9hpA093fCHAiwO6lg0ts0s6abvzy7FKs+pJwktWJLlgLoC36G6ZfEFZ1Dq8I1cdPTtvMj7RUVzv9Ig/90NcrXC+wLDfydpx+9XOHlv5Hn7eV3qx/dIZD/OZ5rn5Di/o6DXhO/iLd9k3tnzcSD8+5oU145nyX0kzfKee77cW7zfgYfAqvZnTZzPDW9IAn/lcvHiI93DF8VXcGv3Hpuzx7aOlv2tUBPdyi93OdoYdbjG3sDD3cYlFDB/RAmu2fSny3F7/s09b0oPCvn2ubHj7xMihFthYav/3iOOT3ip9+hrB98t7P7j5xEePOxtcFBo4VbzfQvChcZQv0bEzl/lmHEH0sIzFsoZvkbrqXm6xv7Ohqv9qRvP7zfrx9vYCVpPGkIo33i5KnSZX2RHHfaO9AnpYxhy/iqwycJt57nUnUxE45czDm20qLRSVEk3F7Lp+wTGfx8L6PYpEnVNR1dBDE4AWZk9OqV3NmBxlkcrsHewfGyhKu4hKCRgnXcSJ7pARM0mSb1UNPzk2pdIbW20IbbQiY/Xlo/7fBoprkISmVPwrt/y44tGaYZUihpbJ3aP/3wdNrhiUPKUyuPDK0H5eX1wyzDim0oqBSLki7HaC5LLssq/lkvnW0uQ9xD1c8OschPn6Cq27ejbq/WByxlWXweFKtGw3r52XbKNnITsjJw/3w/DkPLGUTU15rxVI8vjmS0qppNQyPTjzeJh/tSb7gFPHYC8ReyRAadM8lckuFJl2rRyqtRNJ2PrBx4FXGBuk=
*/