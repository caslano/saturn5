/*!
@file
Defines `boost::hana::make`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CORE_MAKE_HPP
#define BOOST_HANA_CORE_MAKE_HPP

#include <boost/hana/fwd/core/make.hpp>

#include <boost/hana/config.hpp>
#include <boost/hana/core/default.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Datatype, typename>
    struct make_impl : make_impl<Datatype, when<true>> { };
    //! @endcond

    template <typename Datatype, bool condition>
    struct make_impl<Datatype, when<condition>> : default_ {
        template <typename ...X>
        static constexpr auto make_helper(int, X&& ...x)
            -> decltype(Datatype(static_cast<X&&>(x)...))
        { return Datatype(static_cast<X&&>(x)...); }

        template <typename ...X>
        static constexpr auto make_helper(long, X&& ...) {
            static_assert((sizeof...(X), false),
            "there exists no constructor for the given data type");
        }

        template <typename ...X>
        static constexpr decltype(auto) apply(X&& ...x)
        { return make_helper(int{}, static_cast<X&&>(x)...); }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CORE_MAKE_HPP

/* make.hpp
wvgz9aSZ3wLJC4z3dtLmY20kLzBbshnz/LbKrmi19x7e+nuWYPZ0bkiTVa2UmZUyzkvnOavHSZY0W9SiWrjMAcb9/DS31VllITCu4YjvhuYyBxjvyrTDu+yVRWvnvC/cl2eJgXENF35Z3URZgvacHi0uTpMZwfx53/MDykuvYZzB8QvaWSjLgVUkCyie5Sw9czS+X7WkDcekZzA3stST3mbKgrRzTR8UT1EWDmtP79aCVm/k3ZoC47nPc7/4s+wYLJhrWHdb+vkRVpgyMefPI2qn8aDG7+Te/v6llVWHcZZe3J/eWGYL4+/CzY7+dlTmB7MgG2GZNVxZHKwUmX3BxzjZMe1++y3flZD5afbewko+N5M1K3yrcV3pGYz3dp3N7F7KNmnnRi9y/0l2E2bJP1c5jpJ3+VEYv5MXHht4RFmmdr+zwXN6yN7COGfmT99WV5arzeH6zKVFJUuljb+Xe+07Zi1zgJXh3UzYITsdBePsWuyMKiO9hgWRdcswGy37APMmS7448W95h8AcyC4+39RX9sHZ+FnWtWqzTZmvZs+37d+tLBRmQ7YgqX2Osq4w7ufnDXeGSH0wnl/gkQyDshgY/zwdUNDXS1kqjHfzxcnENzIjmD3Z1Jrul5XlwczJPjia9VZWAOMZPWmwYp8ydxdTE1ey9/u6bZb5wSz4fg+r9lMWDuMdK3WlY77skWZtU1qfkn2A+ZG1OzljveQTxj1r3mbLO2U5MJ5Do7rtasrcYXb8nE23f1JWxNX4mv+McK+szFIzqz/SWyuz1+zpQ8N86RmMf6+x+ExkB5m7Zpuif/aX2mHclzpJOQcl17AaZKvXFSxSZuJmPPfiB3KLyf7BPMlCLJtmyvxgjmQTW1WTfkbC3Mms9+12l/nBeB8+f4mX2SbBeP9MO6YFKUuH8Wyf/DShj8wIVpls29/Leko/yxj/DNR34+jykjNYGc7n5UYLZI9gpckeDMkupCwRVp7szDpLeV+nwbzI+rwMk/d1LsyJbJLjmH/JHmn3q3B0x2aZQ1njDFbO6n5NWSDMlix0lqetslAYz2FKUJrsSjTMjayly8YbyhJgZclqxw94piwFxpm4U+HUaWXZMF+ynU0fn5T6YK5k7gvuWEl97sZz6PUoKFhZEIzzeaT1wgcyP1hNMudhb3+TGmB8v5HlrkZJDTDOy/VrreQ9mKOdK3vB7Z3UAOM5LD9Vf6Yyg4epSQWyuk0bOsiuwFrTO3nx+bxfJUsw7pnn+c71JfOwJnSuU+W9ZZSZeRrPvU/tP2Rv3WE2vO+B6TWlnzAXsou+exJlb2GlyDa415YsxcB4N2OLjSstewuz4729kfmzslSYBc99aFKE1Acz52te7R0pWYLV5cwXOpgvvS5n/LuSmCUhY5W5wvg7SqmLW6op84VxX56ezjkmM4JZk/W3mvhUcgbjZ2lRZmZ7mR/MiuxkiQe+ypK151zVwy5W+gKLptl+8P5llOyDl/HvjKf2PF5FnkUz3/g67yXzsOrc621ZkdJrmDnnOvb+T9JrmBPZ7R8O/qIsDxZENunSweuSM2/jd8juve/2ST9hfmRlVlbZrmwwjGd0K+Cus7I4GOczwH3VF8kZrAyZ16ZhjsrSYOXISg2KCFCWCytLdr/37R+VmZQ3rr3t5hYfZQ4wL7JpVe+OkPpgnJe+1bcvlhnBeDd/GxQuexutnZu55vAJqV2z8UkuTjJbzTLudZgnfdGsw+A4OZcC4/071MolXXoGM5B1vl5GdiwDxj+/t7Iuu1fyAitJ59y2/dlCeq3Zvdl2i5Tla/Zb1rQbMgcfY6vV5F9yTQOMc5a22kNqCIRx7Qe7vftLZgQz4wxWHPRYWah27nE=
*/