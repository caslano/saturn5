
#ifndef BOOST_MPL_SIZE_HPP_INCLUDED
#define BOOST_MPL_SIZE_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/size_fwd.hpp>
#include <boost/mpl/sequence_tag.hpp>
#include <boost/mpl/aux_/size_impl.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/mpl/aux_/msvc_eti_base.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    >
struct size
    : aux::msvc_eti_base<
        typename size_impl< typename sequence_tag<Sequence>::type >
            ::template apply< Sequence >::type
      >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1, size, (Sequence))
};

BOOST_MPL_AUX_NA_SPEC(1, size)

}}

#endif // BOOST_MPL_SIZE_HPP_INCLUDED

/* size.hpp
w42d9jkvXRGypsKTtqMMsAqhVVpiia5yutUFoyPHL5BZUfjyERJ91iMbNr5R22vVhDlcJnOaR9D3JcgSaaDTnivfQ17emjkMj+dvwfqYgFQmmRYtBvddy7Hx7kmTAtA373p+Sd7r0BME4AY4ccqhguNJHOO/bhU9uKAPwjSMaWVIlWe+A9N5Y+EQWGHTzq8IbKBCaw0w/idc+aQ9+ovMKhXyLSXyMhCN0bMm+gjCBXEpspRM9i0OZogyXGa1DFEe+N5y3KWQC9h1QRwVMD4xfG2n34yQguPpyLCXYG4vOzGpmU1G/eE4nt7qGJlVXxbAQNykOG6rhtl8EQ4bbOnHS3Jfns0SoD6Sj3g84l+FOoiKWd/OfIUpkGnE6shQoKOnTcy2PtNQTHTW9cYPRvgFTcpVPoy0WTbgVuyCc04ZNH0kc8HelbOHL1xXPef3FtCwCLSIl6hCNZMz1fHu/0SSuRmgxeXGCTeVIjdhVSiJcy9YsoxdHZQ0d1frNWX2DUVNmK6I3TF66VX4+TLQWqQqXs/cGi1HA6ormbfefwbsk8j2nY/bYM/mzVRuGQ==
*/