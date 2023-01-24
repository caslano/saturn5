/*!
@file
Defines `boost::hana::empty`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_EMPTY_HPP
#define BOOST_HANA_EMPTY_HPP

#include <boost/hana/fwd/empty.hpp>

#include <boost/hana/concept/monad_plus.hpp>
#include <boost/hana/concept/sequence.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/core/make.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename M>
    constexpr auto empty_t<M>::operator()() const {
    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::MonadPlus<M>::value,
        "hana::empty<M>() requires 'M' to be a MonadPlus");
    #endif

        using Empty = BOOST_HANA_DISPATCH_IF(empty_impl<M>,
            hana::MonadPlus<M>::value
        );

        return Empty::apply();
    }
    //! @endcond

    template <typename M, bool condition>
    struct empty_impl<M, when<condition>> : default_ {
        template <typename ...Args>
        static constexpr auto apply(Args&& ...) = delete;
    };

    template <typename S>
    struct empty_impl<S, when<Sequence<S>::value>> {
        static constexpr auto apply() {
            return hana::make<S>();
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_EMPTY_HPP

/* empty.hpp
QXG/fMpeJAPp4ZsLzoI7sHzZ1fBeqHhSgE6Z54jIX8WHKsEg96e9nqsojuoad4CY5UBRZMJP0Pvc/rSX3fxqORKXbVbxKX/Z1BDd+lloIE+Y+buun4NB4oBrapHlyW6cSWHmyrd4dTz8ZaAydG4H5y8J6jMXGXuWlXAtVtJSOqkfteGkh7W/AqeQhPjZ/JNDsYVvKHHtcIzveSy589467zT8tbrYDiee2/Rar4fCOOcp0aJD2fSBYtJlpNrzXVcYG6hoRzwvfAtvLSojzmuWBoqtp8WVAQ2HwP94Vuk0nOtU04aexbBitGThPS2fnuSm5khqRY+VwXZ+XZnTjAmzcEFIbvMHpzRmNWaNByHFYvQLJbSDqVujLlObvg7IGig4FUJTSVOE8GoEc7iUEm4g/e1XE0AULvEx97PPiOGl4XTvY0vJ61hTFe4WyQ83H6x44xvRL0B0p9FQ3oM0wNjLuboka8OfzLiU3GxNTomQ9r+GnQHh9QSv3O1CjB9wvCIYoPL9RjVL3AQRQlvf3F/x2wvlUlqHdmmQfwZk1bVX1LWfDjoaM/k8rYeSG0qg/4XSS5AaEzefWa3oM7YzhcSLjvV2tq+dTpQyRSeFmgst8glNVmlLLAsvjXa8ohnbGC6lI1+xeLOro4i7VEMiDtVxU81DHrMYPUO/MqTmRezUDAba3nPbDPIHPmbEmhtGequCQbY97y5+nawWw7uU
*/