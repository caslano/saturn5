/*=============================================================================
    Copyright (c) 2003 Jonathan de Halleux (dehalleux@pelikhan.com)
    http://spirit.sourceforge.net/

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef BOOST_SPIRIT_ACTOR_REF_CONST_REF_ACTOR_HPP
#define BOOST_SPIRIT_ACTOR_REF_CONST_REF_ACTOR_HPP

#include <boost/spirit/home/classic/namespace.hpp>

namespace boost { namespace spirit {

BOOST_SPIRIT_CLASSIC_NAMESPACE_BEGIN

    ///////////////////////////////////////////////////////////////////////////
    //  Summary:
    //  A semantic action policy holder. This holder stores a reference to ref
    //  and a const reference to value_ref.
    //  act methods are feed with ref and value_ref. The parse result is
    //  not used by this holder.
    //
    //  (This doc uses convention available in actors.hpp)
    //
    //  Constructor:
    //      ...(T& ref_, ValueT const& value_ref_);
    //      where ref_ and value_ref_ are stored in the holder.
    //
    //  Action calls:
    //      act(ref, value_ref);
    //
    //  () operators: both
    //
    ///////////////////////////////////////////////////////////////////////////
    template<
        typename T,
        typename ValueT,
        typename ActionT
    >
    class ref_const_ref_actor : public ActionT
    {
    private:
        T& ref;
        ValueT const& value_ref;
    public:
        ref_const_ref_actor(
            T& ref_,
            ValueT const& value_ref_
            )
        :
            ref(ref_),
            value_ref(value_ref_)
        {}


        template<typename T2>
        void operator()(T2 const& /*val*/) const
        {
            this->act(ref,value_ref); // defined in ActionT
        }


        template<typename IteratorT>
            void operator()(
            IteratorT const& /*first*/,
            IteratorT const& /*last*/
            ) const
        {
            this->act(ref,value_ref); // defined in ActionT
        }
    };

BOOST_SPIRIT_CLASSIC_NAMESPACE_END

}}

#endif

/* ref_const_ref_actor.hpp
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
*/