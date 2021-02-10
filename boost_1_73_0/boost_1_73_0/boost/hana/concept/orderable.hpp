/*!
@file
Defines `boost::hana::Orderable`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CONCEPT_ORDERABLE_HPP
#define BOOST_HANA_CONCEPT_ORDERABLE_HPP

#include <boost/hana/fwd/concept/orderable.hpp>

#include <boost/hana/config.hpp>
#include <boost/hana/core/default.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/detail/integral_constant.hpp>
#include <boost/hana/less.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    template <typename Ord>
    struct Orderable
        : hana::integral_constant<bool,
            !is_default<less_impl<typename tag_of<Ord>::type,
                                  typename tag_of<Ord>::type>>::value
        >
    { };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CONCEPT_ORDERABLE_HPP

/* orderable.hpp
45dPPvDi7aIO3tk6eMcuv1kPiv90O63eWdvSHUvB480jr6xYU/aodawmqbW6X8ZD2EiCm1H42g9gimlm1PvBh/4IORxOz0X7fV31hpPSuuy0uyOn1R6MnH5zdKF3gQOxl7EPsnU9uOSlhqPeoO30B73fnOGH4ah9xeyPMwh4QBM25NCsAPagHFQZXh6JMah+LO8MmfHg8wH/vChq9rig2eMHNgub5WFes9o7a7MvDoqbPShs+CDbtBWooh6KQbcAL0A/OigBPXcGjbfZhl/YGm63Xl+fn7cHwJKAppImzecZReLwJ9UUcPnXIbBouZmDJDObgeQS+f8Alr9Yw6Yy9tgrdkBbiE7cSvgQXXW6HaCXzv+BFc9+OPj5x+LS54N2W5Y+PDj6IZFtaHWMLq6vXvdhpdOCdy7bXWgzt8hZc9SkMkcHNKLrADaLhReQvA1bOYh5sHmNQ5C/QIRYrmMU2WRjqMTMap8bDATxvb29OuN7cQ1+Os5vTac5eDN0YA/QqsxAEahWZT+ZrFbz8o0zvGg6R89/1DYU/bGYa5jqSTLXotzrZuttu3tG8lAUzXdfjV0QaILp1lYUuzFIqi3c1UHB+aTmkn6dGO9R7Ere46+TpAGYJxJ3lx+XztIPnKXnrRxQSj569zWQtNYg
*/