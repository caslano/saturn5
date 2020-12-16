/*!
@file
Forward declares `boost::hana::none_of`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_NONE_OF_HPP
#define BOOST_HANA_FWD_NONE_OF_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Returns whether none of the keys of the structure satisfy the
    //! `predicate`.
    //! @ingroup group-Searchable
    //!
    //! If the structure is not finite, `predicate` has to return a true-
    //! valued `Logical` after looking at a finite number of keys for this
    //! method to finish.
    //!
    //!
    //! @param xs
    //! The structure to search.
    //!
    //! @param predicate
    //! A function called as `predicate(k)`, where `k` is a key of the
    //! structure, and returning a `Logical`.
    //!
    //!
    //! Example
    //! -------
    //! @include example/none_of.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto none_of = [](auto&& xs, auto&& predicate) {
        return tag-dispatched;
    };
#else
    template <typename S, typename = void>
    struct none_of_impl : none_of_impl<S, when<true>> { };

    struct none_of_t {
        template <typename Xs, typename Pred>
        constexpr auto operator()(Xs&& xs, Pred&& pred) const;
    };

    constexpr none_of_t none_of{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_NONE_OF_HPP

/* none_of.hpp
GTsuzBaAFbgATl3PrPuaTONSpCSB9b7nA+AXUhDf9aoXK8ptk1I+z2BXIgAIUUBViZGL6Uh15C7mRahBVqfnTX09SQMG+wFhGySQ21/kE4n0QYCmwACoqj/LekYJ5Az1vbc874UJDetJRrQYlvALYqIhzKolugtYYVTJWhMophsYZzxRGgB5QGJEyvKwGY5wQQPTNwxd8LDEh8Iwlw0ilxv2wwdLGrWs/8wdG0nyYkOI03jkXvymxHqOMXQRAUh6KY5dz5KlQO7kYSHBOzwadRQXE0pZLTnz6XgGX69DiEq+3BqTGarbj411iAJDsnwo5UMLJpedZCjt/mTBINmiBa4hQMAV1NfDJAEl+gzJYY71qw0ZUWIM+4TWZgmI0Wp06f7EE2R8Gi+HiBLep5jOFUJOA0h6DCxXmIsESBp+EnQIQMyDXkGqRFCevENaIgkwaA+GOgFuSxzHRnqIBw2p9o7nPWzVCrN+LgcKbndMcQgv4EUvVnKAhhj1XTHquxMUCCbpDkmV8YkKxKBWCkRJTIH4o9FZ21MgcmJaQ0bscQALGZGgQGS1UiD6t1IgdqqByVQg8tpTIDJbKxBhhFIviSkQ1Mkg1ag3htHu9pSIoZ4321QghsYrEMSCMZUE41x7CkQBKxDuzigQWWEkb6VAZLACwZyd10qB8JLUiFcgnKYCwdYqjFax/prenhIxnjprxMD6bon1ks4pEC7k+FrmSI8pEDISrS5gBcAUO/s4JS/P9m+lQLhjGfNij1kxBeLb9hUIMEC9oUIoBcJNo2mbCgQRn5AaUyDIEyWmRBSYSgTN4eMkhOSYmAJRkKBA5IBCJTEFwtlSgSDFFcBIQxBKxSWeJsEL5SKmMEBQjDq40sBGDJdUGgzv2AE0xnMjw0CuqUCMOiQFIsnSvgKRrkMmxV7HxysQNkubCkRJTIHoT32+lQKRwwoEF223SNYwtIeDqQwOSioxEpN16fwoeYHSAblkF0EhI83+Bprzq5M6LRfEHVZO3lB32d+AOJCKIxCimJqmRJt4Jmd24a0mQ0nJUkK4NtgBypbSiswxo0A3+i1qhn7xgedjNeWMn3CS5B+KqpnDgjlGs8LKwkQKxBivuaCJbImJrN1KZI2X+k0JsR7Zg3ToGgZmMfqAHAahJFPwI4dyf2UTDJs6zN5dZDIEC+xG7t8kBOVV3Woiy81kBb5CcQBvaOCXePoXqIzmmGPm52RqmuR5WUdjysuM6kzQq5fz5lXbK3giXSYknKEdfcMFr9jyQ/udC7bryzkhbEc/+eYA7nhy/bterv3/z/8////8V39qf8n3n311IGY/ZjOsvty4/u95tuVBi7fpFowMGq40xc8Ver4dPzPoClSYd/V80jHm6fku/CzQ892Awhbg/HQAepwASENoI7Sby+bN+Cl+J06bnOHRLYhYxiltxk2EBFlaoAFc1QYmPpl70sAfX3IVficHL8u4XB4Mz5cXcnypb8W6PPzmbkwbtjuCRF78yZJOa0/Js3Q9dXTz4Ntst85IW3IXHiL+aGRUzknW93L3z3VEaMfKW2mhZRRxQdS6GYG23Hdmz9c/i/idkSBt4sveHPrTDt7z80b2Zp6A8c6Z7Df0IJ73k76Gy3fQXHzSnAW2zIjDmuYc5cBvSuTCjClpn2+i4JxQXUZaDwQj7pgdHNrj/B25G2a9ShtiaM6EZj3OzZmdSfXSP89+P7spApXK+mZejePogV2XOfrlbpy1y0inS3OZ9fuoxFr2RuvHYZp6yeiwjKaLid6DLztWLwxrfQVGooe+ppHol//i2wbb4E9iI/HGbpM/icH4+oPnue5o+irJnyNJ501zpoI58rryOgZ0kjRnkZMeJuI=
*/