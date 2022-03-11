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