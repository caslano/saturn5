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
TOACHcrlhDxDPvHKOaz9JXm4r0We8Po45nlMkIWXxzcGfPI184beqmifsGCre8FWRduidGhbaC/Ig/aCbYo8cpseE3iwlvW8zYY6lik4mPT9AaxnXe+9HZmbuwWZD79TMjdnOgSZI3dK5my1KKwdLj6+sbqc9r7pUccrL+Vdzphgg3he4T3L+aPwLqeMz3Is/rEAp8uQgF8X4LSxFvtB+Nwm7AfhU5vzYX/u8NTcpAtvdMo1n+iYcfoKSCM+kZHeQZZTn8iE71nK7nMW8a1KWX6qgmPhjQEvHvgzn5Sv6xsI36qU05+qYP5Xyvwwnywo18wTwVuVcl1PVYz8F8jpeO4Q3qqU63qqYvTysiCd/FQF3qlI/JH/Pimx76t9/ppOH31G/Qm1T6B98Zkk4z7JPQemnaFojfgO5rIpvoPLvLUlvg2YE+MiE91/nGHSPZ9x9g0Y+s3rNF1tm0tl9x4z0YPYtF+w/OYOO8YXJkyOL4xYGF+YMTm+MGFhfGGgB/GFAQviCwMmxRcmzHt4EeqeY++GvhejYPCtIMbOE+sfAYwdJMqWvkQ6fsky/ZZ8ZXKfhWifJ9oKoN1OtEXkrHon0Bav17SnAG0J0x4AtLPXY9o65+w4VKf6RXGlxRhML2l8HWBl5mbGJZkvFefZdVR+NRZQQj1+0GAwQVGW0bbXr+dv4+RLjq9sA9H5PIPOkot5XM+fazHVkmRzeT7jtzb0kNMxbz3cJWNim02P5yEswpbh/nHZssxansXvM7QjZiIB2XH3c8sxfxUVcHaqwKM61jODcrx78p1u/iV8v/abMwT5vG84v8E2jSn0CflwfXetuN98A8XT43zVFQsrgPKvHodNVSvS2u1NYt5d0PbU7EUVjZiGguqoF6PgV+scG2laCXQqZUwkv95UuVAxWHdoV2Ytdr62ZQOQVQZ3Gx6IPFw6ZRU4B1wQyjHfbO8jTI0p19yFvJY8Buxk2lVAO0C0brLvwSaiNT4u5OdFP8l1jr5RX5RgdLpofNb2XoO2zz10Q1d9gn54396BwR3cT8x58nqbfqKgD7VI0Bz2gYuBRxkUro+2A8Zp9YQXh12CM2m5LCU+NoRxwcgL9uJ5ktG799DQvj18xhb3awrxRJ4v88bJ2Aiew1kZRShvJNcXyxB8u2ZS2wfrAe5pLXHyjaqjVUqtftl35mW3/NOF6VhJ+uPdYIOnER/3Xyqimie0mS6H8nFetOmxOr5U0rEd+0xZI4nPu28/i2MwnlfCmTeXkVVF6w3A7MBLaeRxXd3hS8NIotXbUcT00tgoDmzR42PzsZyGbx75uKujvNXBWCbfLXqMi9NooeaqGeAJx2JjV/CWetWp2qZUC6hZDtM/Xm5TGpEszxNFHhUprU4fih176BKfNPZ8a3XNuIusCL7L12i+46Oiv+G7Tr4bIV/OrlKYKEa0So87Sa6kNiBVx6f6EIEX+VoW4iuWD6sNwAI8HM024vFH5tk73LMg3lcLp+/pLITTZZIF66G+pVBLJ2oNHe+iIspLvtcyXqxEzhrwye5YO1OYs3cIniKu4ZqgDBKeqLwmH6sd6i3zkepr8vTVw0Pf3avBQ81Qmyduio0L8mBTkH+jDl51eZITmDF4Fa8/iTGbG6svziX0Rxo6JZ/xn8RxoMvOVyrQoPp+OnwvzefRw5zyV7r9L5DBc2/D6ye65CSNJX8Xyo5zLeid58LWgAf0DYzmTRT0B28+sN/6Ah5/7kG+pzt8JIcG1tK8ZZX4wjnP6v8ZwCd9v/GZiPPcLOcRzr+yjPQ5XKoP3g2nk05WtzIEbQawt5HwbHwuC2V+tm0zvh6i1ko8hoHP8rnOHq53V3/PIF0EG9jXv5vkRoU=
*/