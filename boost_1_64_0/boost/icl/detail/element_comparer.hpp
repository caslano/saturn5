/*-----------------------------------------------------------------------------+
Copyright (c) 2008-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_ELEMENT_COMPARER_HPP_JOFA_090202
#define BOOST_ICL_ELEMENT_COMPARER_HPP_JOFA_090202

#include <boost/mpl/and.hpp>
#include <boost/icl/type_traits/is_map.hpp>
#include <boost/icl/detail/notate.hpp>
#include <boost/icl/type_traits/identity_element.hpp>

namespace boost{namespace icl
{

namespace Interval_Set
{

template<class LeftT, class RightT>
class element_comparer
{
public:
    typedef typename LeftT::const_iterator  LeftIterT;
    typedef typename RightT::const_iterator RightIterT;

    BOOST_STATIC_CONSTANT(bool, 
        _compare_codomain = (mpl::and_<is_map<LeftT>, is_map<RightT> >::value)); 

    element_comparer(const LeftT&      left,
                     const RightT&     right,
                     const LeftIterT&  left_end,
                     const RightIterT& right_end)
        : _left(left), _right(right),
          _left_end(left_end), _right_end(right_end), _result(equal)
    {}

    enum{nextboth, nextleft, nextright, stop};

    enum
    {
        less    = comparison::less, 
        equal   = comparison::equal, 
        greater = comparison::greater
    };

    int result()const{ return _result; }

    bool covalues_are_equal(LeftIterT& left, RightIterT& right)
    {
        if(co_value<LeftT>(left) < co_value<RightT>(right))
            _result = less;
        if(co_value<RightT>(right) < co_value<LeftT>(left))
            _result = greater;
        return _result == equal;
    }

    int proceed(LeftIterT& left, RightIterT& right)
    {
        if(upper_less(key_value<LeftT>(left), key_value<RightT>(right)))
        {
            _prior_left = left;
            ++left;
            return nextleft;
        }
        else if(upper_less(key_value<RightT>(right), key_value<LeftT>(left)))
        {
            _prior_right = right;
            ++right;
            return nextright;
        }
        else
        {
            ++left; 
            ++right;    
            return nextboth;
        }
    }

    int next_both(LeftIterT& left, RightIterT& right)
    {
        if(left == _left_end)
        {
            _result = (right == _right_end) ? equal : less;
            return stop;
        }

        // left != _left_end
        if(right == _right_end)
        {
            _result = greater;
            return stop;
        }

        // The starting intervals have to begin equally
        if(lower_less(key_value<LeftT>(left), key_value<RightT>(right)))
        {   // left: same A... = sameA...
            // right:same  B.. = sameB...
            _result = less;
            return stop;
        }

        if(lower_less(key_value<LeftT>(right), key_value<RightT>(left)))
        {   // left: same  B.. = sameB...
            // right:same A... = sameA...
            _result = greater;
            return stop;
        }

        if(_compare_codomain && !covalues_are_equal(left, right))
            return stop;

        return proceed(left, right);
    }

    int next_left(LeftIterT& left, RightIterT& right)
    {
        if(left == _left_end)
        {   // left: same
            // right:sameA...
            _result = less;
            return stop;
        }

        if(!key_value<LeftT>(_prior_left).touches(key_value<LeftT>(left)))
        {   // left: same B = sameB...
            // right:sameA  = sameA...
            _result = greater;
            return stop;
        }

        if(_compare_codomain && !covalues_are_equal(left, right))
            return stop;

        return proceed(left, right);
    }

    int next_right(LeftIterT& left, RightIterT& right)
    {
        if(right == _right_end)
        {   // left: sameA...
            // right:same
            _result = greater;
            return stop;
        }

        if(!key_value<RightT>(_prior_right).touches(key_value<RightT>(right)))
        {
            // left: sameA... = sameA...
            // right:same B.. = sameB...
            _result = less;
            return stop;
        }

        if(_compare_codomain && !covalues_are_equal(left, right))
            return stop;

        return proceed(left, right);
    }

private:
    const LeftT&  _left;
    const RightT& _right;
    LeftIterT     _left_end;
    RightIterT    _right_end;
    LeftIterT     _prior_left;
    RightIterT    _prior_right;
    int           _result;
};



template<class LeftT, class RightT>
int element_compare
(
    const LeftT& left,   //sub
    const RightT& right, //super
    typename LeftT::const_iterator  left_begin,   
    typename LeftT::const_iterator  left_end,
    typename RightT::const_iterator right_begin, 
    typename RightT::const_iterator right_end
)
{
    typedef element_comparer<LeftT,RightT> Step;
    Step step(left, right, left_end, right_end);

    typename LeftT::const_iterator  left_  = left_begin;
    typename RightT::const_iterator right_ = right_begin;

    int state = Step::nextboth;
    while(state != Step::stop)
    {
        switch(state){
        case Step::nextboth:  state = step.next_both (left_, right_); break;
        case Step::nextleft:  state = step.next_left (left_, right_); break;
        case Step::nextright: state = step.next_right(left_, right_); break;
        }
    }
    return step.result();
}


} // namespace Interval_Set
    
}} // namespace icl boost

#endif 


/* element_comparer.hpp
kaMXDqKeVqbs/Lgt2n98Jv9MuIOFk64g5r4uo2v92Wf4FD6YvVkOGvcXoyJrZcRAY87raohetlpMH95OXreYhdax6WJBsB/iPD3hFzOZOWPCpJ6qKmNuNZEzLQdg8NEMOchLCREvokTnc+4w72onvuofZPqmv/LJ7ZtMctguDfvV4JnIlSfOamNXrZ7Q0V/Jtj+yWHZkHc+lPpQWoyzRr8QI+QmjeXmBI9p6qqB7y6ncGviLej/cMPFiWyo/7Y6m6f74XvFKrL8/l02ePRSZm2fSaXG+4n3Uw9TbWsK583cmJlyDjncYHo5vTl2jSBxoXSsCZ1fwb0iByDi/CvPfTOHEPxHQ99SHg8YM1OmslscW2bDTbSURaKqDxgnd5bivpxiv/kKOSQ3DyMBmmO5ViZVH+2HPrBYc11nhZE+G0drpOhF5g5GTrspl0wJZebhShNhVMV/1qzi0UocXFr3ChWPtcMOjlVAfs16RPS8wcf16hmfOlJO+rWAnr9YsezWcyfqf6T19BXu0X83L3xaizG4PLYv/cMlJZxEUFYXqbSqiLFcb+as7iyUtP8Nr7h4RXt8G3+LOyEVefsjadVD2M5ql4JeDMcBwKuNuxsD+qQPOqqqJ5palzJVRmHElD4tarZO+i0/z3yPIo3kjYGRZL4wUvEh57HJpv9iA7y/+ETu5FeV71VFppAk/8Z2FJ6O5cGErmdH2Js+6rRQpqg1Mm9tCdjE2p3KvJvzjaozO3SPEuUhlOPvnicy5WshwknL1yAfQ0rfAWkMl7B4fgQ+l9XS/9VacNX+NhCs63LNkOw8remiA3gJ8cXwvjbyO0mJNrThYP5JBfdXF9xl1sJvYUTh9mEzr8eOYVfYJphF2PHtIk15rXsuXfVpzy9VtcCq4hkVD7JErU/m23Qt51nwFyz5MZ5//CnGsbL/scaMdjqa3FsrznfgmZS6OPf/I+6EG2Oz8H8MyP8mdqzbR5/RXOexNBxp3OM0PKzPR4X1PeUctBWUyVIT0XYr9057wWXUpRhZslTWjNuBUliPr1X5TK9qMytHKmL4zjWt/PETn14UwC9BmuIJVl/eaxZl6L8U7M3UUFQco+q7ifzi3TG5x3MGVZjpM81e4sX8WePNHF7lz3cQmRSf8WtZCLBuWTROj5VjoXY03uU5i8jWBeTG9YV2cyDZ36tmqvJGPQ36i878WtH3cRQQ38YJuXE98sq/izVO5PNDirSLnDcPtpAhWtL/IpbsN6KbWRTTmJOJOcTMaXA/n+kNHpd3mEbRea8o2Rv3RqX8A7U78RFGiBQpOKvH18yxp6Xic93q5caBihm55fwZ1S7vC3Pw9Qm1VuXlUP7lzmhFs9xtihPNhhKuel86rr8JH05d1Sd/Z+moI0pY9ousrRwxs1MPxA82w07cGLkJLfjn4nCc8OlC/5hy8+1fg9l9DyKOeMnRdf7qumIAXBzQZ9rQAA64fw8MB+ly27DpvmBezcrQPPr6pFfeaNoPu2hGyWWwwdUxPy8TQRSyoaIP5Kcp4mT2OKk3HYs2q1fzj1hKfAtrxaNd76H5FW5RMruf6DoNliJEuz6p+FH7xvfnTdDIeB3hhu3swin91Z9XuPRh3ZImCdd/Aa5+z7K27VuZMnIEeG15Jqy5HeTXmPifd/wf3mUeEek5fPDe9JTpX22NfsQqM7QvZeuZlBpWvo/ejvcLvwnha7riAd1HL4GfjzvywgVjQ6hIfLw5mu8V94HwviY++R8Isfy+3/WpAk5NtoPr7Cna3kNDJ0eTcxyWwDzJgx6vdsefDM/H78x+WT+whz10NYfVjA7Fz+kConyuWPWsn4IdnJQZpt2KZ90zRbJIK+yy9iRY++pw=
*/