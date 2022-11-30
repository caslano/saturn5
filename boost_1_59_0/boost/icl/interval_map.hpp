/*-----------------------------------------------------------------------------+
Copyright (c) 2008-2012: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_INTERVAL_MAP_HPP_JOFA_080705
#define BOOST_ICL_INTERVAL_MAP_HPP_JOFA_080705

#include <boost/assert.hpp>
#include <boost/icl/type_traits/is_map.hpp>
#include <boost/icl/interval_set.hpp>
#include <boost/icl/interval_base_map.hpp>

namespace boost{namespace icl
{

template<class DomainT, class CodomainT, class Traits, 
         ICL_COMPARE Compare, ICL_COMBINE Combine, ICL_SECTION Section, 
         ICL_INTERVAL(ICL_COMPARE)  Interval, ICL_ALLOC Alloc>
class split_interval_map;

/** \brief implements a map as a map of intervals - on insertion 
    overlapping intervals are split and associated values are combined.*/
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
class interval_map:

    public interval_base_map<interval_map<DomainT,CodomainT,Traits,Compare,Combine,Section,Interval,Alloc>, 
                             DomainT,CodomainT,Traits,Compare,Combine,Section,Interval,Alloc>
{
public:
    typedef Traits traits;
    typedef       interval_map<DomainT,CodomainT,Traits,Compare,Combine,Section,Interval,Alloc> type;
    typedef split_interval_map<DomainT,CodomainT,Traits,Compare,Combine,Section,Interval,Alloc> split_type;
    typedef type overloadable_type;
    typedef type joint_type;
    typedef interval_base_map<type, 
                              DomainT,CodomainT,Traits,Compare,Combine,Section,Interval,Alloc> base_type;

    typedef ICL_INTERVAL_TYPE(Interval,DomainT,Compare) interval_type;
    typedef typename base_type::iterator      iterator;
    typedef typename base_type::value_type    value_type;
    typedef typename base_type::element_type  element_type;
    typedef typename base_type::segment_type  segment_type;
    typedef typename base_type::domain_type   domain_type;
    typedef typename base_type::codomain_type codomain_type;
    typedef typename base_type::domain_mapping_type domain_mapping_type;
    typedef typename base_type::interval_mapping_type interval_mapping_type;
    typedef typename base_type::ImplMapT ImplMapT;

    typedef typename base_type::size_type     size_type;
    typedef typename base_type::codomain_combine codomain_combine;

    typedef interval_set<DomainT,Compare,Interval,Alloc> interval_set_type;
    typedef interval_set_type set_type;
    typedef set_type          key_object_type;

    enum { fineness = 1 };

public:
    //==========================================================================
    //= Construct, copy, destruct
    //==========================================================================

    /// Default constructor for the empty object
    interval_map(): base_type() {}

    /// Copy constructor
    interval_map(const interval_map& src): base_type(src) {}

    /// Copy constructor for base_type
    template<class SubType>
    explicit interval_map
        (const interval_base_map<SubType,DomainT,CodomainT,
                                 Traits,Compare,Combine,Section,Interval,Alloc>& src)
    { this->assign(src); }

    explicit interval_map(const domain_mapping_type& base_pair): base_type()
    { this->add(base_pair); }

    explicit interval_map(const value_type& value_pair): base_type()
    { this->add(value_pair); }


    /// Assignment from a base interval_map.
    template<class SubType>
    void assign(const interval_base_map<SubType,DomainT,CodomainT,
                                        Traits,Compare,Combine,Section,Interval,Alloc>& src)
    {
        typedef interval_base_map<SubType,DomainT,CodomainT,
                                  Traits,Compare,Combine,Section,Interval,Alloc> base_map_type;
        this->clear();
        iterator prior_ = this->_map.end();
        ICL_const_FORALL(typename base_map_type, it_, src) 
            prior_ = this->add(prior_, *it_); 
    }

    /// Assignment operator for base type
    template<class SubType>
    interval_map& operator =
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
    interval_map(interval_map&& src)
        : base_type(boost::move(src))
    {}

    /// Move assignment operator
    interval_map& operator = (interval_map src)
    { 
        base_type::operator=(boost::move(src));
        return *this;
    }

    //==========================================================================
#   else

    /// Assignment operator
    interval_map& operator = (const interval_map& src)
    { 
        base_type::operator=(src);
        return *this;
    }

#   endif // BOOST_ICL_NO_CXX11_RVALUE_REFERENCES

private:
    // Private functions that shall be accessible by the baseclass:
    friend class
        interval_base_map <interval_map<DomainT,CodomainT,Traits,Compare,Combine,Section,Interval,Alloc>, 
                                        DomainT,CodomainT,Traits,Compare,Combine,Section,Interval,Alloc>;

    iterator handle_inserted(iterator it_)
    {
        return segmental::join_neighbours(*this, it_); 
    }

    void handle_inserted(iterator prior_, iterator it_)
    {
        if(prior_ != this->_map.end() && segmental::joinable(*this, prior_, it_))
            segmental::join_on_right(*this, prior_, it_);
    }

    template<class Combiner>
    void handle_left_combined(iterator it_)
    {
        if(on_absorbtion<type,Combiner,Traits::absorbs_identities>::is_absorbable((*it_).second))
            this->_map.erase(it_);
        else
            segmental::join_left(*this, it_);
    }

    template<class Combiner>
    void handle_combined(iterator it_)
    {
        if(on_absorbtion<type,Combiner,Traits::absorbs_identities>::is_absorbable((*it_).second))
            this->_map.erase(it_);
        else
            segmental::join_neighbours(*this, it_);
    }

    template<class Combiner>
    void handle_preceeded_combined(iterator prior_, iterator& it_)
    {
        if(on_absorbtion<type,Combiner,Traits::absorbs_identities>::is_absorbable((*it_).second))
        {
            this->_map.erase(it_);
            it_ = prior_;
        }
        else // After a new combination (e.g. combiner=max) joining neighbours may be possible
            segmental::join_neighbours(*this, it_);
    }

    template<class Combiner>
    void handle_succeeded_combined(iterator it_, iterator next_)
    {
        if(on_absorbtion<type,Combiner,Traits::absorbs_identities>::is_absorbable((*it_).second))
        {
            this->_map.erase(it_);
            segmental::join_right(*this, next_);
        }
        else
        {
            segmental::join_left(*this, it_);
            segmental::join_neighbours(*this, next_);
        }
    }



    void handle_reinserted(iterator insertion_)
    { 
        segmental::join_right(*this, insertion_); 
    }


    template<class Combiner>
    void gap_insert_at(iterator& it_, iterator prior_, 
                       const interval_type& end_gap, const codomain_type& co_val)
    {
        if(on_absorbtion<type,Combiner,Traits::absorbs_identities>::is_absorbable((*it_).second))
        {
            this->_map.erase(it_);
            it_ = this->template gap_insert<Combiner>(prior_, end_gap, co_val);
            segmental::join_right(*this, it_);
        }
        else 
        {
            segmental::join_left(*this, it_);
            iterator inserted_ = this->template gap_insert<Combiner>(it_, end_gap, co_val);
            it_ = segmental::join_neighbours(*this, inserted_);
        }
    }

} ;


