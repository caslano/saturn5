/*-----------------------------------------------------------------------------+
Copyright (c) 2008-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_INTERVAL_SET_ALGO_HPP_JOFA_081005
#define BOOST_ICL_INTERVAL_SET_ALGO_HPP_JOFA_081005

#include <boost/next_prior.hpp>
#include <boost/icl/detail/notate.hpp>
#include <boost/icl/detail/relation_state.hpp>
#include <boost/icl/type_traits/identity_element.hpp>
#include <boost/icl/type_traits/is_map.hpp>
#include <boost/icl/type_traits/is_total.hpp>
#include <boost/icl/type_traits/is_combinable.hpp>
#include <boost/icl/concept/set_value.hpp>
#include <boost/icl/concept/map_value.hpp>
#include <boost/icl/interval_combining_style.hpp>
#include <boost/icl/detail/element_comparer.hpp>
#include <boost/icl/detail/interval_subset_comparer.hpp>
#include <boost/icl/detail/associated_value.hpp>

namespace boost{namespace icl
{

namespace Interval_Set
{

//------------------------------------------------------------------------------
// Lexicographical comparison on ranges of two interval container 
//------------------------------------------------------------------------------

template<class LeftT, class RightT>
bool is_element_equal(const LeftT& left, const RightT& right)
{
    return subset_compare
            (
                left, right, 
                left.begin(), left.end(), 
                right.begin(), right.end()
            ) == inclusion::equal;
}

template<class LeftT, class RightT>
bool is_element_less(const LeftT& left, const RightT& right)
{
    return element_compare
            (
                left, right, 
                left.begin(), left.end(), 
                right.begin(), right.end()
            )  == comparison::less;
}

template<class LeftT, class RightT>
bool is_element_greater(const LeftT& left, const RightT& right)
{
    return element_compare
            (
                left, right, 
                left.begin(), left.end(), 
                right.begin(), right.end()
            )  == comparison::greater;
}

//------------------------------------------------------------------------------
// Subset/superset compare on ranges of two interval container 
//------------------------------------------------------------------------------

template<class IntervalContainerT>
bool is_joinable(const IntervalContainerT& container, 
                 typename IntervalContainerT::const_iterator first, 
                 typename IntervalContainerT::const_iterator past) 
{
    if(first == container.end())
        return true;

    typename IntervalContainerT::const_iterator it_ = first, next_ = first;
    ++next_;

    while(next_ != container.end() && it_ != past)
        if(!icl::touches(key_value<IntervalContainerT>(it_++),
                         key_value<IntervalContainerT>(next_++)))
            return false;

    return true;
}


template<class LeftT, class RightT>
bool is_inclusion_equal(const LeftT& left, const RightT& right)
{
    return subset_compare
            (
                left, right, 
                left.begin(), left.end(), 
                right.begin(), right.end()
            ) == inclusion::equal;
}

template<class LeftT, class RightT>
typename enable_if<mpl::and_<is_concept_combinable<is_interval_set, is_interval_map, LeftT, RightT>, 
                             is_total<RightT> >,
                   bool>::type
within(const LeftT&, const RightT&)
{
    return true;
}

template<class LeftT, class RightT>
typename enable_if<mpl::and_<is_concept_combinable<is_interval_set, is_interval_map, LeftT, RightT>, 
                             mpl::not_<is_total<RightT> > >,
                   bool>::type
within(const LeftT& sub, const RightT& super)
{
    int result =
        subset_compare
        (
            sub, super, 
            sub.begin(), sub.end(), 
            super.begin(), super.end()
        );
    return result == inclusion::subset || result == inclusion::equal;
}


template<class LeftT, class RightT>
typename enable_if<is_concept_combinable<is_interval_map, is_interval_map, LeftT, RightT>, 
                   bool>::type
within(const LeftT& sub, const RightT& super)
{
    int result =
        subset_compare
        (
            sub, super, 
            sub.begin(), sub.end(), 
            super.begin(), super.end()
        );
    return result == inclusion::subset || result == inclusion::equal;
}

template<class LeftT, class RightT>
typename enable_if<is_concept_combinable<is_interval_set, is_interval_set, LeftT, RightT>, 
                   bool>::type
within(const LeftT& sub, const RightT& super)
{
    int result =
        subset_compare
        (
            sub, super, 
            sub.begin(), sub.end(), 
            super.begin(), super.end()
        );
    return result == inclusion::subset || result == inclusion::equal;
}



template<class LeftT, class RightT>
typename enable_if<mpl::and_<is_concept_combinable<is_interval_map, is_interval_set, LeftT, RightT>, 
                             is_total<LeftT> >,
                   bool>::type
contains(const LeftT&, const RightT&)
{
    return true;
}

template<class LeftT, class RightT>
typename enable_if<mpl::and_<is_concept_combinable<is_interval_map, is_interval_set, LeftT, RightT>, 
                             mpl::not_<is_total<LeftT> > >,
                   bool>::type
contains(const LeftT& super, const RightT& sub)
{
    int result =
        subset_compare
        (
            super, sub, 
            super.begin(), super.end(), 
            sub.begin(), sub.end()
        );
    return result == inclusion::superset || result == inclusion::equal;
}

template<class LeftT, class RightT>
typename enable_if<is_concept_combinable<is_interval_set, is_interval_set, LeftT, RightT>, 
                   bool>::type
contains(const LeftT& super, const RightT& sub)
{
    int result =
        subset_compare
        (
            super, sub, 
            super.begin(), super.end(), 
            sub.begin(), sub.end()
        );
    return result == inclusion::superset || result == inclusion::equal;
}

template<class IntervalContainerT>
bool is_dense(const IntervalContainerT& container, 
              typename IntervalContainerT::const_iterator first, 
              typename IntervalContainerT::const_iterator past) 
{
    if(first == container.end())
        return true;

    typename IntervalContainerT::const_iterator it_ = first, next_ = first;
    ++next_;

    while(next_ != container.end() && it_ != past)
        if(!icl::touches(key_value<IntervalContainerT>(it_++), 
                         key_value<IntervalContainerT>(next_++)))
            return false;

    return true;
}

} // namespace Interval_Set

namespace segmental
{

template<class Type>
inline bool joinable(const Type& _Type, typename Type::iterator& some, typename Type::iterator& next)
{
    // assert: next != end && some++ == next
    return touches(key_value<Type>(some), key_value<Type>(next)) 
        && co_equal(some, next, &_Type, &_Type); 
}

template<class Type>
inline void join_nodes(Type& object, typename Type::iterator& left_, 
                                     typename Type::iterator& right_)
{
    typedef typename Type::interval_type interval_type;
    interval_type right_interval = key_value<Type>(right_);
    object.erase(right_);
    const_cast<interval_type&>(key_value<Type>(left_)) 
        = hull(key_value<Type>(left_), right_interval);
}

template<class Type>
inline typename Type::iterator 
    join_on_left(Type& object, typename Type::iterator& left_, 
                               typename Type::iterator& right_)
{
    //CL typedef typename Type::interval_type interval_type;
    // both left and right are in the set and they are neighbours
    BOOST_ASSERT(exclusive_less(key_value<Type>(left_), key_value<Type>(right_)));
    BOOST_ASSERT(joinable(object, left_, right_));

    join_nodes(object, left_, right_);
    return left_;
}

template<class Type>
inline typename Type::iterator 
    join_on_right(Type& object, typename Type::iterator& left_, 
                                typename Type::iterator& right_)
{
    //CL typedef typename Type::interval_type interval_type;
    // both left and right are in the map and they are neighbours
    BOOST_ASSERT(exclusive_less(key_value<Type>(left_), key_value<Type>(right_)));
    BOOST_ASSERT(joinable(object, left_, right_));

    join_nodes(object, left_, right_);
    right_ = left_;
    return right_;
}

template<class Type>
typename Type::iterator join_left(Type& object, typename Type::iterator& it_)
{
    typedef typename Type::iterator iterator;

    if(it_ == object.begin())
        return it_;

    // there is a predecessor
    iterator pred_ = it_;
    if(joinable(object, --pred_, it_)) 
        return join_on_right(object, pred_, it_); 

    return it_;
}

template<class Type>
typename Type::iterator join_right(Type& object, typename Type::iterator& it_)
{
    typedef typename Type::iterator iterator;

    if(it_ == object.end())
        return it_;

    // there is a successor
    iterator succ_ = it_;

    if(++succ_ != object.end() && joinable(object, it_, succ_)) 
        return join_on_left(object, it_, succ_);

    return it_;
}

template<class Type>
typename Type::iterator join_neighbours(Type& object, typename Type::iterator& it_)
{
           join_left (object, it_); 
    return join_right(object, it_);
}

template<class Type>
inline typename Type::iterator 
    join_under(Type& object, const typename Type::value_type& addend)
{
    //ASSERT: There is at least one interval in object that overlaps with addend
    typedef typename Type::iterator      iterator;
    typedef typename Type::interval_type interval_type;
    typedef typename Type::value_type    value_type;

    std::pair<iterator,iterator> overlap = object.equal_range(addend);
    iterator first_ = overlap.first,
             end_   = overlap.second,
             last_  = end_; --last_;

    iterator second_= first_; ++second_;

    interval_type left_resid  = right_subtract(key_value<Type>(first_), addend);
    interval_type right_resid =  left_subtract(key_value<Type>(last_) , addend);

    object.erase(second_, end_);

    const_cast<value_type&>(key_value<Type>(first_)) 
        = hull(hull(left_resid, addend), right_resid);
    return first_;
}

template<class Type>
inline typename Type::iterator 
    join_under(Type& object, const typename Type::value_type& addend,
                                   typename Type::iterator last_)
{
    //ASSERT: There is at least one interval in object that overlaps with addend
    typedef typename Type::iterator      iterator;
    typedef typename Type::interval_type interval_type;
    typedef typename Type::value_type    value_type;

    iterator first_ = object.lower_bound(addend);
    //BOOST_ASSERT(next(last_) == this->_set.upper_bound(inter_val));
    iterator second_= boost::next(first_), end_ = boost::next(last_);

    interval_type left_resid  = right_subtract(key_value<Type>(first_), addend);
    interval_type right_resid =  left_subtract(key_value<Type>(last_) , addend);

    object.erase(second_, end_);

    const_cast<value_type&>(key_value<Type>(first_)) 
        = hull(hull(left_resid, addend), right_resid);
    return first_;
}

} // namespace segmental

namespace Interval_Set
{
using namespace segmental;

template<class Type, int combining_style>
struct on_style;

template<class Type>
struct on_style<Type, interval_combine::joining>
{
    typedef          on_style            type;
    typedef typename Type::interval_type interval_type;
    typedef typename Type::iterator      iterator;

    inline static iterator handle_inserted(Type& object, iterator inserted_)
    { return join_neighbours(object, inserted_); }

    inline static iterator add_over
        (Type& object, const interval_type& addend, iterator last_)
    {
        iterator joined_ = join_under(object, addend, last_);
        return join_neighbours(object, joined_);
    }

    inline static iterator add_over
        (Type& object, const interval_type& addend)
    {
        iterator joined_ = join_under(object, addend);
        return join_neighbours(object, joined_);
    }
};

template<class Type>
struct on_style<Type, interval_combine::separating>
{
    typedef          on_style            type;
    typedef typename Type::interval_type interval_type;
    typedef typename Type::iterator      iterator;

    inline static iterator handle_inserted(Type&, iterator inserted_)
    { return inserted_; }

    inline static iterator add_over
        (Type& object, const interval_type& addend, iterator last_)
    {
        return join_under(object, addend, last_);
    }

    inline static iterator add_over
        (Type& object, const interval_type& addend)
    {
        return join_under(object, addend);
    }
};

template<class Type>
struct on_style<Type, interval_combine::splitting>
{
    typedef          on_style            type;
    typedef typename Type::interval_type interval_type;
    typedef typename Type::iterator      iterator;

    inline static iterator handle_inserted(Type&, iterator inserted_)
    { return inserted_; }

    inline static iterator add_over
        (Type& object, const interval_type& addend, iterator last_)
    {
        iterator first_ = object.lower_bound(addend);
        //BOOST_ASSERT(next(last_) == this->_set.upper_bound(inter_val));

        iterator it_ = first_;
        interval_type rest_interval = addend;

        add_front(object, rest_interval, it_);
        add_main (object, rest_interval, it_, last_);
        add_rear (object, rest_interval, it_);
        return it_;
    }

    inline static iterator add_over
        (Type& object, const interval_type& addend)
    {
        std::pair<iterator,iterator> overlap = object.equal_range(addend);
        iterator first_ = overlap.first,
                 end_   = overlap.second,
                 last_  = end_; --last_;

        iterator it_ = first_;
        interval_type rest_interval = addend;

        add_front(object, rest_interval, it_);
        add_main (object, rest_interval, it_, last_);
        add_rear (object, rest_interval, it_);

        return it_;
    }
};


template<class Type>
void add_front(Type& object, const typename Type::interval_type& inter_val, 
                                   typename Type::iterator&      first_)
{
    typedef typename Type::interval_type interval_type;
    typedef typename Type::iterator      iterator;
    // If the collision sequence has a left residual 'left_resid' it will
    // be split, to provide a standardized start of algorithms:
    // The addend interval 'inter_val' covers the beginning of the collision sequence.

    // only for the first there can be a left_resid: a part of *first_ left of inter_val
    interval_type left_resid = right_subtract(key_value<Type>(first_), inter_val);

    if(!icl::is_empty(left_resid))
    {   //            [------------ . . .
        // [left_resid---first_ --- . . .
        iterator prior_ = cyclic_prior(object, first_);
        const_cast<interval_type&>(key_value<Type>(first_)) 
            = left_subtract(key_value<Type>(first_), left_resid);
        //NOTE: Only splitting
        object._insert(prior_, icl::make_value<Type>(left_resid, co_value<Type>(first_)));
    }

    //POST:
    // [----- inter_val ---- . . .
    // ...[-- first_ --...
}


template<class Type>
void add_segment(Type& object, const typename Type::interval_type& inter_val, 
                                     typename Type::iterator&      it_      )
{
    typedef typename Type::interval_type interval_type;
    interval_type lead_gap = right_subtract(inter_val, *it_);
    if(!icl::is_empty(lead_gap))
        //           [lead_gap--- . . .
        // [prior_)           [-- it_ ...
        object._insert(prior(it_), lead_gap);

    // . . . --------- . . . addend interval
    //      [-- it_ --)      has a common part with the first overval
    ++it_;
}


template<class Type>
void add_main(Type& object, typename Type::interval_type& rest_interval, 
                            typename Type::iterator&      it_,
                      const typename Type::iterator&      last_)
{
    typedef typename Type::interval_type interval_type;
    interval_type cur_interval;
    while(it_ != last_)
    {
        cur_interval = *it_ ;
        add_segment(object, rest_interval, it_);
        // shrink interval
        rest_interval = left_subtract(rest_interval, cur_interval);
    }
}


template<class Type>
void add_rear(Type& object, const typename Type::interval_type& inter_val, 
                                  typename Type::iterator&      it_      )
{
    typedef typename Type::interval_type interval_type;
    typedef typename Type::iterator      iterator;

    iterator prior_ = cyclic_prior(object, it_);
    interval_type cur_itv = *it_;

    interval_type lead_gap = right_subtract(inter_val, cur_itv);
    if(!icl::is_empty(lead_gap))
        //          [lead_gap--- . . .
        // [prior_)          [-- it_ ...
        object._insert(prior_, lead_gap);
    
    interval_type end_gap = left_subtract(inter_val, cur_itv);
    if(!icl::is_empty(end_gap))
        // [---------------end_gap)
        //      [-- it_ --)
        it_ = object._insert(it_, end_gap);
    else
    {
        // only for the last there can be a right_resid: a part of *it_ right of addend
        interval_type right_resid = left_subtract(cur_itv, inter_val);

        if(!icl::is_empty(right_resid))
        {
            // [--------------)
            //      [-- it_ --right_resid)
            const_cast<interval_type&>(*it_) = right_subtract(*it_, right_resid);
            it_ = object._insert(it_, right_resid);
        }
    }
}


//==============================================================================
//= Addition
//==============================================================================
template<class Type>
typename Type::iterator 
    add(Type& object, const typename Type::value_type& addend)
{
    //CL typedef typename Type::interval_type interval_type;
    typedef typename Type::iterator      iterator;
    typedef typename on_style<Type, Type::fineness>::type on_style_;

    if(icl::is_empty(addend)) 
        return object.end();

    std::pair<iterator,bool> insertion = object._insert(addend);

    if(insertion.second)
        return on_style_::handle_inserted(object, insertion.first);
    else
        return on_style_::add_over(object, addend, insertion.first);
}


template<class Type>
typename Type::iterator 
    add(Type& object, typename Type::iterator    prior_, 
                const typename Type::value_type& addend)
{
    //CL typedef typename Type::interval_type interval_type;
    typedef typename Type::iterator      iterator;
    typedef typename on_style<Type, Type::fineness>::type on_style_;

    if(icl::is_empty(addend)) 
        return prior_;

    iterator insertion = object._insert(prior_, addend);

    if(*insertion == addend)
        return on_style_::handle_inserted(object, insertion);
    else
        return on_style_::add_over(object, addend);
}


//==============================================================================
//= Subtraction
//==============================================================================
template<class Type>
void subtract(Type& object, const typename Type::value_type& minuend)
{
    typedef typename Type::iterator      iterator;
    typedef typename Type::interval_type interval_type;
    //CL typedef typename Type::value_type    value_type;

    if(icl::is_empty(minuend)) return;

    std::pair<iterator, iterator> exterior = object.equal_range(minuend);
    if(exterior.first == exterior.second) return;

    iterator first_ = exterior.first;
    iterator end_   = exterior.second;
    iterator last_  = end_; --last_;

    interval_type leftResid = right_subtract(*first_, minuend);
    interval_type rightResid; 
    if(first_ != end_  )
        rightResid = left_subtract(*last_ , minuend);

    object.erase(first_, end_);

    if(!icl::is_empty(leftResid))
        object._insert(leftResid);

    if(!icl::is_empty(rightResid))
        object._insert(rightResid);
}


} // namespace Interval_Set

}} // namespace icl boost

#endif 


/* interval_set_algo.hpp
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
*/