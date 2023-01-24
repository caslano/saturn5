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
1g6CXJjJunEOKd6ls4XkXst60SonoOW97pr6KeC61IQrYGlB5ey8dRZxDxdOHVzAa7xNMTncVzIbJfk3JLO4vopgmEUM9QFFw777FGRR/JpNdHYmLc9OldpUlnIa7C+VA7541AyxTuvy3bmBOWt+1ObmMBCu4S72ti9gj176+qDyV2Sl8DQHDpJlBLhifOD6oMx0qq697c1gWdG74XW+DaO7h9aejB2tt8zXLecYY5Eua0AuD5V7q2DXicd5TDM7C5V/n+v4AiSXD2aoApaMYaZu/DGmtJ7s45YjPdVAuu0EpDwJnjSYKXssVjWnCnhYd+o1U0L2McGWsRm3fXfy0f/knA9B609BATFpLj7YSekONUBCwrnceFsdapeUlZStlbpi9Z+VccB+553UbG8OA8srOgtrY+zzmUMld1yJgrpolicMorXrNKc+rZ6sAIkeCuAgBm88Z3sNjNsrnEgJSTHA9C7f8YBXET8ov5NrJl+GeN7ZGvWAusoCXbs23u/iMmulsmDatQ8AR9mV4gChmoSefr5qlhtNRdiJMdx9vJ4aZTfo65xgFhFe7eQmnfwUmq/Ip7W2OyWdXNd6F2D7MulRGlUjGYOnp3f7ZsbVJMfpiRJMf93gX3dDPuedPGP8ONOiQzuOaKWwygcxPtLA7nqJTSV3USYhV33mp1oCwB0b5EmI8MD2Nyb1fQha6H1dk+H8Dw/BGKuF/2iq
*/