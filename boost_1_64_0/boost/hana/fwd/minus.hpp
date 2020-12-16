/*!
@file
Forward declares `boost::hana::minus`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_MINUS_HPP
#define BOOST_HANA_FWD_MINUS_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Subtract two elements of a group.
    //! @ingroup group-Group
    //!
    //! Specifically, this performs the `Monoid` operation on the first
    //! argument and on the inverse of the second argument, thus being
    //! equivalent to:
    //! @code
    //!     minus(x, y) == plus(x, negate(y))
    //! @endcode
    //!
    //!
    //! Cross-type version of the method
    //! --------------------------------
    //! The `minus` method is "overloaded" to handle distinct data types
    //! with certain properties. Specifically, `minus` is defined for
    //! _distinct_ data types `A` and `B` such that
    //! 1. `A` and `B` share a common data type `C`, as determined by the
    //!    `common` metafunction
    //! 2. `A`, `B` and `C` are all `Group`s when taken individually
    //! 3. `to<C> : A -> B` and `to<C> : B -> C` are `Group`-embeddings, as
    //!    determined by the `is_embedding` metafunction.
    //!
    //! The definition of `minus` for data types satisfying the above
    //! properties is obtained by setting
    //! @code
    //!     minus(x, y) = minus(to<C>(x), to<C>(y))
    //! @endcode
    //!
    //!
    //! Example
    //! -------
    //! @include example/minus.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto minus = [](auto&& x, auto&& y) -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename T, typename U, typename = void>
    struct minus_impl : minus_impl<T, U, when<true>> { };

    struct minus_t {
        template <typename X, typename Y>
        constexpr decltype(auto) operator()(X&& x, Y&& y) const;
    };

    constexpr minus_t minus{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_MINUS_HPP

/* minus.hpp
SO6OkN3fvgFTxcHFiVhPzHlMYLElrIwrZ77JJ87L10n1WUgHKo10bwzV01VBTcurTmS37QXTef69kEwzCIoIqmUFudZxgJxQ9nMDpiDTUjDEP44W0AeKn7v43nT1GvbXLjcvAHjjJGrDKfNsftE4+0AEngWXGLaMyRIvm/3FhZ+AX8Rj2ZWyIMsYac64lPcZyce4VDpl++hhLGBH5ZeHXdFPIFaMgrj6xPL2v9G5TnlV9Lx7cep6BKmLU7fiBxoEf8ePl5WP/oEnOuRBnMCjn0xNIcFBPHsQnkayF4SlikdJyLEaDnLJjFrFZuKZXqSlNTc2FDHD9gHMFs+VLB3vwPxU0WxL6P3Y2sNTZ6dUvKNnCFRVLJEHV5NYAuZqz5AkxOWLZAYX8+rkgY2AXjGrpiIdPAIgkOakuTmAiCWIAJ+iTJac4l9J3wgJppI4OA/3oW/QNvgQXv8NcVLJsgPS54AFz3xDIcsjUnwImIp8JDGlMGS1Iyzy51RXLOcqoiMr5CxFwjwkXKIlnOgR7yIMT5OpYVu5tfukZK1Y7Ujf/UweU6A8R+HHwSWpbyLeVwLmTqwN4aYa8kPh19xM1BC77buGg0bQppx8Lfzudn3H1k+TAqexEdALsHLhkiCPN3yp5L9WEdFhWSoewe4SzbBT96d6RHEhK4h8auLUaqN2Wv59TOeaF2lWnCoqfCV/x8xvk7g59oTzm9Nb6YN035AWOhs/u7wYce5JlRcjEo5XHthnS8yqXyfB4jlLgp95YDAO3UeGnpsmL5bbYQoQBP8qPj69fKihPEJSCGywxG3TJGJYag+Zqs6SFwbFPybwTFWb2FxecORhcD114zmM8t5Pk3fkIQTOjAYu1lTk4HpenSFtVdB9btCkiMdHDJxTt88GudiaYt24dybZ0Oi3KGrQVib4rZHAQQkOLdTnXwBUtNKFFN81UlxBHFD4vgpqVvgqagNVilMKqUuCTFdQpiRkGq9nqn4TXdMEfxW/MvD/O4E7gPxlLIlzSSYR+xEZN4vjhss4rJknISz8Ev4k/3Q5sf9gasE+4TroJXQJEzdeV6D9Q6DE56hbiqcSliIO8nIPMQrydnn9LESRG7ozkDLVce80vGr2Jr0+8t+ZHBs6YPbXvB+v+3PtLAikBsealEpwGRE2+8f99xJDJtpvl8uOHctOn8CFiOEtykJAJm2aJJkfIA+Ts8hZD4Bvw9SSMrNv33Ygggu4iEr5BL46U6FqLl6+iqyoiEmlumnkpeSUiroXWzXGvQ8nVSNIhydg8oirOI2V0tQhzT0Izl10ey/wVz3vyb82Um+5Nnxm7iWz4pot18aErbkTZlnwFCnI2TPveeIG6FAQc2VAJaT1VT0XjTMtao43hRODYyMrzRu3W+PD8HAV7/jd7nr2wbZvfUo84JUFGUhxToTP3dHMR27hWRg1eRzwS9BgqZ0odfaa9Gv9gckSNrMZNvYbtVnzbz9Oj1xAg2K8GvbFcan7XbodXODyiNfxwL54M02VzsDFFZ3oiE9s8R3PoDjnD2SRWengc73w/WYtQwIFlTHP8Areu6cPJHF5gSzRe9YRxsF94ue1WgNW1GoOizMJ1Cc0kX6Uv4P79AtXVBrKoSV5gIeZIZf4brncXRfAXGZGDP5OIJWS9uj+OkPuV1NBIr26ZU/xszsQKv6YjW9GhkfwRCqy7LqeLlHgPrjNK5YimIXrZB0CfUPQnTIIvQWJjnEs3oXKiUV4n34/ZGOfvHvZIgVNGdLm0UtX6tRqGKyOCN847kumTzw2g2HsRVfPFL/KPoKLtzeKH8oQ7qEeyLLUu8o0o51qYZp5NRbscWSmOCVnXEblmV4Yt3f5PaJ6MZdNWqo=
*/