/*!
@file
Defines `boost::hana::members`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_MEMBERS_HPP
#define BOOST_HANA_MEMBERS_HPP

#include <boost/hana/fwd/members.hpp>

#include <boost/hana/accessors.hpp>
#include <boost/hana/concept/struct.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/second.hpp>
#include <boost/hana/transform.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Object>
    constexpr auto members_t::operator()(Object&& object) const {
        using S = typename hana::tag_of<Object>::type;
        using Members = BOOST_HANA_DISPATCH_IF(members_impl<S>,
            hana::Struct<S>::value
        );

        #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
            static_assert(hana::Struct<S>::value,
            "hana::members(object) requires 'object' to be a Struct");
        #endif

        return Members::apply(static_cast<Object&&>(object));
    }
    //! @endcond

    namespace struct_detail {
        template <typename Holder, typename Forward>
        struct members_helper {
            Holder object;
            template <typename Accessor>
            constexpr decltype(auto) operator()(Accessor&& accessor) const {
                return hana::second(static_cast<Accessor&&>(accessor))(
                    static_cast<Forward>(object)
                );
            }
        };
    }

    template <typename S, bool condition>
    struct members_impl<S, when<condition>> : default_ {
        template <typename Object>
        static constexpr auto apply(Object&& object) {
            return hana::transform(hana::accessors<S>(),
                struct_detail::members_helper<Object&, Object&&>{object}
            );
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_MEMBERS_HPP

/* members.hpp
ilEAckRcnxp5inYONlemlvY8YIgcaDdMLwkwzlJOXfszJitlsUNSE3avcbwek4cGwjvhPrxl+OM4d9rXgIEwW4thZMHRaaK2SNkQHQGbpSVetvGnrvQXxWY0eIzEKoKJ+fVq6d4g+BoZUsKvvWquNurddAlVpZKE3/OBB2I7asQw9fbj9tNkx2C3iE7vyPHUWcrwXmUbkA4Kj6CUw7b4YcrCfKwKEofVmSLhFe7ZXXekPJrUIhLPuzUY5Gnmn4FPwBAyy9Xuox8WKk1f1DtXvzgKtZpCiLhgdwdVqIpcMcbvlBRmbOusjL5FF3LVXfrR0FV1XIHdMyjkmNP/KMmrWuG6aawKMqdVv7ZFAsEmV/9VV/cUKLdSwbOrAMDs36p+9ZY+kEsyuBQxrF/kksbTDo4b0TJ/g/Mlll2fBSKavt4rDVwCJ4V4d79ab3m33p/Jj1qNfuozHNuiiUvoY/+3WKBJQOtJPqYV8l5XXalEMUGcTItyg8refBCxtX9z53UDg0RQxe4m5tarmHhzXp/XEy+/uQw4ufVg0GbhvZfJjUEmCQkFeqhj7Hsb0Q==
*/