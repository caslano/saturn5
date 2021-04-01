/*!
@file
Defines `boost::hana::Foldable`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CONCEPT_FOLDABLE_HPP
#define BOOST_HANA_CONCEPT_FOLDABLE_HPP

#include <boost/hana/fwd/concept/foldable.hpp>

#include <boost/hana/config.hpp>
#include <boost/hana/core/default.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/detail/integral_constant.hpp>
#include <boost/hana/fold_left.hpp>
#include <boost/hana/unpack.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    template <typename T>
    struct Foldable
        : hana::integral_constant<bool,
            !is_default<fold_left_impl<typename tag_of<T>::type>>::value ||
            !is_default<unpack_impl<typename tag_of<T>::type>>::value
        >
    { };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CONCEPT_FOLDABLE_HPP

/* foldable.hpp
qP7TNKOhAXfJF+qoKUunISjmSZ/T8R2jwMcNNlC8eZ+zIkE4Y5QDWj15FlX304wPLnCK++hxAnoxy1AkonroYD8FzRu0crLvUQYRozqYq2V22j2VeC6oMp+L9zF84wZ6oIo9EURF7VTh3nHiniXCy7ov18ObphM+Hqy5+M4U9VlFXBjA6K+zDYxV6Z7yXF3OPIkRchfmdEM12oO5QCylZNtrdf/+dNa6cCF9g8p3d6pT/HImxe2bxHJokfIWD9xilu+f/jY3Vengoqdw7o0mD/6pqSxKwjjLRXwsBHEYA3tedEFB/u20Ii8mdgyZi7bDgZihsws1uHBebalMb71daRN4DwrtL94MLOOqE9wtCNrjNSG8IDEjDt7ZtXOk3YQycQZk+MFM28YLOMQ1LTo76kgnt+xcXPo6kLWkn6XW36MqTNc+4inv3AvcAFKeiV5CfwCujyR8b+I80FOXU/AbaHm130Lg1fxQuWpmRdTL6w7JxBpm8QcGxAUY+W1hc+gBL30ZYoiUcbVxUw5c6arBDQB7uSUsvgTFfmmtWWpdrsjkhYmgc2Ev1AleGA==
*/