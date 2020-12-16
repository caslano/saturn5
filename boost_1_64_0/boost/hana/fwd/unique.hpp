/*!
@file
Forward declares `boost::hana::unique`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_UNIQUE_HPP
#define BOOST_HANA_FWD_UNIQUE_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>
#include <boost/hana/detail/nested_by_fwd.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Removes all consecutive duplicate elements from a Sequence.
    //! @ingroup group-Sequence
    //!
    //! Given a `Sequence` and an optional binary predicate, `unique` returns
    //! a new sequence containing only the first element of every subrange
    //! of the original sequence whose elements are all equal. In other words,
    //! it turns a sequence of the form `[a, a, b, c, c, c, d, d, d, a]` into
    //! a sequence `[a, b, c, d, a]`. The equality of two elements is
    //! determined by the provided `predicate`, or by `equal` if no
    //! `predicate` is provided.
    //!
    //!
    //! Signature
    //! ---------
    //! Given a `Sequence` `S(T)`, a `Logical` `Bool` and a binary predicate
    //! \f$ T \times T \to Bool \f$, `unique` has the following signature:
    //! \f[
    //!     \mathtt{unique} : S(T) \times (T \times T \to Bool) \to S(T)
    //! \f]
    //!
    //! @param xs
    //! The sequence from which to remove consecutive duplicates.
    //!
    //! @param predicate
    //! A function called as `predicate(x, y)`, where `x` and `y` are adjacent
    //! elements of the sequence, and returning a `Logical` representing
    //! whether `x` and `y` should be considered equal. `predicate` should
    //! define an [equivalence relation][1] over the elements of the sequence.
    //! In the current implementation of the library, `predicate` has to
    //! return a compile-time `Logical`. This parameter is optional; it
    //! defaults to `equal` if it is not provided, which then requires the
    //! elements of the sequence to be compile-time `Comparable`.
    //!
    //!
    //! Syntactic sugar (`unique.by`)
    //! -----------------------------
    //! `unique` can be called in an alternate way, which provides a nice
    //! syntax, especially in conjunction with the `comparing` combinator:
    //! @code
    //!     unique.by(predicate, xs) == unique(xs, predicate)
    //!     unique.by(predicate) == unique(-, predicate)
    //! @endcode
    //!
    //! where `unique(-, predicate)` denotes the partial application of
    //! `unique` to `predicate`.
    //!
    //!
    //! Example
    //! -------
    //! @include example/unique.cpp
    //!
    //! [1]: http://en.wikipedia.org/wiki/Equivalence_relation#Definition
#if defined(BOOST_HANA_DOXYGEN_INVOKED)
    constexpr auto unique = [](auto&& xs[, auto&& predicate]) {
        return tag-dispatched;
    };
#else
    template <typename S, typename = void>
    struct unique_impl : unique_impl<S, when<true>> { };

    struct unique_t : detail::nested_by<unique_t> {
        template <typename Xs>
        constexpr auto operator()(Xs&& xs) const;

        template <typename Xs, typename Predicate>
        constexpr auto operator()(Xs&& xs, Predicate&& predicate) const;
    };

    constexpr unique_t unique{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_UNIQUE_HPP

/* unique.hpp
9YTMpfAHaG8wjOQPEKCdf7T2+/Z13VBqQP9iIAt6uj2H95EOEWP7kNCBdag/phe/ZgElQuIx4GNIbOhNcSSPGC2ehDtEtYoH4cpYOu9HVTwtJF+Jv7C4uB/XS9GEhssGUieXMQPwR5961He4lDEUS8pP6XhFVxj7Q8a5v41XvIBtXy4VwPpK4skxbXuI7gKgl4bR1sw/Cp55o7RnzP4oV/2RHMdwhcQ8ahnKRwFh8cDArM7Bm8F9KbZSf7aofk2Tbde9+rOJd+0Vu+6hvoc8PMgSiIKTYCiZ3smjyVo6amcsl4VLzZdRazsBpeK1/PS5B8AC73wA+AbUo4Z02JZR0wFoF40E0U2not+XbkW9z9n36Zsyq7XvalOvVzxUxfhm30nc/KgWTOYPqAQPj9yKQzNa9jpzOQ69UbWM+X9Rnxn83zOND/on+dEUugmP/NI2ySUu7MbdUoCVqZeYSH20Rd+FLX1OLW8Ai+oxifJD7mvrw8woPhYmvn+DF//rQqzBl8JLxSOGKyDu8zIqwc1oTs+M0WKbx+qJwFNmcV9Ms37zlBTs/kO488NAaU4MTp4x/ddMe5k3myifOituGkCOXJpXmTsDTjOEo8IhZJeTR+2oENcFcYgoDYmlw00APqc0XJQ4Nx36DkJZr4H3hyHRUmRAEZ8m1gFN9PV8VzF1CRmEtccLBqfcWL5aY/FBYogLrPxMOcPO0W6XM2zoaLnKXUreM2SkXUV2kZHNPw0JNyhTy5YwvblBNZfygVEuwRfI2BjRo62ltFfH6PhiveDyhIJQKS9US+LhLPNkMhIRSyZL5s6btYMMi0t70T5gQz/F4zln1H4f9/38U+8vigsO4wddxRz+lgoNX31yHrTAl24A+7Ww1BIjnks9NFkthpIYcl6pGMjfctG7grvp658j5fro+eQPJ8gS/jJBlvCqlOIif8fpX5os0zdOlulXT+b0jRX5zG9WFMhPofwUy0+J/IxO4YeS9wcPK/6m5udRPfUT1OavEz/6Bdymau9WwbEmTAMC4Hoz5HW9Emry+bq6AyAvAEjtf6n6z/r2+Yn6gVhCBhJF7hSkQh/trYq4JjuaarhRRbuXzEUDKIflJNn6VkmXv+3rm6p/cfeS2r6u3KxwNc2LaM7yhfkRinkclKSKHttq7RTLT7TawW4/RGve5T86xKMlyNUg593VJelXMJnrJKiPLVGT6G96brteePBQ1QsbyNsfTaOcAW7n8QaNiN2XnROxF5o5ryTv+5XkdahO+XpkPIgfJrETPBxhCMHfC1iCR3PGKxyxy6evvYjyAFOC4hIVFetP81+GlwfFT8zwTsxWHOxj1KRPjjd5xfHHcduq2uZR72Op5zKPF2+6SaKrt2ALcqRmt8ohokevbpbj8+kIHp+IGNpbLswNpM8O+WpRkJahE7sjuyBAt8eGkXn85WVYNuaWh8Q5nJH7ICTCbs78KLUE2FL+xoylu+m57cu6czh0dA81Sv+mL4JKeiT8/EC12MZfp9iCrz7ZgbfFJT1yZtOj68toXjjFlfx1iUvLvhk9coiQUcIPjBImlB2AHiH9uIky/fETZfpj8GV65LEwTAeoz8XYhEJS8x0iWNaW3qDM1HynGFlm0huUnprvEkPNkNfpVk+l56AmP+EvhGBzXI2lDJhYfHiacjR0mN4FXCIZ+sgF2L3NZvziV3XvKFUAnBoh/yqUJOepU1xWqubpiAj5VyBOHIXjwSD1zWwz1hch/0IJA/qKoFjNgwgOsUH7iYmw47XbJMKWFSuC8o3wyJwf6GueH8we/8ylmhDQLjPrimq/k3W9WmQe1DaIc48C9NTxy/umM11lZjpRZbolIxN1lg9ToR9GNiw=
*/