#ifndef BOOST_MP11_TUPLE_HPP_INCLUDED
#define BOOST_MP11_TUPLE_HPP_INCLUDED

//  Copyright 2015-2020 Peter Dimov.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include <boost/mp11/integer_sequence.hpp>
#include <boost/mp11/list.hpp>
#include <boost/mp11/function.hpp>
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

using std::get;

template<class F, class Tp, std::size_t... J> BOOST_MP11_CONSTEXPR auto tuple_apply_impl( F && f, Tp && tp, integer_sequence<std::size_t, J...> )
    -> decltype( std::forward<F>(f)( get<J>(std::forward<Tp>(tp))... ) )
{
    return std::forward<F>(f)( get<J>(std::forward<Tp>(tp))... );
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
    return T( get<J>(std::forward<Tp>(tp))... );
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
    return (void)A{ ((void)f(get<J>(std::forward<Tp>(tp))), 0)... }, std::forward<F>(f);
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

// tuple_transform

namespace detail
{

// std::forward_as_tuple is not constexpr in C++11 or libstdc++ 5.x
template<class... T> BOOST_MP11_CONSTEXPR auto tp_forward_r( T&&... t ) -> std::tuple<T&&...>
{
    return std::tuple<T&&...>( std::forward<T>( t )... );
}

template<class... T> BOOST_MP11_CONSTEXPR auto tp_forward_v( T&&... t ) -> std::tuple<T...>
{
    return std::tuple<T...>( std::forward<T>( t )... );
}

template<std::size_t J, class... Tp>
BOOST_MP11_CONSTEXPR auto tp_extract( Tp&&... tp )
    -> decltype( tp_forward_r( get<J>( std::forward<Tp>( tp ) )... ) )
{
    return tp_forward_r( get<J>( std::forward<Tp>( tp ) )... );
}

#if !BOOST_MP11_WORKAROUND( BOOST_MP11_MSVC, < 1900 )

template<class F, class... Tp, std::size_t... J>
BOOST_MP11_CONSTEXPR auto tuple_transform_impl( integer_sequence<std::size_t, J...>, F const& f, Tp&&... tp )
    -> decltype( tp_forward_v( tuple_apply( f, tp_extract<J>( std::forward<Tp>(tp)... ) )... ) )
{
    return tp_forward_v( tuple_apply( f, tp_extract<J>( std::forward<Tp>(tp)... ) )... );
}

#else

template<class F, class Tp1, std::size_t... J>
BOOST_MP11_CONSTEXPR auto tuple_transform_impl( integer_sequence<std::size_t, J...>, F const& f, Tp1&& tp1 )
    -> decltype( tp_forward_v( f( get<J>( std::forward<Tp1>(tp1) ) )... ) )
{
    return tp_forward_v( f( get<J>( std::forward<Tp1>(tp1) ) )... );
}

template<class F, class Tp1, class Tp2, std::size_t... J>
BOOST_MP11_CONSTEXPR auto tuple_transform_impl( integer_sequence<std::size_t, J...>, F const& f, Tp1&& tp1, Tp2&& tp2 )
    -> decltype( tp_forward_v( f( get<J>( std::forward<Tp1>(tp1) ), get<J>( std::forward<Tp2>(tp2) ) )... ) )
{
    return tp_forward_v( f( get<J>( std::forward<Tp1>(tp1) ), get<J>( std::forward<Tp2>(tp2) ) )... );
}

template<class F, class Tp1, class Tp2, class Tp3, std::size_t... J>
BOOST_MP11_CONSTEXPR auto tuple_transform_impl( integer_sequence<std::size_t, J...>, F const& f, Tp1&& tp1, Tp2&& tp2, Tp3&& tp3 )
    -> decltype( tp_forward_v( f( get<J>( std::forward<Tp1>(tp1) ), get<J>( std::forward<Tp2>(tp2) ), get<J>( std::forward<Tp3>(tp3) ) )... ) )
{
    return tp_forward_v( f( get<J>( std::forward<Tp1>(tp1) ), get<J>( std::forward<Tp2>(tp2) ), get<J>( std::forward<Tp3>(tp3) ) )... );
}

#endif // !BOOST_MP11_WORKAROUND( BOOST_MP11_MSVC, < 1900 )

} // namespace detail

#if BOOST_MP11_WORKAROUND( BOOST_MP11_MSVC, < 1910 )

template<class F, class Tp1, class... Tp,
    class Seq = make_index_sequence<std::tuple_size<typename std::remove_reference<Tp1>::type>::value>>
BOOST_MP11_CONSTEXPR auto tuple_transform( F const& f, Tp1&& tp1, Tp&&... tp )
    -> decltype( detail::tuple_transform_impl( Seq(), f, std::forward<Tp1>(tp1), std::forward<Tp>(tp)... ) )
{
    return detail::tuple_transform_impl( Seq(), f, std::forward<Tp1>(tp1), std::forward<Tp>(tp)... );
}

#else

template<class F, class... Tp,
    class Z = mp_list<mp_size_t<std::tuple_size<typename std::remove_reference<Tp>::type>::value>...>,
    class E = mp_if<mp_apply<mp_same, Z>, mp_front<Z>>,
    class Seq = make_index_sequence<E::value>>
BOOST_MP11_CONSTEXPR auto tuple_transform( F const& f, Tp&&... tp )
    -> decltype( detail::tuple_transform_impl( Seq(), f, std::forward<Tp>(tp)... ) )
{
    return detail::tuple_transform_impl( Seq(), f, std::forward<Tp>(tp)... );
}

#endif // BOOST_MP11_WORKAROUND( BOOST_MP11_MSVC, < 1910 )

} // namespace mp11
} // namespace boost

#if BOOST_MP11_MSVC
# pragma warning( pop )
#endif

#endif // #ifndef BOOST_TUPLE_HPP_INCLUDED

/* tuple.hpp
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
*/