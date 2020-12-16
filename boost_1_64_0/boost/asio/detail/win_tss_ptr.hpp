//
// detail/win_tss_ptr.hpp
// ~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_WIN_TSS_PTR_HPP
#define BOOST_ASIO_DETAIL_WIN_TSS_PTR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_WINDOWS)

#include <boost/asio/detail/noncopyable.hpp>
#include <boost/asio/detail/socket_types.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

// Helper function to create thread-specific storage.
BOOST_ASIO_DECL DWORD win_tss_ptr_create();

template <typename T>
class win_tss_ptr
  : private noncopyable
{
public:
  // Constructor.
  win_tss_ptr()
    : tss_key_(win_tss_ptr_create())
  {
  }

  // Destructor.
  ~win_tss_ptr()
  {
    ::TlsFree(tss_key_);
  }

  // Get the value.
  operator T*() const
  {
    return static_cast<T*>(::TlsGetValue(tss_key_));
  }

  // Set the value.
  void operator=(T* value)
  {
    ::TlsSetValue(tss_key_, value);
  }

private:
  // Thread-specific storage to allow unlocked access to determine whether a
  // thread is a member of the pool.
  DWORD tss_key_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#if defined(BOOST_ASIO_HEADER_ONLY)
# include <boost/asio/detail/impl/win_tss_ptr.ipp>
#endif // defined(BOOST_ASIO_HEADER_ONLY)

#endif // defined(BOOST_ASIO_WINDOWS)

#endif // BOOST_ASIO_DETAIL_WIN_TSS_PTR_HPP

/* win_tss_ptr.hpp
aZS9krKKCTH9eR1o6c/8Zp5PkDuHbU3U+AMQXSbXanz2amvte7V6bbuP34Bd5r0RnaNrIXvMNdUtSlsHRuU6OkSv7QXRFVxTXaF7V8w7tVcze1fsEauO1zYf8Op4s3dxfAT/6HmlborzYzp+rlfH616Q99upOt+fljzLVO9bZfTWOLuaqtP89PQMQ5+tcbQa9NY3UXNte9k8IZn5/YzkmR8SOx/Gu3aE7j91yQ555FLtPdaIzVVivl3dviFy7WPsum9mjWwsoEz7tIiwkj7NmePtUzaHg+6bSj9AffKgsSV+OT3aIWi/W/P0NP0zXeJzg75fq/QXUwdxWx2Z5hu2nvul5C115CVuy5sVSlKfHk3fP4eEtAzjqzf4PrdI6FLN/ahK4v2s+5ypO8I1m5wY2Zwq6flGN14/PKYfEh1/GR9fe4BgfyHeeZ/vmfdO+dnzjpD8vqzys48wF/mp95EfVr6D5EfpM8x7wwsSrwvNDp6DmmeQ4zvE9T6+614Tum2hUVCK70Zk/gxBnrWTR3qftZUm6x3W82/t7UHPv79P5Q6egG1k7Pl38Fz786+Oh8+4TfPOW6MLB41qLHSkrklmE1bR7/k+z7tq4qo2rh6bPc3TL+g705re3TY/SsuLedwwPhRdZQyROlaJBtfnWk3v6RirpT2lLm4SznkGrX2emfEZHocNsNlLSzXy7uszJ8Ph39rwY/p9iOQXHoxdKu3lWqy9/1o/L/5+RhL3/+LvzyXIX0mQn5cgfyXnz29LkB+TCwfJN5xrfn/7Twd8bmrREwdmz9529Dx+w9nfP0uQH5bE/ekE+W25bWDs+pLVH3029b4Fv9z85rK3tvUr+Gbiflv8/ekE+XMJ8svTpJ8XZF7t6tXPyy7KKDV/i32zfDe4ICRnHPhb/HTIs38D7Z4eov3mb1k/FZrLQvIcb+j3268PP0s/1/b3Utvf821/LzN/UxZ/5/H3HbG6bH8vsP1dYPt7kflb1gylDc8Q9Fw459WCvwc93nZ+PH9h8HeoR9noahcGf5f5MhtdXRP1jrTR7Y+zvOMLg8ubaKM72QQfBYaOsCi43oU2/yr5SneT0tn9qwxqw7l0cDB4scaHavwy8GLwcnA4OAUcAl4DXgIuAIeCS8BhYLHSGT4WBfM73+JDmGqej+OEHKVbGhY68X39vNL9lhtwL/ANcCh4CrwUzKI9V4KnieeBb4ILwD+CSzR9HfgW8WrwL2At2Ibrj4AdwX1gClgPdgafBDPB74BdwFfAdPBVMAP8rab/DuwFtqGtvcELwL7gJWA/cALYH8wDaYeOl557AFf7jNeL6g/np2Af8Dh4IfgyeDn4c3As+Ao4HTwBzgF/BS4GXwULwZ+BRRo/BWZa9v96JoF6ZWwioJwJU79Ht4BZ4K3gOPAp8BpwG1gC3gauBd8L3gDuUH8YHwZ3g3eBHwE/At4Dfgz8JHgP+JDG92v8KfBe8NvgJ8DvgfeDz4IPgD8AHwR/BD4E/gzcB/4WfNTyawPGeHgM7Aw+DvYCvwJmgYfAAeCD4GCwHhwKPgFOBJ8CjV+mZc3LKXTYfsenD6JxllcXR3m1hAal26F0dr8mh+GjL/g9cAD4DCi29iovDeAEjV+t8ULwOXCl0q8CnwfXarwKfAHcAP5I+4ky1V6VuaDtSAIHaTu2qH+O94BdwXdr+8V313VOPtuC2ZrvNs33XjAd3A5matx8b9/U6/Efwn3SppfipMOW0dDltXHS3WH3gxMnXX6cdNE46XbFSbffRtfgoptu77846U7GSZdaGB9dTpx0+XHSReOgm2ZsKcQOQ+RtMH+PA+V7d+oHaJTOjyvA8eDl4ESNXwPmgrPAMapnK3SeXAk=
*/