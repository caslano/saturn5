/*!
@file
Defines `boost::hana::partition`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_PARTITION_HPP
#define BOOST_HANA_PARTITION_HPP

#include <boost/hana/fwd/partition.hpp>

#include <boost/hana/at.hpp>
#include <boost/hana/concept/sequence.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/core/make.hpp>
#include <boost/hana/detail/algorithm.hpp>
#include <boost/hana/detail/array.hpp>
#include <boost/hana/detail/decay.hpp>
#include <boost/hana/detail/nested_by.hpp> // required by fwd decl
#include <boost/hana/pair.hpp>
#include <boost/hana/unpack.hpp>

#include <cstddef>
#include <utility>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename Pred>
    constexpr auto partition_t::operator()(Xs&& xs, Pred&& pred) const {
        using S = typename hana::tag_of<Xs>::type;
        using Partition = BOOST_HANA_DISPATCH_IF(partition_impl<S>,
            hana::Sequence<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Sequence<S>::value,
        "hana::partition(xs, pred) requires 'xs' to be a Sequence");
    #endif

        return Partition::apply(static_cast<Xs&&>(xs), static_cast<Pred&&>(pred));
    }
    //! @endcond

    namespace detail {
        template <bool ...B>
        struct partition_indices {
            static constexpr detail::array<bool, sizeof...(B)> results{{B...}};
            static constexpr std::size_t left_size =
                detail::count(results.begin(), results.end(), true);
            static constexpr std::size_t right_size = sizeof...(B) - left_size;

            static constexpr auto compute_left() {
                detail::array<std::size_t, left_size> indices{};
                std::size_t* left = &indices[0];
                for (std::size_t i = 0; i < sizeof...(B); ++i)
                    if (results[i])
                        *left++ = i;
                return indices;
            }

            static constexpr auto compute_right() {
                detail::array<std::size_t, right_size> indices{};
                std::size_t* right = &indices[0];
                for (std::size_t i = 0; i < sizeof...(B); ++i)
                    if (!results[i])
                        *right++ = i;
                return indices;
            }

            static constexpr auto left_indices = compute_left();
            static constexpr auto right_indices = compute_right();

            template <typename S, typename Xs, std::size_t ...l, std::size_t ...r>
            static constexpr auto apply(Xs&& xs, std::index_sequence<l...>,
                                                 std::index_sequence<r...>)
            {
                return hana::make<hana::pair_tag>(
                    hana::make<S>(hana::at_c<left_indices[l]>(static_cast<Xs&&>(xs))...),
                    hana::make<S>(hana::at_c<right_indices[r]>(static_cast<Xs&&>(xs))...)
                );
            }
        };

        template <typename Pred>
        struct deduce_partition_indices {
            template <typename ...Xs>
            auto operator()(Xs&& ...xs) const -> detail::partition_indices<
                static_cast<bool>(detail::decay<
                    decltype(std::declval<Pred>()(static_cast<Xs&&>(xs)))
                >::type::value)...
            > { return {}; }
        };
    }

    template <typename S, bool condition>
    struct partition_impl<S, when<condition>> : default_ {
        template <typename Xs, typename Pred>
        static constexpr auto apply(Xs&& xs, Pred&&) {
            using Indices = decltype(hana::unpack(
                static_cast<Xs&&>(xs), detail::deduce_partition_indices<Pred&&>{}
            ));
            return Indices::template apply<S>(
                static_cast<Xs&&>(xs),
                std::make_index_sequence<Indices::left_size>{},
                std::make_index_sequence<Indices::right_size>{}
            );
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_PARTITION_HPP

/* partition.hpp
nbRHikapPFODi0sdkYfDpT7Fi3gvp8O2YXHB6qGSmuIWBrIkYiGZtvu5GmMa/YXzOievOjuUpaC76aNCnRi8NO6jbIa672U3xdfHCUpYYytyNXjOrm8f7Lr2rDO90W05r9tCZsZnyDN3pJOcvhPrFSibyDZto7uhNvE8Z4Hm0bvF+jdYfNtTnNftcaNv6nZo0dnt3Ye4cymuk7g2z/DyeeniMTdtmUGugsEwaGJcSGeVwHFTKCZV0k9scTrTBXSGD6cYPcBRj2syLds7hAsj9nb3AsRWLPfypJzEoec8zTB799Jyr+blbtNCzFW5LsWDY9UkPyf8tIRSs6+1v7NRG8+JZwUv2wkti0HaMhsL336UgaKYQL43nObcJhtqaGIKcbi5vRMDGe/HNn8yabNTouVOobi1HyLDXzPet9f8e1JYI/QmuXXVuDecn8fbOdhbf9AmxU94OfyxHK6zfwXyULt40QNS3oNZbBCKi8ri9qyFsqN1/9ojDjzR0j7hut7U8Q2pDkM17hXIJB64vezsIrZMHM/zJLF7EPlnyjuZ5uFfYLvGPZ/lAZ+63Dxs4T7tjVcJd/kO3/K4y4PuPY7/pgsWuX8OdnSGKyy+RXFgPLaVhx/G2os8inm+uxGHN7rY7+dRfBzMVYbX+7qvxXSPo7u1445o8CaM+iRGjcfRJZ5fHvN6F7Zid2ODcGO/EdIjYjiSKO87IY/QwlneVb8Z8tCNNbets/Zf8osxD/xYnJsfRH4OH5Zh4v4spj981yHf7vE2/Cbm7R+c2nrwIWxEGI72d6c+7e1DoAPxEhuPZ/l8fQ+Yv+Dp3reS+L7kyz6vL02vga8MGWmq8+0sL/Sb6jzlsbc3ztlKsb+J9tKPj9jYUO48xMcZsIRj/TjKWweM9foNI272FZeQHjGF/dbpodNDXIr1yHvvjsDhpTXq34mo3j99L8bt8SoWdHaK8bI0YkojPpD3VfDyVnzdG6M1TmvugrFsQBS/ZZx7nz0Ljj+um/FIRbEsln8TlV+Mb8Oiy2RxDD5M5XkcmrE85tZ2LPfJJAYOD1azmcTn2PvMEbFqqM0E7pzFMfp8Uj/eTKksZO/dh3uQ+NiGb50lVs2au3+yOFe/o3JbOwHom9byOZ87Is4GZNBYxwnKT2KArHmNA8OkVkmcgVER7yUmnDGxrprKJPnbMX+gfHpIcCNA+9490nweF4BiljyQyhwV52PC2j61UI5Ll0trMX7Ciz9zRLn4TYC4zr5hEWl2juIdX/39myhR0bp5NB9nX/4hE778Ql5PY/Kqz1FsjdAoiq3xqEj/eqKPwAHT930z570YE2M/zsuvUzke8wcn5t5+nDMUE+XbR5bFhrruZWbaw75P5ZxVFkX9ofyL8hgPYbpgW6L8S8d8JGLvDSWm+XJF5LM16ifvwYP8EXEQ23p1XocvFza+EA0plrs44eH7l6E1f29Ze0gfI80QHv4My/7w4XvOuiS2CfjYhJ8eZ8TG5iFc5DDW+RTrHjLQXdfsKLWsoCVQMAq4sd31nwg3Qtxe3H6J/BCvnMac7/o2l3ku2O7Dsc53Sac1uwuoUvdVVeeiv3sLxXXQW2wcjcd1TCwR9vNVUh2SaXRZDQX8+f8pB+7hnty7L77GcXEdcIkxvRK+cOjEEH3xBK87t6KV2gFODOJBEIKwP/NaqT7C6U5cjKk/H036U4gcmsqiUu2/ix3uxhzsMvLdTNpYiL4tqq5tFLXxn2CHE77PVdN+attqg0veAnj4+ME5ePhiTPE5r1pnVda2KX7o4lkzxzupEj65sFaruuzzOeY3ASEwmfy+nPY2rSoGUzkEtNv1fgx8aYpdjrL8rpQXXdNLAaa3ewiVZrg=
*/