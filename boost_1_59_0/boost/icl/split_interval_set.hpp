/*-----------------------------------------------------------------------------+
Copyright (c) 2007-2009: Joachim Faulhaber
Copyright (c) 1999-2006: Cortex Software GmbH, Kantstrasse 57, Berlin
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_SPLIT_INTERVAL_SET_HPP_JOFA_990223
#define BOOST_ICL_SPLIT_INTERVAL_SET_HPP_JOFA_990223

#include <boost/icl/type_traits/is_interval_splitter.hpp>
#include <boost/icl/interval_base_set.hpp>
#include <boost/icl/interval_set.hpp>

namespace boost{namespace icl
{

/** \brief implements a set as a set of intervals - on insertion 
    overlapping intervals are split */
template 
<
    typename                  DomainT, 
    ICL_COMPARE               Compare  = ICL_COMPARE_INSTANCE(ICL_COMPARE_DEFAULT, DomainT),
    ICL_INTERVAL(ICL_COMPARE) Interval = ICL_INTERVAL_INSTANCE(ICL_INTERVAL_DEFAULT, DomainT, Compare),
    ICL_ALLOC                 Alloc    = std::allocator
> 
class split_interval_set: 
    public interval_base_set<split_interval_set<DomainT,Compare,Interval,Alloc>, 
                             DomainT,Compare,Interval,Alloc>
{
public:
    typedef split_interval_set<DomainT,Compare,Interval,Alloc> type;
    typedef interval_base_set<type,DomainT,Compare,Interval,Alloc> base_type;

    typedef interval_set<DomainT,Compare,Interval,Alloc> joint_type;
    typedef type overloadable_type;
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

    enum { fineness = 3 };

public:
    //==========================================================================
    //= Construct, copy, destruct
    //==========================================================================
    /// Default constructor for the empty object
    split_interval_set(): base_type() {}

    /// Copy constructor
    split_interval_set(const split_interval_set& src): base_type(src) {}

    /// Copy constructor for base_type
    template<class SubType>
    split_interval_set
        (const interval_base_set<SubType,DomainT,Compare,Interval,Alloc>& src)
    { this->assign(src); }

    /// Constructor for a single element
    explicit split_interval_set(const interval_type& elem): base_type() { this->add(elem); }
    /// Constructor for a single interval
    explicit split_interval_set(const domain_type& itv): base_type() { this->add(itv); }

    /// Assignment from a base interval_set.
    template<class SubType>
    void assign(const interval_base_set<SubType,DomainT,Compare,Interval,Alloc>& src)
    {
        this->clear();
        this->_set.insert(src.begin(), src.end());
    }

    /// Assignment operator for base type
    template<class SubType>
    split_interval_set& operator =
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
    split_interval_set(split_interval_set&& src)
        : base_type(boost::move(src))
    {}

    /// Move assignment operator
    split_interval_set& operator = (split_interval_set src)
    { 
        base_type::operator=(boost::move(src));
        return *this;
    }
    //==========================================================================
#   else

    /// Assignment operator
    split_interval_set& operator = (const split_interval_set& src)
    { 
        base_type::operator=(src);
        return *this;
    }

#   endif // BOOST_ICL_NO_CXX11_RVALUE_REFERENCES
    
private:
    // Private functions that shall be accessible by the baseclass:
    friend class
        interval_base_set<split_interval_set<DomainT,Compare,Interval,Alloc>, 
                                             DomainT,Compare,Interval,Alloc>;

    iterator handle_inserted(iterator inserted_)
    { 
        return inserted_; 
    }

    iterator add_over(const interval_type& addend, iterator last_)
    {
        iterator first_ = this->_set.lower_bound(addend);
        //BOOST_ASSERT(next(last_) == this->_set.upper_bound(inter_val));

        iterator it_ = first_;
        interval_type rest_interval = addend;

        this->add_front(rest_interval, it_);
        this->add_main (rest_interval, it_, last_);
        this->add_rear (rest_interval, it_);
        return it_;
    }

    iterator add_over(const interval_type& addend)
    {
        std::pair<iterator,iterator> overlap = this->equal_range(addend);
        iterator first_ = overlap.first,
                 end_   = overlap.second,
                 last_  = end_; --last_;

        iterator it_ = first_;
        interval_type rest_interval = addend;

        this->add_front(rest_interval, it_);
        this->add_main (rest_interval, it_, last_);
        this->add_rear (rest_interval, it_);

        return it_;
    }

} ;


//-----------------------------------------------------------------------------
// type traits
//-----------------------------------------------------------------------------
template <class DomainT, ICL_COMPARE Compare, ICL_INTERVAL(ICL_COMPARE)  Interval, ICL_ALLOC Alloc>
struct is_set<icl::split_interval_set<DomainT,Compare,Interval,Alloc> >
{ 
    typedef is_set<icl::split_interval_set<DomainT,Compare,Interval,Alloc> > type;
    BOOST_STATIC_CONSTANT(bool, value = true); 
};

template <class DomainT, ICL_COMPARE Compare, ICL_INTERVAL(ICL_COMPARE)  Interval, ICL_ALLOC Alloc>
struct is_interval_container<icl::split_interval_set<DomainT,Compare,Interval,Alloc> >
{ 
    typedef is_interval_container<icl::split_interval_set<DomainT,Compare,Interval,Alloc> > type;
    BOOST_STATIC_CONSTANT(bool, value = true); 
};

template <class DomainT, ICL_COMPARE Compare, ICL_INTERVAL(ICL_COMPARE)  Interval, ICL_ALLOC Alloc>
struct is_interval_splitter<icl::split_interval_set<DomainT,Compare,Interval,Alloc> >
{ 
    typedef is_interval_splitter<icl::split_interval_set<DomainT,Compare,Interval,Alloc> > type;
    BOOST_STATIC_CONSTANT(bool, value = true);
};

//-----------------------------------------------------------------------------
// type representation
//-----------------------------------------------------------------------------
template <class DomainT, ICL_COMPARE Compare, ICL_INTERVAL(ICL_COMPARE)  Interval, ICL_ALLOC Alloc>
struct type_to_string<icl::split_interval_set<DomainT,Compare,Interval,Alloc> >
{
    static std::string apply()
    { return "sp_itv_set<"+ type_to_string<DomainT>::apply() +">"; }
};


}} // namespace icl boost

#endif // BOOST_ICL_SPLIT_INTERVAL_SET_HPP_JOFA_990223




/* split_interval_set.hpp
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
*/