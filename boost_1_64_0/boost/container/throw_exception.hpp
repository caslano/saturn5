//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2012-2013. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONTAINER_THROW_EXCEPTION_HPP
#define BOOST_CONTAINER_THROW_EXCEPTION_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/container/detail/config_begin.hpp>
#include <boost/container/detail/workaround.hpp>

#ifndef BOOST_NO_EXCEPTIONS
   #include <stdexcept> //for std exception types
   #include <string>    //for implicit std::string conversion
   #include <new>       //for std::bad_alloc
#else
   #include <boost/assert.hpp>
   #include <cstdlib>   //for std::abort
#endif

namespace boost {
namespace container {

#if defined(BOOST_CONTAINER_USER_DEFINED_THROW_CALLBACKS)
   //The user must provide definitions for the following functions

   void throw_bad_alloc();

   void throw_out_of_range(const char* str);

   void throw_length_error(const char* str);

   void throw_logic_error(const char* str);

   void throw_runtime_error(const char* str);

#elif defined(BOOST_NO_EXCEPTIONS)

   BOOST_NORETURN inline void throw_bad_alloc()
   {
      const char msg[] = "boost::container bad_alloc thrown";
      (void)msg;
      BOOST_ASSERT(!msg);
      std::abort();
   }

   BOOST_NORETURN inline void throw_out_of_range(const char* str)
   {
      const char msg[] = "boost::container out_of_range thrown";
      (void)msg; (void)str;
      BOOST_ASSERT_MSG(!msg, str);
      std::abort();
   }

   BOOST_NORETURN inline void throw_length_error(const char* str)
   {
      const char msg[] = "boost::container length_error thrown";
      (void)msg; (void)str;
      BOOST_ASSERT_MSG(!msg, str);
      std::abort();
   }

   BOOST_NORETURN inline void throw_logic_error(const char* str)
   {
      const char msg[] = "boost::container logic_error thrown";
      (void)msg; (void)str;
      BOOST_ASSERT_MSG(!msg, str);
      std::abort();
   }

   BOOST_NORETURN inline void throw_runtime_error(const char* str)
   {
      const char msg[] = "boost::container runtime_error thrown";
      (void)msg; (void)str;
      BOOST_ASSERT_MSG(!msg, str);
      std::abort();
   }

#else //defined(BOOST_NO_EXCEPTIONS)

   //! Exception callback called by Boost.Container when fails to allocate the requested storage space.
   //! <ul>
   //! <li>If BOOST_NO_EXCEPTIONS is NOT defined <code>std::bad_alloc()</code> is thrown.</li>
   //!
   //! <li>If BOOST_NO_EXCEPTIONS is defined and BOOST_CONTAINER_USER_DEFINED_THROW_CALLBACKS
   //!   is NOT defined <code>BOOST_ASSERT(!"boost::container bad_alloc thrown")</code> is called
   //!   and <code>std::abort()</code> if the former returns.</li>
   //!
   //! <li>If BOOST_NO_EXCEPTIONS and BOOST_CONTAINER_USER_DEFINED_THROW_CALLBACKS are defined
   //!   the user must provide an implementation and the function should not return.</li>
   //! </ul>
   BOOST_NORETURN inline void throw_bad_alloc()
   {
      throw std::bad_alloc();
   }

   //! Exception callback called by Boost.Container to signal arguments out of range.
   //! <ul>
   //! <li>If BOOST_NO_EXCEPTIONS is NOT defined <code>std::out_of_range(str)</code> is thrown.</li>
   //!
   //! <li>If BOOST_NO_EXCEPTIONS is defined and BOOST_CONTAINER_USER_DEFINED_THROW_CALLBACKS
   //!   is NOT defined <code>BOOST_ASSERT_MSG(!"boost::container out_of_range thrown", str)</code> is called
   //!   and <code>std::abort()</code> if the former returns.</li>
   //!
   //! <li>If BOOST_NO_EXCEPTIONS and BOOST_CONTAINER_USER_DEFINED_THROW_CALLBACKS are defined
   //!   the user must provide an implementation and the function should not return.</li>
   //! </ul>
   BOOST_NORETURN inline void throw_out_of_range(const char* str)
   {
      throw std::out_of_range(str);
   }

