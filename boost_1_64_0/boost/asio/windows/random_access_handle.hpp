//
// windows/random_access_handle.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_WINDOWS_RANDOM_ACCESS_HANDLE_HPP
#define BOOST_ASIO_WINDOWS_RANDOM_ACCESS_HANDLE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_WINDOWS_RANDOM_ACCESS_HANDLE) \
  || defined(GENERATING_DOCUMENTATION)

#include <boost/asio/windows/basic_random_access_handle.hpp>

namespace boost {
namespace asio {
namespace windows {

/// Typedef for the typical usage of a random-access handle.
typedef basic_random_access_handle<> random_access_handle;

} // namespace windows
} // namespace asio
} // namespace boost

#endif // defined(BOOST_ASIO_HAS_WINDOWS_RANDOM_ACCESS_HANDLE)
       //   || defined(GENERATING_DOCUMENTATION)

#endif // BOOST_ASIO_WINDOWS_RANDOM_ACCESS_HANDLE_HPP

/* random_access_handle.hpp
J41CtAXnmdCuBNPNQiSAxT54tuBVsD140II2DLgR76cjONNXiETwDj8hOoGN/FF/gt+DXcDPAoRIAr8LFCIVjMT19wWbgwNAvj+0R7zf3yXFfn9XwWhQqNeHwD/CPRK8Ao5R7P45oAIKA5zgh6ARPIH7M4FzcX9mcCjuzwcswn1ZwCugFTyA+/MFN+D+/MC7cX/+4HDcXwDYEPcVCF4Cg8AzuL8afH+RfH91+P7qyfvjup+/Me7397KCeOAO3jfmLfBe8G1Q1au+A+LaxD7wt+B+cBP4HpiJ+3ofPAAeAK+AHyj2fTsOgSG4z8NgOniE9+U4CmaAx8CnwONgNu77BPggeBJ8BPwY3I7ncAo8Ap4GT4KfgGF4Ht/yfhKTj5mc63z/Aj2eVodXirSq0uOtxvEK2P03oM+7xfr/aUXZqs0q6ZTQduLN6ANQ5f17NOP/TRZB5jdGuw59IBifgLLSk9onQ9N7ZGXg3JD5p0EpnWVzjJNvWpPaKUU4qZQp3qU4cUZus3AarSh87TDaA7utbLPI47ezWxEnblfdVtLJb+fzcLx4rXzB8djtGm+nS7yp8nxDnPHY7Rpvj2s8nM9lbAHHVSjsAQ4bS2Ez6Kbk2AK3sMfcwsZrwia6hT3tFhZOKUNl96L9CWXcZLe4Z13jTtVeU6pb2G/cwmqvKc0t7GW3sPRc+JqO0zV9pZiVD2T8DLf4gPCT8W0ilPeB6EiHHjAUKRbF7qeIg/Q+WqB6jZTpjXVLz6rYryekLu3LPg6HpVyaR2nmGhxxc93iBnPcHajwrWJ8cYlmP/7PKVyIUd0vP4LL9jvkV1/Y/RTyQ54hPx5bAjPNptLRVj5GcW4zZokSw0fYSfkHg4H3cUNrj+IG0Z5xFQh7mMK2MHK+U9NK0D7fU71xHF/pD0QtzgeOZ9SY0lCfdQu658MGTRoyzw9HGmF0fI+B3DLPRwlNeHte5/eyhc7ZBO+0NsJo34uBzqnmj2hK82MDP0sYPMt4+zkHIY0jdF9NtfelFgspm1gp/iEDueU1RYjFYhS155aEY30P2HvcbCbst2jrLa3lyq3wfxk22Unyexf2MVg1vQMc9zEH2W8e7AJJstTuzK1SJjSHHKJrFo1t06bJfe9QJ6K9SXUi+W0Hcf/wQxXBfjudfvEOvz3Sb6oMd8DpJ8MdA2PJD3UO+53W+MWz31mNnyPuN9IPdQP7Xdb4cVzclNNPsPxrlX42ChMMN8of3Ch/3Lbuxt+TAb6CzFKEqQ/awHbI1af7uH5PJtoKbNOyi22q4IuvSqVvCn9DOF4bmbdqpFLfiuIc2zUur7jIHh6XyOFj5Z7CARR+pKKtg/g7wmGby3zpS2EzFE/1yxAZvrGsk00UPkuR5cCtTqlFxwcrznKAZ8rHU3F8Ox1vQeVKfVH9yV2X740E0UkUnusWHzqerU2vUFvWu9Hxn0UHlKMAD+XoXi4vqr2vlt0ujuG8z/m+tKoxb8j3rfrKfD9lmhDe874ct8bvh/M+5yPO95Xz0UWQ9p+jvdfeCgh7Jatduze7mVt2mlqvd51bL7vdrP14Hjao/kcf+HRvii1v3fwLM8c91/BJM76FJtX/qZEzM875rNw4tzzs9P5ND+zCGrwk0x3c2OFKj4u93+g+eN7V/n9psPTG9+nZT+ftHm27NCdzYkvjjIn+sz+3HfIqG5IMuN3RNuJ2IOoKem5Pqx48pi6G9+NpxfvxJPI+PD3A+rxvTzTvNdgQHAU2BseBTcB8sCnv39MMvBdsDj4ItgQfA2PBCrAV+BLvKXkYTAT/AnYC/wYmgfG4th5gbzAFHAT2BEeAvcH1YD/wRfAOcCc4AtwLjgTPgGNAgeeVBTYAs8E=
*/