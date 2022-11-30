/*-----------------------------------------------------------------------------+
Copyright (c) 2007-2011: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_MAP_HPP_JOFA_070519
#define BOOST_ICL_MAP_HPP_JOFA_070519

#include <boost/icl/impl_config.hpp>

#if defined(ICL_USE_BOOST_MOVE_IMPLEMENTATION)
#   include <boost/container/map.hpp>
#   include <boost/container/set.hpp>
#elif defined(ICL_USE_STD_IMPLEMENTATION)
#   include <map>
#   include <set>
#else // Default for implementing containers
#   include <map>
#   include <set>
#endif

#include <string>
#include <boost/call_traits.hpp>
#include <boost/icl/detail/notate.hpp>
#include <boost/icl/detail/design_config.hpp>
#include <boost/icl/detail/concept_check.hpp>
#include <boost/icl/detail/on_absorbtion.hpp>
#include <boost/icl/type_traits/is_map.hpp>
#include <boost/icl/type_traits/absorbs_identities.hpp>
#include <boost/icl/type_traits/is_total.hpp>
#include <boost/icl/type_traits/is_element_container.hpp>
#include <boost/icl/type_traits/has_inverse.hpp>

#include <boost/icl/associative_element_container.hpp>
#include <boost/icl/functors.hpp>
#include <boost/icl/type_traits/to_string.hpp>

namespace boost{namespace icl
{

struct partial_absorber
{
    enum { absorbs_identities = true };
    enum { is_total = false };
};

template<>
inline std::string type_to_string<partial_absorber>::apply() { return "@0"; }

struct partial_enricher
{
    enum { absorbs_identities = false };
    enum { is_total = false };
};

template<>
inline std::string type_to_string<partial_enricher>::apply() { return "e0"; }

struct total_absorber
{
    enum { absorbs_identities = true };
    enum { is_total = true };
};

template<>
inline std::string type_to_string<total_absorber>::apply() { return "^0"; }

struct total_enricher
{
    enum { absorbs_identities = false };
    enum { is_total = true };
};

template<>
inline std::string type_to_string<total_enricher>::apply() { return "e^0"; }



/** \brief Addable, subractable and intersectable maps */
template
<
    typename DomainT,
    typename CodomainT,
    class Traits = icl::partial_absorber,
    ICL_COMPARE Compare = ICL_COMPARE_INSTANCE(ICL_COMPARE_DEFAULT, DomainT),
    ICL_COMBINE Combine = ICL_COMBINE_INSTANCE(icl::inplace_plus, CodomainT),
    ICL_SECTION Section = ICL_SECTION_INSTANCE(icl::inter_section, CodomainT),
    ICL_ALLOC   Alloc   = std::allocator
