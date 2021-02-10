/* Copyright 2003-2013 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_DETAIL_MODIFY_KEY_ADAPTOR_HPP
#define BOOST_MULTI_INDEX_DETAIL_MODIFY_KEY_ADAPTOR_HPP

#if defined(_MSC_VER)
#pragma once
#endif

namespace boost{

namespace multi_index{

namespace detail{

/* Functional adaptor to resolve modify_key as a call to modify.
 * Preferred over compose_f_gx and stuff cause it eliminates problems
 * with references to references, dealing with function pointers, etc.
 */

template<typename Fun,typename Value,typename KeyFromValue>
struct modify_key_adaptor
{

  modify_key_adaptor(Fun f_,KeyFromValue kfv_):f(f_),kfv(kfv_){}

  void operator()(Value& x)
  {
    f(kfv(x));
  }

private:
  Fun          f;
  KeyFromValue kfv;
};

} /* namespace multi_index::detail */

} /* namespace multi_index */

} /* namespace boost */

#endif

/* modify_key_adaptor.hpp
U2lD0vs3R1rtSZFVkCS+IujcqouWubb7woEh07dgFBM6Jk5iLiLtwkg52iFWyW1NeRxbjqit37gI0zxCaBpK1Emaq6YlLiOc54vCHCGhIozOPgTHvdHRcDCFnUaDCxIohbbChCnYpG7aje8NAGunY4ED2N6jr7ZN2LTC/7wCcEnb30dnw6EH9v3eehY4maSLdkD3d27BA6YWr+tNFkXuxNf2dx72I7rxwqjbzztv/ry0VhJaTiPTZg803RYDm8Vy4NLuleXyBwRDeGgCW22F0bqSPGpTF3vgkw6oG6tnNHlWHVkoiTPLKaHFLZeskErABTcty0Dwbjg+7A2D3nDYhhcHjpVBMH7fBksZQJwpKiRuaUP3SnnQfITShpgGCkYXotneczGKalACZoPpLBhMJsGH3j/jSXDYO7Lb97aapRYlbsWMB5p/Q1kbSJxNjeoKVQdvGN0i7NjUuxua/pteY3WU26Oh4VGcgSuiRG9uaCrLe+Df7VVE1+QHLMtQRC33Zc2b3IlbYn5NZE7ZCWk5JTkRv0STVC3ulAUc9ledybC1VbFZYtFkWYEoEMCZCkqdKPllSScF6QxDGrGlCqqAmsVaHQ881qb2OlkATTv1aej/nF4/Yybxu2+6Oxvbf/Dmj8EF1xy2oFvWtyLN
*/