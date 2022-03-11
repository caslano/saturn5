
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