/*!
@file
Forward declares `boost::hana::default_` and `boost::hana::is_default`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_CORE_DEFAULT_HPP
#define BOOST_HANA_FWD_CORE_DEFAULT_HPP

#include <boost/hana/config.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @ingroup group-core
    //! Mark a tag-dispatched method implementation as a default implementation.
    //!
    //! When defining a new concept with tag-dispatched methods, it is
    //! sometimes possible to provide a default implementation for some
    //! method(s). Making `default_` a base class of such a default
    //! implementation makes it possible to detect whether the method
    //! was dispatched to the default implementation afterwards.
    //!
    //!
    //! Example
    //! -------
    //! @include example/core/default.cpp
    struct default_ { };

    //! @ingroup group-core
    //! Returns whether a tag-dispatched method implementation is a default
    //! implementation.
    //!
    //! Given a tag-dispatched method implementation `method_impl<T...>`,
    //! `is_default<method_impl<T...>>` returns whether `method_impl<T...>`
    //! is a default implementation. Note that if there is no default
    //! implementation for the method, then `is_default` should not be
    //! used unless a static assertion saying that "the method is not
    //! implemented" is acceptable.
    //!
    //!
    //! Example
    //! -------
    //! @include example/core/default.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    template <typename Method>
    struct is_default { see documentation };
#else
    template <typename T, typename = void>
    struct is_default;
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_CORE_DEFAULT_HPP

/* default.hpp
SlLPuhfp7QkAAJ4dAAAdAAkAY3VybC1tYXN0ZXIvbTQveGMtYW0taWZhY2UubTRVVAUAAbZIJGC9WVlz20gOfh79CqysxHZKki05+zI5amiJtlkrkR6RmmxKdhiKbEnc8AoPHzuZ/75ANw/djmtc6yrraAIfjgbQDeig9XJ/tYPaATzYLctvuTPLZm3/LV/qhdFj7M4XKRzZx9A97ZxBC9+6p9C3Apd5oKcsmLJ4Du8dvvDbwnp4aCfsI2e/ZrHvJokbBpCGkCWsCTYiNsEPHXeG71bggOMmaexOs5RBunATSMJZem/FDGZhjASPiBNlcRQmDO7ddAG4Su9hlsKMMUCOBYvZ9BHmsRWkzGlCFId3rsMcxLNSfGFgTcM7hkB2aU8Qpq7NuAJcalSpWjyKImbF4AZgeR5xuixpc7OMKxl07cL4JI1kUHS4Hml/KH25D3VJx+91kNQ+J5LGxpU2gr6i9waSMtRBGgwAuUaSaiiyjlCfFOMKRvKlNEIODZkQroJWe4NxX1EvOZ8yvB4oKKTiB+0CIYbyqHeFC9K5MlCMz1z4hWKosq63EQJUDeQ/ZNUA/YpglvQ6l2GgSOcDGS60ESJJ6mfQr+WeIg2aqPRI7hlNRCg+IUdPU3X59zGiIQ30paF0SWqMOGv+
*/