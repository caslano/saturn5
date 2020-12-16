// Copyright Sebastian Ramacher, 2007.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PTR_CONTAINER_SERIALIZE_PTR_VECTOR_HPP
#define BOOST_PTR_CONTAINER_SERIALIZE_PTR_VECTOR_HPP

#include <boost/ptr_container/detail/serialize_reversible_cont.hpp>
#include <boost/ptr_container/ptr_vector.hpp>

namespace boost 
{

namespace serialization 
{

template<class Archive, class T, class CloneAllocator, class Allocator>
void load(Archive& ar, ptr_vector<T, CloneAllocator, Allocator>& c, unsigned int /*version*/)
{
    typedef ptr_vector<T, CloneAllocator, Allocator> container_type;
    typedef BOOST_DEDUCED_TYPENAME container_type::size_type size_type;
    
    size_type n;
    ar >> boost::serialization::make_nvp( ptr_container_detail::count(), n );
    c.reserve(n);
    
    ptr_container_detail::load_helper(ar, c, n);
}

template<class Archive, class T, class CloneAllocator, class Allocator>
void serialize(Archive& ar, ptr_vector<T, CloneAllocator, Allocator>& c, const unsigned int version)
{
   split_free(ar, c, version);
}

} // namespace serialization
} // namespace boost

#endif

/* serialize_ptr_vector.hpp
wL5pR03yZj604i2TYJVE6J7dBG86e7tsAjT6tWbTcLLNhxGGDWzRGQt8d3AGS0sZNhES9W35fom81iSM9zfsdNC/GIKJ9G4W7+c0i70MCVm/cAZXyE0e4b70F3P3tb23dFsT5ktzY21H+ho5yb89BK/lHpXholziHpfMM9I19NCaVJ3kZa3fb6PmyngHLmnnBaH0rRqywqV8RHk0CjqTUTqNJbZeF1pW1nvpgGDdI91W1n7KZiE39jsxcwlbylqgHybluxVcvGNHqHjLTuRdEvT1jC4rw9tk3vK9h9g5ec4PW3PRV4v7/WXdtv7RNw0S5SVzI93ZMcAaK+nhqa8EkL+sOWkzOhfyt3yAfSYyelovvbdT0oRFkW+/xJYhkqm9LZmxbfQ+MeHyzcacLFnK1r/7WWloXdg9/znp3+2c7T//WtpfbdcPGQBaHZxJ3Lx7aTMbFzentYtIO3a/JQIzZlQ4JvgD+b6+O+dxoOnbrXxb2+LP8RZF+QoZOJz0mVsMhybR7KroT0cENLXNBYsIiMPxygV+dIBDzP0j2TjE4OFbwGCjEsF9c1t0r35IAYOeLJ9pemz9ThSyEW1grmvhT+Jn08j3K+2wuLP6J8vwetJfllQirgwzcbNtSqpZm5R0mmtEPD3gErY3p/P6pPvF4C5oZd+xaYR3I9LIrn9AIvLJ5oEoSyyNSEfsj4TGh4I5SLH/ETy4Qb41KcdaZ5pxGNZ/aVKsT5+dVe/Ivh8f6HZkqCVjPvTcmDqQp84x7IsXQPPEHow5oO/Xrf0Fvqzq6fyY/lgj5ZVyxL+LJJWy5OclorzGBumMUqZf/ZFwVROUtX+3+1WcvlooytlV/mYID01BN2w9D0jU1Df6zmCN2dMqx1b1GWPMHCvMGpd1WaaANFi/uIzw1bWMC/1phW7ypC41LqbtmmN1+H1h/oUl2gqG9ZL3F9RwfwGXPenrC8Kw+0W5C/xD8eOivXYPZvFQEyS4Fn1OAvrgEl7kR9DDozgqP3b0Zh50Ps3oRGttsiAYFelOKXTfo9k0jcvkHkMZTrCM+4Spk/YbWpeHI5N03KdM3HHBjB8JRO38THyd4VcYLutIuPCHnxf+Smfskv3+ReNndsavsEyvxKYb1ec1mY51R+6bYV1j7nF4x/BJhxf4EhCl+V7oZ1aWmqdKxXwuYXFllud5P4aGFRt0H1LbbXkfGyPvB8XK+6emDGNNZ0Ntp/XsZ4Rh2/wRjTZu8m0rf5LOzLVmnO34QoyjrXe+CIv1iaEM+vZXhP+QDN7EzwnfjQfbcR1q4ETY9wbbVmA/GGxLH+s2n/ILsv3GY2L5tP5A+V6BXtBI82NXlBH6oiB43yTTNm840IztqLL/3E2rmSvOjDu9eHIUOx13o4HWHePkKtPehHAZ175XflMdXiJCsbuZZU5nGsbpGcQRUaL0cgljNBqIC8NkmdcgGaankaJ6DJFhbGiw+8FWUXh+QYLtpSWFk6akCSP52Qa6gMgwUq+VpWoWirn+oVk0rWP9oa30RRQ0rNNp8ZQ+0HYxcXGXdPSQZvhAIfuphG9wU7j7GefLRsTVxzrDW9BJOlKvjYbGSsSXOz3XIPMbE0uXyPBHx0Gj62tmKuQ6yvhO8mkdx7SLyGeCoRuniyvKItLaqZO0tBUWsjRxoNCLujeJPY1RGqGXmVoi5p8ndcEXwb/O+AKXNW/SdIWxdPm6aWR6RZ3k60ug5EFxPJ1elZJ9ZjJ0vLkqH8VOy9nUOBmy9gfPCmg0G+vZWNYu+lzFQPkOtgkWa79VhGO1tdHOei8XZjfW69n2dNg06KmE2Aoa8W/OQOGz2fPRos3npflirn4WYQuiMPJl2qtOzH8QZnwFwjM=
*/