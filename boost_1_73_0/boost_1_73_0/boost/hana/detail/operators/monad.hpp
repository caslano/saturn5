/*!
@file
Defines operators for Monads.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_OPERATORS_MONAD_HPP
#define BOOST_HANA_DETAIL_OPERATORS_MONAD_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/fwd/chain.hpp>

#include <type_traits>


BOOST_HANA_NAMESPACE_BEGIN namespace detail {
    template <typename Tag>
    struct monad_operators {
        static constexpr bool value = false;
    };

    namespace operators {
        template <typename Xs, typename F, typename = typename std::enable_if<
            detail::monad_operators<typename hana::tag_of<Xs>::type>::value
        >::type>
        constexpr auto operator|(Xs&& xs, F&& f)
        { return hana::chain(static_cast<Xs&&>(xs), static_cast<F&&>(f)); }
    } // end namespace operators
} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_OPERATORS_MONAD_HPP

/* monad.hpp
iNYkZ+H1VGxH5JhyUEoXCU1bO9pwVgElyK09KIiuNVfOsPVB9WP093ngnbyC0jl6InfKta9atIxkMLkS5skpUZ6PV3aVNJpIDcn92VU9Lu5Gia0URMYbhpgVQX6GbeEJb/7eIgGxAIXHOUpkWJm7Sz7OmSJCte6CqgYb6KdgGDxhItB6KJgZrL5M1DpqJgBB1+nfEG1PNweRX3es2XAlelxH0JbCza1Geu22yzyzU2FQTefUYfX9yqc5kF+pilTr/f9II21WNa3sBStcZHt24cSOEBcpy3m7Ksd5o0Qzb6hWoORdlavSIiQus0yrsunrleFDT9fws5mhrEKGmAHbrM3ucCikW9uX8SHEiDTtQpzYDfHeN76hjPydHIqAZ+VH2c2x+WHE3VtoMHvvefMGZmUzquxoIeV3XkOvSY+UeUGIXo1cPYpUNQXG+HlQqmkzq8tdrv75BbSz/YDQ3MK354nFvtERwoIU3vD5MKeffD8WeykVW+i5k3yBof8j32TAZpmML60JBtTDEfzon6N3Z03Mk3zpFQg7MLuCzP4xe26xSKvr3bKOlsh4FDpY51jOrvaUgtWlsxlYG1Ud47HRdYjuMduthN8bi9FUa3EO5vsXfpLI0wWEyj38ggN2eekFkLiDryC8nQv/nLW6
*/