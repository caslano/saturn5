// Boost.Assign library
//
//  Copyright Thorsten Ottosen 2003-2004. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/assign/
//


#ifndef BOOST_ASSIGN_STD_QUEUE_HPP
#define BOOST_ASSIGN_STD_QUEUE_HPP

#if defined(_MSC_VER)
# pragma once
#endif

#include <boost/assign/list_inserter.hpp>
#include <boost/config.hpp>
#include <boost/move/utility.hpp>
#include <queue>

namespace boost
{
namespace assign
{
#if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

    template< class V, class C, class V2 >
    inline list_inserter< assign_detail::call_push< std::queue<V,C> >, V >
    operator+=( std::queue<V,C>& c, V2 v )
    {
        return push( c )( v );
    }
    
    template< class V, class C, class V2 >
    inline list_inserter< assign_detail::call_push< std::priority_queue<V,C> >, V >
    operator+=( std::priority_queue<V,C>& c, V2 v )
    {
        return push( c )( v );
    }

#else

    template< class V, class C, class V2 >
    inline list_inserter< assign_detail::call_push< std::queue<V, C> >, V >
    operator+=(std::queue<V, C>& c, V2&& v)
    {
        return push(c)(boost::forward<V2>(v));
    }

    template< class V, class C, class V2 >
    inline list_inserter< assign_detail::call_push< std::priority_queue<V, C> >, V >
    operator+=(std::priority_queue<V, C>& c, V2&& v)
    {
        return push(c)(boost::forward<V2>(v));
    }

#endif
}
}

#endif

/* queue.hpp
JvgUXAWfgQ/DZ+HL8Dn4d/gX+C7cBD+Dr0IfDfJ12Aq+CXvDzXAUfBuWwo/gxXAbvAN+Ch+An8H1cAfcBPfAzfBLuBV+BXfDr2EG5f8tbA1/gO2hz0/+w5Pc+4Ynw4EwDvehMB7mwnpan1J8+m1bv/279ekIQ3itT5SZ1Oci2BUWw95wHjwElsFBcD4co/sxFMAKWKz7MZwOz4AXwzPh3XAh/As8T/Wqnw/fg0vhx/AS6NN9F9LgMtgWXgE76b4LXXXfhUHwGngkXA7H6P4LE+CNsATeBOfDFfAc3XdhObwd/hneBTfCu+FrsBK+A+/RfRjug1/CB+C38EHYTPdVOED3VegIH4XD4Z9gHnwKToardf+FdXAhfBZeA/8Mb4YvwD/pfgovwL/DDXAD3AM3wr3wNdjYrV8wFb4CD4KbYDf4EsyFmx2tb3AyPAueDbfCK3X/hd/r/gv3wQ/gg/BD1V+d6dPvg/odNtHBbmTdm9XT3RG+p8+N92E31dOdDT+D/eF2ldn/B5wAd8IC+IX2y5xL6sdueD7cA+9U2eln4TfwLVjPob3DBPgP+IPqtzbYMcYHU6Afpqn+7vaql/sgmAxzYGOYB1PhyTAdTocZcBZsBhfDTHg+bA6vgC10P48DYCVsC9fCdvBp2AG+BbtAN496wCawJ2wOs2E72At2hn1gf9gPDoIHwxNgfzgNHgpnwoHwQjgILoNDtN501X07joKPwWHwdTgcboUj4E44Ejp++nlYHx4Pe8KJ8BA4CQ6CJ8IhcK/hvPBkt77CKfAcOBVeA6dp/Vhhv73w7UnrRy8j+6LI8anu//IFHAB3wUnQFRE9EebCmXAv7hXwK7hc/a9T/9vgd269hN/DdfCf8EX4A3wF+gn3AYyHX8N60HGoJzAZJsKWsD48AjaAJ8B0OA02gaW6f8d8mAkvhS3hDbAVXA3b6POpHXwQtoevwc7QRz4fBNvBrrA/7AmPhL3gODgQToWHw2nwYHgaPARWwEPhJfAweBnsA1fCI/T5kwPXwiR97gyFn8Oj4FdwGGyi+2pkwFyo5aTvwdxLlHLqp+OwARBjBsJJKjM/WdeszII58Aw4GF6n/jeo/51wGHwEHg3Xw1y4AQ7XNQ+j4TY4Bn4J8+D3cCxs6ATWnrSC4+HhcALMh5PgQjhT9ykogr+FJ8M74RS4BhbAx2AhfBzmw7/CaXADPBFugafAbbAEUldMKcyA82BHWA4PhKfDnrACjoEL4WnwXHg2PA+uhOfDNfACeB+8EK6Fx8K/w0vgx/BS+Dm8DCb7Jf/oxyX/pNyRlSdgXI0y9ZHy9HmlkTL1oqv+/0KuHj3s/7Wy9fff/uvK16+kbq3DbMMkb4sz3TCjMEWYpZhKzBsY80mdfH3d8Z91/Fry//mFpT9Z/t+V7R+QZUxvle1nzys53DHFgbAY/uDqj3tXvvkH5PpHHz3Mqx/Mu3Z9hBMMO9B+550s9tHyvTpNhsChvXnTTTB8X7HPcZ+lYh/r3Zu3sLAgIEeZ5b7bif9RjpXjDqRv0iT9YHg9B3E6wnwJM0rizArFkXvYnObGKZhZVh6S1Zwk/hOc4HzTWLG3dZ4zo+y8wqlbZE7L8w1f09Vv+MCrc0iuqJF+f18m4b4wDeSaVa+Szq/dLH6vi9/vVM4yKANVLn6HSN78NTOQrldWyHUvaiVx5pSre1vokUk9LTj34b5nnirpHeyk2euwW+3adQfTJcxwp7M5QWR9m6QG9v7tBA9QU5IZMBn6bXyViXociTf3dZh84x7jOPKdfPGW8O/kW0zw+7fUK3HbZqDECe0DvNN+O5f6Id/E94lf0M2GlbKgnHGXcray3+QhbuShhmsLyT/cJP8=
*/