>
class map: private ICL_IMPL_SPACE::map<DomainT, CodomainT, ICL_COMPARE_DOMAIN(Compare,DomainT),
                                       Alloc<std::pair<const DomainT, CodomainT> > >
{
public:
    typedef Alloc<typename std::pair<const DomainT, CodomainT> >  allocator_type;

    typedef typename icl::map<DomainT,CodomainT,Traits, Compare,Combine,Section,Alloc> type;
    typedef typename ICL_IMPL_SPACE::map<DomainT, CodomainT, ICL_COMPARE_DOMAIN(Compare,DomainT),
                                         allocator_type>   base_type;

    typedef Traits traits;

public:
    typedef DomainT                                     domain_type;
    typedef typename boost::call_traits<DomainT>::param_type domain_param;
    typedef DomainT                                     key_type;
    typedef CodomainT                                   codomain_type;
    typedef CodomainT                                   mapped_type;
    typedef CodomainT                                   data_type;
    typedef std::pair<const DomainT, CodomainT>         element_type;
    typedef std::pair<const DomainT, CodomainT>         value_type;
    typedef ICL_COMPARE_DOMAIN(Compare,DomainT)         domain_compare;
    typedef ICL_COMBINE_CODOMAIN(Combine,CodomainT)     codomain_combine;
    typedef domain_compare                              key_compare;
    typedef ICL_COMPARE_DOMAIN(Compare,element_type)    element_compare;
    typedef typename inverse<codomain_combine >::type   inverse_codomain_combine;
    typedef typename mpl::if_
        <has_set_semantics<codomain_type>
        , ICL_SECTION_CODOMAIN(Section,CodomainT)
        , codomain_combine
        >::type                                         codomain_intersect;
    typedef typename inverse<codomain_intersect>::type  inverse_codomain_intersect;
    typedef typename base_type::value_compare           value_compare;

    typedef typename ICL_IMPL_SPACE::set<DomainT, domain_compare, Alloc<DomainT> > set_type;
    typedef set_type                                       key_object_type;


    BOOST_STATIC_CONSTANT(bool, _total   = (Traits::is_total));
    BOOST_STATIC_CONSTANT(bool, _absorbs = (Traits::absorbs_identities));
    BOOST_STATIC_CONSTANT(bool,
        total_invertible = (mpl::and_<is_total<type>, has_inverse<codomain_type> >::value));

    typedef on_absorbtion<type,codomain_combine,Traits::absorbs_identities>
                                                        on_identity_absorbtion;

public:
    typedef typename base_type::pointer                 pointer;
    typedef typename base_type::const_pointer           const_pointer;
    typedef typename base_type::reference               reference;
    typedef typename base_type::const_reference         const_reference;
    typedef typename base_type::iterator                iterator;
    typedef typename base_type::const_iterator          const_iterator;
    typedef typename base_type::size_type               size_type;
    typedef typename base_type::difference_type         difference_type;
    typedef typename base_type::reverse_iterator        reverse_iterator;
    typedef typename base_type::const_reverse_iterator  const_reverse_iterator;

public:
    BOOST_STATIC_CONSTANT(bool,
        is_total_invertible = (   Traits::is_total
                               && has_inverse<codomain_type>::value));

    BOOST_STATIC_CONSTANT(int, fineness = 4);

public:
    //==========================================================================
    //= Construct, copy, destruct
    //==========================================================================
    map()
    {
        BOOST_CONCEPT_ASSERT((DefaultConstructibleConcept<DomainT>));
        BOOST_CONCEPT_ASSERT((LessThanComparableConcept<DomainT>));
        BOOST_CONCEPT_ASSERT((DefaultConstructibleConcept<CodomainT>));
        BOOST_CONCEPT_ASSERT((EqualComparableConcept<CodomainT>));
    }

    map(const key_compare& comp): base_type(comp){}

    template <class InputIterator>
    map(InputIterator first, InputIterator past)
        : base_type(first,past){}

    template <class InputIterator>
    map(InputIterator first, InputIterator past, const key_compare& comp)
        : base_type(first,past,comp)
    {}

    map(const map& src)
        : base_type(src)
    {
        BOOST_CONCEPT_ASSERT((DefaultConstructibleConcept<DomainT>));
        BOOST_CONCEPT_ASSERT((LessThanComparableConcept<DomainT>));
        BOOST_CONCEPT_ASSERT((DefaultConstructibleConcept<CodomainT>));
        BOOST_CONCEPT_ASSERT((EqualComparableConcept<CodomainT>));
    }

    explicit map(const element_type& key_value_pair): base_type::map()
    {
        insert(key_value_pair);
    }

#   ifndef BOOST_ICL_NO_CXX11_RVALUE_REFERENCES
    //==========================================================================
    //= Move semantics
    //==========================================================================

    map(map&& src)
        : base_type(boost::move(src))
    {
        BOOST_CONCEPT_ASSERT((DefaultConstructibleConcept<DomainT>));
        BOOST_CONCEPT_ASSERT((LessThanComparableConcept<DomainT>));
        BOOST_CONCEPT_ASSERT((DefaultConstructibleConcept<CodomainT>));
        BOOST_CONCEPT_ASSERT((EqualComparableConcept<CodomainT>));
    }

    map& operator = (map src)
    {
        base_type::operator=(boost::move(src));
        return *this;
    }
    //==========================================================================
#   else

    map& operator = (const map& src)
    {
        base_type::operator=(src);
        return *this;
    }

#   endif // BOOST_ICL_NO_CXX11_RVALUE_REFERENCES

    void swap(map& src) { base_type::swap(src); }

    //==========================================================================
    using base_type::empty;
    using base_type::clear;

    using base_type::begin;
    using base_type::end;
    using base_type::rbegin;
    using base_type::rend;

    using base_type::size;
    using base_type::max_size;

    using base_type::key_comp;
    using base_type::value_comp;

    using base_type::erase;
    using base_type::find;
    using base_type::count;

    using base_type::lower_bound;
    using base_type::upper_bound;
    using base_type::equal_range;

    using base_type::operator[];

public:
    //==========================================================================
    //= Containedness
    //==========================================================================

    template<class SubObject>
    bool contains(const SubObject& sub)const
    { return icl::contains(*this, sub); }

    bool within(const map& super)const
    { return icl::contains(super, *this); }

    //==========================================================================
    //= Size
    //==========================================================================
    /** \c iterative_size() yields the number of elements that is visited
        throu complete iteration. For interval sets \c iterative_size() is
        different from \c size(). */
    std::size_t iterative_size()const { return base_type::size(); }

    //==========================================================================
    //= Selection
    //==========================================================================

    /** Total select function. */
    codomain_type operator()(const domain_type& key)const
    {
        const_iterator it = find(key);
        return it==end() ? identity_element<codomain_type>::value()
                         : it->second;
    }

    //==========================================================================
    //= Addition
    //==========================================================================
    /** \c add inserts \c value_pair into the map if it's key does
        not exist in the map.
        If \c value_pairs's key value exists in the map, it's data
        value is added to the data value already found in the map. */
    map& add(const value_type& value_pair)
    {
        return _add<codomain_combine>(value_pair);
    }

    /** \c add add \c value_pair into the map using \c prior as a hint to
        insert \c value_pair after the position \c prior is pointing to. */
    iterator add(iterator prior, const value_type& value_pair)
    {
        return _add<codomain_combine>(prior, value_pair);
    }

    //==========================================================================
    //= Subtraction
    //==========================================================================
    /** If the \c value_pair's key value is in the map, it's data value is
        subtraced from the data value stored in the map. */
    map& subtract(const element_type& value_pair)
    {
        on_invertible<type, is_total_invertible>
            ::subtract(*this, value_pair);
        return *this;
    }

    map& subtract(const domain_type& key)
    {
        icl::erase(*this, key);
        return *this;
    }

    //==========================================================================
    //= Insertion, erasure
    //==========================================================================
    std::pair<iterator,bool> insert(const value_type& value_pair)
    {
        if(on_identity_absorbtion::is_absorbable(value_pair.second))
            return std::pair<iterator,bool>(end(),true);
        else
            return base_type::insert(value_pair);
    }

    iterator insert(iterator prior, const value_type& value_pair)
    {
        if(on_identity_absorbtion::is_absorbable(value_pair.second))
            return end();
        else
            return base_type::insert(prior, value_pair);
    }

    template<class Iterator>
    iterator insert(Iterator first, Iterator last)
    {
        iterator prior = end(), it = first;
        while(it != last)
            prior = this->insert(prior, *it++);
    }

    /** With <tt>key_value_pair = (k,v)</tt> set value \c v for key \c k */
    map& set(const element_type& key_value_pair)
    {
        return icl::set_at(*this, key_value_pair);
    }

    /** erase \c key_value_pair from the map.
        Erase only if, the exact value content \c val is stored for the given key. */
    size_type erase(const element_type& key_value_pair)
    {
        return icl::erase(*this, key_value_pair);
    }

    //==========================================================================
    //= Intersection
    //==========================================================================
    /** The intersection of \c key_value_pair and \c *this map is added to \c section. */
    void add_intersection(map& section, const element_type& key_value_pair)const
    {
        on_definedness<type, Traits::is_total>
            ::add_intersection(section, *this, key_value_pair);
    }

    //==========================================================================
    //= Symmetric difference
    //==========================================================================

    map& flip(const element_type& operand)
    {
        on_total_absorbable<type,_total,_absorbs>::flip(*this, operand);
        return *this;
    }

private:
    template<class Combiner>
    map& _add(const element_type& value_pair);

    template<class Combiner>
    iterator _add(iterator prior, const element_type& value_pair);

    template<class Combiner>
    map& _subtract(const element_type& value_pair);

    template<class FragmentT>
    void total_add_intersection(type& section, const FragmentT& fragment)const
    {
        section += *this;
        section.add(fragment);
    }

    void partial_add_intersection(type& section, const element_type& operand)const
    {
        const_iterator it_ = find(operand.first);
        if(it_ != end())
        {
            section.template _add<codomain_combine  >(*it_);
            section.template _add<codomain_intersect>(operand);
        }
    }


private:
    //--------------------------------------------------------------------------
    template<class Type, bool is_total_invertible>
    struct on_invertible;

    template<class Type>
    struct on_invertible<Type, true>
    {
        typedef typename Type::element_type element_type;
        typedef typename Type::inverse_codomain_combine inverse_codomain_combine;

        static void subtract(Type& object, const element_type& operand)
        { object.template _add<inverse_codomain_combine>(operand); }
    };

    template<class Type>
    struct on_invertible<Type, false>
    {
        typedef typename Type::element_type element_type;
        typedef typename Type::inverse_codomain_combine inverse_codomain_combine;

        static void subtract(Type& object, const element_type& operand)
        { object.template _subtract<inverse_codomain_combine>(operand); }
    };

    friend struct on_invertible<type, true>;
    friend struct on_invertible<type, false>;
    //--------------------------------------------------------------------------

    //--------------------------------------------------------------------------
    template<class Type, bool is_total>
    struct on_definedness;

    template<class Type>
    struct on_definedness<Type, true>
    {
        static void add_intersection(Type& section, const Type& object,
                                     const element_type& operand)
        { object.total_add_intersection(section, operand); }
    };

    template<class Type>
    struct on_definedness<Type, false>
    {
        static void add_intersection(Type& section, const Type& object,
                                     const element_type& operand)
        { object.partial_add_intersection(section, operand); }
    };

    friend struct on_definedness<type, true>;
    friend struct on_definedness<type, false>;
    //--------------------------------------------------------------------------

    //--------------------------------------------------------------------------
    template<class Type, bool has_set_semantics, bool absorbs_identities>
    struct on_codomain_model;

    template<class Type>
    struct on_codomain_model<Type, false, false>
    {                // !codomain_is_set, !absorbs_identities
        static void subtract(Type&, typename Type::iterator it_,
                              const typename Type::codomain_type& )
        { (*it_).second = identity_element<typename Type::codomain_type>::value(); }
    };

    template<class Type>
    struct on_codomain_model<Type, false, true>
    {                // !codomain_is_set, absorbs_identities
        static void subtract(Type& object, typename Type::iterator       it_,
                                     const typename Type::codomain_type&     )
        { object.erase(it_); }
    };

    template<class Type>
    struct on_codomain_model<Type, true, false>
    {               // !codomain_is_set, !absorbs_identities
        typedef typename Type::inverse_codomain_intersect inverse_codomain_intersect;
        static void subtract(Type&, typename Type::iterator       it_,
                              const typename Type::codomain_type& co_value)
        {
            inverse_codomain_intersect()((*it_).second, co_value);
        }
    };

    template<class Type>
    struct on_codomain_model<Type, true, true>
    {               // !codomain_is_set, absorbs_identities
        typedef typename Type::inverse_codomain_intersect inverse_codomain_intersect;
        static void subtract(Type& object, typename Type::iterator       it_,
                                     const typename Type::codomain_type& co_value)
        {
            inverse_codomain_intersect()((*it_).second, co_value);
            if((*it_).second == identity_element<codomain_type>::value())
                object.erase(it_);
        }
    };
    //--------------------------------------------------------------------------

    //--------------------------------------------------------------------------
    template<class Type, bool is_total, bool absorbs_identities>
    struct on_total_absorbable;

    template<class Type>
    struct on_total_absorbable<Type, true, true>
    {
        typedef typename Type::element_type  element_type;
        static void flip(Type& object, const typename Type::element_type&)
        { icl::clear(object); }
    };

    template<class Type>
    struct on_total_absorbable<Type, true, false>
    {
        typedef typename Type::element_type  element_type;
        typedef typename Type::codomain_type codomain_type;

        static void flip(Type& object, const element_type& operand)
        {
            object.add(operand);
            ICL_FORALL(typename Type, it_, object)
                (*it_).second = identity_element<codomain_type>::value();
        }
    };

    template<class Type>
    struct on_total_absorbable<Type, false, true>
    {                         // !is_total, absorbs_identities
        typedef typename Type::element_type   element_type;
        typedef typename Type::codomain_type  codomain_type;
        typedef typename Type::iterator       iterator;
        typedef typename Type::inverse_codomain_intersect inverse_codomain_intersect;

        static void flip(Type& object, const element_type& operand)
        {
            std::pair<iterator,bool> insertion = object.insert(operand);
            if(!insertion.second)
                on_codomain_model<Type, has_set_semantics<codomain_type>::value, true>
                ::subtract(object, insertion.first, operand.second);
        }
    };

    template<class Type>
    struct on_total_absorbable<Type, false, false>
    {                         // !is_total  !absorbs_identities
        typedef typename Type::element_type   element_type;
        typedef typename Type::codomain_type  codomain_type;
        typedef typename Type::iterator       iterator;
        typedef typename Type::inverse_codomain_intersect inverse_codomain_intersect;

        static void flip(Type& object, const element_type& operand)
        {
            std::pair<iterator,bool> insertion = object.insert(operand);
            if(!insertion.second)
                on_codomain_model<Type, has_set_semantics<codomain_type>::value, false>
                ::subtract(object, insertion.first, operand.second);
        }
    };

    friend struct on_total_absorbable<type, true,  true >;
    friend struct on_total_absorbable<type, false, true >;
    friend struct on_total_absorbable<type, true,  false>;
    friend struct on_total_absorbable<type, false, false>;
    //--------------------------------------------------------------------------
};



