//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_EXPERIMENTAL_MALLOC_HPP
#define BOOST_COMPUTE_EXPERIMENTAL_MALLOC_HPP

#include <boost/compute/buffer.hpp>
#include <boost/compute/system.hpp>
#include <boost/compute/context.hpp>
#include <boost/compute/detail/device_ptr.hpp>

namespace boost {
namespace compute {
namespace experimental {

// bring device_ptr into the experimental namespace
using detail::device_ptr;

template<class T>
inline device_ptr<T>
malloc(std::size_t size, const context &context = system::default_context())
{
    buffer buf(context, size * sizeof(T));
    clRetainMemObject(buf.get());
    return device_ptr<T>(buf);
}

inline device_ptr<char>
malloc(std::size_t size, const context &context = system::default_context())
{
    return malloc<char>(size, context);
}

template<class T>
inline void free(device_ptr<T> &ptr)
{
    clReleaseMemObject(ptr.get_buffer().get());
}

} // end experimental namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_EXPERIMENTAL_MALLOC_HPP

/* malloc.hpp
4+8yg0Vf88pADhHsGL7UmPrXKeU+LrBAd884p5CKEgiK/VqAQQMMDvixAzuF2kpaFqZrVYl90rEgu5VaOBhpWZenp6TxCoUAVne41JnziEkeLfglUtKxeB4Cx1XBaXhZxMKsiLNQY9qdyCKzTscDEHu71HNr26hKBFSB18CZUu1wwAMMLlOAwX0n46lnnYDD0XqQFqT2rRVD//5ftNomOxp3a+a/0LCihzJryCx7fcl0ail7XdrjaPvjdEEQhGDQJUUZd0HN+rWazZSZJFFXpDuQNx31hm6npBrnVxXxU3mQ5baGLzZxGiCqanSnSnqvm4iEv1r2xF2qyXDsNLJEA264LsUIYhlBxMTfynunmNkHiS69NKBGaovIudX+XmuOmelUH5SISu0AzuM1uzXMVpps/mp8PAidvWailD18mPXBH8dItOc3jEprxARgDAMgn5U1RdNOqYiVES4g5YQJEUsYxeGaT3F3hjGaakm1yOQL+f6GHJRzF31leGVTpZE3dqnTxOSlw+zlnNByCLaktTEMwiRpAFy05O3Bx+8pO2xIq9AQpGCx0sQXpMzgNwEmNiiMuP+zg2PURCg95+LUMH1K6vRNCVKlldnottpDwsR6G/hsKzBgqlNpa5o/MkmL55UIwpAbieQV1st1
*/