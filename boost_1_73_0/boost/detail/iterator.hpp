// (C) Copyright David Abrahams 2002.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef ITERATOR_DWA122600_HPP_
#define ITERATOR_DWA122600_HPP_

// This header is obsolete and will be deprecated.

#include <iterator>
#if defined(__SUNPRO_CC) && (defined(__SGI_STL_PORT) || defined(_STLPORT_VERSION))
#include <cstddef>
#endif

namespace boost
{

namespace detail
{

using std::iterator_traits;
using std::distance;

#if defined(__SUNPRO_CC) && (defined(__SGI_STL_PORT) || defined(_STLPORT_VERSION))
// std::distance from stlport with Oracle compiler 12.4 and 12.5 fails to deduce template parameters
// when one of the arguments is an array and the other one is a pointer.
template< typename T, std::size_t N >
inline typename std::iterator_traits< T* >::difference_type distance(T (&left)[N], T* right)
{
    return std::distance(static_cast< T* >(left), right);
}
#endif

} // namespace detail

} // namespace boost

#endif // ITERATOR_DWA122600_HPP_

/* iterator.hpp
xCsv3hZ8wspMCMu2p5p5bBCpi+/XpHaLP2cyoYgdpjmLsOP00AAnCNr+0+ceud48tPVnbkXJvPgzcF6N6Gigjqg+jfNd8yfhT8mXZs4Qzrg+j3OO7zIFct0xb0l4I1M7c2V5KOSsTdngxNdyl9u52rES7u+I133mFM2XTlI2FzpDae+TkHnIhchVPO3fgTyB7EY+JXZNnTRzDLueByDjkVIkW8Jhh7vkSWUgyompsTZIuhZ4
*/