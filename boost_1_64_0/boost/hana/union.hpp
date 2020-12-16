/*!
@file
Defines `boost::hana::union`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_UNION_HPP
#define BOOST_HANA_UNION_HPP

#include <boost/hana/fwd/union.hpp>

#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename Ys>
    constexpr auto union_t::operator()(Xs&& xs, Ys&& ys) const {
        using S = typename hana::tag_of<Xs>::type;
        using Union = BOOST_HANA_DISPATCH_IF(union_impl<S>,
            true
        );

        return Union::apply(static_cast<Xs&&>(xs), static_cast<Ys&&>(ys));
    }
    //! @endcond

    template <typename S, bool condition>
    struct union_impl<S, when<condition>> : default_ {
        template <typename ...Args>
        static constexpr auto apply(Args&& ...) = delete;
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_UNION_HPP

/* union.hpp
JyexTuiuj15XGaIc3xdsXArfBWVbYRzGC1/04+0x2hyOs9ztqdwTxMC7ruosi507BL9p2KZIh917nMf5PS4Xa4MfjBw6zbZPz5dY/RiTQXkvDp2METL17tEaXP8LlJdbZrjVRnnNNmMibWh5vnRPjboemlSOAYE+ikXbbON4rbxn1TncMpwuHQL3cj2fX7TJxdWuVdE6tOIrckh5e1Z3relbJZj1NsCkB9CylXj/11EZ0TCuqsFooZmGe086e0V8hvhPxGdAYDAyhj5a6JNMyK7tAz6tCvek/10Z7Fyjvs18Ji/0VVC/ruJtJZjx/5MyXAaJL9cfLpd5FCvn+GDj6RJe3GPgT5RY4NmO8kvLjGmHureKbcdohLNg3NsNKJZXz6GF4wXOIiZzPM+YdE/L+7/LTyixclvH68b3DXhBwystED8em5LGxzkl/I3uzjA1hR3gEP6yZb7+V1K913HXVMZZD3bAFNOB9vuCrxn6mnPLXpHYNma5j95E+Z5gdd/ZulNs9yRgGiwxBI7yOH0P5X+8GAJ8jjFh/Vpyo92+4FXdYAehEAm3zDn70cSLeN61qaRTEWfB7M/HlWgeLumiaA7dsLm/v5Dk8UziTFMNvp3avXABoFugdOzLFbvAlvvQX1O9l2Qrnak1Z2AZnOcws906j7eiDZJZ63rXuIqtFF3DsFnZI1zdzGfOScyb0K1q7CDX6UlVX6+TYD9ciDp3wjXFEXvsweN39x9/9bon7F7Z2736uMvAF+KYn3gn8KmJcc/nM7x3Bz/0J8PzcG8ZYobd4IOfOz6/YXwO6AGmfs5GykUv4fnWc7a21RDSZAEvPKvg2bOMhfT0tbFyR1bbVXx+CM+N9c8IMbvCbcrokw7PXwbPB8igtaOeqSwhBplb3xF8ZLyDQvvKeyVzuR8Dmd6HSOFluZ+Oz0htko7Pw3OfCqa63w/Pn9FXm42Km/RGbY71+X2oj4PNe1mhSFsArXbiGVsT2m1DO8L9u9DVZrgbgt/nYz9I96wdcNGv4SywBYnIUCS24wvAc+3KIqbiOQsxQPDsb/Cs9AKjHmY7V4+T7P03Qv2dbcLf1JdHIAveHZPajfX7MtCEgwckFuBL4W4sva1xa7uMgb0c890FxwdiXiXxtX++SaSfnOTLMqr3pokWL8lPdoGKMcsPuUWmzRZwVYzlPeJW6Tm9x9ogMbu3WUPfWcYEf+G2SJ/eg2EZL7o95cl+Scs2bd8h0bMjImnv2+6YadHCGa4AUS+7U6adXYsXPHCMpPTv3jnQg/tN+KDxVh3b9uu7rKPvoPzH71bQYZt2cErr9tl7ZfrZPDhDUtqF+wba3uH8BIYQXFIsSL1ec3+gTXJFUfovHzTST0/PT852ENAK3/P7HhzpMC5Hv7+9KzCGc18/LNLOXrn+jh35nvxwwrd61Y91kdHnPzu24LyF9B9GevSijXmDQpp22g83fvRIP4luUHBoIbQvFbTZMZV7/QVKg7WA0GS8Dxg9WnfiHdKS9rmRdnqQroPp9/HKaFuOucTA5/e0GCvvjHYcgDIdFe68YjeuVaj35vE8F1Wi4vvl7y7RMH9Xr6t/UXalIW52VTgurbW2OlWrY79ax35Vq7hMx21c0MkkmSZ2JhOTTK0baSbJzMTOJDFLnbpgQUVFwSIKda+i0B+CFfxRUKGgYhHBiooVXCqIuKEFUSv6w3PPe+/znru8mREcrTnPe+527rn3nnvOuZU8ZxsAhs4YIYz6L9ShOQuMfAcM8jr5CptO06y+KWL8rwl6dKoUNRG4373SxcnaxDrjWxx3q+Ysjy3akn2t9bvSkCyIcvzePW9hBlY7sjaNVawoN/s60IkSf/f8Jfm7+ms=
*/