/*!
@file
Defines `boost::hana::Struct`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CONCEPT_STRUCT_HPP
#define BOOST_HANA_CONCEPT_STRUCT_HPP

#include <boost/hana/fwd/concept/struct.hpp>

#include <boost/hana/accessors.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/default.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/detail/integral_constant.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    template <typename S>
    struct Struct
        : hana::integral_constant<bool,
            !is_default<accessors_impl<typename tag_of<S>::type>>::value
        >
    { };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CONCEPT_STRUCT_HPP

/* struct.hpp
5Rgwckel3vzZiyREKEQic/oYcuPLrg2HxTrdN34FMpGIvqkSfhDEOZRZxENpCyo+tjmaDfyRUUu6zuZM6+4v9qgTXHsG1kBo7ZeHpc+i22VHHd+gECdxIVi2WJliz/RUi02OAnM5XJ7Wqz7X0Xb1Wj0z9C+JJUA0pXG8LShM2nUA122ayf1wGL84vxOWkkr2/VwK+CWd8Mu75Y45t07TjYKg5dcEivVw2nOOg9Jt70AZ+ql65Cpmk9UjvvBFs0oxjN+Tre3kgtYPppo0gxSVA42MZ9pnYA6YRD3VopPyejnfdVWzwFba4m7N9B5c4lSsUPbbo/HTUkiESoWzgiRpE+YqrDAepH3RISdq8WIMWS6qhBgV5hLSxPuQasGDT59B/BYZ8zyOy16pMHXQ/BhqueHnlEC8i9x9UvWtdMt980sZ/EI5ci27XbWbZhv4lXdQ2ubxJkb4qMt4vK0Ti2jrycqifqO5HEpkcBqT+Dgff7L5MfHFif3EoVchOXaBTIcKyeKs2gCpaPHKuk8qtJELZMn+L6/M/DlK4j0CtlmBq7h1vK359icxb9FQoA==
*/