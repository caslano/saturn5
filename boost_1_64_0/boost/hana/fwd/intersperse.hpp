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
faLXGLk84WJELSchFLoGx2Xv6/SnYW6UP2hQ04UkYfS+599hjUc28luQjxZIxpUQ5WP5RkXR3ZarwrWAXRT/x3JrmPNx+cpCAuaQfvt4k9+Jkl/9bWyCpo5QQawfn02lLiLM4pxKX2nlVCpzUm/4NkYDK/L/QtMgcvj2lt9w0sF3xpp33hjrn4ffivn7VcHtsf5XeL/d0eZ5p5MHLODhgvPOj4sLRFt4USjExFTWGSYyWPVRSNu8OGu2A8f+wm9hfFHWteIG6W8L64s9RmtuXkhvrB9jUF4Uj26uD+nP1VqZNePRrDJIGusBFT2vWMxTakgBiXFgfZpBlBprXTvg8La58Rtf0j1xpaW2gjQCGvcHSifcwtV3WOPgKUw0y7q9n+vG7Vi/2/sp3on5epGvAWfb7lbaPKtoh3VaKqVN+XTbXKWsnzzDXD6YIZmnXDCkqApU3bEM/ukpdyllnXfUT2/lq6473oUSXjvOHMv2V3jVl66HiAvC8TINb4mOSfjXexXWe1e+ssz7eId3gvJVr1r1FVX+qPqqGtviLtvb+rhZctm+T76a3e/jhGc9WNmnedbPKDvYepITgJwF2jsUffe/2bsS8KiqKzyTeZCBjMwgA0SNEku00VAFhyo4sQbIhrIMHWbGliVdLE2jtS4TAZsE6ZjK63UQW22xrd2srUutWjes1mYykgRkC1hFUQi43TioEZVEiEz/c+57b8ImaPdlvi957527b+ece8655zLK0VLHhUPyDGCSQFAWDLfmQgGJCeoUUhktbx9hoqfTx6Mza4eGgaSD8qqwNQDvoV+INCTxnK4jYWol70t8TeJ9Wo1A7d6rzxXgY6Y3phd8BgfYppt5Yk+0TrQUoV6bXo2ttVPslEajWD7dj1R165EqEMOGwRZfYK89xbcbOtoR6A9jChdQTTpN5U50Xrm/u+4VaikjyfYP09HfzUaMVsQgf+UqViW1LdaWRtd6HOANkTl+VG+3PgC8FdrHDX+gqDeNqU19whMVNw2Qy5sUSWnYlBb1KrYRrezlvsBGbcxApjOl+Njf40iy5P8eR/6Zv5DYuWI2IXtXsUnSVkLUGRRzvGGoBVrLnrARPdPrO/T6nfLmsSahOaP6W1kZQlMHQlM92iA08a8thxhGTO31rZXvYf2IV+ckIQ1M13r0si75uTMU/dCgxbkoKO/4rImKC4GKa52K8txzkkF5+uZ1p5FXjR3x5BJEYTrUN0qjESVdmyvPgroHxi0q8356WU/qNHlTKREnfU4PEaHZaAAipmu9QfnzMou6lAG8eN9dDuDy7McJu6dOX7zvLDt/9qPPE2L7voB3jd7dvi2xfcPcP0/G8+YwVizrEk8zftTnyE07xGo91OS+ry1ebINp3rQ9MFGa+kri9Sx0Z7yiZHHahv10/QDpQOmiN3Vi9XqzTwPyz+cpSYCLEMaddqpqh2iNdTTFmkogYdDLdsrZS+AwYOorwB4hUostru+g/FrLfscXX0xtbS3bQG+iRw/dL8p26qFnWsseAgBRNtMDssrWshUoErl49bI1etkrcW2ZXnansLeWvUhwvf69WN0yogXrKZZNhF6BaUN9l57FbYxXpNGspb838b5OkezIRpStiV8EWegKfU5brKlXL3tKIO9Khkz9NUoD0L9ZzJGi7Kn5/fxlv75qxvipbUD1iasqkemhUP2cV8T6orZlwO8/QO4Gil+GV2D5H5hYfhlj+fa655G1/7n6XMxi4RAuimYg+Ofq3kKYXr8hlcdj3yMj4K8D8bI1AXnBYJNd9ot6V2yRCz6RGm3U8+BQ6xymCKgWCeNldyItWI9hZhp34w+o9fXviTk9sfo8oLugPIYVShr6nng=
*/