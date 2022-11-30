/*-----------------------------------------------------------------------------+
Copyright (c) 2007-2012: Joachim Faulhaber
Copyright (c) 1999-2006: Cortex Software GmbH, Kantstrasse 57, Berlin
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_SPLIT_INTERVAL_MAP_HPP_JOFA_000706
#define BOOST_ICL_SPLIT_INTERVAL_MAP_HPP_JOFA_000706

#include <boost/icl/interval_set.hpp>
#include <boost/icl/interval_map.hpp>
#include <boost/icl/interval_base_map.hpp>
#include <boost/icl/split_interval_set.hpp>

namespace boost{namespace icl
{

/** \brief implements a map as a map of intervals - on insertion 
    overlapping intervals are split and associated values are combined. */
template
<
    typename DomainT,
    typename CodomainT,
    class Traits = icl::partial_absorber,
    ICL_COMPARE Compare  = ICL_COMPARE_INSTANCE(ICL_COMPARE_DEFAULT, DomainT),
    ICL_COMBINE Combine  = ICL_COMBINE_INSTANCE(icl::inplace_plus, CodomainT),
    ICL_SECTION Section  = ICL_SECTION_INSTANCE(icl::inter_section, CodomainT), 
    ICL_INTERVAL(ICL_COMPARE) Interval = ICL_INTERVAL_INSTANCE(ICL_INTERVAL_DEFAULT, DomainT, Compare),
    ICL_ALLOC   Alloc    = std::allocator
>
class split_interval_map:
    public interval_base_map<split_interval_map<DomainT,CodomainT,Traits,Compare,Combine,Section,Interval,Alloc>, 
                             DomainT,CodomainT,Traits,Compare,Combine,Section,Interval,Alloc>
{
public:
    typedef Traits traits;
    typedef split_interval_map<DomainT,CodomainT,Traits,Compare,Combine,Section,Interval,Alloc> type;
    typedef       interval_map<DomainT,CodomainT,Traits,Compare,Combine,Section,Interval,Alloc> joint_type;
    typedef type overloadable_type;

    typedef interval_base_map <type, 
                               DomainT,CodomainT,Traits,Compare,Combine,Section,Interval,Alloc> base_type;

    typedef DomainT domain_type;
    typedef CodomainT codomain_type;
    typedef ICL_INTERVAL_TYPE(Interval,DomainT,Compare) interval_type;
    typedef typename base_type::iterator iterator;
    typedef typename base_type::value_type value_type;
    typedef typename base_type::element_type element_type;
    typedef typename base_type::segment_type segment_type;
    typedef typename base_type::domain_mapping_type    domain_mapping_type;
    typedef typename base_type::interval_mapping_type  interval_mapping_type;
    typedef typename base_type::ImplMapT ImplMapT;

    typedef typename base_type::codomain_combine codomain_combine;

    typedef interval_set<DomainT,Compare,Interval,Alloc> interval_set_type;
    typedef interval_set_type set_type;
    typedef set_type          key_object_type;

    enum { fineness = 3 };

public:
    //==========================================================================
    //= Construct, copy, destruct
    //==========================================================================
    /// Default constructor for the empty object
    split_interval_map(): base_type() {}

    /// Copy constructor
    split_interval_map(const split_interval_map& src): base_type(src) {}

    explicit split_interval_map(const domain_mapping_type& base_pair): base_type()
    { this->add(base_pair); }

    explicit split_interval_map(const value_type& value_pair): base_type()
    { this->add(value_pair); }

    /// Assignment from a base interval_map.
    template<class SubType>
    void assign(const interval_base_map<SubType,DomainT,CodomainT,
                                        Traits,Compare,Combine,Section,Interval,Alloc>& src)
    {
        this->clear();
        this->_map.insert(src.begin(), src.end());
    }

    /// Assignment operator for base type
    template<class SubType>
    split_interval_map& operator =
        (const interval_base_map<SubType,DomainT,CodomainT,
                                 Traits,Compare,Combine,Section,Interval,Alloc>& src)
    { 
        this->assign(src); 
        return *this; 
    }

#   ifndef BOOST_ICL_NO_CXX11_RVALUE_REFERENCES
    //==========================================================================
    //= Move semantics
    //==========================================================================

    /// Move constructor
    split_interval_map(split_interval_map&& src)
        : base_type(boost::move(src))
    {}

    /// Move assignment operator
    split_interval_map& operator = (split_interval_map src)
    { 
        base_type::operator=(boost::move(src));
        return *this;
    }

    //==========================================================================
#   else

    /// Assignment operator
    split_interval_map& operator = (const split_interval_map& src)
    { 
        base_type::operator=(src);
        return *this;
    }

#   endif // BOOST_ICL_NO_CXX11_RVALUE_REFERENCES

private:
    // Private functions that shall be accessible by the baseclass:
    friend class
        interval_base_map <split_interval_map<DomainT,CodomainT,Traits,Compare,Combine,Section,Interval,Alloc>, 
                                              DomainT,CodomainT,Traits,Compare,Combine,Section,Interval,Alloc>;

    iterator handle_inserted(iterator it_)const { return it_; }
    void handle_inserted(iterator, iterator)const{ }

    template<class Combiner>
    void handle_left_combined(iterator it_)
    {
        if(on_absorbtion<type,Combiner,Traits::absorbs_identities>::is_absorbable((*it_).second))
            this->_map.erase(it_);
    }

    template<class Combiner>
    void handle_combined(iterator it_)
    {
        if(on_absorbtion<type,Combiner,Traits::absorbs_identities>::is_absorbable((*it_).second))
            this->_map.erase(it_);
    }

    template<class Combiner>
    void handle_preceeded_combined(iterator prior_, iterator& it_)
    {
        if(on_absorbtion<type,Combiner,Traits::absorbs_identities>::is_absorbable((*it_).second))
        {
            this->_map.erase(it_);
            it_ = prior_;
        }
    }

    template<class Combiner>
    void handle_succeeded_combined(iterator it_, iterator)
    {
        if(on_absorbtion<type,Combiner,Traits::absorbs_identities>::is_absorbable((*it_).second))
            this->_map.erase(it_);
    }

    void handle_reinserted(iterator){}

    template<class Combiner>
    void gap_insert_at(iterator& it_, iterator prior_, 
                       const interval_type& end_gap, const codomain_type& co_val)
    {
        if(on_absorbtion<type,Combiner,Traits::absorbs_identities>::is_absorbable((*it_).second))
        {
            this->_map.erase(it_);
            it_ = this->template gap_insert<Combiner>(prior_, end_gap, co_val);
        }
        else
            it_ = this->template gap_insert<Combiner>(it_, end_gap, co_val);
    }
} ;

