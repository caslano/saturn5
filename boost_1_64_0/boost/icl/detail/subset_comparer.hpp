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
GVslVaU352u3ryhXZ+y9QSt0oM1uUmVmekcMmQsQol/7G0R1NvddNwqZI9wYbbixz3j77bKdMprX5g5ed+UYHIwf4q1j9yTp/UznYgmhcpdqO6tt2p9fJs/QN0md990nuIs800ZWFUkrt76dCfsDe1cCHkWRhd8kQRNQGIQgiEBzHxLIieE0IQkQCRBJuAQdJjOdZGAuZiYhQW7lWA6BRRZRVA7lEiQoCCpoQBREQMQLQVjwQgQUFfGG/bu7KtPT6RzD7rfXZ3350/2uqlevq6u7q6ar351x7/F1TTvcmLmjzvGWRiIDLbwnav1mT8mD6R/Pue/9fSVZnQ7cczj003frdJ/wRvGuWecinkta813MuXcOj/w4LzBeXYhodFui6rSpclE13DZ98qWbP/y9dsuMzWH2MffNmdF1ZEv73k0df+hw06Zdb528IpScX3bDkSVT7K6vD5mz8/9uHPDp3w4tMH68FfNCk+ZGpox49rfGU7JnlGScnzn9zpNvnTr+aIe8x+5d9HiOY2DmupPexsYJy3ISm207duNrbRreUqf0vh556584Yz56OaJNi6sH3I0//7FO3+HjBs6Z9cr3a4Z/O6/52Te+PSd2aWZvv6x0T9+SEx/d9OV24cjmv4Sud803rdozxHdfj7TG0R0X9/l4++czzu78vNnYEc16LRhz8u2SnRmdH5kw6cy6x3PuGzNi7p2jKTQpvsK/lq/X+3Vbjb+4u9//5vyEWVffvLnB7bsxWHb3InVc+TyoZs6z8nAacouLn6719NIvPtjjLrrhVrrc/+7vLuyx1A4vGnX+YCTxZ5nXFm12fO0NPI71iShUM16TFMzY1o1xC3S4D+i0gf0hG3ja98O+2Y2PzFywzs79aKhXbyLh+sbZmp4j/dSQ9NPNdM2fLv4yMfXEU62El39fe//feJyYE+fuv9vkdY/4ZPTf921a8sKxeksic+rE137g01VTz/s+fdX88nHffUu/+ul1ajr8sRlLesffUm/QhqhdF5bsP5Z3//BXP9jc4Ou7xgzKWTyvT8z5e3/atfPE6w3y3u474baHX0/8pW9y7vKllgbHLc39ZYxY9H5m+6QnR/8eUR0/dHg3TRgy1vFc1sgH7rnYccCkDRNqjRryw9Qty7Z0fzz+291dJ1tfPl9j4x7xWsuiTR+OmztxYiPzpWWNH2qVMr754LdOb6rMj4bMj9dDLjdZ3KHLobWr+0Qvfnf+9gWH+zrOrMtZOmbRrUmFW06fWd61NObqzBm7D5xO+uLNx9p92weY2O7g6k88TcIGpf5t54HJl+u7Xmv9VukK6+QNLz49K6sk7g17yaWFNTuP6pd1p+nD+i8unDlm18gdc0392u1Op5Avx9+16tf2jy9Qldv5yScXjR351Xchj+3duLu6/lXAf6TeB65fLxTlN83/5dTW7gmv7vktP7tT2788UNzt3Bfzpl/pEd2uU7Ozr1y+a23H1DFXLpuntY+Y3HFo3p4W3RZ22HYg9Ql6aPsXL5yaeNDwVlX+3c78+2h3/IY2KbkzOzSMbl3w7kezSp66cdjS43/5cfL+0mv5z3zZcf1h++3tHw1dszur1j0DG3Y4VhLWYcSBo0+ltJ56pcc7nycnzrqx3pb1LW2f9WqecDT3xAueRHtSrZsXtt/UcfKoy/HhLZ9fN+nNeU9mfHZrRlPnH9/cUjpp+IahP3lKPa5Wb+54cuChja0S+j+57MDqK+8V1g85FODLkd8efbfBzv6OUztXP7N28VPB+F2J7Pf+cZMWJ4cdeuDbto2v3HSx6dGbV2aEv/CK9bs5o2fPH7Pls9TDra8l/q33wClX6xd2ejv957/OKd03uv3WD6aG+s4=
*/