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
U0PO/G25IQNbqSELtfOE3mIaAjgxVbPHg7OTfu4i6dwNVLmNyhEqjiw0swQmtLLsgx7YkScI7FdD8cN63Gq0s1anzqktus2OeW2dG2jrS/62vk43s95EW9+taOs52vmF3kxtbZuxz51v+uD0082nGE7+zSCcr2rnUX2tutCF02CpcCaiwpP2hAtjgn7qIqH2L1Jlp/texF29A/YevVdltWpottXc8Ro1l96ZOznHvHPQ/843qdgP613USvx2Dv02rOaunjNRxlXNjpp7ZM5xajkw1YhOuX9b6/5twSw1t6qe6IY9bU2ExnQKOMx5q0Z93e1bHVU6qRSohM00LNBL38/KVq/S+w5p23Yyb3ld/tS1YXXTrMivQtYV9j20V7Y7l6uqiKUiacIltOrcNRd/2rRnSjCn254xtz3JajX7Kmkl8G2OnleFady2aVWdqVINpzgqdiRyPDztTNlH0WqD/6gNZ8t8fJ9ufv4W5uMpr3ETB6lx39LWxVoPu+vD7IWNvBdOtlVk0hsJF2bsbd8cz6eb9NuAufDt4AZ72rpPlwgG4zYXbw/TT8bOdH+XoTbbKkbzGKN5jE1GzDxu8cP+It3cyLCvrID9pLNXr1ZFd+/OBOcBP5xjdPMsw/l+BZyj1lf0yplhvOOHUf27GtX4O8Co+V0QxivOPXrsw9sy8DsfnDPpZiPDOacCzqvWHe4MNLQ5qm5braobj6k6
*/