/*-----------------------------------------------------------------------------+
Copyright (c) 2007-2011: Joachim Faulhaber
Copyright (c) 1999-2006: Cortex Software GmbH, Kantstrasse 57, Berlin
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_INTERVAL_BASE_SET_H_JOFA_990223
#define BOOST_ICL_INTERVAL_BASE_SET_H_JOFA_990223

#include <boost/icl/impl_config.hpp>

#if defined(ICL_USE_BOOST_MOVE_IMPLEMENTATION)
#   include <boost/container/set.hpp>
#elif defined(ICL_USE_STD_IMPLEMENTATION)
#   include <set>
#else // Default for implementing containers
#   include <set>
#endif

#include <limits>
#include <boost/next_prior.hpp>
#include <boost/icl/associative_interval_container.hpp>
#include <boost/icl/type_traits/interval_type_default.hpp>
#include <boost/icl/interval.hpp>
#include <boost/icl/type_traits/infinity.hpp>
#include <boost/icl/type_traits/is_interval_joiner.hpp>
#include <boost/icl/type_traits/is_interval_separator.hpp>
#include <boost/icl/type_traits/is_interval_splitter.hpp>
#include <boost/icl/detail/interval_set_algo.hpp>
#include <boost/icl/detail/exclusive_less_than.hpp>

#include <boost/icl/right_open_interval.hpp>
#include <boost/icl/continuous_interval.hpp>
#include <boost/icl/detail/notate.hpp>
#include <boost/icl/detail/element_iterator.hpp>

namespace boost{namespace icl
{

/** \brief Implements a set as a set of intervals (base class) */
template
<
    typename             SubType,
    typename             DomainT,
    ICL_COMPARE Compare  = ICL_COMPARE_INSTANCE(ICL_COMPARE_DEFAULT, DomainT),
    ICL_INTERVAL(ICL_COMPARE) Interval = ICL_INTERVAL_INSTANCE(ICL_INTERVAL_DEFAULT, DomainT, Compare),
    ICL_ALLOC   Alloc    = std::allocator
>
class interval_base_set
{
public:
    //==========================================================================
    //= Associated types
    //==========================================================================
    typedef interval_base_set<SubType,DomainT,Compare,Interval,Alloc> type;

    /// The designated \e derived or \e sub_type of this base class
    typedef SubType sub_type;

    /// Auxilliary type for overloadresolution
    typedef type overloadable_type;

    //--------------------------------------------------------------------------
    //- Associated types: Data
    //--------------------------------------------------------------------------
    /// The domain type of the set
    typedef DomainT   domain_type;
    /// The codomaintype is the same as domain_type
    typedef DomainT   codomain_type;

    /// The element type of the set
    typedef DomainT   element_type;

    /// The interval type of the set
    typedef ICL_INTERVAL_TYPE(Interval,DomainT,Compare) interval_type;
    /// The segment type of the set
    typedef interval_type   segment_type;

    //--------------------------------------------------------------------------
    //- Associated types: Size
    //--------------------------------------------------------------------------
    /// The difference type of an interval which is sometimes different form the data_type
    typedef typename difference_type_of<domain_type>::type difference_type;

    /// The size type of an interval which is mostly std::size_t
    typedef typename size_type_of<domain_type>::type size_type;


    //--------------------------------------------------------------------------
    //- Associated types: Order
    //--------------------------------------------------------------------------
    /// Comparison functor for domain values
    typedef ICL_COMPARE_DOMAIN(Compare,DomainT)      domain_compare;
    typedef ICL_COMPARE_DOMAIN(Compare,segment_type) segment_compare;
    /// Comparison functor for intervals
    typedef exclusive_less_than<interval_type>       interval_compare;

    /// Comparison functor for keys
    typedef exclusive_less_than<interval_type> key_compare;

    //--------------------------------------------------------------------------
    //- Associated types: Related types
    //--------------------------------------------------------------------------
    /// The atomized type representing the corresponding container of elements
    typedef typename ICL_IMPL_SPACE::set<DomainT,domain_compare,Alloc<DomainT> > atomized_type;

    //--------------------------------------------------------------------------
    //- Associated types: Implementation and stl related
    //--------------------------------------------------------------------------
    /// The allocator type of the set
    typedef Alloc<interval_type> allocator_type;

