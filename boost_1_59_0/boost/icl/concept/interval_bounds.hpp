/*-----------------------------------------------------------------------------+
Copyright (c) 2010-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_CONCEPT_INTERVAL_BOUNDS_HPP_JOFA_100927
#define BOOST_ICL_CONCEPT_INTERVAL_BOUNDS_HPP_JOFA_100927

#include <boost/icl/interval_bounds.hpp>
#include <boost/icl/type_traits/is_discrete.hpp>
#include <boost/icl/type_traits/is_numeric.hpp>

namespace boost{namespace icl
{

inline interval_bounds left(interval_bounds x1)
{ return interval_bounds(x1._bits & interval_bounds::_left); }

inline interval_bounds right(interval_bounds x1)
{ return interval_bounds(x1._bits & interval_bounds::_right); }

inline interval_bounds all(interval_bounds x1)
{ return interval_bounds(x1._bits & interval_bounds::_all); }

inline bool operator == (const interval_bounds x1, const interval_bounds x2)
{ return x1._bits == x2._bits; }

inline bool operator != (const interval_bounds x1, const interval_bounds x2)
{ return x1._bits != x2._bits; }

inline interval_bounds operator & (interval_bounds x1, interval_bounds x2)
{ return interval_bounds(x1._bits & x2._bits); }

inline interval_bounds operator | (interval_bounds x1, interval_bounds x2)
{ return interval_bounds(x1._bits | x2._bits); }

// left shift (multiplies by 2^shift)
inline interval_bounds operator << (interval_bounds bounds, unsigned int shift)
{ return interval_bounds(bounds._bits << shift); }

// right shift (divides by 2^shift)
inline interval_bounds operator >> (interval_bounds bounds, unsigned int shift)
{ return interval_bounds(bounds._bits >> shift); }

inline interval_bounds operator ~ (interval_bounds x1)
{ return all(interval_bounds(~(x1._bits))); }

inline interval_bounds outer_bounds(interval_bounds x1, interval_bounds x2)
{ return left(x1) | right(x2); }

inline interval_bounds inner_bounds(interval_bounds x1, interval_bounds x2)
{ return interval_bounds(x1.reverse_right() | x2.reverse_left()); }

inline interval_bounds left_bounds(interval_bounds x1, interval_bounds x2)
{ return left(x1) | (left(x2) >> 1); }

inline interval_bounds right_bounds(interval_bounds x1, interval_bounds x2)
{ return (right(x1) <<1 ) | right(x2); }

inline interval_bounds left_subtract_bounds(interval_bounds x1, interval_bounds x2)
{ return right(x1) | ~(right(x2) << 1); }

inline interval_bounds right_subtract_bounds(interval_bounds x1, interval_bounds x2)
{ return left(x1) | ~(left(x2) >> 1); }

inline bool is_complementary(interval_bounds x1)
{ return x1 == interval_bounds::right_open() || x1 == interval_bounds::left_open(); }

inline bool is_left_closed(interval_bounds bounds)
{ return bounds.left().bits()==2; }

inline bool is_right_closed(interval_bounds bounds)
{ return bounds.right().bits()==1; }

inline std::string left_bracket(interval_bounds bounds)
{ return is_left_closed(bounds) ? "[" : "("; }

inline std::string right_bracket(interval_bounds bounds)
{ return is_right_closed(bounds) ? "]" : ")"; }

template <class Type>
inline typename enable_if<is_discrete<Type>, Type>::type
shift_lower(interval_bounds decl, interval_bounds repr, const Type& low)
{
    if(is_left_closed(decl) && !is_left_closed(repr))
        return icl::pred(low);
    else if(!is_left_closed(decl) && is_left_closed(repr)) 
        return icl::succ(low);
    else 
        return low;
}

template <class Type>
inline typename enable_if<is_discrete<Type>, Type>::type
shift_upper(interval_bounds decl, interval_bounds repr, const Type& up)
{
    if(!is_right_closed(decl) && is_right_closed(repr))
        return icl::pred(up);
    else if(is_right_closed(decl) && !is_right_closed(repr)) 
        return icl::succ(up);
    else 
        return up;
}

template<class CharType, class CharTraits>
std::basic_ostream<CharType, CharTraits>& operator <<
  (std::basic_ostream<CharType, CharTraits> &stream, 
   interval_bounds const& object)
{
    return stream << left_bracket(object) << right_bracket(object);
}



template<class IntervalT>
inline typename 
boost::enable_if<has_dynamic_bounds<IntervalT>, interval_bounds>::type
outer_bounds(const IntervalT& x1, const IntervalT& x2)
{ return outer_bounds(x1.bounds(), x2.bounds()); }

template<class IntervalT>
inline typename 
boost::enable_if<has_dynamic_bounds<IntervalT>, interval_bounds>::type
inner_bounds(const IntervalT& x1, const IntervalT& x2)
{ return inner_bounds(x1.bounds(), x2.bounds()); }

template<class IntervalT>
inline typename 
boost::enable_if<has_dynamic_bounds<IntervalT>, interval_bounds>::type
left_bounds(const IntervalT& x1, const IntervalT& x2)
{ return left_bounds(x1.bounds(), x2.bounds()); }

template<class IntervalT>
inline typename 
boost::enable_if<has_dynamic_bounds<IntervalT>, interval_bounds>::type
right_bounds(const IntervalT& x1, const IntervalT& x2)
{ return right_bounds(x1.bounds(), x2.bounds()); }

template<class IntervalT>
inline typename 
boost::enable_if<has_dynamic_bounds<IntervalT>, interval_bounds>::type
left_subtract_bounds(const IntervalT& x1, const IntervalT& x2)
{ return left_subtract_bounds(x1.bounds(), x2.bounds()); }

template<class IntervalT>
inline typename 
boost::enable_if<has_dynamic_bounds<IntervalT>, interval_bounds>::type
right_subtract_bounds(const IntervalT& x1, const IntervalT& x2)
{ return right_subtract_bounds(x1.bounds(), x2.bounds()); }


}} // namespace icl boost

#endif


/* interval_bounds.hpp
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
*/