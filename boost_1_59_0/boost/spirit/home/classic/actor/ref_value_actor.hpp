/*=============================================================================
    Copyright (c) 2003 Jonathan de Halleux (dehalleux@pelikhan.com)
    Copyright (c) 2011 Bryce Lelbach
    http://spirit.sourceforge.net/

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef BOOST_SPIRIT_ACTOR_REF_VALUE_ACTOR_HPP
#define BOOST_SPIRIT_ACTOR_REF_VALUE_ACTOR_HPP

#include <boost/detail/workaround.hpp>

#include <boost/spirit/home/classic/namespace.hpp>

namespace boost { namespace spirit {

BOOST_SPIRIT_CLASSIC_NAMESPACE_BEGIN

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
#pragma warning(push)
#pragma warning(disable:4512) //assignment operator could not be generated
#endif

    ///////////////////////////////////////////////////////////////////////////
    //  Summary:
    //  A semantic action policy holder. This holder stores a reference to ref.
    //  act methods are feed with ref and the parse result.
    //
    //  (This doc uses convention available in actors.hpp)
    //
    //  Constructor:
    //      ...(T& ref_);
    //      where ref_ is stored.
    //
    //  Action calls:
    //      act(ref, value);
    //      act(ref, first,last);
    //
    //  () operators: both
    //
    ///////////////////////////////////////////////////////////////////////////
    template<
        typename T,
        typename ActionT
    >
    class ref_value_actor : public ActionT
    {
    private:
        T& ref;
    public:
        explicit
        ref_value_actor(T& ref_)
        : ref(ref_){}


        template<typename T2>
        void operator()(T2 const& val_) const
        {
            this->act(ref,val_); // defined in ActionT
        }


        template<typename IteratorT>
        void operator()(
            IteratorT const& first_,
            IteratorT const& last_
            ) const
        {
            this->act(ref,first_,last_); // defined in ActionT
        }
    };

BOOST_SPIRIT_CLASSIC_NAMESPACE_END

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
#pragma warning(pop)
#endif

}}

#endif

/* ref_value_actor.hpp
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
*/