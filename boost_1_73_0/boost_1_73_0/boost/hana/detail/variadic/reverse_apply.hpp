/*!
@file
Defines `boost::hana::detail::variadic::reverse_apply`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_VARIADIC_REVERSE_APPLY_HPP
#define BOOST_HANA_DETAIL_VARIADIC_REVERSE_APPLY_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/detail/variadic/reverse_apply/unrolled.hpp>


BOOST_HANA_NAMESPACE_BEGIN namespace detail { namespace variadic {
    BOOST_HANA_CONSTEXPR_LAMBDA auto reverse_apply =
        [](auto&& f, auto&& ...x) -> decltype(auto) {
            return detail::variadic::reverse_apply_unrolled(
                static_cast<decltype(f)>(f),
                static_cast<decltype(x)>(x)...
            );
        };
}} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_VARIADIC_REVERSE_APPLY_HPP

/* reverse_apply.hpp
L6vEGZMQeQ7z3mFpM2SZEQXOqfpViatPkT9zNlFo7WUPYSTRLVLa5V1TPGefTTo58uKeg1DXqX8+uvh4Drhlobb0I6Rd6vwxybdd6vrRyWM8xIPK/8xk4ss7kGwvoncRrA6txqusBJ5DwUN4r8ri249HYfrC2QShPT5A0f610xGPuggGizzeBJ3HQSEegXfwx2Y3w/8rls0zVUG8YlVhE3/BUwRcWkaHZsIy1I5NKdm9dgTUrTfiEVbTeimebr0x1Q9FWXGKiAhR/XmVQyKSGz0TD2MoK6HDxkI14KeGZIC0Q8/mUdx59aor2JOCxu/xUcztolLTwV71HIn3XjYrXS7rzztU/Huo3VUcT8q48N/VyksSPC4S+xwX4C5CI14ch9Er8VQCe83AEMzo9BBKJV6Mh6HXK1jPq6VOkWIXzg6l+DAJN1/uQZhG2AiuzCBKvNlJdBKl/vxOB8Lj1Uu9i92pN18FsmdfxF80Z2Cbs4jFX+AToN1qoPhJh8fXNbaAqQt1Ryeno5OLfWNFPd7U+IQzpQ7kV119F/lzCbN286rQ6vD05OR8NB7lWi5CHVyCLtII5ODd4OikHNzPaC94GwD55KDpNK/0a6hGynRNyyCRuasgtbXqy1VSWl3OofaYH9GkypnS14NcVLJg
*/