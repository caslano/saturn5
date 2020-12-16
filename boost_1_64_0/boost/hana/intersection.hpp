/*!
@file
Defines `boost::hana::intersection`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_INTERSECTION_HPP
#define BOOST_HANA_INTERSECTION_HPP

#include <boost/hana/fwd/intersection.hpp>

#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename Ys>
    constexpr auto intersection_t::operator()(Xs&& xs, Ys&& ys) const {
        using S = typename hana::tag_of<Xs>::type;
        using Intersection = BOOST_HANA_DISPATCH_IF(intersection_impl<S>,
            true
        );

        return Intersection::apply(static_cast<Xs&&>(xs), static_cast<Ys&&>(ys));
    }
    //! @endcond

    template <typename S, bool condition>
    struct intersection_impl<S, when<condition>> : default_ {
        template <typename ...Args>
        static constexpr auto apply(Args&& ...) = delete;
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_INTERSECTION_HPP

/* intersection.hpp
a15b084oS4R/oRzmSf+ldPqYIPQrddPFKOtkrvu+CdOs/dpz7x/XMfNbx/6Guplni+zfSaObMRYJ/d7rGk7RzzTrZP7B92HoZpxlUje1h1aGmWeb3D/an36mWSfzT/anm3GWSf2z/WlmiDm2yNkyLmyHzfchc8UsoVta9/QwQ+hW0hlhnfwUxwcLVN3a2mGUBbYpv431wTzpt/WcHqYIpXrOEPOkX+R4Y4Jtcm7nvMYsabe3huhlibo0+7HBkYttZ5mMO1jvjBO6ozYxyBpZ6e6fmCJ0iXMEc13mVpxilbw7ycMQ84TvrI80M8Qm0Qx9Yo38uziPsEzOXbWDOdLvZiyYJSXTemeM8N21lx7mSLmHMWCYeTbJvKc66Cb2HeuIDU5813on9XvmlS5Sf2DeGWSNnB86Lpibke7as07+p+VhlAUyP+M4Y4ZNMmetB4ZY/5wyPu94YIRFUuakceQL6mGO9C8qk1lSvyQ/M6TMaycj5H1ZGwh/RXsZZJG0rzommWCTIwvyMU/G17SfSVL83tBJxgl9Q5sZZo3cRY9J/abt9FHwOscbI6yR7nVlD5OsMDbs+Cb6BtvIe6O6WCLlTY5LBpkhNCKddeK/uxh5i7KYZbFb/rfqE0MskD0qnRVS36Zcpkl/u7Fljpx3aB8L5IzZ94OOSfI+pA8fduwyQ9qUNjLOFpGP6B91H9VnQh/Tfyaert5nKIfwM7WHLkaJ/zZwK8Msvcy4DpgXhpgn9eXqpJu8V2g7C4Rfab3Qyhhb5A9qZ6e+xMwVw6SeUx8xplih7np9JtQljUH85rXfXfD4lub6VsYiRb9YIfvW5pc5Cm6jnYRvq02sUpVqP2YYvUgfbmdc6Web1tsriyWy0/SPERbIuFj/6GeK0B30ky7G2CDrjtJZIiVd+5khfIk+M0rGnaxVBlgh/c7awACnM9RF5C7qoOuu9mGdzLvZj0FWSM3UPnqYZZPJu1un5N/DuDDBCifuqQ1Zxpp+Zsk+bKyZoc73snuJPlzbCV8hL92Mk/oI7WObvCO2M0f4UfLRzhipR7WHWbaJRuzHLGmF2sEquUXmiQHmGSs2fhyJajfDzLFJxml//3fc3wGxTbp/86h1yPcFJ3132N+thf17PX1sdR/yHv0h7xEc8r3PQ34D2t8Q2jbh8bTHjc9QBoP+7Z1U+4Yv8lkeEU7TzRBTLLJJ2u18jkcVrfQxxirh29ufboaIcpp5n9tN+CxsxudEGz7DWYh/DjPt9aTPQbp8NhH2OcZmn9eRvisWa/c+2ZZ7v27nbPdS/e6FGq9wzt8yZt8z9jPG5bXm8bx5d7wsha2Pk/F/D8RcO5efiv+7S3X6zRqb/m2o0TOea9/ypGPM5+T571ZPvuPGZxxLJ+zjnn/c31Dl2Tfs36OausGYXGsf/wadr1R4P87fVilnqd7fv7LNm71X4goXarJe4/Fta6J4yPcf4/H8Pz0XS/4ZFsU/yi/+esR28ac+n43Hi34pXfxINP5c2gjiZ/U5Ht+ZIopvfokovu9j0sXCD3guvupu8fpseyjxesK2ix+/1HPxinbPxU+tqEc89zhRfMDHxXg94UOicv/sufidBu0Q31CiXLFl3v7i31tE8S+/lU98SYfn4l3+IMb3+6D88fobD4nGYdN28YM/urlo/3rPxUtf6Ll4r6Adr/2DKD6+x3bx3ANCovxXex6vLzMsGq8Oz8WPfNVz8bLbqke86V5hUfut6Xi8eCEYj0cH410tin88IYq/+4408e7ft5/4tLKg/2+QLn7hykOifl0cEm0P5vO+FwX9e+AhUfvvF8z3S7VLvPUngn69WBR/9Nmgnh94Lj7mR+oTX3hMFJ/0PVH8e1k=
*/