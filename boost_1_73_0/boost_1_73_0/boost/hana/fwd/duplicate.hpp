/*!
@file
Forward declares `boost::hana::duplicate`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_DUPLICATE_HPP
#define BOOST_HANA_FWD_DUPLICATE_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Add an extra layer of comonadic context to a comonadic value.
    //! @ingroup group-Comonad
    //!
    //! Given a value already in a comonadic context, `duplicate` wraps this
    //! value with an additional layer of comonadic context. This can be seen
    //! as the dual operation to `flatten` from the Monad concept.
    //!
    //!
    //! Signature
    //! ---------
    //! Given a Comonad `W`, the signature is
    //! \f$
    //!     \mathtt{duplicate} : W(T) \to W(W(T))
    //! \f$
    //!
    //! @param w
    //! The value to wrap in an additional level of comonadic context.
    //!
    //!
    //! Example
    //! -------
    //! @include example/duplicate.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto duplicate = [](auto&& w) -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename W, typename = void>
    struct duplicate_impl : duplicate_impl<W, when<true>> { };

    struct duplicate_t {
        template <typename W_>
        constexpr decltype(auto) operator()(W_&& w) const;
    };

    constexpr duplicate_t duplicate{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_DUPLICATE_HPP

/* duplicate.hpp
qmEJeL35Cs4NGgcGp7cDla/C3Wt13mtUWtV0ALndJvK2xqn4RQV7vZOPVN92uKEzk4OuIGAivgIH3MqoZ7VqxuYE7mQFvmYztYXiB447mURYaxb9mG5pdPvt18BLvfNfX9iNX2StX6S5Fu1fUsR73BtR3/Ph4MNH6mzu5akPszBOAnchlYPeG3HzGip23mzB8xcOxAe3d01s3KTWmmiqiX5uJpPWD1bSMY0gYv/vII5pa2cuA+gBM4c/avpppiBqVsOfxcXoDXgu79ofrAiuhdsztJeT1v/W2idOr98dN9KhGuIZkb9OXSuW4B5oLwrgXihwZpRmx3wXsQTOqAj24I3zZjAaO/32u64BfA3f1tKCEArS6yaFlI4zfHDTAXjfHvZ7/dNDoWIm1hq8v6A3wGkJIcDXsl0DDOsiZy8wvpe3iQwwnLR9G7MoABTdlX8thbvETSKG51KawiNVC5ZbRnjUgH1KVIqofVfLZuodIOY7r+BpE+uQcSvVSE7pXVatm16K2nZ5B0WBx4RJ6U8p5GXGqoxEhX1R/iysmzvnExm494p5OV3oWDA0DM+iLPNsPsAkJ3azYKuYNeiY29+ei/kDqkV1J1QX4rlGwWmWsbL2nXj1PoFDyPXgdxDmLj5tNUWXjyPxuQS2apbh
*/