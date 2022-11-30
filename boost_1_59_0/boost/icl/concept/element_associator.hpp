/*-----------------------------------------------------------------------------+
Copyright (c) 2010-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_CONCEPT_ELEMENT_ASSOCIATOR_HPP_JOFA_100921
#define BOOST_ICL_CONCEPT_ELEMENT_ASSOCIATOR_HPP_JOFA_100921

#include <boost/config.hpp>
#include <boost/icl/type_traits/is_associative_element_container.hpp>
#include <boost/icl/type_traits/is_key_container_of.hpp>
#include <boost/icl/type_traits/is_combinable.hpp>
#include <boost/icl/detail/subset_comparer.hpp>
#include <boost/icl/concept/element_set.hpp>
#include <boost/icl/concept/element_map.hpp>

namespace boost{ namespace icl
{

//==============================================================================
//= Size
//==============================================================================
template<class Type>
typename enable_if<is_element_container<Type>, std::size_t>::type
iterative_size(const Type& object)
{
    return object.size();
}

template<class Type>
typename enable_if<is_associative_element_container<Type>, typename Type::size_type>::type
size(const Type& object)
{
    return icl::iterative_size(object);
}

template<class Type>
typename enable_if<is_associative_element_container<Type>, typename Type::size_type>::type
cardinality(const Type& object)
{
    return icl::iterative_size(object);
}


//==============================================================================
//= Containedness<ElementSet|ElementMap>
//==============================================================================
//------------------------------------------------------------------------------
//- bool within(c P&, c T&) T:{s}|{m} P:{e}|{i} fragment_types|key_types
//------------------------------------------------------------------------------
/** Checks if a key is in the associative container */
template<class Type>
typename enable_if<is_associative_element_container<Type>, bool>::type
within(const typename Type::key_type& key, const Type& super)
{
    return !(super.find(key) == super.end());
}

//------------------------------------------------------------------------------
//- bool within(c P&, c T&) T:{s}|{m} P:{s'} fragment_types|key_types
//------------------------------------------------------------------------------
template<class SubT, class SuperT>
typename enable_if<mpl::and_< is_associative_element_container<SuperT>
                            , is_key_container_of<SubT, SuperT> >,
                   bool>::type
within(const SubT& sub, const SuperT& super)
{
    if(icl::is_empty(sub))                return true;
    if(icl::is_empty(super))              return false;
    if(icl::size(super) < icl::size(sub)) return false;

    typename SubT::const_iterator common_lwb_;
    typename SubT::const_iterator common_upb_;
    if(!Set::common_range(common_lwb_, common_upb_, sub, super))
        return false;

    typename SubT::const_iterator sub_ = sub.begin();
    typename SuperT::const_iterator super_;
    while(sub_ != sub.end())
    {
        super_ = super.find(key_value<SubT>(sub_));
        if(super_ == super.end())
            return false;
        else if(!co_equal(sub_, super_, &sub, &super))
            return false;

        ++sub_;
    }
    return true;
}

//------------------------------------------------------------------------------
//- bool contains(c T&, c P&) T:{s}|{m} P:{e}|{i} fragment_types|key_types
//------------------------------------------------------------------------------
template<class Type>
typename enable_if<is_associative_element_container<Type>, bool>::type
contains(const Type& super, const typename Type::key_type& key)
{
    return icl::within(key, super);
}

//------------------------------------------------------------------------------
//- bool contains(c T&, c P&) T:{s}|{m} P:{s'} fragment_types|key_types
//------------------------------------------------------------------------------
template<class SubT, class SuperT>
typename enable_if<mpl::and_< is_associative_element_container<SuperT>
                            , is_key_container_of<SubT, SuperT> >,
                   bool>::type
contains(const SuperT& super, const SubT& sub)
{
    return icl::within(sub, super);
}

//==============================================================================
//= Equivalences and Orderings
//==============================================================================

#ifdef BOOST_MSVC
#pragma warning(push)
#pragma warning(disable:4996) //'std::equal': Function call with parameters that may be unsafe - this call relies on the caller to check that the passed values are correct. To disable this warning, use -D_SCL_SECURE_NO_WARNINGS. See documentation on how to use Visual C++ 'Checked Iterators'
#endif                        // I do guarantee here that I am using the parameters correctly :)

/** Standard equality, which is lexicographical equality of the sets
    as sequences, that are given by their Compare order. */
template<class Type>
inline typename enable_if<is_associative_element_container<Type>, bool>::type
operator == (const Type& left, const Type& right)
{
    return left.size() == right.size()
        && std::equal(left.begin(), left.end(), right.begin());
}

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

template<class Type>
inline typename enable_if<is_associative_element_container<Type>, bool>::type
is_element_equal(const Type& left, const Type& right)
{ return left == right; }


