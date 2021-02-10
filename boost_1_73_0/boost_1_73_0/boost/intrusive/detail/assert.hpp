/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga  2006-2013
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTRUSIVE_DETAIL_ASSERT_HPP
#define BOOST_INTRUSIVE_DETAIL_ASSERT_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#pragma once
#endif

#if !defined(BOOST_INTRUSIVE_INVARIANT_ASSERT)
   #include <boost/assert.hpp>
   #define BOOST_INTRUSIVE_INVARIANT_ASSERT BOOST_ASSERT
#elif defined(BOOST_INTRUSIVE_INVARIANT_ASSERT_INCLUDE)
   #include BOOST_INTRUSIVE_INVARIANT_ASSERT_INCLUDE
#endif

#if !defined(BOOST_INTRUSIVE_SAFE_HOOK_DEFAULT_ASSERT)
   #include <boost/assert.hpp>
   #define BOOST_INTRUSIVE_SAFE_HOOK_DEFAULT_ASSERT BOOST_ASSERT
#elif defined(BOOST_INTRUSIVE_SAFE_HOOK_DEFAULT_ASSERT_INCLUDE)
   #include BOOST_INTRUSIVE_SAFE_HOOK_DEFAULT_ASSERT_INCLUDE
#endif

#if !defined(BOOST_INTRUSIVE_SAFE_HOOK_DESTRUCTOR_ASSERT)
   #include <boost/assert.hpp>
   #define BOOST_INTRUSIVE_SAFE_HOOK_DESTRUCTOR_ASSERT BOOST_ASSERT
#elif defined(BOOST_INTRUSIVE_SAFE_HOOK_DESTRUCTOR_ASSERT_INCLUDE)
   #include BOOST_INTRUSIVE_SAFE_HOOK_DESTRUCTOR_ASSERT_INCLUDE
#endif

#endif //BOOST_INTRUSIVE_DETAIL_ASSERT_HPP

/* assert.hpp
IImU5r/XKBCCvTsfu+P41GBm53123rFZL6bf45ssXabzlfMrXq6niROu1rM4dcI0Wa/idOGcxUl07Jyl2d9pHhNly81Bz293Os3Gh8Igr9dsXGXpn+hm9bH11B+OTkfjYd/tD7sD1/OCjtsPPM/tdAad0amXv9v1n1ufnK9O62adJa3jl3/b9zePd3mSzeunnu/3x3kWd+B7J27X98/cQW984vbyo72xHwRfvOC51WyMF7OtcLPxLUmvp0mzcfTyR5gfzJk/7mY0Shfz+HadTTcvrpLpap7PbbnBuMuiXVA++iiYTJwgul7fOq6z+fvHXbQIw8n21SS+DsNz/9/vePHZzwczounJH0+65NR5LJAY40TJYBadep51lj4snTC8utgfuggutTzICJ6ImhmMxwRI4DRWAp6O6CFN5pCrB+9DCdQIb949GFzWUygUc77N8jNKoukyIp9R5HiOwJ6PGA0mx3kJhBiTnoJ2hrHGcIV07KTzTD+EOAEqMwlTT6Y644AIOIkORXHebQNUukqlcu5dtsnFkPF5xoimJ39hI8cCiTFOlAxm0anjZxtzBE9EzYyeZ9AAEjiNlYCnItr8vW+BzSuoF5FoevIyLBgLJMY4UTKYRadevCKB70MJ1OqFa9Hr22U9hUIx59ss
*/