
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
0cPoA/XvW+gOs3MQ+uv3d9Y7n3JFT8KttIPgLzjgjt6xrBPqCu+0zhCQAKjUMXL5N+irevrTDyI+d7j6WN8T4BLBQYTPtgglSbeU3sz1bAdb9yhIW6RWrQYz/qZIl/H+WPzYaCv8sHMh6DOht+STybCFqAOJa3rM3zKlcOnwX+JzuzfoWT7lCicTRyd8JUkmPvzjXVkBIVfRPnk4AX3ky0i6yFeR9H2/jdMpvNyKgRL1bXN7YW7XBO//9utl5Mb+lyV0vQBndbZU8Vb/vy6h1yyNbxgs1Xor/3UJnYBSQ0jYzd5amsBo+v5QTm38tbxBH3d1cjQDQGJRbihLUgvMXGES85CUnD4pb3E6sjgtPZQSeti3E8enr57PFd1wvfIRHko8y8dqcxSybfyJP2LEcGLAdE/L9JNiO9nIN/L5KbeZd4DY0QNyVi59hb0Crs7k9K3JuFhcyvyM2uo9ra1KUf58dZWF18Mj+VLzL7gTBQJDDdzdpffSvZdvuCO1pKNhhEP7pce1ZEYiqfyxpqQOyg3+K2pP1V3P+tNnPnZ/+lnfWqi3xyb8Yo7T7L42Fs/MtLCW14/nx0qj9d7nRUJ2nuT5Nzf00mPvPdDr0jjcueyxb4Ldinif309WhjPyqE8DfHOS0/LypgukT+4Je+0MuLvrgiJW5DRSt6cjSUI1HcwAxa+dWIIpOadrTeS/UfBSGb033gnN6GHWZiEL
*/