//==============================================================================
//= Addition<ElementMap>
//==============================================================================
template <class DomainT, class CodomainT, class Traits, ICL_COMPARE Compare, ICL_COMBINE Combine, ICL_SECTION Section, ICL_ALLOC Alloc>
    template <class Combiner>
map<DomainT,CodomainT,Traits,Compare,Combine,Section,Alloc>&
    map<DomainT,CodomainT,Traits,Compare,Combine,Section,Alloc>
    ::_add(const element_type& addend)
{
    typedef typename on_absorbtion
        <type,Combiner,absorbs_identities<type>::value>::type on_absorbtion_;

    const codomain_type& co_val    = addend.second;
    if(on_absorbtion_::is_absorbable(co_val))
        return *this;

    std::pair<iterator,bool> insertion
        = base_type::insert(value_type(addend.first, version<Combiner>()(co_val)));

    if(!insertion.second)
    {
        iterator it = insertion.first;
        Combiner()((*it).second, co_val);

        if(on_absorbtion_::is_absorbable((*it).second))
            erase(it);
    }
    return *this;
}


template <class DomainT, class CodomainT, class Traits, ICL_COMPARE Compare, ICL_COMBINE Combine, ICL_SECTION Section, ICL_ALLOC Alloc>
    template <class Combiner>
