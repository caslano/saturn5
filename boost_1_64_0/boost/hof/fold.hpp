/*=============================================================================
    Copyright (c) 2015 Paul Fultz II
    fold.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_FOLD_H
#define BOOST_HOF_GUARD_FOLD_H

/// fold
/// ========
/// 
/// Description
/// -----------
/// 
/// The `fold` function adaptor uses a binary function to apply a
/// [fold](https://en.wikipedia.org/wiki/Fold_%28higher-order_function%29)
/// operation to the arguments passed to the function. Additionally, an
/// optional initial state can be provided, otherwise the first argument is
/// used as the initial state.
/// 
/// The arguments to the binary function, take first the state and then the
/// argument.
/// 
/// Synopsis
/// --------
/// 
///     template<class F, class State>
///     constexpr fold_adaptor<F, State> fold(F f, State s);
/// 
///     template<class F>
///     constexpr fold_adaptor<F> fold(F f);
/// 
/// Semantics
/// ---------
/// 
///     assert(fold(f, z)() == z);
///     assert(fold(f, z)(x, xs...) == fold(f, f(z, x))(xs...));
///     assert(fold(f)(x) == x);
///     assert(fold(f)(x, y, xs...) == fold(f)(f(x, y), xs...));
/// 
/// Requirements
/// ------------
/// 
/// State must be:
/// 
/// * CopyConstructible
/// 
/// F must be:
/// 
/// * [BinaryInvocable](BinaryInvocable)
/// * MoveConstructible
/// 
/// Example
/// -------
/// 
///     #include <boost/hof.hpp>
///     #include <cassert>
/// 
///     struct max_f
///     {
///         template<class T, class U>
///         constexpr T operator()(T x, U y) const
///         {
///             return x > y ? x : y;
///         }
///     };
///     int main() {
///         assert(boost::hof::fold(max_f())(2, 3, 4, 5) == 5);
///     }
/// 
/// References
/// ----------
/// 
/// * [Fold](https://en.wikipedia.org/wiki/Fold_(higher-order_function))
/// * [Variadic sum](<Variadic sum>)
/// 

#include <boost/hof/detail/callable_base.hpp>
#include <boost/hof/detail/delegate.hpp>
#include <boost/hof/detail/compressed_pair.hpp>
#include <boost/hof/detail/move.hpp>
#include <boost/hof/detail/make.hpp>
#include <boost/hof/detail/static_const_var.hpp>

namespace boost { namespace hof { namespace detail {

struct v_fold
{
    BOOST_HOF_RETURNS_CLASS(v_fold);
    template<class F, class State, class T, class... Ts>
    constexpr BOOST_HOF_SFINAE_MANUAL_RESULT(const v_fold&, id_<const F&>, result_of<const F&, id_<State>, id_<T>>, id_<Ts>...)
    operator()(const F& f, State&& state, T&& x, Ts&&... xs) const BOOST_HOF_SFINAE_MANUAL_RETURNS
    (
        (*BOOST_HOF_CONST_THIS)(f, f(BOOST_HOF_FORWARD(State)(state), BOOST_HOF_FORWARD(T)(x)), BOOST_HOF_FORWARD(Ts)(xs)...)
    );

    template<class F, class State>
    constexpr State operator()(const F&, State&& state) const noexcept
    {
        return BOOST_HOF_FORWARD(State)(state);
    }
};

}

template<class F, class State=void>
struct fold_adaptor
: detail::compressed_pair<detail::callable_base<F>, State>
{
    typedef detail::compressed_pair<detail::callable_base<F>, State> base_type;
    BOOST_HOF_INHERIT_CONSTRUCTOR(fold_adaptor, base_type)

    template<class... Ts>
    constexpr const detail::callable_base<F>& base_function(Ts&&... xs) const noexcept
    {
        return this->first(xs...);
    }

    template<class... Ts>
    constexpr State get_state(Ts&&... xs) const noexcept
    {
        return this->second(xs...);
    }

    BOOST_HOF_RETURNS_CLASS(fold_adaptor);

    template<class... Ts>
    constexpr BOOST_HOF_SFINAE_RESULT(detail::v_fold, id_<const detail::callable_base<F>&>, id_<State>, id_<Ts>...)
    operator()(Ts&&... xs) const BOOST_HOF_SFINAE_RETURNS
    (
        detail::v_fold()(
            BOOST_HOF_MANGLE_CAST(const detail::callable_base<F>&)(BOOST_HOF_CONST_THIS->base_function(xs...)), 
            BOOST_HOF_MANGLE_CAST(State)(BOOST_HOF_CONST_THIS->get_state(xs...)), 
            BOOST_HOF_FORWARD(Ts)(xs)...
        )
    )
};


template<class F>
struct fold_adaptor<F, void>
: detail::callable_base<F>
{
    BOOST_HOF_INHERIT_CONSTRUCTOR(fold_adaptor, detail::callable_base<F>)

    template<class... Ts>
    constexpr const detail::callable_base<F>& base_function(Ts&&... xs) const noexcept
    {
        return boost::hof::always_ref(*this)(xs...);
    }

    BOOST_HOF_RETURNS_CLASS(fold_adaptor);

    template<class... Ts>
    constexpr BOOST_HOF_SFINAE_RESULT(detail::v_fold, id_<const detail::callable_base<F>&>, id_<Ts>...)
    operator()(Ts&&... xs) const BOOST_HOF_SFINAE_RETURNS
    (
        detail::v_fold()(
            BOOST_HOF_MANGLE_CAST(const detail::callable_base<F>&)(BOOST_HOF_CONST_THIS->base_function(xs...)), 
            BOOST_HOF_FORWARD(Ts)(xs)...
        )
    )
};

BOOST_HOF_DECLARE_STATIC_VAR(fold, detail::make<fold_adaptor>);

}} // namespace boost::hof

#endif

/* fold.hpp
ufXgGl/yoc0S28VoC15uHzT9tHbH+PpJvXjnqu6YsaZJ8TviKa/5FvGUHzruwWrSeULsAal/MEfq/MnXX9C/QxvdD35p/X4LW/cMHcgK/T6LeKZhUBBT2Xet5wkrAaYz50byi0NWa7D3TNIfedix5i9MbazyeCD1JW0cIf4TDguzn6ELDPJDdFVyGPHUf97+VkZpu7NlFKKEYg7nNXdR1rOttDC2XmSJXFr+0uv6PPy3toImeEkQ+dPnwLaVnjyIt/Zu/cFLwmE/NZqxzXOqjhSRuVZal/EvdNABiHO2fEJs+DXDSbhf3P8YH2yo2+Fb3owZZ4PKgmHrIk/e4wznvpf+QOTFtpzxVA/ef3PLdM3CGWfrZQTXNlxZpoBWfF96g1x0Fb71hwQhQ6W3A66CUzM+mCmhCOYwFCcDChJkIimJl4reRyKXUabMCUmKYiml/hhyTRk4L2mLUURosXv5UOTs8pNmW2Y77AOKdlP/MB2AVEZZA/3WhbXie9+Nl/V+Qn6fQ37UBcQZZflHyPqO1w+2v9MblqLyWLdzrbgKidvf6I207e9kWCnrP1KDRZc9hRJAEE34U3tXRunHa06d8HFkbTniROz9OSmsNL5vsyBFIUx11oozkA9ZGnw/mqt3tosML8WJzCrPaPeKqxARBWR8UBSToJGdpCticoH+tIdQ/0E/FjfWtzPX6EUMcUyiQL82cr58yFF5Rnm01168m2eGDuetKwwdLl/rbiunrsVBUlV5xh7CARe9x03jt8IHt8veho4gHjJRGyLnpUQukZHrIws2P+OgGXQrz19bZM5H2yrskXPt7cKxrSKD3zZ+W0MHrcHfqty3f0fZ3chuIA0qTlcm4ySfc4DF6apyOQeUu/DNwzcP30J8C8XdQERxc9YnbMv1RH5cuF/qpV72LuqWJGaj7M2d9XU5vGm7QBKP7unwdTmvOUgHYnSVLNdH+KYe5z3fpbZ/Bk+z9Slumt+GXsti5YS4Iz+VvdaOkXhtK+G1kIUR2m4DoWGrAII8l7RH7EXoDpo8S6yUDSY58Naa5a1jIgsZRxFOAhJyVI4sj8wvBx4Csho0C3AoZOTG1ITOQYjRtq70jKY+fVWiIokGCM29zshn5cjyMMMd3dE6IOMDznzPSwK5OuzDZm1b5BmkEAvn+NwjyHGRkWPR+8iNMGk5Z/iHopjEZ26ZY1dpTGKALzMGoPlfoP+uPdob9xxPrkVmGx8x1Qq0v9Yblcz4kZz+1GbRJd+3MPKe8FtC30fWnDLhSCRYjlgR+5DahZj/f8H8hzwk5n+dOOMRNf+HyfkPoBZm7MHZ6F/U5GfgGDJGAJcDOGpubnZgrdOoW7e00zsMr9Bb1jDhMsRwbj0JqAzn1iSy0H4gwwvQd2JVU+Pl/P9QE3OhVThLZqEwfXV2cBn+5UDEPDhLfBeyFJB4WHSzlKuykpSxaEcLYpKeAlkGdTNjsH+J1nYy31q6GPcmXrrNVANF6BU6Mg/3YvMHJzgvcdlaZpctTvt6/DLpCPG+H4KgmXwfw88xfOJd3byP0Vll52uUf/yiYV8uOAJXLWtXd0ODhRF7L8d2qRsg4dXZJyKBxk2j7fiO04X2IeHSfJBSyPrQFfhAC9gwiGdqtHoZpazgUnJ7zLXNg0KF86uJ9Fie3FYX41NH5FgJ/hS9Q+uoohAg88TBpDqXtG+RUpvz6TRf6nL95F6iuSjnjlrwC8ooJpSwhI5AbBInLquQjecrFw5yRQeHjticW0n8Hd5e8iaJPZBzlcRJEDddghYXbNDsz6pK/qwuoHS6buCj42xx5HOIEyBT/cTeAECF1Cr971fqUba/jNj15PfwN4wr7LoTGMmgz+JXoys=
*/