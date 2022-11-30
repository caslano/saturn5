/*=============================================================================
    Copyright (c) 2003 Jonathan de Halleux (dehalleux@pelikhan.com)
    http://spirit.sourceforge.net/

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef BOOST_SPIRIT_ACTOR_PUSH_FRONT_ACTOR_HPP
#define BOOST_SPIRIT_ACTOR_PUSH_FRONT_ACTOR_HPP

#include <boost/spirit/home/classic/namespace.hpp>
#include <boost/spirit/home/classic/actor/ref_value_actor.hpp>
#include <boost/spirit/home/classic/actor/ref_const_ref_actor.hpp>

namespace boost { namespace spirit {

BOOST_SPIRIT_CLASSIC_NAMESPACE_BEGIN

    ///////////////////////////////////////////////////////////////////////////
    //  Summary:
    //
    //  A semantic action policy that appends a value to the front of a
    //  container.
    //  (This doc uses convention available in actors.hpp)
    //
    //  Actions (what it does and what ref, value_ref must support):
    //      ref.push_front( value );
    //      ref.push_front( T::value_type(first,last) );
    //      ref.push_front( value_ref );
    //
    //  Policy name:
    //      push_front_action
    //
    //  Policy holder, corresponding helper method:
    //      ref_value_actor, push_front_a( ref );
    //      ref_const_ref_actor, push_front_a( ref, value_ref );
    //
    //  () operators: both
    //
    //  See also ref_value_actor and ref_const_ref_actor for more details.
    ///////////////////////////////////////////////////////////////////////////
    struct push_front_action
    {
        template<
            typename T,
            typename ValueT
        >
        void act(T& ref_, ValueT const& value_) const
        {
            ref_.push_front( value_ );
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
            typedef typename T::value_type value_type;
            value_type value(first_,last_);

            ref_.push_front( value );
        }
    };

    template<typename T>
    inline ref_value_actor<T,push_front_action> push_front_a(T& ref_)
    {
        return ref_value_actor<T,push_front_action>(ref_);
    }

    template<
        typename T,
        typename ValueT
    >
    inline ref_const_ref_actor<T,ValueT,push_front_action> push_front_a(
        T& ref_,
        ValueT const& value_
    )
    {
        return ref_const_ref_actor<T,ValueT,push_front_action>(ref_,value_);
    }

BOOST_SPIRIT_CLASSIC_NAMESPACE_END

}}

#endif

/* push_front_actor.hpp
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
*/