/* Strict weak less ordering which is given by the Compare order */
template<class Type>
inline typename enable_if<is_associative_element_container<Type>, bool>::type
operator < (const Type& left, const Type& right)
{
    return std::lexicographical_compare(
        left.begin(), left.end(), right.begin(), right.end(),
        typename Type::element_compare()
        );
}

template<class LeftT, class RightT>
typename enable_if<is_concept_equivalent<is_element_container,LeftT, RightT>,
                   int>::type
inclusion_compare(const LeftT& left, const RightT& right)
{
    return Set::subset_compare(left, right,
                               left.begin(), left.end(),
                               right.begin(), right.end());
}

//==============================================================================
//= Addition
//==============================================================================
template <class Type>
inline typename enable_if<is_associative_element_container<Type>, Type>::type&
operator += (Type& object, const typename Type::value_type& operand)
{
    return icl::add(object, operand);
}

template <class Type>
inline typename enable_if<is_associative_element_container<Type>, Type>::type
operator + (Type object, const typename Type::value_type& operand)
{
    return object += operand;
}

template <class Type>
inline typename enable_if<is_associative_element_container<Type>, Type>::type
operator + (const typename Type::value_type& operand, Type object)
{
    return object += operand;
}

template <class Type>
inline typename enable_if<is_associative_element_container<Type>, Type>::type&
operator += (Type& object, const Type& operand)
{
    if(&object == &operand)
        return object;

    typename Type::iterator prior_ = object.end();
    ICL_const_FORALL(typename Type, it_, operand)
        prior_ = icl::add(object, prior_, *it_);

    return object;
}

template <class Type>
inline typename enable_if<is_associative_element_container<Type>, Type>::type
operator + (Type object, const Type& operand)
{
    return object += operand;
}

//==============================================================================
template <class Type>
inline typename enable_if<is_associative_element_container<Type>, Type>::type&
operator |= (Type& object, const typename Type::value_type& operand)
{
    return icl::add(object, operand);
}

template <class Type>
inline typename enable_if<is_associative_element_container<Type>, Type>::type
operator | (Type object, const typename Type::value_type& operand)
{
    return object += operand;
}

template <class Type>
inline typename enable_if<is_associative_element_container<Type>, Type>::type
operator | (const typename Type::value_type& operand, Type object)
{
    return object += operand;
}

template <class Type>
inline typename enable_if<is_associative_element_container<Type>, Type>::type&
operator |= (Type& object, const Type& operand)
{
    return object += operand;
}

template <class Type>
inline typename enable_if<is_associative_element_container<Type>, Type>::type
operator | (Type object, const Type& operand)
{
    return object += operand;
}


//==============================================================================
//= Insertion
//==============================================================================
//------------------------------------------------------------------------------
//- V insert(T&, c P&) T:{s}|{m} P:{e}|{b} fragment_type
//------------------------------------------------------------------------------
template<class Type>
typename enable_if<is_associative_element_container<Type>,
                   std::pair<typename Type::iterator,bool> >::type
insert(Type& object, const typename Type::value_type& operand)
{
    return object.insert(operand);
}

template<class Type>
typename enable_if<is_associative_element_container<Type>,
                   typename Type::iterator>::type
insert(Type& object, typename Type::iterator      prior,
               const typename Type::value_type& operand)
{
    return object.insert(prior, operand);
}

//------------------------------------------------------------------------------
//- T insert(T&, c T&) T:{s m}  map fragment_type
//------------------------------------------------------------------------------
template<class Type>
typename enable_if<is_associative_element_container<Type>, Type>::type&
insert(Type& object, const Type& addend)
{
    typedef typename Type::iterator iterator;

    iterator prior_ = object.end();
    ICL_const_FORALL(typename Type, elem_, addend)
        icl::insert(object, prior_, *elem_);

    return object;
}


//==============================================================================
//= Erasure
//==============================================================================
template<class Type>
typename enable_if<is_associative_element_container<Type>, typename Type::size_type>::type
erase(Type& object, const typename Type::key_type& key_value)
{
    typedef typename Type::size_type size_type;
    typename Type::iterator it_ = object.find(key_value);
    if(it_ != object.end())
    {
        object.erase(it_);
        return unit_element<size_type>::value();
    }
    return identity_element<size_type>::value();
}

template<class Type>
typename enable_if<is_associative_element_container<Type>, Type>::type&
erase(Type& object, const Type& erasure)
{
    ICL_const_FORALL(typename Type, elem_, erasure)
        icl::erase(object, *elem_);

    return object;
}



//==============================================================================
//= Subtraction<ElementSet|ElementMap>
//==============================================================================
template <class Type>
inline typename enable_if<is_associative_element_container<Type>, Type>::type&
operator -= (Type& object, const typename Type::value_type& operand)
{
    return icl::subtract(object, operand);
}

template <class Type>
inline typename enable_if<is_associative_element_container<Type>, Type>::type
operator - (Type object, const typename Type::value_type& operand)
{
    return object -= operand;
}

