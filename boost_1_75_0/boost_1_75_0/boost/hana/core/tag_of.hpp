/*!
@file
Defines `boost::hana::tag_of` and `boost::hana::tag_of_t`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CORE_TAG_OF_HPP
#define BOOST_HANA_CORE_TAG_OF_HPP

#include <boost/hana/fwd/core/tag_of.hpp>

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename T, typename>
    struct tag_of : tag_of<T, when<true>> { };
    //! @endcond

    namespace core_detail {
        template <typename ...>
        struct is_valid { static constexpr bool value = true; };
    }

    template <typename T, bool condition>
    struct tag_of<T, when<condition>> {
        using type = T;
    };

    template <typename T>
    struct tag_of<T, when<
        core_detail::is_valid<typename T::hana_tag>::value
    >> {
        using type = typename T::hana_tag;
    };

    template <typename T> struct tag_of<T const> : tag_of<T> { };
    template <typename T> struct tag_of<T volatile> : tag_of<T> { };
    template <typename T> struct tag_of<T const volatile> : tag_of<T> { };
    template <typename T> struct tag_of<T&> : tag_of<T> { };
    template <typename T> struct tag_of<T&&> : tag_of<T> { };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CORE_TAG_OF_HPP

/* tag_of.hpp
AFGPBAlRXuO/Q1SPoCHq6+GxiMIw7ISoF3VEFVg4Gn7IESXuNJQrebPLcYUYX2HFIFX6BTxV7rnIujKCLP9SQz/gxAD1S4K/i+BvGvzNgL+58Hd1cCi+do35DnwFEEmmngi+sr/i+Nrz/fD1zZlz8fWnbsLXfOHf4QvLJXy9NSwWXycFDV/3mTR8TUz4j/g6C0GOCILU8DSoSwb8OeBvGfwVw9+N8Hcb/N0Jf+Ke3FkyS/XNxLPKJsvM4htHwtgIeJZS5KWpluBYuJqDNrgKweFwTQ2a4WrcLjSKO3Nn/9eZKaYSdMcFrPbLCPb3fIGxUhrx82L9c3n0828in6FfvQaYojUgRiCGvGQnDnfe2U5mITdIeF+Y3JSbLawQdxbOrm7AbyvY5fRNkxffNFShn5Nl67JZTXnZBnHHIeCyhvLabKdvHgIt1Mhnpw2SLbNtFWBk+3OFqi2zDMDSpET21heRCg52YwWD0L7VZcDVqu6ZdZlvuD833cluBiWjUc5NhPk5ES2DuemgCwAu0sNQkXL5ntl6wsf/XcKtubOy86QLVUHusIAOJtaiv39zbgodHYdhh7OXSZeogtdyw5S99H0WHodamMImRet4A9WxUb5nhkH6TNwTkENe8REkd7EG93TIoaW+5XLoet/VcugH0LUhj1gbxCkn11Y1zyPZcppzZ1DghlxbF+4ehEc6ba6Z3+NyYNcb/J4OmUOY
*/