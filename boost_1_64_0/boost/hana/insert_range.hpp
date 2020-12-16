/*!
@file
Defines `boost::hana::insert_range`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_INSERT_RANGE_HPP
#define BOOST_HANA_INSERT_RANGE_HPP

#include <boost/hana/fwd/insert_range.hpp>

#include <boost/hana/concat.hpp>
#include <boost/hana/concept/foldable.hpp>
#include <boost/hana/concept/sequence.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/to.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/drop_front.hpp>
#include <boost/hana/take_front.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename N, typename Elements>
    constexpr auto insert_range_t::operator()(Xs&& xs, N&& n, Elements&& elements) const {
        using S = typename hana::tag_of<Xs>::type;
        using InsertRange = BOOST_HANA_DISPATCH_IF(insert_range_impl<S>,
            hana::Sequence<Xs>::value &&
            hana::Foldable<Elements>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Sequence<Xs>::value,
        "hana::insert_range(xs, n, elements) requires 'xs' to be a Sequence");

        static_assert(hana::Foldable<Elements>::value,
        "hana::insert_range(xs, n, elements) requires 'elements' to be a Foldable");
    #endif

        return InsertRange::apply(static_cast<Xs&&>(xs),
                                  static_cast<N&&>(n),
                                  static_cast<Elements&&>(elements));
    }
    //! @endcond

    template <typename S, bool condition>
    struct insert_range_impl<S, when<condition>> {
        template <typename Xs, typename N, typename Elements>
        static constexpr auto apply(Xs&& xs, N const& n, Elements&& e) {
            return hana::concat(
                    hana::concat(
                        hana::take_front(xs, n),
                        hana::to<S>(static_cast<Elements&&>(e))
                    ),
                    hana::drop_front(xs, n)
                );
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_INSERT_RANGE_HPP

/* insert_range.hpp
bf+sezdxgBlST5lvRpgn40nGnQk2yH+yNNbIqZfGGBucOOtalqbfnKSPk8/zuufWvs/scerF8tPPFKuk3UEbPuM9B7GZQSb/7DWnuE7GHfWJGCPM021etlO8pvA4O93ao4dxVuy7JIYvsf5pf573LlZcOznpeeaHfUdZzPm5ey2xV+yVlv8j966eZ9/J3MT/DSexR+wTJ8VpcYPcO2sno6yQmSGftpwUe0n9rXt0TitvwvPJ37iX97x8wz16PP0u9lHe+ro+e9zOKIuk3NUaoZURlu27KIbvZtwpUE6jOMgsvdI3xexMY08vUwzKty5m3N3Y0c4IC4TuYbu25ImnGWWZnHtaV4yzSk6WdEZZJTf+PU5OZJtXlki9r3lhgiVS7yedPiYJ319/iDHJOjk5njPLJlkPMN50McIcmQ80pwwwwzp5DzLuDLNMZq48dDPGIqFLjYH5T91yn00zA0yxcN5Yhc2Jv8tZJmXb+0nMsEnm372up5VBplkl7R/eh2SEdTL/6T6OedJDxohxtsm5mfawQObNjTuzZN5C/1gkJ6zddDHKAttkH7KdbqZYI/2Wjn1aGWKdvFtZC34/uItTLV7jiptkuW84TT+b5P1eOxlhjbQ/6Ae9NG7qC1l/9HcrDDHLFpE/ef41zwl93esNTj1XPnGSFXK/oSxGWSNn0bgxyALblH/TuLNG3re0l2nWyP22/RlmjtQlfzdEN7NsUPAdbWWBUa/vM7+rHfSxQMhv7R+hmUlWyF1WLvmf1hZxhdTvawtd1K3q8y2tCXHC+1ehn0qjn0XSf+a6Sg/TpP7cc4ZZJWNNG+hnlm0KfmGcmWCb6C/1gznCzsNVzJG9bowYY4nIV/SPLaJfVQbDC/J93Fgz/ylpnNaXURbI+Iz96GeS0Kw+08UoJz5pXsX8z9qPERZI+5z96GGClS+Yky96zgwpX9JO+pkjNC8/09px4hPayTzpyu8jXbt6PyYvI9P2fY/2PNX+4hLzZ7WdzPfKKzaKQ6Q+3ftQbcbS49wJfWaEFVLeZxxoZ4pV8t7vOcOskfEBY3urkPs05Xkc+ZC5ZIXcDxsHZkmfUnenuRJH2SD7I8afqacZkwLnc4/XWXmHdTSmX0yzTs479ZshZkl7lzxUvdu6YoXMcf1ikpSbtJVTrL/N9rcbGxo9bvd6fZyui0LWrfcfPM7osU7pZY40/TlC1nOsZwZZJeO52sUC073GgLznGQ9WOfF8j2l8gXbe2fmNCY+3yekzvoxxynvky/HfExwwxmyR+3LpjLFJ/yvMHTmv1AZGWKNgUB8YZYmsVxlHJtkm+mpzwhzrj3RNo5txWl9jvAkNaSs9TJHyWs/pZYHM16mTSUKvd5zSzRhLhIe1g27GWSb1DcaQUdYpeKP+MMkW0TdZG0wzMqIv5L9ZGcyyHrPPOX3gyPX2ZYoN8s3Vyg3WTLe+MsIqzc/UJtqt9RVyW/WDAabYIPM6+zDEIj3Wf541f4p18tqldzgOWeW0dTpC2gOdi+hjltCDtIsYYyyTnWtfJtniyKXKZ5otIg/2nCk2yHqIsaSXKdbJzlMng8yySfZl+kEvs2yRf7m6GGOFrIfqA4MskpbveKCPWbbIO2wtMswS6Q9TLv3MEnq4NtLLDOECfaaPGbbIu8L4Ms4qWY/QXoZZIv2R9qGXGbbJO6KtjLNK5qPUSx/TbJB1pfXCINNskXPUNvqZIy1i3dDFJNscKTQHTLBKRpGyGWCJ1GLroEK/GWaN+G9E5l7pmnXMmDHGJpFK7Wae9CppjLJKerW62SanRruYJlxrTpkhVKc9xJhmnSOPViYzbFNwXH6mybrKGDDNOpknrAe6GWOTgsfoL+OskPY=
*/