//
// detail/keyword_tss_ptr.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_KEYWORD_TSS_PTR_HPP
#define BOOST_ASIO_DETAIL_KEYWORD_TSS_PTR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_THREAD_KEYWORD_EXTENSION)

#include <boost/asio/detail/noncopyable.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename T>
class keyword_tss_ptr
  : private noncopyable
{
public:
  // Constructor.
  keyword_tss_ptr()
  {
  }

  // Destructor.
  ~keyword_tss_ptr()
  {
  }

  // Get the value.
  operator T*() const
  {
    return value_;
  }

  // Set the value.
  void operator=(T* value)
  {
    value_ = value;
  }

private:
  static BOOST_ASIO_THREAD_KEYWORD T* value_;
};

template <typename T>
BOOST_ASIO_THREAD_KEYWORD T* keyword_tss_ptr<T>::value_;

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(BOOST_ASIO_HAS_THREAD_KEYWORD_EXTENSION)

#endif // BOOST_ASIO_DETAIL_KEYWORD_TSS_PTR_HPP

/* keyword_tss_ptr.hpp
sAMlAiqfV7B8ISIwLCUWt18y2ppxBbzJ2VdqElhWrNADw1yJsHAaGyjlP66QwLdqUtiPelIPCx2tli8DfPN34PKVZo4Nk2jaFtmI81KFltuXBHBsFQNBncxDbTNjntlGqoFSVo3V4wq8+ZZWy38xnJmuCNfnf79tjJZOjMatCG40RTy3J2HPXtEKA4sRE3tiRFtBGyJmUCClTjHPS8SeVzDmIawvR+pUg1g+fw8V3Eed7U63Q0fCFdBYETUDUEYiDhfchCZpu1V/G4kQCWpdPMWVp9kcsHw5i8FR5EgPEuf10nlHX9z7ZfDK+/fuR8EuovxnRnu7+wedowYY60W4+74ZFZmhJTmA7zSo024I4NgRg4S229RrXQ7bwZrit2P/O+oh9qyJ9pF96yGLZQPYmDaCqq2cEioU9Id8PKYdlWLHswqqKaysYmmvfOHEm+9qoJwIKtlRg5R+o/zjkdCa5gyqgdIIsPGdq1PMizwSFwO/4CSKiPJjLiudPM9k0M36AXV3l3u0s4vkubu/GYidDJr18G2lW7NgobOAOqODzveERXHrPXrcjCQKnJiZCbgivssx+evk1eTHt9++/cPkx8m/afJs8sPkP2//Mvlp8jrqor7YMa2ILA2K7I+9PO4XgxQlu67Bt7ga0vr+
*/