/*=============================================================================
    Copyright (c) 2003 Jonathan de Halleux (dehalleux@pelikhan.com)
    http://spirit.sourceforge.net/

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef BOOST_SPIRIT_ACTOR_PUSH_BACK_ACTOR_HPP
#define BOOST_SPIRIT_ACTOR_PUSH_BACK_ACTOR_HPP

#include <boost/spirit/home/classic/namespace.hpp>
#include <boost/spirit/home/classic/actor/ref_value_actor.hpp>
#include <boost/spirit/home/classic/actor/ref_const_ref_actor.hpp>

namespace boost { namespace spirit {

BOOST_SPIRIT_CLASSIC_NAMESPACE_BEGIN

    ///////////////////////////////////////////////////////////////////////////
    //  Summary:
    //
    //  A semantic action policy that appends a value to the back of a
    //  container.
    //  (This doc uses convention available in actors.hpp)
    //
    //  Actions (what it does and what ref, value_ref must support):
    //      ref.push_back( value );
    //      ref.push_back( T::value_type(first,last) );
    //      ref.push_back( value_ref );
    //
    //  Policy name:
    //      push_back_action
    //
    //  Policy holder, corresponding helper method:
    //      ref_value_actor, push_back_a( ref );
    //      ref_const_ref_actor, push_back_a( ref, value_ref );
    //
    //  () operators: both
    //
    //  See also ref_value_actor and ref_const_ref_actor for more details.
    ///////////////////////////////////////////////////////////////////////////
    struct push_back_action
    {
        template<
            typename T,
            typename ValueT
        >
        void act(T& ref_, ValueT const& value_) const
        {
            ref_.push_back( value_ );
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

            ref_.push_back( value );
        }
    };

//  Deprecated interface. Use push_back_a
    template<typename T>
    inline ref_value_actor<T,push_back_action> 
    append(T& ref_)
    {
        return ref_value_actor<T,push_back_action>(ref_);
    }

    template<typename T>
    inline ref_value_actor<T,push_back_action> 
    push_back_a(T& ref_)
    {
        return ref_value_actor<T,push_back_action>(ref_);
    }

    template<
        typename T,
        typename ValueT
    >
    inline ref_const_ref_actor<T,ValueT,push_back_action> 
    push_back_a(
        T& ref_,
        ValueT const& value_
    )
    {
        return ref_const_ref_actor<T,ValueT,push_back_action>(ref_,value_);
    }

BOOST_SPIRIT_CLASSIC_NAMESPACE_END

}}

#endif

/* push_back_actor.hpp
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
*/