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
ONVU7l0oZlRu2/C0IbiomSNNIZRVPbcrI8HE7kn7M9FOq+n3sVt39/lb+62ISNhyfMhHO79R4uQ9oUbF7GS/YDLgN1t1PGN0dFyv9AnfjTK48RdR+ffP8xOap10dIb7aUz3wbii07SXhNBbf3km4o232l+UH9lupDLwfu3spAife2DSdfjGaLdetTZQW0RYqivWOt738PX9TJR7no9Evz5/9JDDn5VDtfaSLluj7Wk9KWNuJUrbbi84nJXrQof6FOf/dh8nET/hMEVMiT9sJU3YJWWAMl0/Sa5/xiozSC2tdXHeffzH4eYsvf1GyqC+2xSB84eeMwULNWcLg92eGqaiMsU7FnnbdvZI1YaRd8GhSe2aiyWCTKWTGOUIdr71ioy23tr96fdS1iWWOS56sdXLDivfQfb701S/vb+uvTG25JPcMEyrMiooEjTHwBoRQWT5E7/blYgszuGy4Elt5lYqbLOLgtuFVY78aSOPF9Z6kvc82vq5uRDPPqrFrO/PDGqeH/NRVJrngvtufaxi47rrJHg33uIn6S+++545XbtOp9u+fVCHkmnO30agTP2akD/LWEkwu21wlcaw4GXjTHiTZ771xBoewy7vOyf7nSYtzaefdBPNOfKxrd3QH6OSe/krOh5yf4uDrIX7P+Z0FRIPbj+r1Ho4y11zo9jMTucK6+8L9qMnKZyFn/j3j201yRaVf+r7Z6ZEiDxJRLCgj66aMmD+ZKLqJdUbRuOjVTzg/SJPZvmz0SUdVSqkcVj9mPaatj8JOK5TGOaNF3X03un5hW92RjSI3cWQV782Z5NykojrRdutjN2Wzva1vUr6l97QzCNciEivPh+qtTJfNE4RoP5gayT/mUuGZszBDLR+xcR+/+OWDHdf4C8K4hN+EgnSwm0yZu7Jkhn1zSCb79aucWlKY7q3OMQ0uih9qVKyVdHb5FHD6pSRKoO8MBikDIsdnT1QIl0+z4pWr8ha5WNWp4ia+jXHKLyg7ydbaaM1Jn+Pgqc4zk7GeZ0B3Jy0I2s81aP1qUgtvgiv1IX2sc1gpBW3sW4F7CfthvktYv9jWunarS7z61Cu5TsKiza2GpcsvQtidrsxxj1ZgKTllUHvzrJuPlY+/J1bqwvJtvld7tMX+i4U1mfjA1lycamFLM/LqHbUZi2vf3lx+93gc154kNuDrsbB76OHg3sJwl9fh28kfZnwTYTvVY9Jcq4kWs+xU5to17RuauzW6UX1YmnGKPt31b4i0TuaU+PCrF/uq9PUujoRM21sXf7C4wvx+i7vjexB+xrWr3feIsGzxGRfpciasIj666uxu7bZhH7SNeUupDVV0K+PHU9SfGykbelRxhvBQ/ZP22MjE7GtWae2z7xI+aukQ2c9NTzVVBZpmsp7Rbbmxl/A4lGPGVMsj0xf7cxuZ6z3cERtb8wrlGLlnm5UW4eZfW0qHvK12eZeUVIUz+KyFqn9+GOQbJLUfq4T9ctNFeVEMP5VWhhMvQVGu9qb9Q2Iugjcdxl0R2+nBXg6mqiRR510vTnPTVDhWxhRRjOSK19OQexHHlKTncCuU9t+ezbwtPyBPMvbtU4hmx7jK99ktB0U7imUST4K3uXRm/g+N5bYDtCmSrDveh2I33XfsfV+x1W9o72YSz5jrmyY//sWkCYu/tdCAP3flm4wKsyOZAe3PNI67Wyf91CpSbJG8IyoCRzWWUo9JWHAfNTwzsB8m+hzAHOdMYaP8yL58RTdIlUAuhE5R0uPl8Q+XkyrXZmyWSG3n7aILZQrGWJwE3Hs7IhKXGQoIw6+X3mpZGLJwwhebJFbHTSwY0aMpGaLfdZvdtQ30c2a8e/ChT7dpL5T9Hs71rf1dovs=
*/