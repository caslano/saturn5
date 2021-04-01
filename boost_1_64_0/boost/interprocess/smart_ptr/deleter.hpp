//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2007-2012.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_DELETER_HPP
#define BOOST_INTERPROCESS_DELETER_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/interprocess_fwd.hpp>
#include <boost/interprocess/detail/utilities.hpp>
#include <boost/intrusive/pointer_traits.hpp>

//!\file
//!Describes the functor to delete objects from the segment.

namespace boost {
namespace interprocess {

//!A deleter that uses the segment manager's destroy_ptr
//!function to destroy the passed pointer resource.
//!
//!This deleter is used
template<class T, class SegmentManager>
class deleter
{
   public:
   typedef typename boost::intrusive::
      pointer_traits<typename SegmentManager::void_pointer>::template
         rebind_pointer<T>::type                pointer;

   private:
   typedef typename boost::intrusive::
      pointer_traits<pointer>::template
         rebind_pointer<SegmentManager>::type                segment_manager_pointer;

   segment_manager_pointer mp_mngr;

   public:
   deleter(segment_manager_pointer pmngr)
      :  mp_mngr(pmngr)
   {}

   void operator()(const pointer &p)
   {  mp_mngr->destroy_ptr(ipcdetail::to_raw_pointer(p));   }
};

}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //#ifndef BOOST_INTERPROCESS_DELETER_HPP

/* deleter.hpp
KQS1uGRVO7/mHyEnAJnUZpCOFzJF6M0v/MLbTSisGUw7B/bnHu8cyPS/DpXBFxgwgdlwK5vgFIhI7aRHtrzhaTJeZO5vaZujjhToYPi8/BA2RH4k0gd9GJkxQ8WmVMw7nS9SUc1VxkU/R5tFyjBOur6PuPSmZOabq8FyvlkYUc3B31oVUDAVB9sm4UZbUKw6qlBph1HlKzDRqCeYCsurLFWCwASNamuNw0Yx1T6JjzJIxDxm32PXQKqaQleKWE47EXeNN4uz58DavVbRz3QjHtelEPiNoRWVOLE6BeOIF8trnoiubA3xiKW1fJyjLBTY2ThwJgQ2rNFJajW86ynd65tBpGAJsub1uUS0UHLKG52UHjGEHB5H6jNWZ+unGzKpcllL5MVk1df3svJIqDlfpAzEx13vIMCtLoZWUGzgS5O6VTNE8zQaiWZiZOmk12ov5britx6feOX/hNKaldlyN9af0WqezsWXfGHKbuwa7HVW8BmHc25YM21OWZXCfl/VRqKfVoDiBVuFKSBuO/MsIIhhRyI6qXnc2l9lYOoCDzlNLc7ftu0t065Msg==
*/