//
// detail/win_fd_set_adapter.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_WIN_FD_SET_ADAPTER_HPP
#define BOOST_ASIO_DETAIL_WIN_FD_SET_ADAPTER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_WINDOWS) || defined(__CYGWIN__)

#include <boost/asio/detail/noncopyable.hpp>
#include <boost/asio/detail/reactor_op_queue.hpp>
#include <boost/asio/detail/socket_types.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

// Adapts the FD_SET type to meet the Descriptor_Set concept's requirements.
class win_fd_set_adapter : noncopyable
{
public:
  enum { default_fd_set_size = 1024 };

  win_fd_set_adapter()
    : capacity_(default_fd_set_size),
      max_descriptor_(invalid_socket)
  {
    fd_set_ = static_cast<win_fd_set*>(::operator new(
          sizeof(win_fd_set) - sizeof(SOCKET)
          + sizeof(SOCKET) * (capacity_)));
    fd_set_->fd_count = 0;
  }

  ~win_fd_set_adapter()
  {
    ::operator delete(fd_set_);
  }

  void reset()
  {
    fd_set_->fd_count = 0;
    max_descriptor_ = invalid_socket;
  }

  bool set(socket_type descriptor)
  {
    for (u_int i = 0; i < fd_set_->fd_count; ++i)
      if (fd_set_->fd_array[i] == descriptor)
        return true;

    reserve(fd_set_->fd_count + 1);
    fd_set_->fd_array[fd_set_->fd_count++] = descriptor;
    return true;
  }

  void set(reactor_op_queue<socket_type>& operations, op_queue<operation>&)
  {
    reactor_op_queue<socket_type>::iterator i = operations.begin();
    while (i != operations.end())
    {
      reactor_op_queue<socket_type>::iterator op_iter = i++;
      reserve(fd_set_->fd_count + 1);
      fd_set_->fd_array[fd_set_->fd_count++] = op_iter->first;
    }
  }

  bool is_set(socket_type descriptor) const
  {
    return !!__WSAFDIsSet(descriptor,
        const_cast<fd_set*>(reinterpret_cast<const fd_set*>(fd_set_)));
  }

  operator fd_set*()
  {
    return reinterpret_cast<fd_set*>(fd_set_);
  }

  socket_type max_descriptor() const
  {
    return max_descriptor_;
  }

  void perform(reactor_op_queue<socket_type>& operations,
      op_queue<operation>& ops) const
  {
    for (u_int i = 0; i < fd_set_->fd_count; ++i)
      operations.perform_operations(fd_set_->fd_array[i], ops);
  }

private:
  // This structure is defined to be compatible with the Windows API fd_set
  // structure, but without being dependent on the value of FD_SETSIZE. We use
  // the "struct hack" to allow the number of descriptors to be varied at
  // runtime.
  struct win_fd_set
  {
    u_int fd_count;
    SOCKET fd_array[1];
  };

  // Increase the fd_set_ capacity to at least the specified number of elements.
  void reserve(u_int n)
  {
    if (n <= capacity_)
      return;

    u_int new_capacity = capacity_ + capacity_ / 2;
    if (new_capacity < n)
      new_capacity = n;

    win_fd_set* new_fd_set = static_cast<win_fd_set*>(::operator new(
          sizeof(win_fd_set) - sizeof(SOCKET)
          + sizeof(SOCKET) * (new_capacity)));

    new_fd_set->fd_count = fd_set_->fd_count;
    for (u_int i = 0; i < fd_set_->fd_count; ++i)
      new_fd_set->fd_array[i] = fd_set_->fd_array[i];

    ::operator delete(fd_set_);
    fd_set_ = new_fd_set;
    capacity_ = new_capacity;
  }

