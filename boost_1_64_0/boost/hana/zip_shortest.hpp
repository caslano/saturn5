/*!
@file
Defines `boost::hana::zip_shortest`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_ZIP_SHORTEST_HPP
#define BOOST_HANA_ZIP_SHORTEST_HPP

#include <boost/hana/fwd/zip_shortest.hpp>

#include <boost/hana/concept/sequence.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/detail/fast_and.hpp>
#include <boost/hana/tuple.hpp>
#include <boost/hana/zip_shortest_with.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename ...Ys>
    constexpr auto zip_shortest_t::operator()(Xs&& xs, Ys&& ...ys) const {
    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(detail::fast_and<
            hana::Sequence<Xs>::value, hana::Sequence<Ys>::value...
        >::value,
        "hana::zip_shortest(xs, ys...) requires 'xs' and 'ys...' to be Sequences");
    #endif

        return zip_shortest_impl<typename hana::tag_of<Xs>::type>::apply(
            static_cast<Xs&&>(xs),
            static_cast<Ys&&>(ys)...
        );
    }
    //! @endcond

    template <typename S, bool condition>
    struct zip_shortest_impl<S, when<condition>> : default_ {
        template <typename ...Xs>
        static constexpr decltype(auto) apply(Xs&& ...xs) {
            return hana::zip_shortest_with(hana::make_tuple,
                                           static_cast<Xs&&>(xs)...);
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_ZIP_SHORTEST_HPP

/* zip_shortest.hpp
/UHmSjwHngJXYVyBrjoIK94xtHnqTBCpdfgi2XQvf801m64P/9jcDLBvD+L82P0/2Dhz9acf1ooUGfzsxmLrg8E7aEMrcqvdH4cn1tb7x2FsCjYzm85XQqY18NcMYKQunHbGCVIr7Xc2hq/kTPYR6N8QRmUx67Xx1hLWOB/ryRviLnzstOCLHobP3Vg89/A7jA2sZGOFeOr9AaF1On+MX8r5pmxY82dsEbhk+F8ei71Q77e5HC4C7wiP/cauFvzm7W+crhRecANxdnz8uG/svAcbY/hj/kzHvqo3bd7m7qnVzCoBxQIP/I2x+GbLxc85eKX5TA8ho43QRdPJePiNw/4n18N0pSr2LjXY7x1M4l5J+LXPryyQGKqzcDw35/bb9KXcknVuKPl0ZdOwfCzzPgZtgv1sr8AUKYDEfs0d9Z08LHHccp5bWJOPWvQ+ByySlyJi0+xyeoPWiO5W+nW6wT0NXX5IYvQJQL7PfUzSsaUFffaJkq6cdaP9M84Jdh3YpoSzrV1/2nmod+rEHZf9bXtQe2er3xUx80dcOlV/q0VM4vZ96KiL6TabJDvQ6fslXYUmss2xBlutXQbOIShJ+M7OWvW1zyDXbT40iaJyzLfXrHpy7NQqxsiu42pnhqop2jB12KUTe0Gf3uvSV9sdQZ84ZtPbBJD0O3b5pMIjOcS+25ah07liZl5Jq4zJfjDhY1gaCAMbV4gP+1f01XkBvs6pAE5PsnWss1Z/4s6vhTO2R7fH6/YeQS8sI8E6ziyHbTrd8Jnc+Mg9tnHUxgy6dGAcRhGY2Fs+PYSJ94L3fR4qMrk72mxyMOoloXu2A7y0L1UNMWIBftrZBZgHTtsHHVYLa9J36oqNkQ99Yu5sTPiYBh22VilFlR7TIc5HY7ApMa55t/5RKPQm7FNuvdQRMBXTe245UV68Tezh3D5UJtMOv210AW0/7GIoi2uL1hrC4J7Irgf7fksbzx2HTja7gaTP7nfpgw1Jf/Bom65HCLrosl1HFYAe2yHsPtThn+rJZApIvhj7Et5+koXTkRg8FWi9juX8VhBnvzdw2S5TTUYt68JudNjD8AFeBZTjrmuPj6Er8BrGz6fzCFt+1IG6NNejRLSwU/p8IAmmj6/7GNSzZ8uReVy3g3XJpbcHqk878FFy6kija97tin1w7fKVqrTeI/4DeIAe6QztbSDtP/cecrH+XEXd7HJZcdYIK+X/RgCj6oa91FGHzmqR1WgKPCZczJblDzb5ZIeur48VDfJw2MWQNK05mP0ehow3L3uJxFw/aGOaI/qHer5C5DCYPeJjZGzZtt2eyBCGXhbna7vvzLjXMfftvoNcYh2w6dErMHqyQYfZ8qc1GG1o5JtqDp90Nlum7eM7et0onx3iXB4K42ijwEdX5IcM4EysM+ZdAKOFB3GKpaf7mEJxIVrMokvgIeweSVh672XYbXSlj9xcApY9KoRv50YYZ4QcuHwirr7V3rwU5z1IwpkOlOvClMAu4DS0bOh5i479+jLsTzZdnpRgRy0JW3C68sZiRkWGU2T627qrkI28h2kPSJR79VXWtQPEY7m4KJvIcCNaEAfIz+Diouweo56BinGa9rBvSBeq2OMhJnIujIPXLrkLrTUHcW7L2SDef9v5stAXfHIb1tdnItecNcxBB6MXWVYJiGmbdDC0xdzSKTyl7pk65OJmTD6jC7BlOuXhpKKf+oLOdHnR+3yaVwM2m8c5mJVqplpYYo8szzctAevmMJhNwJm5DRuNhysW6OmNSnqxUqVJcZpOy7oK4s2QKeeb6htLugJV7Hv3hzAkBgJzLoDRFaxiru51MXbHyD3y9uNCWPvOteRiROehXi5GdBzs3SE=
*/