/*!
@file
Defines `boost::hana::extract`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_EXTRACT_HPP
#define BOOST_HANA_EXTRACT_HPP

#include <boost/hana/fwd/extract.hpp>

#include <boost/hana/concept/comonad.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename W_>
    constexpr decltype(auto) extract_t::operator()(W_&& w) const {
        using W = typename hana::tag_of<W_>::type;
        using Extract = BOOST_HANA_DISPATCH_IF(extract_impl<W>,
            hana::Comonad<W>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Comonad<W>::value,
        "hana::extract(w) requires 'w' to be a Comonad");
    #endif

        return Extract::apply(static_cast<W_&&>(w));
    }
    //! @endcond

    template <typename W, bool condition>
    struct extract_impl<W, when<condition>> : default_ {
        template <typename ...Args>
        static constexpr auto apply(Args&& ...args) = delete;
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_EXTRACT_HPP

/* extract.hpp
+r1zv9Xpv2sPhl4G3JRMazyRONn1/dKjXw5+q0uG5EkuTr/x7W8wOOQGYE2QW0filZctYTsjJvS8f26n4++2G1VDRnHX7vqD1nf+4dEPPmqT/uXZ918asunufPK9u/napqBywh7kalxo2v5rvzcYfXdQhnG0AeZHBKN12nI03wAF3bwKDVjQa9E4aw/9l9+5sIDW4SQ8XklDbH3445HfPmsfl2Hw7B7vg6JcMcNZ4AO9aSCl6cIuBsMmg5QUN4hktM1ugw3aDt81jbbHML5yw2LbYxwhjI4GZwOoam8DwPbltog4zFeZRWVbnlKNP3xcHPrRYyAcERIlKPFyNnPAKIwBNxtXw7XUo4Z65NNokVXSXTY87/SHK2lPUNZNnoZSngDQNPPwH/9wzJwAcA6Ea//tb03/7FIAUU/ckJyM6IZUZkYFBGnqokoZiEVX1CxhgR3uHbzy2iQ2yCDx/cvda9D1WrzuhrTu9syFhyT8/qWDigDN4KDDg6Pv1rHyo8AgBaCBgX6zLeWDxnByG/oTUHkCwBLpNb4e6z4Q9Nm7tn82FARpohwS0lCjZ8I4gi7Xw8CvyjBwmCvxUAxfjYeEUYmHBaOMh4lDidaS1CtwMPtf377YP0xSu9UqTVI4ntz68JdTICDQduvsHf5V
*/