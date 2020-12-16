
#ifndef BOOST_MPL_AUX_RANGE_C_FRONT_HPP_INCLUDED
#define BOOST_MPL_AUX_RANGE_C_FRONT_HPP_INCLUDED

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

#include <boost/mpl/front_fwd.hpp>
#include <boost/mpl/aux_/range_c/tag.hpp>

namespace boost { namespace mpl {

template<>
struct front_impl< aux::half_open_range_tag >
{
    template< typename Range > struct apply
    {
        typedef typename Range::start type;
    };
};

}}

#endif // BOOST_MPL_AUX_RANGE_C_FRONT_HPP_INCLUDED

/* front.hpp
0mW5j9AZn2BlfIo18Q9siDrlfTsF7Iq5sQ/aSXnZ43DMg0noiDOxEM7DwlKORXA1FsWD+Dp+hU0xBX3xMjZH4tK1wKLYEhtga+yGbbAXtsUobIdx2B7HYwdcgB1xCXbCZdgFt6AffoDd8CR2x7PYCx2VdsZYHoehO8ZhB4zHTqhHPSbgcByBYzERp+EonImj0fhsQ87T5PxN+2xjjrynMB9L4gKsgAuxNr6N9XAReuM76ItrsDWuxfa4DoNxPUbjuxiHm/ANfB8n42Yply24FLfictyG63A7bscduBPJK9kO5JwN47PZDjZIfdqIzrgF3XArtsNtOBC3YySewhg8rZN8yiXnUnKOpSy/vpJPqAwdpd19V3TBbrL87lgF/dEde2AjDMDm2Bt7Yh/sj/0k3v44AgfgOAzCGRiMszAE38cw3IWD8HMMx/sYgeVI2xB0x6HYCyPxDYzC6RiNszEW1+Iw3IRxuBPj8QAm4BEcjmfxDbyHE/B3nIiFlfc9sD5Ox2Y4AzvjTOyLszAc38IEnI0TcA7Oxrm4AufhJpyPybgAD+NCPIVv47e4CO/hYmnPvhLdcBXWwjXogWvR+D6hnD/JedVRzfuEZaSelFM9A3PDulgX3bE+emBD9MKmWB97YQPsjQ2xL3pLOfpgIjbBufg6zseWuBRb47vYBjdiWzxqezb1Up5Nbf7I+udTm+cXyPEzKt+V9GdPSCKsJhwkpBAcVhXQ1SL4r7I9v7INtsE22AbbYBtsg22wDbbBNtiGFxn+kuf/oS+n/f9pVft/f7lX5CPPwxsSWinP313Uz3Por15nfT/a1j6zMT5flGekmuc12mfpaZJOP0lnZ0Ibb6Zr0xk4LCEiZOi/PK3qtB2U5/xr5JnYSkI70jbQVZ22yPjwiEH6nLyL8Ly06QnRVuSjPKvMeO5VTP2uQnB8oHZ9+klbgvqS1/UIyjch3EtmXR+Pl1wvorJ57qx+Nn5D0tZR0taesF+5sZVd2v4FdSEK1ek5KA+nS8iznaLYQXkemk16jMmRNgbWPt9+gfJXngenkTn7WPBxxkuXIi1YQspdnkEHGhIl66N+r2axtD/YIfV5i+wTfEtrnvFa+Vz3h9Iv/lzXmrpt8Zmu5n0hd2mP8JrUHR+p125l1OsVPyzuL6rTki6e92e/D441T1dC8EtOlzX5a9aeSZ79t5J0tpB98EFtOv8F252lfXAdSZurVMJoqbNDTGWb0Y4tOprUPbd9z7PSFKVJU2i2bWR8ik6UZ75/a6iztSn4H2xTcMLQpsB/7Qc/nllxas2au0vt55QYV+evaVPgq5NzM/SRZ0V50Itg6mvLDstjaXTD8lgBG2JF1TP0NFmOXzbP0GvIcmrKcmrJcmpjPayD7bAudkZ3NH5bWs57cI0sV/1t6cnyLGsKOuN0dMcZ6IWzsAm+hR1xNnbDOdgT5+JAXICzcREuw8W4EpegMZ/kfAXrZ5NPMbJ+seiCw2Q942X99Kp8SpLldMwmn0bLcsbIcsbKcsZhXUziXyt8E9vjeFluihJkuSXkvbeS/P+MLHe1qs/sErgGa+Ba9MB38TXchH1wC/bDrajHbTgaP8AJuBOn4YeSb7vxPdyD72My7sKPcDfuxWP4MX6F+/Bb/ASv46doJ31e58PD6IhHsSh+gawn6yHnDbhD8q8oLpD17CD1oRM6Y3d0Q3+sjz2wIfbEptgLe2EA9sbe2Bf74Ajsi4nYHxfiAFyEA3ElBuMmDMEtGJpRX+Q8AF/Lpr4MlnIOl/KNwPI4FH0wUrWc2DKWtk+U5dSX5TSQ5TSU9fRW1buDspxW2dQ7X1lOM1lOc1lOC6yGLfF1bIUtsHXGcuWYiNHZLLc=
*/