template <class Type>
inline typename enable_if<is_associative_element_container<Type>, Type>::type&
operator -= (Type& object, const Type& subtrahend)
{
    ICL_const_FORALL(typename Type, it_, subtrahend)
        icl::subtract(object, *it_);

    return object;
}

template <class Type>
inline typename enable_if<is_associative_element_container<Type>, Type>::type
operator - (Type object, const Type& subtrahend)
{
    return object -= subtrahend;
}


//==============================================================================
//= Intersection
//==============================================================================
//------------------------------------------------------------------------------
//- void add_intersection(T&, c T&, c P&) T:{s}{m} P:{e}{e} key_type
//------------------------------------------------------------------------------
template<class Type>
inline typename enable_if<is_associative_element_container<Type>, void>::type
add_intersection(Type& section, const Type&              object,
                       const typename Type::key_type& operand)
{
    typedef typename Type::const_iterator const_iterator;
    const_iterator it_ = object.find(operand);
    if(it_ != object.end())
        icl::add(section, *it_);
}

//------------------------------------------------------------------------------
//- void add_intersection(T&, c T&, c P&) T:{s}{m} P:{s}{s} set key_type
//------------------------------------------------------------------------------
template<class Type>
inline typename enable_if<is_associative_element_container<Type>, void>::type
add_intersection(Type& section, const Type& object,
                 const typename key_container_type_of<Type>::type& operand)
{
    typedef typename key_container_type_of<Type>::type key_container_type;
    typedef typename key_container_type::const_iterator const_iterator;
    const_iterator common_lwb_, common_upb_;
    if(!Set::common_range(common_lwb_, common_upb_, operand, object))
        return;

    const_iterator sec_ = common_lwb_;
    while(sec_ != common_upb_)
        add_intersection(section, object, *sec_++);
}

//------------------------------------------------------------------------------
//- Intersection<ElementMap|ElementSet>
//------------------------------------------------------------------------------
template<class Type>
inline typename enable_if<is_associative_element_container<Type>, Type>::type&
operator &= (Type& object, const typename Type::key_type& operand)
{
    Type section;
    add_intersection(section, object, operand);
    object.swap(section);
    return object;
}

template<class Type>
inline typename enable_if<is_associative_element_container<Type>, Type>::type
operator & (Type object, const typename Type::key_type& operand)
{
    return object &= operand;
}

template<class Type>
inline typename enable_if<is_associative_element_container<Type>, Type>::type
operator & (const typename Type::key_type& operand, Type object)
{
    return object &= operand;
}

template<class Type>
inline typename enable_if<is_associative_element_container<Type>, Type>::type&
operator &= (Type& object, const typename key_container_type_of<Type>::type& operand)
{
    Type section;
    add_intersection(section, object, operand);
    object.swap(section);
    return object;
}

template<class Type>
inline typename enable_if<is_associative_element_container<Type>, Type>::type
operator & (Type object, const Type& operand)
{
    return object &= operand;
}
//------------------------------------------------------------------------------

template<class Type, class CoType>
inline typename enable_if<is_associative_element_container<Type>, bool>::type
disjoint(const Type& left, const Type& right)
{
    return !intersects(left, right);
}

//==============================================================================
//= Symmetric difference<ElementSet|ElementMap>
//==============================================================================
template<class Type>
inline typename enable_if<is_associative_element_container<Type>, Type>::type
operator ^ (Type object, const typename Type::value_type& operand)
{
    return icl::flip(object, operand);
}

template<class Type>
inline typename enable_if<is_associative_element_container<Type>, Type>::type
operator ^ (const typename Type::value_type& operand, Type object)
{
    return icl::flip(object, operand);
}

template<class Type>
inline typename enable_if<is_associative_element_container<Type>, Type>::type
operator ^ (Type object, const Type& operand)
{
    return object ^= operand;
}


//==============================================================================
//= Manipulation by predicates
//==============================================================================
template<class Type, class Predicate>
typename enable_if<is_associative_element_container<Type>, Type>::type&
erase_if(const Predicate& pred, Type& object)
{
    typename Type::iterator it_ = object.begin();
    while(it_ != object.end())
        if(pred(*it_))
            icl::erase(object, it_++);
        else ++it_;
    return object;
}

template<class Type, class Predicate>
inline typename enable_if<is_associative_element_container<Type>, Type>::type&
add_if(const Predicate& pred, Type& object, const Type& src)
{
    typename Type::const_iterator it_ = src.begin();
    while(it_ != src.end())
        if(pred(*it_))
            icl::add(object, *it_++);

    return object;
}

template<class Type, class Predicate>
inline typename enable_if<is_associative_element_container<Type>, Type>::type&
assign_if(const Predicate& pred, Type& object, const Type& src)
{
    icl::clear(object);
    return add_if(object, src, pred);
}



}} // namespace boost icl

#endif

/* element_associator.hpp
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
*/