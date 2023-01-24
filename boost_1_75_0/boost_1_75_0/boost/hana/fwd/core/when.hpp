/*!
@file
Forward declares `boost::hana::when` and `boost::hana::when_valid`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_CORE_WHEN_HPP
#define BOOST_HANA_FWD_CORE_WHEN_HPP

#include <boost/hana/config.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @ingroup group-core
    //! Enable a partial specialization only if a boolean condition is true.
    //!
    //! You might also want to take a look at `when_valid`, which provides
    //! similar functionality but enables a specialziation only when some
    //! expression is well-formed.
    //!
    //! > #### Rationale for using `when` instead of `std::enable_if`
    //! > `when` is used to control the priority of partial specializations
    //! > in a finer grained manner than what can be achieved with the usual
    //! > `typename Enable = void` and `std::enable_if` pattern. For example,
    //! > a partially specialized tag-dispatched method will have a higher
    //! > priority than an equivalent specialization that uses `when`. For
    //! > more details, see the tutorial section on [tag-dispatching][1].
    //!
    //!
    //! Example
    //! -------
    //! @include example/core/when.cpp
    //!
    //! [1]: @ref tutorial-core-tag_dispatching
    template <bool condition>
    struct when;

    namespace core_detail {
        template <typename ...>
        struct always_true { static constexpr bool value = true; };
    }

    //! @ingroup group-core
    //! Variant of `when` allowing specializations to be enabled only if an
    //! expression is well-formed.
    //!
    //! `when_valid<...>` is always equivalent to `when<true>`. However, when
    //! used inside a partial specialization, SFINAE will cause the partial
    //! specialization to be ignored when the expression is ill-formed.
    //!
    //!
    //! Example
    //! -------
    //! @include example/core/when_valid.cpp
    //!
    //!
    //! @bug
    //! Using `when_valid` seems to trigger ambiguous partial specializations
    //! on GCC.
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    template <typename ...>
    using when_valid = when<true>;
#else
    template <typename ...Dummy>
    using when_valid = when<
        core_detail::always_true<Dummy...>::value
    >;
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_CORE_WHEN_HPP

/* when.hpp
/uuLzfa/ozP3f9BZzsXR0sr9P+gcEqi9ki7+aHWX+h0B8S5Xfl6CQMr6A+6hLnf2sOTzXx8XOO5IIw/x5Jh4QG9fZGLzWxaNu63xdI26py7G0VtbK34MpEw2VH13Ps+oP09a8W5fLd/yWnBqZW9dEX4VfewTyA4PT3GEVxWqXT/nPV51P24HBG97XIs+zgbCt8fbH6jybizOUjM0UYJSpsvrWri/lSgjI6HfQ79yZ7fEpoYoFtZAAEWRbuROiRaMuyLHGwMUZhxfcAQxs3AosCm+LT6oRLxPgzNDbytaCZBkFCrJ0PcoS9r6lAatlvQmlWf8HpIDMO6s/Npr6i9lA4+T/cQx+lkcjUyrYrmrE0uWMW8Ud6doRqwVCFIY8O5oqDsw4dll9wYe9TLHDAP6OZO6Xf2NdU32iR59r7F/XaXffcWv45pLZT2Ck+7R/3riNIRIekWcm838/YxjAOc2k1WEW00ZOLzVAzLELnN4kMgJJEJMeFCGTM8KNqLgJWC+NcwEeNH9CUQxYwT+bS1+U2gWNR/VGJyXWhusKeqhrhkfAesRu8vxLX/LxCt/+CsOXnYGMDpxaFvFTARo7ONCTHNGCx9dvJF3p/xMTEAvIYQTuN/lEOWTN8V9FZNo2tAWVgbcBm4H0AZiyh4iJ3zVEFSRzwbsBmj3PPf4BhxCRwZIhz1yq5B8KW/899j2HM2YXRM3CildUF05GikE
*/