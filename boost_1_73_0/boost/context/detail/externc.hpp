
//          Copyright Oliver Kowalke 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//

#include <boost/config.hpp>
#include <boost/context/detail/config.hpp>

#if defined(BOOST_USE_ASAN)
extern "C" {
void __sanitizer_start_switch_fiber( void **, const void *, size_t);
void __sanitizer_finish_switch_fiber( void *, const void **, size_t *);
}
#endif

#if defined(BOOST_USE_SEGMENTED_STACKS)
extern "C" {
void __splitstack_getcontext( void * [BOOST_CONTEXT_SEGMENTS]);
void __splitstack_setcontext( void * [BOOST_CONTEXT_SEGMENTS]);
}
#endif

/* externc.hpp
WEkBq2VS0znNpl/Tr+nX9PuxXwgz9Tfb/19VMaVeDwBY1i8+A7AqxzLrglt1k96fyEAPuBbOzOWPLu7aTE11VVVsX2YVbqzdTy2va1hP2MKkYXvxe3Oolc4RtxD7laFDSdWV7L9fy2j9NvtPgdg8+0vdHfcEvzkxrtt4nmqmXKuVzontIe43BjP4ysVJzEpdZecz/lrpOz9GXGZNPwtrskV5VFTPqi+dUYcV+fCMDL3ucd3w
*/