/*-----------------------------------------------------------------------------+
Copyright (c) 2007-2010: Joachim Faulhaber
Copyright (c) 1999-2006: Cortex Software GmbH, Kantstrasse 57, Berlin
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_INTERVAL_SET_HPP_JOFA_990223
#define BOOST_ICL_INTERVAL_SET_HPP_JOFA_990223

#include <boost/assert.hpp>
#include <boost/icl/type_traits/is_interval_joiner.hpp>
#include <boost/icl/interval_base_set.hpp>

namespace boost{namespace icl
{

/** \brief Implements a set as a set of intervals - merging adjoining intervals */
template 
<
    typename    DomainT, 
    ICL_COMPARE Compare  = ICL_COMPARE_INSTANCE(ICL_COMPARE_DEFAULT, DomainT),
    ICL_INTERVAL(ICL_COMPARE) Interval = ICL_INTERVAL_INSTANCE(ICL_INTERVAL_DEFAULT, DomainT, Compare),
    ICL_ALLOC   Alloc    = std::allocator
> 
class interval_set: 
    public interval_base_set<interval_set<DomainT,Compare,Interval,Alloc>,
                             DomainT,Compare,Interval,Alloc>
{
public:

    typedef interval_set<DomainT,Compare,Interval,Alloc> type;

    /// The base_type of this class
    typedef interval_base_set<type,DomainT,Compare,Interval,Alloc> base_type;

    typedef type overloadable_type;

    typedef type joint_type;

    typedef type key_object_type;

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

    /// Comparison functor for domain values
    typedef ICL_COMPARE_DOMAIN(Compare,DomainT) domain_compare;
    /// Comparison functor for intervals
    typedef exclusive_less_than<interval_type> interval_compare;

    /// Comparison functor for keys
    typedef exclusive_less_than<interval_type> key_compare;

    /// The allocator type of the set
    typedef Alloc<interval_type> allocator_type;

    /// allocator type of the corresponding element set
    typedef Alloc<DomainT> domain_allocator_type;

    /// The corresponding atomized type representing this interval container of elements
    typedef typename base_type::atomized_type atomized_type;

    /// Container type for the implementation 
    typedef typename base_type::ImplSetT ImplSetT;

    /// key type of the implementing container
    typedef typename ImplSetT::key_type   key_type;
    /// data type of the implementing container
    typedef typename ImplSetT::value_type data_type;
    /// value type of the implementing container
    typedef typename ImplSetT::value_type value_type;

    /// iterator for iteration over intervals
    typedef typename ImplSetT::iterator iterator;
    /// const_iterator for iteration over intervals
    typedef typename ImplSetT::const_iterator const_iterator;

    enum { fineness = 1 };

public:
    //==========================================================================
    //= Construct, copy, destruct
    //==========================================================================
    /// Default constructor for the empty object
    interval_set(): base_type() {}

    /// Copy constructor
    interval_set(const interval_set& src): base_type(src) {}

    /// Copy constructor for base_type
    template<class SubType>
    explicit interval_set
        (const interval_base_set<SubType,DomainT,Compare,Interval,Alloc>& src)
    { 
        this->assign(src); 
    }

    /// Constructor for a single element
    explicit interval_set(const domain_type& value): base_type() 
    { this->add(interval_type(value)); }

    /// Constructor for a single interval
    explicit interval_set(const interval_type& itv): base_type() 
    { 
        this->add(itv); 
    }

    /// Assignment from a base interval_set.
    template<class SubType>
    void assign(const interval_base_set<SubType,DomainT,Compare,Interval,Alloc>& src)
    {
        typedef interval_base_set<SubType,DomainT,Compare,Interval,Alloc> base_set_type;
        this->clear();
        // Has to be implemented via add. there might be touching borders to be joined
        iterator prior_ = this->_set.end();
        ICL_const_FORALL(typename base_set_type, it_, src) 
            prior_ = this->add(prior_, *it_);
    }

    /// Assignment operator for base type
    template<class SubType>
    interval_set& operator =
        (const interval_base_set<SubType,DomainT,Compare,Interval,Alloc>& src)
    { 
        this->assign(src); 
        return *this; 
    }

#   ifndef BOOST_ICL_NO_CXX11_RVALUE_REFERENCES
    //==========================================================================
    //= Move semantics
    //==========================================================================

    /// Move constructor
    interval_set(interval_set&& src)
        : base_type(boost::move(src))
    {}

    /// Move assignment operator
    interval_set& operator = (interval_set src)
    { 
        base_type::operator=(boost::move(src));
        return *this;
    }

    //==========================================================================
#   else
    /// Assignment operator
    interval_set& operator = (const interval_set& src)
    { 
        base_type::operator=(src);
        return *this;
    }

#   endif // BOOST_ICL_NO_CXX11_RVALUE_REFERENCES

private:
    // Private functions that shall be accessible by the baseclass:
    friend class
        interval_base_set <interval_set<DomainT,Compare,Interval,Alloc>, 
                                        DomainT,Compare,Interval,Alloc>;

    iterator handle_inserted(iterator it_)
    {
        return segmental::join_neighbours(*this, it_); 
    }

    iterator add_over(const interval_type& addend, iterator last_)
    {
        iterator joined_ = segmental::join_under(*this, addend, last_);
        return segmental::join_neighbours(*this, joined_);
    }

    iterator add_over(const interval_type& addend)
    {
        iterator joined_ = segmental::join_under(*this, addend);
        return segmental::join_neighbours(*this, joined_);
    }

} ;


//-----------------------------------------------------------------------------
// type traits
//-----------------------------------------------------------------------------
template <class DomainT, ICL_COMPARE Compare, ICL_INTERVAL(ICL_COMPARE)  Interval, ICL_ALLOC Alloc>
struct is_set<icl::interval_set<DomainT,Compare,Interval,Alloc> >
{ 
    typedef is_set<icl::interval_set<DomainT,Compare,Interval,Alloc> > type;
    BOOST_STATIC_CONSTANT(bool, value = true); 
};

template <class DomainT, ICL_COMPARE Compare, ICL_INTERVAL(ICL_COMPARE)  Interval, ICL_ALLOC Alloc>
struct is_interval_container<icl::interval_set<DomainT,Compare,Interval,Alloc> >
{ 
    typedef is_interval_container<icl::interval_set<DomainT,Compare,Interval,Alloc> > type;
    BOOST_STATIC_CONSTANT(bool, value = true); 
};

template <class DomainT, ICL_COMPARE Compare, ICL_INTERVAL(ICL_COMPARE)  Interval, ICL_ALLOC Alloc>
struct is_interval_joiner<icl::interval_set<DomainT,Compare,Interval,Alloc> >
{ 
    typedef is_interval_joiner<icl::interval_set<DomainT,Compare,Interval,Alloc> > type;
    BOOST_STATIC_CONSTANT(bool, value = true); 
};


//-----------------------------------------------------------------------------
// type representation
//-----------------------------------------------------------------------------
template <class DomainT, ICL_COMPARE Compare, ICL_INTERVAL(ICL_COMPARE)  Interval, ICL_ALLOC Alloc>
struct type_to_string<icl::interval_set<DomainT,Compare,Interval,Alloc> >
{
    static std::string apply()
    { return "itv_set<"+ type_to_string<DomainT>::apply() +">"; }
};

}} // namespace icl boost

#endif



/* interval_set.hpp
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
*/