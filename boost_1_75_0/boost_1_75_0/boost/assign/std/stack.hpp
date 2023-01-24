// Boost.Assign library
//
//  Copyright Thorsten Ottosen 2003-2004. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/assign/
//

#ifndef BOOST_ASSIGN_STD_STACK_HPP
#define BOOST_ASSIGN_STD_STACK_HPP

#if defined(_MSC_VER)
# pragma once
#endif

#include <boost/assign/list_inserter.hpp>
#include <boost/config.hpp>
#include <boost/move/utility.hpp>
#include <stack>

namespace boost
{
namespace assign
{
#if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

    template< class V, class C, class V2 >
    inline list_inserter< assign_detail::call_push< std::stack<V,C> >, V >
    operator+=( std::stack<V,C>& c, V2 v )
    {
       return push( c )( v );
    }

#else

    template< class V, class C, class V2 >
    inline list_inserter< assign_detail::call_push< std::stack<V, C> >, V >
    operator+=(std::stack<V, C>& c, V2&& v)
    {
        return push(c)(boost::forward<V2>(v));
    }

#endif
}
}

#endif

/* stack.hpp
sIWSpqTxR8Am/Z8Am5UwjRxH/bv6cnaiOsjG6OpNN94ZELKJ2dr3TrH6/TOaP7vTdfC9MLXuhUbrvd8cv1WXXl71xMjweSmVO2fq9cN2LcuIWvRr4u4dW54P39o86Zlxu8HoY9d8yvQ5vnJRYN2X3uGHok7W/bXFmT2JNzOKLnNZGZW3Y0rL9o/mNFz08PGD+79OqMRpO6IWFERUHV9rxZiAWddne1R4dL3189Slx/JLrpzR+kj5M9OT5tQa2G9huecBBRHne5+o8jamwsll/1d1XwFV1ba2TXcj3d2w9qaluxsF6ZaUlBbYW0RSQro7lC6RkBJFlBZEUloQBAlp/TZ4VPR47jn//907/O5gDMaec40115pzvfN5nveZc40V2cJS7WN5WTZXq/dgJU//8lQagpwsj+nOePlLKPjacX4C4cI7u+WSXM5H3Rx4ONZ3UiZ2cw8JmNGtheI/+NIoNw3OXn474J1IavSMn9h06i6V0h2uR2V8spTv8YjI4Yyn+A3p+pKfor+/hROp4YRDqC7mz6aY7ja47djTvuaSpxendyM+KptCEdFgrz/vKoZHgcA6Fw9J95KbIMGOc5XoVeiBdnUUL7E1NU74FN601Y5zn/zLYZIVn8dItcNHnDM04ZmlGEeELJJlCwezJYHyTahmCtZmkuqV0mvq6zWePmMYfOhOlEEgmjkc3anFnKNFBbwyq+TPmsTc/q3I
*/