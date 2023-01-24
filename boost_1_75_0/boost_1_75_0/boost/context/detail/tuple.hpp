
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
l9GE/rz3Tgjhvff0ej1/cHAATU4kJgLEDLjwfZ/IuG4LADg3EdeKTNXeulxphVQBURONdAvPGlM7o97FVIYyW6BvbCGu3YOqXiQ78gXkgcIuxqz1RszrCm9FjOfHAhMTQTsm+aACqHhjcdIiNEGoLSGlWK4hlWQ+t8Gci5ZKEngfZofRBf2m40xqNUX08aFj9kfhT6x/sgq6SUEpnbip9guWBKnIx0Uz34TZAQEE2r6CqZDIOtuE/FLLqdQ8QOCxdU2ueuxd94yeuZcTZ2ZcODjfDFs1MWQpJVgVkn5cCc5b8p7iyN6DTP7oQ/TurOjfXSKmPcYPX6SaZmyN3x5v1RrNy1qyWcmCEmJJMfj4mYjTdAWhqab3nrqu2LlZcuPmTSCQuFmWkeUKrTNObo54/88fRxd3keUj8izHek1ZlnzhG5anv/4KX3wGXnx2m92b27jJGqgcRlswuBehC4TMQvSh2gazD2YHX++S8hVA4JykN/I8/OCQqrJAE/qLh++F994qpdI48KT5kxWwx19AK7C0bgsAuPcT9+7d+D9u1M7YXOU6xHc7qZaH8oHJDSPIxmJqkGrB2jjDXzvKscsfZXDsAu7VB+jlOfNFhRCaRDZ6J4IatsQYf2TYo2kmfCvUQoQCGh/dE5l6AUTCsm0x5eL+4wFKGvPaRwY8kH8dkxta4Y8EYBL+RuvH95rCoeT/R7AI2j1pe3AmJAzZ
*/