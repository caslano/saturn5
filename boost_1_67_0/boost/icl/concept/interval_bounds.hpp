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