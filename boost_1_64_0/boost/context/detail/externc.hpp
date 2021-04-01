
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
b2v9RYQLGZdGQtnXKNgTW9RzRm5FhI6ckFooU5DabChjtlDX5vtj1u0jjX6QnIFCLVfUfxc8Hx/2imV2oo7HYoNlg9GSbp61Edxwsc0cojKW+Rnelt13/LkKTUeMsz7KwwwnVMFdc7y1kEbxqN5TVjQCKlVKt1L/oPydy8tjKv6SFVaRLxgXhlxF4jWzvMuSpLX/9WmB+XW2TZtW96uavHiCpQdJHbXNHaUvncYPS3U80n3//x7Iac7YHx/JXXbpl78AnWH+wRt9RTMxIbivMdkpl+xXJAjSNwuhYXogUesZXRypUosqHi+kB+P1mgUk5PVxodVIOZkusox6ZB7NFLeXicwsZ15jtOUAK1MqcOUc60jldly2YguyuPlUIYM3Wsej6saQxNAw+dMRjYQ26eFX0HRJbEagEC2liYMq0l7nyqXbXJhLaxO+3geh0CAmBI/MkHs3w/M93baKG/zgHCaaTs8xiAEGVYbZ+D39j2TzDvsKhwg38y5q6v1WQ7PQiEsF2U+RwmTJgGFWCpRLXAG9B99eRDY2GjyER3YKcCZPPAUOO/eMT41zpQ==
*/