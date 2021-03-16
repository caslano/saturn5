/*!
@file
Defines `boost::hana::Comonad`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CONCEPT_COMONAD_HPP
#define BOOST_HANA_CONCEPT_COMONAD_HPP

#include <boost/hana/fwd/concept/comonad.hpp>

#include <boost/hana/config.hpp>
#include <boost/hana/core/default.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/detail/integral_constant.hpp>
#include <boost/hana/duplicate.hpp>
#include <boost/hana/extend.hpp>
#include <boost/hana/extract.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    template <typename W>
    struct Comonad
        : hana::integral_constant<bool,
            !is_default<extract_impl<typename tag_of<W>::type>>::value &&
                (!is_default<duplicate_impl<typename tag_of<W>::type>>::value ||
                 !is_default<extend_impl<typename tag_of<W>::type>>::value)
        >
    { };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CONCEPT_COMONAD_HPP

/* comonad.hpp
tZJ+skNJP7ncNMUM1xQzdLU/5GjrHa2/OdC0bhrqY6uG6d9ol5iz0ugfm5V1Vzu3mzV16unPUsyF2rJ1Q/XGpj3BJe6qVZkSlJrVZ/rBx7FYZ0giby9XutGHSPzwK4b2tE3unVWNhqs1ky6KzD9DdFF9yPC/zfl+XWl14WGIe/FvfIAhnlDCEBvw74OUOdeChgWz25p3e9I12Ey6/jjYpxOrQRqVZdnAalPHGNSmTk4TnkSYRzIH5/ZxQ2szgyg=
*/