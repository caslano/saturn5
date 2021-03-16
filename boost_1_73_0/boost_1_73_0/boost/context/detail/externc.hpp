
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
V142d35pSSH8ly/+yjmgkuK8kkL4P3dVST4e5gszJfmlLG56XmFRlrLlFRYX5eYWFc7Kz7JteUAWgWReXsHMPM4sj2v9uYs1lkxZ/NYU602YOl+EG/opt7OILS7Z9v4Kt+PZYlGLupWy5DJ13gg3nGEITNHlIEM4qv2SibU2LcyRgqf+P78w3isjaISCvcGcrpXXw7hudgpbjpOTaSyOPbuCEdZ2tPR09XatCmZNbrwsq74bHt6ODR2d12WVd60=
*/