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
D2VPDhcgTJ1t0y9tqgEwg60skddl8wpys7U3w+2ca7KgYEtPFXNpGsS/qRqf22qKANdjtmdxkW44FiaafgpnvJq8R5784W+QN4Tz0epC8ZvE6lEoOxNtCuizQ2PQxR1vSK6Lwv1loSU2HVObrt9qJTi8HoAZtDwQafR3TH3wNE2+i5dDzeVSDTAgSNwaRNGfbF6i2JSbAQAh1H7NKLpIVwSva9rD8YsycrNijIKti+/j1a9VI5NEqyn/FrNa7UyYGzW9TE6QldAgfK7tPi8nhSS4Vcpno3Y1UkYpXYK9xN05byozrK4q+EYXomIZPzGNd1G4hcvq6z0eIuPPm5auw/mIuRXo1Glo16I/rU/8sDnmFoHvY1FdXIYN5tS/yv4ZPwLthj6wWx7jMvMBZ3jOd7ZNJcY1cAC+vA2Hn6PcRzSZ/Ql7JKr4UzpU2Xn3za/q2KGf7I7wqx7QVZakbBm9ID0NyKWzHVVMk3Qk0+t9z8eWeTtyKiavGfBlEjji3ySVRfl0NA3C/pOOX54XK0SY//4+nnhhboCSTTnvo+d4xFutLggKIkdbv191Mw==
*/