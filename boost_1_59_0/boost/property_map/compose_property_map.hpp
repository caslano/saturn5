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
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
*/