/*!
@file
Defines `boost::hana::drop_while`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DROP_WHILE_HPP
#define BOOST_HANA_DROP_WHILE_HPP

#include <boost/hana/fwd/drop_while.hpp>

#include <boost/hana/concept/foldable.hpp>
#include <boost/hana/concept/iterable.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/detail/first_unsatisfied_index.hpp>
#include <boost/hana/drop_front.hpp>
#include <boost/hana/eval_if.hpp>
#include <boost/hana/front.hpp>
#include <boost/hana/is_empty.hpp>
#include <boost/hana/lazy.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename Pred>
    constexpr auto drop_while_t::operator()(Xs&& xs, Pred&& pred) const {
        using It = typename hana::tag_of<Xs>::type;
        using DropWhile = BOOST_HANA_DISPATCH_IF(drop_while_impl<It>,
            hana::Iterable<It>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Iterable<It>::value,
        "hana::drop_while(xs, pred) requires 'xs' to be an Iterable");
    #endif

        return DropWhile::apply(static_cast<Xs&&>(xs), static_cast<Pred&&>(pred));
    }
    //! @endcond

    namespace iterable_detail {
        struct drop_while_helper {
            struct next {
                template <typename Xs, typename Pred>
                constexpr decltype(auto) operator()(Xs&& xs, Pred&& pred) const {
                    return hana::drop_while(
                        hana::drop_front(static_cast<Xs&&>(xs)),
                        static_cast<Pred&&>(pred)
                    );
                }
            };

            template <typename Xs, typename Pred>
            constexpr decltype(auto) operator()(Xs&& xs, Pred&& pred) const {
                return hana::eval_if(pred(hana::front(xs)),
                    hana::make_lazy(next{})(xs, pred),
                    hana::make_lazy(xs)
                );
            }
        };
    }

    template <typename It, bool condition>
    struct drop_while_impl<It, when<condition>> : default_ {
        template <typename Xs, typename Pred>
        static constexpr auto apply(Xs&& xs, Pred&& pred) {
            return hana::eval_if(hana::is_empty(xs),
                hana::make_lazy(xs),
                hana::make_lazy(iterable_detail::drop_while_helper{})(
                                            xs, static_cast<Pred&&>(pred))
            );
        }
    };

    template <typename S>
    struct drop_while_impl<S, when<hana::Foldable<S>::value>> {
        template <typename Xs, typename Pred>
        static constexpr auto apply(Xs&& xs, Pred&&) {
            using FirstUnsatisfied = decltype(
                hana::unpack(static_cast<Xs&&>(xs),
                             detail::first_unsatisfied_index<Pred&&>{})
            );
            return hana::drop_front(static_cast<Xs&&>(xs),
                                    FirstUnsatisfied{});
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DROP_WHILE_HPP

/* drop_while.hpp
6c8uk/2/6s3z0If61s9+cr58+P360zzXihm/NFMvGfcc7OO4oul/NvK8oN9on0k7Tv0O5P38wDD66zyXc+hXLDLwuRHtS0gpz6MX6K91CDHBLX+G+jGD7c9m/LVdll/E885BvTlG/bCz3stp7L+V8d8W7scs7gva2T3Md3Uu7U4413eZ3I9LeB6fyKMe1AiZj+fftmjGkcVy3i8e4X0i6nkJ7VSqep+c+/n057mO32QcpcYFAzJfzXuMHxOFrJ/tneRztX0c77kC3lcPpf6UMC6h33z4bUXK+ZzBznkOVJ//mNkv2kuF8csx7pPTTZxHF+Ni9iM2g/3gPtnCeney37s6aO8Yj9lyGa8+w+8+1CMh0zP0109lSHkInzO5mJ7aQ7sZR39rHeMUmzfrZ7w2l/Eu/fz5jA/PsdwuO59DnuR9+IdZH/27PVm0ow7qbxbL0T85UMZ4g3qvqPdzuU+OFNB/5n3bAbvMd2I216GQz51oBwN5PuyYxDixgf79etot1c9W799n+jCOof1h/L6N/p+N+/s0919sIdfpT+zHG7wPcJH6tZb9Zbw3w5f+Tjmfh5fI9LKF5+56qee7GAdNKaGfS33xc7Ffj9GfWCXjzi0mPnfN53mzjuUKGQ8wvjyRw+d2s3if4C3G7dynN7m/zOr4suW5k+WivdxNf4T6ucTC59fcf4FMS6gnM7hOU9jeNvW59zrqlZV+orpe66lXGTKu8cvn/a8a2pE32c5axi3cv+cpX5XC7+9QX9j+GdqdVbwfu6RYlndF0W910N5t5/NJtnOrgnpLfTz/O+oJ9ePcAtqhp+kXUR8UzssJrvcdnps+tPdXcxgnsL4b11k//TD7RNZL+3dyJePDbFkuh3Z8Sx7jne8z/qQeHmO5s9yHgf3yuXbkRvrFcfQT6HemPkJ9Y39jv8l4vpp+Ju33dMZt22gHT3L+ozk+G/XNTr/DRbt7i/bWTD1IsPN5A/1SVz73XQHvT66n3ea5WSHot6jPJ1ayHNcpkuN/bT/tUAafL6j30dLpr5YzPi/1oZ2gX0k7ePh96u2jXI9KIfzdKeOiO9wnc96m38Rz0WETYum4/0e/mX7HEdrzG4wnrufxvpR6Xn2X+zCMz1me4X7op/1kquQw/rzA+Vgh/etdYbwfyf5M+T39cK6vg8+pIr9Cv1u9D93Hfc96Dm+nnfiA8RTr2aH6Hev5PJf22o/nuYP1HqF9DnmPcdos2nv2Q1H98XzGg4/RPnJ/RvP6zGxpRysa2U/1vYf5PAfU5/+83+Fn5fxS36LXcv/N5ng5b8foN13+vWp3hZQ7uS7shx/tQzTtot3GuJV+vCOP/ZlDv/E8+xNKO32d8UIC15HtvWaX+08xMC7jPp/m4v6ivzKD53EO21vO9x7MiULm4/5Kzaf+O6hvjFt8mG+rOj+MG07zfDrL8YQU0o951SDlXH8H44glk7hvfBkXlEp/7QTXO/VR2l+u8xzal0v5jFsL6L89osiUej9Af/gI/ecj1PfrmdwPdfI9mlVsd1eCkPrHclfL+d4X9Xc6z9ESxh8zuT9vUQ9vqX5IIcfxGNeP58WdjfRzGL+9xv5u576MZj0OjvfsJa6z+p5SrryPeuMDzkOlrP/IK4zDJ9IfCKU9iuC6f53+GO3t4dXS3q2ifM8pnmMrqR9hjE94ftryuJ7s71X1vSbqWwL1MmsN/X8H7W8/47W19BdVP4zrqDA+WWKT8oqdfJ5CvZ6jME7PkfntjJNuDjDescrnjlf5HkFOv5Dj4jly4k/sH9dlhhon0c85U8bnBZT78dxN4HrfSKJdfpX9YPntBtohnt8l1KudtK9H1Pu69AsOv0X92Sjf08nift4=
*/