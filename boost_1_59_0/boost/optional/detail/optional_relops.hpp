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
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
*/