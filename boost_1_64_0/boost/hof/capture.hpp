/*=============================================================================
    Copyright (c) 2015 Paul Fultz II
    capture.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_CAPTURE_H
#define BOOST_HOF_GUARD_CAPTURE_H

#include <boost/hof/detail/callable_base.hpp>
#include <boost/hof/detail/compressed_pair.hpp>
#include <boost/hof/reveal.hpp>
#include <boost/hof/pack.hpp>
#include <boost/hof/always.hpp>
#include <boost/hof/detail/move.hpp>
#include <boost/hof/detail/result_type.hpp>

/// capture
/// =======
/// 
/// Description
/// -----------
/// 
/// The `capture` function decorator is used to capture values in a function.
/// It provides more flexibility in capturing than the lambda capture list in
/// C++. It provides a way to do move and perfect capturing. The values
/// captured are prepended to the argument list of the function that will be
/// called.
/// 
/// Synopsis
/// --------
/// 
///     // Capture by decaying each value
///     template<class... Ts>
///     constexpr auto capture(Ts&&... xs);
/// 
///     // Capture lvalues by reference and rvalue reference by reference
///     template<class... Ts>
///     constexpr auto capture_forward(Ts&&... xs);
/// 
///     // Capture lvalues by reference and rvalues by value.
///     template<class... Ts>
///     constexpr auto capture_basic(Ts&&... xs);
/// 
/// Semantics
/// ---------
/// 
///     assert(capture(xs...)(f)(ys...) == f(xs..., ys...));
/// 
/// 
/// Example
/// -------
/// 
///     #include <boost/hof.hpp>
///     #include <cassert>
/// 
///     struct sum_f
///     {
///         template<class T, class U>
///         T operator()(T x, U y) const
///         {
///             return x+y;
///         }
///     };
/// 
///     int main() {
///         auto add_one = boost::hof::capture(1)(sum_f());
///         assert(add_one(2) == 3);
///     }
/// 

namespace boost { namespace hof {

namespace detail {

template<class F, class Pack>
struct capture_invoke : detail::compressed_pair<detail::callable_base<F>, Pack>, detail::function_result_type<F>
{
    typedef capture_invoke fit_rewritable1_tag;
    typedef detail::compressed_pair<detail::callable_base<F>, Pack> base;
    BOOST_HOF_INHERIT_CONSTRUCTOR(capture_invoke, base)
    template<class... Ts>
    constexpr const detail::callable_base<F>& base_function(Ts&&... xs) const noexcept
    {
        return this->first(xs...);
    }

    template<class... Ts>
    constexpr const Pack& get_pack(Ts&&...xs) const noexcept
    {
        return this->second(xs...);
    }

    template<class Failure, class... Ts>
    struct unpack_capture_failure
    {
        template<class... Us>
        struct apply
        {
            typedef typename Failure::template of<Us..., Ts...> type;
        };
    };

    struct capture_failure
    {
        template<class Failure>
        struct apply
        {
            template<class... Ts>
            struct of
            : Pack::template apply<unpack_capture_failure<Failure, Ts...>>::type
            {};
        };
    };

    struct failure
    : failure_map<capture_failure, detail::callable_base<F>>
    {};

    BOOST_HOF_RETURNS_CLASS(capture_invoke);

    template<class... Ts>
    constexpr BOOST_HOF_SFINAE_RESULT
    (
        typename result_of<decltype(boost::hof::pack_join), 
            id_<const Pack&>, 
            result_of<decltype(boost::hof::pack_forward), id_<Ts>...> 
        >::type,
        id_<detail::callable_base<F>&&>
    ) 
    operator()(Ts&&... xs) const BOOST_HOF_SFINAE_RETURNS
    (
        boost::hof::pack_join
        (
            BOOST_HOF_MANGLE_CAST(const Pack&)(BOOST_HOF_CONST_THIS->get_pack(xs...)), 
            boost::hof::pack_forward(BOOST_HOF_FORWARD(Ts)(xs)...)
        )
        (BOOST_HOF_RETURNS_C_CAST(detail::callable_base<F>&&)(BOOST_HOF_CONST_THIS->base_function(xs...)))
    );
};

template<class Pack>
struct capture_pack : Pack
{
    BOOST_HOF_INHERIT_CONSTRUCTOR(capture_pack, Pack);

    BOOST_HOF_RETURNS_CLASS(capture_pack);

    // TODO: Should use rvalue ref qualifier
    template<class F>
    constexpr auto operator()(F f) const BOOST_HOF_SFINAE_RETURNS
    (
        capture_invoke<F, Pack>(BOOST_HOF_RETURNS_STATIC_CAST(F&&)(f), 
            BOOST_HOF_RETURNS_C_CAST(Pack&&)(
                BOOST_HOF_RETURNS_STATIC_CAST(const Pack&)(*boost::hof::always(BOOST_HOF_CONST_THIS)(f))
            )
        )
    );
};

struct make_capture_pack_f
{
    template<class Pack>
    constexpr capture_pack<Pack> operator()(Pack p) const
    BOOST_HOF_NOEXCEPT_CONSTRUCTIBLE(capture_pack<Pack>, Pack&&)
    {
        return capture_pack<Pack>(static_cast<Pack&&>(p));
    }
};

template<class F>
struct capture_f
{
    template<class... Ts>
    constexpr auto operator()(Ts&&... xs) const BOOST_HOF_RETURNS
    (
        BOOST_HOF_RETURNS_CONSTRUCT(make_capture_pack_f)()(BOOST_HOF_RETURNS_CONSTRUCT(F)()(BOOST_HOF_FORWARD(Ts)(xs)...))
    );
};
}

BOOST_HOF_DECLARE_STATIC_VAR(capture_basic, detail::capture_f<detail::pack_basic_f>);
BOOST_HOF_DECLARE_STATIC_VAR(capture_forward, detail::capture_f<detail::pack_forward_f>);
BOOST_HOF_DECLARE_STATIC_VAR(capture, detail::capture_f<detail::pack_f>);

}} // namespace boost::hof

#endif

/* capture.hpp
x31gZ58NB3ZGT2h/6IGglmtVOvrEB76PnCeW9ylCoxTffTfemIu2+zaED8dd92yIdImeQJ+eNfHuO5EyWKxdw733H9JxYsYJ8igXCXj+MfmqhHzI12zo/SjjbZQBOucGexvl3C/LUQs9qfiDkiDyVuRiCZh+fAiPyQgNm8X673pK5dsQcz3WmdgofNAe+kLP9m0Jg96uVRv1jdH4FV5wBS1xtsXewPQCCKKZSG0DE7/tCr9Txp/7LmDEXBvd+M3JxHckfVp+GjaAalHL9yP7kr/FV0nfJO+5dW3hQ/baToYBSJYfPpRZ20NbgQzxOU4RkQZxFZVV+1fc7MsGTxLAr7VApoZlXyfD30rfyfXXKEwMrEonlDmOCCzaT2kxXrxxHas0ZlxK+csozcuXp82/TJX/0OQW48XNrZfv3o8016UvH3Gy/G+kLb+B4i1hsix7i/CYn2lFv/BcThI+2CN0tlyTXXKwp1tbQm90rmJwiNhRbq6RBm34l1EjXq401Btk+tLM9ANLpjWJTHpFrj4nl4BFz2FgF29DmlA77SB+mu/WJ+eGix0o6JhZ0FJLQVdaCvqGg9mIFs/Bw/X4iw+FHBY/n8rotEnS8ZOe/sTj4u/+tPRHnKT/lkktxouV32m1falPiaXpy0ecLP+G9OVz3qGtl/8+pRmYtnzEKf5PW34DxVvCZFkbv90qvHLi6SfT9yfESXj3XZoWHsVbwmRZU1uHRzJHTEgPD3ES3nlp4cm8e7/VavngLbR/2v6FONX+l6StD8VbwmRZd7QIT8kj80/sYLiqDG1ZavxTlnju3ynxP1Xxih9T4m9V8YqfUuJrkuKpqvSnTR5kc2vnTLe5RZezVYLUJ336CZ5W0oO/Uut/WVr47mqUt+1slLfyrLbAT6R/uWcr6cFvqfVPD//t76C8vsOp/m2Cn0g/oTX44MfU+k+yJgf/pLb/pLT4lUwEvFlU35vz24JfIv1ve7SSnvnTVKHrZqaq0Noya/zVJ8Yzf6r40SfGM3+q+LwT45k/VfzRGTI+TX26D0NVPurfevzPup9Q/vvW8le3XP7WAPIv6t96/MiU8pm/rPVvufzwaOTv37/1+HdzU+PBP5by359+QvwKa/yz01ss/94ZKP/+fq3HB1LhS/1Bz4YPwubOUoFY6LCFZkMhOBe6MAbzenMwD9PbT+Vgro82B3NgKP2F50+Q67s1BRafrUEY/lUBd1gKuCRRABkTCVY7Q7/W7jVz3GnJ4ZE5/kMTCfRbQmtqjRYjAA8eYOqCckUJzwJf8AatgWKXEfh7Jfj7sE4k83yhMgYzxTe5rl59U0tI1QS0hsZuDAMLZc3liaXnrjU1WDyv4BZx8+aWPsEREm6E4N4n4Z5VwtUOiI/KjF19M1sjQAM7ck6pYH9aE3aeb48vLr5XnnCDddOWBNF1qrFBzx8IwItU401HWOkQH15muKgsnAokfzDJyKhnsiW4WvQazoNnYyZv3qkQf7pMrdptZ/fJPkG/pSo/l1WpGcWFaldW2WAQWTQZOIr20oikv0yrD1edessm01cfn6BvdwojEv99qpXE10i8lhNev5B4PV9skLiu9KQkbnDz/U/lwJ3s3UTjFWAF2kTB3j2+PfDjy8NfAf685OUqyi9SLrAT/OLvZZLPHIjKBULDgjdJhH5ICP1MInQBEOJimdeqwGdfDmQ+axpG3sc4EmvMJNMh2YYg/QLvT/q4aT0Ku452XmIQYf2qQ9Cx56E+y92juhi7Ovz2UVNpBXYDVmBTd3XU5unS6XgFmz/foVIc5IrdRH1//WoU1/ay3FxWaCLKIees5tENDyL/8s6jnMi9Bbkn20dNpNybeH/JluTc18vcHTg=
*/