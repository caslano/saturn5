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
pbDfEUGeeovUGkJutUDBK1qJ38Mc08doQDbim1sL9TVgcxxWS/pGxu5uKc/Rps4Z1qQEaIzA6Zk1+atc60C26gudX12X1VrDFNu7et+gyhaJp5n9dkO3qzPkGhdGA9SABoqccQ0UREF49UNp0yaBKM/XuM9BfKFUHa0W2lnYY8uA9+Bv3BPIyhmGqTbTqspfxPdNcDtrtYb+uXctfF9NlZsRaBRbWi/y4oLWnpcR+JDFVLgFGkgwnPwcpHicf2YYlRWHNka38ls6XobHbDYSIbeGvTbEwP3KLKosMO/E0Kryd/4OcY0VXTNWU9x//1txxm0Eap7G0bvSZs7tSTdiYr8DWs+rtwhd3C1vC23M09UVdgi3B24dW3llIhtHriCHNHX7HAeMWao7E98yYDIcA05xO6YmSHq13iVe8pjAl52Iy11EG5ePO4opYrm7QuutcWMUuXibxHuoF3y7ilRWXfXq4mrxZQBn7zqIfQ6H6Q30EAO5Y9b5F6SUdCT1bNYlYh7lg3a7u0a48qqjrKMdVB/0iQgECKuDAbJEpUvZ0kZJsV9Iy5m68K+dJA==
*/