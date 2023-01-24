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
5g+D1RKlcjE8DxI7+lPtI5ffDr7aVDsEjOKvKA0y/GKDQ+63tMnvbwQIrCCzL5HexyKiJF2YXVtbqtpiqI/zsFMYIrP0We6OKL3FIlJ/3o7eCCUDb7vYiMGSNkPBkcgb7/eAL54Lx6l9IjBA3AXVhXYCZQ7FITgmKCZ4HuUgSClynn+Se3berVMX5SCYNbgyCLdHNk9r0mu249Xax8PlV04Y/GiGQRx5FHCNI+/pdq7aWmStXSZ4cGUPSsPbEi5iITlNdIrZZyxy76viKUh6gOX921aOfsLheW9+Kl5Ae1/+OIpNs1xvl3X/PviyeTVYtXLZBqO9vfrNaDT61SAbT/u0qG1TRgDrG65lQJx7RsLHslHiF7d0jx0PP0n/7usY8fvb7BrhXvTlW7rIH78MhRv01d6ag/Q25APvMceejgIqKd7pJbioRy/VdC+1BOdDXl5VnFRlpftcXq2Fcfz61HzdlkA8dTSyC8Koyku3myePlK7+HTEouh7/vCHXObCs7yULX8MzOc/0BCZB6Da+x68H412V4LIdbJpkDOqSRKih6P4qMbacm1wB+wQx4aPPs8m1PLDpy9fujg13X6wrwX3bIc09q6LqG5FMHs+r4GHZpkLuFScrMWTO+WjBNXr9kFT1x4Erueog4q1Eqo3uOZeiQc7XUlBq8I4uS7TGEvFR8ufoGkcn/eVt4/mJqbUpuJO96XRjgPG9h4Ph
*/