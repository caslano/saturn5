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
M56Hfzob+STSYT6kpSaemm0doV/d7nJqiWXewEt0gUctvd8j/GH6YX1L1BYzLYnMsxwkZ7FKkiyARg9LlFBu9kxuNg8/G9NhVJcbGM88hsI/GAcUT+pfphRpAxtxS/q92+32h5bTA0TbDlOFL58DcSzaxAAczq5ni7Ia0cyKUrQaGWNunyOGTk3fkuFL5xseYRFI+pFLdhp6Ho2Ygfpc/M02bsKT2OaYlssDSppD34peNK6RB+l427+RKfeNhg6QhgnySQpETE0xavzsk4KZG01FREg6uS3tZVL197aZkko6VP86dFjR5MdfDE4SRPk1xU+Pl61j+fzNJ31Y8GTnGnW9O8GErbeA4I5/qYFK6fFZXFtv0e2G/LIQS67IdFaL24VRrSV6sKYM+v6NKiDS/1tD3RLUrSxBq1R0GdhQ1qe7PPslrD6G0blsWc0FWlt1uzHMbL6H8ueJ34nuVzu3yDxQYIHKKvOlY4WQ8ZnaSrNE4+gDrBjwPLvMTnVPffgGYpTNPlQAjARPvLmwN+FP+z11pphIyb/6LUA+95YnPwxKAnKXQYmX8uRS5O9a0nU7RC+xsR+/fjvlB67izxxxfTMuXtVm8K9DH0upMYGqMz9Z3a0RfefotQnrt22RHq3TDWoULrYxYgiDJgh+Xv0K/PTMKNejW7qenghMpyBVa+WjbjYfIR9jKX9D+GkcIoL5fB5xEysJqWnwUzHn
*/