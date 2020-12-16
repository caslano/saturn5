
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
YY2khrCkf1/zmDEe7+t2r53zO9TSl/kX+KD8HdB9NuO9a2obWuOb1A+XcHqCdXQnEFZAMOdWdZ/VCO4zEazb+WwvDdvFwfo6WDaF7eZgbQITvoUO1kuM9V48Hh8TzD3bLrCR7H8JRkdN2EcLLMKyZMKiDtbiwyrkTokPM9oK9wSUNoncLnA/2KXVfjDvSSzJPAPo+9vYQXS/e2+mjmILtqTiXqCfWCPRjTscfYPlk4z+ZWz5uqTD8IXQEN9bl8Ou6hdp8fFnuv0locSmwvIZc3RnzeiYXsVpg6DcXRxiL/3Y8OQw/Jyy5bEvGSpy7uTkHAJvWpXyL2tf8jCCubQRSLszwbCPxXMEpg3btVTfAtCzZv59OR+zrOvT7xzuXjqQPY0rGmrqGxuXxTqSdHvzJrqsgl/cU195tviLD2TOY49S314KjZwfgG8hOVjOIsEdqbgU9x74Phc3uhTn6/TddP7LNlhq3mbfU2gWI3+RU2XdKG3CWMEdp7jk1zZ6wXiQx7we7/sN5lgJl9/dKswee+0j9OYWujQis0lTQt89RubSUngD1szpOlnLRH7Lr1z4OZn1fN73DO9JwjtaGs67kmDYTzlopLxhJDrBvtUEKZN9S3HenOVjumVijwdkyVrgfUFknRpSngWFQVmeVWjmXyXddMOzz+ELv5Toya5Dz5S0s6y8qNcc8s6WtHNAD0ON3Rwgce7b0cF3lhwumTL/SiWs318qzd5vNk9oflloavnnlartZq9PzZc0C0qDuxaHOA97zKeNC5tiq2tWNtatqI/Vr2iKNdY0eds5zsOo1dP8tnIY70l2dBcRrWRLKia7imPslQ+agSDnmrevD3gRvWUrlsRq6ptWro01rW2oUY5EW3hmo6yh9UCNzwuJb1hZs7BmZZM3j2QbKrItJtlIjs5EW4x2Lvduibnpd5UwO4LldPcdBPluXLFqJTX2q+oPrF9xUH3AH+KaltGJ6TVNNfVOQb7OhkA8C756OqD4NIYizoqFjQ0xaikaltUsiq2saWxYUd9Y47Ge8yUvtaLnZKKvtyWdCYSQ9O/4d15Buc1fVrdofhOxdeSbVjWmVc35CMfR7DoVe5KfUDyGQH7CcOrqGcZ08nPyI/uqW1xXs8jX3079y6XW6C0m/RSIfpaqHTZ3drTykVpusPuSqKrsSC7zqjy/7aspzd4fH+GxLSWWMPdhmVNnHHGKPWdN0jcTvIjAGBXgUc/1r0iCrh5P00+lNQ3kMduFkQe/X9benGyP0UMNXho23+3RdyCQpdbBgFaDCwOtJZTPNV5g+SpbHcG/5vn2pLADCXaYl6U47s/s4e5noHj91856kSG3/yl9pdB1pRRpR7E5gHMj9WlfmcffOiZsULieEZL2aIWTg+Arxcc1lvYzJ2PkRL6rgO8q4HuQ4btG+K4WvmuF78GCp2m0nf2a6V8cUur/cHx2qNCIGV6OB44vmwVvHfBqAF6thlecwnHDa73QaDO8VhheHYJ3OPByODgn3VkK86jQH+0iOPY77V61BMTz3YyFWJa0h7U02OcQERpLpN+r/LQMeGQFZWLHww5WY3SwicKcB44PP+u3WfUBYUyTGpGd5kiCI98y09/+uolfYuQ6WsP4Pg+Oqc0cfYTC83COnufi4L0k45tY1/K2Cz/KBmOtY6E+T+2njs7dwfxpEzUenCoTlK5nx6kNidzHM19i4N4ZlLHSCSDLcJUFNwkBqF+5BpjWyXWSyKX3s50scgmqRzCeHx/O85MetAkd3ewl072KjniSaC4VvZ4CeSlGeQi/uRXXpcPj8O3Ok00d/Q7Yk9PjBo3XNRQZF54E/uxMU4fPojDu9SG/yrb3XUl7HKQ92/g=
*/