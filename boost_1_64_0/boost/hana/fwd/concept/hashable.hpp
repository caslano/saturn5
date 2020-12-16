/*!
@file
Forward declares `boost::hana::Hashable`.

@copyright Louis Dionne 2016
@copyright Jason Rice 2016
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_CONCEPT_HASHABLE_HPP
#define BOOST_HANA_FWD_CONCEPT_HASHABLE_HPP

#include <boost/hana/config.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @ingroup group-concepts
    //! @defgroup group-Hashable Hashable
    //! The `Hashable` concept represents objects that can be normalized to
    //! a type-level hash.
    //!
    //! In day to day programming, hashes are very important as a way to
    //! efficiently lookup objects in maps. While the implementation of
    //! maps is very different, the same idea of using hashes for efficient
    //! lookup applies in metaprogramming. The `Hashable` concept represents
    //! objects that can be summarized (possibly with loss of information) to
    //! a type, in a way suitable for use in hash-based data structures. Of
    //! course, in order for a hash to be well-behaved, it must obey some laws
    //! that are explained below.
    //!
    //!
    //! Minimal complete definition
    //! ---------------------------
    //! `hash`, satisfying the laws below
    //!
    //!
    //! Laws
    //! ----
    //! First, `hana::hash` must return a `hana::type`. Furthermore, for any
    //! two `Hashable` objects `x` and `y`, it must be the case that
    //! @code
    //!     x == y   implies   hash(x) == hash(y)
    //! @endcode
    //!
    //! where `==` denotes `hana::equal`. In other words, any two objects that
    //! compare equal (with `hana::equal`) must also have the same hash.
    //! However, the reverse is not true, and two different objects may have
    //! the same hash. This situation of two different objects having the same
    //! hash is called a _collision_.
    //!
    //!
    //! Concrete models
    //! ---------------
    //! `hana::integral_constant`, `hana::type`, `hana::string`
    //!
    //!
    //! Free model for `IntegralConstant`s
    //! ----------------------------------
    //! Any `IntegralConstant` is `Hashable`, by normalizing its value to a
    //! `hana::integral_constant`. The type of the value held in the normalized
    //! `integral_constant` is `unsigned long long` for unsigned integral
    //! types, and `signed long long` for signed integral types.
    template <typename T>
    struct Hashable;
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_CONCEPT_HASHABLE_HPP

/* hashable.hpp
TnyTHi9KfOOMFyS+yYwPhT8N3fQG/nnF09NSG+2vS5R7MH0iyb07F6IEkVuoeZbRShSQB7lIkWPBQGOTBXE2Q6yVEAFDeW16itn3lJcnTHkxcao1bC0fjiRyMxsJ4Yx65/GkBYCL/1Jz6nVkLsYAXDDUeLJVcVm2ChS3rgCQL2VrGXcUSKGWtJYxi60fDY7vxv/DMWTCdHYk8njwuPFOtGhpmA9W9E+cdo4eILMJxQ5ozpreTHiurtaOBbJwbXFtZnP62v40pti0kZg9hWtqvkD+KvUUZaNb/pIXakcYH1j1Gcf1GXEqlxMWOYyOVMSZNbJVxdiLPawtmC9tbUqvINWkgi2f32U+m3gvo/zzO4lmUTdlPBXkg8ZXwR9lkEWQ+gpHyU5MgR0ke6nDsJD1mMH1eCQqMX23BaZvlrxb24k9yTXRbg27iUO44OfMlzL2oXCr3IzPUbBVqE/dhHNl7CT+uGR3vBMrIDZ5ue0rjpE3G5wUycmXFHMIzjf+C466pX7gC2iBSLT14iGOz92dVCS3t/AeoxZJl7kPpB93rInBLNiC0Z4bCnuu3hLl49GLsdGCgPBoWpCEuISfb4qL8KT4CWLe0XrLxgoX16ez1DUHW5YcRebKxBPVlkbZEorPjCY2/5gwqjmKVXKXr8d7iA3bc6IpMpGMW0txYUQ2D1YwQ+L0YyyAeSQG1hFhsUGiQzHdEZNYOiEtPkpGF0ExMsdaJb7AkNDhIZFdYwHcJiNC4bC4dzqof9TsGjVXELqkCpysLbMhutFhFV4KKD1QeHM3AmmuILR1YonPJSnAd8St4uY6qK7mclVAH4AbZyvhZJWpORP/IwqZ56Yy0/1cUgMlHMJQWR6rzwDHi5eJB3p6xXuExgrS6cio6XFY0oMm2XN+TUdRePhuKLQ1XxyLSxKQYdyh5J8RuSK+Ss0uCkAT6KBRrmC1IfHroZrkTNEVF6+coJzd7kP/p1EJDggILrHIy7ka9mthKSC42FhrRZ6nIzeryOoQ1VeMGaIX2ZND4u6pehHtZ2xIkS2ddYnKOoiX1lIaCtAnqCJ5Drf9I/Ke8rN0XhYV449SooOVw6QGIJkWmsbD/z966u/3j+9XxY+UXl0GSYUg2vK00ZHzVEonzcZHxCKtf4+5+ttl+/abrBjMg7cP8wN8KMD+F3kzGIoQY6MokZ+eYlKeXtUHGV9bBcaM22SBd4e08hET5CjRfbKyK6blqdV0jzZmhWjImF6bS1TqwyMllXqLnuxj8WX1liOexhsS6/OlWx3s/rKOp90z8Z7R5AI3iMxLamKtIU4twzzHHRZXTrFpuvJcXUuZTIBHxhI610VmZzCV+URpWLWQdMGG8/RGApec4lVyajeREhiy+iinuLva0h3uinDmc/BOR+vIGBTrZXwT2bblqS5Zoycm6ekeMI5K142YoRvxLI72NT2apkjuVUxyvZLchqnXiap2IYB80O9G4+r6s1ob17CvpMSEKRNjroLmR9AvOKGyQe+JNBo6EQ4m3N11EQiBqsLHR2iGZhByhlFFmYnWCgu2S99rgSULpGcEXzlGWyBwQZn7P2Kt3pzLCy8WEuq0Ij4Q1max8MxlNclPavqyhUhqAPqJkcO5J8gYa24DG3qj60/cbK4Iu90UXvlFY4jzideO5oBpMpOZQZOm0lxLDSt7nK1jjyVnFOPw6mUmoDOg4KOQ55NrpsocFatwQIKGHyyPJNYP1vPpEvVWJBaptzxxnnorFLPVW6k4dTAfYlA8DaetGTyqJyQWgQrlQumej9EemGYN+xuRADccWX3tZzK4eWoUpjbg3x72ltWovAipohGZPY8ipqil9TQFn3NE7DEVnEWCzrdHDEU=
*/