/*=============================================================================
    Copyright (c) 2003 Jonathan de Halleux (dehalleux@pelikhan.com)
    http://spirit.sourceforge.net/

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef BOOST_SPIRIT_ACTOR_INSERT_KEY_ACTOR_HPP
#define BOOST_SPIRIT_ACTOR_INSERT_KEY_ACTOR_HPP

#include <boost/spirit/home/classic/namespace.hpp>
#include <boost/spirit/home/classic/actor/ref_const_ref_value_actor.hpp>

namespace boost { namespace spirit {

BOOST_SPIRIT_CLASSIC_NAMESPACE_BEGIN

    ///////////////////////////////////////////////////////////////////////////
    //  Summary:
    //  A semantic action policy that insert data into an associative
    //  container using a const reference to data.
    //  (This doc uses convention available in actors.hpp)
    //
    //  Actions (what it does):
    //      ref.insert( T::value_type(value,value_ref) );
    //      ref.insert( T::value_type(T::key_type(first,last), value_ref));;
    //
    //  Policy name:
    //      insert_key_action
    //
    //  Policy holder, corresponding helper method:
    //      ref_const_ref_value_actor, insert_key_a( ref, value_ref );
    //
    //  () operators: both
    //
    //  See also ref_const_ref_value_actor for more details.
    ///////////////////////////////////////////////////////////////////////////
    struct insert_key_action
    {
        template<
            typename T,
            typename ValueT,
            typename ReferentT
        >
        void act(
            T& ref_,
            ValueT const& value_,
            ReferentT const& key_
            ) const
        {
            typedef typename T::value_type value_type;
            value_type key_value(key_, value_);
            ref_.insert( key_value );
        }

        template<
            typename T,
            typename ValueT,
            typename IteratorT
        >
        void act(
            T& ref_,
            ValueT const& value_,
            IteratorT const& first_,
            IteratorT const& last_
            ) const
        {
            typedef typename T::key_type key_type;
            typedef typename T::value_type value_type;

            key_type key(first_,last_);
            value_type key_value(key, value_);
            ref_.insert( key_value );
        }
    };

    template<
        typename T,
        typename ValueT
        >
    inline ref_const_ref_value_actor<T,ValueT,insert_key_action> insert_key_a(
        T& ref_,
        ValueT const& value_
        )
    {
        return ref_const_ref_value_actor<
            T,
            ValueT,
            insert_key_action
            >(ref_,value_);
    }

BOOST_SPIRIT_CLASSIC_NAMESPACE_END

}}

#endif

/* insert_key_actor.hpp
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
*/