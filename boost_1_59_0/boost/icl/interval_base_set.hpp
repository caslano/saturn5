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
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
*/