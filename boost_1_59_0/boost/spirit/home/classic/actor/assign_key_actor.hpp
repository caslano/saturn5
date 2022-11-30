/*=============================================================================
    Copyright (c) 2003 Jonathan de Halleux (dehalleux@pelikhan.com)
    http://spirit.sourceforge.net/

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef BOOST_SPIRIT_ACTOR_ASSIGN_KEY_ACTOR_HPP
#define BOOST_SPIRIT_ACTOR_ASSIGN_KEY_ACTOR_HPP

#include <boost/spirit/home/classic/namespace.hpp>
#include <boost/spirit/home/classic/actor/ref_const_ref_value_actor.hpp>
#include <boost/spirit/home/classic/actor/ref_const_ref_const_ref_a.hpp>

namespace boost { namespace spirit {

BOOST_SPIRIT_CLASSIC_NAMESPACE_BEGIN

    struct assign_key_action
    {
        template<
            typename T,
            typename ValueT,
            typename KeyT
        >
        void act(T& ref_, ValueT const& value_, KeyT const& key_) const
        {
            ref_[ key_ ] = value_;
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
            key_type key(first_,last_);

            ref_[key] = value_;
        }
    };

    template<
        typename T,
        typename ValueT
    >
    inline ref_const_ref_value_actor<T,ValueT,assign_key_action>
        assign_key_a(T& ref_, ValueT const& value_)
    {
        return ref_const_ref_value_actor<T,ValueT,assign_key_action>(
            ref_,
            value_
            );
    }

    template<
        typename T,
        typename ValueT,
        typename KeyT
    >
    inline ref_const_ref_const_ref_actor<
        T,
        ValueT,
        KeyT,
        assign_key_action
    >
        assign_key_a(
            T& ref_,
            ValueT const& value_,
            KeyT const& key_
    )
    {
        return ref_const_ref_const_ref_actor<
            T,
            ValueT,
            KeyT,
            assign_key_action
        >(
            ref_,
            value_,
            key_
            );
    }

BOOST_SPIRIT_CLASSIC_NAMESPACE_END

}}

#endif

/* assign_key_actor.hpp
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
*/