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