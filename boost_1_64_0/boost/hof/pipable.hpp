/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    pipable.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_FUNCTION_PIPABLE_H
#define BOOST_HOF_GUARD_FUNCTION_PIPABLE_H

/// pipable
/// =======
/// 
/// Description
/// -----------
/// 
/// The `pipable` function adaptor provides an extension method. The first
/// parameter of the function can be piped into the function using the pipe
/// `|` operator. This can be especially convenient when there are a lot of
/// nested function calls. Functions that are made pipable can still be called
/// the traditional way without piping in the first parameter.
/// 
/// Synopsis
/// --------
/// 
///     template<class F>
///     constexpr pipable_adaptor<F> pipable(F f);
/// 
/// Semantics
/// ---------
/// 
///     assert(x | pipable(f)(ys...) == f(x, ys...));
/// 
/// Requirements
/// ------------
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
///     struct sum
///     {
///         template<class T, class U>
///         T operator()(T x, U y) const
///         {
///             return x+y;
///         }
///     };
/// 
///     int main() {
///         assert(3 == (1 | pipable(sum())(2)));
///         assert(3 == pipable(sum())(1, 2));
///     }
/// 
/// References
/// ----------
/// 
/// * [Extension methods](<Extension methods>)
/// 

#include <boost/hof/first_of.hpp>
#include <boost/hof/pack.hpp>
#include <boost/hof/detail/delegate.hpp>
#include <boost/hof/detail/move.hpp>
#include <boost/hof/detail/make.hpp>
#include <boost/hof/detail/static_const_var.hpp>
#include <boost/hof/limit.hpp>

namespace boost { namespace hof { 
 
template<class F>
struct pipable_adaptor;

namespace detail {

template<class F, class Pack>
struct pipe_closure : F, Pack
{
    
    template<class X, class P>
    constexpr pipe_closure(X&& fp, P&& packp) 
    BOOST_HOF_NOEXCEPT(BOOST_HOF_IS_NOTHROW_CONSTRUCTIBLE(F, X&&) && BOOST_HOF_IS_NOTHROW_CONSTRUCTIBLE(Pack, P&&))
    : F(BOOST_HOF_FORWARD(X)(fp)), Pack(BOOST_HOF_FORWARD(P)(packp))
    {}

    template<class... Ts>
    constexpr const F& base_function(Ts&&...) const noexcept
    {
        return *this;
    }

    template<class... Ts>
    constexpr const Pack& get_pack(Ts&&...) const noexcept
    {
        return *this;
    }

    template<class A>
    struct invoke
    {
        A a;
        const pipe_closure * self;
        template<class X>
        constexpr invoke(X&& xp, const pipe_closure * selfp) 
        BOOST_HOF_NOEXCEPT(BOOST_HOF_IS_NOTHROW_CONSTRUCTIBLE(A, X&&))
        : a(BOOST_HOF_FORWARD(X)(xp)), self(selfp)
        {}

        BOOST_HOF_RETURNS_CLASS(invoke);

        template<class... Ts>
        constexpr BOOST_HOF_SFINAE_RESULT(const F&, id_<A>, id_<Ts>...) 
        operator()(Ts&&... xs) const BOOST_HOF_SFINAE_RETURNS
        (BOOST_HOF_RETURNS_STATIC_CAST(const F&)(*BOOST_HOF_CONST_THIS->self)(BOOST_HOF_FORWARD(A)(a), BOOST_HOF_FORWARD(Ts)(xs)...));
    };

    BOOST_HOF_RETURNS_CLASS(pipe_closure);

