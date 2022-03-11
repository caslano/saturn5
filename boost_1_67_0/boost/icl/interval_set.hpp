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