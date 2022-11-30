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
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
*/