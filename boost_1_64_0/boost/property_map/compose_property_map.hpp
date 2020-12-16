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
4QLRbiOjH6+0FB5ffu+0oaFVUb+dYmyoyD82IWVu2dSk8phlLxoKwyK7YAyL9GuSJvT6vveVyScXt49aaWw6T9FbxTMa0zTWXXTt4zBA0VNxNoJbgEPAF9C+DWVg7/0ZsG+DukfDtFS91z4Nnns0uPzruE9Dqv6s349Y4q/s1bAeaWvbq6ES8dr9Gg5LvZuEhISEhISEhITE3+j/b7HacxzZWBun5didjhwbX/Sf25qfr9mjI870/wcpoDU7feNfu1r3rkyd1+MRkIfFek0fytqWLd1Q/JC5yli4M3FZrd+vB+j79Z5+AKr9f4RDrkMkJCQkJCQkJCQkJCQkzh8a/vv/VvudwuW+Ydb9F0XU7PtnqMX3fxgW7bueVdb9eRk5+TaLdvmPumQ6cuzZ9d/3b41Y+4++o/3pbsFzoiveNbyTUfmDwf0OgCiz3u8AlEodgISEhISEhISEhISEhMR5QsOv/9OxdlcVAOe8/u8WUfPufyPvb/vRu/+3ww7v/e6/Wot6rvt/Fut+5zP+K1Pf+iWl0/3PxTXe9dx96rqfykIdaln3B2ls/nqwkdb9gXly3S8hISEhISEhISEhISFxfvE3rP9tTuy1b2mAd/35+r93hFLHWLmGlpCQkJCQkJCQkJCQkJD4y2gEub1B1/+Z9jvhfG8x5Zod5mwrcjFlmO0WrOcbxB9gIPQByeQP0Knu+wD4rFR9vwkYt0zsiRdvqvho95S9y8Y7Vr2e0ezruu0JQP4Bql9AkdRpSEhISEhISEhISEhISPxDaHj7f7bZmWF1OBrI/p+MRXdXWu8n1PL+//Udar79RyVj7/KrjNd14HEmU7rY/o8hbpCxlXK+lF6H/AcaA+uw/g9jRpGO5xmmydOtF4iF3C30AtWLd1WUtNwf9vyGV43RCZM2+dorv27fEmxF+oIw2kcgHMzrsTEPe5xL3YGEhISEhISEhISEhIREPdDw63+79a4G3P9vpPb9/3p8+99di/ra9xeKdfwts5/ufOqnXzcMPlZYPWv2id51W68bab0eQuv1ULLz93DKtbqEhISEhISEhISEhITE+UUjSGqDrv+dGQ6r2aJ8H79h9gAcq/kGQHA9dACamtBmgPXTBewTuoCJ4ePKbnfGLDrReNDHz23MvbFuuoBmpAswkC6gOekCHpW6AAkJCQkJCQkJCQkJCYnzgIa3/zvtaTar2Z6fe85r/ygWaNyGtX3KiBRTYv+kpAH9E4eZBiXfNHT4dckM4P/vbM9YLX+bburOhO7gKSzkB5DuYJSOCRjca3TaLyCX9gsw5eHstLsGOAtyrQin55xdb9CC9TLm07v/l3as0SME88X/IrDu0qkJy78atvRY+G9NXvmpctJF+HZhKY83jthRMjomJdLebvV1/XscyGKs7WIevyZpQq/ve1+ZfHJx+6iVxqbzGPvmfR4//ZqIux0pP53cmmLPWvVrwRTG7lnI44uGbn/z29DwOZsaXxa+OnImKpUuyo2/vcPrluQZ06PXfXjZ5lvfdjJ25C0e/8l9AbcFzJl+6OYZpRPnl24exdhyEb/k1LG0gvZ6e7+BCy87tO3IacaefoPHb7/3049/P1F8vODxduGLJ48OYMwl8r9iQv/ju74+ddW8yCU/bOlQghcUCkT9n1kZdXD/yjausW2f6hkf/101Y++L9K88mz58SaMjny9/Keb356Y9+hJjbUQ7XDR734IOe/U/rUu5q+KutmPy0ebifDtZZ2e1S9kUszB13fbmr+7uw9ibIj5+zNEnXrvM0TglJmD83r4T0c5HRf5TH7qhelnkZFfsO6Y5zbL6bGdsgajPyOjHKy2Fx5ffO21oaFXUb6cYCxTntbpi/hs=
*/