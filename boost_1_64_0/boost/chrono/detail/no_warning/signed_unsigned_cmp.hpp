//  is_evenly_divisible_by.hpp  --------------------------------------------------------------//

//  Copyright 2009-2010 Vicente J. Botet Escriba

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

#ifndef BOOST_CHRONO_DETAIL_NO_WARNING_SIGNED_UNSIGNED_CMP_HPP
#define BOOST_CHRONO_DETAIL_NO_WARNING_SIGNED_UNSIGNED_CMP_HPP

//
// We simply cannot include this header on gcc without getting copious warnings of the kind:
//
//../../../boost/chrono/detail/no_warning/signed_unsigned_cmp.hpp:37: warning: comparison between signed and unsigned integer expressions
//
// And yet there is no other reasonable implementation, so we declare this a system header
// to suppress these warnings.
//

#if defined(__GNUC__) && (__GNUC__ >= 4)
#pragma GCC system_header
#elif defined __SUNPRO_CC
#pragma disable_warn
#elif defined _MSC_VER
#pragma warning(push, 1)
#endif

namespace boost {
namespace chrono {
namespace detail {

  template <class T, class U>
  bool lt(T t, U u)
  {
    return t < u;
  }

  template <class T, class U>
  bool gt(T t, U u)
  {
    return t > u;
  }

} // namespace detail
} // namespace detail
} // namespace chrono

#if defined __SUNPRO_CC
#pragma enable_warn
#elif defined _MSC_VER
#pragma warning(pop)
#endif

#endif // BOOST_CHRONO_DETAIL_NO_WARNING_SIGNED_UNSIGNED_CMP_HPP

/* signed_unsigned_cmp.hpp
3/n/x01+XOCR9SfWJwe6j1fUtfsl9Xqt+BiMCCwq60S7al5Fei45gARAsGqBd7uTQ6MpUEJb05eDqkTisbmvkPbr4BgknkcaviKQJZ7B1iJzxIksZykxSUVuCMyi+x0hufWe6IrFpEskRm76RJnGAO98n4B4tktVwsV8CQEV9vvC24iSfxiSc74cyY9rnW63x99Frwa0Cj2FRK8lc9ES5o6ZtVz6F2pyzyP4xLPtWeOxjKg/uDpS7o0zpj2lEt4dhEYQ7vM7aQExnuddYFuDXVSCJJPfUOY9ZhHuzZIsjjdK6iMtyGV590iVeg+dtnooHP1G2T4vsfVOYRyk6hb9LhgsBwoP8lmXY2wonqAB1uaXNiwNunKoW3Z2R8ZNh1lZ0KxzZCLShFp5V3DRFf/PStQKhjEBrs8tQkLwGaSt1Nig3RSlaTawUVm0hbRPLRsh9vx74wYDXBv3Xok5GWA8I5B55BxTWdBmR0nMKAaPds8R5LsP/8juBMpq4pAcNeVXPHO40AJ75w54AxibmvJqpt5o7ye9ljMwcZmZ+WshTtocqy7ZbYyA54kDbg==
*/