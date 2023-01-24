
//          Copyright Oliver Kowalke 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FIBERS_FIXEDSIZE_STACK_H
#define BOOST_FIBERS_FIXEDSIZE_STACK_H

#include <boost/config.hpp>
#include <boost/context/fixedsize_stack.hpp>

#include <boost/fiber/detail/config.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace fibers {

using fixedsize_stack = boost::context::fixedsize_stack;
#if !defined(BOOST_USE_SEGMENTED_STACKS)
using   default_stack = boost::context::default_stack;
#endif

}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_FIBERS_FIXEDSIZE_STACK_H

/* fixedsize_stack.hpp
xWYUMeU4IwTLLiYVvHN9EEaqlFjsTvg9WHZpVabcnCl/C1BJF1vavrGF4b4xlfxT4j8Oix/7cQnZHkpEl3DWBieKJrlrB0taXwLnFACQvLRpmwpNBEusH0PZvDTbYUiAzB0QmctjXs4SlcUvMXgfon4SKzw3mddB7jTIjSO/Aw7YAx7zJ5BufQmGMy2peLEtpPCqTPnv0EmLx+p1F8MvIIVrwuFqT2701lBa0x9Q74o9aDP/lqSNINNvBIPV7nQHffDerMHDL7KO2NoM4BTkbIOca32+6NwH0tf4db0npK9+Udf1/qzr9WrX66nry8bxbsN7s4X1uYpn9OJxjrIUxQPIJrsK9Aa+hN+IhGqUekqvgPSPPNQSXDzmcFMmopiMADiTAUIYgOYqYd2hh3uhQ6x4iyuem5oAppkLVxqfKx4gPmbEDw7gM3ly70jqlx0oJ92aW7am4ICrIf+1SGSNk+i1eJEtxBXNK4dBXA+1RqJ7U1arciAC95tSEy+hEoipLAvULNKWJlDoXMiLqIsGErCIez6zZjDQzWIjz/Caj1WgsBvXCyYpVxl9iFESU5Q1Q9zSO7N+M0U72U6ySvwuHnVbDrGaveUFnNCilzEt/g3VCg3k858tyi/uWHEt861bIN9j/FeVUsd/NSofu1UCuM0tCOBmtyCAL+MvACYinr+8AiqbS4G5l3jScUqS0BiJkmooyciS4nnSPygp
*/