    template<class A>
    constexpr BOOST_HOF_SFINAE_RESULT(const Pack&, id_<invoke<A&&>>) 
    operator()(A&& a) const BOOST_HOF_SFINAE_RETURNS
    (BOOST_HOF_MANGLE_CAST(const Pack&)(BOOST_HOF_CONST_THIS->get_pack(a))(invoke<A&&>(BOOST_HOF_FORWARD(A)(a), BOOST_HOF_CONST_THIS)));
};

template<class F, class Pack>
constexpr auto make_pipe_closure(F f, Pack&& p) BOOST_HOF_RETURNS
(
    pipe_closure<F, typename std::remove_reference<Pack>::type>(BOOST_HOF_RETURNS_STATIC_CAST(F&&)(f), BOOST_HOF_FORWARD(Pack)(p))
);


template<class Derived, class F>
struct pipe_pack
{
    template<class... Ts>
    constexpr const F& get_function(Ts&&...) const noexcept
    {
        return static_cast<const F&>(static_cast<const Derived&>(*this));
    }

    BOOST_HOF_RETURNS_CLASS(pipe_pack);

    template<class... Ts, class=typename std::enable_if<
        (sizeof...(Ts) < function_param_limit<F>::value)
    >::type>
    constexpr auto operator()(Ts&&... xs) const BOOST_HOF_RETURNS
    (make_pipe_closure(BOOST_HOF_RETURNS_C_CAST(F&&)(BOOST_HOF_CONST_THIS->get_function(xs...)), boost::hof::pack_forward(BOOST_HOF_FORWARD(Ts)(xs)...)));
};
    
template<class A, class F, class Pack>
constexpr auto operator|(A&& a, const pipe_closure<F, Pack>& p) BOOST_HOF_RETURNS
(p(BOOST_HOF_FORWARD(A)(a)));

}

template<class F>
struct pipable_adaptor 
: detail::basic_first_of_adaptor<detail::callable_base<F>, detail::pipe_pack<pipable_adaptor<F>, detail::callable_base<F>> >
{
    typedef detail::basic_first_of_adaptor<detail::callable_base<F>, detail::pipe_pack<pipable_adaptor<F>, detail::callable_base<F>> > base;
    typedef pipable_adaptor fit_rewritable_tag;

    BOOST_HOF_INHERIT_CONSTRUCTOR(pipable_adaptor, base);

    constexpr const detail::callable_base<F>& base_function() const noexcept
    {
        return *this;
    }
};

template<class A, class F>
constexpr auto operator|(A&& a, const pipable_adaptor<F>& p) BOOST_HOF_RETURNS
(p(BOOST_HOF_FORWARD(A)(a)));

BOOST_HOF_DECLARE_STATIC_VAR(pipable, detail::make<pipable_adaptor>);

namespace detail {

template<class F>
struct static_function_wrapper;

// Operators for static_function_wrapper adaptor
template<class A, class F>
auto operator|(A&& a, const boost::hof::detail::static_function_wrapper<F>& f) BOOST_HOF_RETURNS
(f(BOOST_HOF_FORWARD(A)(a)));

template<class F>
struct static_default_function;

// Operators for static_default_function adaptor
template<class A, class F>
auto operator|(A&& a, const boost::hof::detail::static_default_function<F>& f) BOOST_HOF_RETURNS
(f(BOOST_HOF_FORWARD(A)(a)));

}

template<class F>
struct static_;

// Operators for static_ adaptor
template<class A, class F>
auto operator|(A&& a, static_<F> f) BOOST_HOF_RETURNS
(f.base_function().base_function()(BOOST_HOF_FORWARD(A)(a)));

}} // namespace boost::hof

#endif

