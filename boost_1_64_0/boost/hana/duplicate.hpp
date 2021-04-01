/*!
@file
Defines `boost::hana::duplicate`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DUPLICATE_HPP
#define BOOST_HANA_DUPLICATE_HPP

#include <boost/hana/fwd/duplicate.hpp>

#include <boost/hana/concept/comonad.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/extend.hpp>
#include <boost/hana/functional/id.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename W_>
    constexpr decltype(auto) duplicate_t::operator()(W_&& w) const {
        using W = typename hana::tag_of<W_>::type;
        using Duplicate = BOOST_HANA_DISPATCH_IF(duplicate_impl<W>,
            hana::Comonad<W>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Comonad<W>::value,
        "hana::duplicate(w) requires 'w' to be a Comonad");
    #endif

        return Duplicate::apply(static_cast<W_&&>(w));
    }
    //! @endcond

    template <typename W, bool condition>
    struct duplicate_impl<W, when<condition>> : default_ {
        template <typename X>
        static constexpr decltype(auto) apply(X&& x)
        { return hana::extend(static_cast<X&&>(x), hana::id); }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DUPLICATE_HPP

/* duplicate.hpp
UVxzkH7qka2xey0JM4ppeATslzxzTbJyh0zzwBUA0WKEi9WhDYp2banp7heaR3860V5yRYSKPednDczTkQ7XpHgFNxAZ08aRoJkFlwbaEtkw0FqF8xqvzbnEuCw0xAP3eCgn9k63cV0pEyiuwUMSiudQ/4QCitmJOSbdbQUY0YlnrxcC4S3IRrmxLErjVNTCtHZBJmbL+//BFpVq7lx3HBqCQXebKaVA89ZM7JYaGggnG3Q2rZlstqaD3Ur63NrSDhipUDPyVaYs8J9ZEhMGWL39yBA+TnWApLU8oh5c/PDR75ER+rAdGpQwkMysyx9Q0k618rmPmLvamYN1q6MsJUER+ul2xia2LajrdMlcBW2ZDYL5HLGnYNfhkWxeeAXNCq9wejUOkEyJCHsQuQ0ufAia4GNfCI5cjyGCo6dhinUP0b6rpfv0/7pyKgrhcx2l2TF+15J9I/yLctL5rWPQaMuqMZXTJ6PgsBWx5ZTFdbz40xFq4AImK6bGmN7scV9MCvk9m7t3/DUsZe7+NqhJH2QNrlkCdEWSBkLM2HR8xo7nsgeKuBLIFkl9tA==
*/