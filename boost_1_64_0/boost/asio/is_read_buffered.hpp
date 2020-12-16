//
// is_read_buffered.hpp
// ~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IS_READ_BUFFERED_HPP
#define BOOST_ASIO_IS_READ_BUFFERED_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/buffered_read_stream_fwd.hpp>
#include <boost/asio/buffered_stream_fwd.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

namespace detail {

template <typename Stream>
char is_read_buffered_helper(buffered_stream<Stream>* s);

template <typename Stream>
char is_read_buffered_helper(buffered_read_stream<Stream>* s);

struct is_read_buffered_big_type { char data[10]; };
is_read_buffered_big_type is_read_buffered_helper(...);

} // namespace detail

/// The is_read_buffered class is a traits class that may be used to determine
/// whether a stream type supports buffering of read data.
template <typename Stream>
class is_read_buffered
{
public:
#if defined(GENERATING_DOCUMENTATION)
  /// The value member is true only if the Stream type supports buffering of
  /// read data.
  static const bool value;
#else
  BOOST_ASIO_STATIC_CONSTANT(bool,
      value = sizeof(detail::is_read_buffered_helper((Stream*)0)) == 1);
#endif
};

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_IS_READ_BUFFERED_HPP

/* is_read_buffered.hpp
uQKbXpjmxipsbKdg8wu4rJ6BzcajsDkE/I4A5j4DOGiFubQBol6I6e4Mpr4rK7HpAHRWzMKGFSZ1BcyxC+a9aQE2zTDVfVdh44wpc8ocbBwtXxUW/DD7L8E0W+dhY4jp5YuA1U5A2RdmYPMJ6P8SoFN7GDa4gIMg4G/WGmw+YeKnxEYZMN+OaeBKTE/NgLcZgN6pmB4rq7F5WoGN4HxsCgG70zC9fW652AhjQwMo/eJ8bDAxNcychs3gI7AJnoWNVxU2v3OwEQfMfhmQdcVMbFDWYnOrTV5/Z+9IwJssluEQsaJW5FTQn6NQkEIpd6FIaEMplDY2LRREQ5r8bSNpEvOnpfXEGwUVPFFR8cYbDxQVEU8OL8ALb1T04Y3XE+83++9M/v+fJm2KPt5732O1THZm752dPf7Z2X1un9tjt3TIhROX5I066ZVf16269Z1Vnx339PQx3x767cxbzjrm0tdP6HHX0jv339bquLM7rj13aN9nTutQFj1+beSP+9+ff3u7d6+NfnvtU0/5r91xXv7ab56/7qlDXryxQ9/QoM8y7jwnOuXdO1bOfnvBz3Ulx45fWvP80BUb+rdZuf6MmU9+f+D25/OX3P76sd5N7aoGDOh0bsoj/Uf3OmLwbzWDph120GhXqZaiPp5yYt3gjU+fee6gyKU37nzypqmVh68IL5z69M3HBtZ333nplr7trn7j3BEH/xBefmJql6du6d4+MOrIwnmT+69as3L4gx16jJly57ai4k3Ljvs+NLj667MuiYa8t9Z3qt9wTvvW6xf98ufaxV8EnLf8dPPPa7+rP+l52190ve9Nf1O04UvqN31EOw4ZO+1L0ZZr3rngTNGeo1dN/l60affN+z0s2vXa4u73ibbtdmbN26J9J7Zuc7No47WhsEO086IHdhSJtv7ooT9fF+0duuCU70Sb339ll7Gi3Ud0XJ8m2v7yfv5XRPtvnfLt9aIPPk4rHi36YdXrixaKvlCX3T1P9Edt66Nnij45e8dtQdEvr/1qf0L0zSrXoWeL/rnrg8qvRR+lZj2UIfrpmF6/LhV9tePgb9aK/nr6khU5os/Sbk+5TPRb6Kw220XfhYMHp4j++23I1kmiD/tt7Ddb9ONXA5+dJfrygwevuE705/ve+xaKPl3xwLxxol8/vferfNG3Y0ec1Un0r6/Nt4Wij1tlTlwj+nnJVbs3i77OXFvaTvR3t5Jv3hB9nnqHWib6faBy0gzR96u3PJ4l+n/D5q2rBQ+47rIfK/jg6i8u/kDwworJ134o+ME7a+NzgideuND+seAL7WPvPMEbN69+4A3BH7898M3xgkfmDOmaK/gkcteuGwWvfDnGd7jgl/QjvX0Ez3z2xFnvC77p3PD8A4J3jnZFPhb8s8zT7/OXx/fftP/T63qtX33eliO/2P7SG6e9/Xn9luDXZxSf9uNjoa6RO6t2tbtt6YabnjvNm3LvQT+vbbv0mEOPyO9x2IgDTzrinNPa9vlx3jvpl/VdP+GUuzZlrVm7sXPK2uvHFR6UuuzZqp65D08c/8La154rHHi6+tuyAWfM/PKXN7LvCr3g7lqeP2VR97yA7T/sRg8dkyXgyKHDhws4PHPMSAGHZY7S8VmZw0cLOHTEMMADzMwa3tx5vxYJi78Wf8+kePyVpoHNxRM6Tfq/LdMnjVaLG2iae56/+e830jVvf2T+o2gPZmjHuPadFyOd7MlwGzXLgI7pW+gKwhVIr6uy2i9JR7ga6fy99fADTdtn2YDxWjH6ZlaeC1h93+V0yhPpOxidaHMebPq+wa5Hk7OPw9ufty+51AT9w/Pl9lJsrP1tj7H32Fn7t0f64kxr/2dSPkDH/rPQRyc=
*/