   //! Exception callback called by Boost.Container to signal errors resizing.
   //! <ul>
   //! <li>If BOOST_NO_EXCEPTIONS is NOT defined <code>std::length_error(str)</code> is thrown.</li>
   //!
   //! <li>If BOOST_NO_EXCEPTIONS is defined and BOOST_CONTAINER_USER_DEFINED_THROW_CALLBACKS
   //!   is NOT defined <code>BOOST_ASSERT_MSG(!"boost::container length_error thrown", str)</code> is called
   //!   and <code>std::abort()</code> if the former returns.</li>
   //!
   //! <li>If BOOST_NO_EXCEPTIONS and BOOST_CONTAINER_USER_DEFINED_THROW_CALLBACKS are defined
   //!   the user must provide an implementation and the function should not return.</li>
   //! </ul>
   BOOST_NORETURN inline void throw_length_error(const char* str)
   {
      throw std::length_error(str);
   }

   //! Exception callback called by Boost.Container  to report errors in the internal logical
   //! of the program, such as violation of logical preconditions or class invariants.
   //! <ul>
   //! <li>If BOOST_NO_EXCEPTIONS is NOT defined <code>std::logic_error(str)</code> is thrown.</li>
   //!
   //! <li>If BOOST_NO_EXCEPTIONS is defined and BOOST_CONTAINER_USER_DEFINED_THROW_CALLBACKS
   //!   is NOT defined <code>BOOST_ASSERT_MSG(!"boost::container logic_error thrown", str)</code> is called
   //!   and <code>std::abort()</code> if the former returns.</li>
   //!
   //! <li>If BOOST_NO_EXCEPTIONS and BOOST_CONTAINER_USER_DEFINED_THROW_CALLBACKS are defined
   //!   the user must provide an implementation and the function should not return.</li>
   //! </ul>
   BOOST_NORETURN inline void throw_logic_error(const char* str)
   {
      throw std::logic_error(str);
   }

   //! Exception callback called by Boost.Container  to report errors that can only be detected during runtime.
   //! <ul>
   //! <li>If BOOST_NO_EXCEPTIONS is NOT defined <code>std::runtime_error(str)</code> is thrown.</li>
   //!
   //! <li>If BOOST_NO_EXCEPTIONS is defined and BOOST_CONTAINER_USER_DEFINED_THROW_CALLBACKS
   //!   is NOT defined <code>BOOST_ASSERT_MSG(!"boost::container runtime_error thrown", str)</code> is called
   //!   and <code>std::abort()</code> if the former returns.</li>
   //!
   //! <li>If BOOST_NO_EXCEPTIONS and BOOST_CONTAINER_USER_DEFINED_THROW_CALLBACKS are defined
   //!   the user must provide an implementation and the function should not return.</li>
   //! </ul>
   BOOST_NORETURN inline void throw_runtime_error(const char* str)
   {
      throw std::runtime_error(str);
   }

#endif

}}  //namespace boost { namespace container {

#include <boost/container/detail/config_end.hpp>

#endif //#ifndef BOOST_CONTAINER_THROW_EXCEPTION_HPP

