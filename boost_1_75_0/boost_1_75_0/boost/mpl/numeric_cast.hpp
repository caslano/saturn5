
#ifndef BOOST_MPL_NUMERIC_CAST_HPP_INCLUDED
#define BOOST_MPL_NUMERIC_CAST_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
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

// agurt 21/sep/04: portability macro for the sake of MSVC 6.x-7.0;
// resolves conflicts with 'boost::numeric_cast' function template.
// use it in your own code _only_ if you care about compatibility with
// these outdated compilers!
#if BOOST_WORKAROUND(BOOST_MSVC, <= 1300) || BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x570) )
#   define BOOST_MPL_AUX_NUMERIC_CAST numeric_cast_
#else
#   define BOOST_MPL_AUX_NUMERIC_CAST numeric_cast
#endif

namespace boost { namespace mpl {

// no default implementation; the definition is needed to make MSVC happy

template< typename SourceTag, typename TargetTag > struct BOOST_MPL_AUX_NUMERIC_CAST
{
    template< typename N > struct apply;
};

}}

#endif // BOOST_MPL_NUMERIC_CAST_HPP_INCLUDED

/* numeric_cast.hpp
gSgEtjDxCDZwtFCxgw70Lfmta8V3tBfzNc1xO5U/mdNfXfcODBvuQBVBiG9BkUID6JgegRKYHgAnzCfAEOUVTDmog0EYcc//2h4T0oe+J3qjT3mFC3833GMaLgvqaQXs1z0+wc8ZdpTFaKHOg+MlTdwC0lvcJ67aMm6uHPw2B7d6et90XlJMwByItD2DR8DqC96WPc1HBJ/oniGHApG+MMSAhtPtZvAOlls0LAFG4xMPw5lixvITzM0tZWGQfsUroE1KhqTQ3y/4lbKW+UQ5sZWzvP4e2cX2dT32AsplrRs8dpeGNB+5aoEA495N8ZlLi97KxdWCDtspMZdQ7SPifXPomRmDod9FSXV8rutD45Lfw01Twz7c79D1nAT+qk4pcA/ol6y5zcUvPX3jSvsHLobU1LyVv7H3rnQm8KVYi6h4/JiE65TFEXGnz/xsaUmEYhKVNzLdWrDe8fFjyHtnUx2FYDimL0vcbcoC1pPgy1zxuvfHawl5OV2GQMrIRwmtZ0Fjxy0BMAgDRZsznf3+zhkMGgv9QRXiaqE8/5wjyMdNwDy9k7wBpRUx8vxLgG+nvor+NXdS629wtCmVBASvpACgXzra2i6xzi+sW84PxkF816hQ4W5kbSdwxvCDVwj4X2G2OKFxc5CXC0vCn95AuHNdz1u6rUpbmZAjx2tca98fz54bwcsIZDH16xAdRtYIEbWBnnD5C9ii/8bx
*/