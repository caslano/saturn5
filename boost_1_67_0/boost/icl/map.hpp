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