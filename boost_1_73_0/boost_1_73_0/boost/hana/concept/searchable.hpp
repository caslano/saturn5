/*!
@file
Defines `boost::hana::Searchable`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CONCEPT_SEARCHABLE_HPP
#define BOOST_HANA_CONCEPT_SEARCHABLE_HPP

#include <boost/hana/fwd/concept/searchable.hpp>

#include <boost/hana/any_of.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/default.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/detail/integral_constant.hpp>
#include <boost/hana/find_if.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    template <typename S>
    struct Searchable
        : hana::integral_constant<bool,
            !is_default<any_of_impl<typename tag_of<S>::type>>::value &&
            !is_default<find_if_impl<typename tag_of<S>::type>>::value
        >
    { };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CONCEPT_SEARCHABLE_HPP

/* searchable.hpp
hUqaancrNCUK2Zvqt0aHRZjS3ufAghadYlQfFTZAUkBBA9p7ewODlp1u4XkOvQNy7ZTOmW1SRTO3Ou+Oj5r9DkDy3z2lMdTZly+527S++Vra6XQ3bIe3lDQELbx59+MPTiLnAmQbtJQzJvaKPediRPWW8poCkeS5MGZbx40Wm3odWtjfSYihPzhnt27EXBbdBzGI4fwgCDajKz948+77iN0dH7lLn62XaDiRms3zvQOhJUWepwz0YTQN9gIv3l/yw/RoH6SGm7t9EH8+wtPjF8c/H6L9I4/yAJgcIoKF7gza/ctmC+TBd3bGni5kb6qJW9fRCzv75u8KKv5s3xDFu/yKaN/JqwjvcivmVcphD8KSlCP15PeEL49f/JBbEd7lV3yeIyWId/aK7daZncfji7wqV3//LacOvMntZ9jM62jYzAeOSwC5ICYCgtxThcB/UGiemPjLW1hCJWYJLt+LsppasAPNruLWGm0+4i1u1mgxA62iFa7hixCvBQBCNoe3nWn0+w/P/zyB1T+Cih5Joj88Z3M/ihOfiashu/XcKTRMy/Tu1p97NdUr8pYD9uQ0AYTzG9X5L9BiXWrrZKiAV1xBicO5aqjBDuD/QjME5eoJlKoLNZFXsChKqktVzayFA5SAPHuGegb84mXp
*/