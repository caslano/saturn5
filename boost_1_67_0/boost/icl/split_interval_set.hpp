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