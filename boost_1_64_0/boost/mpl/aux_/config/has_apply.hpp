
#ifndef BOOST_MPL_AUX_CONFIG_HAS_APPLY_HPP_INCLUDED
#define BOOST_MPL_AUX_CONFIG_HAS_APPLY_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/config/has_xxx.hpp>
#include <boost/mpl/aux_/config/msvc.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

#if !defined(BOOST_MPL_CFG_NO_HAS_APPLY) \
    && (   defined(BOOST_MPL_CFG_NO_HAS_XXX) \
        || BOOST_WORKAROUND(__EDG_VERSION__, < 300) \
        || BOOST_WORKAROUND(BOOST_MSVC, <= 1300) \
        || BOOST_WORKAROUND(__MWERKS__, BOOST_TESTED_AT(0x3202)) \
        )

#   define BOOST_MPL_CFG_NO_HAS_APPLY

#endif

#endif // BOOST_MPL_AUX_CONFIG_HAS_APPLY_HPP_INCLUDED

/* has_apply.hpp
dtgfode6d+r57qrR1vdbR6HvpFYXl4QOCOkJBv/cOqhSd/MYaGhRpQtDH98qzauowL7hR82rdBnPlxDU76552z9yfuHs2vM935rBWkgPgnQ/X8+2i3TlFbKhka5iRmHkl/ojf9PocPPY2LU9VkofV9HzuL2ycbIu3q8c1V1WBqw65ukPkONArpRvmFXVVaaicmYt52nXw25bVV5pdcCz4+XDUaG+Hmpu7Nzy+dzh+nfuQ8NpxLDiGVdnl4S/sRJ2EUZel+frb224ZaoHeIrRybp4C2I7PF8ojByfo97WqBXZ0l+XlXllpaXRb1iA95PP8EW8Kf/UL+Cji7tva4TOkqFS42QphTo+F3X2lGG+Lq9XJtpXFYbWiKdczzJHqnPSaGl8vFu0D1YUYG97y4eOi9rrNmp25HIife3lnDQyvB0oHuFDXVa/lt/PkHfTr3NOGJWL/aW/gxvtctnlvPM87RnpQ+O61+Fz8ln9+I037fCqX2hGpFNr7j0lRM6P3BuRPuIHGqPnFcytiHCei4Zop7tNnfPKSwui18nzI5DRzruo6HmhziO/x1drfqHauVEuct0i59W/bkWF1Zm5I8fW4SYNr6ss/+uKupcjFwt1+Ym1l6VOrnW5uttkduF87+uIH8ys7fVSIufhqJ8d9bquchH/F0ak06XrnCc/sYrs4ebVqj8JqxA6ePl6Sqi4Nvq72gv05htySAyUo0gaq2QeG0D7ef0iZ9WaN37k6H6e2ZHzeWDWml8BIZ1RH+SIhuSW5RWV5OdWl3u+0A+vR+WG3Ufx+4iHuw9EEe/nRaVBJ4w6eczkscbh65XM81YbN4W1GnffyE/ENjDukx9x41S77Fm1y0b9JQC/wWeu41VsIpHO9riRjK1le9woT6zh9NZGOM4Rw3I/FCp3paxblLsK9IxyV4MeUe4a0CXKXQtmRLmbPevyTZZy67jO3m27k867beu5vXrbTKS3cnlwoT9xaZZytsel093qc52fbo3HBehu9riOdLd4XAZdd8t1u+ne8Lh36d6k89WxP8S9ZLnu3X6/PsbcmL+G9POKGZGBncmn5Ywa2tC6UQexiQZZAfTG7Xk92THeQGwPhITet0btP9uIjDFXoM5KsLUBdStJZy3exDMHUPNmZN2tku6KjBvncplarnkb7wkOvO2Wiw8t+8h/me/geQLIAZHbVvtvLpgPWuntRZ2VYOs7ketc4Knj9cNZN17EbsRpQc7u2nUXw8kx8UeQyvKB99A+YOV7keWrdRug7GoQYPnsI5SXY+kPIJPlt0q597Hf33fLL5bVZF6Os5tANsvvqbf8r/s7Ut8t4y2At+92trhdfD3902RnMdj4aeQ2b/gV71eBU2NlRXUD4oajpug7CM+dQzd1B1MrXleGK++yiu6NjAOWzKtjsX0H/YrtwWORw7wn76jdE5+IRryHXFQ34jspEpltXPnIM3yXKvfWOnBUl6qjAp4760TP8wUVwxivt0X/MIMW7m/nN3Q9ZF4jfitD6kj/bXQddTHa4N9kkDqh7wbNnN34OkW/ok7jvoNUJfnG/B7ygtDzg4gKp1oK+Zt6XrozHeh5a2Y4tc7RNXlOg87be1AuB/VrwPT8I9eR7+4bhvu7lfKavytzxO2Suy5McvNq/VKju22BAqxPoeNsLYhcl8yZ9a/bRszLLDryutegTE2x86t+71mve4Va98bWy8s/7HPZs+p8RIFBKGLElO9nhgod4T35QzgRf01tnheeUNu/8okjt1dj/lY+jn2wFe275de176yCmdOKMfGud1mBYRQXLpBQYei1/rEFOGZ5z1ddWiX/IcfMyMBJ5DxvcMPzGwXRv7Ef+kkoz89O/aT75bM=
*/