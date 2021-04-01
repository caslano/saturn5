/*!
@file
Forward declares `boost::hana::adjust_if`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_ADJUST_IF_HPP
#define BOOST_HANA_FWD_ADJUST_IF_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Apply a function on all the elements of a structure satisfying a predicate.
    //! @ingroup group-Functor
    //!
    //! Given a Functor, a predicate `pred` and a function `f`, `adjust_if`
    //! will _adjust_ the elements of the Functor that satisfy the predicate
    //! with the function `f`. In other words, `adjust_if` will return a new
    //! Functor equal to the original one, except that the elements satisfying
    //! the predicate will be transformed with the given function. Elements
    //! for which the predicate is not satisfied are left untouched, and they
    //! are kept as-is in the resulting Functor.
    //!
    //!
    //! Signature
    //! ---------
    //! Given a `Functor` `F` and a `Logical` `Bool`, the signature is
    //! \f$
    //!     \mathtt{adjust\_if} : F(T) \times (T \to Bool) \times (T \to T) \to F(T)
    //! \f$
    //!
    //! @param xs
    //! The structure to adjust with `f`.
    //!
    //! @param pred
    //! A function called as `pred(x)` for each element of the Functor,
    //! and returning whether `f` should be applied on that element.
    //!
    //! @param f
    //! A function called as `f(x)` on the element(s) of the Functor that
    //! satisfy the predicate.
    //!
    //!
    //! Example
    //! -------
    //! @include example/adjust_if.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto adjust_if = [](auto&& xs, auto const& pred, auto const& f) {
        return tag-dispatched;
    };
#else
    template <typename Xs, typename = void>
    struct adjust_if_impl : adjust_if_impl<Xs, when<true>> { };

    struct adjust_if_t {
        template <typename Xs, typename Pred, typename F>
        constexpr auto operator()(Xs&& xs, Pred const& pred, F const& f) const;
    };

    constexpr adjust_if_t adjust_if{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_ADJUST_IF_HPP

/* adjust_if.hpp
BpDwN3aDvO+Xuz9vBJhlYf6rq5zmci9dgg8wUJKeXgGktcp4U3JmdLkI5HwFjx0HyFWVt6k10dR/1+DIO6rqbj32Z+R73BNfbYxOOE92/J1Xt6ayHDUAQzpB4h878f1jlF8c09sn5/J37Ju28lw+2Mlb07FObiTupBW76WYZxUduWKk8CJUQH7NLqvdYh/HIRel79rCayKE7QeWYA4JaeJA7k3d7yy/1tHl5IK21hPy9Pf1MGozHs0B06ihfVFv8hFwiJkajZ3jbXVXcuQ7EPPLk6wpqus3EcVk4SwYAZ+hvhwuZO7FyfE6zyeM7+/pv4udn60BOCdHdj1F+G7zFv7Jw7VUsxkHKVpA2jV0kc3kepR1T5y6+uNkBxTf8E2cPAwsPAloIWFkC6zmQg/1LdGcx6VNlDlh6JbQYBkcu6Mwb9VI2G0LczGvTKiQ2t9/LYBYZC4gisF8163FD9Ap1xLww3n3Jfotb0tlRMzQ7El6jOLh7zgiN3W7IwBT4NKXoyXJ3JlwG/IlqzQlckp1gV8CdfIwnMEMtH6OrTMIokPCZELRi5bpk67DZ4w==
*/