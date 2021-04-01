
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
QXfk2Jzc2kikFqQpHR6GOg8iiXf7ko/FeWJGzsa5tM9ajJX7RLD3X1sUOvV1exQaN+xyQCMQsmx1UTkVcM+BcYPn3I4O7bwb0XuR2BS3ikJq13cdge4M+rJ325qef+dEpexqLAaULLDoEEk637vF2cd33EyaFgV1/X7DwYJ+YFKOwXpm86xUQH9teQ9Vfe+CKQQtcOC8jwiMvH64asEdVYG+mNRvjfjWV0t+HWLqdD7xb1SrZupM5/W1gzFn3xLpwjStnYR7bR05/3akmG1nPvrgwai4hzUgjtFpftkkfxK9qK+qJsVBmNXINS6QUAJ29LqpjfDUqDoGLraSC1zLD9ExLMciDDPYefejxjH6FHb/7OSt1xXedu7VY0zwkxKu8iPpnsjxztJgjHLERfMVM3dbOe9ChvLVEH7ewyEolwBhu9zaSP6Xmew7pAbOv2QRV5hH+wXNmgP3beMou9rUKsoukmCip29yjtv0xaTaa1GJmAyoJN9WkJh8ercIu2GyyP4Czg4V/CY4W0wkoC88pQNX1ehGLarlrnIspnwOJ5jotY+w7/wV9aua4Q==
*/