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
f4RlbBbf/5glJ3+xY23izcH6GTbtjH6yf+6hiR4HsQaT5TO/23HYh1MHIcz4KyD8NovaWi76RlPIaEKrPtKq10m9kGGUdFvG7ZpRhmOOXUeyHzwXfcEo6EKS7Ac7y0GWX3G35dfeubdUgj61GGPthUFjbatm3Pc/XBg6VUxhyv2PDBHjGi9iktNFjGls53sH2jp1pqrb/OSau9Tpzm7qNDZEhCEf/jdoBeSnm3a3d0JA2/kEFusabYXAHEm+iyMq6F0ctokBfnvCYr0bfodq3YWbHOh3DCxoyL7Ovufoe0Vcgf6ryH+Wpi3vPs2NgX5vV2F7Rfd+Nwf6fWmizJ9XJGhyXyZQx+UabBDaU0zQXtGRiXwd35JtF45so19q0pu0B+RcUI6toUFj65O0P4D/9G0hohambizdwSHEW5A/DLCrb9bY6H0cHjqH9rtP2x4iRsPczH6ckGfAtLD9IshlAf+TfX7A/6H9rOgjTxX9vJjTeXoVU7ioenEX/FyzA3Nh+COarPJdbLmyPVJaoiwiqjSiTe7Mor6N8155LUR8C3PQCD+KvvXiFFGII0q9X8lj+I3bGSIugIkZZ5M0hZhFyHilgz3lvnAPzJcdxn5L53m3wm8rzBXjOA4aowf503D2GyHiaZgH8T/RpJkEpdxkM2FMBkNNIrSU3mTE11GwTjDZ/O9yN/XQ+V5Va66ptwX19Aza6yY57qs5FN2L
*/