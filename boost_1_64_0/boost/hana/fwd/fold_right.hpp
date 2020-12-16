/*!
@file
Forward declares `boost::hana::fold_right`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_FOLD_RIGHT_HPP
#define BOOST_HANA_FWD_FOLD_RIGHT_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Right-fold of a structure using a binary operation and an optional
    //! initial reduction state.
    //! @ingroup group-Foldable
    //!
    //! `fold_right` is a right-associative fold using a binary operation.
    //! Given a structure containing `x1, ..., xn`, a function `f` and
    //! an optional initial state, `fold_right` applies `f` as follows
    //! @code
    //!     f(x1, f(x2, f(x3, f(x4, ... f(xn-1, xn) ... )))) // without state
    //!     f(x1, f(x2, f(x3, f(x4, ... f(xn, state) ... )))) // with state
    //! @endcode
    //!
    //! @note
    //! It is worth noting that the order in which the binary function should
    //! expect its arguments is reversed from `fold_left`.
    //!
    //! When the structure is empty, two things may arise. If an initial
    //! state was provided, it is returned as-is. Otherwise, if the no-state
    //! version of the function was used, an error is triggered. When the
    //! stucture contains a single element and the no-state version of the
    //! function was used, that single element is returned as is.
    //!
    //!
    //! Signature
    //! ---------
    //! Given a `Foldable` `F` and an optional initial state of tag `S`,
    //! the signatures for `fold_right` are
    //! \f[
    //!     \mathtt{fold\_right} : F(T) \times S \times (T \times S \to S) \to S
    //! \f]
    //!
    //! for the variant with an initial state, and
    //! \f[
    //!     \mathtt{fold\_right} : F(T) \times (T \times T \to T) \to T
    //! \f]
    //!
    //! for the variant without an initial state.
    //!
    //! @param xs
    //! The structure to fold.
    //!
    //! @param state
    //! The initial value used for folding.
    //!
    //! @param f
    //! A binary function called as `f(x, state)`, where `state` is the
    //! result accumulated so far and `x` is an element in the structure.
    //! For right folds without an initial state, the function is called as
    //! `f(x1, x2)`, where `x1` and `x2` are elements of the structure.
    //!
    //!
    //! Example
    //! -------
    //! @include example/fold_right.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto fold_right = [](auto&& xs[, auto&& state], auto&& f) -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename T, typename = void>
    struct fold_right_impl : fold_right_impl<T, when<true>> { };

    struct fold_right_t {
        template <typename Xs, typename State, typename F>
        constexpr decltype(auto) operator()(Xs&& xs, State&& state, F&& f) const;

        template <typename Xs, typename F>
        constexpr decltype(auto) operator()(Xs&& xs, F&& f) const;
    };

    constexpr fold_right_t fold_right{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_FOLD_RIGHT_HPP

/* fold_right.hpp
pfVT/y9y/a+sHrD+bTSrIkntkecQMW2aPBzs5MnydBA5+Bw43cavMqt4CZcx/ip5uVW8bAMynNm+hVCt4ZVX54KYG5oG8Poa4tM+0/I8fTRnGgIzpRu08YmucCj75ogrGlWY8OjqG0UYM2xWoe1Dy+KMIkc6q6xxdx5DQc5uBSdRSR63qNm5RHarkrLbNi0hO5c1/mr1JeolSosoI5s9R9OmJ2Jl82sG03o1mi9ykSS9kNVciFcU8mElxgZZT14CNKSM4HHSSzOZKAp2F2lwnGfgzZWNY0L98Bjgp7IBO99FN1n9Q4032eRyW0k5EEV19BpOTQiC5wuhe1+frqN7+uUWzl+usapG2yEjD4YlS6h5lMhfVcAr32SDUoHJ5Y7lKXKNI/95GeFkBlaemWl+moSc6iMfqb0TEtubivYal1nRrMHpY9Sep8uT2oNFEVplMYi2EMbmi2GpvP5um6JhqYSOWL3yKkdJZ2A4IanrxuhIKsJqbHKveR+w0BeAkr7QaplQ0tlkkXvzD5Nwjtb0PeFB6zpg/dH1oUkp/mHo5gKrxsyp9vqgvG4faAt4o5v4aYI+wL3kZSdzey+VcTVxXTTbq1x+vkYTGEpN+NVo9XoLWjAofwnbQxVXwQEVSw8Cy6Mty4pRmM3SfP6KfqqyAlXZBS9xuWGuWpWeZqgD+/V5elXofDRBVGVQ3tOp7P97T4n/JGROBQcKtL8p9zD/6SeC/1SRbiZU3oaXV+c/+Zn/lKmsO1/lP2WGG1T+ExDqFGjiNzGzbVO/jCiPSWdE2YCnhtN0po6RPGy6B3NFiFCxSghMxwWY7S12ZEOBay/ujwHSgIqeAgNEXNlev8MoqhRuIOLI1ahEa9BGltMqaEtjrtVOZo8NuwRnaYPXU6fyxm6cmMAbg1YJiny3lsKtvDKeYXFcEy+R7tWCQbRStiGCtEXzqVPOvUJljMVzxSYSXeo5nIfwpovVo9KYdIZIyrFzeWHyMUgH0PH99BdBlUzkkzFHzBHjiDmYIxZj/TjUqM0JnK+qHHCfGnJO4nzJDfF8pHCV5sLo8qC3Y7X6QBn0Kt/jme9ABwtPI3neITzprqiZ3A+NpU4mkuC9jMbdXMY0e98wr7KT6U4Fcew7eQ4xrtCSJP5UfZrZsXKI2fF5PAbMXhOezfg+hOdSq9mxHuEX4LsGz9fxPUPEi+dPpZjNqRn/gB8uMhAzKvk3dJBk/zNsq0R4L71qUBeHL7d/FpapOkY8S2/ZHZ6TW093pHCANhpZfRIZ48MXAuBfP7h8XzL/ypVD3BAgcymBIXEskRxlTQbDHrU+mJ5wfwz+FQmyD/OTYBVRVji+XJOLb1v48pzIwPyuadIboo+E6ozFoBpJ3YY4IOOFDwHsZ0Yh5C0txKNMY/pS3kCViu96ZYsrxqISjEGVURVL7JH20jFupPdk/tQij/KD0iT+1JGSwfhTe/vF33NCMHV9PuMBPCA1sQHpHho/IMi3H/wcudAVC+ZFubAL2SsVjSdFhzTsdguGmx10xz2QLgh8PqPOKPqksX9GEeB+MqNoTiZJzBEgs9GoPFSmM4q+aqJMmEZI1r1BAxWMoi6SP/Pxrvbk8BjZ/vza2PcXLhDfyqhp8byiichGZxR10SGMWCR/+STTWhk5E8kvmaJmtTxHuTWXclBZKCzPHvC4lcJzOAbd0/+cUeyw72azF6pJNT4bvpR8XTr7iporNWbcRBtF/rtzND5INmVypVHjTYHjcaY3OrE2+lv13jCM+xhjLKv1QFa61sLDV8tTjo/CvuV0/imi2WtTGUVWjVH05BievF0zKY1fpLlDS/PCBN4WuwoocK0IvF0LfFQNtCNQCos5nsibums=
*/