//
// detail/impl/service_registry.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_IMPL_SERVICE_REGISTRY_HPP
#define BOOST_ASIO_DETAIL_IMPL_SERVICE_REGISTRY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename Service>
Service& service_registry::use_service()
{
  execution_context::service::key key;
  init_key<Service>(key, 0);
  factory_type factory = &service_registry::create<Service, execution_context>;
  return *static_cast<Service*>(do_use_service(key, factory, &owner_));
}

template <typename Service>
Service& service_registry::use_service(io_context& owner)
{
  execution_context::service::key key;
  init_key<Service>(key, 0);
  factory_type factory = &service_registry::create<Service, io_context>;
  return *static_cast<Service*>(do_use_service(key, factory, &owner));
}

template <typename Service>
void service_registry::add_service(Service* new_service)
{
  execution_context::service::key key;
  init_key<Service>(key, 0);
  return do_add_service(key, new_service);
}

template <typename Service>
bool service_registry::has_service() const
{
  execution_context::service::key key;
  init_key<Service>(key, 0);
  return do_has_service(key);
}

template <typename Service>
inline void service_registry::init_key(
    execution_context::service::key& key, ...)
{
  init_key_from_id(key, Service::id);
}

#if !defined(BOOST_ASIO_NO_TYPEID)
template <typename Service>
void service_registry::init_key(execution_context::service::key& key,
    typename enable_if<
      is_base_of<typename Service::key_type, Service>::value>::type*)
{
  key.type_info_ = &typeid(typeid_wrapper<Service>);
  key.id_ = 0;
}

template <typename Service>
void service_registry::init_key_from_id(execution_context::service::key& key,
    const service_id<Service>& /*id*/)
{
  key.type_info_ = &typeid(typeid_wrapper<Service>);
  key.id_ = 0;
}
#endif // !defined(BOOST_ASIO_NO_TYPEID)

template <typename Service, typename Owner>
execution_context::service* service_registry::create(void* owner)
{
  return new Service(*static_cast<Owner*>(owner));
}

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_IMPL_SERVICE_REGISTRY_HPP

/* service_registry.hpp
5R9kymCdhPO946KWwTUSP0rL0JIf0FoGCY6L6/vENy4e6+GdI/yc9tHg0lenB6qrY34Ar3N+8FJO8PzgxRzn/KDBo2di84MWPZdHtRu+Rk+f7tA+cBNUxdifNdLo6Bh7jvT0jj3zhPfdqrPKBo89xDvHnjkSXhE49syS+GtMH0A+6thTJPEbzdgDv+d99KEE30eP9Gz78WdZT+/76AURu9GtZR/Xuyj8jnfRvxO23kUPnC9jkLgiturrBPHmXVTkne+iD7XBuyjpck3SdYwhJ+WMPn1a+9S7tb3ljTI6c9b0asYj0+x82x16q8zwoHam8YONT4dLJVzMeaxO7rZm/FlcIjwLQwMtf1nmPoPc7c34GF8g8bPx4dXNanPIaN81/oFQyeZv4gqJv9CU+XDK+6P/pvbIWODwC7lF5wnl0GOR8c5WN/os9Picpj7gc84R/iLhWUHPQvidc4Q/SbgkcI5wRMtZ6wV55xzhxQSehRXiqzrxOYLVd9P68J+eqczW97cLI+9to01ZmedgQHnB65ofSHhW8PxgtOudTcJTW/VP8Dko+gc/B027OKW6vl/77DqogXYRyjW62p+B6Ol4BirfINPHBkm4nPOfSV5/voZ/gPHnMkDCZVzpZsbw5N7om+DzkHwFPQ/NN1IHM9S+DdRd+8Ek6rUu13zfULx4RumGys18HLWAUYqh2ToX/7k08ecbtp2LV7nBEj8hU8awjcutOjXx/c25+NVxnPO3xl3SI/+Snhl3SYNrkoZj3P1aX69ehejVFKTX6rDk+Q6pGwJ2G9UxdGpy6VSZgE6kR/5Xx6VTdaZ/XWWNsetUXnr5zAWzl0pFBdcTMsE6Sfw7U0+l/fzrqcJXJymnwHqqiK4T8e9MPQ3t79VpcqRPteo0e5azSwX3J5tO+aLTqhUM2K39qY3rKV90kjSc7zE+Ok2N9KcAnSip4P4UQ6emNq6nIJ0ODPCvp6yxNp206cUa95AJ1kniz249Wc/pXQP966nCR6fgMQ/+6PoQf3bryNKn9jzvnGF6pC+16iN7OjHqB37nnOEhwtacob5l/XqSfR3iu2MdcwbknXOGnzJnWBenr8agOiRdrpGu6/2jZpBX5xno3OzSObj+4HXp22VcdH07jXPq2+yjbzgBfbWOo+o705oXnu9ts7PQt2icQ9+C8tLL5l1RTsMVb1hS44H1jaxpv0MzRd8CHFRb+hHftv2RNLgmaTh0K8jy6jYb3Wqi60bBBY+fNdF1I75t+6ZLN9M3Ow/26raQmzS4dIvVNxts+vTu36KPw79oG9cVaYg+7n530EefuYX8l+fSJ7jfwRtVF+Lbtm7cupjnwBCvLldwkyKjS3zviUWqT1fiB0pbW27pQlzb1EsP1YX7c225Q4+V2V495kX6j9EjvnfDmkA9iGujOvHRw7xr5A31r48Gmx6uSVZwfwnUhbizWCeWLqeG+tdJKN9Hl+j1gkygLsSdvXqZZr3XDvM+axegS1GrLpclMv9FzvHcXUrYeu5OEv02bFxue+5eke947iLvfO7+ZsSZv2eQLtdI173vO9yr+8XoXmvTPd45cq1L77tj6L3HpXetR+8zf98I0vvoCP86b3LqvenqtZUrYszPkHGtRcfQ+4RL7yaX3q+cxfpuyvGv77zxXr1jzOGQceo9j3A0vecQb/QWeZfeZ7G+HxjpGq+0vmtsese7biIy3MFPzwUS3zbjbyydbh3l0knrssGmU7zrJg3RdSK+bcbhAJ3Ms756tLd9/jwSuMDjrz1an4Tf2Tb7EXaeVeLIkK1tZhBv2qbIu84qtcFcj3S5RrouncO5Xp0XUY+lXp2j9sdSl86VMXRe7dK51K1zG8z3gnQ=
*/