/* throw_exception.hpp
0OKY5e/TJi+ZC42v+9sHK5uQudH4nKV/97OazNOF1sj0f2t1+rf2oveu/vYuofxoMoPCKuj3ifUzKSwud8xh0TsavQcUhyAo8GJZWzI7WgSzoqdhApkDrZzXSuD/LlY49oNYW7R8zHSt6/5K9hqN3gPQIG1h0jdk7xVWdczPfcjADBDC7D+NJlckC0MLZfahwLcpZGq03MxOnN6sJotW5Pyx/cRiZHq0PKyH7OVD/yFLVOScun+qmM8kRS2ju2hG0fcjjWg01yUhCLL7NBdmRTPBp2v9Uvh6ulrCMTI3qxMNCjlOdSB7wHKiQe8ip3Rk+m4A5Zl1M5+vI66z0CjuM3xd07XzLTIbWlmvlcbXct335iY7wexzfJ3XccAiMugOYPH2EI+vF240TyfLQqO1RYNutW0dyGYo7Gb5Kd1FLd19xxIajKo99yWZHS2Rmb5DgqglB62A18oA5u811k72BI3OPzToUjv1BzIPWhkWV+9M3myyUj1811ll8fVFlYZizuLRqBY0KL8iX1UyMxrNWQK+7r1bYgFZNjOMh+Ab/4STudAM3vu/cgCQ56dNhclq9BI9oOH4axY2IjOi5WY2YV+pvmQpaPScFg3q38pbhiwDLYxZzZ+f7yQbihbKcpqLxvQhs6JFsLh9l+d/T2ZDy89sQqfSYq7taHbv8VIeX/Mu3nebzNzbd8yjwcYuRduJOtFCmfXJPTCVzIJG+zUaRBoPPha1oNHx+YXi+Izu4xsPDc5OHCbWT6+wFEO/kmLd0WifQAP7rhaVyJLRyjILfflSJ+pE03vX1gAAx7rVvU/myhDrgIa9fxdfi8yNlpfZwakD7pF50MKZrTzQJ4EM+vpb4fJPxHgRaHT+ocEE19NIMnVfdBb3b707+8j0aInMkpI7ibk2o7m8c10BX1fsL/KLsH6+YwINKl5MW0tmQQtn9uHwnGNkVrQYZslP/6xAZlfETS7UsgyZQzGe09n0A5kTrRyzTnUainWHrwDc3h4q4usP0yffIVP3960RGiw6+Xc3slg0Ol7QYE8nzWqyeLS8LO7Ijh8fkiWjaZgd/WZrPTITGq1RJXyN3FVqDVkbNDrfk/C15o2gy2TpaKHMDm5avYAsg42HBvrffmhPZkUry6zH98nPyXajRTB7tHhhCNkJxXjaQWvPk7nQ6PqzMr6+yj8yjewBWhizix9cLcheo8Uym1DvzmIy/QCAOGZ5atWZSpaCFs3sxaZ36aJ3tMLMFv+rTybLQuO1FD78eD6ZHc3qPSaq4GvIjdRlZMaB4nxAwzybbQ6yTLQwZpX6DG5GNhGN1g8NtJOS8pHNQAtltquMLpEsm41XFV9rtIiNIHMxw8bgdPQL7/vKEAgb5LNqYIHSzS3e+/7qYESL9f57kurwDRQYd2YoWQaLQ4PGY8eEkdnRwpl1nGx9ROZAK8jsim1OCNkJtKLMMkfsEOM9QaNjHg1CnCNUZB60UGbXf04PJnuNpmU5g5oNWUkWbQGIZNa3Q/lDZAa0MGYNWrV9SWZEi2AWtXXEZTITGq8lbjgMIUtDC2Z2t37mfjKzImf427NuMosi56o2q2aRZaKFMKv25q8mZFZFDwvP6YqR2dA0zEypc8PJ1inGizBFePeJ7uBAo3X/EnrB5W19L3yyrvAAzRTy6XipAQANm5Y6SJYynOb6k83PuyWSzIwWzqzkbv1vZBa0CGbTt75cSmZFy8MsJ/poHTIbWn5m6dd0/5LZFbW0vDH+HdluxXgXg/5zkewEmprZljVVKpK50fIxi/5m4gwyj6KWqrZvq5BBpr8536buIFOjFWJ23dbiDZkBLYpZ0IuoXWKu0XgtWlOe9mRpirglSz39ySyKuKs=
*/