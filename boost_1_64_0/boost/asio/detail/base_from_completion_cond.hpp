//
// detail/base_from_completion_cond.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_BASE_FROM_COMPLETION_COND_HPP
#define BOOST_ASIO_DETAIL_BASE_FROM_COMPLETION_COND_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/completion_condition.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename CompletionCondition>
class base_from_completion_cond
{
protected:
  explicit base_from_completion_cond(CompletionCondition& completion_condition)
    : completion_condition_(
        BOOST_ASIO_MOVE_CAST(CompletionCondition)(completion_condition))
  {
  }

  std::size_t check_for_completion(
      const boost::system::error_code& ec,
      std::size_t total_transferred)
  {
    return detail::adapt_completion_condition_result(
        completion_condition_(ec, total_transferred));
  }

private:
  CompletionCondition completion_condition_;
};

template <>
class base_from_completion_cond<transfer_all_t>
{
protected:
  explicit base_from_completion_cond(transfer_all_t)
  {
  }

  static std::size_t check_for_completion(
      const boost::system::error_code& ec,
      std::size_t total_transferred)
  {
    return transfer_all_t()(ec, total_transferred);
  }
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_BASE_FROM_COMPLETION_COND_HPP

/* base_from_completion_cond.hpp
bEssref4Jmz51gTKJ+JrdE9FTlWSb/Sk7HPGlV7k30XdeHAt9syxSgnV1AdV4NN6dMA3H3qlDup+RJ1l8EvHTg9B484UqQLew9qILcafzdOgA/1ZifDGrq868ZGNts2srzOQBTs3UH8kMp1fIdmR1Ut6H/a4guMzKN+KDXd6yY+T+mYyP9ejTxJ6ke6G5yAffjP3cKj/M+y2mv6XBB5vYj4bzjw6Az4D8EEp85kZl6ajYwVyJTOuMlfEI9OSOs7NvbdJjGnYpCOLeG2EBvWXkf4O29w7ivhH7jCzXqP+fCtjziDyEhm3c6VyeNtp5yD9LnTF8WMe7FaMz0mvK8AfHBcZG8Bnk7mvA71k5Hwa+e9PwAakn1E2NQPbmnVrBWMG+teSTkSWyei4wKy5sOv2QvxBzCSkSW3QvSMNOWh7mrm/hI65+HqMjfnEh8+88PQw19J2HnVmmnVoFX0FHunQXTWX8zbpVHAZdvESW8Pxyd1ZxBX2KDXjLGkZPIbkYBv8vh5/thfBF/pnJTAOQGMadPemSBfQLi2V2EW+COjEZ6Nji1TD+S7k+is6xeDDN7FV9XRkno8s8P0JdmshHnilmxZPhRayXjoH+9M2Gj/mwyexhn5czfhCfxqALNdQ/4/UuQQf5ZlrZ9o9Yu7nQW+wR9qMjCfWSR7yS2rJN/dZXKy78V0W/S8FOq834aNc/JlJHyT9dZ4UA70FlF3kRT/y+3N+eylxWU8M+iSnB51Jvwsd32Rij/RDG/IlENukxejyBLqGLyCeneR5SdG5dyq0G+Bj7vGYOR2ZLHX4Pw/94XMLY10ceTnYeD5QPuMNdtjQir0YY7JHYWfsuZXjeRn0KfPuCuK81UrZTPhDa8YAbOqCnp34tBDT2GMuds6Afz+O3zf3NsuZf8x6aB5jKrQem4SMyPQCtG6Dbo25ZvVJ+znvWULfIO9y7PFiAz7xSJ4W7If/KrxSbQu6OokRxqJrm4gvZBqF7rdD/0TsMAK/WKGzZybnCVI5eva241dzv4C2K8tAKvGWJrUzXtfBN72ReKddlpl/WvFJFbYBl0KjHpqXEVfP0Q9cpdA310fwnk/eXeZe3gj8los86LA9h/oJyEU6FrRCKxweez2M1dhhOfSHI/M2eDtTkKkCXb3SUnivrJOaaDNgCHHmpX49fp6OH8cQ49jvzCRsgi82cmzBhg8ST1XUeb4KeVOJQ+g/hhxjjCzQbyYvAnrWAcQO9RaRPoRd3iO2nhyKDbGzedXMydjuL9Ao80k7hjF2UH6mWW9apGp4XFOEP9uYq6vhAco5bkzHt3MZz130hRLojoQevk2jfg5+sNH+vQKJVxCobx02yqMfIffj1Ls5jv5H/0oy8YNt70WW88l7CtlOA49x3kQ66nj6O20Wmznd8GpEbi9tSROrkBm6LxgbzzfvZmTtloAc6ciOPPZ8+OGPA9XIMwR5adMfer+1S1dUSo42+uAo1sgn0I62HxUyZyDvIOqvnsMcQtt751AO7zgbtiH/Gs7XoMedpM8mEO/Q2AatxwZKvcchVylrK3OPjJhfOxf66LEJnrngZPDTBumDGvydSzyAn9Vgf+Lor6RZ0L2yjHUNbVoo20j+gLHYmrJrS9G1DZu0Slb0PZvyCTOxJXbePYM2nPdIoQ2yRHH86mxigHPnJOrQZgmy3YxNfk593yD0Ix77nIB88YzhZs60El/VxCW+2YNuS9PQiTQSHZ4BH2HTiiLWdnHS/kJiLZMxgna8CliT0CkBWUs4/84wbEgMPI2uj3A8cQj2a2GMBNYm4ge7/Hgieph7Th7JRTqb9AHSUnCzuc8B7gI+fHKJWRsg99pK5AB310vh8fQ90r+YuZA=
*/