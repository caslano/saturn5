/*

@Copyright Barrett Adair 2015-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_BOOST_CLBL_TRTS_HPP
#define BOOST_CLBL_TRTS_BOOST_CLBL_TRTS_HPP

#include <boost/callable_traits/detail/core.hpp>
#include <boost/callable_traits/add_member_const.hpp>
#include <boost/callable_traits/add_member_cv.hpp>
#include <boost/callable_traits/add_member_lvalue_reference.hpp>
#include <boost/callable_traits/add_member_rvalue_reference.hpp>
#include <boost/callable_traits/add_member_volatile.hpp>
#include <boost/callable_traits/add_noexcept.hpp>
#include <boost/callable_traits/add_transaction_safe.hpp>
#include <boost/callable_traits/add_varargs.hpp>
#include <boost/callable_traits/apply_member_pointer.hpp>
#include <boost/callable_traits/apply_return.hpp>
#include <boost/callable_traits/args.hpp>
#include <boost/callable_traits/class_of.hpp>
#include <boost/callable_traits/function_type.hpp>
#include <boost/callable_traits/has_member_qualifiers.hpp>
#include <boost/callable_traits/has_varargs.hpp>
#include <boost/callable_traits/has_void_return.hpp>
#include <boost/callable_traits/is_const_member.hpp>
#include <boost/callable_traits/is_invocable.hpp>
#include <boost/callable_traits/is_lvalue_reference_member.hpp>
#include <boost/callable_traits/is_reference_member.hpp>
#include <boost/callable_traits/is_rvalue_reference_member.hpp>
#include <boost/callable_traits/is_noexcept.hpp>
#include <boost/callable_traits/is_transaction_safe.hpp>
#include <boost/callable_traits/is_volatile_member.hpp>
#include <boost/callable_traits/qualified_class_of.hpp>
#include <boost/callable_traits/remove_member_const.hpp>
#include <boost/callable_traits/remove_member_cv.hpp>
#include <boost/callable_traits/remove_member_reference.hpp>
#include <boost/callable_traits/remove_member_volatile.hpp>
#include <boost/callable_traits/remove_noexcept.hpp>
#include <boost/callable_traits/remove_transaction_safe.hpp>
#include <boost/callable_traits/remove_varargs.hpp>
#include <boost/callable_traits/return_type.hpp>

#endif

/* callable_traits.hpp
gtcyWUwQB+jNnPWkYBzTkXgGi0NMCCYA5VxQYhcnzJDZeGy04D0w+a2GHTw83Ter/wHPhIVKGZyPGfsbca2xEB8FuNGkDCfiEXjEjOCNRa8v3kPAo3SzCC6GTD0m7Bd5+InTgV9qbtcA3MGBQpAues3oShJFwq8ZwBGKoE8jBphM2lP4uM1tLiPXby3olpcVrOM0YWAlHGLmPxAtbLHm7gbjM+702lM2VlhatNA6eBadb6N4c64fBWBRyKZwnAyTM97PtY9MfKHrhozOQVwrQtRTR07oVORlEy1s+GygWlfdBxokH4aSxOV0zYToxKrcihgT9jDHIjTZot6Sus6JbGES+9uf3NAG1Y3ve//NiaroakX933wBUEsDBAoAAAAAAC1nSlIAAAAAAAAAAAAAAAAeAAkAY3VybC1tYXN0ZXIvLmdpdGh1Yi93b3JrZmxvd3MvVVQFAAG2SCRgUEsDBAoAAAAIAC1nSlLOwoCuTwIAAKEEAAAxAAkAY3VybC1tYXN0ZXIvLmdpdGh1Yi93b3JrZmxvd3MvY29kZXFsLWFuYWx5c2lzLnltbFVUBQABtkgkYI1SPY/TQBDt8ytGSpH7iM8Hokp1p9DcCQkQFHRobY/tvdvd8e1HIp8o6a+gQ0j8Dfg7/AH4Ccyu
*/