/*=============================================================================
    Copyright (c) 2014 Paul Fultz II
    result.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_RESULT_H
#define BOOST_HOF_GUARD_RESULT_H

/// result
/// ======
/// 
/// Description
/// -----------
/// 
/// The `result` function adaptor sets the return type for the function, which
/// can be useful when dealing with multiple overloads. Since the return type
/// is no longer dependent on the parameters passed to the function, the
/// `result_adaptor` provides a nested `result_type` that is the return type
/// of the function.
/// 
/// Synopsis
/// --------
/// 
///     template<class Result, class F>
///     constexpr result_adaptor<Result, F> result(F f);
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
///     struct id
///     {
///         template<class T>
///         T operator()(T x) const
///         {
///             return x;
///         }
///     };
/// 
///     int main() {
///         auto int_result = boost::hof::result<int>(id());
///         static_assert(std::is_same<decltype(int_result(true)), int>::value, "Not the same type");
///     }
/// 

#include <boost/hof/detail/callable_base.hpp>
#include <boost/hof/is_invocable.hpp>
#include <boost/hof/always.hpp>
#include <boost/hof/reveal.hpp>

namespace boost { namespace hof {

template<class Result, class F>
struct result_adaptor : detail::callable_base<F>
{
    BOOST_HOF_INHERIT_CONSTRUCTOR(result_adaptor, detail::callable_base<F>)

    typedef Result result_type;

    struct failure
    : failure_for<detail::callable_base<F>>
    {};

    template<class... Ts>
    constexpr const detail::callable_base<F>& base_function(Ts&&... xs) const
    {
        return boost::hof::always_ref(*this)(xs...);
    }

    template<class... Ts, class=typename std::enable_if<(boost::hof::is_invocable<F, Ts...>::value)>::type>
    constexpr result_type operator()(Ts&&... xs) const
    {
        return this->base_function(xs...)(BOOST_HOF_FORWARD(Ts)(xs)...);
    };
};

template<class F>
struct result_adaptor<void, F> : detail::callable_base<F>
{
    BOOST_HOF_INHERIT_CONSTRUCTOR(result_adaptor, detail::callable_base<F>)

    typedef void result_type;

    template<class... Ts>
    constexpr const detail::callable_base<F>& base_function(Ts&&... xs) const
    {
        return boost::hof::always_ref(*this)(xs...);
    }

    template<class... Ts, class=typename std::enable_if<(boost::hof::is_invocable<F, Ts...>::value)>::type>
    constexpr typename detail::holder<Ts...>::type operator()(Ts&&... xs) const
    {
        return (typename detail::holder<Ts...>::type)this->base_function(xs...)(BOOST_HOF_FORWARD(Ts)(xs)...);
    };
};

#if BOOST_HOF_HAS_VARIABLE_TEMPLATES
namespace result_detail {
template<class Result>
struct result_f
{
    template<class F>
    constexpr result_adaptor<Result, F> operator()(F f) const
    {
        return result_adaptor<Result, F>(boost::hof::move(f));
    }
};

}

template<class Result>
static constexpr auto result = result_detail::result_f<Result>{};
#else
template<class Result, class F>
constexpr result_adaptor<Result, F> result(F f)
{
    return result_adaptor<Result, F>(boost::hof::move(f));
}
#endif

}} // namespace boost::hof

#endif

/* result.hpp
Nr14Aj7NS33x85U9K/49I2E+n5yZYP88Pr+vrlzL9gAkOMWqK+P8YbA+C9OQGPULD8Bmx/6uopF9fEgMltYptAD3oknhax0tuaEFuNaCEPApsMHyqxQ2CJBAfFWfR7ziVUOei0KzUF4x53aIa7HbwpUO6bGyC8ShHlBJgz3qZnIboWDiUarGJD8GCJQUKXPg+bvbqlLyWsAfIK/1xkyFrA5V8lps9fVKQw6w6Cp7sLvuYlOVs+3i5MtUb3ogWYW4Y6aS2Fpv+C78VsEteYypE009imdnHAVqyaFtvvJo9AljqBj7nz72yPbcIfXMLpJwlbNj/i7ek5oUuKgGGLUTQ/CqLJqccZJcPIWKOVdg+3vEQG6UW2pROSvEQ1eq7r45lf1cTJ1keK9B9YxLf/PDqNfR9hExmseh0Nj3/T9KWL8J631BTfz7rKL491VXJOh/JLwPTci/JL6+FZkM/6ZLwSUSBGLbdvbsRnu2h24xIlJoYuwp+avJqJIMH/YjDkfA0Tuu8O2lsnynj6ALQVhaYfLaSdV5Er2MS0qhiEhhFoKxn+PdjzX6qT3YE37czmKS1+BKniATc1+XQtOD6E61bEeTAwlBAXQ+lctieH0rEpHobl+4qKtQsjV0uK+kTK4RawxEFE1zA+2dC9UulnvCfpxkXEtzwM1NNhoXqAgdsAWdFCN+J6Ewu1LOw+5HFdnnsmGPHykPbs5JMY2Lxc6hrF5hEJhOHCZsyIu4GubTocWr/8vzcHPa2eLGinaLlWinfn7+NvSsqNY+PwfXrId+gHhfurxm3Yl4wuqez9kRKWuc4yY1jVr7vK3G9dIh6pFAm0mCzZM9LE+yahQCrlIBfvHIKJZ0bqdsCNOHiNiTscfqgMbwBFWQR/xwVOL25/V/eQL+qyX4v0yIX18X/16XkL62JP5956D498cT3pcm7L/pCfWNT6jvnrHx759dlnD+JeR/Pj6e8W/idXQW1bmsoWF6x8PUlQ0yvVml8kIzY3LGJrjNO8qHfWGyhXFgncl6Kgyt4ocRFJhjFOFpUQRlgE4IAvu/Z1HADEZWCFkW92oMWSWmUj8garf4W+VxJD1hLKphNSY0ZZRdT0raoAfWkzXOkaQG3Xi9k1zMB2GJ9CyDkHsqEXFHFJiQK5PeC8bE9DnYgeUq0CqCENktHRrLnAT+0Jvr7VavnquwItdPmZXynJ393+gj7MRiigoxukPPufMj4obL1LEylYUlT50RFZbMKCqzB/OlM4Y/nmmo0UytIVGZfLOF3ej9lotiWhgoYRHJUy9TIpIPkAwryZANC+OnZJTddfOVACQIySn5MjiQrHmTcors02QE7gq6IUabls8FrEtiV+TRXgPW4k0pbnC29uzIf+0jz4MFEANhrMsvymcYA7egozxc0X+Jm5FTXzXb5evbaHLESSr1/IHSHxHEKFZMJwBrGRSLc9PZ4q8Qn/5QneBveP2E//A7HwLE/5X2ouspPyvX4QQUnWZKNRM31EzKgCThPzAFqLdc84bF7FumKEXg2fpFULC7EP6mQEZ18oqwe5DiEa7JjZKudxNRuF4jRWbCLfrB0L5bPDhKoVYD0c6hqp2um3+EGYW16uhYhEal25QEHr1PYVzkBB0PxP/iiWEKo35+aK2bjoFKrM0NpWzPwyc6qFM5ULy3wmkhFNnlR7jVrsL7kUsnaOjx0rYGu5ShGDolVnI/JP+rnX4CVmTw/p9M9zM/C1l3m860lAKM1941FhT4NK3rfzAu4Yms4P+J1vC47ExX+YEwGL9IRWuivAkPaCJZlCXD+a7yFomBLNoc7Fg7pXG4bRJZffQ1Xh3R34WwfAE8rZ6zrCaCJ+G9lIyi6DvrQBY=
*/