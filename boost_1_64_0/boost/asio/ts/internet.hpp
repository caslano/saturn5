//
// ts/internet.hpp
// ~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_TS_INTERNET_HPP
#define BOOST_ASIO_TS_INTERNET_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/ip/address.hpp>
#include <boost/asio/ip/address_v4.hpp>
#include <boost/asio/ip/address_v4_iterator.hpp>
#include <boost/asio/ip/address_v4_range.hpp>
#include <boost/asio/ip/address_v6.hpp>
#include <boost/asio/ip/address_v6_iterator.hpp>
#include <boost/asio/ip/address_v6_range.hpp>
#include <boost/asio/ip/bad_address_cast.hpp>
#include <boost/asio/ip/basic_endpoint.hpp>
#include <boost/asio/ip/basic_resolver_query.hpp>
#include <boost/asio/ip/basic_resolver_entry.hpp>
#include <boost/asio/ip/basic_resolver_iterator.hpp>
#include <boost/asio/ip/basic_resolver.hpp>
#include <boost/asio/ip/host_name.hpp>
#include <boost/asio/ip/network_v4.hpp>
#include <boost/asio/ip/network_v6.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ip/udp.hpp>
#include <boost/asio/ip/v6_only.hpp>
#include <boost/asio/ip/unicast.hpp>
#include <boost/asio/ip/multicast.hpp>

#endif // BOOST_ASIO_TS_INTERNET_HPP

/* internet.hpp
f8wnaKcAz1+4s/Mp56S1Pyk37fOU6y+GCZmdh2or+b3GdcsW9mtOTOR+LZ0RgYfYvn6S5nb2cyCPlpbvMaXsv0Bcrn5PyRf/etIG9zcLNG3PCq+BAna/Jki6TiqNslp2hyUsDRzro5wIf0/+9mese5BvyLonnNez9FqoVPw59IMm6rroYo5Txzr6TLS2GzUTtM1io40T3zsjzwGmqxa299wrLM4+Foz7RfPd+u6dRT9obO8Fn9QJPwv+Od6PhvvbW4gdZAx2y+Yq+r4yaatH3VceKfFVz9CWHGtbOFZShq2u8+r6qZdTNt3KfdRl/rqax6fPunfqp62qZdKD/rSyVj3DfirTZYCGe2niv0bWqSF6EFqWHQeN9ZtrdpzpT45ob+VFob1C1iCnMSY+tPU9WYM0infHxju7RluDkL4x6N8PW4Oemx2Wiu77BuZKzvnh+9o3II8CaWcZzt8HjuIX9Ovft0fv7hb7QNe3DLPbwXTcs2Y7oz+nc2zyGfnRDoe9jt9FqOONoC2JVkfaPIhWxxLWkbJQnl+zGA+e1PF6DH5mG+x2IqUM2/OkvF54u64y54JulyzPudaXZZ/UeUh4m5gmw6L/VPE6D4nS7+vqh9dvM2i3RqyfNvQWtY5bg/3ObxMwdGl9VzjDuIwLxlfQtkb0NnJc+I1C6sBnf9hY6b5Izw3vi3LkeTByX2iDXXr/rQI8ZOWN7RHK24DyTkcpD5NS+m19hH4//Qvm5PoovLGkQXj9NoI2OT5S/TghVbQ6Ml30OYn4nz8n11dgTrZhu3IbhrfrVqRvFtIuqw7jwvD2gP7nz8eFur72ujVuFF63m0FbEFI3zsSodSuw9LU3bB4yPvo8RPzPn4cLI4yFtwLzUMvMCH1wLfIsCekDi8m8c56Dgf5u1Ti8rK2mfA4rC7OPvLAlvL9B//Pn35YovOBqEl63baDdGlI3zryoddt6lnm39RfMuy0VmHeBcV0XoT33mvJVtyfsE4jUeVCENh38BXNvUBR5t7VpeP2WgvZ0xPrpZ2GUOjId+z0hwhw8fZY5ePoXzMFBEcYloQJzUK8ZLwjvi3tM2Z8QqS9++bNwV4TyHjNlcuTy9LNwe3i/I83Pn4vbo/DGmmbh9SsFbUHE+tFoZFT+ZTrqhiYLb5jkdruQBSHtGHgO7dDjb3lHSJbx1+XY2jereXj7dpoyN3L7KHGijQHTRZc5iP/5Mmd7BWROQIYObkmbBLTndwpuninf2a6pJbpRYhk8OFdLp44Ktof0qXrvZK343xD7flvg9sBloxXz0I9FLajTXnZmnfbGialmKv3eeTn8YTrtfI+tL3HV6SctbauzXJz1pn73OBTqcnmc8S5vJB3v76TucZK2KdP6Wvr18uI9teLisPORZtoijInzxtX1/2fmiD0Q67dZ9lX4nQn7Jf/71TUYh3I4sxzecyB6f8My/O7FCuyJ2L/rYUxCvjXktPET/w3lJgNPA9eYz0jpn7JpmIVTJuE4i+K+eI58NxgRfDZyDDI4rvvEf8J4FppNr8Ml0mY00pgfS2iXjelQ6lZYoQjYahuehDD4XbAIxW8w5KNg37ws6d415kLv5UjwHgrml8lvo7CmluyvVxX8G/yeJ1pA+ntetpQ30+iGMgPPjNUSVps0rBMsZyTAakW20ECzR8L2KS905GaD31aqdPs+DXWeGwpdkdHHSLHET5D4cWZbJH6OuhLpz5C3RQ+LdqrJ/5OE1qe/GV8vfq9xnnpPbGQOwzhub80zFM78OA9sZDYyGTE27BuX1nn+SfpxtTGS49LTMi5e6AVG+/ZlCE1V/R0m70z6p7Q3lyPfXEYIjw4Weymmn3xCndTcZPIt7dCNlXI=
*/