//-----------------------------------------------------------------------------
// type traits
//-----------------------------------------------------------------------------
template <class DomainT, class CodomainT, class Traits, ICL_COMPARE Compare, ICL_COMBINE Combine, ICL_SECTION Section, ICL_INTERVAL(ICL_COMPARE)  Interval, ICL_ALLOC Alloc>
struct is_map<icl::split_interval_map<DomainT,CodomainT,Traits,Compare,Combine,Section,Interval,Alloc> >
{ 
    typedef is_map<icl::split_interval_map<DomainT,CodomainT,Traits,Compare,Combine,Section,Interval,Alloc> > type;
    BOOST_STATIC_CONSTANT(bool, value = true); 
};

template <class DomainT, class CodomainT, class Traits, ICL_COMPARE Compare, ICL_COMBINE Combine, ICL_SECTION Section, ICL_INTERVAL(ICL_COMPARE)  Interval, ICL_ALLOC Alloc>
struct has_inverse<icl::split_interval_map<DomainT,CodomainT,Traits,Compare,Combine,Section,Interval,Alloc> >
{ 
    typedef has_inverse<icl::split_interval_map<DomainT,CodomainT,Traits,Compare,Combine,Section,Interval,Alloc> > type;
    BOOST_STATIC_CONSTANT(bool, value = (has_inverse<CodomainT>::value)); 
};

template <class DomainT, class CodomainT, class Traits, ICL_COMPARE Compare, ICL_COMBINE Combine, ICL_SECTION Section, ICL_INTERVAL(ICL_COMPARE)  Interval, ICL_ALLOC Alloc>
struct is_interval_container<icl::split_interval_map<DomainT,CodomainT,Traits,Compare,Combine,Section,Interval,Alloc> >
{ 
    typedef is_interval_container<icl::split_interval_map<DomainT,CodomainT,Traits,Compare,Combine,Section,Interval,Alloc> > type;
    BOOST_STATIC_CONSTANT(bool, value = true); 
};

template <class DomainT, class CodomainT, class Traits, ICL_COMPARE Compare, ICL_COMBINE Combine, ICL_SECTION Section, ICL_INTERVAL(ICL_COMPARE)  Interval, ICL_ALLOC Alloc>
struct is_interval_splitter<icl::split_interval_map<DomainT,CodomainT,Traits,Compare,Combine,Section,Interval,Alloc> >
{ 
    typedef is_interval_splitter<icl::split_interval_map<DomainT,CodomainT,Traits,Compare,Combine,Section,Interval,Alloc> > type;
    BOOST_STATIC_CONSTANT(bool, value = true); 
};

template <class DomainT, class CodomainT, class Traits, ICL_COMPARE Compare, ICL_COMBINE Combine, ICL_SECTION Section, ICL_INTERVAL(ICL_COMPARE)  Interval, ICL_ALLOC Alloc>
struct absorbs_identities<icl::split_interval_map<DomainT,CodomainT,Traits,Compare,Combine,Section,Interval,Alloc> >
{ 
    typedef absorbs_identities<icl::split_interval_map<DomainT,CodomainT,Traits,Compare,Combine,Section,Interval,Alloc> > type;
    BOOST_STATIC_CONSTANT(bool, value = (Traits::absorbs_identities)); 
};

template <class DomainT, class CodomainT, class Traits, ICL_COMPARE Compare, ICL_COMBINE Combine, ICL_SECTION Section, ICL_INTERVAL(ICL_COMPARE)  Interval, ICL_ALLOC Alloc>
struct is_total<icl::split_interval_map<DomainT,CodomainT,Traits,Compare,Combine,Section,Interval,Alloc> >
{ 
    typedef is_total<icl::split_interval_map<DomainT,CodomainT,Traits,Compare,Combine,Section,Interval,Alloc> > type;
    BOOST_STATIC_CONSTANT(bool, value = (Traits::is_total)); 
};


template <class DomainT, class CodomainT, class Traits, ICL_COMPARE Compare, ICL_COMBINE Combine, ICL_SECTION Section, ICL_INTERVAL(ICL_COMPARE)  Interval, ICL_ALLOC Alloc>
struct type_to_string<icl::split_interval_map<DomainT,CodomainT,Traits,Compare,Combine,Section,Interval,Alloc> >
{
    static std::string apply()
    { 
        return "sp_itv_map<"+ type_to_string<DomainT>::apply()   + ","
                            + type_to_string<CodomainT>::apply() + ","
                            + type_to_string<Traits>::apply()    +">"; 
    }
};

}} // namespace icl boost

#endif



/* split_interval_map.hpp
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
*/