typename map<DomainT,CodomainT,Traits,Compare,Combine,Section,Alloc>::iterator
    map<DomainT,CodomainT,Traits,Compare,Combine,Section,Alloc>
    ::_add(iterator prior_, const value_type& addend)
{
    typedef typename on_absorbtion
        <type,Combiner,absorbs_identities<type>::value>::type on_absorbtion_;

    const codomain_type& co_val    = addend.second;
    if(on_absorbtion_::is_absorbable(co_val))
        return end();

    iterator inserted_
        = base_type::insert(prior_,
                            value_type(addend.first, Combiner::identity_element()));
    Combiner()((*inserted_).second, addend.second);

    if(on_absorbtion_::is_absorbable((*inserted_).second))
    {
        erase(inserted_);
        return end();
    }
    else
        return inserted_;
}


//==============================================================================
//= Subtraction<ElementMap>
//==============================================================================
template <class DomainT, class CodomainT, class Traits, ICL_COMPARE Compare, ICL_COMBINE Combine, ICL_SECTION Section, ICL_ALLOC Alloc>
    template <class Combiner>
map<DomainT,CodomainT,Traits,Compare,Combine,Section,Alloc>&
    map<DomainT,CodomainT,Traits,Compare,Combine,Section,Alloc>::_subtract(const value_type& minuend)
{
    typedef typename on_absorbtion
        <type,Combiner,absorbs_identities<type>::value>::type on_absorbtion_;

    iterator it_ = find(minuend.first);
    if(it_ != end())
    {
        Combiner()((*it_).second, minuend.second);
        if(on_absorbtion_::is_absorbable((*it_).second))
            erase(it_);
    }
    return *this;
}


