/*!
@file
Forward declares `boost::hana::for_each`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_FOR_EACH_HPP
#define BOOST_HANA_FWD_FOR_EACH_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Perform an action on each element of a foldable, discarding
    //! the result each time.
    //! @ingroup group-Foldable
    //!
    //! Iteration is done from left to right, i.e. in the same order as when
    //! using `fold_left`. If the structure is not finite, this method will
    //! not terminate.
    //!
    //!
    //! @param xs
    //! The structure to iterate over.
    //!
    //! @param f
    //! A function called as `f(x)` for each element `x` of the structure.
    //! The result of `f(x)`, whatever it is, is ignored.
    //!
    //!
    //! Example
    //! -------
    //! @include example/for_each.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto for_each = [](auto&& xs, auto&& f) -> void {
        tag-dispatched;
    };
#else
    template <typename T, typename = void>
    struct for_each_impl : for_each_impl<T, when<true>> { };

    struct for_each_t {
        template <typename Xs, typename F>
        constexpr void operator()(Xs&& xs, F&& f) const;
    };

    constexpr for_each_t for_each{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_FOR_EACH_HPP

/* for_each.hpp
Qr9FXoUipVZ9UTRxbks4t9IulkB9UAQm6my9vP/c0im3H+q5Xc+5jRa5dTcRr2psJiNYguuDkaJ5pfzZiK720vimTUQGW/USoR+Cizt4ab/F3Tua1JvqxS3l4n58KdsiKYp2p/zaKAZpmBgkDJHYZDv5NWuY2XE9nh14bHazYyrWyC128381T6eWUWPg8XJDrkDpQ6uBOmUxYp/Dzwr1jNF9Ya1ybfQYL65apUJANrdP1xLHEQ/oJ4DZxdoJwEsGe6IBt6qwvG9Z83DgsX0W/7mhvqF+bDzXdw+/mC6r+R0hJdU/9OLvXYBvAE2AGR4wkMh86V7lyHDOUWQTnpGL89XHIV3hp+mzfueyBH3WzPcp1lRZUwcVyw2MRbfD7dEOP7AKijgFBopjHw5g0Gh/HvrcFCtZNl9O9kEy0UO9r47sCf3ZJG6uKo9PF91G0mez6rjLfqN2unwocBZ0P55B6QiXLPAq8ydSbOpQ5cQEtTtXnetRerBYVPMidKD6nSOxY7zK3wSLDB0EGW9V43X1FF3jdQGrq4Vf8ZTToPP6w5zXNh0/FX2SDZNZy52NL5tUazpeMVWX56pKESX7bXYzH982ZPPxLQ+vWmWtVSiLorYbwjNyGFmf4YCevNVY6qwYj3a765CJjvLPIJR/NZTgcQR5tUP74rSaC7WHSANEanAo33TiGDVCDfEoXiq1z9P7mvJeJY8EbZvpOKS1GVIwk1PaygDVzH1avi6neOOQgooFhUs14neOOxzMwa7G5TgTylGV5WHW2Yenyp2YbC6HxrkR9Xji6DFWfSoozpaSvqBJ7mNBxzxlyK12QywvarxsDLvy5HJsegWaL9rY9tzsawFKe5daFqcq6OGOI6mqZUfzLp7CUqpQX81bJBl4jmZtE0qsw8202ezlnWHRnWw+HQiImjfPauK/J2aAsc2jwdXNGmRL2/rPgIRruHJU919bybrf21S57TDjad4eNi5up+rmH1q8k97hcsuHalQK6tR1ARAqvZ6qXy38bgnmzrqQUCC2wdWp4r5iPgVzl9tb1p/kT3oM2FYl6eqHUXKaERfwsb0LSICmbHuY7yL0gehAua8l2tWWEGhIDLwXgR7ljRSxtPtik9Q1SW1rkdZZm0djOXw6y+z4LJ5cfK/C+0U8C88yO7bimTAC4XgCeH4MdwRhT+LZDHcV3CPxfAnuB+A2IL0Dzyi4y/BQ3oYRhhH4GU0GsxlfST9LCl9lTx9qAAPKwhyozBEf5Zd11t7//+J/Qs5pA2E3pcqbk5NFKjRZilOXX/SP4SuSQ+losVns7nya08920kNaiSRrc0jIywx+0Ivnd/COP5Z2/Fza8UfG7fh22vHTxY5vPgVLIEIexG/FaZXjx+MU51EJo6iE7LgSbFRCGpcQeHqw7HG+q0BLlZKZ+vkuYGLejxWPwydBBPLMD7rh1kbJI8n4xRcmJOIX2NYKvJqlJ3k1xCfyYGI11FwAvWYuo7CeQcFs/4UciUBTB5aORGDZfRFddWBg19sVBxurClXguGtxBwPHqmIPg7ho1qwvjnRoIC8XbjfcbIsLUPGWnYZ1HePAhVr3lbsMWefOufYE9qRhTvTM3DwCa4vbEQCIyzaACRib5MMdb48xH5a9BSXPr7W1lU23w7aued/MbpPgC5TsWpsGdSo1RnjsklcUondTJq8ohqHFd5vTAnMme4vXzOTqL95N9ex9w2fhZpj3UEM6tIuvyb2xTfTGsMS9hyx95DUQljOn+DRjOXtPnb4Sv74KjyWur1NQPMZWnr4mjrQ6VlFoYKwiR5/L/ci3hoKYUqmhYIEheIWYEUuLF7sKqVt9lvj9L7lDV9CmnjtQpw5GsudKKd8=
*/