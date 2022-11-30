/*=============================================================================
    Copyright (c) 2003 Jonathan de Halleux (dehalleux@pelikhan.com)
    http://spirit.sourceforge.net/

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef BOOST_SPIRIT_ACTOR_INCREMENT_ACTOR_HPP
#define BOOST_SPIRIT_ACTOR_INCREMENT_ACTOR_HPP

#include <boost/spirit/home/classic/namespace.hpp>
#include <boost/spirit/home/classic/actor/ref_actor.hpp>

namespace boost { namespace spirit {

BOOST_SPIRIT_CLASSIC_NAMESPACE_BEGIN

    ///////////////////////////////////////////////////////////////////////////
    //  Summary:
    //  A semantic action policy that calls the ++ operator on a reference.
    //  (This doc uses convention available in actors.hpp)
    //
    //  Actions:
    //      ++ref;
    //
    //  Policy name:
    //      increment_action
    //
    //  Policy holder, corresponding helper method:
    //      ref_actor, increment_a( ref );
    //
    //  () operators: both.
    //
    //  See also ref_actor for more details.
    ///////////////////////////////////////////////////////////////////////////
    struct increment_action
    {
        template<
            typename T
        >
        void act(T& ref_) const
        {
            ++ref_;
        }
    };

    ///////////////////////////////////////////////////////////////////////////
    // helper method that creates a increment_actor.
    ///////////////////////////////////////////////////////////////////////////
    template<typename T>
    inline ref_actor<T,increment_action> increment_a(T& ref_)
    {
        return ref_actor<T,increment_action>(ref_);
    }

BOOST_SPIRIT_CLASSIC_NAMESPACE_END

}}

#endif

/* increment_actor.hpp
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
*/