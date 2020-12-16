//
// Boost.Pointer Container
//
//  Copyright Thorsten Ottosen 2008. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/ptr_container/
//

#ifndef BOOST_PTR_CONTAINER_SERIALIZE_PTR_UNORDERED_SET_HPP
#define BOOST_PTR_CONTAINER_SERIALIZE_PTR_UNORDERED_SET_HPP

#include <boost/ptr_container/detail/serialize_reversible_cont.hpp>
#include <boost/ptr_container/ptr_unordered_set.hpp>

namespace boost 
{

namespace serialization 
{

template<class Archive, class T, class Hash, class Pred, class CloneAllocator, class Allocator>
void serialize(Archive& ar, ptr_unordered_set<T, Hash, Pred, CloneAllocator, Allocator>& c, const unsigned int version)
{
   split_free(ar, c, version);
}

template<class Archive, class T, class Hash, class Pred, class CloneAllocator, class Allocator>
void serialize(Archive& ar, ptr_unordered_multiset<T, Hash, Pred, CloneAllocator, Allocator>& c, const unsigned int version)
{
   split_free(ar, c, version);
}

} // namespace serialization
} // namespace boost

#endif

/* serialize_ptr_unordered_set.hpp
9t+tf5xfoqXa3DsUpVEd5a+1eZhGAtzyVU06kbc0PPTD+3fm4wuvXfS3e2L8ezMmSOdfL9JkLJLOuwNpX0pLS1lNRrSmVyUy5sNPFOunusvofpvpyzXIOsT4TmFdl8TQmbIxoxnxJkw3GUNPL6QZ2vW8RThOao6hM71H+2Vx57BaRJz6muakqXxatn7YImt+Kh22p4kr44XppghjDFnDEeLgmBZDe8Fv/DQRV8x9pM+UGj/DMCad5/L+ch2VYZUYr60wYdxro0JsFVgqVVfDsS173pnowSAgxAtCnWMGddJnwtdCLUemLAw7kDhy/4i0i4f45SlPz/6ky3moxjPv2DgswNDpLfXyrOSRaZySMcyQ59KODsLaUosaF7bnR/jqAOdEp6/OonwPDnBuZotoj9OY3Gcn7Yw9fgjuzkvvVyWuHCeUi3LbYQ1CP59AGOMwc823vhuX83HR2MHiCeYh0PA5oh5+mnMC2S5PoBDJILrD1JY9MQ9+kpRZTYRmEG22hvDEskBiEk2B/j4P7C/TmGf0360w+vsCgz3sRtilBjt3HbBu7tGpq43zwS6N9cGu6m/NS4r7sK6xwrSDIvrbdf3te3v0rFq0T8DwRU8cGxsfXGhMu4n9/9Cga7EC/o7EugzCeDotMpIuaotTM+cosc+wCNtkzyciQ745TMvmDaafN9jzzvKtB+EfynHrLf1j5l3NhJUcQ90m6OgxGTb1disNM1BS9nixMVxeF3bkzv72ek56sYW8Y2hMYHqepr9YT2OgFWzJiMLvscL9DiDPJtzXP9hHLrGHwMzek+gtBzAxVqKGrFlasiIHUIOz1sTI3IzAtIdLfnKdqL7FWmoS4Y/bPqzlbz0lw3VHrunAq0EDR/uZnxE0UWePZOsBwhl3mAOY5C1kt6Qo3GjNQRdaVu6Fe4F4zAlqfTQ4+/0KceGwHzuS9Zf723fG1qSa86P+96oI10GaKLBw/ax1Hr191cyKhGGvm/pqnWrGHXKvlWZ2gBtTK96iMHHxVeQyZDr+30R4dEgkKvvbwoew0whp3hU0djph33xP0GQ/ARH5ph90np92yGR//6DTfCEVfs5l0IXz1WY0lM7vw8wxU7ROIPypkPZj6YP9CO3fM2lHpInRiPp6FtFG/7DSpc4Za/yfZeh3PeUoNvhF/Pi8vxhfSq9e6+lIpr+w5DU/EezWlz64fSZAHk8I87uPvh5O/JrJ3YgVZv/dt+S1cRV7YKDv2S272Zaixzdl7219I9Zufmd4I45Ad3o/dL5/Ekr4A/8kLoi+iE7qKDVA4+b8anqjuh1uJFiczY2NT/CPxA8zCOvkEu7vaTaLg9rM+bz8BXjtbB1d9erWfRLwMmuv+EexfFx3gHhXAKdN3p2wnimvuGNY8s/0Zzgvwr429/mj4peYjR5p2Vqf9Agzq72ZryTZ8eU+kTD+hsRn/07muTbtn8fT6GYwJKKdJY25+tqniHTWxgMs/z8zx3Q/6GHTiVylDtwwji7mTu5NBwi5td4T6CnDUtky3VvXqTYxa850XZm0P9Y7wC2GfZIVLpllfN9+pPmPOcHbhb27J3fJPbPkzu0VJ3eDSRtqI0PM0Qt9tiVh0UQeGlzfT0LJGBeUFkd83X6AuItZvy1Q097eFpKJfWHQ4Udr106/hW3NP4+0w42nHeYzuvPytK8Q601jJJ2h0TeairqNiy+zSUq8owKdrwaM6k3Hnyjj229ECP7e0EOUxdp3OIk08NXwasxgWchZEWHhgCOgwIkWvJoi8w/DRb6lJjwubtkAeTa/EgKO3Qn9WO7XGXWi1/+MYpDzVzMJT2gL6IfWNxp3c2G4KCR9hErZX0Ijj4wGNjhKc3YcHWU=
*/