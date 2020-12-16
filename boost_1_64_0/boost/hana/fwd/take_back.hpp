/*!
@file
Forward declares `boost::hana::take_back`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_TAKE_BACK_HPP
#define BOOST_HANA_FWD_TAKE_BACK_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>

#include <cstddef>


BOOST_HANA_NAMESPACE_BEGIN
    //! Returns the last `n` elements of a sequence, or the whole sequence
    //! if the sequence has less than `n` elements.
    //! @ingroup group-Sequence
    //!
    //! Given a `Sequence` `xs` and an `IntegralConstant` `n`, `take_back(xs, n)`
    //! is a new sequence containing the last `n` elements of `xs`, in the
    //! same order. If `length(xs) <= n`, the whole sequence is returned and
    //! no error is triggered.
    //!
    //!
    //! @param xs
    //! The sequence to take the elements from.
    //!
    //! @param n
    //! A non-negative `IntegralConstant` representing the number of elements
    //! to keep in the resulting sequence.
    //!
    //!
    //! Example
    //! -------
    //! @include example/take_back.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto take_back = [](auto&& xs, auto const& n) {
        return tag-dispatched;
    };
#else
    template <typename S, typename = void>
    struct take_back_impl : take_back_impl<S, when<true>> { };

    struct take_back_t {
        template <typename Xs, typename N>
        constexpr auto operator()(Xs&& xs, N const& n) const;
    };

    constexpr take_back_t take_back{};
#endif

    //! Equivalent to `take_back`; provided for convenience.
    //! @ingroup group-Sequence
    //!
    //!
    //! Example
    //! -------
    //! @include example/take_back_c.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    template <std::size_t n>
    constexpr auto take_back_c = [](auto&& xs) {
        return hana::take_back(forwarded(xs), hana::size_c<n>);
    };
#else
    template <std::size_t n>
    struct take_back_c_t;

    template <std::size_t n>
    constexpr take_back_c_t<n> take_back_c{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_TAKE_BACK_HPP

/* take_back.hpp
ISaqQnwTJz/ceGtJCWohDyI2d6fztqcL4m3v/T9v+//fJ/KT9qggDs0+RntU0v7HX/m8w1B6z92Kyfuee6QFkASr+GPDBkiGePcVXe3zetjOgMGoN5V22Pewt7/HMNnBlkEQ/OxHpV5YpEr44GSDHOexQY4lWyRfScbx4ldjuP31T3xoU0u6b+KVHeCgM8UL+MBqRnQqG0KSyv0WGry6HY4/A5+ww3GXhCBDwVqsX6/6hA4W1X3X7o39H8negH7+v12dL0Hpry53p1KfzI2TrSdaUM20ut+IPbKyv/IO63rx2lYwxdE0pGAK9CsJ8SIQ8LG3rmeHzd7azezOrX8hlXmc4ogb2WXTNos2uGj26afWpC3L/K1S1480BhfhW11Xywuw/TllQOV6Vl2LTA2I8zkyG9iGoZh47la2ucP6gSfBbo2BdZKWD8l0+ibkduCL0AFWvaA4Yshzhn0m0oBQzYIehzQLpriabAO899SyHlS1eB7/1ol1+DconsC/LEjpUI5beWl05XZ8Qs18zD/DfkQr24/I0+1HeMNxiJix6in7EXMu5UMKd/Il7ByxE+wcmc8NhtNEKzZKSED8fg99reLAG9xqYg9/HeIt/jrF6/x1iVfwDS1iOyY9dOrW1U255R3zyQR+hn5VzqdhD8KWbA/CcTh7EBFlVWHPXf3xOyOHsgeR1TsXs0syvdnJ9iD+ePcAexAlqA++73EumPuEPQi/9C6GZZt0YdvQn7AH4WV7EO3ol7htwfYgKpPDbgfPFP66Xsnf7upX9iASlBcqyqPUxB7Wljsj/n48bhiFcP8+YRQiKBM/s+970dk5fVbRuZMyzsGVUGkU4tJtHBZpcfCpKvi5GqeuElbd5q4eNZ7GcADXIMsQM2T8Mi6L81ldU7bkrv5P2zIEfsn3z3ABpoyo9ASEJnUxA9TL5+huMZabxDqF1Y8OTdHR7UPcu7X/EPYhbtnaf+z2IWppVWGdhjo53dLbHG5lIALQVjIX4WDBQVOGzJ2voyAYKPiSntflVmUZwq37TLFJehwiXdHzESxZU/+XoyR5fFy1qv/Q9iFkfR1q6rmioz9h/0EadOPu8yHtP6ykdUucsoUTYxXQP5IgvSOtG0SkAkfmILqwBMfZJkQU5LYDUoboSPixGPpr5o4wTMObhPYKny8fJtMj2o/Ia+nwsv2Igo39H8Z+xJdDq2mA5IhfvWTMFxE/zYPhcxhld5jYfkQx24/A14OvJz5WPAFiBxo4GM8RgmLcKsaEzwXME8kcDL5fPN1/DAYOBv0S9iN8nBZ0Ll6OYULKljnR8egx2I/wHsV+hLNzUP0exR6EaxCcPQh2DIKzBsGWo9irsCXZm3Cp9rkcsrmB9iZOBkrZm/CIcS8Pbo5TZSVhZyibw6s3B2vIoUWGPPWhWyRhL8F7GPsTX1NEOcXSlxK3ftzhSpX7PJn7DU/2DzRBEVAt/P7j/cdqguLY7Ue4P6Z9CNdR8Nkf2b6ExGd9TPsW1oPxx2CfQ9pnnPq83P8YfPhO7H9a7qUtCzHkYhacJMAndrkFyRiniFDvKrjaam99FEDB1TbIC9kBbvwPcAjP/eoy5dcJHEvJDBVfoE+ZpeBLLODjxL5E6HPvQGhBrPkpAPXnihx8ShkMQKFzNyS16hQZRLI8lGyVj+/uH2x7Z/zm2S5CeQag2t2psffN1DUp0SwxfaMhlvkjiQwRI352/GoXI4febogaF+mCQ/y5Sdvr1j8pnuMaRCGfKHZ80ia8Ez5amQVSo81/VaGq4cGJR6Q46TYlwhuHzv6F2w0T35TSaAVGzuWS02rBpX/Hoko/P43Ugc00iiKhfpLCQOCYLs7pob1BK7NaLto4TF8=
*/