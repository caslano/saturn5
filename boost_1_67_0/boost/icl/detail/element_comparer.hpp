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