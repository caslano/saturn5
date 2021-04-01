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
/twArWP6nBysOKMn3SxftZ3QMzQus6bj6U3PBbiCVXYL7njUVM+rdCdMVnB35+mAeOZ9cO03pkf4Jkty8sq4AkJqkaWVSxdm/ad/fkfYFFgEopRqeBjG7lynFTPiPLSF2w6XkP/80yFVZFZCh0oDxeJpXHYDbdw7WazBurr2wxTGjZmkw8ieU4fIJQwGb5EiISEzi/hX43ZzLTfPlXUUFd9hpIlavN5vzO4nqyqENyvUQVRJHH+nuMSkbaiLEQ3HGBN02peDvlINxEkhOlCmwJB9qavmtIL3Ga+J+P8Nt/04LaiPgPRdkF3wNHu8UArwE9ymZhHmYuUUEDrjjOFiDSY/jsyyyeAZ9xkGaHgJTXii/au28wgPjTuCw+Ua3u4Ue7RUT8WE3GoIdssgfRHPWWFhF/GbOqxTRR1F5BZuhlaUVR5NavubaDS3FHqdBeysi1V223Xclo0QvN83EulrRXEgEcxXAfsyq/RjPEepn7GEIbS0wXGVAU5RiBDfcLMQj5Qw0FJ3yUca+TmsgCiN7/Fv6Tkb0UxYglbwSOst1xYSCtp0jigdFof/pg==
*/