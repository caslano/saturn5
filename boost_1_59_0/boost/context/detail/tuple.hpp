
//          Copyright Oliver Kowalke 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_CONTEXT_DETAIL_TUPLE_H
#define BOOST_CONTEXT_DETAIL_TUPLE_H

#include <tuple>
#include <utility>

#include <boost/config.hpp>

#include <boost/context/detail/config.hpp>
#include <boost/context/detail/index_sequence.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
# include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace context {
namespace detail {

template< typename ... S, typename ... T, std::size_t ... I >
void
head_impl( std::tuple< S ... > & s,
           std::tuple< T ... > & t, index_sequence< I ... >) {
    t = std::tuple< T ... >{ std::get< I >( s) ... };
}

template< typename ... S, typename ... T, std::size_t ... I >
void
head_impl( std::tuple< S ... > && s,
           std::tuple< T ... > & t, index_sequence< I ... >) {
    t = std::tuple< T ... >{ std::get< I >( std::move( s) ) ... };
}

template< typename ... S, std::size_t ... I1, typename ... T, std::size_t ... I2 >
void
tail_impl( std::tuple< S ... > & s, index_sequence< I1 ... >,
           std::tuple< T ... > & t, index_sequence< I2 ... >) {
    constexpr std::size_t Idx = (sizeof...(I1)) - (sizeof...(I2));
    t = std::tuple< T ... >{ std::get< (Idx + I2) >( s) ... };
}

template< typename ... S, std::size_t ... I1, typename ... T, std::size_t ... I2 >
void
tail_impl( std::tuple< S ... > && s, index_sequence< I1 ... >,
           std::tuple< T ... > & t, index_sequence< I2 ... >) {
    constexpr std::size_t Idx = (sizeof...(I1)) - (sizeof...(I2));
    t = std::tuple< T ... >{ std::get< (Idx + I2) >( std::move( s) ) ... };
}

template< typename ... T >
class tuple_head;

template< typename ... T >
class tuple_head< std::tuple< T ... > > {
private:
    std::tuple< T ... > &   t_;

public:
    tuple_head( std::tuple< T ... > & t) noexcept :
        t_( t) {
    }

    template< typename ... S >
    void operator=( std::tuple< S ... > & s) {
        static_assert((sizeof...(T)) <= (sizeof...(S)), "invalid tuple size");
        head_impl( s,
                   t_, index_sequence_for< T ... >{} );
    }
    template< typename ... S >
    void operator=( std::tuple< S ... > && s) {
        static_assert((sizeof...(T)) <= (sizeof...(S)), "invalid tuple size");
        head_impl( std::move( s),
                   t_, index_sequence_for< T ... >{} );
    }
};

template< typename ... T >
class tuple_tail;

template< typename ... T >
class tuple_tail< std::tuple< T ... > > {
private:
    std::tuple< T ... > &   t_;

public:
    tuple_tail( std::tuple< T ... > & t) noexcept :
        t_( t) {
    }

    template< typename ... S >
    void operator=( std::tuple< S ... > & s) {
        static_assert((sizeof...(T)) <= (sizeof...(S)), "invalid tuple size");
        tail_impl( s, index_sequence_for< S ... >{},
                   t_, index_sequence_for< T ... >{} );
    }

    template< typename ... S >
    void operator=( std::tuple< S ... > && s) {
        static_assert((sizeof...(T)) <= (sizeof...(S)), "invalid tuple size");
        tail_impl( std::move( s), index_sequence_for< S ... >{},
                   t_, index_sequence_for< T ... >{} );
    }
};

template< typename ... T >
detail::tuple_head< std::tuple< T ... > >
head( std::tuple< T ... > & tpl) {
    return tuple_head< std::tuple< T ... > >{ tpl };
}

template< typename ... T >
detail::tuple_tail< std::tuple< T ... > >
tail( std::tuple< T ... > & tpl) {
    return tuple_tail< std::tuple< T ... > >{ tpl };
}

}}}

#ifdef BOOST_HAS_ABI_HEADERS
#include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_CONTEXT_DETAIL_TUPLE_H

/* tuple.hpp
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
*/