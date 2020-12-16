// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2015, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_VIEWS_DETAIL_BOUNDARY_VIEW_INTERFACE_HPP
#define BOOST_GEOMETRY_VIEWS_DETAIL_BOUNDARY_VIEW_INTERFACE_HPP

#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/algorithms/not_implemented.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DISPATCH
namespace detail_dispatch
{

template <typename Geometry, typename Tag = typename tag<Geometry>::type>
struct boundary_view
    : not_implemented<Tag>
{};

} // namespace detail_dispatch
#endif // DOXYGEN_NO_DISPATCH


#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

template <typename Geometry>
struct boundary_view
    : detail_dispatch::boundary_view<Geometry>
{
    explicit boundary_view(Geometry& geometry)
        : detail_dispatch::boundary_view<Geometry>(geometry)
    {}
};

} // namespace detail
#endif // DOXYGEN_NO_DETAIL


#ifndef DOXYGEN_NO_TRAITS_SPECIALIZATIONS
namespace traits
{

template <typename Geometry>
struct tag< geometry::detail::boundary_view<Geometry> >
{
    typedef typename detail_dispatch::boundary_view
        <
            Geometry
        >::tag_type type;
};

} // namespace traits
#endif // DOXYGEN_NO_TRAITS_SPECIALIZATIONS


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_VIEWS_DETAIL_BOUNDARY_VIEW_INTERFACE_HPP

/* interface.hpp
gY4bqQdM+iWf4ADX9vJ7I58XgUO/wE8pl8XnRVuxP8gCfci/Ar+aBQ7xfQPoABv7aResADPBfuy/HRz+DTygA/SD7ddBg16zh7ZBFujCD4Z/R51gA1gBOsDMHcjE57TrsQd65T1OOXBpF34BtoJW5EtnHNX1YEs+t4B+rs3n93TGTU8H+vN7G4gZvwIrQBvY/ls+QRaouhPePuoEwdvhA+vAbJCBnVf8BTvxuZ82dz7B55PUCYYH6G9QBfppbxtoR+8aPsv4bDPXehkDIEZf7wSzuvEh0IusHbuQm+/ZfJ92P59guBserg92oPON0PvQj7YOYPP5tH8RyKLuJcSzdBABg5Sb1oNNzdjCZzeAaeAQdpvHZzc8QerspZ42kDWAjmAjNh4AnWCoFzqY/iB2p9xWxsw6kEZbB9AjFRvOpv5Lb6AMmI5s8+mbKNd2DGB70AoOdEK7BXvyOcDnrFuRkc8dYDNYwu8AWML3tGcBdr3oKWz4EHVg5yxwAJ/u49qKffgQn53wpHE9yOcgnxvADK7PBxnwbOXzUj5nUG4bn1V8DvHZZ/hBD/zZXNvAOCpn/LXvoWwM2cwcdyr5D/NsWTXz14eRgXlr/+vkL4fGsK9GrsM9mE0gG/RwbyYF7OV7FZjH9w1gCxgC8yib+iHuyeDnvdwjOsQ8uYJrNbRV9io6DKHrQfoEtIKhzAmB9vTxgY5actk545hjuLdF2fZubLZsHHtkEwKRL47j+cwxzFXkAO8h/4OUwX8zWAeUH5rAs6gTGfvwIXvrN7g/dCmymL2/y8hjXyVXLMA332KOfjkl0NrONdpofZd7QKeDVPh/zrWz0e/jyPck5d6GdwM5TAZ8n+D7SeMDabTXVQcPuUXw4QmBdN79jhlZqGfIvOOwm7JcT5syMZD9DjqkTuT5yfGB8h9Y72x13E5dufCbMduNnsemkIuiFzr33zyB97u5/vnxgcikieS2EwP9jJPuj40PxN7lQdfjGSf0W7CX+n+IXKdS7wXkHtzn6uojz7qKfJcygTPR5d/YNGbqp45fpQRi6NpfjQ6mHeTrvgc5Z6cE0m9FB7MPtpH8668TAh070I39i0AfdscG2eUTyPmp53cpga4XyafIXTP+GjB7nfgO+szkGnyRR2mfsuWPM777yZPvmxAI3mqtCcupO3AU7V0O/Wf0QQayPYKO2KdrKvK2IS/91I5vdi8C15On01YaMsfyxgfaqyYEMtApgg2zh9H9WymB7o+i0xnonkk/MK7bT4L/ufGBLr6nXUk7Udo4DV1for7xEwOxfH7PpY8aKJ8GfSl5d06AvcWUQEYGNq9F5rETAxkPUhf26T/J8GJjZA/ix+1PYPu96GbimpGbuND165RA+yP02d/G84wA90UfoI8/zid/zC9YwkPL+GAaPhnZT9+djPz8sdzs31P2Eeq8Bp9Dn47gePIhbLULObFP+4PjA9138fkeffQQsqFj+b+QBZ/puhJf+xn9dA22npHCQo22Bih7Fb6PXNlX4p/1tPM6/fge+r2JvGfSXz9Grm7K4xPlr02AD73Ju7uxfX+bWRciy0Zsi6+1Z9Pfj/C9CdluxX8nYruZtIV+6fRPhvGTO5CPh7qHvomP0F/pZu56Dj/C57top/uT9NtRyHE3fYN8GS8Q59C962Lko386TsBPqTf9Pb7TVx27+SyjP1dhzyHG78fwy9Upgch27HcVdS8fH2gdS79eQz9hs3LaHzLjLB8ddlAe/fqJe0HTB3vpC+xnYni68cdJyH8t9ZyKLIyZ1jModxv2WG/WjNB/zPXvoytttaZSju9p9OkQ813/JmxKP/T/FXkfpuzP8eVZtFGJX+E7XaZcOjZ6Cr0=
*/