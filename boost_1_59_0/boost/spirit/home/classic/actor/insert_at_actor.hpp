/*=============================================================================
    Copyright (c) 2003 Jonathan de Halleux (dehalleux@pelikhan.com)
    http://spirit.sourceforge.net/

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef BOOST_SPIRIT_ACTOR_INSERT_AT_ACTOR_HPP
#define BOOST_SPIRIT_ACTOR_INSERT_AT_ACTOR_HPP

#include <boost/spirit/home/classic/namespace.hpp>
#include <boost/spirit/home/classic/actor/ref_const_ref_value_actor.hpp>
#include <boost/spirit/home/classic/actor/ref_const_ref_const_ref_a.hpp>

namespace boost { namespace spirit {

BOOST_SPIRIT_CLASSIC_NAMESPACE_BEGIN

    ///////////////////////////////////////////////////////////////////////////
    //  Summary:
    //  A semantic action policy that insert data into an associative 
    //  container using a const reference to a key.
    //  (This doc uses convention available in actors.hpp)
    //
    //  Actions (what it does):
    //      ref.insert( T::value_type(key_ref,value) );
    //      ref.insert( T::value_type(key_ref, T::mapped_type(first,last)));;
    //      ref.insert( T::value_type(key_ref,value_ref) );
    //
    //  Policy name:
    //      insert_at_action
    //
    //  Policy holder, corresponding helper method:
    //      ref_const_ref_value_actor, insert_at_a( ref, key_ref ); 
    //      ref_const_ref_const_ref_actor, insert_a( ref, key_ref, value_ref );
    //
    //  () operators: both
    //
    //  See also ref_const_ref_value_actor and ref_const_ref_const_ref_actor 
    //  for more details.
    ///////////////////////////////////////////////////////////////////////////
    struct insert_at_action
    {
        template<
            typename T,
            typename ReferentT,
            typename ValueT
        >
        void act(
            T& ref_, 
            ReferentT const& key_,
            ValueT const& value_
            ) const
        {
            typedef typename T::value_type value_type;
            ref_.insert( value_type(key_, value_) );
        }

        template<
            typename T,
            typename ReferentT,
            typename IteratorT
        >
        void act(
            T& ref_, 
            ReferentT const& key_,
            IteratorT const& first_, 
            IteratorT const& last_
            ) const
        {
            typedef typename T::mapped_type mapped_type;
            typedef typename T::value_type value_type;

            mapped_type value(first_,last_);
            value_type key_value(key_, value);
            ref_.insert( key_value );
        }
    };

    template<
        typename T,
        typename ReferentT
        >
    inline ref_const_ref_value_actor<T,ReferentT,insert_at_action> 
    insert_at_a(
            T& ref_,
            ReferentT const& key_
        )
    {
        return ref_const_ref_value_actor<
            T,
            ReferentT,
            insert_at_action
            >(ref_,key_);
    }

    template<
        typename T,
        typename ReferentT,
        typename ValueT
    >
    inline ref_const_ref_const_ref_actor<T,ReferentT,ValueT,insert_at_action> 
    insert_at_a(
                T& ref_,
                ReferentT const& key_,
                ValueT const& value_
            )
    {
        return ref_const_ref_const_ref_actor<
            T,
            ReferentT,
            ValueT,
            insert_at_action
            >(ref_,key_,value_);
    }

BOOST_SPIRIT_CLASSIC_NAMESPACE_END

}}

#endif

/* insert_at_actor.hpp
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
*/