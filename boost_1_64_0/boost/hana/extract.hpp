/*!
@file
Defines `boost::hana::extract`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_EXTRACT_HPP
#define BOOST_HANA_EXTRACT_HPP

#include <boost/hana/fwd/extract.hpp>

#include <boost/hana/concept/comonad.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename W_>
    constexpr decltype(auto) extract_t::operator()(W_&& w) const {
        using W = typename hana::tag_of<W_>::type;
        using Extract = BOOST_HANA_DISPATCH_IF(extract_impl<W>,
            hana::Comonad<W>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Comonad<W>::value,
        "hana::extract(w) requires 'w' to be a Comonad");
    #endif

        return Extract::apply(static_cast<W_&&>(w));
    }
    //! @endcond

    template <typename W, bool condition>
    struct extract_impl<W, when<condition>> : default_ {
        template <typename ...Args>
        static constexpr auto apply(Args&& ...args) = delete;
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_EXTRACT_HPP

/* extract.hpp
+L2V+hWH6U838xtdkeD8q/DpVeF3VJunQX4zy3mzY+r080jwPNfikwTzc5a/8UTpv6LB5y7FAw/7Lrrt0eC+xwav56rTdX+Z33bB9bJS5M2yBONqFvx9Efw8WbxOD96vgyslp0SCPL2crtgOtz6EI1fK90fgZiLd0DE4L+Uu+kQeLKuJBM93JLxbGwny6CfzngVnZiQE5+2FJ1/6raMmeBoJjtklkWBennT+3eL6GV4swOOdg9dj6j1WLj974P094nlE8PeyrvJrJLyaF7ye+Z7vCj7ObxksTPTdeeruLXj0pL+jUTojuE5Sb7wsj7ttCD4fXa2+B/pt8o7w70g4NShBXIPrFuXSb1MS6Fd5PYOOwvc9Z0aCz/8Hv55FB4h3bCU8NM6cFnQZfCq+xne23hq83/46eVTgPDy5MAPOnGTeXwzez+gcHNP30xeZ6r4d3htJj0yge+Ho7D8iwbj6wyXzWTkmkV7E6x/hc9cpxUMZj8Ll9X5bL1t8xkSD/MmnaxrF5Y3gOOt+PHa1ej8qOBbuph/fj/rOZ3lg/nK30WsHy8cZ8n2B3zIxn5PV65SH4dT94pMS/F1Aj2TNwqtZcOAu30X8rnGfG7w/9eyE4L6d4OAr+Ml4RsC/7U145nJxvxaO5sKTu+VhHV4fYZ7xaVmqet9Pz4W/BTdHnpbj54voiqfxwKXuP8t3/Bp3sfpa+bm6KPb58+iqN+l7enFqD9eRl5XzPY96TJpNl15A34+iP903vTC4X9rHfEkjPF1tHpuC40K8UrExMTgfTs2dh4+vVX8r5NnLvhP7TfOyzHOEOo5vKyzEX0fxEZ3o1dPk1RUJfgOdb8CDpfC5256I69HzLcXveXiyX50bb8oH8L8VvO1g/PRm+xPM3wa43plO2sgHjuIvTuEH1UGKcZSPh6MPBsfCrXxbUoQvpme8Pvdt80fXzW1tHuB78QPhb9T5buW4+esKT5r47R38dQu4+hK860X3X8R/HOb8A3BgLZ1zAb5Olz94clmR80bTgafzQWvoksXq8Sp5fHVicF38tp0vzuwi3r2Mr6V8rsYLS4PjwtvgZ3O6IJfOKeJvBsAP+ZPTnU6mHztFosE4ZkbpOb95vgmPPGge6IvCx/HYjODvhlcde+tvdMT/p0SD827Fn3P4owH89+N+I+ogcX3EvGWpMzgZO5r+uZme6qPvMpLubSVvXqQXwrjhwewIndQZrh2hD1BBL71r/tTN5BI4KH/SX5W3v6uX783PvfTDRsd+seB4Zkx/hJ87mT7YKd+m4uX8aPB8B8Pxd+iX/+jTqJ9OZ7pfX/P8L7qut3xuYb7pq3m7PGcfv3EwOyE4nuK77vcFr2e0UUfqftpT8ncF/2GcFS3x/LPyo7P+0yB5hG9nuG5dt4jvYua75fv2M+H/Un2bRnWVpE5Wyeud9MZ7wefq1/r8d/DNPFY/Fgni/bd5HK9foX+w5VPz8ih9cwR+LsUzn+P5i42fn9hyofr+23NHY8H7J4lrXD4eLb/xRPFWeH2hPtZb3jc/DVXi+6p5hnu5k/DTDfi6Lx77IsLP6U9cAafOoyvhYcXF8CZF/rWhM04I3l90qD7JZjgqz3Jz8M45weeT4VXlaXCfv5/6eiTI45Pg/mJ5naI/1Y3uwt+lg+Hda5Gg7uBG+So6Ak9MPpQOvIc+Gi7fon5Lo3twzLjLb9s18K9/0MnHme88euFlcTrYb1a9ZF7wXGM7dcDnVi0wnwNifCe8HKovcQf9cyFc+Vie7hD3DHiXEByz6PekXsFxijgtuhSenSHux8C/5X7Dqhkef4gOOy0h+Hsu/fwTPbGdH9sdvF/rufNvo4Pl9aIkfVDPW1XnueqifD0=
*/