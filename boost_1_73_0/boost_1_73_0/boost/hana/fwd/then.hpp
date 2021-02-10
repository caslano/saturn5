/*!
@file
Forward declares `boost::hana::then`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_THEN_HPP
#define BOOST_HANA_FWD_THEN_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Sequentially compose two monadic actions, discarding any value
    //! produced by the first but not its effects.
    //! @ingroup group-Monad
    //!
    //!
    //! @param before
    //! The first `Monad` in the monadic composition chain. The result of
    //! this monad is ignored, but its effects are combined with that of the
    //! second monad.
    //!
    //! @param xs
    //! The second `Monad` in the monadic composition chain.
    //!
    //!
    //! Example
    //! -------
    //! @include example/then.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto then = [](auto&& before, auto&& xs) -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename M, typename = void>
    struct then_impl : then_impl<M, when<true>> { };

    struct then_t {
        template <typename Before, typename Xs>
        constexpr decltype(auto) operator()(Before&& before, Xs&& xs) const;
    };

    constexpr then_t then{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_THEN_HPP

/* then.hpp
TK+H02WqQIio1XqKLhhNDgWJaKszg7XB6Un/8B+D/UH/5P3Zfm+dTKRE/2HydwLV5ubLzR+PDBkcEj5/zx7SqZv8x8lp71htUP4Rbe7F5qa1KSWkm8wWo+pIh2daWJx4T8TGcGsUF8UgK4plOngBsoMib7CAuhgo/s/mFJ1azaKUGIV1U0MrSrpVVQzT17mgt2awe3UW01h9fLMi5Obl0PjgpnnRNMWSvkBEOn+SYpJ2VEKPSU1hiMrIm+eBQSGDKXJFxBpNtOo6RaWZmtcf6Hi7OkelocbFV6rYnbiCVNHYcHraAIR6Fkyp6T+JFCm/qJtFlZHYj/gcMnXSwCFjQA16SCd5RtfHdFlOt+ttcymhoVGndI3ehvee4w/pZCBDjunk+rCDuqYGIsugzmv/YV0jbz+u68hs6NM6A+QB53Vt4IEndh3gv5pTO5Q9wo7snJOpyxO7KBsbW0Gl2GNtjM2cy/3F5c6NwOGz5ybkQPlzCQRwBt2AtjOHDpR3WdOZRwdZH5Ubb9gE9Lk9FUpfZtxgdXRuvG1yx3ee3+4dsrO9s7OTjrgnPTwsF/yI705QT0nhFvOU0MERT6niN+Kd0jBstNMlIiaZS6SNF4xzyh5xhyinpPZal1xTwQ9PNZXqEKYpVQBvgtok9vFM
*/