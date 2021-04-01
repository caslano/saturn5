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
aW7YCZVH80slEehFpQesI+4W2qpK6HxDAxwFXeciP+yzEW7z6yP/L81aKFw64L7H4xTy4EnOirmUFE6yymSNMUKsp3929vusiOfzZmqFWH0YBnl2L6gmM564U8Pyg3mro/dSt6WqoiSax85wBmtAM78q9kX6RgkkImN95GQ8r0jh4rUpOwA3jvLVNwCdCcS+4EeWy2QB1ECipQLl2/mmKFhhxfCkhO1yexEMly7wOA8TAJ4Ou8wO6PLsbgc1MlI3hGxQnmiQT1PdwOkwsc0XZsjDWfQkTMkDPRaSKrxUtCUmJaU6iWAAEff6sBmt2E6gXEW1Qmoq2WcoD9JTSsyIbERUU3zZ/FrxXM3orRTFHHpUHaWhxy6yjHCD+pLqHUOIgbcwUNSl/aI9vM7avQLGQVfIfxRaXqRHIt2l2VNC5uu0gczFTwPsse2Z9rKGE3rKc5JFuySI0P6F4Y3W2x/ODhvan31+bEcK9aL8LaZVlG0vOwQOfEWyGjGsHsXIQxxU7nggQdcopPqmvetbwRL56btDu6vljFqtyYnyILPqKqlNMno01yYgoHYcIg==
*/