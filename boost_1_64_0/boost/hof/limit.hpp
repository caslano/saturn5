/*=============================================================================
    Copyright (c) 2016 Paul Fultz II
    limit.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_LIMIT_H
#define BOOST_HOF_GUARD_LIMIT_H

/// limit
/// =====
/// 
/// Description
/// -----------
/// 
/// The `limit` function decorator annotates the function with the max number
/// of parameters. The `limit_c` version can be used to give the max number
/// directly(instead of relying on an integral constant). The parameter limit
/// can be read by using the [`function_param_limit`](function_param_limit)
/// trait. Using `limit` is useful to improve error reporting with partially
/// evaluated functions.
/// 
/// Synopsis
/// --------
/// 
///     template<class IntegralConstant>
///     constexpr auto limit(IntegralConstant);
/// 
///     template<std::size_t N, class F>
///     constexpr auto limit_c(F);
/// 
/// Requirements
/// ------------
/// 
/// IntegralConstant must be:
/// 
/// * IntegralConstant
/// 
/// F must be:
/// 
/// * [ConstInvocable](ConstInvocable)
/// * MoveConstructible
/// 
/// Example
/// -------
/// 
///     #include <boost/hof.hpp>
///     #include <cassert>
///     using namespace boost::hof;
/// 
///     struct sum_f
///     {
///         template<class T>
///         int operator()(T x, T y) const
///         {
///             return x+y;
///         }
///     };
///     BOOST_HOF_STATIC_FUNCTION(sum) = limit_c<2>(sum_f());
/// 
///     int main() {
///         assert(3 == sum(1, 2));
///     }
/// 
/// See Also
/// --------
/// 
/// * [Partial function evaluation](<Partial function evaluation>)
/// * [function_param_limit](function_param_limit)
/// 

#include <boost/hof/detail/callable_base.hpp>
#include <boost/hof/detail/forward.hpp>
#include <boost/hof/detail/delegate.hpp>
#include <boost/hof/detail/move.hpp>
#include <boost/hof/detail/static_const_var.hpp>
#include <boost/hof/always.hpp>
#include <boost/hof/function_param_limit.hpp>

namespace boost { namespace hof {

namespace detail {
// TODO: Make this work with fit_rewritable1_tag
template<std::size_t N, class F>
struct limit_adaptor : detail::callable_base<F>
{
    typedef std::integral_constant<std::size_t, N> fit_function_param_limit;
    BOOST_HOF_INHERIT_CONSTRUCTOR(limit_adaptor, detail::callable_base<F>)

    template<class... Ts>
    constexpr const detail::callable_base<F>& base_function(Ts&&... xs) const
    {
        return boost::hof::always_ref(*this)(xs...);
    }

    BOOST_HOF_RETURNS_CLASS(limit_adaptor);

    template<class... Ts, class=typename std::enable_if<(sizeof...(Ts) <= N)>::type>
    constexpr BOOST_HOF_SFINAE_RESULT(const detail::callable_base<F>&, id_<Ts>...) 
    operator()(Ts&&... xs) const BOOST_HOF_SFINAE_RETURNS
    (
        (BOOST_HOF_MANGLE_CAST(const detail::callable_base<F>&)(BOOST_HOF_CONST_THIS->base_function(xs...)))
            (BOOST_HOF_FORWARD(Ts)(xs)...)
    );

};

template<std::size_t N>
struct make_limit_f
{
    constexpr make_limit_f()
    {}
    template<class F>
    constexpr limit_adaptor<N, F> operator()(F f) const
    {
        return limit_adaptor<N, F>(static_cast<F&&>(f));
    }
};

struct limit_f
{
    template<class IntegralConstant, std::size_t N=IntegralConstant::type::value>
    constexpr make_limit_f<N> operator()(IntegralConstant) const
    {
        return {};
    }
};

}

template<std::size_t N, class F>
constexpr detail::limit_adaptor<N, F> limit_c(F f)
{
    return detail::limit_adaptor<N, F>(static_cast<F&&>(f));
}

BOOST_HOF_DECLARE_STATIC_VAR(limit, detail::limit_f);

}} // namespace boost::hof

#endif

/* limit.hpp
kd8rajJ0Vt/oDJzjFaNO0x+D0c6qmRnBwQaCUxKH/KVgNUBSVutcRbdiMMmi4cu18hyYqWc2X2pv7w31QD5IXc8eVGoRx+TVDmlHdY9N3bUZrF7WmfCyw+fSiWc4Xm2vOFBudH3izC+UMvQsYD4BT4y50sBsw43xnkv7g0AEjAo4vKKuSL3VAp3xwdTRbpgpxknJSiBlMpOiucnXPsLxvv0Cb6Jo24h1wGFgHArYtm7KgmpAADqnjhFq+ew+V3YevniE/88e5srh7BV3YUWtxvtNhlkqsWntkFdE9bTRSIOgdWMbNUQ+WayWpVWMbeVT4EaoWchtzjo+v1iCNReb8pVPEwx+De3NdGC2mZ3qxEZDbctjxEUReaFzU/m0KgcbMSPMEtleiQuxHYU2Ab8L2V1RFFRGHy/g+va+1qEilIb7otCs2GIQDMUN67Y+oPo8IvdFHjAwY6QqvqJLEumFm2PJ62H4gt2idZdjIqSYBZqcBTUi84/6WL3dqsbqcJQcoE+CJK4eGsCcEJOhN7L8U58K7XtrxJmfqvF/KnCe8Kka/wbOQhTYHoDp0cWnqFH6KyR118d+/L7j0v08R94G8KaAo/35577yR7fHWk1qO4qOjwUtM3ieHth3tBf9IA5lKBuJk73olUB/Xd271JDSw31wGylaNYWpw9Cq39qtq/K5lAed0CLJm6igp2KK9iCRU+2JXe0h4U4sAgXYSNPQEZu7Kc2bqzhGWkIfIGImcvAAWjE+IzRsRdhqDQ1aEUYgoH64csPuxs97V5lc5lSVYLvSQBIU08liVCyEs19QoZH+rtLFYkukCX/5ZntlbjTkADXinG56PSVXTwkPhv6NEs9Fokccj9LTJKRx/zfm+Zb3I6z45hvTvNOKNM6xBGtxHUAam6BPduu/xKfZaiydHbgQbGF5tgq0eCKbqyIpoJLIjgbS9jxxsEVvmrDcnHEy9BsyuXgXOPg9LfVaS5c6NPV888WuLhKfYKA3XzZKOwRH4XIeDPb/IkNX+3jE2VIpp/vBJnP38EnrvFRwkYUsqq8eidNV1vVdx5wgD32Z7S452LCXrr+jxZ23YNbh+1g4trIFC7u0OlukscgSrPLVCHcspg+WsSmONP4W6zDvycYnrD9ZcumQFk3uADSqpTA6nd1LXUEvToHylsNRnpew8D+kVZXh63xCNhHIPshUyEanQFZ1OLKyxNV4Dt7u37Wu8XhNQdOvvlQ0ydMzcF33vAS+mW5sxU31Sg6GBsmN/Cd/Tt7Ig+OwM/5raYMvpP/dVWRj66Hcu5GbrmYju34nPtifZu1l3EocKztz7mzgQCJOdmfGlG1yBcf3pKydXzDxJW3BU3FEO2mb0kPnAegWx6OEPNV9GQPxfeBy3oJZ9MRoUGAkfNWdtLw/dByqIMcXtPxNcmlX0Y3bDIrnZegkWLFQcgCqhQPi3mcM1cKjumoh7eRNsIWUElMAoQQs4h/dpJDlgpDVXZd+VZfGdK3CPjA83qLp24cw9unzuDNJ/jrifnIYVM9qP0mo3kQDs0wXabc617xkpcMZaRbJ+6dFek0C+/KenZUL852r7kceXSEAXS0easUprwPJoVpy8yf+AoboI4272oOKGTiTqNYXDvT58p5PVSN5/wtKG34m4HwDdolVnHhA9beea5OuLqiWp1DXQC8PXhvjEnnaIfwdJa7gxL/yYMgtaQt156LtVwFYIJY5dN8doC6PtAyfynrh37cYIFrmRooDOwjDn3YTBtDYO5RNlPnEiYalo47TRmp7xvsoeCYvbxN/g1KsqIjv5khzEpY9omzqqTW/x61pa14SK/ksXM/t3/8z2cArbqHVTlq+l+EIYTMYrWRq/TE=
*/