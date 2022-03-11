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