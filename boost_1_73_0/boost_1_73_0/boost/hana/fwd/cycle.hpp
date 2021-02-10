/*!
@file
Forward declares `boost::hana::cycle`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_CYCLE_HPP
#define BOOST_HANA_FWD_CYCLE_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Combine a monadic structure with itself `n` times.
    //! @ingroup group-MonadPlus
    //!
    //! Given a monadic structure `xs` and a non-negative number `n`,
    //! `cycle` returns a new monadic structure which is the result of
    //! combining `xs` with itself `n` times using the `concat` operation.
    //! In other words,
    //! @code
    //!     cycle(xs, n) == concat(xs, concat(xs, ... concat(xs, xs)))
    //!                                       // ^^^^^ n times total
    //! @endcode
    //!
    //! Also note that since `concat` is required to be associative, we
    //! could also have written
    //! @code
    //!     cycle(xs, n) == concat(concat(... concat(xs, xs), xs), xs)
    //!                               // ^^^^^ n times total
    //! @endcode
    //!
    //! If `n` is zero, then the identity of `concat`, `empty`, is returned.
    //! In the case of sequences, this boils down to returning a sequence
    //! containing `n` copies of itself; for other models it might differ.
    //!
    //!
    //! Signature
    //! ---------
    //! Given an `IntegralConstant` `C` and a `MonadPlus` `M`, the signature is
    //! @f$ \mathrm{cycle} : M(T) \times C \to M(T) @f$.
    //!
    //! @param xs
    //! A monadic structure to combine with itself a certain number of times.
    //!
    //! @param n
    //! A non-negative `IntegralConstant` representing the number of times to
    //! combine the monadic structure with itself. If `n` is zero, `cycle`
    //! returns `empty`.
    //!
    //!
    //! Example
    //! -------
    //! @include example/cycle.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto cycle = [](auto&& xs, auto const& n) {
        return tag-dispatched;
    };
#else
    template <typename M, typename = void>
    struct cycle_impl : cycle_impl<M, when<true>> { };

    struct cycle_t {
        template <typename Xs, typename N>
        constexpr auto operator()(Xs&& xs, N const& n) const;
    };

    constexpr cycle_t cycle{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_CYCLE_HPP

/* cycle.hpp
JowtRSKjRYwwcHh3HofCvXb9uXsJA7mJmCXJMj7c3fVW0Ryw352EXrzr6ek3Z8kinclHQGLh3olwmYgkFKtYNgS2bIhFOPGn+BsIAg+Xq8u5H88aGTYwVDDZDSMRy/kcYUE/X8aMthQjRZ4GNhNLwNhP8FccBjEOdTMLF1ZDoCNCma6iAAYCOkCjSQhkbohVMJERNaaZ6yEUTYnAlUuT4TsRYQDIiK32SPRGW+LSjf24Id73xm8GF2Pxvj0ctvvjj2JwItr9jwjsba9/DEvvw2CRkLfLSMYweCT8xXLuy4ka8/v97D55skuzGIWryFOcM4UB3flc3ITz6Wh0JuKl9Pyp7wG9J/wWaTE+G+3i27l7J6Om6If0GmHB1MV1Mo+bnmY3eQ3T8RAmdIYlRwDw73QVeMhjsZoXYPMffuDNVzDMFvKSE8tktWzOtvDFdCKn4mLUdd4Pzk5gZHgGT/xACvXAGZyPe4P+yOmd9gfDrjP6OMrg/YyzieP5LqASI1/PXpW8BK4kfOAlEEaMgSEkcgCOcjMDTk9RZklIheAGxWl+hwseQluY5mWYzIBvDp+AntghisHEo+exSMcQVzKQkYt8cnmnqZ01j+8Wl+E8Jgw81QiJAiC8MJj6V6tIYusRzIIoekc4Ldzos5wA
*/