
// (C) Copyright Tobias Schwinger
//
// Use modification and distribution are subject to the boost Software License,
// Version 1.0. (See http://www.boost.org/LICENSE_1_0.txt).

//------------------------------------------------------------------------------

// no include guards, this file is intended for multiple inclusion

#undef BOOST_FT_type_mask
#undef BOOST_FT_kind_mask
#undef BOOST_FT_callable_builtin
#undef BOOST_FT_non_member
#undef BOOST_FT_function
#undef BOOST_FT_pointer
#undef BOOST_FT_reference
#undef BOOST_FT_non_member_callable_builtin
#undef BOOST_FT_member_pointer
#undef BOOST_FT_member_function_pointer
#undef BOOST_FT_member_object_pointer
#undef BOOST_FT_member_object_pointer_flags

#undef BOOST_FT_variadic
#undef BOOST_FT_non_variadic
#undef BOOST_FT_variadic_mask

#undef BOOST_FT_const
#undef BOOST_FT_volatile

#undef BOOST_FT_default_cc
#undef BOOST_FT_cc_mask

#undef BOOST_FT_flags_mask
#undef BOOST_FT_full_mask

#undef BOOST_FT_arity_mask


/* undef.hpp
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
*/