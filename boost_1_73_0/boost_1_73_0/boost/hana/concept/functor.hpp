/*!
@file
Defines `boost::hana::Functor`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CONCEPT_FUNCTOR_HPP
#define BOOST_HANA_CONCEPT_FUNCTOR_HPP

#include <boost/hana/fwd/concept/functor.hpp>

#include <boost/hana/adjust_if.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/default.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/detail/integral_constant.hpp>
#include <boost/hana/transform.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    template <typename F>
    struct Functor
        : hana::integral_constant<bool,
            !is_default<transform_impl<typename tag_of<F>::type>>::value ||
            !is_default<adjust_if_impl<typename tag_of<F>::type>>::value
        >
    { };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CONCEPT_FUNCTOR_HPP

/* functor.hpp
lDAOB6K3VVh4cJDzv7mb4T4BEHbVskkq3sa2dX/ppWxTy8hhcsRCPk4ZJTZBc5anqm+pfYpdWwf4UPE0NS8lMvYlvkqOcLvHuj3sKkeqHvdLt2TEY4llSN+uFGGwKDwyPlbYhUB9BohL49jr6+v+nHspMNZP0suBtw6fE4oFdOp9IKMBvSXpgsQOQs9xh32QCgLIuaVakyueLmEXUvRmLAd9/gT8wKpAZ78+//H7n/7CvmPfv/hBykyqENe0Tc/qBQqBbA2MxVsUrdVGZbG82oNMQvUhxFx0qKAG9akaycBo0yOvL35AHuF1jRmBn10pYkctTZoj+Fj52CMfGtKjRQxTaRgRQDpR+GRwMpjL0NDSATMyY5iuKaoX/nnruUYpPAKMUZ9xr5wQGmfgtWCQySlyIh0a+/iR2a9LB6cpKwGEuNzR9OgaSxIdP2oLoM66xeJe8l8RCE6BoZqcjbTrHfZEQNSGvSLhXMF17zMERlsA/tlkkwTiSE4eORG86kKlL5Mu9JD25Uxuuj4So40fjV5evBrOZqPpeVX4ByB8nA4S0oh3mwx3j3Wl0fZs0gKoFiba6Buorwvvu+qFdpldvfM2e9IiYdc1zK+7V/jeuq3v01iJG9G2Yu+b/RogLm3H0qvMAcL4jvW0GFFV
*/