/*!
@file
Forward declares `boost::hana::filter`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_FILTER_HPP
#define BOOST_HANA_FWD_FILTER_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Filter a monadic structure using a custom predicate.
    //! @ingroup group-MonadPlus
    //!
    //! Given a monadic structure and a predicate, `filter` returns a new
    //! monadic structure containing only those elements that satisfy the
    //! predicate. This is a generalization of the usual `filter` function
    //! for sequences; it works for any MonadPlus. Intuitively, `filter` is
    //! somewhat equivalent to:
    //! @code
    //!     filter(xs, pred) == flatten(transform(xs, [](auto x) {
    //!         return pred(x) ? lift<Xs>(x) : empty<Xs>();
    //!     })
    //! @endcode
    //! In other words, we basically turn a monadic structure containing
    //! `[x1, ..., xn]` into a monadic structure containing
    //! @code
    //!     [
    //!         pred(x1) ? [x1] : [],
    //!         pred(x2) ? [x2] : [],
    //!         ...
    //!         pred(xn) ? [xn] : []
    //!     ]
    //! @endcode
    //! and we then `flatten` that.
    //!
    //!
    //! Signature
    //! ---------
    //! Given a `MonadPlus` `M` and an `IntegralConstant` `Bool` holding a
    //! value of type `bool`, the signature is
    //! @f$ \mathtt{filter} : M(T) \times (T \to \mathtt{Bool}) \to M(T) @f$.
    //!
    //! @param xs
    //! The monadic structure to filter.
    //!
    //! @param pred
    //! A function called as `pred(x)` for each element `x` in the monadic
    //! structure and returning whether that element should be __kept__ in
    //! the resulting structure. In the current version of the library, the
    //! predicate has to return an `IntegralConstant` holding a value
    //! convertible to a `bool`.
    //!
    //!
    //! Example
    //! -------
    //! @include example/filter.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto filter = [](auto&& xs, auto&& pred) {
        return tag-dispatched;
    };
#else
    template <typename M, typename = void>
    struct filter_impl : filter_impl<M, when<true>> { };

    struct filter_t {
        template <typename Xs, typename Pred>
        constexpr auto operator()(Xs&& xs, Pred&& pred) const;
    };

    constexpr filter_t filter{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_FILTER_HPP

/* filter.hpp
UOWov7BmPeRLizHQoZLLo9IBcTYl42X8/A3jqa70zcR694HHpRWp8dgNkevY0FS41xM1TNovrcOMX839Bhrd4l9imSkw4lxtJ1fd7smXse4uQ/yaKHXjCuGvYs9D3oguxpIPPV2st93pTihE2NpvmtaMeZpvMhtl7QgVBeht9upr+leu3JbD++xrZrPnD5Lc4uAV0msiY5yy1kebY+JMKr1Vx6rob4VYJvrDFSARuUHselyWiz6yQkCdjiYnXF9Kp7aN6O4fHnVbfbFXNik/+8J5V1BlhvriUXUIj05YhUuwS+p+PKr6v5UefQn8levT19IjFPqWdz63DS45X/iSA6nPM2zzt0DxPTkaE7wdb7FM1FfUCTrwTO6Odl/UMaYUCbxfg8/0uQSKD07pc+jIzjWqy5fI1Pg1eHisgU+gaRh0PbeL5wQgZp1O6J7nkE8o6ou2s2hqjYXe38xCowI1GbxYJoQ/jzTSxs+32etKQBuZ7nxxqeGGIA9HcindRK3uCszpnL9BKmNrPuGGwt7MDo89oMogPWS7Zr0OvodHlUOL1dMGmNkuuKj8GqSjtPUmJ5g3PcNMLJ1z97+aAX9Oz3I4MpQoG+EqSm/FZOQXLp7jUrpq023jvaNNa20Ki2cIz6P2IgoM/vjEkPFj
*/