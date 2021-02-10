
#ifndef BOOST_MPL_AUX_CONFIG_HAS_XXX_HPP_INCLUDED
#define BOOST_MPL_AUX_CONFIG_HAS_XXX_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2002-2004
// Copyright David Abrahams 2002-2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/config/overload_resolution.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

// agurt, 11/jan/03: signals a stub-only 'has_xxx' implementation

#if !defined(BOOST_MPL_CFG_NO_HAS_XXX) \
    && (   defined(BOOST_MPL_CFG_BROKEN_OVERLOAD_RESOLUTION) \
        || BOOST_WORKAROUND(__GNUC__, <= 2) \
        || BOOST_WORKAROUND(__DMC__, BOOST_TESTED_AT(0x840)) \
        )

#   define BOOST_MPL_CFG_NO_HAS_XXX
#   define BOOST_MPL_CFG_NO_HAS_XXX_TEMPLATE

#endif

#endif // BOOST_MPL_AUX_CONFIG_HAS_XXX_HPP_INCLUDED

/* has_xxx.hpp
XffSYnvpxRaHw3nDNzNPijS2WooWpywqqkzR3wPunlSTtlN2tVot9z+wvFt1D3Wjnnfd48diTWdBbHXObrHdbpBdqkpjpfmtqNa0uotXi5vb+e9383jFIusYOLI6LPYzxNg8YsPbIkUWNViXO9pOhRYdvOVcOODYNpjQRbXFHutOhHBTyEa1KtP8+jq2/Au7xz4KjSHE2+oc7AHM6gZc2/bB8UJ/FHo+fLpZ9dg3vlRP2GDKf92FMIuXF1/mZO4d8Tzb2V+LrlJIoQtVQV0ikQTtU5uobSVPpjE0adzf3/PZ8TyldOCqQVFuJn3D+f6xfw6iXKum0DmZ46sZ9x2Xu/6QNipFMJO+Y/uDoe05nke2bYtNLtp8ohvDxAvdq11NGBqftZXrTfkLyFw0LepJ0SoeBP6YO0fn37Ba6zwE21w5sjqq94wTzfYb1ok6mMHi899e9R+lMDApqIdDFh18l4rMUT783wE/oAP+s3IfSkyrw9STGFyWhTnQiYHcL6ZkZlG7T2nKcq1rOvGyjDIUetsgScpPcby8ZrLZ1VqxTqUi67gNUSU2OD2o2SJeAedpV5In4t4I3DkVx6hYCtu6VCI9h41Ki6wgwwZ1rsjwpj4gqvR9NQjD6kAgkmqzIYcu4dCyzq4I8noZnhn8
*/