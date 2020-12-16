//
// detail/null_tss_ptr.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_NULL_TSS_PTR_HPP
#define BOOST_ASIO_DETAIL_NULL_TSS_PTR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if !defined(BOOST_ASIO_HAS_THREADS)

#include <boost/asio/detail/noncopyable.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename T>
class null_tss_ptr
  : private noncopyable
{
public:
  // Constructor.
  null_tss_ptr()
    : value_(0)
  {
  }

  // Destructor.
  ~null_tss_ptr()
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
  T* value_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // !defined(BOOST_ASIO_HAS_THREADS)

#endif // BOOST_ASIO_DETAIL_NULL_TSS_PTR_HPP

/* null_tss_ptr.hpp
UE/H8LkO7nnahQvP4VrQIbwPsugovvjDjI924/shl1b/DpbQ6nEf4fmiAziqzXWRtBR5/7kpcoD1HtwBMVpt+yjXlLlSfwLS6BB+b3qKrKGd+F0f436gXXgl9Dw8GXMeEKbVD5/H/mn1NojRto/zbE7jfjYZz/kpcgwaHmJuP5EiC6CRVm+GHlr9JOyi1T+CA7TNyX0Ka+govmM614X9h/FFFzJvjM3Ek2ZwHzP/LrwDOukoXvFJ7n/dBs/P4HlnPwH8Mhxlvfqjn+J6sV69BBy0eiNk0upfgJt2ZabIt6GMjuFrL+Jc2E8An34x4+G46q/CHlr9CkRp96dTpAQSaAOvhSQ6iNthL9crhHfDDjqCD8FBOobHz+QZp214CuyinTgbDtNuXAIjtIHXwlE6iNthOx3Cu2E9HcGHoIeO4fGzUqSNtuEpMEBHcPolXDvahYtgP+dr4LMuZXvajZ9w8cxyXRyzU2QhxJgf9c0grFdfcxnXiVZXQiatroZcOoI/MIf5NzkvXAgh2sD7waBj+MosnmXawI+Dj47gTdnc8xsZw+W8M2E96008NodnjXZgA4bb+Cz+HsimyaL+2LwUSaUN/CtIYj/q1PmMh1a7YSbtvjJFXoL9rezzKq417KWjuOOzXC/asYB3IySwvYknLeTeo1343nzGyTbGIu4NaKQdi1Ok6/O8KxiD7eoUeRGijNN5DfcaTG2ZjPm5uYQx0OoRWEKrz1vKzy86hCsLeEboKD7Hw+f1uPheSNNt8ORCnmGO5cK3w2Ja/Yki5ohWZ0EDHcE3FNPsR/0jH88XrR5Xyn1Oe67jeYEgY1YPQTOtvv56riOtXgl76DAOlzMPtKuC+fkC88t+ovhYFc8j43RX8w6sZT5NxryC8dzA80XHcNMXabYJ4zu+xH3IHLpuTJFfQ47OYSBF7oFi1ofxCMTYXv37m7i+rFefcwtzQqunwExaPQvcdBR/bE2KDPJZF150K+OnHfUpcjUcZMzqEBym1c9AAuel7odJtO22FLkMtjM29WbYRatDEKVjePrtXEe9x3Ar7NLx43Pv4B2o1xHnQ7rJnONacNIB3ARu2sS9kEOHcT9k0lE8BItpaeDnLLhoB34GnIwT8/8FzWdp9Xbw0M47ud/v4nloZwxBrjWMMOYwPgw21svdKVIKTjr8lRQ54x6OS0/F8yCHduPN4KIj+PfgpqWR36egkc7Cyfdy39K5uACK6WL8OuTR6U38bnAf9z+9Cv8W/HRCM7/LwRp6AA+Du4P/Xvv+FHkeDrD+MHY8wByy3onngoPOxX5w0QF8L+TQ6/ExSKRTH2QdOOk87INM2sCPwyD734u713NsegCv3sA7lm7DeyBK78evQ4xOeoh3I7TR2/EzsJ6OYMfD3APsfwa+3OTa0Q04tYVnjZ6Jp7fyrqYNvAv20gP4nI1s18k54hfbeIfQgU38/GpnDunUDgxZtA/vgFx6EDs6OTc6Ew+AQc/YnCJXQYAuxluhng7j07sYMx0b4WcrhOihpIny3gkTJcK52PHHoV7nHOfCDnohvg1sbB9f4kt8iS/xJb7El/gSX+JLfIkv8SW+xJf4El/iS3yJL/ElvsSX+BJf4kt8iS/xJb7El/gSX+JLfIkv8SW+nLokbk5TSablHMsey7WW6y0/YHmr5fO7MMskte7P8tBmzHLI8n7L37LswP+LxW+N7yuWQ5afsxyzvMzygq7/zjh3beE4LActJ2zFOq+WL7B8ieVcy1dbLrZca3mt5SbLvZaftjxgediyfRvW41jOVuv+1bpfy7dbXm+5cytm6dmCdV4tr7JcZtnoxiz1lk3LIctPWt5r+WeWX7I8vgezpFieYjnDcpY=
*/