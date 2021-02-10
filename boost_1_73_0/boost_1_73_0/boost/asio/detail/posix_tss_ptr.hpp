//
// detail/posix_tss_ptr.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_POSIX_TSS_PTR_HPP
#define BOOST_ASIO_DETAIL_POSIX_TSS_PTR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_PTHREADS)

#include <pthread.h>
#include <boost/asio/detail/noncopyable.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

// Helper function to create thread-specific storage.
BOOST_ASIO_DECL void posix_tss_ptr_create(pthread_key_t& key);

template <typename T>
class posix_tss_ptr
  : private noncopyable
{
public:
  // Constructor.
  posix_tss_ptr()
  {
    posix_tss_ptr_create(tss_key_);
  }

  // Destructor.
  ~posix_tss_ptr()
  {
    ::pthread_key_delete(tss_key_);
  }

  // Get the value.
  operator T*() const
  {
    return static_cast<T*>(::pthread_getspecific(tss_key_));
  }

  // Set the value.
  void operator=(T* value)
  {
    ::pthread_setspecific(tss_key_, value);
  }

private:
  // Thread-specific storage to allow unlocked access to determine whether a
  // thread is a member of the pool.
  pthread_key_t tss_key_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#if defined(BOOST_ASIO_HEADER_ONLY)
# include <boost/asio/detail/impl/posix_tss_ptr.ipp>
#endif // defined(BOOST_ASIO_HEADER_ONLY)

#endif // defined(BOOST_ASIO_HAS_PTHREADS)

#endif // BOOST_ASIO_DETAIL_POSIX_TSS_PTR_HPP

/* posix_tss_ptr.hpp
sBvXVCZKS6/fRC6qXrNL54UJQM8r1bG/N7CZ7stM9dZQn7CKuqdO8HAvXfKD1yxlmvNE65ZarSXv721rkPhUFmc7CbNktTBBoauzYdOW2TmrH+XhzQXNFy5Le8uf1rzNQ3Wemtbr4txVOtKdptNrcPfjUwq0Ey77WRdK7xwZET1Q5ZJCqqumI+igJTV+dgHD1Im1iq8rka4ObLtKfpZnI19fiyvwNZFUQdMutVAOfnXVfanVvl1gcmLV/uhYvJ/fqQ2x0xrMKalFq5UrfPpdkL5mcwtmpTdEZ+7CCRzfpRCxL60g/yreWJla/HcsZEsz4r/ks9/0dw53D/f6R4Pd7qC/d7h3tHuwd7jxvFu8d1RP6x8GFe2c8a31c7o74rKUPIeEqnsZ/7BmorhjPRy9Kc/sWqIkXQYGFRU7ac+1LtU4U2SLCJ91Wqecu2temR+yCp3QxpPk5yaf8hi5GXYb3uQXeZemcydiVrBiWNAhvbJU9L3E4MftBZUOWf6AuYFqbLJJ3GcTu73blzHwijupcwHvdjWrcl4IXvrSv/A7twtUKsYENMihzrgqTKEXv1azy3C1WFq0cpmVr7rNCynRtvv3octq6ZKzWARdk6vU8I9/u3/fHmQrKuboRnsZmZU0JkkNJu4qHPOWV2dj
*/