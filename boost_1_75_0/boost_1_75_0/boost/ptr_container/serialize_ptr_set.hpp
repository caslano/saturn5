// Copyright Sebastian Ramacher, 2007.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PTR_CONTAINER_SERIALIZE_PTR_SET_HPP
#define BOOST_PTR_CONTAINER_SERIALIZE_PTR_SET_HPP

#include <boost/ptr_container/detail/serialize_reversible_cont.hpp>
#include <boost/ptr_container/ptr_set.hpp>

namespace boost 
{

namespace serialization 
{

template<class Archive, class T, class CloneAllocator, class Allocator>
void serialize(Archive& ar, ptr_set<T, CloneAllocator, Allocator>& c, const unsigned int version)
{
   split_free(ar, c, version);
}

template<class Archive, class T, class CloneAllocator, class Allocator>
void serialize(Archive& ar, ptr_multiset<T, CloneAllocator, Allocator>& c, const unsigned int version)
{
   split_free(ar, c, version);
}

} // namespace serialization
} // namespace boost

#endif

/* serialize_ptr_set.hpp
efTw+v+jqntkeHAkncnkAnz7DT9dhw2sz8kFzysoDuxFj4vidt4nkfNm9sqBNie7+j0V5PbSygH5qi3L0ve7GEIsaUGIppSICSLPyirF0F0Jf0OIFpwNV1xwRQr85/0ljgRLX0howLsaUF6HVQp6joU3NVhOiPqmuLH/yUZ7qwjWSSe70WhifWDXj/kNG0kPDvCL0KXH0Tk/e+tqvkY8W3RkOEXHzEsIKaWBROdNS8qVp9BS/PQGYEbEqnPYkHsVK/8QbkwfYIOFQgMIOCPgzzfRaUWrvzvp914yJ/MMju8HaqhvYvi/S+5bvuDEvZz0gPGsF5fzsFvWciXpTLr/gKxjq935pn2xEEtZDGN9999fpVm/QWOYEYtYgIEREZELkV3TGP13gsTvy+FwDrpEJDmPpU+q0jen/kwx+KPVVPug+ipgVApttudsj2EXFOmXmpKAh0wJ1a/LMDP7UVCkdS0kB3w30O/lwVxgz6kXjeaX+H1c9T6weZMluXHmFEYAPYzJDXKKVnjjjj8kHd0H8tcsCElAVc2b8vaPoWR+WCCJFjL9Q1XjASVTaugK4cAVNFrqVR6aYh/g4XGSNM8lzCh6qK5rdCg9khHA1J1BD4gKj2Qi9hRor741AkpjxVdJJDWE0qiSzrP5mzi6IDshKYBrQX1Bc9KKGGshi26Sk0JqjtDqDN4ep6QDPYTwMQjXiNRD2Otw6dteqJG+
*/