  win_fd_set* fd_set_;
  u_int capacity_;
  socket_type max_descriptor_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(BOOST_ASIO_WINDOWS) || defined(__CYGWIN__)

#endif // BOOST_ASIO_DETAIL_WIN_FD_SET_ADAPTER_HPP

/* win_fd_set_adapter.hpp
I6uQ+eL26EHyeExYp56asCca/XfjxX6JJ8lTpHpM0U76qO3WT771Nk3UPT8zKoqC1waMlXDHeW17kYm3Z5AOvdmm7g97NLTuZ4m9vcR/p9xBuyPLyeOHWSMW5jfN8UuFyeYa5bMLpxfPJ3Ui0EK/r0+QtLT1vu3xRpKVC6Wofr9RImt505iVXsXM/A+W15zxdJamsyvfbxOpJ2lUzq/pa3wTOG/imITOHACRlJCWMCauiT+5mV02+ixT3nOwGn2Xs+Qa09Vu4pXvvk7cS524K5+IEHn0uN+SuAtqjXuXE/eizKC4uycMs+NuFSFurRu5G+y4XPVC4u6ocQ9s7MS9LmFMWMzR4t0i8RZGjNd+nrLkfkU/LyLT0vMi9Dt0L+37bPtqY58m36mrsFOHsZs6bNbc3SnuWvfUPTXUfZpZR6XtRUkTd3uxza50j0V6hrWzl3Szfi20vydMw9vQnhH6+91NIreh1esip624ov5t6NYforehWQnuMvkl7VpGlDKhET3sNvR0Zw2WpraTDz0/ysvsPZaRrzUnJz+vtKy0+GLnbLregXtQNnuO6fcJq+fM6dqoy8V+wPu51ydhkhMlzPRis67QCZPu0hNeSvjl4ved9wtvbJD/RSbspxv1vBfjd6hupqie3dUSx6deL3KNMR/wq5lpE6flzMybT/jTpa9/X2SrvBnevkEyeSJDmyl6jEPCFpeKO2UeIo+7xDkyKM4x3jZadyWsWZf7o/i/7UkRu8fIt8ct0TvZusR7XFC4PNNefSNyH3qSbXtQuJa4XepFL6sJM7Nw9ozCgqB2Pzw+SceXUpaTrRaajjFP2PaB7A87zlUWzTRv6SIzyZX3Zlqex4h/uehazaZu76FSf9fLPoso39TbGx1dqyrjp40+aMv4uiTExfl9TRImxcX6YxuJ/naVGYLM97ZMfBFHER/0xzaOuDbJxFmB/A/StrZKGMWxRc3jGvlP4qapHmDaXWNCwq1zwlXeXK9wyRpuG+F+7CVnrF7pj28cvh7KyB105BIql0TUEatyqc2d/C6+xKwfDpMZjsw3tkzzxeNNOxgmU3RIJjOazApkrHRZo9XfkWmeEipTjYwnXeLpauI5JjRvO5pr3nyLL/XHx0Utg5jEQBnHNfP3X3yjuY8h5eqE9arO2vl19GtF2q+10H6rt7Tx0laJ21q7PZa+ibbIedc3/ZW2Caq3XPsw45YWJCfPuepCVzlx0/5P+xbz/KmsO86BYeFDzpBIcvcJN9FOZz0Z2k4H9ZLyfC8L7SORP6w+MmRMvCxCHxnfInIfWRXWR5oe8jDGGbm19JEVLdzlcbO9p8JdHtpDHv44w3lHWatnQv4C0xyzAHOLfYZ94FqTmT/SySP7n5ziUg74JL3SHjZuK+WPn+kfNVzLqH1hsP+Z4j8HAbP22PjrOJK/6brWk7VR4jfD6s2/ORjnOWqUjg7OY+reP+GMgUm3vrPpcxHhWcmEZ4qbpC+kzA7Y6dKysvNUirnNrq9PRSyzwGDCilpmGq5d1DJT/6hlpv56XpuEN2Ov6eKXJvYJRjZZ/T3WRrE3Chq/mbFP0BkQEs51BkRv6V+1zdE+tlTkzqesPCLT05EJWsd7pcikW22JTftr6T/XHcO1Wjnt94WWq/1WmbHINLbb5sRBrjNInDrRBP8Ec1Zu7fMimRHqxMgIdSIrrE400/YzNU7kVHe4M4YILsfgtpKyCHsG1+n5b3dg7J/XYu625xUi16fZ9mNvRa9PGq5jtPqk/seacxqa1sj8UtT6ZeIz9ctuwS1z9neChF9mFepa7gkmTLvgMPQEVkid2lfPOtVK4l9k5dZSpyaKTF/qVIKpUxHemaUtKUa+o8g=
*/