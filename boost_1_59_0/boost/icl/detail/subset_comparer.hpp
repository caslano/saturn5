/*-----------------------------------------------------------------------------+
Copyright (c) 2008-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_SUBSET_COMPARER_HPP_JOFA_090202
#define BOOST_ICL_SUBSET_COMPARER_HPP_JOFA_090202

#include <boost/mpl/and.hpp>
#include <boost/icl/type_traits/is_map.hpp>
#include <boost/icl/detail/notate.hpp>
#include <boost/icl/detail/relation_state.hpp>
#include <boost/icl/type_traits/identity_element.hpp>
#include <boost/icl/type_traits/codomain_type_of.hpp>
#include <boost/icl/type_traits/is_concept_equivalent.hpp>
#include <boost/icl/type_traits/is_element_container.hpp>
#include <boost/icl/concept/interval_set_value.hpp>
#include <boost/icl/concept/map_value.hpp>

namespace boost{namespace icl
{

#ifdef BOOST_MSVC 
#pragma warning(push)
#pragma warning(disable:4127) // conditional expression is constant
#endif                        

namespace Set
{

//------------------------------------------------------------------------------
template<class LeftT, class RightT>
struct settic_codomain_compare
{
    static int apply(typename LeftT::const_iterator& left_, typename RightT::const_iterator& right_)
    {
        return inclusion_compare( co_value<LeftT>(left_), 
                                 co_value<RightT>(right_));
    }
};

template<class LeftT, class RightT>
struct atomic_codomain_compare
{
    static int apply(typename LeftT::const_iterator& left_, typename RightT::const_iterator& right_)
    {
        if(co_value<LeftT>(left_) == co_value<RightT>(right_))
            return inclusion::equal;
        else
            return inclusion::unrelated;
    }
};

template<class LeftT, class RightT>
struct empty_codomain_compare
{
    static int apply(typename LeftT::const_iterator&, typename RightT::const_iterator&)
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

    enum{nextboth, stop};

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
        //CL typedef typename codomain_type_of<LeftT>::type  LeftCodomainT;
        //CL typedef typename codomain_type_of<RightT>::type RightCodomainT;

        return  
            if_<
                bool_<is_concept_equivalent<is_element_map,LeftT,RightT>::value>,
                map_codomain_compare<LeftT,RightT>,
                empty_codomain_compare<LeftT,RightT>
            >
            ::type::apply(left,right);
    }

    int restrict_result(int state) { return _result &= state; }

    int next_both(LeftIterT& left, RightIterT& right)
    {
        if(left == _left_end && right == _right_end)
            return stop;
        else if(left == _left_end)
        {
            restrict_result(subset);
            return stop;
        }
        else if(right == _right_end)
        {
            restrict_result(superset);
            return stop;
        }
        else if(typename LeftT::key_compare()(key_value<LeftT>(left), key_value<RightT>(right)))
        {   // left:  *left . . *joint_     left could be superset
            // right:           *right ...  if joint_ exists
            restrict_result(superset);
            if(unrelated == _result)
                return stop;
            else
            {
                LeftIterT joint_ = _left.lower_bound(key_value<RightT>(right));
                if(    joint_ == _left.end() 
                    || typename LeftT::key_compare()(key_value<RightT>(right), key_value<LeftT>(joint_)))
                {
                    _result = unrelated;
                    return stop;
                }
                else
                    left = joint_;
            }
        }
        else if(typename LeftT::key_compare()(key_value<RightT>(right), key_value<LeftT>(left)))
        {   // left:             *left   left could be subset
            // right:*right . . .*joint_ if *joint_ exists 
            restrict_result(subset);
            if(unrelated == _result)
                return stop;
            else
            {
                RightIterT joint_ = _right.lower_bound(key_value<LeftT>(left));
                if(    joint_ == _right.end()
                    || typename LeftT::key_compare()(key_value<LeftT>(left), key_value<RightT>(joint_)))
                {
                    _result = unrelated;
                    return stop;
                }
                else
                    right = joint_;
            }
        }

        // left =key= right 
        if(_compare_codomain)
            if(unrelated == restrict_result(co_compare(left,right)))
                return stop;

        ++left;
        ++right;
        return nextboth;
    }

private:
    const LeftT&  _left;
    const RightT& _right;
    LeftIterT     _left_end;
    RightIterT    _right_end;
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
        state = step.next_both(left_, right_);

    return step.result();
}

template<class LeftT, class RightT>
int subset_compare(const LeftT& left, const RightT& right)
{
    return subset_compare
        (
            left, right,
            left.begin(), left.end(),
            right.begin(), right.end()
        );
}


} // namespace Set
    
#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

}} // namespace icl boost

#endif 


/* subset_comparer.hpp
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
*/