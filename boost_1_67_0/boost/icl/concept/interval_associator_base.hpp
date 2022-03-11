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