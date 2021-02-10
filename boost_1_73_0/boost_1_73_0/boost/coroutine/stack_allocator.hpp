
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COROUTINES_STACK_ALLOCATOR_H
#define BOOST_COROUTINES_STACK_ALLOCATOR_H

#include <cstddef>

#include <boost/config.hpp>

#include <boost/context/detail/config.hpp>
#include <boost/coroutine/segmented_stack_allocator.hpp>
#include <boost/coroutine/standard_stack_allocator.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace coroutines {

#if defined(BOOST_USE_SEGMENTED_STACKS)
typedef segmented_stack_allocator   stack_allocator;
#else
typedef standard_stack_allocator    stack_allocator;
#endif

}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_COROUTINES_STACK_ALLOCATOR_H

/* stack_allocator.hpp
SnrLwX4q64dG3BYatqbbMDk6egs7sLc7ObTglFWClxBpXi15c2vBu6yT/F6wr1+p4u8t4BpYSTccxoVQoGSu71nDAd9LkfJK8QyYgoyrtBFL/BAV6IJDLkoO02C2cP0PFtwXIi0GPw+yBVXItsygYHccGp5ycde7qVmjQeboAf1nQmn02WohK4rhOWjerNTgxiTBSiWB3TFRsiWGYxoKrWt1PB6nbVPiScaZTNU4XZeCFnr13akWmM2KPYCsNWgJreIWGH0LVjITuVmxRCis22UpVGE9poUBq2wsG1C8LAd3aCq46o/AIRqqZRlNqDF7oc2iZKVMtPtCrjYUsayDo7xtKgyHZUG9TGLhLWirjDedfleIdZShyl3JX2jZY+4ZyAqzgpEdgRuNYMmUUBZcu/F5MI/h2g5D248XEJyB7S8Gfxeuf4rYEBi1Af61brjCLBoQq7oUPNsI/lMnndD4HKbz0AtmcXLqR0nkhFdOGME+jCZH8EdbGWgfjGBUiqXpPRzS/UO6iwLzlXCmHhLFteky/hBQCn1G5+Dblw55zvHNDrYVm9XwnDcNlgs3UdLcYfc6y2jhB7PIjcgvokrLNuPwzoTqkVe8J53XVKL8+wy2zA68KhATJULjmegIwYI18GqIt/1rF/HUiaah
*/