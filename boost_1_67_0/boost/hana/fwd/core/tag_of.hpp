/*!
@file
Forward declares `boost::hana::tag_of` and `boost::hana::tag_of_t`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_CORE_TAG_OF_HPP
#define BOOST_HANA_FWD_CORE_TAG_OF_HPP

#include <boost/hana/config.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @ingroup group-core
    //! %Metafunction returning the tag associated to `T`.
    //!
    //! There are several ways to specify the tag of a C++ type. If it's a
    //! user-defined type, one can define a nested `hana_tag` alias:
    //! @code
    //!     struct MyUserDefinedType {
    //!         using hana_tag = MyTag;
    //!     };
    //! @endcode
    //!
    //! Sometimes, however, the C++ type can't be modified (if it's in a
    //! foreign library) or simply can't have nested types (if it's not a
    //! struct or class). In those cases, using a nested alias is impossible
    //! and so ad-hoc customization is also supported by specializing
    //! `tag_of` in the `boost::hana` namespace:
    //! @code
    //!     struct i_cant_modify_this;
    //!
    //!     namespace boost { namespace hana {
    //!         template <>
    //!         struct tag_of<i_cant_modify_this> {
    //!             using type = MyTag;
    //!         };
    //!     }}
    //! @endcode
    //!
    //! `tag_of` can also be specialized for all C++ types satisfying some
    //! boolean condition using `when`. `when` accepts a single compile-time
    //! boolean and enables the specialization of `tag_of` if and only if
    //! that boolean is `true`. This is similar to the well known C++ idiom
    //! of using a dummy template parameter with `std::enable_if` and relying
    //! on SFINAE. For example, we could specify the tag of all
    //! `fusion::vector`s by doing:
    //! @code
    //!     struct BoostFusionVector;
    //!
    //!     namespace boost { namespace hana {
    //!         template <typename T>
    //!         struct tag_of<T, when<
    //!             std::is_same<
    //!                 typename fusion::traits::tag_of<T>::type,
    //!                 fusion::traits::tag_of<fusion::vector<>>::type
    //!             >::value
    //!         >> {
    //!             using type = BoostFusionVector;
    //!         };
    //!     }}
    //! @endcode
    //!
    //! Also, when it is not specialized and when the given C++ type does not
    //! have a nested `hana_tag` alias, `tag_of<T>` returns `T` itself. This
    //! makes tags a simple extension of normal C++ types. This is _super_
    //! useful, mainly for two reasons. First, this allows Hana to adopt a
    //! reasonable default behavior for some operations involving types that
    //! have no notion of tags. For example, Hana allows comparing with `equal`
    //! any two objects for which a valid `operator==` is defined, and that
    //! without any work on the user side. Second, it also means that you can
    //! ignore tags completely if you don't need their functionality; just use
    //! the normal C++ type of your objects and everything will "just work".
    //!
    //! Finally, also note that `tag_of<T>` is always equivalent to `tag_of<U>`,
    //! where `U` is the type `T` after being stripped of all references and
    //! cv-qualifiers. This makes it unnecessary to specialize `tag_of` for
    //! all reference and cv combinations, which would be a real pain. Also,
    //! `tag_of` is required to be idempotent. In other words, it must always
    //! be the case that `tag_of<tag_of<T>::%type>::%type` is equivalent to
    //! `tag_of<T>::%type`.
    //!
    //! > __Tip 1__\n
    //! > If compile-time performance is a serious concern, consider
    //! > specializing the `tag_of` metafunction in Hana's namespace.
    //! > When unspecialized, the metafunction has to use SFINAE, which
    //! > tends to incur a larger compile-time overhead. For heavily used
    //! > templated types, this can potentially make a difference.
    //!
    //! > __Tip 2__\n
    //! > Consider using `tag_of_t` alias instead of `tag_of`, which
    //! > reduces the amount of typing in dependent contexts.
    //!
    //!
    //! Example
    //! -------
    //! @include example/core/tag_of.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    template <typename T, optional when-based enabler>
    struct tag_of { unspecified };
#else
    template <typename T, typename = void>
    struct tag_of;
#endif

    //! @ingroup group-core
    //! Alias to `tag_of<T>::%type`, provided for convenience.
    //!
    //!
    //! Example
    //! -------
    //! @include example/core/tag_of_t.cpp
    template <typename T>
    using tag_of_t = typename hana::tag_of<T>::type;
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_CORE_TAG_OF_HPP

/* tag_of.hpp
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
*/