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
BHW3xydt7GK7qxf/X///xvrnyCHV4+wVj27t79wWu49ac9pfN6+er7r22V179c/WWJxikG7y0h9e1L+28EFX9fkuzO3dY8a7Xymxzl78Sm+jn/viiHMr8r773PPgnvpDXFHhFi//+4OsQEHM5budx7/X6F7PiZmveQWXze84sbx478lfvsjM6q7bMll5a89X57IWPbNsssCZ5v1///8P73/UHz61qn958urGGN26a7e+W6U773ZTotZ68WnrmheTn+FK93sr3OuyEUpMkN+eWOs9uIf/k6lKLv/EluXbVW86dA205isNul5ed/rytWqNrlQl9/5LPA9ztpeXQedx5+jvnyGtd12t9Uu/iLzg8emjx2a/MNrimOhnn3Rejkp4/bxjZYxw3hfyn1QcczLdQ9Lc73e/KfVs44NhbvHHm6wubTtLYbpVTn6wvMHjGv47A8n7X1/KitxUO7/3J6VLK69SNlvfOZrL+PVpfp8errBjZ2XDzfUjS74W72DVPh5Qu1RWRO/48OaypkfGTz83s0l90Bllj1mDccha7Th/1a+KtUb+pISE6/2fjWlFXnLS+X/7/3/7/59t/2dpfglFn0Yrvr73s03SxlPFZj27fjr7w5X4KtPToh/NTmUWtCMSWEdrd7xyH+Stf7434rDOaruS4C+X/zyyxoJ7MsHgSdNH3Czl5r6CUKO+ie/PvvrDjhva2saYw+iNePqA7zF17uNGi/hXIet+MYnwaP5xizA9o/tlgUfqoXNbHySvMUcP+nfb4QzsR8oPffRVpD79haPrC6MeU4U7CSVrrdxyH+Qd5K2oCxnWbJCbl8EcK5mvtmJwU2FZB7Vm0/1F8S+HI+q1Wg+tsdwz79nA1gOfOhFcds7XXNe5bR/CuONXG4MmNfJXr1BR7jkf/Oy+LOnh1/tNltxdv+yznh9Zyx5sroqKXdW0ufuLwfae2eMe8f/w//AfHP763/3BCXNf/HriFp3KnnNNAgVMuv807UuYDwtD8CbtBMznBEOnuWm3fyOtZ+a56HPSrkCa7HxX7vxGWu/089Dk5qR5c+ctKGiuDElZfHoHv+dY2tavVUdiXd4zPvMdq0fu6KLIoxO7+kPVP7Tqsa51qzn5IznguFfhuUv+I57qRS9t3EPuvbw+uTgufh/ny93zv4ip+WFPSnfzN7Xp+dfsP8zV4dJwxd+efEQ/t7TfWGvI5gtV8aHELXfjVwWKri69WLB234Ui3PiZA01LH72/4tuVtz+9zbyz+eDnWaSye9+Vaw9ErczQ0d84dnlRVsaPO6+o+hUkGRUdj9/ddjjo+o5Dp8KRxFqmN4vwsdzCQ1+tJ74I1iYX7Ok1Lq5q7xzvfLaAvz/1/eyVa7dpnDipglKmP8X4UMI3JXksk3yo9Uu0rmmkrtLkOqfrqUu++eDqIuoLbF7VkPPh0DBFi4n6jua2w579VPnXPT8QNb+PXWxzr6A1llU0eTd4eFNV4u6IuvjxPgHxmEeruKIpOPe+sgLpCTffGEP/OY7TUPWdXtOX/avOPth6r6pwS8vmw5ILX/QmrjDdmm7meslurCVyPvHWvpQvGAkHO1iKo9T4W0OmtxvjP+Gb7F0hUbqPUu7K2H7GJFAvzWpbdozpjtpyudwfqg7eQaw9yz+z05B0+sLzLotBWuZYE1677tSVyo6PPWwrfYaytG68WHRzaLDJeo/i+bWlS9McI786mKC4/Pt+poLqlyY71ogHGD2FG5zs9x3vWrZ8jKn0sj+RyDyVy/CoaDsgWnMvhHyI1eCXc/TlqutXirnZWpuopS8NWGrte77/Q3lojH6q3Jm0ZOSj572qP6gtnGyN1aQs31BzeG3+67jXg+Go8s8=
*/