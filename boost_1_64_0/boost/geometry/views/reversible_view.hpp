// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_VIEWS_REVERSIBLE_VIEW_HPP
#define BOOST_GEOMETRY_VIEWS_REVERSIBLE_VIEW_HPP


#include <boost/version.hpp>
#include <boost/range.hpp>
#include <boost/range/adaptor/reversed.hpp>

#include <boost/geometry/core/ring_type.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/views/identity_view.hpp>

namespace boost { namespace geometry
{

/*!
\brief Flag for iterating a reversible_view in forward or reverse direction
\ingroup views
*/
enum iterate_direction { iterate_forward, iterate_reverse };

/*!
\brief View on a range, reversing direction if necessary
\tparam Range original range
\tparam Direction direction of iteration
\ingroup views
*/
template <typename Range, iterate_direction Direction>
struct reversible_view {};



#ifndef DOXYGEN_NO_SPECIALIZATIONS

template <typename Range>
struct reversible_view<Range, iterate_forward>
{
    typedef identity_view<Range> type;
};


template <typename Range>
struct reversible_view<Range, iterate_reverse>
{
#if BOOST_VERSION > 104500
    typedef boost::reversed_range<Range> type;
#else
    // For older versions of Boost
    typedef boost::range_detail::reverse_range<Range> type;
#endif
};

#endif // DOXYGEN_NO_SPECIALIZATIONS


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_VIEWS_REVERSIBLE_VIEW_HPP

/* reversible_view.hpp
U/RnzerV7yL7qNrTmdb3XuX9Ne2nW3tJdlwWaSef1Z4+4zg96Xxytu2N7KO82Xn0N9Zreo3lLN2pve42XpxqHPSC8profHZAO9Pu94XU3x79mOvUmHvsb5rydT/3Ke3ycGYkftePqceTD7nPrvwe1K+u+bFydj5+UDu95CHn9wzjo4if0H/sdfw3P6Weaddb+pw3y9TXnxtPTFW/XvC93+r34m3vXX7+q/a0Uf9/uXa02n47by7Rb86O194S9MOReGuC89+d+pWfOn/Yz0Oumy9sdN0RiWuUz/YX3Z/8pfakfj3t/HDkRuVeoj5+wbj1sci+v3oVUp//pD990LjffYCn2vSLC0yPKe/Ifqjt2t+gntn/SQ+pT/qdTZ+yvQ/ov1xP7nHd9vx09bVFfdulnA/bHvXgxF/Mr59a+xX3D3v078/4nnI+5vNL9jou2vP2XPM7P6543PGP7NtqNwtn6B8z7cc05XaL8j5XfdqjXErUn8j3faYpt8csr8f33Nef1Ks9bneeVC+nOx9uaVY/1ylP49yFl1qe9r/kMu3nO9rlhe5TVmj3xgVzDxqfT1GPztN//F47PsN4O057LTI+W6+e1KsnIcfT8ia9Un+vvsZ0Ws4+x1k7O/Co/i2yT36BetOpPPRb290v3BL53uwO26GfXfqE+7QPap8fMw56RPtRD+dkaJ/KZdmv7deT2oHrqp0PWa/zycZ229+i3V+i/13pOB1z/ptjvZfq/9/jvDTN8X/R9LOO4zb1e77zxjXGXdaz3/hpj/q9zX3JXWttb756Xex4f0M9KHH+rrKeia7r16qX6tvcTMehXX/ZaZzivLFnj8+NU6ddYf2/cByeUP536Ze06+POEwdnayd1rhec527dqzxj9OvOm0tLQ87L6utd6uV3Xa+90/HVnzySpr63287fOW7qxyVLnR8tb9rnje/OdrzKtVfleOJG72/Tz7jeufYB2/NK49ub3Of6s/b8Y8v9quuDbzrvPq58kvU7Dcatl6nfpcrLdPOuiJ83/rCfD/5Ue1NOu7uMP65Sn9PVS/3mvhjlUKp+XqTd3eG46qeX6e82qY/TztAe36K/6VRfv2T71ccVX3S8qDfwZ85j7mOseYfxyDzXi/bjtlc67+kfdiqfB893/pygnPXb9x2IrNeVZ53z2G71pkH/VWE+122HnN8W7dTOjaN33m48sF+56PdWNCj/SHz1nP5Fe9ocsTfnnXsnGk+u1d4zlc+Y6yrni8nPaZ/dtvfnyrdYe+9QnvqLo99Uv+42fjVe3XtMeV2mfIy7btGfzlqvHJ/Tzlzf3nez9ekfb7lYu/iR/alUD/RLc23Hdvu1e69+d5brrzfrj9r1t99WvurLtJvs11X6sU+p5x+znw84rzsuGzeqj+rZ7pu187nm/4P692Xt4u3GoZP1664D1hqvXPMr/aDyXTTR/k5wXlrgeqJcP3SD4zVNP7FR+d1iP2zvsn7ny3bboR5N+ajj5fw2u91+2M57O7TD1ymv633/HtOfmb5N/T2gfM9Q33+pXU92fuzSzp7Ujxx2nLTvza63Zn3Bfl6nHfaoT47vXP3UkW36izcq9xetN9P+6P9mjWgfr1LuMx2XJcYn51nft7Vv9WHeiPPCRa4T+5TvHN+zXRfuUX++rj/RPrf73j7t4pKfG2dcYD+V78Fh/aLz0JGQ35d4Qb+zUH18n/PSX/RvK7TTev2r8/W1Y+4bZKsn6uFs/fi0OcrhPP3vTNOJ+pczlE+8drlFP3CF+lCsPr5eu55p+57X3r+lvzigXPa7PzVPvbzMeWeh6wbXPVevtR/POp/5/pYC59uvaR+T1Mcn7J/t33iNehvv3/0+5Pt+T+g=
*/