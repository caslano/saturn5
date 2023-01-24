
#ifndef BOOST_CONTRACT_DETAIL_NONE_HPP_
#define BOOST_CONTRACT_DETAIL_NONE_HPP_

// Copyright (C) 2008-2018 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

namespace boost { namespace contract { namespace detail {

// Tag for "no type".
struct none {
    // Some lib code use this to avoid unused local var warnings on #if, etc.
    static none& value() {
        static none none_value;
        return none_value;
    }
};

// Transform `void` to `none` type (for convenience, instead of using MPL).
template<typename T> struct none_if_void { typedef T type; };
template<> struct none_if_void<void> { typedef none type; };

} } } // namespace

#endif // #include guard


/* none.hpp
YeGxpqPnO/KVZNXHM9WLWsunpxef1YwnkYiHZew2Eo8YIreY2r6OgWu+26K5FQnRp/lJuLx/RBUda6opd/G5upBtGJzrMqv9vPLJiEtabrOC4LXnHRuwG95XaMeW+z56TjyW3pGt2sKMwY380+SUQ/pitYMOxZGjR5O7oyuYWlQ6rjjfvr1Frejamp07d76e/1Q3s6zctEi36RknRmjlEYtg9vGhYxbPLLtsD3Ym1XxqbD7cg7Uuln5eztyff3HYl2Ofikebpv6z9ASmCyRap9Pso/VjxS+fNGcr9nkjE2G5LWdiwMWv9Qa1JJPFJz6+V9ynGN5i71565OV1+iy71ABJnI2kiUGj+VmfjiPuK2mqI9YXIp61j5q/7643z8o2uPmsIngRc8vy7B6MYlXzITryvY20V41JHtWGYozzu67TLVSQ9ZahOHIsKC1dcdjjGhUbWxu495T5ZOn8YEbxRFVVFSHvGEeNJs8OLbQkb/wQtkwUF3PuaPvnjuctJkrCxnNHK+lCOHyt3j2odd47i/HkJosX0gy5bN60jeIiskeybGxNfb2kPi3faBQc23hcVKxvYZhFqPD6nQ3Khy03kZt8ypgv2k8c8Ul3V/Fb6ztrMHHHaTYddBamWdsuQkW64znBo7vZ7LQ7txIIb3QZVGPSlCeSUtwlKDBcKhklYQFiO/UaqoLvZJPU6LNYt6nQbqKWwNx4Tqh/k6v2
*/