/*=============================================================================
    Copyright (c) 2015 Paul Fultz II
    eval.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_EVAL_H
#define BOOST_HOF_GUARD_EVAL_H

/// eval
/// ====
/// 
/// Description
/// -----------
/// 
/// The `eval` function will evaluate a "thunk". This can be either a nullary
/// function or it can be a unary function that takes the identity function as
/// the first parameter(which is helpful to delay compile-time checking).
/// Also, additional parameters can be passed to `eval` to delay
/// compiliation(so that result can depend on template parameters).
/// 
/// Synopsis
/// --------
/// 
///     template<class F, class... Ts>
///     constexpr auto eval(F&& f, Ts&&...);
/// 
/// Requirements
/// ------------
/// 
/// F must be:
/// 
/// * [EvaluatableFunctionObject](EvaluatableFunctionObject)
/// 
/// Example
/// -------
/// 
///     #include <boost/hof.hpp>
///     #include <cassert>
/// 
///     int main() {
///         assert(boost::hof::eval([]{ return 3; }) == 3);
///     }
/// 
/// References
/// ----------
/// 
/// * [POO51](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2016/p0051r2.pdf) - Proposal for C++
///   Proposal for C++ generic overload function
/// * [static_if](static_if)
/// * [Ordering evaluation of arguments](<Ordering evaluation of arguments>)
/// 

#include <boost/hof/always.hpp>
#include <boost/hof/identity.hpp>
#include <boost/hof/first_of.hpp>
#include <boost/hof/detail/result_of.hpp>

namespace boost { namespace hof {

namespace detail {

struct simple_eval
{
    template<class F, class... Ts>
    constexpr BOOST_HOF_SFINAE_RESULT(F) 
    operator()(F&& f, Ts&&...xs) const BOOST_HOF_SFINAE_RETURNS
    (boost::hof::always_ref(f)(xs...)());
};

struct id_eval
{
    template<class F, class... Ts>
    constexpr BOOST_HOF_SFINAE_RESULT(F, id_<decltype(boost::hof::identity)>) 
    operator()(F&& f, Ts&&...xs) const BOOST_HOF_SFINAE_RETURNS
    (boost::hof::always_ref(f)(xs...)(boost::hof::identity));
};

}

BOOST_HOF_DECLARE_STATIC_VAR(eval, boost::hof::first_of_adaptor<detail::simple_eval, detail::id_eval>);

}} // namespace boost::hof

#endif

/* eval.hpp
tLYB/4mvX2bs0UxjoebJ3QaN2TfyNMpZTTe540AD9AVzb02AXJa2MmZFMrlvw3Q+krALF4uLs68He6ttVE8Ec2VwmbZCDl3DPmVCI+5n8hqtxuwggfuuI15rE1c9YcAiKq/Sv+eoFn3ht8ObeLggP/bLiVWMES69YlNCkJe7PdViu1MyPa0+DLo4E1XIkRsOuuO+zqeMgvNp5tB0EU0tzvloOvvM4lrC2Z9BwnoZApyYd3LxqNhp0vxUnsR+DWfU+t3ertujlvWzGdQNqr+Q9jv2Ku9/gL0hRCEUcbLCTHkadbiK60AUCLwrt9Ldv45+88VmNBeZQAa/GIu7AhtwlyyuDnN1qSC9ryJ/RlvrqfDpgT3Vf7cQTexgoqGctOn5ghfmu9XEdwuizHfA42RI1CQYq/O+BGP1PoGx3vuYGUvf1Lb9mJGyvGjSN6jN31fIb4TnRMblRi7xtLT/ysERTfeC3VP6Ww6vp5f0r8PmEDepXOwQxSZd+hNvfZ1w3eg4HWlY8QUf0qyh3Fi3KCfHZwj7Sg799Es1xEMHonNzq8hzz8EXFleLuzcoT44r8XVXljLj+SpKIMHqngNOHmxtjg+/VzRBGccr8qImeZHB92IPPe7li+Tcaxgtqg18xAu7GRHj2j4/sEBMBsUcg6pZHanMjcD39D5OlXNmLvfDw/dxkZA51y4nSzWh4fpIun/Qw/Mdrsaj4myJHMJv26MNpAH0U3ADT6LeZoQ05FeBOeISBPI+cFYSG8gy7xd/ZZpSKc12msy5lv0EEdVVRO/QXkXvdlhXGRxGS52FxihfoQ0zyx3+hPgSbhIVKBX3g33WfC4SDNAdT5REb3GUvHxrN+0ildQvtrzFWFUg4Qc0ImnFKo7BZcmVbb9YI9NJjHJdkZsgqKZTiquf5wpP0y5WGQMiJBP/V/fs65OM9bCSznUdGyuYneVdMU7dsQwc1x6B8iI3qVJ2zmTuQ6itLfs/ub+oTfHFYxYWo+Dw6AZbaBBcpnRHQxKv90RkVXx4g3goY68yBv4GUCpLxtQ1cvYyld2XJnt/lX3mc2hd430GF+WmYYKKeaGKBG3vd1WHugoV4YWz+MIRZE9CtikMYEAaAC5VaP0LMn980TY5ymEZfCb27WIKVsF9CAOLYSY8E53mhPkGdkkl+R/j12PLQETho8TXxO002/gIQRqFV4mNT5rzsy0ICA5kHgvmi3ObY9ZlMXI0Q5MNr5+fU685Ix4409JDB6I3tqM38asv5ewWEpIyzKPSBtcP/yVFcqE1ETKibftcljvBxqsXlOpCGS3Wfa5AeiPtKNaHWN9+YPwj8gwKH3G47lxmYzzy9cts9VVHw9Gjme9lbqeVxpIooTfPUfLG3OtLXsbvO3NnljTi9925Ab0c8a/h/eW5l5Zsw2/j3PF6dCB4evFtWRPDm4+W6q8O2hze5CjZW3dIX2CrL8u8L/xJZiZuQtt4OGPjJw5pVXkYMsq78fMM/RV+LSjZtyDf1X8JE0KfYGt0PMpv7YyXipJ9dUIHyekwVXLJDL/siOCVnGodmxbHec2uo6v/Ys6FiKVxsCpaLIuaxl9FJhlxeaJ9zkMGyuloZ6NUgxr9+Mps9POqUO0noH4VSbrFo0fZ6nNGuZZcgvRQerMWjxoQeqD+ZnOL3uuES+ahxXWj4h1q9eCly8pHYdPXEENiDYG53CIvdeGLZwIRami0Wf08u36pw7dreRecijgIRBhu4L/4cPvaLFhfr5zo27XMvfjw1a5V0dIySlb7KdEKl+ZiTBpeO3Exri0eXxopf9JGaFRTr3sA8oyGKqNn78VcPngzo1Mtlr3O6DQPQQFlpSUHFjxOWSuafxv8rpFiFlI=
*/