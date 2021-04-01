//---------------------------------------------------------------------------//
// Copyright (c) 2017 Denis Demidov <dennis.demidov@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

// size_t and ptrdiff_t need special treatment on OSX since those are not
// typedefs for ulong and long here:
#if defined(__APPLE__) && !defined(BOOST_COMPUTE_TYPES_SIZE_T_HPP)
#define BOOST_COMPUTE_TYPES_SIZE_T_HPP

#include <sstream>

#include <boost/mpl/if.hpp>

#include <boost/compute/type_traits/is_fundamental.hpp>
#include <boost/compute/type_traits/type_name.hpp>
#include <boost/compute/detail/meta_kernel.hpp>

namespace boost {
namespace compute {

template <> struct is_fundamental<size_t>    : boost::true_type {};
template <> struct is_fundamental<ptrdiff_t> : boost::true_type {};

namespace detail {

template <> struct type_name_trait<size_t>
    : type_name_trait<
        boost::mpl::if_c<sizeof(size_t) == sizeof(cl_uint), cl_uint, cl_ulong>::type
        >
{};

template <> struct type_name_trait<ptrdiff_t>
    : type_name_trait<
        boost::mpl::if_c<sizeof(ptrdiff_t) == sizeof(cl_int), cl_int, cl_long>::type
        >
{};

inline meta_kernel& operator<<(meta_kernel &k, size_t v) {
    std::ostringstream s;
    s << v;
    return k << s.str();
}

inline meta_kernel& operator<<(meta_kernel &k, ptrdiff_t v) {
    std::ostringstream s;
    s << v;
    return k << s.str();
}

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif

/* size_t.hpp
wKfJuyANerJgkiJYBGl6DIN3k4kDfrlRTlI2UAQhLlogk6KGGe6VmM/ykhJNqVYCwdlGwzdHznnMd47MdoJQrDxDX8O0PPdz509vhUWwDocjcj3EM3CgUN3nkVW7Q1bSCFtj+jIuEN9AESn4QdxVKeR9hbmCXw2UQQpwCf33NfrRn4RtOGagutuuM8P8xmUuCPPqvaEtJFGgHHBF98ZiZCkMOR9+UMK8z65ar1QXI0CGpLl/hCxv1aZq+ZVwWFKLl1/OEXmUow/ZydV/miVQ8dSbre1DgBRV+SrRh9mkOtMpbNto4BK83+hI8IFId2hnA34KGNuByVUoGglXgfz78vbbT8qMhFjNnumgfDp61+1HAk3FzK80WU+livZ48DV/5skbaYQUgyMNE/4CsNrzkYi5KlpND+ZYqdRBUhjhQfkTk+Im5TpxzxzyQAZ64/s7aeUJ+cz5jXqjn7+gMpzabE7+ZqAy9QQ4g+MxxZKtEuA71j3P5IOhvVzlMUdp9PYb2fGgG6D+M4hk+Uc+/C7WpcGMgK6/X+EFXCx04KWBCDTdnPt8N2yg77agsg==
*/