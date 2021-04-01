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
4DKtLWXuwTeV3izQDz1e3jr/WJgP0z0WI5VP44aiwcmz+3V/5MQNEO4tZTST/K31GAGE9IbqFzdCMYbWC7nFS1bvSSkp00VLOjS+eGDQ3YuouG940DsFN6UuAoJiOvhUyEyJ9aHJlfrhddcZytgskKXtlwcXFcp/8N4iGAHXLxjzO9rfn3aDh0wi5RwZTIh0Wk7oV3Q4FTPmqAGs+DuY5zsLsAF8B+xQfoTwQ5CcWlTlE8/rh4TYoCVU0xqGVA7HE2PHzc3HY5FIXOhwdpOf+gNvSOQVgmzqnX8wcUoMeOBiuSHq41b2Y75yR/Exj0ZzhmK2uhlXxCbSRxoK1Muh26j3fp3BVeVAhTvb8QjlkCe2pBag2euVyRsz6W3jSg9Y/vyLH57RlBpI+U/rHDV9SN1myvIluRxmfhZXE3DuRx1oV3goGpveZg54IVp4lTwFQ6bhw+/DWZUPGV1/7teOBmDo9pEBH83TaNbjDeG6mrd7MFUdO637L80JYBV8x6Vm4dcBm431lPeaV/up+uSeocGIJGAdlAPKofhguiPMWfAY8kfgYUSJuXEhsQ==
*/