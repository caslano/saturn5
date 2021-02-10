/* Copyright 2016-2017 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/poly_collection for library home page.
 */

#ifndef BOOST_POLY_COLLECTION_DETAIL_IS_FINAL_HPP
#define BOOST_POLY_COLLECTION_DETAIL_IS_FINAL_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/type_traits/is_final.hpp>
#include <type_traits>

/* technique explained at
 * http://bannalia.blogspot.com/2016/09/compile-time-checking-existence-of.html 
 */

namespace boost{
namespace poly_collection{
namespace detail{
namespace is_final_fallback{

template<typename T> using is_final=boost::is_final<T>;

struct hook{};

}}}}

namespace std{

template<>
struct is_void< ::boost::poly_collection::detail::is_final_fallback::hook>:
  std::false_type
{      
  template<typename T>
  static constexpr bool is_final_f()
  {
    using namespace ::boost::poly_collection::detail::is_final_fallback;
    return is_final<T>::value;
  }
};

} /* namespace std */

namespace boost{

namespace poly_collection{

namespace detail{

template<typename T>
struct is_final:std::integral_constant<
  bool,
  std::is_void<is_final_fallback::hook>::template is_final_f<T>()
>{};

} /* namespace poly_collection::detail */

} /* namespace poly_collection */

} /* namespace boost */

#endif

/* is_final.hpp
fmI1SCZt12ZOOeKT/L7U5Pt8lS3Of7ie3H59/c3Lm9J2/7Cevrq+dp59/eqHm2/x+Oezyiz5wx9ffzu9vv7WmXSd/iN59Wry7cXZ2VWpSVmp/vPZY0l3KbX7TakpbxZ3pcpkq1LLVqvSN+WrN5WCiIpXkn09365L61V+WGHV9l0yVBa6WxX5mxKZmj/MNhr+//9TfaUq9vTe9XuX5XXoV9fetLoORpeHzyfVNehX10Q/7+n7Hj715F7Dk2epvg6raxRV1ziurr5+HmoMoX4+0bM9PXIc6uf1VcOLJ4aa3lhf9ec9wEs0lfpJMDT304jGe3IFfRp3b6CvPQN7oGf0MZY4ADyCU696gLmBwNOfeMSPANeBgefFBp4XnYCXGHienhHoGSE4pyUUagyhZ54P9PgwNnwNJ4Dn9+RflSQ0Vl9zJeobGKASz0GlP2qgEvQF5hmo9INnUqnhgTJQCQ1jGJHmTRiY2bgG6eGswOP1Yi24lxlDGVWtUVPWh4TCy8ZZgdDX75PsJiTBseFcf0j3PcLg0/MaHs+gzwdJC2zSHaGlnsXw8Eng3AcGNmBE7XpO+nygmY16jk/BXdFz5pV3Ap7mgPiJhKRP+iKaEoo+aHiRb/RZPicd9kKigOhuwC/yEArGpJ+ewSC6oGFE
*/