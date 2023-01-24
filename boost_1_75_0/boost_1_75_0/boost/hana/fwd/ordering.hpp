/*!
@file
Forward declares `boost::hana::ordering`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_ORDERING_HPP
#define BOOST_HANA_FWD_ORDERING_HPP

#include <boost/hana/config.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Returns a function performing `less` after applying a transformation
    //! to both arguments.
    //! @ingroup group-Orderable
    //!
    //! `ordering` creates a total order based on the result of applying a
    //! function to some objects, which is especially useful in conjunction
    //! with algorithms that accept a custom predicate that must represent
    //! a total order.
    //!
    //! Specifically, `ordering` is such that
    //! @code
    //!     ordering(f) == less ^on^ f
    //! @endcode
    //! or, equivalently,
    //! @code
    //!     ordering(f)(x, y) == less(f(x), f(y))
    //! @endcode
    //!
    //! @note
    //! This is not a tag-dispatched method (hence it can't be customized),
    //! but just a convenience function provided with the `Orderable` concept.
    //!
    //!
    //! Signature
    //! ---------
    //! Given a Logical `Bool` and an Orderable `B`, the signature is
    //! @f$ \mathrm{ordering} : (A \to B) \to (A \times A \to Bool) @f$.
    //!
    //!
    //! Example
    //! -------
    //! @include example/ordering.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto ordering = [](auto&& f) {
        return [perfect-capture](auto&& x, auto&& y) -> decltype(auto) {
            return less(f(forwarded(x)), f(forwarded(y)));
        };
    };
#else
    struct ordering_t {
        template <typename F>
        constexpr auto operator()(F&& f) const;
    };

    constexpr ordering_t ordering{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_ORDERING_HPP

/* ordering.hpp
sOjerpjzdzeXMTTF+keg9I0EfkGtw3X7LJSIuXdgHJeHXhpb/Cz8y6U0SpoJEWIbWRCm681Q9bt4D6b+4ViVDLCgksSTl8uZf7HJ6EeYnecDNCL/TnI91YsTx7ydcH/MUenx8GqYxUayKdMrfVlI251Lf4wghGwACGy0wF3jBaKeSHxn8mvDmncAEsvPykiBjZ+JXulfCdaUZ+UoY20gct8h68Bbj2Ps70ufe6MadJ95ROVjo/RJ/UJz8Hhzp/xa83NnJFo5dsx8InNKxPIsvw7ITCkHvK0Qm47Wd7dd+qYOC4bhrcnb8FV0yfwtqoPuCJEfIJEFJwV/j+rJOch/j+qreseXJ4JJ/tFtyi9YdxjPMs/0flGwCBgxr8EdBxHG1k31U0UxKMQWdIL8zOepn3cJ7J3rnY26M3h+FBF7xF8pQtcsl1pv3nHBKvIPh6F3+FO6fB93L3Z5LgKcyHkreSmZq65ZiSYjBNP7zL33rCh4C2Pl2IW8WN6a0dN9Fp6aaDNSkANz+NyKnjYR5tRpNRVAPRWUVhOtcw56uHVLM/9W1aFTOg4dgky+IAYQuBbd6MUsFghS3SZvLp98m6PMdGrGmC53pj8f8YWEbMZcvXfLTHp0DQnyrVpdWSgxdPrqtDmRC/HTxPsZT8bFOJzDxIikOXfqpDWx+LTRqzakDvMEaGJEUdNyEh2Vg7e8w700ltDd6BfqUAFUtrk6
*/