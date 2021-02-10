/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2018 Andrey Semashev
 */
/*!
 * \file   atomic/detail/fp_operations.hpp
 *
 * This header defines floating point atomic operations, including the generic version.
 */

#ifndef BOOST_ATOMIC_DETAIL_FP_OPERATIONS_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_FP_OPERATIONS_HPP_INCLUDED_

#include <boost/atomic/detail/fp_ops_generic.hpp>
#include <boost/atomic/detail/fp_ops_emulated.hpp>

#if !defined(BOOST_ATOMIC_DETAIL_FP_BACKEND_GENERIC)
#include BOOST_ATOMIC_DETAIL_FP_BACKEND_HEADER(boost/atomic/detail/fp_ops_)
#endif

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#endif // BOOST_ATOMIC_DETAIL_FP_OPERATIONS_HPP_INCLUDED_

/* fp_operations.hpp
GhewzQAQ/FeGjIjc57SEffZwAMr/A1BLAwQKAAAACAAtZ0pSlR6xBa0OAAAZLgAAKgAJAGN1cmwtbWFzdGVyL2RvY3MvZXhhbXBsZXMvTWFrZWZpbGUubmV0d2FyZVVUBQABtkgkYLUaa3PaSPJz9CtmbaeCNoBsnKSyvmQrGGSbMwYK4TjZy5VKSANoEZJWEsbO7f336+4ZvXjYSZxzHtJI/X5NT8v7v/68H2WfPfpj0j8TfuCKCIMo+JPbyXZg0/ybiT+A9AWuj7DQWI7xt6myRzH+ZhXCMCWPd3hvmo+w+YKC4X8aIn4x8RaeKPuA1wrC+8idzhJWaamscXj4ltXg0jissrblu9xjRsL9MY+mVfbOoScfZtbdXT3mv1cZT5jl1YnQaObGLA4mycqKOIN7z7W5H3OHWTFzeGxH7hgWrs+SGWcT1+Os1R987vTOq2w1c+0Z0LgPliyeBUvPYTPrlrOI29y9FSRCK0pYMAFsoO24cQL0lokb+HVgzVnCo0UMJJC55cUBs24t17PGwMZK2CxJwvhE0+xl5IHkmhPYsWanqtdnyUJq8RkkWFj3LAgTlgRsGfMqQ7gqWwSOO8ErmAIehsux58azai4KMPIdLYhYzD0PSAGay2MhMmeGtEwVoVgI0roJXuLA
*/