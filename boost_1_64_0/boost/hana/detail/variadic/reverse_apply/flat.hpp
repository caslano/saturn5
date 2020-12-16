/*!
@file
Defines `boost::hana::detail::variadic::reverse_apply_flat`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_VARIADIC_REVERSE_APPLY_FLAT_HPP
#define BOOST_HANA_DETAIL_VARIADIC_REVERSE_APPLY_FLAT_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/detail/variadic/at.hpp>

#include <utility>


BOOST_HANA_NAMESPACE_BEGIN namespace detail { namespace variadic {
    template <int ...i, typename F, typename ...X>
    constexpr decltype(auto)
    reverse_apply_flat_helper(std::integer_sequence<int, i...>, F&& f, X&& ...x)
    {
        return static_cast<F&&>(f)(
            detail::variadic::at<sizeof...(x) - i - 1>(
                static_cast<X&&>(x)...
            )...
        );
    }

    template <typename F, typename ...X>
    constexpr decltype(auto) reverse_apply_flat(F&& f, X&& ...x) {
        return reverse_apply_flat_helper(
            std::make_integer_sequence<int, sizeof...(x)>{},
            static_cast<F&&>(f),
            static_cast<X&&>(x)...
        );
    }
}} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_VARIADIC_REVERSE_APPLY_FLAT_HPP

/* flat.hpp
z2fzJMudS3N/AfVFzVNltPpdg1eel/yWPoNEKxfR74vp9yVke6lj9LEym9UlEvRPoTEar/2G3LbpZrnLlXIJz8jbGKoDjfAzNndwHhl0vixpj/qi0N6toL0eGaBBwKVMvxS/3TTnE3/dmEeJy6ivhzuFDfgVgKcBvrjZsu1q4m+mnc5wiJZ0eVmSdHllArqcRLL8Kk6XSeqom5DnZhwH+a2dctPyNYzfXaPwu+sYzcq8a4n2rmf8DnCb5m9UaP6mBN/fTN975TV45nnrpTcQP7qFZPCtRNe3qe160CvgNs2vyubl7PF55t2s8MQ7qQ932TyRyit0eYqHvnk7/ranhfjhHcQPCWjwwrs9eOEdSdLcPZ3Q3DaguXs5zSVJNxWboDl5zBFAhI1AxHwTxqpGzeD7pX8wOvyHQof3s/mUefcRrTzA6BBwmw4fUujw4QTfP0LfK3mecvdBmudHicYeU+v0oDHAbRr7ZzYvZ/fdM+8RhcaepLafsmmMyis0diXR2DVM7j6Ovz0n5RuT3p6w6E0tQHuYpz1o74kkae+ZBLRXQXL4WU57f5B+oox+ogr9PM/mSuatpvl/gdFPlNHPSwr9vJzg+1foeyWPZLdXnjcfe5Hm91XiY68Rjb1O7cpvo+o+Sa3bg/6ijP7+lc3L2WP3zHtFob+3qX9rbPqj8knsqd/A32xjaexB3kxiDyJp8y2iTetjSY/veNDjW0nS47ubkL9rOT0muSdO9F7LDLpFgz8MnUW+W2/ZxIW3TZxs6PAFk5d9g2EKcGz6frwv6RtaSIjZ4AeqZ9VkVx/sYVefSb7TH3ja0WU7/BPFiu5dIPEbLFugXrkmP2Jr8mNmp/8Ef9Mw7HPQTw2AwSEqmzxqhU+MfW/9M4aDlI37ah7TUy89soz+8X4MZP34Iol+zKN+fMn6MVgM9W7N62gwuaIUb4D74i9oDCNoF/Np4GnQ3iIjPZxs7+tY/3p50HSq5JCiypifr63zW0/dwD5gNVaRnaLztW/ZHupbNuffK3z4B8aHZbnviA9voH5SXTbP+ymblRO8HOpm+5Vsqu8XhYfKvByWx+qgfY7Xd0ofu7AHsvGi7oHsDHUPRG0ofPhD2gN9A7jc7/yYzWaA9kA/cz5KsF8Baw62Ngfk5TmC/cbLTRYbwTIZrD6EAOQhM/070jDRm7yX0vHg4oAD6wcGRHsup3PG/koD3N5fgW/rVE7l25LWeoFv+yhf0uDATmhtenK8Kqn1L2m121CHVlOHUnyKTZ6bcp6t8H27HSevu1Fvi7sHaPNg8iFKQ771L2MLnkVL/tYr3X4TxI6RAJo3YpBHG6UXDkKPNVbY93m2oXnjORiHHaurJ+tr+mbQ/HB3H2bJLTm9EWq0GyuRz7c77W3L29sMO4PFdwoUn6feqNfTd6kL/iWSZvoQzVjt9EWat9MPae7zfPiOSGNeHstyYkheYN9fw5wWBgpL962p3dfyHybYzGp451TW1Jih1CmOGeVVVlfXVeGEsBbxHex38M08vEtYUSa/LMw33v6jWGf8u+KiQH65LGDkdTPzysrLi6fllwvDrzeV/HoHDKUeGm6h5CZo+PWqUMc28Rj5c/H7g2n8/iCl7buouvuNNfzDOkl8LxdDyy+SYVJLyqbhVxF5L1WTy3HdJkuhq7/pbL0rsaLV+Hx2PE4zxhMFP0B5gm9jxnYiOLu7T2+dGI6oMpxM3MlL53k1bn+MDFGIgC7y7jrFwyoKNQXbI22yV3hJhsV6LwqZ8ZPkAjJeWYDjYai1ORZpdL1JZperjbWhSRT2LDdClKOKKtwzCC8xj/udvBzrvdj8iHXt30CalT/BulNvPnLnWX+e9TZEflOTjCg=
*/