
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
8ehWPQ4+9kfqQRezU1ahXfoEJR2cwuHryniThYGv5Ac+Wr9dthvHJRa7PIAXp4Ijo92wMOPccktHEVHhgQk8yX5QtkW8CwuUAc0Yl8a0apY8nrqXOAPovmnQopw+Xoq3+B+j4OxlUL3QsWJVEC38m6T2D/McjAzBIpHxFdpNoHNS0tUpuP+ATvLdNR0TlVfk5U5i4p/CcUWKEpwVDKWGayet74SFrQ7CoRvHS9f7pJxJXWtyPWcKhS8X4/58OBm3CO1F9IUzqcFP1Rv2FkvXyzIPAo6ZbVjEl/IxwZxdOnCfRj50sANmvitdA2qaI/NOKoRDEGQycxOB4qCDb2h5savGtoewyPQKeVWViTrb45iK7Ipbv51UphTeE19wXlGW06KCfMQgKXcPEJLAycWFk2aDAxynxrMJDgEzrKzBmJ0vLi8HUzYcX05IgkhjzqIkSBXCJnIj8dgQhAnCVNGnKNEpaTowSTxKPxxG42hJk4HCUYoaJoYKXDMmtspVHWvkuHfjnGtJ2Me9kHufaDBeuVEipGJ112meSK1ii6LRIjRCZ/+Sq/pCgoMlY8RIhF5OUC5x4JVeSFISIgdYNQK2OOSpRBroNGKD6XQyPcLplCZqGie0nE1K2KwNpQJ2ta04ZlI6ccLtDAdb8aWj
*/