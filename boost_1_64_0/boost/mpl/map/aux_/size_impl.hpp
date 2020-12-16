
#ifndef BOOST_MPL_MAP_AUX_SIZE_IMPL_HPP_INCLUDED
#define BOOST_MPL_MAP_AUX_SIZE_IMPL_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/size_fwd.hpp>
#include <boost/mpl/map/aux_/tag.hpp>

namespace boost { namespace mpl {

template<>
struct size_impl< aux::map_tag >
{
    template< typename Map > struct apply
        : Map::size
    {
    };
};

}}

#endif // BOOST_MPL_MAP_AUX_SIZE_IMPL_HPP_INCLUDED

/* size_impl.hpp
P7C0GTg+O6CTdoAhLLvern5/UOavj5HnAeQ5AOlLpJ2LviTbS5eA0o/INO98gNStpX+/qp+Qul+/sz79tr5BBoKqP5Bj331VnbbQRd98g/TlSVDyg7CCUEQ4urSyzln5qnxVvv73Xn9M/f/mPP/fiGeGr3EDokGc8ts8Q29MzUrJNW3b/Nz/XlXfgHT5bdlE7sMGEFaE6VjR2jagrKg8/i51yfKfWXZV51jOdg2ykUZS55DPbJVUu3HnuJXjNH3BTtJHvei3p4+NOKSPz1ylb4OT9K1U2lbs0pd7E/JvMdu1bMNf0iefWZOnTluEh/O0LbJP203IOyUdbMMhbaqsk7q/jLvg4ficvBc/RvfY0jbZXGTLT5O6X0GEVIb7SP25J6GsA/WuKrbn75Uzjefo05MSk6fFJxtz0nXujxMg+21t5zISkjNSrO1cl4lrskH6sUhbVaY+n8W09fyD5no+x4J0ij+ybuDVKup0SvLc6Y9Ty7TdwGusrXqvk/d1aLcL+dX0d8vIkZ076+Sz5rbPgnXSvudn/exO81wfVy3ve5jeH7G+7256v9n6vpvp/QLr+67l5pu6nxDNDJ3t2x74LEQ9XujqMNYz5lvn/WA9+sjYxpB4hn/XU97o5mH6rNTJMehpGavhFp3ptVfKym7C2jClT4i2rExOz8tNjdfnV2Q8Cfv9taS7jurcSE7XJ2bmGaz7uyjMmk7HMUBoM0r3IF2yrros1apmTsAc2Y8CwoNB/M+uzCsn4Y3ugzrv1XGfkLgHSNx9Cc8peeihjVu5PutvoJ3VVXlZrjrOjST/LJ+xm6Z/cJKP1va4J0zL0itKe17SgOF4/Tjfgf0pq2K/P7k3mpe10MBKjFIi+6MeW7b8a4euBoHXOLl2xhDWsz/Bnto8T8ukxd2N66ekUVNGa6nSZN9umy/x3yd5NEPKW4JOGz83FW4of1yVtYsSb3PZ70DCBY7NWrtjY8gz5lZkv+2PDQdEOTaauJfVdF4uouziztEnpvzWcpGWqRlzhvfp5ZaJGKl6d5H0dSL8WWlLtysTuabz0P05nss7Dxc7OQ8XO56Hcn1WnXd21+I2clFIkGM7ibCBZYsd059nYA9+y/F1di02bVfauC3XYvYh10hvUJ183kA+zzKm6nPkn5TrclUv59fltRwI5VWofMeLZykzpZe0ZWZGTppRL/vT0o3v+AVXbN/puy5bv7976OSzkbbPQi2f7fjF+lkXy2eP2z7rbPnuT/lF+90/1hxXSlam/jrni9Mya38uO4zVVUc1FvaMHEa/km2esN0/cfodLtdwWY8bFpp7EK7a5F3163N1j8DVvQxX9yxc9Q+8efcyXPU7LTHdU/ih5vPZM74t6d9p+5zg159dcvLG+g0G66TuJ/WGUoJ6HNcX6NflgRswADeieT3CddbbIuttlfW2qdZLuM56z8p6z8l661TrLbrOei/LeptlvVes60kdA2s6WS9OxqmdiNVxEprHW5Y6BPaR9dTjLXdm+7UxROLrgs0xFFtjV+yJ3SQdBVXkt7789i/FDjrbs/p3yvbC0A/7YgsMxyDsh8HYH/viAEzHQZiDg3EWDsH5OBQXYiQuwxG4BkfiizgKCzEat+MYfAtj8D0cix9iLB7D8fgNTsDzeDdexEl4FeOxKvuShLUxGevgZGyAU7ApTsU7cBoOwgwcgQYci9mYjbk4A404E2fgHMzHtXgvbsb78DW8H4uwAHfibPw7PoSf4lw5Dmt18nsf98px9SUsk+N6Ue41/Iz+eAkD8TJG4hWMxjKMwauYjL9iOl7DWViF+B7EqvgceuAm9MSt6CX5Xg13YHXcjTXQPH6V/J6HOZJO9fhVsySdBXI=
*/