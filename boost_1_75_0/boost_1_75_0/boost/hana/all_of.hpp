/*!
@file
Defines `boost::hana::all_of`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_ALL_OF_HPP
#define BOOST_HANA_ALL_OF_HPP

#include <boost/hana/fwd/all_of.hpp>

#include <boost/hana/any_of.hpp>
#include <boost/hana/concept/searchable.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/functional/compose.hpp>
#include <boost/hana/not.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename Pred>
    constexpr auto all_of_t::operator()(Xs&& xs, Pred&& pred) const {
        using S = typename hana::tag_of<Xs>::type;
        using AllOf = BOOST_HANA_DISPATCH_IF(all_of_impl<S>,
            hana::Searchable<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Searchable<S>::value,
        "hana::all_of(xs, pred) requires 'xs' to be a Searchable");
    #endif

        return AllOf::apply(static_cast<Xs&&>(xs), static_cast<Pred&&>(pred));
    }
    //! @endcond

    template <typename S, bool condition>
    struct all_of_impl<S, when<condition>> : default_ {
        template <typename Xs, typename Pred>
        static constexpr auto apply(Xs&& xs, Pred&& pred) {
            return hana::not_(hana::any_of(static_cast<Xs&&>(xs),
                    hana::compose(hana::not_, static_cast<Pred&&>(pred))));
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_ALL_OF_HPP

/* all_of.hpp
qIDhy4G1h7qU+iCZCBCWY+podTmNt+lzFPorTyKMvEbP8/WLw2/W4aks4NkBvaduFTUelbK0iXeAEoaLo2kYrTIf6W4W0C5fd24YRbyCWF3pE+mf79iKj0XpmEpkzXZTJilLGroWjhycmhzuWpoprG8czlbbFy6O7M/d24Wqzg/u71OiJ7PWqdnz/6gqui1m/Vz8o2OhlpREPUjvPCMl5SCFj31ykv3d8Z9C+iNx96PRhiYtP1g6SjuzNZTj8nh916Pz484/3JThy6AvI/PD9nLTn2ugu0dXw5ZMg5yxlfnJvrnPyLhM1xs7jS4FKmiCew/RxX3ma03yQkWynt32S8sHaZwr74dpCrjp7OR+OPBzQg2gq/ZHqkacxg7L85r5Xm06lgrVLiLZzy1qwY6+z01L1Ybtr+IX+6nXmW4qlAITmU0e7vfP/qmEWTtePn3vo+RKIWsdDr0dBdXVILXMuPgzwMmxr823OueDY3QHFYmuDi6Jq7Y/aSuIuKSFzXqLPL8ImrsHtdw2Pr/guxAZdBGLeHA5v4INX6QrlrM4/c9nlRQ7XO7uHRi7/e5OYw/80zQEa3aaPBDVa8c6YO5iCvVrW1ZDdMKNRd/btEFx4A/liRLztoyrjQqHbny8Gze4rsgEef6cfdu3P3zGLA5mN5+GUfGNrYF+Y56iC4Nrli3Vg/XVOP6PyrUFihbVJ6sNlrWQtYYWBJJ42NNH
*/