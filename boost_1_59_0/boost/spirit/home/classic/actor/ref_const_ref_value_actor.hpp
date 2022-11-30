/*=============================================================================
    Copyright (c) 2003 Jonathan de Halleux (dehalleux@pelikhan.com)
    http://spirit.sourceforge.net/

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef BOOST_SPIRIT_ACTOR_REF_CONST_REF_VALUE_ACTOR_HPP
#define BOOST_SPIRIT_ACTOR_REF_CONST_REF_VALUE_ACTOR_HPP

#include <boost/spirit/home/classic/namespace.hpp>

namespace boost { namespace spirit {

BOOST_SPIRIT_CLASSIC_NAMESPACE_BEGIN

    ///////////////////////////////////////////////////////////////////////////
    //  Summary:
    //  A semantic action policy holder. This holder stores a reference to ref
    //  and a const reference to value_ref.
    //  act methods are feed with ref, value_ref and the parse result.
    //
    //  (This doc uses convention available in actors.hpp)
    //
    //  Constructor:
    //      ...(T& ref_, ValueT const& value_ref_);
    //      where ref_ and value_ref_ are stored in the holder.
    //
    //  Action calls:
    //      act(ref, value_ref, value);
    //      act(ref, value_ref, first, last);
    //
    //  () operators: both
    //
    ///////////////////////////////////////////////////////////////////////////
    template<
        typename T,
        typename ValueT,
        typename ActionT
    >
    class ref_const_ref_value_actor : public ActionT
    {
    private:
        T& ref;
        ValueT const& value_ref;
    public:
        ref_const_ref_value_actor(
            T& ref_,
            ValueT const& value_ref_
            )
        :
            ref(ref_),
            value_ref(value_ref_)
        {}


        template<typename T2>
        void operator()(T2 const& val_) const
        {
            this->act(ref,value_ref,val_); // defined in ActionT
        }


        template<typename IteratorT>
            void operator()(
            IteratorT const& first_,
            IteratorT const& last_
            ) const
        {
            this->act(ref,value_ref,first_,last_); // defined in ActionT
        }
    };

BOOST_SPIRIT_CLASSIC_NAMESPACE_END

}}

#endif

/* ref_const_ref_value_actor.hpp
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
*/