/*!
@file
Defines `boost::hana::Sequence`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CONCEPT_SEQUENCE_HPP
#define BOOST_HANA_CONCEPT_SEQUENCE_HPP

#include <boost/hana/fwd/concept/sequence.hpp>

#include <boost/hana/config.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/core/when.hpp>
#include <boost/hana/detail/integral_constant.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    namespace detail {
        template <typename S, typename Tag = typename hana::tag_of<S>::type>
        struct sequence_dispatch
            : hana::integral_constant<bool,
                hana::Sequence<Tag>::value
            >
        { };

        template <typename S>
        struct sequence_dispatch<S, S>
            : hana::integral_constant<bool, false>
        { };
    }

    //! @cond
    template <typename S, bool condition>
    struct Sequence<S, when<condition>>
        : detail::sequence_dispatch<S>
    { };
    //! @endcond
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CONCEPT_SEQUENCE_HPP

/* sequence.hpp
mQZHKF7hObOPStgd2XHV0IdSTSc8fVXM/q5i9nfCs78Tnv2/PFfQjhI82Ovlijv3cmRbIQNniCOGehliQBxRbwo+yhV8lC7kUkdLONr/hCMuU6n2Zy9H3JVaAbvDDK4K+uphB8INtlJKXKWUhK05RWhrHC3tZhQuNdv62VxZcp52dnWUlIIe6+woWef7zQWDjpL1JnHSi0FfVh7CVPGK/e1vbbjqSvQgSFdFY/vWnOU90Y4H9AcrdQBJELHTgVQ=
*/