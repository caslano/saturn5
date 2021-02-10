/*!
@file
Forward declares `boost::hana::none`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_NONE_HPP
#define BOOST_HANA_FWD_NONE_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Returns whether all of the keys of the structure are false-valued.
    //! @ingroup group-Searchable
    //!
    //! The keys of the structure must be `Logical`s. If the structure is not
    //! finite, a true-valued key must appear at a finite "index" in order
    //! for this method to finish.
    //!
    //!
    //! Example
    //! -------
    //! @include example/none.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto none = [](auto&& xs) -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename S, typename = void>
    struct none_impl : none_impl<S, when<true>> { };

    struct none_t {
        template <typename Xs>
        constexpr auto operator()(Xs&& xs) const;
    };

    constexpr none_t none{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_NONE_HPP

/* none.hpp
BlujYwNANORjbThXUlqnqOrKKlJqlEyG39HGdeqo1rSWRjBrGTZrMWO8rzOB65cXbsvCus328zYazKrG1GGNhw22v7fHHqlnrr8D3BePiICRMfCMCTMme/DZh08bPgeNvGJbqb+h2MQeVisYRtYwrFH0UbWyIzAOq5W8qV7Uhnl8bLSrFb6aLXWLTFljkn1Mdqz+MDaIjT4z+kD9PlC/D9Tvh/A5gM9htrgA3Q+zzwk2wMDnMc/nK7BVE62wku9wooUGWGflREtoJBNt6YQEZXc7OBn8tvv6LesUzKBQqpMzJ+UXNL8Xy6c6cy3WS+auL76gQSgvjs3UmptTUw/RKJdNV8uzZNIlLq/BpWUcun+HHCoWTnfIodAAowao+Jaub2NLHQx6tLbfnPxP/5w9lBr3Te8M/kL7fTIaMRfdGNEUTG01VyG4J2Rs/7IAttjSa6taauoR5WDpgl4HhUv3xprB1Bg+VR2hovutduuAHX8DcNqpF+3W0ZcMX7SPvky9OGw9wceMHe49Sb04AlD7+Opob49aLZdSYd7GUnre/de7HtrDJStlzRguLS4s7YqWM41YgTjDu059w1nUKhTnVWvdqiJMBBSyAoOfGIz2YjZPmYn4NjEmRNlcUwJfJYZEXsEyM0I0oxsRAt7f
*/