/*
Copyright 2014 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_DETAIL_ALIGNED_ALLOC_ANDROID_HPP
#define BOOST_ALIGN_DETAIL_ALIGNED_ALLOC_ANDROID_HPP

#include <boost/align/detail/is_alignment.hpp>
#include <boost/assert.hpp>
#include <malloc.h>

namespace boost {
namespace alignment {

inline void*
aligned_alloc(std::size_t alignment, std::size_t size) BOOST_NOEXCEPT
{
    BOOST_ASSERT(detail::is_alignment(alignment));
    return ::memalign(alignment, size);
}

inline void
aligned_free(void* ptr) BOOST_NOEXCEPT
{
    ::free(ptr);
}

} /* alignment */
} /* boost */

#endif

/* aligned_alloc_android.hpp
RDpkSiojHqldr5dFtqPpkKKVjPHWEInszAkkuzSv5lr/YlDqqu2C01l2i0EYnuYBdTRkWhQ6cgYZhJtcA4JwZoFkHHaac0l5OI0QUYjB5e2dJA9gfDcUjX/ItQrkIAUJL9+JJI2RQKqnzkLgm6qMG75bZrLdFIdN9+7qtVzhCw8lTTVF5W4Wmq2SNG3roMwz4LtGN8FND2I4oHkdnzOihIZhutSoIwA0iat3otewDL7NTZc0DXINFfyZrislIOnT0RlKZ+t85sBUmhInbYrrvAmDmTvzF9SBilek/4Jn2eq9i/G8dm0NGkak8iuYynPSkyQzYJRddKuZXeE/jodDliJKr3KSiOXmRyaP9PILBsmZVbImCtdJ3gCMDLbadG+BhfhAjUZlKgMfqcE5nCnuA6junATJC9jkmulZx5yQrh6T9UdaqTbXCFzVO7iEgVlrs+GJXRSwuNLu7XZVCzBnSHZVa1lbVG5TCG69n1elKzlNix/HdY7itQrhVMj1lZZBdjMNj/cEERp1LA2YZ/dazk6f98PLXiSv2Ve87lCDWCqqo9pFgpFfFXPo3XH1cNcj3+U9YPM627a9bJOApk+FGks6h4HkFxYiU+FB41k9RlGVQ6Ay4s5oEw58JacHiOZXxoIJOG9p+AtQVE81
*/