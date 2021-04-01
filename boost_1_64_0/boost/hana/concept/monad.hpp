/*!
@file
Defines `boost::hana::Monad`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CONCEPT_MONAD_HPP
#define BOOST_HANA_CONCEPT_MONAD_HPP

#include <boost/hana/fwd/concept/monad.hpp>

#include <boost/hana/chain.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/default.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/detail/integral_constant.hpp>
#include <boost/hana/flatten.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    template <typename M>
    struct Monad
        : hana::integral_constant<bool,
            !is_default<flatten_impl<typename tag_of<M>::type>>::value ||
            !is_default<chain_impl<typename tag_of<M>::type>>::value
        >
    { };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CONCEPT_MONAD_HPP

/* monad.hpp
xaha40wOlVxIynnTcGVkET0xbvtfrBp+v4qEV8JrO8dXhzzyCbM45m5YLxQGvNsX4Oivj7V1lYK93DZEQ1orqHxnzcrNPP2Qapo5lTSTocRud6r1fiXe+QAyEgrwJddkGTlBXps98mI3gRn1Cl729sPpxMvSMgrwdWKtibnq+mqYqpKGrvQR20O60ZNpZX21If62wJZUB5BWUErxBHFb+/zOPFswcZEIIjpPR2zDFqRvR6CX7GVObEBUx4cEeKe16MGABRiexYnIUE0Sa4QKrYsMa4hShgO47fsW6S/2+jafEzUN/lrcaMqWZ8RPnVTbCZezzAi/5/OvS8wWeMb/rFLzNClD5fbk9dT4CSoSVNEmWxEBp8GYeOkdyIKYMdEhoqjOeNRI5qiwBDxLKOtg3TJP3IOiah3nViWnmh4CuXYeAuZ4U2OK0PYBp//HWtdZQSIW49Y/uiDeOKgQbo0Fsh2YZqAsXK0y1jkNGsR05SOWXMr+d/VWP4F10n1sWDOUWDTNEFsVjO7Mxkvo6XpFCiu6RGLItS9h5eb9pODNGPB619GJlaFiW3XuQw==
*/