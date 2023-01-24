/*!
@file
Forward declares `boost::hana::mod`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_MOD_HPP
#define BOOST_HANA_FWD_MOD_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Generalized integer modulus.
    //! @ingroup group-EuclideanRing
    //!
    //! Given two elements of an EuclideanRing `x` and `y`, with `y`
    //! nonzero, `mod` returns the modulus of the division of `x` by `y`.
    //! In other words, `mod` can be seen as an equivalent to `%`.
    //!
    //! Cross-type version of the method
    //! --------------------------------
    //! The `mod` method is "overloaded" to handle distinct data types
    //! with certain properties. Specifically, `mod` is defined for
    //! _distinct_ data types `A` and `B` such that
    //! 1. `A` and `B` share a common data type `C`, as determined by the
    //!    `common` metafunction
    //! 2. `A`, `B` and `C` are all `EuclideanRing`s when taken individually
    //! 3. `to<C> : A -> B` and `to<C> : B -> C` are `Ring`-embeddings, as
    //!    determined by the `is_embedding` metafunction.
    //!
    //! In that case, `mod` is defined as
    //! @code
    //!     mod(x, y) = mod(to<C>(x), to<C>(y))
    //! @endcode
    //!
    //!
    //! Example
    //! -------
    //! @include example/mod.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto mod = [](auto&& x, auto&& y) -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename T, typename U, typename = void>
    struct mod_impl : mod_impl<T, U, when<true>> { };

    struct mod_t {
        template <typename X, typename Y>
        constexpr decltype(auto) operator()(X&& x, Y&& y) const;
    };

    constexpr mod_t mod{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_MOD_HPP

/* mod.hpp
od736Nx2HSzr+CtFNOt0aBmXsUP0nE8adU8FqyzTBAOkb/B2/wGcY2q8rcdwpXKdlRuZJC2QXbpz+JegrlKt6MXyifLV6QAzOb28yjfhn3nPtgw6DR9ZryJuXrgRIRp7HVsB/QHfqcybJ/YRZB0jT4iogBd3DHDuQoi6X9Ykwjz7K6faPpTyvgbG9/wXnnVVI8sxuERrHgXZCxEbFesdQwCqlvyhuYMhXx8Q7g9G+QBU+FLSy8W3XYm1rAxbjgev7maKywP/278oiLRNOnQzrE6RAcRGZhHly2N74/RXRBMDIof+URnRMxySc695Udcb0VsYfI/LYIgND3S3BWxBFeYwq170vXPxeJ+zReyOQ3/YbyOMHaUQ+Uj/ZvSntQ9mWgRISEhsSP+H0T/+T0YX+neWsvRytP7PkgPo6HpmFPCFWB50YdZF9/7qmujyK3Jo0jcGs7/MjuZvwmkdPmdmLH04e49nNHk6OYWtR31XGq+cO6aZ4bXHMcX4VdsnwzMtISaojLhsfi+m51xrlC4DoVX2m2XoijHx50OSEg0Z3aeemgC7JtZ02eS837kzUHgx9NUn5DVoQwzyvCRhfAOn67yfUOUfOLOVPYXroLNOKu1wfKuw/dSXSdAqwce3x6gu5mvOAiT4KWSCIoqVisR7YCsppIGsg6IryVeLZPBmXoHE4sfXwV6iXi2LrAoC9Tb4K2LvSsw3wpQO8Jlf
*/