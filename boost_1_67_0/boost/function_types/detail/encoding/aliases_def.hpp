
// (C) Copyright Tobias Schwinger
//
// Use modification and distribution are subject to the boost Software License,
// Version 1.0. (See http://www.boost.org/LICENSE_1_0.txt).

//------------------------------------------------------------------------------

// no include guards, this file is intended for multiple inclusions

#define callable_builtin BOOST_FT_callable_builtin
#define member           BOOST_FT_member_pointer
#define non_member       BOOST_FT_non_member
#define variadic         BOOST_FT_variadic
#define non_variadic     BOOST_FT_non_variadic


/* aliases_def.hpp
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
*/