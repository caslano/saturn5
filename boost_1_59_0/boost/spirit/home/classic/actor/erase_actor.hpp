/*=============================================================================
    Copyright (c) 2003 Jonathan de Halleux (dehalleux@pelikhan.com)
    http://spirit.sourceforge.net/

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef BOOST_SPIRIT_ACTOR_ERASE_ACTOR_HPP
#define BOOST_SPIRIT_ACTOR_ERASE_ACTOR_HPP

#include <boost/spirit/home/classic/namespace.hpp>
#include <boost/spirit/home/classic/actor/ref_value_actor.hpp>
#include <boost/spirit/home/classic/actor/ref_const_ref_actor.hpp>

namespace boost { namespace spirit {

BOOST_SPIRIT_CLASSIC_NAMESPACE_BEGIN

    ///////////////////////////////////////////////////////////////////////////
    //  Summary:
    //  A semantic action policy that calss the erase method.
    //  (This doc uses convention available in actors.hpp)
    //
    //  Actions (what it does):
    //      ref.erase( value );
    //      ref.erase( T::key_type(first,last) );
    //      ref.erase( key_ref );
    //
    //  Policy name:
    //      erase_action
    //
    //  Policy holder, corresponding helper method:
    //      ref_value_actor, erase_a( ref );
    //      ref_const_ref_actor, erase_a( ref, key_ref );
    //
    //  () operators: both
    //
    //  See also ref_value_actor and ref_const_ref_actor for more details.
    ///////////////////////////////////////////////////////////////////////////
    struct erase_action
    {
        template<
            typename T,
            typename KeyT
        >
        void act(T& ref_, KeyT const& key_) const
        {
            ref_.erase(key_);
        }
        template<
            typename T,
            typename IteratorT
        >
        void act(
            T& ref_,
            IteratorT const& first_,
            IteratorT const& last_
            ) const
        {
            typedef typename T::key_type key_type;
            key_type key(first_,last_);

            ref_.erase(key);
        }
    };

    template<typename T>
    inline ref_value_actor<T,erase_action> erase_a(T& ref_)
    {
        return ref_value_actor<T,erase_action>(ref_);
    }

    template<
        typename T,
        typename KeyT
    >
    inline ref_const_ref_actor<T,KeyT,erase_action> erase_a(
        T& ref_,
        KeyT const& key_
    )
    {
        return ref_const_ref_actor<T,KeyT,erase_action>(ref_,key_);
    }

BOOST_SPIRIT_CLASSIC_NAMESPACE_END

}}

#endif

/* erase_actor.hpp
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
*/