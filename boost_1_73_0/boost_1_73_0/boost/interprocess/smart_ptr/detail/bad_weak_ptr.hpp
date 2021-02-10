//////////////////////////////////////////////////////////////////////////////
//
// This file is the adaptation for Interprocess of boost/detail/bad_weak_ptr.hpp
//
// (C) Copyright Peter Dimov and Multi Media Ltd. 2001, 2002, 2003
// (C) Copyright Ion Gaztanaga 2006. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_INTERPROCESS_BAD_WEAK_PTR_HPP_INCLUDED
#define BOOST_INTERPROCESS_BAD_WEAK_PTR_HPP_INCLUDED

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
# pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>

#ifndef BOOST_NO_EXCEPTIONS
#include <exception>
#endif

namespace boost{
namespace interprocess{

class bad_weak_ptr
   :  public std::exception
{
   public:

   virtual char const * what() const BOOST_NOEXCEPT_OR_NOTHROW
   {  return "boost::interprocess::bad_weak_ptr"; }
};

} // namespace interprocess
} // namespace boost

#include <boost/interprocess/detail/config_end.hpp>

#endif  // #ifndef BOOST_INTERPROCESS_BAD_WEAK_PTR_HPP_INCLUDED

/* bad_weak_ptr.hpp
T56q52fvNtKD/F+O+X7zNEkf09k4nY0m6WIt9pgtlpu38jnvfiSty17zst2IapetRtRo1JOolVzVolan2bpKmvVeK2k/5fNkA/OQ3dl4n+T8bPeSMkHTyd02R/nDL5une2kS4VX3WX6bZnfDac78/GCbuW35O9nsfvKwmg/XT26nw+V93gjPSZyn20HrJCb9fiVJ71YPlaiyfvxHnvLBoL951p/cDQaf4v/+nsx+ifPJwGh58O+XDXHofKwncIgzSOZncannUcfZt0VlMLi92b10k3x28gRmYCLFzN7xIQERuIxVgOci+pZN731V3XvfF6AY4dW7e5OP9QoUDmO+jvJnOk2Hi1T8iRKPRwR2fMLR3uBhXgFhiMlNIfuEQXNQIRe76HPmniJcgJRZhOkmK/rEeUb4g7hQCj53mwFFuoVKx7G30fo3beDvGTBaHvyZTTzWEzjEGSTzs7jUw582cAYmUswc/Jz5JojAZawCvCKi9eNdC6yf+XoxMFoe/BjWO9YTOMQZJPOzuNQPj0je930BitUPjkUvbx/rFSgcxnwdBdkDQOMRgR0fsAdwDg/zCghDTG4K2VEJ3gMgk1zsomOTYA8gGSYIJ8EsJpMdpcTjEYEiaNGxqnB4mFdAGGJyUxQdtTwj/EFcFAXH
*/