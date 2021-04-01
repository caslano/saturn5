/*!
@file
Defines `boost::hana::zip`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_ZIP_HPP
#define BOOST_HANA_ZIP_HPP

#include <boost/hana/fwd/zip.hpp>

#include <boost/hana/concept/sequence.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/detail/fast_and.hpp>
#include <boost/hana/tuple.hpp>
#include <boost/hana/zip_with.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename ...Ys>
    constexpr auto zip_t::operator()(Xs&& xs, Ys&& ...ys) const {
    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(detail::fast_and<
            hana::Sequence<Xs>::value, hana::Sequence<Ys>::value...
        >::value,
        "hana::zip(xs, ys...) requires 'xs' and 'ys...' to be Sequences");
    #endif

        return zip_impl<typename hana::tag_of<Xs>::type>::apply(
            static_cast<Xs&&>(xs),
            static_cast<Ys&&>(ys)...
        );
    }
    //! @endcond

    template <typename S, bool condition>
    struct zip_impl<S, when<condition>> : default_ {
        template <typename ...Xs>
        static constexpr decltype(auto) apply(Xs&& ...xs) {
            return hana::zip_with(hana::make_tuple, static_cast<Xs&&>(xs)...);
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_ZIP_HPP

/* zip.hpp
MHIH+LwcEEsQ/KyBZzk9HzCDArgEit2R8sJbskz4AHrgNlk88ACEhuDMSGgQ34OK6neQxvd74+4TNKXGNKS9yuvUZRzGMPF4FHsmn5VDBGDl/J7/IaPBcOp6+AsG55/LFM2UeL+L9O8HvQqjbBSSCV+TjP6xpvlLU15KhYcbLGBA1ykxLJSIKQLucoeg3imN21hXWwqtLMx/51aM6bRTBmd6heC+WmjV8DcqLNJhpU4y9UqLSv86zLuElyf/aaKj4uC6pmjYNhz2gStOfA+8vRh/iwTqzDkuxvl9AV5t3MKIyeAurJVLWQRLLt1YQxvLVrWHUJ2DehMAMLX8epNAKRNdHgYaKlKvXc5p6cvFcEKlnP7Wio824HvgGQDB80UtSuT5NcQgjkC+8oOLlVKowg0le6TOYYi/e9nMPrS0BaIaBLMczcG6RY/mEQHSlNaPetkztJH/L1tVRPQWYnahK/3BprNfWBk73jeJzm8ln1C/bNRHy3H5kv/vzdceiZR5geWyIMV9y0dojptmt1/gnSCVniTyzkSrTbA3DKQHhGj12wcjJzxLOuGuKA==
*/