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
FZJAnDN69vXLh5sr7mZnR+oc+vFcohiBZlJs6Ef7+gf0RcteuafM3TnMHo71Cf2mkO9+a9vCQKki0VaqO5XrofOlW9iyAay2IGuWlr2gZH26LjBbLgg8Wbcx6wlJLrcRRl7yOCaRS5ILBlM5vhqPALb58sY+ReQ7Eot9ddNwAbZ9ewc1R7c0w28GDGX3b2LZ25u7+/MPl1eX91+P+v5v69vHoKYftH0CJ6h3TLECgGgiY5NdRph1baJwHwBEaozkrgSivkkevP989+n842y4w4VUf3FwZTl049Dl68pucXthJXCm+s4S50FOj9tw3p8qLTdgngt1X3KmCX9vP93NLmf3n67vqdu7/nRBkw3IckswgFBuSPimsclW0pOyq7K0FAitPSPzZluMtnDDGKiJGLVDgHKXcNg3AlfibJnFDd02NyPoR029Nbsg3SrSq5/I8cjsuZjCqelS5qS08BWCDuvkT5lDHXxsYzHpwZsFOpAB+tsnCEFANlI8k9SBl8qwD5o3vrGK91B0HONIQCGiB3FLw6OUC7kTC92cZ9LkxmRoCjUNIApuDi5ZeeKvfD3jmv//a5uaLjqvdzDRGSp0YGDQvdyAgRO6I85ftv5kNMhVMIEJMrfJkwkeAPehwBCfNBkzSwojIbEyZ6Az
*/