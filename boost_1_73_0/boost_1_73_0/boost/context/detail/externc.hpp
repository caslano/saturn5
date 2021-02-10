
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
x9/ukPntDmsf2Blx/bJYdUWgpO38e7aeRJw4Fvdr6cposb+pnyNJiXXD1mhaga5O01kYh4NwHDlas2fDv4NP0/HQLje3DazlP+7tClELs4fUL4o9OtyHfz14vEro4Bsr5EEl0NAztbvQQeAhmRxYMvHNjensaCOJYrILF9c777/tegougtE4+DAaj+JLL8hz97bqXhWswGwYn88mcBGMz4fejOMewvc08j9Mwo+OsfmGRwgTrrQ8d+93TvB88nESfp4koV2DpIRc6ErdiYZDCMZRiC8fH2Y7iUEHcYTZbY8H4WQyHMRJHD56NBtG4fhiuDn3/gdQSwMECgAAAAgALWdKUnCgmSTEAwAAGAgAAC4ACQBjdXJsLW1hc3Rlci9kb2NzL2xpYmN1cmwvb3B0cy9DVVJMT1BUX0FQUEVORC4zVVQFAAG2SCRgrVRhb9s2EP2uX3HwvtiFKsdL0axtVky1lUWLIgmS3MyAAUGWqIibTAokFcdY9t97lORkzgokH6rEpny8e+/4+EhrPYI3P+wxLA0HLz5p90nxwfFQFAr+F8nV9wvS9AH6Pyxc4/gKqik8VT2kE3hV1QOMu6p04DrX72n6Crq1blJ/TXXxOtWvGOkrh/o5b/aC3lYKxvMJzD58+AXews8ns/cm
*/