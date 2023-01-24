/*!
@file
Defines `boost::hana::Metafunction`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CONCEPT_METAFUNCTION_HPP
#define BOOST_HANA_CONCEPT_METAFUNCTION_HPP

#include <boost/hana/fwd/concept/metafunction.hpp>

#include <boost/hana/config.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/detail/integral_constant.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    namespace detail {
        template <typename F, typename Tag = typename tag_of<F>::type>
        struct metafunction_dispatch
            : hana::integral_constant<bool,
                Metafunction<Tag>::value
            >
        { };

        template <typename F>
        struct metafunction_dispatch<F, F>
            : hana::integral_constant<bool, false>
        { };
    }

    template <typename F>
    struct Metafunction
        : detail::metafunction_dispatch<F>
    { };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CONCEPT_METAFUNCTION_HPP

/* metafunction.hpp
XSHahmF6ceTd2Ztz0dGs2SY32IKt4k6jPVyeFRJrcEMW1uXPpg+CVeJOAYmuPNMx4BtTnpkgxZsGTQeCvzR90HUvypR7uzLJ3QEjLlF7vjqqXmeBJpeLdwZOiusCULt1wApj6zAN6iCmN5aLEqSX9peLQfg9EsABg1V5X9wdOMT81lwo2/5eeVabWPM+QR8H99Lt6iENrxxY7hAM2UXbONE2nEN/G/72wt87UEILlNAAJSDqoMnBN6AQuWPQ1GYKiTsTUPKGJoZ8SeWZRmjiB6bB4C+gj00HuKm5IeiGvrC3lmcO912r7p3e7DWCtFEGXVVe2yrW9A1SZOV5AGl6C4juktU0iImt86RjeGhFeaYo1tDZSQDyA1MT5AVIUsAeWF0GopR6fJW2owJPZsGDoN7AMUaHhvhm9iXYfBepFrnLjFuL1HWp6gF1c3LE0oTCYF+CxRf3hiHnFwKoBCTC9Tq9Jq/gwcGglPbSKgoadVeDfkIjvFB1JKsFKS63utJWrG62qkeUogH1ZG3r5plr9ybKjRZTo1pqk78J+7Jllnht5sqBCnNW8pY4eCMlqNLAUkhe23rPPxZm9W+6MOuDTWMxLFOBdbWyzlqmWBSnWcm3AGNhiUGdUybLtzFQcpg9DidJnD4cPeT83Ks6EkHM7r71dcGmoCPhAN//rzjQi52LomEpuTAs2djcCRiOTdVfqw3amS05ruoKCyqg
*/