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
2TF/Fy6fevIp+wWDhFMcSaEaskPFO7u+wO/YLHx9g0ympi5obGk9iMQbitcGrPChMFbadunCNtkmJpvInKo4dtPpLDP6kYh36+dffCvwAJm72cHfU2vqc0CADz5H05CbVVNoT4bzUKdqgVbka/5q/+oTIgrYVRyImz30e6KFzqDdM4OyT/xWa1A7m1bDN0lNB56sNaedqQ/wl2PxpWEBb+NG7aWA3BtoyrGvq+FbYuToPsR+X033lJxdq6XFIN36aUl1kIDMLOjxFRgQYg0tEbubihMX2txQJTminsJI8zx+7D529A/nG6+nH6ZI8/vsRzHstFqBh6P4JmhTdtHAd+JKdGuM2DZAaOKiPiNTTqlmyoHR/Mr4iEHvLVmPO5seG8QBhR+1IhWl+h9+TQ4+wMUK2tWCRJif1YJkpQAmvRSloFPuEngwDbjxXSZ3mXxT96Ai79aE1x/j5FQwQE7w9ndXl61i4WQUIDzPZOJnP0brLPHspqmLnakEZCSAdF4IHQaahBrPzerNDkY758POdLWnehBdjKTs8FWaEOcI2fsOsXzlKqd2FL1aEEIZCsQPfxFUuXcFeuspCQgQMZCOqBJrb4AuD97iuYnqEXcGhbxemC57gUcUhHjhUAsoGndq83q4I5knhlEp9U72ZCxFT7Felm6kDS/qQRR0+tum4nsnuwwaFL7K00NlbAPu30Vh57VdtgsAE8zSiyX3
*/