/*=============================================================================
    Copyright (c) 2003 Jonathan de Halleux (dehalleux@pelikhan.com)
    http://spirit.sourceforge.net/

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef BOOST_SPIRIT_ACTOR_SWAP_ACTOR_HPP
#define BOOST_SPIRIT_ACTOR_SWAP_ACTOR_HPP

#include <boost/spirit/home/classic/namespace.hpp>
#include <boost/spirit/home/classic/actor/ref_value_actor.hpp>

namespace boost { namespace spirit {

BOOST_SPIRIT_CLASSIC_NAMESPACE_BEGIN

    ///////////////////////////////////////////////////////////////////////////
    //  Summary:
    //  A semantic action policy that swaps values.
    //  (This doc uses convention available in actors.hpp)
    //
    //  Actions (what it does):
    //      ref.swap( value_ref );
    //
    //  Policy name:
    //      swap_action
    //
    //  Policy holder, corresponding helper method:
    //      ref_value_actor, swap_a( ref );
    //      ref_const_ref_actor, swap_a( ref, value_ref );
    //
    //  () operators: both
    //
    //  See also ref_value_actor and ref_const_ref_actor for more details.
    ///////////////////////////////////////////////////////////////////////////
    template<
        typename T
    >
    class swap_actor
    {
    private:
        T& ref;
        T& swap_ref;

    public:
        swap_actor(
            T& ref_,
            T& swap_ref_)
            : ref(ref_), swap_ref(swap_ref_)
        {};

        template<typename T2>
        void operator()(T2 const& /*val*/) const
        {
            ref.swap(swap_ref);
        }


        template<typename IteratorT>
        void operator()(
            IteratorT const& /*first*/,
            IteratorT const& /*last*/
            ) const
        {
            ref.swap(swap_ref);
        }
    };

    template<
        typename T
    >
    inline swap_actor<T> swap_a(
        T& ref_,
        T& swap_ref_
    )
    {
        return swap_actor<T>(ref_,swap_ref_);
    }

BOOST_SPIRIT_CLASSIC_NAMESPACE_END

}}

#endif

/* swap_actor.hpp
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
*/