/*-----------------------------------------------------------------------------+    
Copyright (c) 2010-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_CONCEPT_INTERVAL_SET_HPP_JOFA_100920
#define BOOST_ICL_CONCEPT_INTERVAL_SET_HPP_JOFA_100920

#include <boost/icl/type_traits/is_combinable.hpp>
#include <boost/icl/type_traits/interval_type_of.hpp>
#include <boost/icl/detail/set_algo.hpp>
#include <boost/icl/detail/interval_set_algo.hpp>
#include <boost/icl/concept/interval.hpp>

namespace boost{ namespace icl
{

//==============================================================================
//= Containedness<IntervalSet>
//==============================================================================
//------------------------------------------------------------------------------
//- bool contains(c T&, c P&) T:{S} P:{e i S} fragment_types
//------------------------------------------------------------------------------
template<class Type>
typename enable_if<is_interval_set<Type>, bool>::type
contains(const Type& super, const typename Type::element_type& element)
{
    return !(icl::find(super, element) == super.end());
}

template<class Type>
typename enable_if<is_interval_set<Type>, bool>::type
contains(const Type& super, const typename Type::segment_type& inter_val)
{ 
    typedef typename Type::const_iterator const_iterator;
    if(icl::is_empty(inter_val)) 
        return true;

    std::pair<const_iterator, const_iterator> exterior 
        = super.equal_range(inter_val);
    if(exterior.first == exterior.second)
        return false;

    const_iterator last_overlap = cyclic_prior(super, exterior.second);

    return 
        icl::contains(hull(*(exterior.first), *last_overlap), inter_val)
    &&  Interval_Set::is_joinable(super, exterior.first, last_overlap);
}

template<class Type, class OperandT>
typename enable_if<has_same_concept<is_interval_set, Type, OperandT>, 
                   bool>::type 
contains(const Type& super, const OperandT& sub)
{
    return Interval_Set::contains(super, sub);
}

//==============================================================================
//= Addition<IntervalSet>
//==============================================================================
//------------------------------------------------------------------------------
//- T& add(T&, c P&) T:{S} P:{e i} fragment_types
//------------------------------------------------------------------------------
template<class Type>
typename enable_if<is_interval_set<Type>, Type>::type&
add(Type& object, const typename Type::segment_type& operand)
{
    return object.add(operand);
}

template<class Type>
inline typename enable_if<is_interval_set<Type>, Type>::type&
add(Type& object, const typename Type::element_type& operand)
{
    typedef typename Type::segment_type segment_type;
    return icl::add(object, icl::singleton<segment_type>(operand));
}

//------------------------------------------------------------------------------
//- T& add(T&, J, c P&) T:{S} P:{i} interval_type
//------------------------------------------------------------------------------
template<class Type>
inline typename enable_if<is_interval_set<Type>, typename Type::iterator>::type
add(Type& object, typename Type::iterator      prior, 
            const typename Type::segment_type& operand)
{
    return object.add(prior, operand);
}

//==============================================================================
//= Insertion<IntervalSet>
//==============================================================================
//------------------------------------------------------------------------------
//- T& insert(T&, c P&) T:{S} P:{e i} fragment_types
//------------------------------------------------------------------------------
template<class Type>
inline typename enable_if<is_interval_set<Type>, Type>::type&
insert(Type& object, const typename Type::segment_type& operand)
{
    return icl::add(object, operand);
}

template<class Type>
inline typename enable_if<is_interval_set<Type>, Type>::type&
insert(Type& object, const typename Type::element_type& operand)
{
    return icl::add(object, operand);
}

//------------------------------------------------------------------------------
//- T& insert(T&, J, c P&) T:{S} P:{i} with hint
//------------------------------------------------------------------------------
template<class Type>
inline typename enable_if<is_interval_set<Type>, typename Type::iterator>::type
insert(Type& object, typename Type::iterator      prior,
               const typename Type::segment_type& operand)
{
    return icl::add(object, prior, operand);
}

//==============================================================================
//= Subtraction<IntervalSet>
//==============================================================================
//------------------------------------------------------------------------------
//- T& subtract(T&, c P&) T:{S} P:{e i} fragment_type
//------------------------------------------------------------------------------
template<class Type>
typename enable_if<is_interval_set<Type>, Type>::type&
subtract(Type& object, const typename Type::segment_type& operand)
{
    return object.subtract(operand);
}

template<class Type>
inline typename enable_if<is_interval_set<Type>, Type>::type&
subtract(Type& object, const typename Type::element_type& operand)
{
    typedef typename Type::segment_type segment_type;
    return icl::subtract(object, icl::singleton<segment_type>(operand));
}

//==============================================================================
//= Erasure<IntervalSet>
//==============================================================================
//------------------------------------------------------------------------------
//- T& erase(T&, c P&) T:{S} P:{e i} fragment_types
//------------------------------------------------------------------------------
template<class Type>
typename enable_if<is_interval_set<Type>, Type>::type&
erase(Type& object, const typename Type::segment_type& minuend)
{
    return icl::subtract(object, minuend);
}

template<class Type>
typename enable_if<is_interval_set<Type>, Type>::type&
erase(Type& object, const typename Type::element_type& minuend)
{
    return icl::subtract(object, minuend);
}

//==============================================================================
//= Intersection
//==============================================================================
//------------------------------------------------------------------------------
//- void add_intersection(T&, c T&, c P&) T:{S} P:{e i} fragment_types
//------------------------------------------------------------------------------
template<class Type>
typename enable_if<is_interval_set<Type>, void>::type
add_intersection(Type& section, const Type& object, 
                 const typename Type::element_type& operand)
{
    typedef typename Type::const_iterator const_iterator;
    const_iterator found = icl::find(object, operand);
    if(found != object.end())
        icl::add(section, operand);
}


template<class Type>
typename enable_if<is_interval_set<Type>, void>::type
add_intersection(Type& section, const Type& object, 
                 const typename Type::segment_type& segment)
{
    typedef typename Type::const_iterator const_iterator;
    typedef typename Type::iterator       iterator;
    typedef typename Type::interval_type  interval_type;

    if(icl::is_empty(segment)) 
        return;

    std::pair<const_iterator, const_iterator> exterior 
        = object.equal_range(segment);
    if(exterior.first == exterior.second)
        return;

    iterator prior_ = section.end();
    for(const_iterator it_=exterior.first; it_ != exterior.second; it_++) 
    {
        interval_type common_interval = key_value<Type>(it_) & segment;
        if(!icl::is_empty(common_interval))
            prior_ = section.insert(prior_, common_interval);
    }
}

//==============================================================================
//= Symmetric difference<IntervalSet>
//==============================================================================
//------------------------------------------------------------------------------
//- T& flip(T&, c P&) T:{S} P:{e i S'} fragment_types
//------------------------------------------------------------------------------
template<class Type>
typename enable_if<is_interval_set<Type>, Type>::type&
flip(Type& object, const typename Type::element_type& operand)
{
    if(icl::contains(object, operand))
        return object -= operand;
    else
        return object += operand;
}

template<class Type>
typename enable_if<is_interval_set<Type>, Type>::type&
flip(Type& object, const typename Type::segment_type& segment)
{
    typedef typename Type::const_iterator const_iterator;
    typedef typename Type::interval_type  interval_type;
    // That which is common shall be subtracted
    // That which is not shall be added
    // So x has to be 'complementary added' or flipped
    interval_type span = segment;
    std::pair<const_iterator, const_iterator> exterior 
        = object.equal_range(span);

    const_iterator fst_ = exterior.first;
    const_iterator end_ = exterior.second;

    interval_type covered, left_over;
    const_iterator it_ = fst_;
    while(it_ != end_) 
    {
        covered = *it_++; 
        //[a      ...  : span
        //     [b ...  : covered
        //[a  b)       : left_over
        left_over = right_subtract(span, covered);
        icl::subtract(object, span & covered); //That which is common shall be subtracted
        icl::add(object, left_over);           //That which is not shall be added

        //...      d) : span
        //... c)      : covered
        //     [c  d) : span'
        span = left_subtract(span, covered);
    }

    //If span is not empty here, it_ is not in the set so it_ shall be added
    icl::add(object, span);
    return object;
}


template<class Type, class OperandT>
typename enable_if<is_concept_compatible<is_interval_set, Type, OperandT>, Type>::type&
flip(Type& object, const OperandT& operand)
{
    typedef typename OperandT::const_iterator const_iterator;

    if(operand.empty())
        return object;

    const_iterator common_lwb, common_upb;

    if(!Set::common_range(common_lwb, common_upb, operand, object))
        return object += operand;

    const_iterator it_ = operand.begin();

    // All elements of operand left of the common range are added
    while(it_ != common_lwb)
        icl::add(object, *it_++);
    // All elements of operand in the common range are symmertrically subtracted
    while(it_ != common_upb)
        icl::flip(object, *it_++);
    // All elements of operand right of the common range are added
    while(it_ != operand.end())
        icl::add(object, *it_++);

    return object;
}

//==============================================================================
//= Set selection
//==============================================================================
template<class Type>
typename enable_if<is_interval_set<Type>, Type>::type&
domain(Type& dom, const Type& object)
{
    typedef typename Type::const_iterator const_iterator;
    typedef typename Type::iterator       iterator;
    dom.clear();
    const_iterator it_    = object.begin();
    iterator       prior_ = dom.end();

    while(it_ != object.end())
        prior_ = icl::insert(dom, prior_, *it_++);

    return dom;
}

template<class Type>
typename enable_if<is_interval_set<Type>, Type>::type&
between(Type& in_between, const Type& object)
{
    typedef typename Type::const_iterator const_iterator;
    typedef typename Type::iterator       iterator;
    in_between.clear();
    const_iterator it_ = object.begin(), pred_;
    iterator prior_ = in_between.end();

    if(it_ != object.end())
        pred_ = it_++;

    while(it_ != object.end())
        prior_ = icl::insert(in_between, prior_, 
                             icl::between(*pred_++, *it_++));

    return in_between;
}


//==============================================================================
//= Streaming
//==============================================================================
template<class CharType, class CharTraits, class Type>
typename enable_if<is_interval_set<Type>, 
                   std::basic_ostream<CharType, CharTraits> >::type& 
operator << (std::basic_ostream<CharType, CharTraits>& stream, const Type& object)
{
    stream << "{";
    ICL_const_FORALL(typename Type, it_, object)
        stream << (*it_);

    return stream << "}";
}


}} // namespace boost icl

#endif



/* interval_set.hpp
PyalSzptS3iF+DWEapjxhVOnUMaJKJo+7CdOHrZmH1WHkPXuGK719AQdqI9jGz7fQ8vnV9A8VkP/+iayyqy3kHnhy91WP6f4pFl8sdUufJLfy8+yvbhuIoWfx7Xp37BvGK4+kbYcvQe/2eo0LsMDXxySyeZhI8l/76GepM+8T3QGEqxDaH27Mh3bMp3bxn1H8cES1jQyA36a8fyB6UX03N1H7QvdaY11Bo6dfYwGmSrMHWmDyeMt2KrqHRgROpEm2yyj+9FvmKrTGgyfznkP/02xl16Qh6ME3Xd9hDNbS3FumDQZK07FjAgRkuoMR0DRQbbmiBZNnGvHz4W/IvNPn+l6ghzupEjxhU5CJFIvwUqfGpKTWysbW7GH3Ba78SkCTqBsrU/+ldPJUmclSY6ZinvbNzHtP7txy28ldBf/oqC3u2nysBlkpWLErlYI2Fa6OknVjIbSyl4uGryWxkqthbxBJeSHyrEp5y9RcKYERKO88XtrOnfJ30cnanZjybE2Gjutkq9aNIpiw715mFw+dFONqUAhgcZaG1FZ5iDdXSjPzpW6o1JwNse0XMPeWQ5cKGglVKvc6FuCOlmd1cKfmjn0taYDf56dRG7gVkTfNyWxcnOasP4Lds69yvKDGL1b+Zt3CtXQ8oAKsnxsi9zWdm6xPRylikXcqbSLOl0+sYppN3HnZBCNrTHDNslVfM3EzZQt7M+2WHKytn5G3lt9yK7mKDkcV8D+CdPx4tYKWlU/h30YNEXK/iIKfp0L+cbRNDfyCEYON0R0zUc8FAefFviPAosb2UO/3ZC544CU0R/JZ0wOn79JGTqOrkyjehjZm0syh8RDGD5uN2Ztc4NeyCQqWZeF56NjWcXvmRjZYorIC3OoymQKrCyNYW7wHibXO2FRe4Ltvf8Zs6QbuKzMSXxtPcK2GXmhbN1vWnTxMK3SyYPGWi167JPEzVydSCPFkNpWJ1HRqRTU9qhgco+AS9VvpDsjdvOQ4Pe4wd8w9ZPncbtBA0MPilO9/EIqCdxLHRcyoVz0m0atN+aKBhdQr+9F0jEr0DFmLCml9yDTcS9q9gzi6tI0Pj1EHlL5gex71xL4rxLGrqhE2nQ5g69ULcLHYk928MgEqF9cxib1udADkkZOh67gTRxOg88VSWx1NROqBGnvCWSfPGSpfd0D6o/9jMbkUcwychlsHRLY1kRh8vFPJd/fF2Bp4kEZb57Qp40S9NzUFuPyj1B1WB8SUl2oyVcN99Vz2MBfNVSMsmEzX9kiVKaHJzbsIJHvEjS4bTKdnHOUEvfZ4K/IGiovOUeD7wdwXyka4/TdaHbNLTL1G89GnThMa4Qb6E9/AFZN1GRdZdmUW53JQoUcEWp6D1+1Uunj40ZISMygokebsTS9j1Y+ZGTiZkZzEEm7+1Rpq64/Zp5sohfnhrMY+yxMmhDBwp/mU+VmDRIdfhFrp31mr6r70XpbjwU/fY3qZAvuGLSSzl18JfAoDNPSjNi7lgjKeKuJUR7bqHW3FJHxH6rgyaw1xxBT51/jY1aPQJCkgKnlK8FXUxZOvaKktJPzpkkZlKbjwD6KMxI/oUrZakrkIHURcicX0+c9d3iJz3I6u/oee+p0mTStPlL12N80cGYUtvLPeC3jwTpV/pLMaS8ack6ZqqpS2KcxP+hf8BJy37WK1p64y53JBl5+rSRikIqB03k4l18imGnnubPoLJqWcxzjBWeoorOdtTyNp3zZJm4v0FGVdV205Iofnh/bxAPMiumiTjAmiVqRxYIeZvtsI/i2EbzS/j6tSxLjt16+ou8ml5CT6EgFEWd4k0kdziqtZ1F1VVSaLUz7OxaTvIwny6EOKFRr4tzOTPq8pYM=
*/