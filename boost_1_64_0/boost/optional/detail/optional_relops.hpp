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
rADTYC04AtaD42FDuAM2godhM/gqbA8/gB3h17AT/B52hj/BivAKrAT/gLfAeD9r4bA47AcHwsFwDBwCF8N0uBJmwIfgcLgOjocH4ET4JpwE34FZKh1i/jmcAi/DqfA3eAcMCTHu4uFMeBO8E1aFs2EbeBfsAefBGXCBKj+4EK6Bi+AuuATuhner+OE98Bu4TMUH74WRoYzPYEG4AhYSfRn4kCpvuAa2h2tV/uEjcAJcB+fCR+EK+DB8EG6Er8Et8GO4HV6CO+Dv8HlYKox+AVaDe2EDuA+2hAdgN3gY9oKvwFtFnw6PKPmBR+HMMCPP88R+CTwB7xX9GngSboKn4PPwdbgvzMj1wTAj14fhG0pe4Fvwffipkgv4OQwPZ5wPa8HzsC78EnaGX8FbRN9H9OnwAhwJv4ZZ8Fs4HV6Ei+D3Kp3ifgPMgYfgv+FR+KMqPxgXSjpgEoyN4D0DLAtLwkawArwVVoeTYU04F6bCbbAWPAFrw69gHfgTrAutSMaTsAy8GTaATWAT2BS2hG3hYNgBToAd4d2wswofdoHPwq7wedgdvgh7wtOwF7wIB8Af4BDIJglrGKwI02FTOBK2g+Ngf5gJJ8KJcBGcDtfCmXAHnKXqDc6HZ+EC1T/BRSqfcDH8Fi5V5QdXqfKLRq5hPFwD28K1sBv8p4oXboIZ8HE4JlrLh+6XVR9x3yTTL78VZvrlAaiLPtmzi7sYNZ6ChdV4SdWTGieFmnnp8yoeNS6CA+EBOBoehNnwZbgGHoIb4IkwM454Ff1+1d/D1yzkV+UPnoERNv2/yhd8Q8UL34al4PuwCvwYdoCfq3jhl0pO4FdwOfwaroQ5cCP8Ee6EP8E98BI8oPpx+Ba0SNeH0A9LkvcQWA3GwlawMOwP4+FEmAAXwUS4BBaBy2BxuAqWguthWfgcLA9fgxVUPLBymOmfq8MCfuaisAisCYvB+rABbATbwcZwCGwC58GmYaa/bqbihS3gg7AdPAF7wCoh9PuwE+wFu8OJsA+cBIfCyXA2nAZXqv4ZroZzwkw/Ow8ehfPhZ3BBmOlnF8LQUOQSFob3wJpwWZjpXx+E4+BauFD1q3Ct6lfhLvgPeAj+E56Cm+Hn8AlVLnCrKhfk8SlYGj4DK8M9sJnqV2Fb+CLcAF+C2+BhVd6qP4UvhBl5O6j6U3gcorLPaHMj/5mo5JlG/m+xZF1d1vEtC38FzDrNqzAGvgbjRF9Y9GXgSVhf9O3gadhRybPMU0/Bnlpv4s1G3SfxbpB4Y1FZEu+EKLP+MBvWhvOiTLjzYX+4JMq0sweizHxmFZwO74EL4FJ4t5gvhffC1SpO+KiYO/P0wbNMOvZ5zNM/wp2y+xiGwi+jTLu/ABuq8RVsosZTsA3MgQPgv2EG/BOqMv4LToKR0WYeFgJXiP5+SF+m+4lf4Sax3yv2zjp52p0mnR9IOt3r5OXDzXyqDdTfiYBDYJdwk47uUOW1J9yh/MHnRf+O1pt4zqm4Zpt42sn86ybUW875xWhTLyWiTX4TYVfR94UpUKW1LBwl+vGwcrSph6qS757wAVgLPgHrwwOwATwDW8ALsKXkvxW8qvKn4idd3WCibcIpBtvBirA9rCbmNWAn2BR2VukVc0furWyTzz0ecj9c1hdG+k1/PxrWgGNgXSWnsB4cC1UdTPCbeeJEuEbs18LJcLfWm3hVnnIk3nMSbxLqI4n3O1lP+gHGKbcwQckTLK/G5fBm+AtsqeQGdoO/w1vhVXi7kjuoz4vGmXmCFWfmvTacCH1wFgyBy2AYXAXD4XYYC5/T/o2cRMD9SubgIRgVZ55b0fCMuDsLC8IPVXRxues4cXPlPZrHOk75SJPfSpEmv1U=
*/