/*=============================================================================
    Copyright (c) 2003 Jonathan de Halleux (dehalleux@pelikhan.com)
    http://spirit.sourceforge.net/

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef BOOST_SPIRIT_ACTOR_ASSIGN_ACTOR_HPP
#define BOOST_SPIRIT_ACTOR_ASSIGN_ACTOR_HPP

#include <boost/spirit/home/classic/namespace.hpp>
#include <boost/spirit/home/classic/actor/ref_value_actor.hpp>
#include <boost/spirit/home/classic/actor/ref_const_ref_actor.hpp>

namespace boost { namespace spirit {

BOOST_SPIRIT_CLASSIC_NAMESPACE_BEGIN

    ///////////////////////////////////////////////////////////////////////////
    //  Summary:
    //  A semantic action policy that applies the assignment operator.
    //  (This doc uses convention available in actors.hpp)
    //
    //  Actions (what it does):
    //      ref = value;
    //      ref = T(first,last);
    //      ref = value_ref;
    //
    //  Policy name:
    //      assign_action
    //
    //  Policy holder, corresponding helper method:
    //      ref_value_actor, assign_a( ref );
    //      ref_const_ref_actor, assign_a( ref, value_ref );
    //
    //  () operators: both
    //
    //  See also ref_value_actor and ref_const_ref_actor for more details.
    ///////////////////////////////////////////////////////////////////////////
    struct assign_action
    {
        template<
            typename T,
            typename ValueT
        >
        void act(T& ref_, ValueT const& value_) const
        {
            ref_ = value_;
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
            typedef T value_type;
#ifndef BOOST_NO_TEMPLATED_ITERATOR_CONSTRUCTORS
            value_type value(first_,last_);
#else
            value_type value;
            std::copy(first_, last_, std::inserter(value, value.end()));
#endif
            ref_ = value;
        }
    };

    // Deprecated. Please use assign_a
    template<typename T>
    inline ref_value_actor<T,assign_action> assign(T& ref_)
    {
        return ref_value_actor<T,assign_action>(ref_);
    }

    template<typename T>
    inline ref_value_actor<T,assign_action> assign_a(T& ref_)
    {
        return ref_value_actor<T,assign_action>(ref_);
    }

    template<
        typename T,
        typename ValueT
    >
    inline ref_const_ref_actor<T,ValueT,assign_action> assign_a(
        T& ref_,
        ValueT const& value_
    )
    {
        return ref_const_ref_actor<T,ValueT,assign_action>(ref_,value_);
    }

BOOST_SPIRIT_CLASSIC_NAMESPACE_END

}}

#endif

/* assign_actor.hpp
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
*/