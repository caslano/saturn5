/*
Copyright (c) 2016 Barrett Adair

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

HEADER GUARDS INTENTIONALLY OMITTED
DO NOT INCLUDE THIS HEADER DIRECTLY
*/

#define BOOST_CLBL_TRTS_NOEXCEPT_SPEC
#define BOOST_CLBL_TRTS_IS_NOEXCEPT std::false_type
#include <boost/callable_traits/detail/unguarded/function_ptr_varargs_3.hpp>
#undef BOOST_CLBL_TRTS_NOEXCEPT_SPEC
#undef BOOST_CLBL_TRTS_IS_NOEXCEPT

#ifdef BOOST_CLBL_TRTS_ENABLE_NOEXCEPT_TYPES
#define BOOST_CLBL_TRTS_NOEXCEPT_SPEC noexcept
#define BOOST_CLBL_TRTS_IS_NOEXCEPT std::true_type
#include <boost/callable_traits/detail/unguarded/function_ptr_varargs_3.hpp>
#undef BOOST_CLBL_TRTS_NOEXCEPT_SPEC
#undef BOOST_CLBL_TRTS_IS_NOEXCEPT
#endif // #ifdef BOOST_CLBL_TRTS_ENABLE_NOEXCEPT_TYPES
/* function_ptr_varargs_2.hpp
TcsbGlY01FZXBSvLK8vUrzUbx/G+ylNLKyvgfyXdlWUQVlnclqqa1ubWptramqrKCvinTP7bmQb/SvAn1cqyKqZp9f3wYFrjj+vk9bB8MTxmYUWFB2+lFacuLilZXLGkjKQ9pZBcvNjjWVR+StkikTl3THBbH2urnLfm337D2IYh8q/88G9A843/jeLRHEa3MTnkVyX4Fi1j7B+A6/HKeDjj3yGXU2PgOkzcRtiv8lI5gUN/tci392AfWcvYR7U=
*/