    /// allocator type of the corresponding element set
    typedef Alloc<DomainT> domain_allocator_type;

    /// Container type for the implementation
    typedef typename ICL_IMPL_SPACE::set<interval_type,key_compare,allocator_type> ImplSetT;

    /// key type of the implementing container
    typedef typename ImplSetT::key_type   key_type;
    /// data type of the implementing container
    typedef typename ImplSetT::key_type   data_type;
    /// value type of the implementing container
    typedef typename ImplSetT::value_type value_type;

    /// pointer type
    typedef typename ImplSetT::pointer         pointer;
    /// const pointer type
    typedef typename ImplSetT::const_pointer   const_pointer;
    /// reference type
    typedef typename ImplSetT::reference       reference;
    /// const reference type
    typedef typename ImplSetT::const_reference const_reference;

    /// iterator for iteration over intervals
    typedef typename ImplSetT::iterator iterator;
    /// const_iterator for iteration over intervals
    typedef typename ImplSetT::const_iterator const_iterator;
    /// iterator for reverse iteration over intervals
    typedef typename ImplSetT::reverse_iterator reverse_iterator;
    /// const_iterator for iteration over intervals
    typedef typename ImplSetT::const_reverse_iterator const_reverse_iterator;

    /// element iterator: Depreciated, see documentation.
    typedef boost::icl::element_iterator<iterator> element_iterator;
    /// element const iterator: Depreciated, see documentation.
    typedef boost::icl::element_iterator<const_iterator> element_const_iterator;
    /// element reverse iterator: Depreciated, see documentation.
    typedef boost::icl::element_iterator<reverse_iterator> element_reverse_iterator;
    /// element const reverse iterator: Depreciated, see documentation.
    typedef boost::icl::element_iterator<const_reverse_iterator> element_const_reverse_iterator;

    BOOST_STATIC_CONSTANT(int, fineness = 0);

public:
    //==========================================================================
    //= Construct, copy, destruct
    //==========================================================================
    /** Default constructor for the empty object */
    interval_base_set(){}

    /** Copy constructor */
    interval_base_set(const interval_base_set& src): _set(src._set)
    {
        BOOST_CONCEPT_ASSERT((DefaultConstructibleConcept<DomainT>));
        BOOST_CONCEPT_ASSERT((LessThanComparableConcept<DomainT>));
    }

#   ifndef BOOST_ICL_NO_CXX11_RVALUE_REFERENCES
    //==========================================================================
    //= Move semantics
    //==========================================================================

    /** Move constructor */
    interval_base_set(interval_base_set&& src): _set(boost::move(src._set))
    {
        BOOST_CONCEPT_ASSERT((DefaultConstructibleConcept<DomainT>));
        BOOST_CONCEPT_ASSERT((LessThanComparableConcept<DomainT>));
    }

    /** Move assignment operator */
    interval_base_set& operator = (interval_base_set src)
    {                           //call by value sice 'src' is a "sink value"
        this->_set = boost::move(src._set);
        return *this;
    }

    //==========================================================================
#   else

    /** Copy assignment operator */
    interval_base_set& operator = (const interval_base_set& src)
    {
        this->_set = src._set;
        return *this;
    }

#   endif // BOOST_ICL_NO_CXX11_RVALUE_REFERENCES

    /** swap the content of containers */
    void swap(interval_base_set& operand) { _set.swap(operand._set); }

    //==========================================================================
    //= Containedness
    //==========================================================================
    /** sets the container empty */
    void clear() { icl::clear(*that()); }
    /** is the container empty? */
    bool empty()const { return icl::is_empty(*that()); }

    //==========================================================================
    //= Size
    //==========================================================================
    /** An interval set's size is it's cardinality */
    size_type size()const
    {
        return icl::cardinality(*that());
    }

    /** Size of the iteration over this container */
    std::size_t iterative_size()const
    {
        return _set.size();
    }

    //==========================================================================
    //= Selection
    //==========================================================================

    /** Find the interval, that contains element \c key_value */
    const_iterator find(const element_type& key_value)const
    {
        return icl::find(*this, key_value);
        //CL return this->_set.find(icl::singleton<segment_type>(key));
    }

