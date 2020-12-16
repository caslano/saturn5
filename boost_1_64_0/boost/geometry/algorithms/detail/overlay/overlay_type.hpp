// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_OVERLAY_TYPE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_OVERLAY_TYPE_HPP



namespace boost { namespace geometry
{

// TODO: move to detail
enum overlay_type
{
    overlay_union,
    overlay_intersection,
    overlay_difference,
    overlay_buffer,
    overlay_dissolve
};

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace overlay
{

enum operation_type
{
    operation_none,
    operation_union,
    operation_intersection,
    operation_blocked,
    operation_continue,
    operation_opposite
};


template <overlay_type OverlayType>
struct operation_from_overlay
{
};

template <>
struct operation_from_overlay<overlay_union>
{
    static const operation_type value = operation_union;
};

template <>
struct operation_from_overlay<overlay_buffer>
{
    static const operation_type value = operation_union;
};

template <>
struct operation_from_overlay<overlay_intersection>
{
    static const operation_type value = operation_intersection;
};

template <>
struct operation_from_overlay<overlay_difference>
{
    static const operation_type value = operation_intersection;
};

template <>
struct operation_from_overlay<overlay_dissolve>
{
    static const operation_type value = operation_union;
};


}} // namespace detail::overlay
#endif //DOXYGEN_NO_DETAIL


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_OVERLAY_TYPE_HPP

/* overlay_type.hpp
WIAAvlGA86HefRpzmsOcrlyuWK2Ynnke5KpM07N/ZkmiuFPoMZIeqrjIR/ONqrhTYsU9QA8Bj+O7n6/141MEaREyPQGbyGyTcp8nL5EQU/IS8goWf5fSgx06YKfXp9JiAZHranL24MxBf6sV/mmVDK4Rq6QtiKP1hw07ZE2TP7slGg1PudYdpqXujC5TrVJA2BMdGOmeZvjS9GGVXo9azKjJ+2f9Fvsr9ViqiD51T9E2RTPF7l4PVXzGMEWMhKf29JZWNcPFmo7dHnOK3gVuyyIpxcBSpokxdGfELkoPKsFWJjcF0GwTM0GYgSiDhkYn7Qy/OfkWt3P0W9xwfSPRK7iiu7e0msnlxW6usOdjlibHw7ya1JVujCmJlrXEEHxWTkEV+wzSy5+jZ2KlzSmzjmOYpYSHF49g9JvpXNHNojae86/Ua9o3nj7cptPIeYbKrvB4uZ/OIXM3s02UvvYMlixwfUx1BKUYEcQtrv4zPKo3gr6pUw0hiWE1y0bPd/DkNKnrx+UDT9LtNPSGfOAApX50g/bJolacf8KSUto+sVRN21Oy0e138C7AJDEdCoVP9biFa0rEBlceXE6dJtfbDC12D7AkZv8cUacfhIZ6qYOocxCArCQOoua1yY1qNukTquiBUn9NrZ32P23o9eFb9UHjskmavQ7Eg6hQhZs6o7SAvB7RHOgYbB4XsIZL3o1YIP3tDx4xBbDu3b1QZ0h1xlCp4nr88WuJTSr3s9ylx0eP8ndWPNuc/FXJvqp9b5vc6Z7I6k65CSiRXphpvpmNnf6A2zcTXafmq9rfScgHo1JBqSU05be9qVesCX3jc/QN2iKngCl2I5z0Z+Tuzl0r3taWo3coWQK/iwQDSt8He+NAhnZePSCoBWZwcLTRP2vllXqnTzeq+xgyueU4YuAB5tPa4evNJOR+0Esdl54LuIRn9eT3Udut4W/hcKkqSZaTFE5McRzk72SLqAaHCQbI/GdI2VP/YPD6OOP3jWPuojAPlZjNRok5UhbqRDIpmGfyZ8dj9lQxzYiJODiQO6VhphTGdIJDOi3PtSJbzlQ22jsvXUveqbwICRKzHP8hocy3ThzJy1a11WnqEsYsQPCJGzNpGMciVkf6euemBZuH2X9kRoBXXGRDCpB5VdpP0PVcIi001uLJv36Y3yrGD4vYSMf3z0gzhIK0LI6APH8nMT4vFKw0UOy1Vr7Niu++nG1YtdBMGtKJDF8KxiD9gKAYWfKo/HtC1zu1HD1zt0GeQUAUISzYv3H0KyFNn6E16RFmIQI8FiLGUoLfqfuPU/4l8K+gf63uf4YEWCzN0zAfC9gV+rMGaTYm5jcXXyIn9hVaYIukoxL1YAeTnB1Epz4l3jLTVMtc1YttaFdt2EDLK4SMFgmJKtZHWuhJvkH5MrO6pRttiJ63nyC+uJPZ5T3cPWSfg2QCo1ShI6qenH8GTNqH+njkleuhdOwSGm7577bcotO/W2L0zhfdLEoF6vfXmQ1HuT+dxsKL0YcrH2YNPqjSS47aNnkEtVJuAVZwaFDkpXP+inrJTaR1axo2LnK41NUID0FAQ5hDhT1qCx1GPbZNCMaOmMVkMJYrwpvxgYEOWqWiXA0z+VJ6mmH0EFgaz4xRIW4SJ+78IPuC/0z7c9JRUV6l0vHFdE6my0O67Fq8jXo6D5aIZhkRkzrnPjHWgheGCP4hcg4CRjJgoRibh9cCBixAwDAEFONdIcZeGiqElWj8QoUzPHPlyIXTCWelcpIu4ngrLIZrufKbQuzF/FfiDhUuk+qQkkm8Ls/Ucnp35xnV9A5z6g/TqnoYv1DhAiR7PGLxwUVBGZ3neAJCKgXsThHds4j6LDyIoUrIMYo=
*/