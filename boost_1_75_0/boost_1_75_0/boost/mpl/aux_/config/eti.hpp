
#ifndef BOOST_MPL_AUX_CONFIG_ETI_HPP_INCLUDED
#define BOOST_MPL_AUX_CONFIG_ETI_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/config/msvc.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

// flags for MSVC 6.5's so-called "early template instantiation bug"
#if    !defined(BOOST_MPL_CFG_MSVC_60_ETI_BUG) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE) \
    && BOOST_WORKAROUND(BOOST_MSVC, < 1300)

#   define BOOST_MPL_CFG_MSVC_60_ETI_BUG

#endif

#if    !defined(BOOST_MPL_CFG_MSVC_70_ETI_BUG) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE) \
    && BOOST_WORKAROUND(BOOST_MSVC, == 1300)

#   define BOOST_MPL_CFG_MSVC_70_ETI_BUG

#endif

#if    !defined(BOOST_MPL_CFG_MSVC_ETI_BUG) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE) \
    && ( defined(BOOST_MPL_CFG_MSVC_60_ETI_BUG) \
        || defined(BOOST_MPL_CFG_MSVC_70_ETI_BUG) \
        )

#   define BOOST_MPL_CFG_MSVC_ETI_BUG

#endif

#endif // BOOST_MPL_AUX_CONFIG_ETI_HPP_INCLUDED

/* eti.hpp
PvMGB8/nxahUZ4sN5t2F+hNaIGBEYfyyY2pSveD4EkBlMOAEV2vxp641QC3a7l9uyiYAIKbzA+Tjkfho1+sgqs0FDJA7xJM+wxBoY0yFcyIb8hEzkVqdhawiGzb8ZvueOl2jPhl0lGxA5/awlxbAqWAWnPPz6eJ+PHPydKfbv/xC0prJdmI4PiB3h3fR5mY7fCfqDWdMMJHuy3aokNwN68Ee9aVGt8yNcknuGDCFh/ZSmVJxO4/Y4mZ7X4T2Ui+O3bfnhiD5bYbTl8w9dEwwsyyzM903fAwY3UGXvhj4toSvZxpUk3RgPEHqMmze4aaipCu/CbzyTx3QZnaSujdmE/nK7zdKHC2ASBp2On+95P8aNakmOX/7+klrsqhvT2ZyUTolqyzJ423aumfpUoD9KKIMnsR7MlGttPLopZ09Ao2dSmZcBPrkJzC4EIqQbBI2Q0mo1+E3pBU2+udsJOjJhXm0l4n3b/dkwEEf0U0yY4WFHo1roZ4N/n3Q9PdzELQEvvXmoiwJkellfcWIaOKVTI7rxid2D1myiSG0w8nVAr2HoZGCppYSx6hG82ep9gwVxzHepANs/2TIkGAzQzFy3wAzPTe9RsiWaIiJpBnTriSJHAifI9U027G1WxdOYC73V299pHLLqhvgAG01Iar/YJKeS8tDJ241C+jER7n69Pfp0WwCrgbcQuzqF8XHb4pdoqS3OWoLS8Kyl95n
*/