    /** Find the first interval, that collides with interval \c key_interval */
    const_iterator find(const interval_type& key_interval)const
    {
        return this->_set.find(key_interval);
    }

    //==========================================================================
    //= Addition
    //==========================================================================

    /** Add a single element \c key to the set */
    SubType& add(const element_type& key)
    {
        return icl::add(*that(), key);
    }

    /** Add an interval of elements \c inter_val to the set */
    SubType& add(const segment_type& inter_val)
    {
        _add(inter_val);
        return *that();
    }

    /** Add an interval of elements \c inter_val to the set. Iterator
        \c prior_ is a hint to the position \c inter_val can be
        inserted after. */
    iterator add(iterator prior_, const segment_type& inter_val)
    {
        return _add(prior_, inter_val);
    }

    //==========================================================================
    //= Subtraction
    //==========================================================================

    /** Subtract a single element \c key from the set */
    SubType& subtract(const element_type& key)
    {
        return icl::subtract(*that(), key);
    }

    /** Subtract an interval of elements \c inter_val from the set */
    SubType& subtract(const segment_type& inter_val);

    //==========================================================================
    //= Insertion
    //==========================================================================
    /** Insert an element \c key into the set */
    SubType& insert(const element_type& key)
    {
        return add(key);
    }

    /** Insert an interval of elements \c inter_val to the set */
    SubType& insert(const segment_type& inter_val)
    {
        return add(inter_val);
    }

    /** Insert an interval of elements \c inter_val to the set. Iterator
        \c prior_ is a hint to the position \c inter_val can be
        inserted after. */
    iterator insert(iterator prior_, const segment_type& inter_val)
    {
        return add(prior_, inter_val);
    }



    //==========================================================================
    //= Erasure
    //==========================================================================
    /** Erase an element \c key from the set */
    SubType& erase(const element_type& key)
    {
        return subtract(key);
    }

    /** Erase an interval of elements \c inter_val from the set */
    SubType& erase(const segment_type& inter_val)
    {
        return subtract(inter_val);
    }

    /** Erase the interval that iterator \c position points to. */
    void erase(iterator position)
    {
        _set.erase(position);
    }

    /** Erase all intervals in the range <tt>[first,past)</tt> of iterators. */
    void erase(iterator first, iterator past)
    {
        _set.erase(first, past);
    }

    //==========================================================================
    //= Symmetric difference
    //==========================================================================
    /** If \c *this set contains \c key it is erased, otherwise it is added. */
    SubType& flip(const element_type& key)
    {
        return icl::flip(*that(), key);
    }

    /** If \c *this set contains \c inter_val it is erased, otherwise it is added. */
    SubType& flip(const segment_type& inter_val)
    {
        return icl::flip(*that(), inter_val);
    }

    //==========================================================================
    //= Iterator related
    //==========================================================================

    iterator begin() { return _set.begin(); }
    iterator end()   { return _set.end(); }
    const_iterator begin()const { return _set.begin(); }
    const_iterator end()const   { return _set.end(); }
    reverse_iterator rbegin() { return _set.rbegin(); }
    reverse_iterator rend()   { return _set.rend(); }
    const_reverse_iterator rbegin()const { return _set.rbegin(); }
    const_reverse_iterator rend()const   { return _set.rend(); }

    iterator lower_bound(const value_type& interval)
    { return _set.lower_bound(interval); }

    iterator upper_bound(const value_type& interval)
    { return _set.upper_bound(interval); }

    const_iterator lower_bound(const value_type& interval)const
    { return _set.lower_bound(interval); }

    const_iterator upper_bound(const value_type& interval)const
    { return _set.upper_bound(interval); }

    std::pair<iterator,iterator> equal_range(const key_type& interval)
    {
        return std::pair<iterator,iterator>
            (_set.lower_bound(interval), _set.upper_bound(interval));
    }

