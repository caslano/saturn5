/*
Copyright 2018 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_CORE_EXCHANGE_HPP
#define BOOST_CORE_EXCHANGE_HPP

#include <boost/config.hpp>
#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
#include <boost/config/workaround.hpp>
#include <utility>
#endif

namespace boost {

#if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
template<class T, class U>
inline T exchange(T& t, const U& u)
{
    T v = t;
    t = u;
    return v;
}
#else
#if BOOST_WORKAROUND(BOOST_MSVC, < 1800)
template<class T, class U>
inline T exchange(T& t, U&& u)
{
    T v = std::move(t);
    t = std::forward<U>(u);
    return v;
}
#else
template<class T, class U = T>
BOOST_CXX14_CONSTEXPR inline T exchange(T& t, U&& u)
{
    T v = std::move(t);
    t = std::forward<U>(u);
    return v;
}
#endif
#endif

} /* boost */

#endif

/* exchange.hpp
76U9idsZwVbu1qCtu+aOBO1t5Zb7vgN0Y9vwloq1jMGNGJzVPrPzKI0tuBv4GM03wI1fj7hw0aQzP1DZTHgm+T3rB5Sj7rRxJDwnsImzfbdE/LmcTwyWx/kMwSMFQypvKIy8XXPKk50CrYNPJ3rO1+zeyo7DM4zsPdnu2vCZaMGH8n0TWwvz0GLfY9bT0ty0aT6AHhn6yXnoUZ9PY9Squfc/oM9Yu/a9uSW93SDMkeOpS/xpesU67LbxOD5sCN9MPzMPvQ7ldtwq6bjJ/gHCuYb5h1A//RF7CaNLMmvzyJT9hpFZ1zJN1YffvGkyDo7OOdw+4LI5JllArgRXw9fCqIQp48ZtK1eRgveVDvQENCYWL1jo992uf8/s4Xs5+lIZz8Nn9XDtJzwvOkfjwRZrV7G0OjV+V4jPA4+7uhp9sAX+lP458fiWM8V3WtOL/wb036N52nN6gnqofDSH2Up0z7W5UG8kszYx4NyeufJv5Ux2zr1gTlqssPLbLhnv87QPSTCxLXIF3YT97XzSN5qxUyx/8dy5fao11zQumJveaM57qZew7nXTKlPd+O7LWG/VR8o9LuyRfRYil3M3z2lTT+VG+PUJv7AdcH67V2ayBke3Znu3FXSGi77w2fEkfV/Ie3dJ/fSGfYXF+e0xvV2aV7G9ShkXVCUo/r2ac0yFor69xuJ0vxPb7nV6/FT3zNiaMzyL43G09/cs3mxBuN9vYrmwaUKx4c3UFmY1ss3Znos38pnmUpcmqsPbRIdygjDVwN3okv0G+TLBqRjdKne/3NIYBsz/Shm/2PnL8EJz31ctmemwsP1+dHSGN3cw03OQRUGdf7bI/X5nj61hoWPqMlEOd2Gdfl8hNOkOMZ0ktv2V3D6hO0gU464iGtQZmxO7SwV99bLs9P89jhxYiWx3tc1bOaYa+7zf5qmM7+gMrrYvlqc+ZLGN7zYOXtPTuuapr9vYOuq1PbGapqUz7xqADrmiqVvaONfy/moNPFGusPnwddn6vWFI1uJhcw+bZTQrRsqd/houn8WZ7569O7bA8x3bsP1QxbbvtHaTRM8te50xWObORz/emTn50SxvAp4PapwzKdC4G3uzSTDj98mAxq3JZ3SfakE3m55a0pmHR+cfYvB62xunTfuUb+DbSj5PCmn9swB7lhLSqtAltKkNjF9+juavlLnNvPt8hA/+acbgizIG8FPNHN46Xnbjy5cM/9kGUKDdbfh/i+Ia3z9f0VK+lHjIT76c+UHRloTZxl9txcMUWOI5tFAFOfRdIY19r9DGgszYpq/foDVoYOvm7aN6JTP+9U3Gj4+PDm/YOT5E+dyKzGY+H7OaWZrvxGpanrybojShvJtN/jSNN+JUmrsXE9+NLd/zaJr1WjUp2TnxA953TKUL5GS+OYO/dYmqQudSP7I2RD0CJ8j5Ov4xC9cpOHuGnxg6i2bf+an2C71YzqIKm58qSeUOPCLjjfGSHZPh8TMrQx6LtaIymp/74xGx4c/sPJEug4/V16eReoKl6XZjHk18vO3p5m4cFBJu+0vS0/99nds5v5G2Ov+zOcYd1B5bcOPzv7dw2WrbmPlHrS87mEw6HUfMmYqdw3x0ZHT/kz9Ona47atCC72Zyi2N7u7/0RO5rmPKPmy9qd5cu8dsU7HuC5rH40BLkO/oKTa4JRXmd+UdMvj2zN+PxL00nmwjL+z8aTr/PZ9t0Lbd3Qlmfwwzc5qZZm7tluJL7LfQ9XLj2nZpbk7hXhMbPfe4ToTHZE9n0fsttLYSEGfwDNB+ZX9ILYy/7W3Z4ur2PcmvYkdtJRKd2R2i+ZgQy+FECV+7I/BYSPFeXCr2ytSsPOZoZISPrWGkrShiex0k=
*/