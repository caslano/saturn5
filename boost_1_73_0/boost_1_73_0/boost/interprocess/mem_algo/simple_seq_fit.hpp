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
ZqMdUU2qykT3FDlpvnh+ENLo8J/nB4GWhy9OTl5keTN50QyUC6UV6Bc6efU0I90Ps5mhjxfHW+Zd/Ly87ZtDzu/O7sbdO2oL2gxWx36qD5qtjV1ij4jb/WbqY2vitZXNszGCliVGxMu2UsokB8chBZpI9uiOUqpkHDdXSpOEiJJSOsSO0iulQmZfUClVMo7GKaVJgv+plA6xY3/KqJBrjrlSquB9I62lKOy+5J5mrrAy6nas8PVTpVD9UYHnslJB1Xo3IlZWKqPC1lww9eodNW6ulAqh0TgVa650C9hZV6ZizZUnQPJUKEgRPYNPKV2SVuNACOWbR8ZJ40ppkmlBrlKKxE5gV0qFmGXBSmmQcWqpUppkWt6nlCKx01yVUiFmkaEyGmQdI1VNE7xf5BgfhRRwVOLHRlVTAd58rnFRlVVR+hFRs9Zb8XCVNAhtPaFerXcX4SqlwcaiPxXrrbD1t7auVLHele/1c65BDa09Xd4bWmB7+ugS0/twDs3S1c375VLbTnvj0p1b9wuIJ81RDKo7eiC0PoEJdqtM1bS9Fbt93d6u8Eb+rTm9LFBgo9DkUXdc5+AFQzovDldlHVpjzaBtoa+5WnBpIDQn+RLnNULLPRbGQryiltJCyWIW30LHIpbrQkXWBb5Qjm1J
*/