// Copyright 2019 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_DETAIL_REPLACE_TYPE_HPP
#define BOOST_HISTOGRAM_DETAIL_REPLACE_TYPE_HPP

#include <boost/core/use_default.hpp>
#include <string>
#include <type_traits>

namespace boost {
namespace histogram {
namespace detail {

template <class T, class From, class To>
using replace_type = std::conditional_t<std::is_same<T, From>::value, To, T>;

template <class T, class Default>
using replace_default = replace_type<T, boost::use_default, Default>;

template <class T>
using replace_cstring = replace_type<T, const char*, std::string>;

} // namespace detail
} // namespace histogram
} // namespace boost

#endif

/* replace_type.hpp
RyI59ztVmk/0zslJBdFxK5Y9cALPd9nsSxDj1gk87yTAocNWx/LP9JLP+s6kO1QdHABslwB6Q8vzyz/rlHw29t2q1so+i5WAQP5pCaAzGAQUvLMSvJHhXVd8djKAR/7Mvxub8CmBkkGeEmHuuRw6XYNNHd6QAMyf1jsM8Nay2zoVUkchjSGZxjYKaDv+FU3lTuSxTUH75sCYDCkCU0Gp0bsOTMv2VeefDLaDj3668Fnjm7OGxj+FvDbdruk6XqchIUhxa0hqB0dky/Q/qJDnOKTtDykGCWfnCQ556Xm2een4luFTJmfO0ZN3yG+Tpx+yHc1syrZHaPN9szuhakqnpEuGd2f3rvq2R8Q9L8H1xsApGmhLVOtMSgz30hxYpJWR874E1+qrbiASxE4ZoueNLRrkeRlkz7FvSJAtaZrMINk/6EKll+L6Q8+Y+FeB56oa7DFypxQZlDq47ZJQz0tRwbgkLZQteQnKzRUGTQb0ctB0Qj+l4HbKcSe29SGx2kgTwXk59Ji0ViD2dGG0vGDsOh/uCMiIyb3bQzOjwSKubogtnOF2XccfUmThvALUGPreTU8dtIUZTnnettUx9SpMJlw9p0+YszsFVMFsAkrHjucHsB7Yxoi6IIu2U4brss0mfa2RbKcMl+2p6pDb
*/