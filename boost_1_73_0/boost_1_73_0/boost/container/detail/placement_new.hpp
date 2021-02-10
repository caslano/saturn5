#ifndef BOOST_CONTAINER_DETAIL_PLACEMENT_NEW_HPP
#define BOOST_CONTAINER_DETAIL_PLACEMENT_NEW_HPP
///////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2014-2015. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

struct boost_container_new_t{};

//avoid including <new>
inline void *operator new(std::size_t, void *p, boost_container_new_t)
{  return p;  }

inline void operator delete(void *, void *, boost_container_new_t)
{}

#endif   //BOOST_CONTAINER_DETAIL_PLACEMENT_NEW_HPP

/* placement_new.hpp
/bEfzyzPyAb10E4QYzAdxXfTAL5447uRNaUKp7OEb8dn7SBux4pWnmyqStRKS1RP/tbwLrgJwvsgCU1zaicuVCsmOxqNwBtHIY6kz9PDsoCNGnTAPlDHtxdHKmbe2dZ/UEsDBAoAAAAIAC1nSlKJGl53KwQAABMJAABCAAkAY3VybC1tYXN0ZXIvZG9jcy9saWJjdXJsL29wdHMvQ1VSTE1PUFRfQ0hVTktfTEVOR1RIX1BFTkFMVFlfU0laRS4zVVQFAAG2SCRgrVRhb5tIEP3Orxj5vtgVwU5TXS9tWh1xaY3iADK4qU+W0BqWsHfrXY5d7KTKj79ZwE1yjZR8KJYNZmfmvX3zZp31AF79sstyTDl49krbb4oX3g9JUS3/ppl+OiFN76D7YOIa7y+AGsN91l06ghdl3cGwzUp7rDPznKYvgFsbkuZnbJLXqXnEN11mnz+V1W3NrksNw+kIjk9P/4AjeD05PrXhExGMcog1FRtaX9twlrdv/izJzY2j6EcbqAbCnUcFk5IpULLQe1JTwGfOMioUzYEoyKnKarbBP0yALikUjFOYhtHKD77YsC9ZVvZ1bmUDqpQNz6EkOwo1zSjbdWUqUmuQBVbA+jlTGms2mknhIDwFTeut6ssYEoQrCWRHGCcbhCMa
*/