//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_SIMPLE_SEQ_FIT_HPP
#define BOOST_INTERPROCESS_SIMPLE_SEQ_FIT_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>

#include <boost/interprocess/interprocess_fwd.hpp>
#include <boost/interprocess/mem_algo/detail/simple_seq_fit_impl.hpp>
#include <boost/interprocess/offset_ptr.hpp>

//!\file
//!Describes sequential fit algorithm used to allocate objects in shared memory.

namespace boost {
namespace interprocess {

//!This class implements the simple sequential fit algorithm with a simply
//!linked list of free buffers.
template<class MutexFamily, class VoidPointer>
class simple_seq_fit
   : public ipcdetail::simple_seq_fit_impl<MutexFamily, VoidPointer>
{
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   typedef ipcdetail::simple_seq_fit_impl<MutexFamily, VoidPointer> base_t;
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

   public:
   typedef typename base_t::size_type                            size_type;

   //!Constructor. "size" is the total size of the managed memory segment,
   //!"extra_hdr_bytes" indicates the extra bytes beginning in the sizeof(simple_seq_fit)
   //!offset that the allocator should not use at all.*/
   simple_seq_fit(size_type segment_size, size_type extra_hdr_bytes)
      : base_t(segment_size, extra_hdr_bytes){}
};

}  //namespace interprocess {

}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //#ifndef BOOST_INTERPROCESS_SIMPLE_SEQ_FIT_HPP


/* simple_seq_fit.hpp
Ris+XpPU17+xfnxLmS+xDb5Gxddq+7CT+eLa8O+Ak8/pn1zHCOqu2OYg+eQcXH/G4BU/vqgg+ZKD4GuQcx3bW2seUCXzTeB2LoPvLp/C5WQqMIPPjFzOZ00W8lmTKj5bsobPmtzC/PfyWZKdfmdJtlhjYrSlmjupF/JbXouB0XyGoht/x/B3An3LdvhKbl+WUHykeSm/LbaC3xRbxW+tVDPfrWy/mc0j+a5M7y/k+YVNwN2/uHh24f/p7MLBX1w8v3Dx/MJ/x/mFoyirzSDPIbgBZYMqQVtAj4COgJpBMb9E/oAyQUtADaAtoEdAh0HNoKhfId6gHFD5ry6edbj4d/Hv4t/Fv/+mv89P/39l2bUX4P4/ocO/EbGdxHvq+zU6/CVx4nAy76nXysuO5k3Lh1JLXn7urLkz2rPeT/7wGj6mHvildIaigRvJvqNu/Z/dqr22m4LYd29r7VnEIZbjgDVlKx+WhEpPiljlsBBUIPQmZD7Ujqg4v3zY+ffg9z2Y12+dv7auRrvXpnjVnTHQCVleJ5Yk1L5FC32tON4D+QG5nWMkISemgnw6bxm8z3AzcCqo5Xq/q5157lzvZ104Spe6W4V1Wjj+9r2oGFbsWmPK+fYK4BIhn/d98qEaAhW5dsjkfb1MEnl/6SDZX25CT89YBYoxu2rkZffH67LkZe01/YTsr8R8vYtehu8rGf5TGBre+mIkxv8uoYrTgiee8oTqDr5OkVkUubsqntyJLCitWC7Tu1/kqXX3EYxJXUja7WulXMSSvx8ZPRHfn4Pkvrj0H16Q+z3s/r1u0tzn716YD0Y56oDvW6JVWdoEvBV0G2gKmamylaPXBZwWTeto46lsxFL+hkV/etp3tuDcyp3XZSt3lEfIO5ipvIM55U+9yAvON/aX0k17ppwXMKM0Ix/IzH+vat8F3KvS7zG1fw+rvXsu+j2v9u9tbRguzCMfSO2dbrz+SMHcpyJm9On19IXb29LvMX32e17/q3tS8k0l7oN5fBBpvcWk7soR2IvXC3v7rXPuZHdF5M6+ztmP334byHezpPD6/iDgMF6/TgMOBc4EpvJ6+zBgPtsvBF7K6+IjgYXSnN8c5DZV9hcI3/7m4DjwJfL66jzgVHa/AljF66vX8vrqHbzP8mW2v5/XVX8AzOa7XubzvlEu8FlgPvC3vJ76AvAK4O95/fQlXjdt5nXQOFOugw4FFvFdL8XAdGAZcAJwBe8fzQEWAsuB5aaM1wq2b+Y7YBKebfvdoaX7Lr479N+2pvqf+vbQxXeHgl9r/U97e+hCr7l+Hu8OjXoWYYPWPvufsV76uc3/vfU13gsw/xfnW5aLM1k5oi9vqK0rqiotqikl8wqYn2kkc29dUXFlGd/1f2e04bhLP0kC9at1cNf4Gs3D5k2dXVhcW1ZUU1JeWIW5mJw70JyIJjT6NYLX1PyphvRSi5ETurmx4lW6uqR3rZtXMa9aP9gSxBkcn66uiHMsxVnNJ0TcYiluaj5BcwGKg/0s3Haerw4KkXk1ANgA93tkPhVAroU5C3Jz5uVliSOwNt1j33n0GOCTxB8XciNy6lHTpX8vwZEndTX1tXXO/NPyLqssWl5L4Ymx2LNkHxGyGjvZD5odNflq96O3nDev1Ov2Kl61llFVtIplG+PHG6PlrRXMxJvgx5vQgjeUyldRzXKOQ5Ifb1IL3ooYmq+S4m9fnu8mvi7sHzMvgevRoMsg0XzEKM90q7kv62jDDcXlKPl51gwR6wLgH4JasxI1cpvpMQZDhzIK8t6PeH2J9EDdntCO7gj3AHeWOxX/DnMPCA/xiGi38F+ti71P/ncxevFcP4TieAByGotxotuoxkrdNiOW3Pc=
*/