/*!
@file
Forward declares `boost::hana::none_of`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_NONE_OF_HPP
#define BOOST_HANA_FWD_NONE_OF_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Returns whether none of the keys of the structure satisfy the
    //! `predicate`.
    //! @ingroup group-Searchable
    //!
    //! If the structure is not finite, `predicate` has to return a true-
    //! valued `Logical` after looking at a finite number of keys for this
    //! method to finish.
    //!
    //!
    //! @param xs
    //! The structure to search.
    //!
    //! @param predicate
    //! A function called as `predicate(k)`, where `k` is a key of the
    //! structure, and returning a `Logical`.
    //!
    //!
    //! Example
    //! -------
    //! @include example/none_of.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto none_of = [](auto&& xs, auto&& predicate) {
        return tag-dispatched;
    };
#else
    template <typename S, typename = void>
    struct none_of_impl : none_of_impl<S, when<true>> { };

    struct none_of_t {
        template <typename Xs, typename Pred>
        constexpr auto operator()(Xs&& xs, Pred&& pred) const;
    };

    constexpr none_of_t none_of{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_NONE_OF_HPP

/* none_of.hpp
JsT/MRPiQJoRMCr9sRVGBXq6Xaanc6Tpfe/soJ0jSxuqdOl+u0Od/vqt8e6HCnaHwKSi4SGBFiie12/N0aiu3qFK65sEUB3xLzQKanGasWRnKl57BLz2CHjtEfDaI+C1RwWGwKMCBnv0WQwB4Ze9Q6aBBiqwDKFRkWMIYgG/wLs1JipRa32OIew3MyI3tSHh82Vu8a3U38z4zfOl75VXK69KH+/VLL9kv64ov8TmK8of1Cy/JF4ryi/Rs1zfFxB2aYMFOewzyK3cM7lLyfUi7laRXWmU3pFHV6JRJPCicW23rpbgp2qvpwBo1y8Gngu3wMm78JybdXy8ol4etlm9RGi8O+vF01mBglp+mVJLBYqpogW1XDgtSMWmk+Z6zOkX2FEv+u8HhV3b/anHdn9y2O4n+P0Jfv/0Aj42fIffn+D3T0/gN3z6t/gxCsBkbM1d2sWqU/ap53u8VoWZ4zkzy61VB+MvnJp10Htbq0LIZ5YXOSMzjPh8DsqiVm1+E3HP5nYBt9FY5Y4DcYVGzJxiMQ/u9uHtHnz24dOGzwF8YLDBioePAf9gK05OdYFEIVcCFG2LYkP1jZvTd6i6AfxKtX3aqWpwYcl87Qtv6ltbVGl9YwuqF5haG5tWuRN+7mz/GWZwLcLgDjkBWmHY
*/