/*!
@file
Defines `boost::hana::ap`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_AP_HPP
#define BOOST_HANA_AP_HPP

#include <boost/hana/fwd/ap.hpp>

#include <boost/hana/chain.hpp>
#include <boost/hana/concept/applicative.hpp>
#include <boost/hana/concept/sequence.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/detail/variadic/foldl1.hpp>
#include <boost/hana/functional/curry.hpp>
#include <boost/hana/functional/partial.hpp>
#include <boost/hana/transform.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    template <typename A, bool condition>
    struct ap_impl<A, when<condition>> : default_ {
        template <typename ...Args>
        static constexpr auto apply(Args&& ...args) = delete;
    };

    //! @cond
    template <typename F, typename X>
    constexpr decltype(auto) ap_t::operator()(F&& f, X&& x) const {
        using Function = typename hana::tag_of<F>::type;
        using Value = typename hana::tag_of<X>::type;
        using Ap = BOOST_HANA_DISPATCH_IF(ap_impl<Function>,
            hana::Applicative<Function>::value && hana::Applicative<Value>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Applicative<Function>::value,
        "hana::ap(f, x) requires 'f' to be an Applicative");

        static_assert(hana::Applicative<Value>::value,
        "hana::ap(f, x) requires 'x' to be an Applicative");
    #endif

        return Ap::apply(static_cast<F&&>(f), static_cast<X&&>(x));
    }

    template <typename F, typename ...Xs>
    constexpr decltype(auto) ap_t::operator()(F&& f, Xs&& ...xs) const {
        static_assert(sizeof...(xs) >= 1,
        "hana::ap must be called with at least two arguments");

        return detail::variadic::foldl1(
            *this,
            hana::transform(static_cast<F&&>(f), hana::curry<sizeof...(xs)>),
            static_cast<Xs&&>(xs)...
        );
    }
    //! @endcond

    template <typename S>
    struct ap_impl<S, when<Sequence<S>::value>> {
        template <typename F, typename X>
        static constexpr decltype(auto) apply(F&& f, X&& x) {
            return hana::chain(
                static_cast<F&&>(f),
                hana::partial(hana::transform, static_cast<X&&>(x))
            );
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_AP_HPP

/* ap.hpp
69/5O+fSm+Md5jnNBa0C5zT3xt7EktWLVmovOH9I88ZMyTQ2vlTbfQafcaP+YO4LPVBd0zlwHoNy9zf3hO+v3LHmnqjjlfvCoL1YXVWc7rvQ6auUfX31b1xjnkV0jXK/oq4ZpMJpnj+t9qJLhPpMq0LCOAObid0SwdSedf/kvIyTDnVehtpjL948AyOw72lCjLlfrxl2/q7CQfiino+9RDbf+zKWgBVjw/DviImS7tUO8zzgGIc6ANnc2/IKdU1OIN2V+wpHe/P84Erzu1ExwfcoxjFNudsE+fWa97OP+q6fuJVfc6/Ejir0NVXB5+Reqb6fYe7JOuMLnC3sVftSq3iFpNNKGXp7FOuBrcKGk05rwtJJ7fyoEip6/nxWXdMjsEerxK+jxO8d5b6eueW0c+avjsQvVvLX7KC81O4/zEvR8sxpmBAbbV+8aPsYRtuXMNp+edH2lfvi+75F2V8vyr6H0fa5i7bfYvR9FUcl+f+e1bj/ltSf9Hr5qacr75jw+eqd0fYZjLYvZLT9KKPtOxltn8po+ypG218v2j6J1u3zGGV/xij7KkbbBzPa/o/R9hOMtg9jtP0Wv/g+mPIOO5/AmtnEsHfYO8oeJV1lbv0ymVvvKWtDesHZMEnm9HvDWtgHroR94bdhP1gHr4VbIb+p3h1Jha/ANNgEh8A34VBzzYGUy1LmJ4atORghe0Skw0Q4Dg6BmXA4vBFeD7NlTcsEeCPMgwUwX9YGYCr8M8w1B1LOSRmaGLLmQFGtCSqCabAUjlDXGWuJPXAGrJD0qYQL4Dx4L3TDVfL3M+TrzQ8zj4KxfkCtDajDzrWOwFt47jUDslYgeJ3Av7RG4IusD2BtgFoXkBJhbUAD1hR5bYDl6wLOtSagDtt+7jUBwesBLFkLsBuTNQCR5v8jzf1HnPeXef7wOf5/aU7/HHP5/3Qe/9+Zw18fmLtX8/Zp/+bcfRm26AvM3cu8fbQ5+/94vl7P1dfLHP3h5vP0X2iO/tzz8+bcvDkvL/PxwXPxUebhQ+bgzzX/fq659y88727Muf9r8+16nv3Qw3HqJZOk9S3zw/9vnzisq/T/yz3FdOonZya7ytWWM8n019vCRtP3xRH76zkTpkxyqDWKrdTvLBLfK/fFqj6XwzPYVZSfn1OUn5WfP2HqFGnvW657Unw/onVdgz3nQ7csRtZj7hHdgpx8/wGuHBUjZ9TYo3tYdBuDdUvKPe7KGlt0e4puroylrN4ruqSx0TG1Vi9Z9HaL3s/2Beuxez8jRIEN/K3V7iPa+pzhF4Ljyo2t9lRVWp2fdHx3xIr3xiDN2mq3Op3QM9dTwrF6VmvrPJUWJ+Nke8K0c32eBehOci+2VFfHuV50OwbHuboGRf71caMZIaostTbOco9Vf12FYW+wdlltjf90HovTWWuuF01vcJ7mXCDjfClr03iwaCa0MXxvCdes9nl1eeV1+pwVFsdZ5601ov9pmL5daa3jHd/W8P2DMF2s2v8cF3lcRSWManLIpKX6Ot4rRX/w3ub6dpQjWtfRzvC9oTFMt8pbg2y11br6WV4iut8L162oLi0qcZaXFztL5tukfUa0d4SnNTe40l1S4y9TrK6n9DNdfoHsCxeuXeypsiutj4vmofC87SwpcXsluhZr6/w1p73h+3S4tp/jCgqtjrPWPSi6J4LS2XyWfW5qK5elujqtCy6U/dJD83W5P1tVUngUeX1VNVX2xHm3aD8WFGfiWukurarx2NAe0G299A5yFlWortNlk95m0VsX1P4gcRdaHT9dNwy4yPC9JDgPq8koaUiPG+OfbbE8fXWZUSf6vuA85amW6thaTZ2Pu19s+C7cF6rpqfQfiMW/1WU=
*/