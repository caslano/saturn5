/*!
@file
Defines a replacement for `std::decay`, which is sometimes too slow at
compile-time.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_DECAY_HPP
#define BOOST_HANA_DETAIL_DECAY_HPP

#include <boost/hana/config.hpp>

#include <type_traits>


BOOST_HANA_NAMESPACE_BEGIN namespace detail {
    //! @ingroup group-details
    //! Equivalent to `std::decay`, except faster.
    //!
    //! `std::decay` in libc++ is implemented in a suboptimal way. Since
    //! this is used literally everywhere by the `make<...>` functions, it
    //! is very important to keep this as efficient as possible.
    //!
    //! @note
    //! `std::decay` is still being used in some places in the library.
    //! Indeed, this is a peephole optimization and it would not be wise
    //! to clutter the code with our own implementation of `std::decay`,
    //! except when this actually makes a difference in compile-times.
    template <typename T, typename U = typename std::remove_reference<T>::type>
    struct decay {
        using type = typename std::remove_cv<U>::type;
    };

    template <typename T, typename U>
    struct decay<T, U[]> { using type = U*; };
    template <typename T, typename U, std::size_t N>
    struct decay<T, U[N]> { using type = U*; };

    template <typename T, typename R, typename ...A>
    struct decay<T, R(A...)> { using type = R(*)(A...); };
    template <typename T, typename R, typename ...A>
    struct decay<T, R(A..., ...)> { using type = R(*)(A..., ...); };
} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_DECAY_HPP

/* decay.hpp
KmBVsBpYHawB1gRrgXkeaW8dYF4wH5gfLAAWBAuBhcEiYFGwGFgcLAGWBEuBpcEyYFmwnJiZh4Mdy6u4kx0rgBXBSmBlsApYFawGVgdrqLoc7lhTxY1wrKXijnLM8+h/cSc51iFm4o50zKvijnPMB+YHC4AFwUJgYbAIWBQsBhYHS4AlwVJgabAMWBYsB5YHK4AVwUpgZbAKWBWsBlYHa4A1wVpgnsfaWweYF8wH5gcLgAXBQmBhsAhYFCwGFgdLgCXBUmBpsAxYFiwHlgcrgBXBSmBlsApYFawGVgdrgDXBWu1NDg/zB+YF84H5wQJgQbAQWBgsAhYFi4HFwRJgSbAUWBosA5YFy4HlwQpgRbASWBmsAlYFq4HVwRpgTbAWmOdxmD8wL5gPzA8WAAuChcDCYBGwKFgMLA6WAEuCpcDSYBmwLFgOLA9WACuClcDKYBWwKlgNrA7WAGuCtcA8T8D8gXnBfGB+sABYECwEFgaLgEXBYmBxsARYEiwFlgbLgGXBcmB5sAJYEawEVgargFXBamB1sAZYE6wF5nkS5g/MC+YD84MFwIJgIbAwWAQsChYDi4MlwJJgKbA0WAYsC5YDy4MVwIpgJbAyWAWsClYDq4M1wJpgLTDPVJg/MC+YD8wPFgALgoXAwmARsChYDCwOlgBLgqXA0mAZsCxYDiwPVgArgpXAymAVsCpYDawO1gBrgrXAPNNg/sC8YD4wP1gALAgWAguDRcCiYDGwOFgCLAmWAkuDZcCyYDmwPFgBrAhWAiuDVcCqYDWwOlgDrAnWAvM8BfMH5gXzgfnBAmBBsBBYGCwCFgWLgcXBEmBJsBRYGiwDlgXLgeXBCmBFsBJYGawCVgWrgdXBGmBNsBaY52mYPzAvmA/MDxYAC4KFwMJgEbAoWAwsDpYAS4KlwNJgGbAsWA4sD1YAK4KVwMpgFbAqWA2sDtYAa4K12pscEOYPzAvmA/ODBcCCYCGwMFgELAoWA4uDJcCSYCmwNFgGLAuWA8uDFcCKYCWwMlgFrApWA6uDNcCaYC0wzzMwf2BeMB+YHywAFgQLgYXBImBRsBhYHCwBlgRLgaXBMmBZsBxYHqwAVgQrgZXBKmBVsBpYHawB1gRrgXmehfkD84L5wPxgAbAgWAgsDBYBi4LFwOJgCbAkWAosDZYBy4LlwPJgBbAiWAmsDFYBq4LVwOpgDbAmWAvM8xzMH5gXzAfmBwuABcFCYGGwCFgULAYWB0uAJcFSYGmwDFgWLAeWByuAFcFKYGWwClgVrAZWB2uANcFaYJ7nYf7AvGA+MD9YACwIFgILg0XAomAxsDhYAiwJlgJLg2XAsmA5sDxYAawIVgIrg1XAqmA1sDpYA6wJ1gLzvADzB+YF84H5wQJgQbAQWBgsAhYFi4HFwRJgSbAUWBosA5YFy4HlwQpgRbASWBmsAlYFq4HVwRpgTbAWmOdFmD8wL5gPzA8WAAuChcDCYBGwKFgMLA6WAEuCpcDSYBmwLFgOLA9WACuClcDKYBWwKlgNrA7WAGuCtcA8L8H8gXnBfGB+sABYECwEFgaLgEXBYmBxsARYEiwFlgbLgGXBcmB5sAJYEawEVgargFXBamB1sAZYE6zV3uQQMH9gXjAfmB8sABYEC4GFwSJgUbAYWBwsAZYES4GlwTJgWbAcWB6sAFYEK4GVwSpgVbAaWB2sAdYEa4F5Xob5A/OC+cD8YAGwIFgILAwWAYuCxcDiYAmwJFgKLA2WAcuC5cDyYAWwIlgJrAxWAauC1cDqYA2wJlgLzPMKzB+YF8wH5gcLgAXBQmBhsAhYFCwGFgdLgCXBUmBpsAxYFiwHlgcrgBXBSmBlsApYFawGVgdrgDU=
*/