//  Boost noncopyable.hpp header file  --------------------------------------//

//  (C) Copyright Beman Dawes 1999-2003. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/libs/utility for documentation.

#ifndef BOOST_CORE_NONCOPYABLE_HPP
#define BOOST_CORE_NONCOPYABLE_HPP

#include <boost/config.hpp>

namespace boost {

//  Private copy constructor and copy assignment ensure classes derived from
//  class noncopyable cannot be copied.

//  Contributed by Dave Abrahams

namespace noncopyable_  // protection from unintended ADL
{
#ifndef BOOST_NONCOPYABLE_BASE_TOKEN_DEFINED
#define BOOST_NONCOPYABLE_BASE_TOKEN_DEFINED

// noncopyable derives from base_token to enable Type Traits to detect
// whether a type derives from noncopyable without needing the definition
// of noncopyable itself.
//
// The definition of base_token is macro-guarded so that Type Trais can
// define it locally without including this header, to avoid a dependency
// on Core.

  struct base_token {};

#endif // #ifndef BOOST_NONCOPYABLE_BASE_TOKEN_DEFINED

  class noncopyable: base_token
  {
  protected:
#if !defined(BOOST_NO_CXX11_DEFAULTED_FUNCTIONS) && !defined(BOOST_NO_CXX11_NON_PUBLIC_DEFAULTED_FUNCTIONS)
      BOOST_CONSTEXPR noncopyable() = default;
      ~noncopyable() = default;
#else
      noncopyable() {}
      ~noncopyable() {}
#endif
#if !defined(BOOST_NO_CXX11_DELETED_FUNCTIONS)
      noncopyable( const noncopyable& ) = delete;
      noncopyable& operator=( const noncopyable& ) = delete;
#else
  private:  // emphasize the following members are private
      noncopyable( const noncopyable& );
      noncopyable& operator=( const noncopyable& );
#endif
  };
}

typedef noncopyable_::noncopyable noncopyable;

} // namespace boost

#endif  // BOOST_CORE_NONCOPYABLE_HPP

/* noncopyable.hpp
4ty/BTNHt7yGV7GBiOGU3pIbWjElzz1liliebhVdZgGk0p3T8bnDJWdNWXWT1bBUF1dEJlcWtlQVHMV5fWYrymoOds7zHERf3yERDMtQmb2OLDbWPatZcbP3bgLTVodWU04XuIqZwiF/1hWm0wLMaNw79HpIuv1Y7/gd8FEXXL0biUiXevJFBn7AiGfR7oZmiFklbGE99upYrXh9TDm/POX195adKLqNt4W/FcLGSObO2VXL+WYSVecRbmKypWACqis/Tr3ciFuC0+PaybbqEeeOFtbyBsaaoTfpOYyGRW45vmXHubNMxw8OHOdD1YT/afKl0k/CVeTzEBhAOiQFuqfdS5HVyBURs7XGjO/cFxHwPgI70Hx33cIkcsAlgyzK0zlDyrTENi4q0mWfRxFlUjjEvvuHQoHF76fSGszUuLR1oEy6I3PBU4xv3jDV/DXMcqyiwGz0RZqD0FpI+dxLpd44jXdX8pfZw/hK2n9X/We1Tdkxfs207NG2qJXE28snDz7p+RWPk1Im8rbeWw0M+eUestWSOaduai8vvfJ7ww+nRvpEHKc7qRnlgA==
*/