/*!
@file
Defines `boost::hana::all`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_ALL_HPP
#define BOOST_HANA_ALL_HPP

#include <boost/hana/fwd/all.hpp>

#include <boost/hana/all_of.hpp>
#include <boost/hana/concept/searchable.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/functional/id.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs>
    constexpr auto all_t::operator()(Xs&& xs) const {
        using S = typename hana::tag_of<Xs>::type;
        using All = BOOST_HANA_DISPATCH_IF(all_impl<S>,
            hana::Searchable<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Searchable<S>::value,
        "hana::all(xs) requires 'xs' to be a Searchable");
    #endif

        return All::apply(static_cast<Xs&&>(xs));
    }
    //! @endcond

    template <typename S, bool condition>
    struct all_impl<S, when<condition>> : default_ {
        template <typename Xs>
        static constexpr auto apply(Xs&& xs)
        { return hana::all_of(static_cast<Xs&&>(xs), hana::id); }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_ALL_HPP

/* all.hpp
fv9QeasPvr5x65jXOz5xHDKZ8e48+s323yp4OPnqlANm6PMHnoJeTP5HvnnZrI8Tr79/9YOZbx/YdsN+7P1gvWrScVvvb6X8zrzm7Jy40oHfR/1pnROxTxvwwIhBFYnzjjz31IfbHnlyO+p3x4j9pcvnPdau9Gj8ksEXPLpuxuuLsAZF+x1/eHzuuH0PXG9++tWFmTdufQDtlvVh96EnXvui1QUrn8+tevmFgc9djztAmQ8P3X3/mCvjA1+Nmjf44YrfDi7EHkXaf/nGvqRvra7bfMGvPi8sm9P5bdQrltd1B4Zf0e2T8h0/v3/S5Ky6F5GfZ3eI2OffsPS+4oMVzwxs8/O1u199ZTDunGS5JJxo8ZdFk0vnvp7c9brwDXUY+Bxnu7j38dufPfzS4pMrM3Y365n0Z+gnZzGfP96Yc0fv/RVf1h2/76k197XbAT2e9Sd8cNHaz451/ckrN45u3evoEOTP5wbagKxHPArpUIvf0/D7Mcfvnfqbd+PzNz4RbwzYvw2Hfbzjd5z8/q3B9wb0917H72ccvxMc/F+J/Zf4/bXjt5lu/14F+3Bc9PzCavs35ijs36/DfhZ+34/fv9bfvDOavw/gd4rj99Np9u/+lj3MAPs315reRhp+BZ5GsN+C31fG8Uwhf98YgOYo9kNQVqXyewJ+/154Gidgv4L8bobf78nvHPw+Kr874/d6+T2zMeSh/J6L33+U36vx+175vRG/75Hft+L3Jvn9Hn5fL7/jknHGUH43wu/jBuQCTC7SbwL3m3TjO/fvSgfxYSOjNgP4MbAt8FNgjtj3FLoKeAK4BvgZ8FrgX4DbgV8A9wK/BB4CfgX8BIjhVi0PtQPTgfHA9sBEYHdgI+DZwCTgVGAysAjYBLgA2BS4BJgOvBKYCtwEzARuAzYH7gSGgE8BWwCfBmYBI9/9IEwaysQEmvLdke+8U777HXS2mcD3gb2AHwD7AT8EDgSeBI4E/h44FfgxsBT4B+Cl4r4E+AlwM/AY8C7gn4CPi/2PgH8G/kT4XwUeB54AngB+LvbHgdArWD9MILo0pjcA7CTpfQHflQo8AEwHvijf2Q18ueIvJY7+qJ+3lrY/A+F3Bc4Bnge8GHgxcC5wKfASYC0wH3g1sAC4GVgIvAU4D/gYsAT4HHA+8E3gAvmOUuBfgGXAeMR5KbAx8Cpgd+DVwGHAtcCRwHXAqcD1wJnATcBy4GbgYuANwMuBNwLXA28GbgTeArwbeCvwHuAW4OPAbwG/D7wd+BTwDuBh4LXAD4AbgR8B75R8Xg+Th77MBH4i+dwEuAqG6zDI1x7AXwB7CX2W0JOBvwTOAh4BzgX+GngF8C3gZuBvgPcA3wE+DnwP+CTwfeBe4AfAl4AfAo8DwzC5SVLuUk9T8LtY0vME0h0CPglcC3wKuB74DPAmsX9f7D8U+xPAp4FfA/cAk030N8BU4DOSD8thChojXuAPJR+CwHKJ927wtQJuBXYE3gfsDbwfmAvcBhwDfAB4AfBx4EzgQ8BLgA8DVwN3AL8DfAz4iPAdBxbA5CQjfuBNMJSbwOkS/1757v3AucDngUXAF4DFwJ8CK4EvAi8D/gR4NfAl4Hq62+W9V+K5PEZ5/xx8TYEvA9OBh4Ah4GFgN+Ar8t2vAc8B/hJ4EfAIcDbwV5Ku14HFwLeAlwLfAFYB3wQuE/vjwDyYXBSwCVwBQ1kNHCPpuSFg1LYE3gjsA7wZOAB4C3AG8DZgEXALsAJ4B9CSd3sl3P0wXnmXa6JeA0dJOY0FXgwcLeV1PnAe8AJgGDgOuAQ4XtI/AbgKOBF4JXAScD3wQuCtwIuAdwAnA+8C5gHvBU4BPgScCnwUOA14HLgFZnM=
*/