// Copyright (C) 2003, 2008 Fernando Luis Cacciola Carballal.
// Copyright (C) 2015 Andrzej Krzemienski.
//
// Use, modification, and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/optional for documentation.
//
// You are welcome to contact the author at:
//  akrzemi1@gmail.com

#ifndef BOOST_OPTIONAL_DETAIL_OPTIONAL_RELOPS_AJK_03OCT2015_HPP
#define BOOST_OPTIONAL_DETAIL_OPTIONAL_RELOPS_AJK_03OCT2015_HPP

namespace boost {

// optional's relational operators ( ==, !=, <, >, <=, >= ) have deep-semantics (compare values).
// WARNING: This is UNLIKE pointers. Use equal_pointees()/less_pointess() in generic code instead.


//
// optional<T> vs optional<T> cases
//

template<class T>
inline
bool operator == ( optional<T> const& x, optional<T> const& y )
{ return bool(x) && bool(y) ? *x == *y : bool(x) == bool(y); }

template<class T>
inline
bool operator < ( optional<T> const& x, optional<T> const& y )
{ return less_pointees(x,y); }

template<class T>
inline
bool operator != ( optional<T> const& x, optional<T> const& y )
{ return !( x == y ) ; }

template<class T>
inline
bool operator > ( optional<T> const& x, optional<T> const& y )
{ return y < x ; }

template<class T>
inline
bool operator <= ( optional<T> const& x, optional<T> const& y )
{ return !( y < x ) ; }

template<class T>
inline
bool operator >= ( optional<T> const& x, optional<T> const& y )
{ return !( x < y ) ; }


//
// optional<T> vs T cases
//
template<class T>
inline
bool operator == ( optional<T> const& x, T const& y )
{ return equal_pointees(x, optional<T>(y)); }

template<class T>
inline
bool operator < ( optional<T> const& x, T const& y )
{ return less_pointees(x, optional<T>(y)); }

template<class T>
inline
bool operator != ( optional<T> const& x, T const& y )
{ return !( x == y ) ; }

template<class T>
inline
bool operator > ( optional<T> const& x, T const& y )
{ return y < x ; }

template<class T>
inline
bool operator <= ( optional<T> const& x, T const& y )
{ return !( y < x ) ; }

template<class T>
inline
bool operator >= ( optional<T> const& x, T const& y )
{ return !( x < y ) ; }

//
// T vs optional<T> cases
//

template<class T>
inline
bool operator == ( T const& x, optional<T> const& y )
{ return equal_pointees( optional<T>(x), y ); }

template<class T>
inline
bool operator < ( T const& x, optional<T> const& y )
{ return less_pointees( optional<T>(x), y ); }

template<class T>
inline
bool operator != ( T const& x, optional<T> const& y )
{ return !( x == y ) ; }

template<class T>
inline
bool operator > ( T const& x, optional<T> const& y )
{ return y < x ; }

template<class T>
inline
bool operator <= ( T const& x, optional<T> const& y )
{ return !( y < x ) ; }

template<class T>
inline
bool operator >= ( T const& x, optional<T> const& y )
{ return !( x < y ) ; }


//
// optional<T> vs none cases
//

template<class T>
inline
bool operator == ( optional<T> const& x, none_t ) BOOST_NOEXCEPT
{ return !x; }

template<class T>
inline
bool operator < ( optional<T> const& x, none_t )
{ return less_pointees(x,optional<T>() ); }

template<class T>
inline
bool operator != ( optional<T> const& x, none_t ) BOOST_NOEXCEPT
{ return bool(x); }

template<class T>
inline
bool operator > ( optional<T> const& x, none_t y )
{ return y < x ; }

template<class T>
inline
bool operator <= ( optional<T> const& x, none_t y )
{ return !( y < x ) ; }

template<class T>
inline
bool operator >= ( optional<T> const& x, none_t y )
{ return !( x < y ) ; }

//
// none vs optional<T> cases
//

template<class T>
inline
bool operator == ( none_t , optional<T> const& y ) BOOST_NOEXCEPT
{ return !y; }

template<class T>
inline
bool operator < ( none_t , optional<T> const& y )
{ return less_pointees(optional<T>() ,y); }

template<class T>
inline
bool operator != ( none_t, optional<T> const& y ) BOOST_NOEXCEPT
{ return bool(y); }

template<class T>
inline
bool operator > ( none_t x, optional<T> const& y )
{ return y < x ; }

template<class T>
inline
bool operator <= ( none_t x, optional<T> const& y )
{ return !( y < x ) ; }

template<class T>
inline
bool operator >= ( none_t x, optional<T> const& y )
{ return !( x < y ) ; }

} // namespace boost

#endif // header guard


/* optional_relops.hpp
cC0WYoJmVNa/FG4ih3PM6hN4pun33uVwoK/jCnm7pp0Mb6FeXbYQA0RxjPJAviCltTAjKsMQvLXRRHnPkMBIWaXZ2yvAWhDqsOUBuafh8kqniyBW04gvRzQLyQrf8+fLnDk/8+8Yph/Sok/Q06vRrK/zFKwznpOZaXEpYDqWz4yYb2RT7rWNyyiKigTWf4wsFRbQvqNizENcnxITbu2ib3lKUgAF6m3TEEHnwEiIEEToS7UIOWUbaDRCjfK7ad884ZPaEv1Kr22391HHXNeAKeoONX0/ge71xUVz+YteJGv6XnxdQxk5feOHxr1yQ/YSFFDgXl3rQVT7NmQ4SgTNdbgt8VUKcVWcM+RRhb5Wc1xZmTkqT3Lu3HAc01I4kws3iDD/qhluaTzD49hmsFS4PGLdK99n0hnK/SyTram3oRix0PVCzqI0rlRXisuwPRi67X7fvWz9pdd3T1vnzQw5Ng65/80kWqFMOxp+XLuCcYN2Wv1Mt1z4f6i6BUmhAfN9GqtohTPtaWQH7TPe+gYLNNE44byQ/pS2Ybq+D8JwZbeZxqFgvjFbpz6al2eitdAkXaFxxKa8QhxoLO4NfBKU2UXeQXpTMddZCcCuN7LcGZyd1RXaKW2sOPqiDHbs/Y+UIrvNTWouqx4LqQLV
*/