    std::pair<const_iterator,const_iterator>
        equal_range(const key_type& interval)const
    {
        return std::pair<const_iterator,const_iterator>
            (_set.lower_bound(interval), _set.upper_bound(interval));
    }

private:
    iterator _add(const segment_type& addend);
    iterator _add(iterator prior, const segment_type& addend);

protected:
    void add_front(const interval_type& inter_val, iterator& first_);
    void add_main(interval_type& inter_val, iterator& it_, const iterator& last_);
    void add_segment(const interval_type& inter_val, iterator& it_);
    void add_rear(const interval_type& inter_val, iterator& it_);

protected:
    sub_type* that() { return static_cast<sub_type*>(this); }
    const sub_type* that()const { return static_cast<const sub_type*>(this); }

protected:
    ImplSetT _set;
} ;


template <class SubType, class DomainT, ICL_COMPARE Compare, ICL_INTERVAL(ICL_COMPARE) Interval, ICL_ALLOC Alloc>
inline void interval_base_set<SubType,DomainT,Compare,Interval,Alloc>
    ::add_front(const interval_type& inter_val, iterator& first_)
{
    // If the collision sequence has a left residual 'left_resid' it will
    // be split, to provide a standardized start of algorithms:
    // The addend interval 'inter_val' covers the beginning of the collision sequence.

    // only for the first there can be a left_resid: a part of *first_ left of inter_val
    interval_type left_resid = right_subtract(*first_, inter_val);

    if(!icl::is_empty(left_resid))
    {   //            [------------ . . .
        // [left_resid---first_ --- . . .
        iterator prior_ = cyclic_prior(*this, first_);
        const_cast<interval_type&>(*first_) = left_subtract(*first_, left_resid);
        //NOTE: Only splitting
        this->_set.insert(prior_, left_resid);
    }

    //POST:
    // [----- inter_val ---- . . .
    // ...[-- first_ --...
}

template <class SubType, class DomainT, ICL_COMPARE Compare, ICL_INTERVAL(ICL_COMPARE) Interval, ICL_ALLOC Alloc>
inline void interval_base_set<SubType,DomainT,Compare,Interval,Alloc>
    ::add_segment(const interval_type& inter_val, iterator& it_)
{
    interval_type lead_gap = right_subtract(inter_val, *it_);
    if(!icl::is_empty(lead_gap))
        //           [lead_gap--- . . .
        // [prior_)           [-- it_ ...
        this->_set.insert(cyclic_prior(*this, it_), lead_gap);

    // . . . --------- . . . addend interval
    //      [-- it_ --)      has a common part with the first overval
    ++it_;
}

template <class SubType, class DomainT, ICL_COMPARE Compare, ICL_INTERVAL(ICL_COMPARE) Interval, ICL_ALLOC Alloc>
inline void interval_base_set<SubType,DomainT,Compare,Interval,Alloc>
    ::add_main(interval_type& rest_interval, iterator& it_, const iterator& last_)
{
    interval_type cur_interval;
    while(it_ != last_)
    {
        cur_interval = *it_ ;
        add_segment(rest_interval, it_);
        // shrink interval
        rest_interval = left_subtract(rest_interval, cur_interval);
    }
}

template <class SubType, class DomainT, ICL_COMPARE Compare, ICL_INTERVAL(ICL_COMPARE) Interval, ICL_ALLOC Alloc>
inline void interval_base_set<SubType,DomainT,Compare,Interval,Alloc>
    ::add_rear(const interval_type& inter_val, iterator& it_)
{
    iterator prior_ = cyclic_prior(*this, it_);
    interval_type cur_itv = *it_;

    interval_type lead_gap = right_subtract(inter_val, cur_itv);
    if(!icl::is_empty(lead_gap))
        //          [lead_gap--- . . .
        // [prior_)          [-- it_ ...
        this->_set.insert(prior_, lead_gap);

    interval_type end_gap = left_subtract(inter_val, cur_itv);
    if(!icl::is_empty(end_gap))
        // [---------------end_gap)
        //      [-- it_ --)
        it_ = this->_set.insert(it_, end_gap);
    else
    {
        // only for the last there can be a right_resid: a part of *it_ right of addend
        interval_type right_resid = left_subtract(cur_itv, inter_val);

        if(!icl::is_empty(right_resid))
        {
            // [--------------)
            //      [-- it_ --right_resid)
            const_cast<interval_type&>(*it_) = right_subtract(*it_, right_resid);
            it_ = this->_set.insert(it_, right_resid);
        }
    }
}

