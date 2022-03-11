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