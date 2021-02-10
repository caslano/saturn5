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
SuJ0uw0jUTXEzlnlmhkf+V5wC5/PpIK6RU5k1n9wtU6sq9FpUHogqXf2/khUX5/TsAgBawoKFQgZRX0tD5dvN8fPWcgyF+CsrGEZ+526nrgjR1ZV0WMqOKiWpq68J94p6tFWHuwOTEVv/rZU5AONGHbzlxy/5Xd9uU8x65+3VY2Cw17+Tgd9+VtwFvkfGQQWZag5NnySEKWdg1ac17vKKPtOA10wyNC/1NQyGAXm+KKRk+EM//pCfJb2XFjvwLZcyu5H7LwkvxKFkK+8T9sRTuuBPDkkS2TY2HgSlylcBsqFwdSMtVSfIl+wjZ62VUHnsHXjX7MvNaNVClOK+tOoQkg+ms9n8/alOCwu1cng5mvHdDDvtkmTlJ1V0AfHT2NYfztY4rsJoW9MBmL5LsQo4uyll+lEDMR8wjxf/vuXFYkTUVLMMeULhxsGCVNoxI+W9zo3ni/12yBSuV5UW6qbZVO2NMATjUeMCrp+lGS7nfmyYosTJRA1m9Eb2HQuq/ro5J0YA+35sja6Bo0jApF2RLHGmMKicOM5Wdtc63uGcHtncEg75tG6PLTTymCMiSUm40CbhZNYR59DcBMFNA7Is/BN72Eyf/nDwrd7OwoARkvxm3xan8PJ6Pfywixt+93ZGw1vBqJ/QrYHbwo4
*/