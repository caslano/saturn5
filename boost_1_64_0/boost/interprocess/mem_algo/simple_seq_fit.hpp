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
Rdt3K0tXlsDLHvs3Q1d6+PXU/Y+N9fDBnMh4egVYPVQBKeU+kUk/3SlfKW7skzUBRU+g4Lj91Cssa8QkEQjlyQrbYKsj2Bd7JOcij8x57ZwGjzAEJvMoePvypZ52lL3sivwujtPsoi3gmfXhy5gJRxcXcA4MYaDv3u5T6RayEtMSLoNtTsYjvQQMr8j577r5ZmNOYDrmkML20iF2sA3Ssg0aQ/LDZaZPmz36dJ6Qn/Hf6sK8/Y4AViay3v37MxtAccgiKcbcaQtTGowlGss3dOdqgVLrMEXS0Sh+hBzb8MT7CsHmBVQp3CLBQGVdqgaCnmC+st8fjGUBpEGLwkqHF6iMpOEQNMA83ShSD1uimbh//+gpBQzg91SveUUALn5at/geNVZ4vUiEsCrx4w4rl90ZAr14y6AVafnPVTGOyJaJniMhp8uBuf2aOAs0rRuL9CamduatQ7g9/bYy4xG/EZF7vMLsbROkJPC/hTd04g0+MjtUZz6axH7zurIrgxXGCeU21l4FEHYzBQd74vhPMahfBySXEG1p5EgtNzTR51FdaTVGLmheFQ6hCQ==
*/