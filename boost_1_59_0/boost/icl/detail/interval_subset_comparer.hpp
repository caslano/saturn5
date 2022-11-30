/*-----------------------------------------------------------------------------+
Copyright (c) 2008-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_INTERVAL_SUBSET_COMPARER_HPP_JOFA_090827
#define BOOST_ICL_INTERVAL_SUBSET_COMPARER_HPP_JOFA_090827

#include <boost/icl/type_traits/is_map.hpp>
#include <boost/icl/detail/notate.hpp>
#include <boost/icl/detail/relation_state.hpp>
#include <boost/icl/type_traits/identity_element.hpp>
#include <boost/icl/type_traits/is_concept_equivalent.hpp>
#include <boost/icl/type_traits/is_interval_container.hpp>
#include <boost/icl/type_traits/is_set.hpp>
#include <boost/icl/concept/interval_set_value.hpp>

namespace boost{namespace icl
{

#ifdef BOOST_MSVC 
#pragma warning(push)
#pragma warning(disable:4127) // conditional expression is constant
#endif                        

namespace Interval_Set
{

//------------------------------------------------------------------------------
template<class LeftT, class RightT>
struct settic_codomain_compare
{
    static int apply(typename LeftT::const_iterator& left_, typename RightT::const_iterator& right_)
    {
        return inclusion_compare( icl::co_value<LeftT>(left_), 
                                 icl::co_value<RightT>(right_));
    }
};

template<class LeftT, class RightT>
struct atomic_codomain_compare
{
    static int apply(typename LeftT::const_iterator& left_, typename RightT::const_iterator& right_)
    {
        if(icl::co_value<LeftT>(left_) == icl::co_value<RightT>(right_))
            return inclusion::equal;
        else
            return inclusion::unrelated;
    }
};

template<class LeftT, class RightT>
struct empty_codomain_compare
{
    static int apply(typename LeftT::const_iterator&, typename RightT::const_iterator)
    {
        return inclusion::equal;
    }
};

template<class LeftT, class RightT>
struct map_codomain_compare
{
    static int apply(typename LeftT::const_iterator& left_, typename RightT::const_iterator& right_)
    {
        using namespace boost::mpl;
        typedef typename LeftT::codomain_type  LeftCodomainT;
        typedef typename RightT::codomain_type RightCodomainT;

        return
            if_<
                bool_<is_concept_equivalent<is_set,LeftCodomainT,
                                                   RightCodomainT>::value>,
                settic_codomain_compare<LeftT,RightT>,
                atomic_codomain_compare<LeftT,RightT>
            >
            ::type::apply(left_, right_);
    }
};


//------------------------------------------------------------------------------
template<class LeftT, class RightT>
class subset_comparer
{
private:
    subset_comparer& operator = (const subset_comparer&);
public:
    typedef typename LeftT::const_iterator  LeftIterT;
    typedef typename RightT::const_iterator RightIterT;

    BOOST_STATIC_CONSTANT(bool, 
        _compare_codomain = (mpl::and_<is_map<LeftT>, is_map<RightT> >::value)); 


    subset_comparer(const LeftT&      left,
                    const RightT&     right,
                    const LeftIterT&  left_end,
                    const RightIterT& right_end)
        : _left(left), _right(right),
          _left_end(left_end), _right_end(right_end), _result(equal)
    {}

    enum{nextboth, nextleft, nextright, stop};

    enum
    {
        unrelated  = inclusion::unrelated, 
        subset     = inclusion::subset,     // left is_subset_of   right 
        superset   = inclusion::superset,   // left is_superset_of right
        equal      = inclusion::equal       // equal = subset | superset
    };

    int result()const{ return _result; }


    int co_compare(LeftIterT& left, RightIterT& right)
    {
        using namespace boost::mpl;

        return  
            if_<
                bool_<is_concept_equivalent<is_interval_map,LeftT,RightT>::value>,
                map_codomain_compare<LeftT,RightT>,
                empty_codomain_compare<LeftT,RightT>
            >
            ::type::apply(left,right);
    }

    int restrict_result(int state) { return _result &= state; }

    int proceed(LeftIterT& left, RightIterT& right)
    {
        if(upper_less(key_value<LeftT>(left), key_value<RightT>(right)))
        {   // left  ..)  
            // right .....)
            _prior_left = left;
            ++left;
            return nextleft;
        }
        else if(upper_less(key_value<RightT>(right), key_value<LeftT>(left)))
        {   // left  .....)
            // right ..)
            _prior_right = right;
            ++right;
            return nextright;
        }
        else//key_value<LeftT>(left).upper_equal(key_value<RightT>(right))
        {   // left  ..)
            // right ..)
            ++left; 
            ++right;    
            return nextboth;
        }
    }

    int next_both(LeftIterT& left, RightIterT& right)
    {
        if(left == _left_end && right == _right_end)
            return stop;
        else if(left == _left_end)
        {   // left: ....end    left could be subset
            // right:....[..
            restrict_result(subset);
            return stop;
        }
        else if(right == _right_end)
        {   // left: ....[..    left could be superset
            // right:....end
            restrict_result(superset);
            return stop;
        }
        else if(exclusive_less(key_value<LeftT>(left), key_value<RightT>(right)))
        {   // left: [..) . . .[---)      left could be superset
            // right:           [..)....  if [---) exists
            restrict_result(superset);
            if(unrelated == _result)
                return stop;
            else
            {
                LeftIterT joint_ = _left.lower_bound(key_value<RightT>(right));
                if(joint_ == _left.end())
                {
                    _result = unrelated;
                    return stop;
                }
                else
                {
                    left = joint_;
                    return nextboth;
                }
            }
        }
        else if(exclusive_less(key_value<RightT>(right), key_value<LeftT>(left)))
        {   // left:             [..  left could be subset
            // right:....) . . .[---) if [---) exists 
            restrict_result(subset);
            if(unrelated == _result)
                return stop;
            else
            {
                RightIterT joint_ = _right.lower_bound(key_value<LeftT>(left));
                if(joint_ == _right.end())
                {
                    _result = unrelated;
                    return stop;
                }
                else
                {
                    right = joint_;
                    return nextboth;
                }
            }
        }

        // left and right have intervals with nonempty intersection:
        if(_compare_codomain)
            if(unrelated == restrict_result(co_compare(left,right)))
                return stop;

        // examine left borders only. Right borders are checked in proceed
        if(lower_less(key_value<LeftT>(left), key_value<RightT>(right)))
        {   // left: ....[...     left could be superset
            // right:....   [..
            if(unrelated == restrict_result(superset))
                return stop;
        }
        else if(lower_less(key_value<RightT>(right), key_value<LeftT>(left)))
        {   // left: ....   [..   left can be subset
            // right:....[...
            if(unrelated == restrict_result(subset))
                return stop;
        }
        //else key_value<LeftT>(right).lower_equal(key_value<RightT>(left))
            // left: ....[..   both can be equal
            // right:....[..
            // nothing to do: proceed

        return proceed(left, right);
    }

    int next_left(LeftIterT& left, RightIterT& right)
    {
        if(left == _left_end)
        {   // left: ..)end    left could be subset
            // right:......)
            restrict_result(subset);
            return stop;            
        }
        else if(!touches(key_value<LeftT>(_prior_left), key_value<LeftT>(left)))
        {   // left: ..)   [..
            // right:.........)
            if(lower_less(key_value<RightT>(right), key_value<LeftT>(left)))
            {   //   ..)   [..   left could be subset
                //   ..........)
                if(unrelated == restrict_result(subset))
                    return stop;            
            }
            //else   ..)   [...
            //          [..
            if(_compare_codomain && intersects(key_value<LeftT>(left),key_value<RightT>(right)) )
                if(unrelated == restrict_result(co_compare(left,right)))
                    return stop;
        }
        else
        {   // left: ..)[..  left could be subset
            // right:.......)
            if(_compare_codomain && intersects(key_value<LeftT>(left), key_value<RightT>(right)) )
                if(unrelated == restrict_result(co_compare(left,right)))
                    return stop;
        }

        return proceed(left, right);
    }


    int next_right(LeftIterT& left, RightIterT& right)
    {
        if(right == _right_end)
        {   // left: ......)    left could be superset
            // right:..)end
            restrict_result(superset);
            return stop;            
        }
        else if(!touches(key_value<RightT>(_prior_right), key_value<RightT>(right)))
        {   // left: .........)
            // right:..)   [..
            if(lower_less(key_value<LeftT>(left), key_value<RightT>(right)))
            {   //       [....)  left could be superset
                //   ..)   [..
                if(unrelated == restrict_result(superset))
                    return stop;            
            }
            //else       [....)
            //   ..)   [..
            if(_compare_codomain && intersects(key_value<LeftT>(left), key_value<RightT>(right)) )
                if(unrelated == restrict_result(co_compare(left,right)))
                    return stop;
        }
        else
        {
            if(_compare_codomain && intersects(key_value<LeftT>(left), key_value<RightT>(right)) )
                if(unrelated == restrict_result(co_compare(left,right)))
                    return stop;
        }

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





//------------------------------------------------------------------------------
// Subset/superset comparison on ranges of two interval container 
//------------------------------------------------------------------------------
template<class LeftT, class RightT>
int subset_compare
(
    const LeftT& left,   //sub
    const RightT& right, //super
    typename LeftT::const_iterator  left_begin,   
    typename LeftT::const_iterator  left_end,
    typename RightT::const_iterator right_begin, 
    typename RightT::const_iterator right_end
)
{
    typedef subset_comparer<LeftT,RightT> Step;
    Step step(left, right, left_end, right_end);

    typename LeftT::const_iterator  left_  = left_begin;
    typename RightT::const_iterator right_ = right_begin;

    int state = Step::nextboth;
    while(state != Step::stop)
    {
        switch(state){
        case Step::nextboth:    state = step.next_both(left_, right_);  break;
        case Step::nextleft:    state = step.next_left(left_, right_);  break;
        case Step::nextright:   state = step.next_right(left_, right_); break;
        }
    }
    return step.result();
}


} // namespace Interval_Set
    
#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

}} // namespace icl boost

#endif 


/* interval_subset_comparer.hpp
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
*/