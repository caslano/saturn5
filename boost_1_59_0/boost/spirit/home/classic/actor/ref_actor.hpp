/*=============================================================================
    Copyright (c) 2003 Jonathan de Halleux (dehalleux@pelikhan.com)
    http://spirit.sourceforge.net/

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef BOOST_SPIRIT_ACTOR_REF_ACTOR_HPP
#define BOOST_SPIRIT_ACTOR_REF_ACTOR_HPP

#include <boost/spirit/home/classic/namespace.hpp>

namespace boost { namespace spirit {

BOOST_SPIRIT_CLASSIC_NAMESPACE_BEGIN

    ///////////////////////////////////////////////////////////////////////////
    //  Summary:
    //  A semantic action policy holder. This holder stores a reference to ref,
    //  act methods are fead with this reference. The parse result is not used
    //  by this holder.
    //
    //  (This doc uses convention available in actors.hpp)
    //
    //  Constructor:
    //      ...(T& ref_);
    //      where ref_ is stored.
    //
    //  Action calls:
    //      act(ref);
    //
    //  () operators: both
    //
    ///////////////////////////////////////////////////////////////////////////
    template<
        typename T,
        typename ActionT
    >
    class ref_actor : public ActionT
    {
    private:
        T& ref;
    public:
        explicit
        ref_actor(T& ref_)
        : ref(ref_){}


        template<typename T2>
        void operator()(T2 const& /*val*/) const
        {
            this->act(ref); // defined in ActionT
        }


        template<typename IteratorT>
        void operator()(
            IteratorT const& /*first*/,
            IteratorT const& /*last*/
            ) const
        {
            this->act(ref); // defined in ActionT
        }
    };

BOOST_SPIRIT_CLASSIC_NAMESPACE_END

}}

#endif

/* ref_actor.hpp
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
*/