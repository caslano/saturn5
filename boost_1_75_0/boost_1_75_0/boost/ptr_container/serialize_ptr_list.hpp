// Copyright Sebastian Ramacher, 2007.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PTR_CONTAINER_SERIALIZE_PTR_LIST_HPP
#define BOOST_PTR_CONTAINER_SERIALIZE_PTR_LIST_HPP

#include <boost/ptr_container/detail/serialize_reversible_cont.hpp>
#include <boost/ptr_container/ptr_list.hpp>

namespace boost 
{

namespace serialization 
{

template<class Archive, class T, class CloneAllocator, class Allocator>
void serialize(Archive& ar, ptr_list<T, CloneAllocator, Allocator>& c, const unsigned int version)
{
   split_free(ar, c, version);
}

} // namespace serialization
} // namespace boost

#endif

/* serialize_ptr_list.hpp
4lGJkcvjs9uqPnn8XOL+rWlp+vKL8741+VZYb95Z6dae9W32eOs7dN28Cv/ZjYatgnOUVeuEUxkXfdZP11Aa4cQfbfpWUSVhccf568fiTBsXeJ56d5rx9PRT0dAzptmhuVkhamHuuvEbGeYujXuP5UgvXH9o8qJcKVNJkzVnnI88Ur57+JTSLnef00tP+TRHrj273P7IQ2WFgug91abdBzvP5lgf+qWy4ZjVzB9F+bsVli+Uq/yl9/ZGz6/k7x8+PVRSerTcLY71rXkZvIkvMxMPvLQ6H+93+qWVcffQyQEJnz4vizvdMTP1FE9Q9+bpuoUlZht+0T7/etlaYuUv1FH89/r7Hcnn2wxf/2WVt9NgUPdu1eIq9R+MM5ceXZjLXJzy67zTaoM9VV0H6EIdmalZyw/96qq9FLL0wZkDjXPu5HamjbwdKNzMrK1YY7Nc5+avv7e3uOU/9zlZEO/3wd0kolq/4+WktksWE3pU2IH7qvaUTUGUM9pDWb987MPDouhhUfO8lkTQmb66caEhB7a5eJTpi9ocT/uc4eQ7S1/0/ikRqzEagvon0g5/Cdc2GeS6udZQ2/kV/4vyjI4cx01pD4NOHVQYIRX/OKW23MOrzvv4vS8b42ovPhL3Pzk31JrPfZvHcBP/60rKB/bHCM64VyoYoVn9bYF0Hv093f2D7ZcRnzJuLa2Jv15X1DjU/ujMqruHcuvf0qfU
*/