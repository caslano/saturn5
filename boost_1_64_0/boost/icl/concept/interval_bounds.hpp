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
qkp1jmZRxQnNWYU659m1di1Z62+L0ewxSXRjXCc6VG8jq32zGFs7N42SK35DO8u+LjZOvMJyar8qXH7cnVWbahJe+mwHW/OVnUZWb0CHukRTjT61qMZqk/DO+8tpeJ0caj+sDetTKkaYdmsrO/WkHK081ZpNn76FJaRl0bBicXTtzGH26dp9QtulR1npO8fovQmv0JCMu7Rtyc/0Qk5NOt9nKY2/coK+q76HrlZbyHJeKMrulmnCngspRtN/bihWq3WfbTw2VgzLW0CbUcbAoO8pJonEPdPO05/W7qF5XTdRubz64tCivejcsdtYF+vp52mXhZUzjtDhRy4xacJnVD6oqdi+zBy2LO4bOtasL2XlXBDTz+5hPZ6UFf7Q9RSrVHqwMGv1MLbhkyn0uFkLunbtiPhBh6X0/O1IYennddnRsH6CYf0DVj6tqpBY2chiKpyh+TNHsVNHrwtX9jDKazWPvg/8A71YcZ4QK5ynvlPDxYS2b7C5se9Q7fRb9NXVJuQqr2ObXi7ONk5IoLrrLgm102Pp5IqpdL/BUjIsGCa+2XAO/flWrHj8taLUoFNdYfLxD6j/2v6s6q4lrOmVaWL6J33pl/x1wusfjaL7j0vQjcof0fSXJ1NYjfoUUXMRG2OpR5e+6EGzX1hDDSeFsIalK7Ef2GJhWZaJ2TdUZhmnMqnFN5MotdRRtmjhXHaz6DIyLg6i5zL74ObWdGqfVZs9XryeDF13sHpd5grLku9TzEWz8Lvqt6n3uSrUy5rHHq4eQ5/lP6CAedfF3iUnU5fWpYQNQStZ7+lTWOiakmzWj/3YusvH2d7XVrFbx59njQcsEYNWJrH3al+hTg3TWLXm9cUbqQNY/dHvCJGOFyhnahgtnlqVLh8YLNaZXA/jO1as+/0Ullskm9UoPYYWDesuJL26n739xSlxRbkk9ompEtXKiaQ+jV8WSgUEUkz8n4RDP71HpcJnCee+SSLXd8toVMpE6njjmnD+u+LswHejhYHH2pB9WpIw6N4e1rRkPWFC5mYaaC8rmBvvZeP3NhJ7s9OsWbdybHwDM7tT4c+0/PtAskTcoN6Ru1jGnw8K68vqybyrF0vpuYfqf3pHqLN9DNVZXIkdeHEblRy7Uni09FOmmxROFYbYWLu8y0LM13XZp+GfMtvNCuz5iCos9fhKNuBITbZqXlGWX6yOkHnWyr6M+4i6m9fTj03CaW2VF1jf938Rmju2sbAWg+l45jpWsmUgnbsaR4dS/izerTKWGm4fIu4J+pCmrStP9q5H2f426wRddFUqM/uo2KDFQdY2eiRtr7CSUlc5qURILi05ckZcHvgtc9yPE3LajKZ1X/YXj5ZdR732HxCPTmhDV3+uKAxrsYjdYGXZroGJbMiCKbR2eTZdS32HLXIl0ZxVCSy5xlesdpOyLHXkVFb0xnZ69GAcm/dZTYq4lMMyvz3JVvZ5i8VWeUdcnNebVV88UAwcF0zzOj4nNLn2C1VtVo4sCbvZyp2XKPvhKvpOPEGfH9rDVj04I7I6b5Juy4/C+I+7UugPIjNtvk1FW3UV02O7sXvl+ogXD09mN4utZyUvrmXfn94mBDetTiuP7xSL5+pYs9tdKXtCFou7fZm2fDiexnZtKFT94Eca+k4VsdqlGlR25ghh9ZrN7L1dcexJjy00fcxOiq04jDVa+Eg4NddEUduWsZG3vqMJH71KtG0sXZ9xjTa+8Sol7N7GNr0Xy7qdz6eexR6zzR2jKeOnA7TFMIOdqHyXomf0EX+YkMdCDrwm1N+tZ8VC8mlZblHaoJ/NTtUrS5Wi5ondqpamARdaCXvH5NMLlc/SydTdVLFHCCtfbRy90f44WWtcoo8=
*/