//-----------------------------------------------------------------------------
// type traits
//-----------------------------------------------------------------------------
template <class DomainT, class CodomainT, class Traits, ICL_COMPARE Compare, ICL_COMBINE Combine, ICL_SECTION Section, ICL_INTERVAL(ICL_COMPARE)  Interval, ICL_ALLOC Alloc>
struct is_map<icl::interval_map<DomainT,CodomainT,Traits,Compare,Combine,Section,Interval,Alloc> >
{ 
    typedef is_map<icl::interval_map<DomainT,CodomainT,Traits,Compare,Combine,Section,Interval,Alloc> > type;
    BOOST_STATIC_CONSTANT(bool, value = true); 
};

template <class DomainT, class CodomainT, class Traits, ICL_COMPARE Compare, ICL_COMBINE Combine, ICL_SECTION Section, ICL_INTERVAL(ICL_COMPARE)  Interval, ICL_ALLOC Alloc>
struct has_inverse<icl::interval_map<DomainT,CodomainT,Traits,Compare,Combine,Section,Interval,Alloc> >
{ 
    typedef has_inverse<icl::interval_map<DomainT,CodomainT,Traits,Compare,Combine,Section,Interval,Alloc> > type;
    BOOST_STATIC_CONSTANT(bool, value = (has_inverse<CodomainT>::value)); 
};


template <class DomainT, class CodomainT, class Traits, ICL_COMPARE Compare, ICL_COMBINE Combine, ICL_SECTION Section, ICL_INTERVAL(ICL_COMPARE)  Interval, ICL_ALLOC Alloc>
struct is_interval_container<icl::interval_map<DomainT,CodomainT,Traits,Compare,Combine,Section,Interval,Alloc> >
{
    typedef is_interval_container<icl::interval_map<DomainT,CodomainT,Traits,Compare,Combine,Section,Interval,Alloc> > type;
    BOOST_STATIC_CONSTANT(bool, value = true); 
};

template <class DomainT, class CodomainT, class Traits, ICL_COMPARE Compare, ICL_COMBINE Combine, ICL_SECTION Section, ICL_INTERVAL(ICL_COMPARE)  Interval, ICL_ALLOC Alloc>
struct absorbs_identities<icl::interval_map<DomainT,CodomainT,Traits,Compare,Combine,Section,Interval,Alloc> >
{
    typedef absorbs_identities<icl::interval_map<DomainT,CodomainT,Traits,Compare,Combine,Section,Interval,Alloc> > type;
    BOOST_STATIC_CONSTANT(bool, value = (Traits::absorbs_identities)); 
};

template <class DomainT, class CodomainT, class Traits, ICL_COMPARE Compare, ICL_COMBINE Combine, ICL_SECTION Section, ICL_INTERVAL(ICL_COMPARE)  Interval, ICL_ALLOC Alloc>
struct is_total<icl::interval_map<DomainT,CodomainT,Traits,Compare,Combine,Section,Interval,Alloc> >
{
    typedef is_total<icl::interval_map<DomainT,CodomainT,Traits,Compare,Combine,Section,Interval,Alloc> > type;
    BOOST_STATIC_CONSTANT(bool, value = (Traits::is_total)); 
};


//-----------------------------------------------------------------------------
// type representation
//-----------------------------------------------------------------------------
template <class DomainT, class CodomainT, class Traits, ICL_COMPARE Compare, ICL_COMBINE Combine, ICL_SECTION Section, ICL_INTERVAL(ICL_COMPARE)  Interval, ICL_ALLOC Alloc>
struct type_to_string<icl::interval_map<DomainT,CodomainT,Traits,Compare,Combine,Section,Interval,Alloc> >
{
    static std::string apply()
    { 
        return "itv_map<"+ type_to_string<DomainT>::apply()   + ","
                         + type_to_string<CodomainT>::apply() + ","
                         + type_to_string<Traits>::apply()    + ">"; 
    }
};

}} // namespace icl boost

#endif



/* interval_map.hpp
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
*/