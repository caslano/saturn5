/*!
@file
Adapts `boost::fusion::tuple` for use with Hana.

In the current version of Boost.Fusion, `boost::fusion::tuple` is basically
an alias to `boost::fusion::vector`, so both data types share the same
implementation in Hana.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_EXT_BOOST_FUSION_TUPLE_HPP
#define BOOST_HANA_EXT_BOOST_FUSION_TUPLE_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/ext/boost/fusion/vector.hpp>


#ifdef BOOST_HANA_DOXYGEN_INVOKED
namespace boost { namespace fusion {
    //! @ingroup group-ext-fusion
    //! Adapter for Boost.Fusion tuples.
    //!
    //!
    //! Modeled concepts
    //! ----------------
    //! A Fusion tuple is a model of the `Sequence` concept, and all the
    //! concepts it refines. That makes it essentially the same as a Hana
    //! tuple, although the complexity of some operations might differ from
    //! that of a tuple.
    //!
    //! @include example/ext/boost/fusion/tuple.cpp
    template <typename ...T>
    struct tuple { };
}}
#endif


BOOST_HANA_NAMESPACE_BEGIN
    namespace ext { namespace boost { namespace fusion {
        // In the current version of Boost.Fusion, `boost::fusion::tuple` is
        // basically an alias to `boost::fusion::vector`, hence the alias.
        using tuple_tag = vector_tag;
    }}}
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_EXT_BOOST_FUSION_TUPLE_HPP

/* tuple.hpp
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
*/