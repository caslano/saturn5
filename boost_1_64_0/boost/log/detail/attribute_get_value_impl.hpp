/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   attribute_get_value_impl.hpp
 * \author Andrey Semashev
 * \date   04.08.2012
 *
 * \brief  This header is the Boost.Log library implementation, see the library documentation
 *         at http://www.boost.org/doc/libs/release/libs/log/doc/html/index.html.
 */

#ifndef BOOST_LOG_DETAIL_ATTRIBUTE_GET_VALUE_IMPL_HPP_INCLUDED_
#define BOOST_LOG_DETAIL_ATTRIBUTE_GET_VALUE_IMPL_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>
#include <boost/log/attributes/attribute.hpp>
#include <boost/log/attributes/attribute_value.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

inline attribute_value attribute::get_value() const
{
    return m_pImpl->get_value();
}

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_DETAIL_ATTRIBUTE_GET_VALUE_IMPL_HPP_INCLUDED_

/* attribute_get_value_impl.hpp
HALXQ/99ap6mV+Bwn/o37a9f63h/EI6H31ja23hT15UO7b1Z23uLttNW7e8vw/ZwmyWdYW+W32+e03I9D2vDjTAJbtJ+84K/PC599l2fy++vY26ijp+5Hq57OAMmw5mwPZwFh8C5cBi8Dg6HxXASLIHpcB6cDufruux6uBkuhDvhTfBt1au7GFdha3gz7AlL4SKXL9xi1e9SfTm8DX4CF0Hv+uJ2XY/dAe+Ai+FDcAk8Cu+EoSGMw3AUXAonwXvgbHgvvBX+GX6s/gdU/0L1w/A+cz2nz8/CNg7zVn2dtxrBZHEvi3dE4/V0iNdU4yXCHjDJ3CfR5zphlEP/G6r7BcN0v+BSGAlH+PIrnWuSxs/XcTcJKdT2vkzbe7zuK4yG7eAY2BmOg91Uv0j9e6l7P43XX/XBGm6o6pepPlr1VA0/WfWpqmepnqd6geqzVS9W/XrV34AToIcyTJR1vk+vqvoweDm8HabCZaovV/09OAnG0T/SYBPo1ZurPgJOhrfBdHiP6stUfwBmwLUwEzanXqdo/5oKJ6qeofpRXbuvfV+vO21HN1JX27FhZe03uo83Cc/NGn5WBOF1nB+p+zlHtJ2OwwvhT3AQPAEz4C9wPvwVLoEn4WrVH1T9OXgK7lD3d6DB+d8Hv6HvV/dPVT+q/seBC3rn0RDYBobCnjAcnoQRcKabssI5EF3mw0jYjHqJgjkwEuarXqL69aqvVP1J1T+AleBBdf9e9WOqn1Tduz8eDWOhB7aAleFFsArspXpf1XfC8+Bbqr+t+nuq71f9E9U/U/1vqh9WvZf3txg4BHr14apPglXhN7AaPAarw/Bw9g5hLKwBl8M4+IjqT6m+XvUXVX9J9TdVfwfWhKH0k9qwPoyHrWFd2BnWg4NgfTgRNoDb3IzDQ6OMVchmZD/Sg82wachSZCdyCknu4jYmIEuQxugnCLdksNt4FNmO7Mcd0xxG7LAoIw92GuI2lsFiuBTZ4BX0fXA73I/0H+o2jsDGxIllQdkc6YPk4b4IGcnfGcgB/l4IlyKbkIOI50L0YW6jLuyGrOkdZgyCE5BCpNTrhiRfShw4DB6ES+AJGMvNbCLSDTmIWzFc82CksRZmDHcbm+EB5AiS0J18IZOQ0BGkDxNhKRwGFyHL+PtRZDtyDKnbgzBIBtKNBVghXIAsQVYhm5B9yDEvR1LHSGhPznMZ50EWImuQBNySke2XEQbp0ZP0uJHOhsXIUmQz+gno6eW7ua6FpCB10RORHshIJAPZh/tCuAHZjuxHIseQ3hjYm7ZAUpA+yBgkDylGFiGbkWnP0W7cuO/m7wNIMm3XHylEFiLLkLXINmQ/cgzxXIp9F6QHMgbJQ0qRVcgGZDdyEAkdHmXURTohI5FsZAGyDNmA7EFOIDEjoozmSA9kAlKMBI//jyNU7uVdPjtnXSbk5mXmFOQW5adn+v4syE6aXJSVnZHUpnWb1slTkq4uaJvcpqPpN7NTh6SCaWn5mRlJ+bxDwuug/hDp+bPyCnMnZE5Oz8hKb507+Qr53aFbVTaw+e2kOs8xbEwzTA7OSs/PLcidUpjQfHiLhKF5hVnTs67Jypma0Ju3a7OyM/ONajyREkJmi73PUxsZRdOnz+IeYVDVzxv4yvBosE8Fj+ARPIJH8AgewSN4BI/gETyCR/AIHme8/8/5z93/ZxSIpM7IymnXVrYB/s19gPrsA7RO4Zka3z4ASU/PLJzmS5+kZU/gYAPvOWKkTN7fK8Xd8l7qhcRfWyrvWPYZMTR1cN+R/Yf2SdUyGQ7vgNrslqqNME0/MkTc0ctsv3Qn/c2+9FOvLsjL512LKanZhrxnufV8A/fUXkVTplAax3deNa5Lwrc=
*/