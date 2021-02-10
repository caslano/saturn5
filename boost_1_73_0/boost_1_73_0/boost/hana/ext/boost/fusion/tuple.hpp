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
YDfNbQLr0L11VHVEib3c/SqY3P1dMbn7b8Lkrg2TM77pINFmDOpjGHvT6CoEJWfmLKW7akuzeeXIctJptVz5n26Nvs923fIM8Pc1Ya5riDZsl39gF/9f6GMbM7DRxzqu99+N9itvtF9j5vX9a92J/w/bxL/W7vuV0bv2uvoP29n/g7bk5qc1yn5RtufRSexDu08OepVYTQ5NMU5aO95E+uwvVouNAh1s5FV1a+xQKxpwVtbZHApyhCYgNBIP6oSDatGgfoP4XWWotcQGbVGqNVC/jd3jeLPfnAzqN8t79GP3q/Rj79792LtnPzTG/3uy/fWYvkZdzezCa7L7pspOHZFrQsofhczmAsrvisy9eyHT2DO/2o7ZZKNYw5D9uzj38r5y6afJdhokE49IZOIGS6V41ttbt59Ii2vPST+JL5vGzcQPqxRrqWvo2MCAKFVcGuTTMVFMnI7trOPaSB8Z/ItBayG/5Onux/FocvLu/cXF2W4m2OHUw6Lw0m084ZYE+EbIIVhYXkWd7FYfq8tuPHI6D3Mn3TBVD3Wkr8LQC/g0vZuPnGTevKTBDJZLKMPXFQUSeyKDghgPtnRxqnp6dNDVtaVwHikaHxyfnfRggc09yh7xTfJbuNFzSsHo1mm+ptC0Z9gQ4w924qw7
*/