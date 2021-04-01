/*!
@file
Forward declares `boost::hana::replace_if`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_REPLACE_IF_HPP
#define BOOST_HANA_FWD_REPLACE_IF_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Replace all the elements of a structure satisfying a `predicate`
    //! with a fixed value.
    //! @ingroup group-Functor
    //!
    //!
    //! Signature
    //! ---------
    //! Given `F` a Functor and `Bool` a Logical, the signature is
    //! \f$
    //!     \mathtt{replace\_if} : F(T) \times (T \to Bool) \times T \to F(T)
    //! \f$
    //!
    //! @param xs
    //! The structure to replace elements of.
    //!
    //! @param predicate
    //! A function called as `predicate(x)` for element(s) `x` of the
    //! structure and returning a `Logical` representing whether `x`
    //! should be replaced by `value`.
    //!
    //! @param value
    //! A value by which every element `x` of the structure for which
    //! `predicate` returns a true-valued `Logical` is replaced.
    //!
    //!
    //! Example
    //! -------
    //! @include example/replace_if.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto replace_if = [](auto&& xs, auto&& predicate, auto&& value) {
        return tag-dispatched;
    };
#else
    template <typename Xs, typename = void>
    struct replace_if_impl : replace_if_impl<Xs, when<true>> { };

    struct replace_if_t {
        template <typename Xs, typename Pred, typename Value>
        constexpr auto operator()(Xs&& xs, Pred&& pred, Value&& value) const;
    };

    constexpr replace_if_t replace_if{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_REPLACE_IF_HPP

/* replace_if.hpp
alzlUE6cp938Aw+rFeuZ8N9cGUJpC0GVuOFSmthdVP+SqCNi4igwT+eWSW6IO2HuDutieDzsP4GMJdFWENYIhhE6y3Jkydj2m23e1Q7B0KwMTlQEBgxPSRyzFGMxLeVZF6bZHUqZxDT388U5aXDaXd3F05c/tCm59Tw8Zy7rcNzzmLWWqxRkT4VxWvwMpOcGhRB+MEAmBn+MCls4SFPy8E7M7Vs6bLNMHWIilO4scD8uulTNMpJvegaPoJD1CfdXlRfCGgPkPgdlViuLe2fRab8hmLyq4/vjM2PtH7aPhKh2HrON9bprcbH2hcuIrSefzZPWWaq2VpUq/DcjOmPcVx7JLpaN+1M2KrFLctUAXgxxYYSFRi3J1Kk2pM/PZmuZdP/i9IX6CmaIkAAyqPorl50mvlxqj/1OpAINCKRPqPggtZjKPzEGXnGLNnC/SBJR7rAQo7AsFHqzLYI6M7MJVb7IQz0te2cSrXAi44WkeLSOyA9VPAVp6jE3LwwkIgoyplesqBibC19n57FLCWx0NPkHDPUmKK7ov8bzc/7sarGPB94amNe/+Jfwkw==
*/