/*=============================================================================
    Copyright (c) 2003 Jonathan de Halleux (dehalleux@pelikhan.com)
    http://spirit.sourceforge.net/

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef BOOST_SPIRIT_ACTOR_DECREMENT_ACTOR_HPP
#define BOOST_SPIRIT_ACTOR_DECREMENT_ACTOR_HPP

#include <boost/spirit/home/classic/namespace.hpp>
#include <boost/spirit/home/classic/actor/ref_actor.hpp>

namespace boost { namespace spirit {

BOOST_SPIRIT_CLASSIC_NAMESPACE_BEGIN

    ///////////////////////////////////////////////////////////////////////////
    //  Summary:
    //  A semantic action policy that calls the -- operator on a reference.
    //  (This doc uses convention available in actors.hpp)
    //
    //  Actions:
    //      --ref;
    //
    //  Policy name:
    //      decrement_action
    //
    //  Policy holder, corresponding helper method:
    //      ref_actor, decrement_a( ref );
    //
    //  () operators: both.
    //
    //  See also ref_actor for more details.
    ///////////////////////////////////////////////////////////////////////////
    struct decrement_action
    {
        template<
            typename T
        >
        void act(T& ref_) const
        {
            --ref_;
        }
    };

    ///////////////////////////////////////////////////////////////////////////
    // helper method that creates a and_assign_actor.
    ///////////////////////////////////////////////////////////////////////////
    template<typename T>
    inline ref_actor<T,decrement_action> decrement_a(T& ref_)
    {
        return ref_actor<T,decrement_action>(ref_);
    }

BOOST_SPIRIT_CLASSIC_NAMESPACE_END

}}

#endif

/* decrement_actor.hpp
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
*/