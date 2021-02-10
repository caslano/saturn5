//          Copyright Oliver Kowalke 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FIBERS_CHANNEL_OP_STATUS_H
#define BOOST_FIBERS_CHANNEL_OP_STATUS_H

#include <boost/config.hpp>

#include <boost/fiber/detail/config.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace fibers {

enum class channel_op_status {
    success = 0,
    empty,
    full,
    closed,
    timeout
};

}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_FIBERS_CHANNEL_OP_STATUS_H

/* channel_op_status.hpp
+VfNnYV4G+khFNjhezbsH1jbjd/cdBrFyb3evhPogRDfcP4/UEsDBAoAAAAIAC1nSlJNh9sD+AQAALQKAAA0AAkAY3VybC1tYXN0ZXIvZG9jcy9saWJjdXJsL29wdHMvQ1VSTE9QVF9QUk9YWV9DQVBBVEguM1VUBQABtkgkYK1WbW+jOBD+zq8Y5b4kVUr2/W53e6ujKd2ipRABaTdSJOSAKb41GNmmbXR7//3GQLbNtqf2wxIlBuOZefzMM+PY6xEc/LLLso07ePJKu2+KF447o4UUf9NMP26Qpt+h/6DhGsdnhJrBndX3dALPsvoO484qHWIdmfs0fUa4tQFpfmbGeJ2aW5zpLQf7uWi2kl2VGsbzCbx8//4POIRXL16+n8IJqRnlEGtab6i8msJR3s38VZLbW1vRT1OgGgi39xwmJVOgRKFviKSA95xltFY0B6IgpyqTbIMPrAZdUigYpzAPFysv+DyFm5Jl5eBnK1pQpWh5DiW5piBpRtl176YhUoMo0AP6z5nS6LPVTNQ2hqegqazU4MaAIFwJINeEcbLBcERDqXWjPsxmWSs57mSWi0zNsh0Vdqmrn3a1QjQV2YJoNGgBraJTMOunUImcFWZEinCyaTecqXJ6BwsD1vlMSFCU88EdmjKq+i1Q
*/