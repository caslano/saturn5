/*-----------------------------------------------------------------------------+    
Copyright (c) 2011-2011: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_CONCEPT_INTERVAL_ASSOCIATOR_BASE_HPP_JOFA_110301
#define BOOST_ICL_CONCEPT_INTERVAL_ASSOCIATOR_BASE_HPP_JOFA_110301

#include <boost/icl/type_traits/domain_type_of.hpp>
#include <boost/icl/type_traits/interval_type_of.hpp>
#include <boost/icl/type_traits/is_combinable.hpp>
#include <boost/icl/concept/set_value.hpp>
#include <boost/icl/concept/map_value.hpp>
#include <boost/icl/concept/interval.hpp>

namespace boost{ namespace icl
{

//==============================================================================
//= Selection<IntervalSet|IntervalMap>
//==============================================================================
template<class Type> inline
typename enable_if<mpl::and_< is_interval_container<Type>
                            , is_discrete<typename domain_type_of<Type>::type> 
                            > 
                   , typename Type::const_iterator>::type
find(const Type& object, const typename domain_type_of<Type>::type& key_val)
{
    //CL typedef typename Type::const_iterator const_iterator;
    typedef typename Type::interval_type  interval_type;
    return object.find(icl::detail::unit_trail<interval_type>(key_val));
}

template<class Type> inline
typename enable_if<mpl::and_< is_interval_container<Type>
                            , is_continuous<typename domain_type_of<Type>::type> 
                            , has_dynamic_bounds<typename interval_type_of<Type>::type> 
                            > 
                   , typename Type::const_iterator>::type
find(const Type& object, const typename domain_type_of<Type>::type& key_val)
{
    //CL typedef typename Type::const_iterator const_iterator;
    typedef typename Type::interval_type  interval_type;
    return object.find(icl::singleton<interval_type>(key_val));
}

template<class Type> inline
typename enable_if<mpl::and_< is_interval_container<Type>
                            , is_continuous<typename domain_type_of<Type>::type> 
                            , is_static_right_open<typename interval_type_of<Type>::type> 
                            , boost::detail::is_incrementable<typename domain_type_of<Type>::type>
                            > 
                   , typename Type::const_iterator>::type
find(const Type& object, const typename domain_type_of<Type>::type& key_val)
{
    typedef typename Type::const_iterator const_iterator;
    typedef typename Type::interval_type  interval_type;
    const_iterator first_collision = object.lower_bound(icl::detail::unit_trail<interval_type>(key_val));
    // A part of the unit_trail(key_value)-interval may be found in the container, that
    // does not contain key_value. Therefore we have to check for its existence:
    return (  first_collision == object.end() 
           || icl::contains(key_value<Type>(first_collision), key_val) ) 
            ? first_collision 
            : object.end();
}

template<class Type> inline
typename enable_if<mpl::and_< is_interval_container<Type>
                            , is_continuous<typename domain_type_of<Type>::type> 
                            , is_static_left_open<typename interval_type_of<Type>::type> 
                            , boost::detail::is_incrementable<typename domain_type_of<Type>::type>
                            > 
                   , typename Type::const_iterator>::type
find(const Type& object, const typename domain_type_of<Type>::type& key_val)
{
    typedef typename Type::const_iterator const_iterator;
    typedef typename Type::interval_type  interval_type;
    const_iterator last_collision = object.upper_bound(icl::detail::unit_trail<interval_type>(key_val));
    if(last_collision != object.begin())
        --last_collision;
    // A part of the unit_trail(key_value)-interval may be found in the container, that
    // does not contain key_value. Therefore we have to check for its existence:
    return (  last_collision == object.end() 
           || icl::contains(key_value<Type>(last_collision), key_val) ) 
            ? last_collision 
            : object.end();
}

// NOTE: find(object, key) won't compile if key is of continuous type that does
// not implement in(de)crementation (e.g. std::string).

template<class Type> inline
typename enable_if< is_interval_container<Type>
                  , typename Type::const_iterator>::type
find(const Type& object, const typename interval_type_of<Type>::type& inter_val)
{
    return object.find(inter_val);
}

//==============================================================================
//= Morphisms
//==============================================================================
template<class Type>
typename enable_if<is_interval_container<Type>, Type>::type&
join(Type& object)
{
    typedef typename Type::interval_type interval_type;
    typedef typename Type::iterator      iterator;

    iterator it_ = object.begin();
    if(it_ == object.end()) 
        return object;

    iterator next_ = it_; next_++;

    while(next_ != object.end())
    {
        if( segmental::is_joinable<Type>(it_, next_) )
        {
            iterator fst_mem = it_;  // hold the first member
            
            // Go on while touching members are found
            it_++; next_++;
            while(     next_ != object.end()
                    && segmental::is_joinable<Type>(it_, next_) )
            { it_++; next_++; }

            // finally we arrive at the end of a sequence of joinable intervals
            // and it points to the last member of that sequence
            const_cast<interval_type&>(key_value<Type>(it_)) 
                = hull(key_value<Type>(it_), key_value<Type>(fst_mem));
            object.erase(fst_mem, it_);

            it_++; next_=it_; 
            if(next_!=object.end())
                next_++;
        }
        else { it_++; next_++; }
    }
    return object;
}

}} // namespace boost icl

#endif



/* interval_associator_base.hpp
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
*/