/*!
@file
Defines `boost::hana::fill`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FILL_HPP
#define BOOST_HANA_FILL_HPP

#include <boost/hana/fwd/fill.hpp>

#include <boost/hana/concept/functor.hpp>
#include <boost/hana/concept/sequence.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/core/make.hpp>
#include <boost/hana/functional/always.hpp>
#include <boost/hana/transform.hpp>
#include <boost/hana/unpack.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename Value>
    constexpr auto fill_t::operator()(Xs&& xs, Value&& value) const {
        using S = typename hana::tag_of<Xs>::type;
        using Fill = BOOST_HANA_DISPATCH_IF(fill_impl<S>,
            hana::Functor<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Functor<S>::value,
        "hana::fill(xs, value) requires 'xs' to be a Functor");
    #endif

        return Fill::apply(static_cast<Xs&&>(xs),
                           static_cast<Value&&>(value));
    }
    //! @endcond

    template <typename Fun, bool condition>
    struct fill_impl<Fun, when<condition>> : default_ {
        template <typename Xs, typename Value>
        static constexpr auto apply(Xs&& xs, Value&& v) {
            return hana::transform(static_cast<Xs&&>(xs),
                                   hana::always(static_cast<Value&&>(v))
            );
        }
    };

    template <typename S>
    struct fill_impl<S, when<Sequence<S>::value>> {
        //! @cond
        template <typename V>
        struct filler {
            V const& v;
            template <typename ...Xs>
            constexpr auto operator()(Xs const& ...xs) const {
                return hana::make<S>(((void)xs, v)...);
            }
        };
        //! @endcond

        template <typename Xs, typename V>
        static constexpr auto apply(Xs const& xs, V const& v) {
            return hana::unpack(xs, filler<V>{v});
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FILL_HPP

/* fill.hpp
IRCM9uUV5GpfXj0GiLJkcYGokCoGnDKZXXDcZC6AsaldBaY82wgmrKKsBNNeQ9mwirROAG7ShlW0dcJYQduwirhOQNXEDauoWwnHTV2/ahdTk1S1i6nWrqVYbl3BslUqSBnAKoatkgplKCvYtUo0uIFUMaukp2MX4GlZRU9u7thFHc2rGLWCog4IK9m0gqQOMKuYtIKmFVAqWDSIk9jFo2pi6INKHqW3gqbOedXNK5iUPlhBUwPCKi6lr1bQ1ACzgk0VlAqaFqDYNBX2c2ujkzSDL3mLi8N7791ls7XLDwtnFnEJwBdMg/OWqUvJScJey2plVa+OrV2oBgU4q/b3MhxDxVgHxyCShlOh8hiw1uk9blhuvNbpPxqWaxux4W2ylxThrRrp+kXP0ISZ2MVk8vu3rUuL11DnhWcFHhOc9f3RDz/Q/Z345UeT1ySyN+P5pqyiO6+Y4jKsyil2wjI19WpYJXW9BMs1xTa8lVPshLcS3ErVrgK9VYRbwTFu5FbOQvU2bgErs1/FHiNaHf/wHTOhzXzLDG8E+H2R4bC1RA9er5MpuqMKOVCGVSkHnLDMY101rNLZrgSrQqUswFqnVxbhpZXQNlEBVmNnj3YldhWjXTUPGzGPk+WsNq13Tfjf0YHf7118PDw++N6S
*/