//==============================================================================
//= Addition
//==============================================================================
template <class SubType, class DomainT, ICL_COMPARE Compare, ICL_INTERVAL(ICL_COMPARE) Interval, ICL_ALLOC Alloc>
inline typename interval_base_set<SubType,DomainT,Compare,Interval,Alloc>::iterator
    interval_base_set<SubType,DomainT,Compare,Interval,Alloc>
    ::_add(const segment_type& addend)
{
    typedef typename interval_base_set<SubType,DomainT,Compare,Interval,Alloc>::iterator iterator;
    if(icl::is_empty(addend))
        return this->_set.end();

    std::pair<iterator,bool> insertion = this->_set.insert(addend);

    if(insertion.second)
        return that()->handle_inserted(insertion.first);
    else
    {
        iterator last_ = prior(this->_set.upper_bound(addend));
        return that()->add_over(addend, last_);
    }
}

template <class SubType, class DomainT, ICL_COMPARE Compare, ICL_INTERVAL(ICL_COMPARE) Interval, ICL_ALLOC Alloc>
inline typename interval_base_set<SubType,DomainT,Compare,Interval,Alloc>::iterator
    interval_base_set<SubType,DomainT,Compare,Interval,Alloc>
    ::_add(iterator prior_, const segment_type& addend)
{
    typedef typename interval_base_set<SubType,DomainT,Compare,Interval,Alloc>::iterator iterator;
    if(icl::is_empty(addend))
        return prior_;

    iterator insertion = this->_set.insert(prior_, addend);

    if(*insertion == addend)
        return that()->handle_inserted(insertion);
    else
    {
        iterator last_ = prior(this->_set.upper_bound(addend));
        return that()->add_over(addend, last_);
    }
}

//==============================================================================
//= Subtraction
//==============================================================================
template <class SubType, class DomainT, ICL_COMPARE Compare, ICL_INTERVAL(ICL_COMPARE) Interval, ICL_ALLOC Alloc>
inline SubType& interval_base_set<SubType,DomainT,Compare,Interval,Alloc>
    ::subtract(const segment_type& minuend)
{
    if(icl::is_empty(minuend))
        return *that();

    std::pair<iterator, iterator> exterior = equal_range(minuend);
    if(exterior.first == exterior.second)
        return *that();

    iterator first_ = exterior.first;
    iterator end_   = exterior.second;
    iterator last_  = prior(end_);

    interval_type left_resid = right_subtract(*first_, minuend);
    interval_type right_resid;
    if(first_ != end_)
        right_resid = left_subtract(*last_ , minuend);

    this->_set.erase(first_, end_);

    if(!icl::is_empty(left_resid))
        this->_set.insert(left_resid);

    if(!icl::is_empty(right_resid))
        this->_set.insert(right_resid);

    return *that();
}

//-----------------------------------------------------------------------------
// type traits
//-----------------------------------------------------------------------------
template<class SubType,
         class DomainT, ICL_COMPARE Compare, ICL_INTERVAL(ICL_COMPARE)  Interval, ICL_ALLOC Alloc>
struct is_set<icl::interval_base_set<SubType,DomainT,Compare,Interval,Alloc> >
{
    typedef is_set<icl::interval_base_set<SubType,DomainT,Compare,Interval,Alloc> > type;
    BOOST_STATIC_CONSTANT(bool, value = true);
};

template<class SubType,
         class DomainT, ICL_COMPARE Compare, ICL_INTERVAL(ICL_COMPARE)  Interval, ICL_ALLOC Alloc>
struct is_interval_container<icl::interval_base_set<SubType,DomainT,Compare,Interval,Alloc> >
{
    typedef is_interval_container<icl::interval_base_set<SubType,DomainT,Compare,Interval,Alloc> > type;
    BOOST_STATIC_CONSTANT(bool, value = true);
};



}} // namespace icl boost

#endif

