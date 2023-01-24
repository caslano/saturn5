
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

#ifndef BOOST_LOCAL_FUNCTION_AUX_NOBIND_HPP_
#define BOOST_LOCAL_FUNCTION_AUX_NOBIND_HPP_

#include <boost/local_function/config.hpp>

// NOTE: The current implementation needs no-bind placeholders only when
// local types cannot be passed as template parameters.
#if !BOOST_LOCAL_FUNCTION_CONFIG_LOCALS_AS_TPARAMS

namespace boost { namespace local_function { namespace aux {

typedef int nobind_t; // Tag no-bind type.

static nobind_t nobind; // Global variable so all no-binds can reference it.

// NOTE: Used only to get rid of unused static variable `nobind` (this function
// is never actually called so it does not need to be defined).
void no_unused_nobind_warning_(nobind_t* ptr = &nobind);

} } } // namespace

#endif // locals as tparams

#endif // #include guard


/* nobind.hpp
v+5Jf2dnhsSXktvfNmfEXrx6HFDkpZxQYJnoEhhpcAYUOmwELkfeLtMkpqqP9zqXA8Hn4w36UxpSOcNYWnzUG4Q+ZW6NfvK17O03rB2i7LdQVYiaNPQLOeLWJs3gzWxMkY2dtXiV0xrP18Awt6xr0IOceMLO4YOfYKcZPqe5RjCYP4zdxeTZ60KsuVpOcFpATKBJ6Q1P16L+vod4k7OW9lHiyrWV5lEI0hParLYQKQvwxWlqRnkjMZpsszzdwvFk8qZ1/KqU5TrEWd0PPtR5Pn79rJbbkGnduvrmB3sZuQzhoroQt5ZYD22luCYeJIBjfEHExqTCGxwIUx2kkakMl8S2CbOJWuQ04sWKpXKlJpc8Ezkz3Y2yGF4OVcD2FYOaCTgSc6Zqx/bCzhG/o8wWOjO6Wwup0xWjyKfAFgvCMoBjFF1tzBYTK8ouYRHwB4QBggBRACCRCF80ICJManOPCHPsTipKnipbOFMiM36fkylpf4w15h5hl1tM6UZOX+bFgIT165hMFDtShcymdL+BjYhgcfTHe9HjGWslTFJNNn5Xa08lzKLElXBl9amPMkazbLNlYDh+0eP5UuHwNF+qihKc57j07HlZq+ffZbhDpX+QL0TXOVRs1csYfbQ6Tjd6/mQltFRZWTYcm1bQblE4BJSQZi8R3fPcfdJ/nq1NGc9vDv/lLC2vce3rxMAbgDx5hocZw/Or1uAEmd5G
*/