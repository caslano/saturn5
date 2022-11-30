/*-----------------------------------------------------------------------------+
Copyright (c) 2007-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_SEPARATE_INTERVAL_SET_HPP_JOFA_080608
#define BOOST_ICL_SEPARATE_INTERVAL_SET_HPP_JOFA_080608

#include <boost/assert.hpp>
#include <boost/icl/type_traits/is_interval_separator.hpp>
#include <boost/icl/interval_base_set.hpp>
#include <boost/icl/interval_set.hpp>

namespace boost{namespace icl
{

/** \brief Implements a set as a set of intervals - leaving adjoining intervals separate */
template 
<
    typename                         DomainT, 
    ICL_COMPARE                      Compare  = ICL_COMPARE_INSTANCE(ICL_COMPARE_DEFAULT, DomainT),
    ICL_INTERVAL(ICL_COMPARE) Interval = ICL_INTERVAL_INSTANCE(ICL_INTERVAL_DEFAULT, DomainT, Compare),
    ICL_ALLOC                        Alloc    = std::allocator
> 
class separate_interval_set: 
    public interval_base_set<separate_interval_set<DomainT,Compare,Interval,Alloc>,
                             DomainT,Compare,Interval,Alloc>
{
public:
    typedef separate_interval_set<DomainT,Compare,Interval,Alloc> type;

    typedef interval_base_set<type,DomainT,Compare,Interval,Alloc> base_type;

    typedef type overloadable_type;
    typedef type key_object_type;

    typedef interval_set<DomainT,Compare,Interval,Alloc> joint_type;

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

    enum { fineness = 2 };

public:
    //==========================================================================
    //= Construct, copy, destruct
    //==========================================================================
    /// Default constructor for the empty object
    separate_interval_set(): base_type() {}
    /// Copy constructor
    separate_interval_set(const separate_interval_set& src): base_type(src) {}

    /// Copy constructor for base_type
    template<class SubType>
    separate_interval_set
        (const interval_base_set<SubType,DomainT,Compare,Interval,Alloc>& src)
    { 
        this->assign(src); 
    }

    /// Constructor for a single element
    explicit separate_interval_set(const domain_type& elem): base_type() { this->add(elem); }
    /// Constructor for a single interval
    explicit separate_interval_set(const interval_type& itv): base_type() { this->add(itv); }

    /// Assignment from a base interval_set.
    template<class SubType>
    void assign(const interval_base_set<SubType,DomainT,Compare,Interval,Alloc>& src)
    {
        this->clear();
        this->_set.insert(src.begin(), src.end());
    }

    /// Assignment operator for base type
    template<class SubType>
    separate_interval_set& operator =
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
    separate_interval_set(separate_interval_set&& src)
        : base_type(boost::move(src))
    {}

    /// Move assignment operator
    separate_interval_set& operator = (separate_interval_set src)
    { 
        base_type::operator=(boost::move(src));
        return *this;
    }
    //==========================================================================
#   else

    /// Assignment operator
    separate_interval_set& operator = (const separate_interval_set& src)
    { 
        base_type::operator=(src);
        return *this;
    }

#   endif // BOOST_ICL_NO_CXX11_RVALUE_REFERENCES

private:
    // Private functions that shall be accessible by the baseclass:
    friend class
        interval_base_set<separate_interval_set<DomainT,Compare,Interval,Alloc>, 
                                                DomainT,Compare,Interval,Alloc>;

    iterator handle_inserted(iterator inserted_)
    { 
        return inserted_; 
    }

    iterator add_over(const interval_type& addend, iterator last_)
    {
        return segmental::join_under(*this, addend, last_);
    }

    iterator add_over(const interval_type& addend)
    {
        return segmental::join_under(*this, addend);
    }

} ;



//-----------------------------------------------------------------------------
// type traits
//-----------------------------------------------------------------------------
template <class DomainT, ICL_COMPARE Compare, ICL_INTERVAL(ICL_COMPARE)  Interval, ICL_ALLOC Alloc>
struct is_set<icl::separate_interval_set<DomainT,Compare,Interval,Alloc> >
{ 
    typedef is_set<icl::separate_interval_set<DomainT,Compare,Interval,Alloc> > type;
    BOOST_STATIC_CONSTANT(bool, value = true); 
};

template <class DomainT, ICL_COMPARE Compare, ICL_INTERVAL(ICL_COMPARE)  Interval, ICL_ALLOC Alloc>
struct is_interval_container<icl::separate_interval_set<DomainT,Compare,Interval,Alloc> >
{ 
    typedef is_interval_container<icl::separate_interval_set<DomainT,Compare,Interval,Alloc> > type;
    BOOST_STATIC_CONSTANT(bool, value = true); 
};

template <class DomainT, ICL_COMPARE Compare, ICL_INTERVAL(ICL_COMPARE)  Interval, ICL_ALLOC Alloc>
struct is_interval_separator<icl::separate_interval_set<DomainT,Compare,Interval,Alloc> >
{ 
    typedef is_interval_separator<icl::separate_interval_set<DomainT,Compare,Interval,Alloc> > type;
    BOOST_STATIC_CONSTANT(bool, value = true); 
};

//-----------------------------------------------------------------------------
// type representation
//-----------------------------------------------------------------------------
template <class DomainT, ICL_COMPARE Compare, ICL_INTERVAL(ICL_COMPARE)  Interval, ICL_ALLOC Alloc>
struct type_to_string<icl::separate_interval_set<DomainT,Compare,Interval,Alloc> >
{
    static std::string apply()
    { return "se_itv_set<"+ type_to_string<DomainT>::apply() +">"; }
};

}} // namespace icl boost

#endif



/* separate_interval_set.hpp
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
*/