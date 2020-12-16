/*!
@file
Defines `boost::hana::detail::variadic::at`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_VARIADIC_AT_HPP
#define BOOST_HANA_DETAIL_VARIADIC_AT_HPP

#include <boost/hana/config.hpp>

#include <cstddef>
#include <utility>


BOOST_HANA_NAMESPACE_BEGIN namespace detail { namespace variadic {
    template <std::size_t n, typename = std::make_index_sequence<n>>
    struct at_type;

    template <std::size_t n, std::size_t ...ignore>
    struct at_type<n, std::index_sequence<ignore...>> {
    private:
        template <typename Nth>
        static constexpr auto go(decltype(ignore, (void*)0)..., Nth nth, ...)
        { return nth; }

    public:
        template <typename ...Xs>
        constexpr auto operator()(Xs ...xs) const
        { return *go(&xs...); }
    };

    template <std::size_t n>
    constexpr at_type<n> at{};
}} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_VARIADIC_AT_HPP

/* at.hpp
zmlcyrkUa5PKuOrYJlOhSQVPKi/gNNmL1b2a5pbXvZ2Sr443HfmuOxew/VSnbHG7imtvn+Kxt+/mcV831eO+bncPGwDdJSQItwli88jiGG+TIE54T/u9dXP/tdWWsNWWsNWWsPm2BLqP5pwLkH1htHXvPTNZ+0Ja+vf0DtRT2zvnhJkkT3x9zZ9u+FHvQvW3+B6VV/16BrJ8tOHoKZQ/SMnvpuQPziSdle63r+kj+6C2kyJ2znSfzbzWz0zfzvZd/I2sO/D7jD90plbAztNM/phifoe/LT5bwmzXlexuUhXjpzPZXfd8we+4Z3dh/toUn6thmW6ZvlDdj8nz70wnvkk74XSXvtaZCNMdUt3xTXbNNNsYabZB/mC0B+tv5o1S2pf532W42x9N9eyRyWwp9OYNH9MYJvvRP4xFjZmAeP1U1zjWJ5Qjvc7MG8/y2oU7bwLlcRmNiVv/xh+S0cnGTOD3uJ37/vspsTh4Xd0JRl8SPdG5AH7ZZ3Z0brI/8d3E56/g3kyG9yIYOHoNqK3GfRZifet5DkJnE845cDr1ld3vp77TOQil5cGhFTe+H50J4ceE8rMQCp1Kp9gGfHvrTNMQDCasvwWrLpY38ulchOrF3T9LFg20z3/wm/q8g32O6sAGmeWc8xBSBWR6sImHwpqqAHy9zXp3Akzt/852vHvKoLqHWOetdeV1Fr/3e5zVZ0qYIYFrKyWFSFiWcs6UbdJifo2p39F7IKRtSDDVP8wjXsFwVtZqcxcT52U4w682BDWVHWGdyZmx+OkNENLOqMxIitsAMSoLGuV2I/21CBAqR29/GCKz2Dq/292BlVby9z+oHNfD9nDgtg6Wo/g+jHH0V4DMNnLN78qrGd2MtWAO3dCbHybRyPSeRLOF1cUYhHuOx1vfY0Ys2F42fZTZZ2gTGP7N+QpUltPYJ7J5sLNoXJNM+ZNfxPSivZXzuX089giT+Vs1dMY+lWTN3knKGosPa3Sf+tV+nFejDcarF6r7TiozNZPOpanMe1SO/Lhpf+t+my8/013Hmyi3iRjA+TUVYwKVQC69S+qVYfvRFTHZUJzp8i1DnmP3n6bIqlLeL8DLmD4j67lZeUN2XyV/qrLPnWHlU92AMzsvpEom2QGYfgacAY8OLgsdOwv9EE5pX63aAfbL5LYb0NL2bp1soTKGWkVnyxLu/JkKTnYbQOVpvlW77v6MZibuAN9S/GxQ7sIcaLdJdMX9wVHHX6hN9IViQLrLq7Eo57D6Znrk11N9hwwg+0u6U17C1PIhpqduMOfE4y5Biphrt2var/ulKj4b1C78m4kGTbuB5RN9F53/af2ZfkW6cYui30VJJyqh2HhROx5coAFnYriosygQjcnf7QtC0bZWi09oLL8dIUBbcPMp1LhxOZ2V8yi1fjx763RhJm8VMZqJwbhh5pumo+1+RoOINxty+oVH14XV9oJgFAGkG5GOG+2kGe20ynYCixoCwba2eLi+vS3UOmkSIrPKM81Ye7whlG/BJ02SsesC1A/z7zzPknlKhZIPDrL72NoSQi/M/rUasWuXyhh61J/2LvQn1oIY/qjB6hOlu9SveR48MdkeGFwy2Za+Mfnh4kx3rLM2pAeJHsa6lXlLjADLmugweapHnknj+AcekGrwgKWAG/dx8Ptw4Dl9e7Nemq/1Mr0IaRs/gPUGxg8FzHtgdOcY+WYtQqaNOlKsWgiWI4wYBaEGhCfHhwY+u4u++mEoa/3r9Sfhs8B5V7ggFpNhmgXRfagMF3znhuLW3iJUEokF25x9Rago1l4fkeM8A7SXQrR3hBftNYciLaG4C7RoDOLDtwEvm1gcHuXyNqrOY2grkqPJ5HpmIHVze2I=
*/