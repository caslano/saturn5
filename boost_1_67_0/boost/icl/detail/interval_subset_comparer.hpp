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