/* pipable.hpp
Zn1q6njHLhnv+O7bOxLjHWOzfZdu5uzqQrxjGnhJwYqvv7EjZhY5VPzqQiN+9cNrk7oL/K/NxD9/btL/PpP07GNO5tlkkI54X71JOPjZRI739T2YAT6JJUC6a8UaCSlY/fPRH9GCBcOnfSDES2w5ht1AOgEuRbwvhITaqWvKl8qQXpMwoO4CKtbk3NPSYQ7pVZ5IATSXqqeDheb4Xf5RxntUBK7Ge3TKjVU8rtfJDx1zXC+53wpQ7JlrQLhua3Ka/1OLqmsxR7RBdatRndf/3tp+rkCGmMGHHPl8x+nwNlz+O9mG97+ot+FR92WHj58ymzl+WKp4HByvqdZLPiXvlf5acvFGpHmgVWHV9UjzSckyfOrBNj6+Pj5WLD68GTK+D4GCbbVQbrUylYZR/mxc7Fzq1D6GULfOkOe8uABtE4tuVVv2TM5I6rAT6OpVLgIRrYespU220b6w3NZc1Y1zaBW26BJb/Ayrbu4x2/iqT5r4ZudBIuHNY/lTHab4ZikGTcvDPGjSDREV/8pGVGJwl/jEdjQPtSnvdsI27YP2TDRt9QfkUDRW21Zh4/DOwzD6uxfvbb7S2j612Y3GFWXywLD4fW2WvX0sGOAQ0N1PwgokDJCK9uzive29IeS6jDSwl724shsl8wvBkX52yWNx3bvi6fCDEJ1lFwvWq94o8r9lDNjywFV4z1fBnsm3J97VI/o8oIeFYDtr7OhOhN+z7bSZcMvYYf2bp8Vm+EQz5idS7LEyOyKGtf8bvI94pb32L6BPVQEJhx7GoIaCdhUdQZyAV9cojMN5CNVdg4nlFbOe4I7unsBGBiVNQrFgi+ESBA27Sb49SvZDeWaLcT9wBfTPx63c70k5bd/cyPUfw7RNeD/xvVZJsLOJonzprixmgfhbnyPif/j4YcTXJBGPAxnFA89Npu/qJyR95xn0pRjg+x5ioE8M2njM3FCuH7mJ/3BANPR5eiHmtKEMrBnJRL3xuCTqgZ9yvUdZL3h+Mbtid87FYv42nl05NA53hJet6lyyuBbTDu2YeZN+h1qUUR6hzzQSJj4OTkKb9pVzac+Tat6026URh30yircguXmyFZCSavvyQQhY1x/3TQHYCAAP8mo7bKX+Qcd19XMxLY798kEif4ZQd/tTUqhLxa9OAKNaCng8YGA2Agb2noHkXNCTNmIgR29YuaEjRbzA24AuHT02WMeS5rqQbiZZZb35keflsR/uTU46AMcVy4ehuYhx34pxVYMXmMYaHlbHA9zw12ML3Ren9yVWkio6JLU916Wg1li/fDhIPEsbUStqn9QlF/a/MWwdqDv0uLxjDgIf2pJE4F8UgRg1H8WKuSXlOMrx4vGpx5XCKhMe4aGE2EVqES27mhzvlLyofeic/sGqGJsga9vB7WNX2X3CasugIbbDNt6i7Tjm43rsr5Pl8f27Tc/BJ5KfBz+eWn5vK7PTaFdiflVS86XPr7YN337uKPmpo/QysYUOMW9ZR8oAIUof3eiiH5AIDIEgcFKz2+rfx8rovjg9UvYhQwMnc2qgnKMckv//TXF27pVOBzZjpEknPqcGimT2RSr7MGQPnEaJyPiju+JyFulfc6JQTXnIQ8RW5DqLcxH3WXLXsUpaKT8q/iMk5BovxELmcD2aUdV4bQ9XViNOBO2B85odQ7QPOGWG6MdvAxNnTPSzsVKd2UxqQoobIBfv6xibmLwWBSdxGcRKvVOWacOKjMiP5arNrpGNMHgj8k7Q8/4QeQMVeotczwWLONjCsRu1yv6HHbEFf3thSu26QTIt7KuOkN/J+Xvw0HoczSFzG/I/JqtaUVGAlt3ePrGfRXk25feI30rl2rjbMOAaRwSPRwwZxNo=
*/