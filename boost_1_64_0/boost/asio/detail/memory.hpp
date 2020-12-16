//
// detail/memory.hpp
// ~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_MEMORY_HPP
#define BOOST_ASIO_DETAIL_MEMORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <memory>

#if !defined(BOOST_ASIO_HAS_STD_SHARED_PTR)
# include <boost/shared_ptr.hpp>
# include <boost/weak_ptr.hpp>
#endif // !defined(BOOST_ASIO_HAS_STD_SHARED_PTR)

#if !defined(BOOST_ASIO_HAS_STD_ADDRESSOF)
# include <boost/utility/addressof.hpp>
#endif // !defined(BOOST_ASIO_HAS_STD_ADDRESSOF)

namespace boost {
namespace asio {
namespace detail {

#if defined(BOOST_ASIO_HAS_STD_SHARED_PTR)
using std::shared_ptr;
using std::weak_ptr;
#else // defined(BOOST_ASIO_HAS_STD_SHARED_PTR)
using boost::shared_ptr;
using boost::weak_ptr;
#endif // defined(BOOST_ASIO_HAS_STD_SHARED_PTR)

#if defined(BOOST_ASIO_HAS_STD_ADDRESSOF)
using std::addressof;
#else // defined(BOOST_ASIO_HAS_STD_ADDRESSOF)
using boost::addressof;
#endif // defined(BOOST_ASIO_HAS_STD_ADDRESSOF)

} // namespace detail

#if defined(BOOST_ASIO_HAS_CXX11_ALLOCATORS)
using std::allocator_arg_t;
# define BOOST_ASIO_USES_ALLOCATOR(t) \
  namespace std { \
    template <typename Allocator> \
    struct uses_allocator<t, Allocator> : true_type {}; \
  } \
  /**/
# define BOOST_ASIO_REBIND_ALLOC(alloc, t) \
  typename std::allocator_traits<alloc>::template rebind_alloc<t>
  /**/
#else // defined(BOOST_ASIO_HAS_CXX11_ALLOCATORS)
struct allocator_arg_t {};
# define BOOST_ASIO_USES_ALLOCATOR(t)
# define BOOST_ASIO_REBIND_ALLOC(alloc, t) \
  typename alloc::template rebind<t>::other
  /**/
#endif // defined(BOOST_ASIO_HAS_CXX11_ALLOCATORS)

} // namespace asio
} // namespace boost

#endif // BOOST_ASIO_DETAIL_MEMORY_HPP

/* memory.hpp
96PS71z8NqboNNM9RS0+y4dhji7xNKS/+izfjw3xWX4bJZ1+4bMYp/N8GFq6xNPQr6t8O2q6yW9jjk6X+CwKOs+HoU+XeBqSrvLt2GA8DX4ZJd3mzC+dV+d4f+TiszwNQ3SVb0cjPssvY7Fuc2aW/V1Xng/DEF3iaWjEZ/l2LNYNfhmV+CxnLjVvOsf7Y60u8umYaf8KX48FcX/5KQxy/Bb/DxPtk72sO+2KtbrAx2OBLvOlGK1rfD8G6Sa/jYmOmX5l3tAb88aHYXncL56GXueq8u1YHuPnlzEzxs+ZqudZ53h/VO1T5NNRt73C1yPrOHV+CmX7tPh/aOvs5caPui7w8SjqMl+KrK7x/SjH2ua3kbc9XWH8aMZ648OQj/nnaWjG/PPtqMZnuTjbfX/ReHj3q8y//Yv8LGo6Xe2zmKVr/Po1xqYLc3xfY5UucxXrdLiN9Tr8iWuN2fHz/AFGRl/nexCr497xab/2LOsq34oVus7j53q/27/K81GK7bwME3WT16Cs2zzwetejs7wTCjrPozBOF/kkjNZlnok+XeXnMMW52txxg7WxynF4b2R1gY/DhpfMJ5+LZHuFr0Pb9hrfh37d4BfR0i3+EGt1+o13NZo6x/uhoQt8IpbrMl+Cuq7ybVis6/wEFugmv4WqbnNHzbOvs7wzajrPh2KmLvKpmKLLfBUqusb3YaJu8Iso6xZ/iJJONxozRusc74eiLvBxGKdLfC4KusLXobjK8flRjNNNfgsF3eaOmxxTZ3ln9Ok8H4qcLvKp6NVlvgR5XeXbMETX+es3+83won34BWRjTnjLeebQ9iw/g8U6/bY7nYGmrvJp890jXecnsEA3efv/c3Q/8E6VdQDG3wyRDLzn/lHRSFZdCRVrFRIZ2CokVMypSGhYK5GuiraKiBRrJRIV1ioyNKyViGhgSwmJsFYhoUEuRSLDnIqEhrkMlfSifX9++jyf5+l0ds573vOes1kmK/zWjWvh+beYhxg/78KSWCc88FbzrDMegYrO80RUdZFnYqEu8+t+5loetg9X0Irxc1ppzLbn+CbsjnNxqW48uvgLzwf6dbrd847NOn+H42Ooz1b4u6vdX9tbfNgvfVfqPA9c4/etrvKb7jTP9g/PQUGHr17rHunwKszW4d+jqou/8tcpWKkr/MI6Y9ClX7unWK2z9Yekz2LCP5yLH8Vone46JD2HPfZhf8+W58v28Pd/617rQsPvwN+ba13l923w+1yH52z0jOjwddiuq5vse49j6ibvwgzd5oH3+q2gMx6B2TrPEzFPF3kmpugyL8B0XeXL/mRtPOK+8GmbrRld4d+hrlv8wS3uny7x/X92Xp2/z3w0zZVu/MVzhIJu8YuYpNP93mMo6ibvQk63eeAD1obOeATyOs8TMVYXeSYyXeYFSLrKyzFU13kjBukm78Kk1lHsPb3N/dXhvajoxl8PSX/9m/Pq0kPeA5jymM/y8L9bM48exdYVlunwcmzQLZ6yw2d1+G6M1eEXUNThwQ97t+jw4ajoMv8Hi1vx90Edkj6JlTo8Fw0dfhrbdfjAR4xbhw/GIMcp8tXYqcP3o1+Hn0KPawmXW8apw2tR0LlHrXNM103ehaGO3+aBj7kvOuMRyHSeJ2Jf3Aueid26zAswyD5VXo6k67wR7bgX/Lqdrt25Snw3FusWn/yEudUlnoPVusJbsF63+Ju7rC3d4G3YqVt82j+tf13ha9Gva1zf7a+nHrfenvQeQDmul8dgri7wRRi602f5lxirm3zgU9aJzvE5mKvLfB2W6Do/gbU6/ctfJ2KJcxX5aszVNX4Q++zT5iP22N/2PF+I7brCv8Q+3eQDn3ZeneNzMFKX+To=
*/