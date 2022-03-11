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