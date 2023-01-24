/*=============================================================================
    Copyright (c) 2015 Paul Fultz II
    rotate.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_ROTATE_H
#define BOOST_HOF_GUARD_ROTATE_H

/// rotate
/// ====
/// 
/// Description
/// -----------
/// 
/// The `rotate` function adaptor moves the first parameter to the last
/// parameter.
/// 
/// Synopsis
/// --------
/// 
///     template<class F>
///     rotate_adaptor<F> rotate(F f);
/// 
/// Semantics
/// ---------
/// 
///     assert(rotate(f)(x, xs...) == f(xs..., x));
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
/// 
///     int main() {
///         int r = boost::hof::rotate(boost::hof::_ - boost::hof::_)(2, 5);
///         assert(r == 3);
///     }
/// 

#include <boost/hof/detail/result_of.hpp>
#include <boost/hof/reveal.hpp>
#include <boost/hof/detail/make.hpp>
#include <boost/hof/detail/static_const_var.hpp>

namespace boost { namespace hof {

template<class F>
struct rotate_adaptor : detail::callable_base<F>
{
    typedef rotate_adaptor fit_rewritable1_tag;
    BOOST_HOF_INHERIT_CONSTRUCTOR(rotate_adaptor, detail::callable_base<F>);

    template<class... Ts>
    constexpr const detail::callable_base<F>& base_function(Ts&&... xs) const noexcept
    {
        return boost::hof::always_ref(*this)(xs...);
    }

    struct rotate_failure
    {
        template<class Failure>
        struct apply
        {
            template<class T, class... Ts>
            struct of
            : Failure::template of<Ts..., T>
            {};
        };
    };

    struct failure
    : failure_map<rotate_failure, detail::callable_base<F>>
    {};

    BOOST_HOF_RETURNS_CLASS(rotate_adaptor);

    template<class T, class... Ts>
    constexpr BOOST_HOF_SFINAE_RESULT(const detail::callable_base<F>&, id_<Ts>..., id_<T>) 
    operator()(T&& x, Ts&&... xs) const BOOST_HOF_SFINAE_RETURNS
    (
        (BOOST_HOF_MANGLE_CAST(const detail::callable_base<F>&)(BOOST_HOF_CONST_THIS->base_function(xs...)))
            (BOOST_HOF_FORWARD(Ts)(xs)..., BOOST_HOF_FORWARD(T)(x))
    );
};

BOOST_HOF_DECLARE_STATIC_VAR(rotate, detail::make<rotate_adaptor>);

}} // namespace boost::hof

#endif

/* rotate.hpp
TZUvswnkf+7aSWm5cuz+a4L57b/v2v++VX/x+rW7M8RF+IW7+24wxXNjlYnX5H/RmOUJM/E/moX4mimBwnKuzP1nRh5WlBgovrN5xqkcQcyUzMHH8cxYUSlSalmpN0SD9lYMJf9yySA1k7b09cQQRn5Xae/XHy7LLzszOtIRdmRKh1LUqZomcBObBRucbffoWeixRWC/Ofn1a/1pjx5y19OHc37o1VrUeOHJXdHtq6ENP0tHs+RmFBw5OlMjddlLmZIUXI1Nq9bRN3TQmwaZIwbM57HBElz1YU6nu79aJ1Groqaoo+qc+P6zHLb3Vt62WQo5K1lsPEE+6wm/e/WOHkn6ess1DdfLyBvDqNu1T9r9Ihl9vizUAgWdscWgB6eBcv18TfTJj2i64rJhevb38hs+6RfRumqUQz0omfuH77FaRVM4t10EaMaIno6wZeZGMx9+ZJ7SJVNR7yfI1/vUhT9q9ZhVXd/lg3jX+354JrsXM07z297Vp0S7FZf39mEV+BP+Z/D5gtQp2i7l5s7g+S32HVyWrl4FVi4hmFuyVyz7qUTDx0na+d+b6ieiMMq4HPdeo5+PQd+oSSMc6NIhz6F1pwjzdT3lexesJ8kU89AxrESEEW251ukjcSLJe5gXXNDejAhnzq7k4WdBQAJahBpHleqTW14kywbGes7rY09/sT6eCxRdbqejUcyOnQ2XZjwy7i0ozYk4UOq4
*/