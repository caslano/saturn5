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
jQrQ6rMhO8UbZrifGs7mx4PyUro0htO9Bf14iFz5tlHFyjfQf60L2CRuILzp0XQ+Ty9V95V1jsj6WX/M3n4cqu3dXirjC+Z5eLLsPA4hPaUctuEEXZDegqI6NfvucbL6QB7kJiFxuR832ThAqJESLbmAdfp6txOWU0v8BeO+oHpyN+HEAN2+oKvw3nyQ5lYwwSIoP1KQWr92Yy0F1MYLdcRzEdhUfOXSHG7M7DbGC7XE9EHf7Hg1WbJhqwLFwc+q2UheDQPV+ZCcLjyJ8KltdRiAWDD1NUEw6jbTvnxuN/PazyDg3hKI/YZZk3dZQbJMZVl//pukcNhPxj4bfS4bpqU/nDBVH0epLlnhLES53ePVqm5FG74uDH9ww93qCQQC7PFcWga9GgE1FNC2yIBotySmRZBcnERgnfAzbBk0FJk7ABLHhGWA2HmhEXi1XwD6f3KpCVf7DDLmgVpjZv3eR41+Ci5QCWTswnUTwQXy7Z8T4NPpm1OBVgawnC46i0xeo95coEtUAguzmgPO3j/4blrSIk1uQm6XbOpS4EBjm/WK9CC6TQHqNuM+9QwQDaVLeLijOkjHKzLgbZ8ppxuVMWgNb/INiHZ4QhsAU4bGddZcmFtvM/KUXUBA3BRQYsjo75HNdAA+ZC7k28ucoBPSNmg/rx4gCHchya3wRBdeMphUD1jCq2Xf7Km16a7aQCNdGOpn5QRNmR1v6zsY
*/