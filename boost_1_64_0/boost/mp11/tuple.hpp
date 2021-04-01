#ifndef BOOST_MP11_TUPLE_HPP_INCLUDED
#define BOOST_MP11_TUPLE_HPP_INCLUDED

//  Copyright 2015, 2017 Peter Dimov.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include <boost/mp11/integer_sequence.hpp>
#include <boost/mp11/detail/config.hpp>
#include <tuple>
#include <utility>
#include <type_traits>
#include <cstddef>

#if BOOST_MP11_MSVC
# pragma warning( push )
# pragma warning( disable: 4100 ) // unreferenced formal parameter 'tp'
#endif

namespace boost
{
namespace mp11
{

// tuple_apply
namespace detail
{

template<class F, class Tp, std::size_t... J> BOOST_MP11_CONSTEXPR auto tuple_apply_impl( F && f, Tp && tp, integer_sequence<std::size_t, J...> )
    -> decltype( std::forward<F>(f)( std::get<J>(std::forward<Tp>(tp))... ) )
{
    return std::forward<F>(f)( std::get<J>(std::forward<Tp>(tp))... );
}

} // namespace detail

template<class F, class Tp,
    class Seq = make_index_sequence<std::tuple_size<typename std::remove_reference<Tp>::type>::value>>
BOOST_MP11_CONSTEXPR auto tuple_apply( F && f, Tp && tp )
    -> decltype( detail::tuple_apply_impl( std::forward<F>(f), std::forward<Tp>(tp), Seq() ) )
{
    return detail::tuple_apply_impl( std::forward<F>(f), std::forward<Tp>(tp), Seq() );
}

// construct_from_tuple
namespace detail
{

template<class T, class Tp, std::size_t... J> BOOST_MP11_CONSTEXPR T construct_from_tuple_impl( Tp && tp, integer_sequence<std::size_t, J...> )
{
    return T( std::get<J>(std::forward<Tp>(tp))... );
}

} // namespace detail

template<class T, class Tp,
    class Seq = make_index_sequence<std::tuple_size<typename std::remove_reference<Tp>::type>::value>>
BOOST_MP11_CONSTEXPR T construct_from_tuple( Tp && tp )
{
    return detail::construct_from_tuple_impl<T>( std::forward<Tp>(tp), Seq() );
}

// tuple_for_each
namespace detail
{

template<class Tp, std::size_t... J, class F> BOOST_MP11_CONSTEXPR F tuple_for_each_impl( Tp && tp, integer_sequence<std::size_t, J...>, F && f )
{
    using A = int[sizeof...(J)];
    return (void)A{ ((void)f(std::get<J>(std::forward<Tp>(tp))), 0)... }, std::forward<F>(f);
}

template<class Tp, class F> BOOST_MP11_CONSTEXPR F tuple_for_each_impl( Tp && /*tp*/, integer_sequence<std::size_t>, F && f )
{
    return std::forward<F>(f);
}

} // namespace detail

template<class Tp, class F> BOOST_MP11_CONSTEXPR F tuple_for_each( Tp && tp, F && f )
{
    using seq = make_index_sequence<std::tuple_size<typename std::remove_reference<Tp>::type>::value>;
    return detail::tuple_for_each_impl( std::forward<Tp>(tp), seq(), std::forward<F>(f) );
}

} // namespace mp11
} // namespace boost

#if BOOST_MP11_MSVC
# pragma warning( pop )
#endif

#endif // #ifndef BOOST_TUPLE_HPP_INCLUDED

/* tuple.hpp
5D6MWPHCvXbmbB7H7YgxciLKXh9ccM7IJDB1Cxnc6upic9SV1MbFQsuS+0xAN0FYf1QkjX4hUQPhNep1x02039tI5frjvoLX7jr1cO1+iRSplJwajQekoj6KydsqbMEdHDbfnrllIFTBLO2oyaxPKchO8RiTUIdK2CDBkB3Fl/rclF8a+B0tZemtXqFEjdEtbnSvMKkrdQfHoR7lYkTBLnMsjUmz/ua2F4niIvrb58uVfrDFbSokeRuEFYvFZa2C6FnjQcs+ArlZGv4BC0hTmpHqxyx0xnukHAoV68waE8vd0CuA1TyxkB2Z3ysZtcXPs9dqgnyDhiKDr8BLSgynpWAiH5pw9Y/RK6Z98uX08la5izN64oQynzoD9roxxFvXMS5B1xq6dB2G8zX4IkZvqgDoY0U1tykkr+cChl30P1MqLU5n+4SvoGJjo+AccE34gjt+BH/5pzsBA1xMKGnhEg3fR9sa+7PA6mY/cJHHe7szL1rrevCcrA/ed6ek6220yVFAG39BzvRcV0UUAz7e7QN2XNEpccKAtOET1lNnnP9aZJSdB4IfPxjoKQ==
*/