// Copyright (C) 2013 Eurodecision
// Authors: Guillaume Pinot
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/property_map for documentation.

#ifndef BOOST_PROPERTY_MAP_COMPOSE_PROPERTY_MAP_HPP
#define BOOST_PROPERTY_MAP_COMPOSE_PROPERTY_MAP_HPP

#include <boost/property_map/property_map.hpp>
#include <boost/type_traits.hpp>

namespace boost {

// A compose property map: make_compose_property_map(f, g)[x] == f[g[x]]
//
// g must be a readable property map.
// The category of compose_property_map(f, g) is the category of f.

template <typename FPMap, typename GPMap>
class compose_property_map
{
public:
    typedef typename boost::property_traits<FPMap>::category category;
    typedef typename boost::property_traits<GPMap>::key_type key_type; 
    typedef typename boost::property_traits<FPMap>::value_type value_type;
    typedef typename boost::property_traits<FPMap>::reference reference;

    inline compose_property_map(const FPMap &f_p, const GPMap &g_p):
        f(f_p), g(g_p)
    {}

    inline compose_property_map() {}

    inline reference
    operator[](const key_type &v) const {
        return f[get(g, v)];
    }

    // return type of get():
    // if (reference is not a ref)
    //     value_type
    // else if (reference is const)
    //     reference
    // else
    //     const value_type&
    inline friend typename boost::mpl::if_<
        boost::mpl::not_< boost::is_reference<reference> >,
        value_type,
        typename boost::mpl::if_<
            boost::is_const<reference>,
            reference,
            const value_type&
            >::type
        >::type
    get(const compose_property_map &m, const key_type &k) {
        return get(m.f, get(m.g, k));
    }

    inline friend void
    put(const compose_property_map &m, const key_type &k, const value_type &v) {
        put(m.f, get(m.g, k), v);
    }

private:
    FPMap f;
    GPMap g;
};

template <class FPMap, class GPMap>
inline compose_property_map<FPMap, GPMap>
make_compose_property_map(const FPMap &f, const GPMap &g) {
    return compose_property_map<FPMap, GPMap>(f, g);
}

} // namespace boost

#endif // BOOST_PROPERTY_MAP_COMPOSE_PROPERTY_MAP_HPP

/* compose_property_map.hpp
Ly/ASGV9wAx/FcXWln0OcJV5hkm7+Ur+5h6fhQaXiYsfqrQw43KXa4tX/aiPrj0o/qD3wbkeUppGIu6WttWn+vM/C4AShVM7tB3BaolyN2hhHqQLH77KfAzScK9t5sYfvrbSGBe7li8KHcDaX1KbT0HhqTU6YyKTONig5rxGW/iwY5zs4WrUq1W/XxT1x5zenwMkx8aD2rOb/TIWNXCzkzBVyf0xdKDJU4q/ujklixq0Ea8xm42rFGcK6v/LfVHKtZmfBg1OKX1wq4N9sRx5EOORQM7kuM5uavyyjca6abkhIDLVERYZSz/LyzJQOlTKIv8/rgsi6OAM24N1ThT4QoYTA8Wdn6TTF+E6TFgcGYUmfZIu4bW0Od3YnsBT/95RPH9pIVeThiu55HfCl8TcKDjtyd7gicaf0I2JjbSiNzf4/YBe6cF80Fsq0cXpSdsycSJl9UrTJdfcaYdcP1VxOB3jsNpJGmBj8r5xYszl3k7hA5YHEdjhpFcMZOda/FFZg9jyoDWI53WH0JdlmRUa0ax6NCmOE5YSWj4UK9hnfE/I96E+iaa3m2/lvQ==
*/