/* interval_base_set.hpp
KL5k3tWbt+w9/a/GeKaOmpuerdxoKtiDevBiIkbIx3zIqN7cZ6iHnc+oy9GOvPCzI71u/q0tlMZfm8bwFBZGcjjZ3UklatuKAa8As7Zz+R1ZdWeehljSJBYfbeCt+lJ/VdGDFz0a64JZ508qKuw360W1ea4+zkhru3gnhxvR+6mDeRBJR6RddfZXhUPfZeSRT/fvko+7rTd6yMjtI8UrE59V5gTJpYQ8Hrl0P7powfsv56ds5U8U1GtlOgxLgt2JCZPGeSVR0XbWEy+erbqleOxF90Dhwl6NPHJEVBfVZ8MFa8OwSNG1UD7mwZVbjWTBk6JJxKVPKbYVpEFK+PiBDau/TOm6TGrNPli0knFjm5BerVPq71Wb/NmGgeui9eXGttbJfrRLuXd1N8PX1WdHS53XiAzWXri0MFFR84nxR9bOimvve31a2V9diFsSPO6hSo1Qfzl4kfZTDU/cVN9710/Z2XULXZEY9Uj+hv4vJR2Lw46HBBzbcnPbw9qzr+t/DvHdfKZgy7nRxy82fLRq0Sr0qnnpE20nWDbPMd+6JV16ZdVpHuGcHlui9XirZPOJgJUI+7O+B5N0vn1Qk+c8zyfQ+IParGcfLD400f3UZijh2fma7Vvrx1Z7J+wu/9HnaeLJqhuv5gXqDnz8hx7mzmSFtX+4mxOQvdsval6M70l2tk/HroW3UU2935CqrmA/qZ4fdIy2vzgh8ZRaaiXhVvGdQoLRavN5Zj+gWMsf7Dr7mMA7mPce9XUUkymuUu85fIREebqlMPzJGr30m5W3XuNsffMv3y1cmtriiVxJW/IyHXf0hwrUQf6VfjJ/14t9ki2OSbiFq+orcMcC9T5WeXxny8i5rz9YhQhKuWXSub+fFvyLDfez7vPeFsrnzy/7tbn69qkzewpTXg2sZ/pdJvyMjd6G3OghJsbZ6mz8dGNAXN+WqoJFcSf969Rffb+//SOf9wcrjrySa98o/ukHSumilUNLtF70B5bdUMo4ZE/3Wne/sSP6h8W9yy7X6ltZ/3ih28JsX6fiJ8Gf7n6pEHYHscrJ+rKtXevIy3brpPMlGkYNy/eHnfjQ2brI04n/SfvZ/DN5BbtpHYx4Su0mTaPrG35ANEZo7Kp021PIOVsW9d3JKKu1wpL5vslRn525ur7owo/nF4T++oLinXI7cx6TGN9xYdGVhV3VtoIl804XP9DN+QbTt/Ls446Xhfu8jNbe3TUUrP3rln3fn99+7rmxjsvXaK0jh688/fJ04Ln0RWsf5i9h3Mu67h9yeuyQrl6vnd3RLTnFHg+DfIbah4SNN0eXjoZHYxz9iC+TGMU/b0ZuObG1tJ+Qv/eeg2j5xJ6HuZ0W+29UPjb02mmAsvum4/OUr1KQ1x1a2/SMUja28g6w8r9/Whp38vryhSPblsd+I7jTf0TtzsQ3J9zzX+4dzPyh/cElX5GeYHXHCz1jenI2MuAjn1WJg64Kn4/uWtnedy0Syzgd+WwbL7AQXfM4BMvYP1B/yHeP/SN1fq4+3q44P9JRY4QTrDW++ssRteFbuno3zBNHJnzKPrFYhq62P72DluSl9+IG8XyY16WSgE9LL3mpPFi0+5aJTdAHBdbZY+y95/d8/MvlDQ7jIZc5XmZnPZM29Z06Nk8sqA/3vj1/cz89hCr37SGd7yK7J4wywldz8ATivH3l3efcQlpvr/vg2x/Zmt2jZ/2dMj/QSEVevVTddzJi09pD3W6TfnauREuHjpaTZ45d/iWu+g8hL79VXJ3pHm1fG/xz/tX9K4TvaySd/zYmePHzTLJCgi/d/36sctyLFSnex+WanZwu3T25eO28qxZ/OM5A6mFO9DLtvsg5eeB73PyDUZc=
*/