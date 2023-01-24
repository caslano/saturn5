// Copyright Sebastian Ramacher, 2007.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PTR_CONTAINER_SERIALIZE_PTR_DEQUE_HPP
#define BOOST_PTR_CONTAINER_SERIALIZE_PTR_DEQUE_HPP

#include <boost/ptr_container/detail/serialize_reversible_cont.hpp>
#include <boost/ptr_container/ptr_deque.hpp>

namespace boost 
{

namespace serialization 
{

template<class Archive, class T, class CloneAllocator, class Allocator>
void serialize(Archive& ar, ptr_deque<T, CloneAllocator, Allocator>& c, const unsigned int version)
{
   split_free(ar, c, version);
}

} // namespace serialization
} // namespace boost

#endif

/* serialize_ptr_deque.hpp
uJpdMlfTJOVP+17Y9F36wZUf0kdqctd616+dNVGv2/TTTYMjo/gNPp7fE3tqxX3P9OKXaW1BwuNWfYqM+PozrXX1mZmDE7u/uy7YqBY7wvJwwXil4Tf/rrR4vmXDX69e7Fd4/HTLMGZ+ac+I/MnTjeX5q1oPn/pQzWdfNTwjxjHQzuHB9VLJ8g9ijq+PDa8f7vSxK+ls4HXf4fVimsdvpV1NyM38NsNi0t0rjoYCKmF6RSl241Kmy+XSDp05sq5rw/4LVoMTOg9J6e38vH/mjSVT2u6N/zqhSagiodN/zb5VS5yfTms/e+Zx9bHQvHBZm7Tt4YOOyERP1qkrXHtwhq5602GNedJ1dhmtFuMdiu3bbjeNaMl7M3Rb25avYgZujlerxbKurUrXH6/L1CwLTD8766lnt+BHh82tYifWSCZpnk47HnR90FGRx+GHGjItG3g1j/jejTqqfSGgdcugplTZwKjZMSszDestNpVZ7RC6ZSFvdka+QO1b1FDXv0YVemhWvtQq3GK5rOLogXG7jGOrfb3cNj5wiN3q2OMzwsanee5T53m5Md3jlvGNuRfTHXtut/IeX/OtP0XEepSfrt/a8r1DyNR7zPA9Yw6tP+d3x/Wu05PDg7L/mhifkzjZOql8yWCZN2YF0sv3dflJ6gq9bM/lqaJ9XO6zpm75bo+fZuFNP826yi7ZV4svn5w9+1fu+1Yn+nrrES3J
*/