//-----------------------------------------------------------------------------
// type traits
//-----------------------------------------------------------------------------
template <class DomainT, class CodomainT, class Traits, ICL_COMPARE Compare, ICL_COMBINE Combine, ICL_SECTION Section, ICL_ALLOC Alloc>
struct is_map<icl::map<DomainT,CodomainT,Traits,Compare,Combine,Section,Alloc> >
{
    typedef is_map<icl::map<DomainT,CodomainT,Traits,Compare,Combine,Section,Alloc> > type;
    BOOST_STATIC_CONSTANT(bool, value = true);
};

template <class DomainT, class CodomainT, class Traits, ICL_COMPARE Compare, ICL_COMBINE Combine, ICL_SECTION Section, ICL_ALLOC Alloc>
struct has_inverse<icl::map<DomainT,CodomainT,Traits,Compare,Combine,Section,Alloc> >
{
    typedef has_inverse<icl::map<DomainT,CodomainT,Traits,Compare,Combine,Section,Alloc> > type;
    BOOST_STATIC_CONSTANT(bool, value = (has_inverse<CodomainT>::value));
};

template <class DomainT, class CodomainT, class Traits, ICL_COMPARE Compare, ICL_COMBINE Combine, ICL_SECTION Section, ICL_ALLOC Alloc>
struct absorbs_identities<icl::map<DomainT,CodomainT,Traits,Compare,Combine,Section,Alloc> >
{
    typedef absorbs_identities type;
    BOOST_STATIC_CONSTANT(int, value = Traits::absorbs_identities);
};

template <class DomainT, class CodomainT, class Traits, ICL_COMPARE Compare, ICL_COMBINE Combine, ICL_SECTION Section, ICL_ALLOC Alloc>
struct is_total<icl::map<DomainT,CodomainT,Traits,Compare,Combine,Section,Alloc> >
{
    typedef is_total type;
    BOOST_STATIC_CONSTANT(int, value = Traits::is_total);
};

template <class DomainT, class CodomainT, class Traits, ICL_COMPARE Compare, ICL_COMBINE Combine, ICL_SECTION Section, ICL_ALLOC Alloc>
struct type_to_string<icl::map<DomainT,CodomainT,Traits,Compare,Combine,Section,Alloc> >
{
    static std::string apply()
    {
        return "map<"+ type_to_string<DomainT>::apply()  + ","
                     + type_to_string<CodomainT>::apply() + ","
                     + type_to_string<Traits>::apply() +">";
    }
};



}} // namespace icl boost

#endif // BOOST_ICL_MAP_HPP_JOFA_070519

/* map.hpp
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
*/