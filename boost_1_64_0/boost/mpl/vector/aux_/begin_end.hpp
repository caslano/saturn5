
#ifndef BOOST_MPL_VECTOR_AUX_BEGIN_END_HPP_INCLUDED
#define BOOST_MPL_VECTOR_AUX_BEGIN_END_HPP_INCLUDED

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

#include <boost/mpl/aux_/config/typeof.hpp>

#if defined(BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES)

#   include <boost/mpl/begin_end_fwd.hpp>
#   include <boost/mpl/vector/aux_/iterator.hpp>
#   include <boost/mpl/vector/aux_/tag.hpp>

namespace boost { namespace mpl {

template<>
struct begin_impl< aux::vector_tag >
{
    template< typename Vector > struct apply
    {
        typedef v_iter<Vector,0> type;
    };
};

template<>
struct end_impl< aux::vector_tag >
{
    template< typename Vector > struct apply
    {
        typedef v_iter<Vector,Vector::size::value> type;
    };
};

}}

#endif // BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES

#endif // BOOST_MPL_VECTOR_AUX_BEGIN_END_HPP_INCLUDED

/* begin_end.hpp
4/231vwl6yVvCc77kOPNlxsPTHEc6/f6HIl43rN9f9DrLWfb1d2293NdJ3nGfMue/3ocvnc0bkUwbxPE6/YXxtkX3N7xHNeTbzdON065Y/lkHHjAeckDPpcwd7bPl5UZTxjfr4wxfrA8D02z/rVZX6Pth+sx1282jnXe76h5lsuOo0++ynhgs/OBto9X9pmHuNt+d5/xgu3QxZ9PMb40j+t78+Nox24K7vv8kOPveMvf9nezcZTz4V3V/t6RKeaLHX9E3/Nk+SaYN11o3LzKeL3xDZPvvZx2xetx0frjerldX3f9XIn5oy87/+H3lc182vl3x7G7Kl336zzu7jTzXF6HA8a7s53XXLttMg5e3m8+Pdt4wnZiT6nxT6Pj1+g4NTqvvdE8xjrrnfX7ivVyf7L7PeB2ppjHuBy8ryxY/+Q4oMr5UddhrLe81np/bHy3/XOb42bbn5UNtufvnPy+jkbjgoXGoUseMu/q+L9rvetAah2HmAfdYv+18CN+v9httvOr7UfGXDdhP3DSdVennB+LW+b7PlLcvvHwinP2B8Zn1zzu51/jukTHEavMl550ncp8x5/7Pf5N24xfvmI7/wXXGUfXh661XfW+PN3huq1i50u+5Pip3HFY2Hiv2OvheGwtcfYvg+f2nTdeFJx/8Pl1x628VyoUnGey5Rtdp3uz+Zoq8ya7jWd+7bi2y/q11PHrJ80/T7Wd+bz5Psu962/OJzp/t6/UfHk0z3PE9bPRccaz5i1/ODneaPR5g9k3TfX5b8e/D1l/eA9IcB57zYsdyTO+MA987hbbpQP2i1PNx0xxPWiueXXjiJXmdWd6XktWef/6fpC125yPsj89EH1v00ddz55sHGp7dSRsvPYu8+l1rs91vcAx27ND903Ofy41H32swfpoHLnevNtW12efMd+07meW62PG3fYvpx83LlhvO5zifMinLN9i81A3OW/n/Xem2HHovcZZa523fNZ6dcY8u/1P46Ned/vZo9HnIZ0PvOMLjsscr19Lnzy/C6+0HTeuOt3rdvO83s4rJNu+J3zB/JrPa5yu8Lo+5HnUOz8evS7W48tNzte3m7/x/A+e9P7cY3v93GQeZ1OG+dvfGVd+1P7adUgrvuZ8xBunTF4nx81rjdNup90Ofn6b8czCiONC89qNv/V5A8fLW3wfw9od5uFtH/eZ/5j45VTbHdtP269dW63vxi2H7nH9yk7r+cOWQ4fjadur9Y4PNxhPzXd8frvrN48Nul7acULX/VOd/3L++e54t2tc328c+k7H644fD+zzvnbeZmHI/ONc4yfrxxnHKyufd17L/MFM468VxtNnSn3fZ3TdwC/MY9TZfvs8U+wH/PmL7e+tt899xeP5lnmKcv/9M14X2+/Zd3t9fI/fpl+b5z9qfvKc7d/Dnnei+Qj/bon3zSnHz8muh9nj8c180PnHKtvjTxvX2L5vMq547u/2069zfP4i3zfi/OHhDL9//pB5MOYjX3cT9cE4PeHDnq/PAV+2P1vq98hN4+9/FcyP/8z8zITjX+OHTfdM/t1x45qZ5McWBccRXS/P+6dCQT20Xd/u+PmK8/Lr/mA/u9h2bo3Ph4Vd35Fuvm6K66322A9a7keMV7Z/zeOL8/62/euyXTzjeTUe8jhOGtdeMP7Jtrzt72OdL794xTjlK36PyovN78y0H7b8DuZaz+e73mVTtD2wf0x3no9yviX4+7O2/x3GKV+a4vlZr9/j/WR/d/Frxq3R9eUR45gp5tNdn/mc9e5yje8X/qv1x7/f+knjsqeNm5IdRzxgv+n3Ma1y/Hdutv36LvvpH9g/xbkOz/thyxbXo0efo/2E9ct849zvuk7N8z0=
*/