
#ifndef BOOST_MPL_MAP_AUX_BEGIN_END_IMPL_HPP_INCLUDED
#define BOOST_MPL_MAP_AUX_BEGIN_END_IMPL_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
// Copyright David Abrahams 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/begin_end_fwd.hpp>
#include <boost/mpl/next_prior.hpp>
#include <boost/mpl/map/aux_/iterator.hpp>

namespace boost { namespace mpl {

template<>
struct begin_impl< aux::map_tag >
{
    template< typename Map > struct apply
    {
        typedef typename next< typename Map::order >::type max_order_;
        typedef m_iter<
              Map
            , next_order<Map,1,max_order_::value>::value
            , max_order_::value
            > type;
    };
};

template<>
struct end_impl< aux::map_tag >
{
    template< typename Map > struct apply
    {
        typedef typename next< typename Map::order >::type max_order_;
        typedef m_iter< Map,max_order_::value,max_order_::value > type;
    };
};

}}

#endif // BOOST_MPL_MAP_AUX_BEGIN_END_IMPL_HPP_INCLUDED

/* begin_end_impl.hpp
PQNlewZJnXK4arlCWY54WU6/LtodQ1TLFZcSX5gs11Pi66XOF0v0l4uU5UbIciPVx7eU5cbIcnGyXLyqLj9clouV5dR1+Q9Lek/HmvgI1sMZku5Z/AvEWdgBZ+NozJb1b6koZRZShqGsfzB/r0Pls0DWv0TOj+XYFB/DFrgCW+FKbIerMBRXY3dcg31xLcbjOkzB9bgCN+Ba3Ih5mIu78Sk8gJvxc3wWv8UtWJWNfQ5r4PNYG7djF8zDnvgS9sMdaMCd+CDuxizcg0vxVXwZ9+IefA3fwH34Ge7Hs/g6/gPfQA/S5gDWxDfRG9/GFngIQ/BdHIrvYRS+j2PxCKbjUZyLH+AzWIAv4If4Mn6MJ/AT/AI/xR/wBF7Ek1iVDPMZ1sBTWBNPoz+ewZZ4Ftvgl9gfv8LBeA5H4NcYjd9gEn6Pa/A8voD/wFfwAu7FH/EIFmMx/oQl+DNewhJUKp8uYkO8hE3wCvrjr9gVr2JPvIZ98Xe8DytUcMmKw4o4DithMt6GxOXiX9FcPmIqLzHwvbuq3mQH81XD3Vgf96IfvoZhuA/vw/04El/HR/ANnI/5uAwPYC6+iU/hW/g8HsSX8O+4F9/BN/FdPITvYQG+jyfwMJ7FI/gdHsWf8QO8hh+iOzvzEVbDY1gHj6M/foIt8SS2wc+wH57C+/E0jsIvMBYLcTKexWn4JS7Dr3ANfoNv4nf4Hn6PBfgDnsTzeB4v4D/xJ3SryPHFKngJffAXbIy/YjBexQ74Ow7EP3AIulK9Px7dcBJWwnSsivPQHRehB27HargLq+N+vAPfwDvxJNbCL7A2foV18Hf0xorkh7p4O9ZD8gvl0lLOgaMIBiVOjJfr5yTJL+nYGCejP07B5vgQtsKp2BqnY0echQNxNg7GbByOcyWfXnaRsgwp41Di9eHv8xLvAOZzxfuxOg7Ge3EItsEI7IZDsQcOw9E4HOMxEifhCMzEkTgLR0k+jsKVOBo34gO4GaPxVYzB/TgG38I4fBfj8UtMwG9wLBbhOMmviajs1AT0xmT0wYnYGFNk/7n9lbINlpV0r4pRsv/zJd0Xohcuwqa4GFvgEmyJS2X/c7AfLsMYXI5x+JglPimrwJkO4nta0nsTeuBmiecZiedZ7IVbJJ7ncApuw6n4As7AFyU+tkHKITj2El8VjJD4VinnMT4u639CjutaDMF1GI7rcSJukOO5UeLNlXhCK0gZgpQtGAhKOgWbx7WXdKyOtfAOyceekm/vxPZYE7ujl1z/amME+mA0NkBjfTlOwMb4IDbD6eiPj+LduBSb4xoMkPx1r1z/WuIHGCjXuVb4K7ZGrulsN8cZ22AotsXe2B5HYgechyFKPNgZV2AXfA274hsYiu9iN/wWu+MPGIY/YS9UymD6oOV96I2WfjzIx7bv/ea4qt4jlvlq6cwXU8nUlrF4ovutac+4ytVhm8aM4pvfrvFaT949XeV6y9s3evdyL3Mbxzy263A425/i7pJb/Ne0dzxc/J/Z5vGEj6um3SN/k6bmto+Xi51r/xjBMiHzmY/1mdtBblvp+m9rC+n/z7+uPWQf4spf6fof0S7yNNuhbht5eaXrLW0feSvaRvpxXoYRkgk5hD2EQkLlVN59J/QnGAhrCPmEIkJlA++vE8IJGYQVhD2E04RrBL9JrHNSedvK8k/5p/xT/in/lH/KP+Wfsn7+ovb/tFz+8+3/lTb+S1Vt/Ck70IxpSqhPecssTTvRhEynxkQ2v8tdzAoNSsMkVf/t0rbMdjwsib+11Cm1JHystGHWxF+WdtuVVXFJmwraQEg7blWbl01Sjl2gxC3WYd99Z2valcbRUCvNmTZCpvZ/x2db2/8dnG1pA2o=
*/