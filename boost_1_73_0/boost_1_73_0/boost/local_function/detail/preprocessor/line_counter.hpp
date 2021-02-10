
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

#ifndef BOOST_LOCAL_FUNCTION_DETAIL_PP_LINE_COUNTER_HPP_
#define BOOST_LOCAL_FUNCTION_DETAIL_PP_LINE_COUNTER_HPP_

#include <boost/config.hpp>

// PUBLIC //

// MSVC has problems expanding __LINE__ so use (the non standard) __COUNTER__.
#ifdef BOOST_MSVC
#   define BOOST_LOCAL_FUNCTION_DETAIL_PP_LINE_COUNTER __COUNTER__
#else
#   define BOOST_LOCAL_FUNCTION_DETAIL_PP_LINE_COUNTER __LINE__
#endif

#endif // #include guard


/* line_counter.hpp
+OZte9jttS+6tcpPQuhRX3vu5Fr6jdmbyk/SBwYgkNBP0AiFpnHiQGtqmnuaeDPphQf7S895Ovb0GnkUJ7TyDmC5/jSgd+nQhRYT35pz3+JzJ4hvXV9RSb9B3r8rNp7LuSMni2t4Kppb4quUIQsYCNx5ezhKEYJ1WJk2suAUNGN79M68aP+Gj5ic6SMB/5t4kycd9RqaZ8POuwHNeaoenKgHKRjVyJjXhGHgv8+o2cWoJo6OdA9aLOnFcm3X3RrOzbZ8PwCJBsmEIVkD4UShxw2oKpwhAiI01y20Am6CTjC9qW9MAfpeDfX5lvAC/5qh4poAYO/Wuo9zWggHkB4MvaGZzjSP/3J6eWmaxLjZrXgt9msElB6I/cYu6MM4G7emsC3DZ7dWio4vb0BgS7BZRabAvFPbTzzg3BULtlUYNoyCJEjuQwW4uNhXvbPRqDscDStxYiWuLYZteHL2v107gCGSaOHbViJNJ7qHS8MGbZgIe2ZFYiu0klm98qCFU3/cK3b/Ic0kAxkGce1QLyPpiFIU5jEIDKh2g0fdUsDA4CUA0KmLPE5IVBOJ+ghirp+IqWddEwZMkbKxI4mwTHdqgiqVEVg7lF6TuZLGWYfVk+iyllQ/NpkfmSbyxka65sJQs3ak7VmRhSY7Rqvq
*/