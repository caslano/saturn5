/*!
@file
Defines concepts from the Standard library.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_CONCEPTS_HPP
#define BOOST_HANA_DETAIL_CONCEPTS_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/detail/std_common_type.hpp>
#include <boost/hana/detail/void_t.hpp>

#include <type_traits>


BOOST_HANA_NAMESPACE_BEGIN namespace detail {
    //! @cond
    //////////////////////////////////////////////////////////////////////////
    // EqualityComparable
    //////////////////////////////////////////////////////////////////////////
    template <typename T, typename U = T, typename = void>
    struct EqualityComparable : std::false_type { };

    template <typename T>
    struct EqualityComparable<T, T, detail::void_t<
        decltype(static_cast<T&&>(*(T*)0) == static_cast<T&&>(*(T*)0) ? 0:0),
        decltype(static_cast<T&&>(*(T*)0) != static_cast<T&&>(*(T*)0) ? 0:0)
    >> : std::true_type { };

    template <typename T, typename U>
    struct EqualityComparable<T, U, typename std::enable_if<
        !std::is_same<T, U>::value, detail::void_t<
            decltype(static_cast<T&&>(*(T*)0) == static_cast<U&&>(*(U*)0) ? 0:0),
            decltype(static_cast<U&&>(*(U*)0) == static_cast<T&&>(*(T*)0) ? 0:0),
            decltype(static_cast<T&&>(*(T*)0) != static_cast<U&&>(*(U*)0) ? 0:0),
            decltype(static_cast<U&&>(*(U*)0) != static_cast<T&&>(*(T*)0) ? 0:0),
            typename detail::std_common_type<T, U>::type
    >>::type> : std::integral_constant<bool,
        EqualityComparable<T>::value &&
        EqualityComparable<U>::value &&
        EqualityComparable<typename detail::std_common_type<T, U>::type>::value
    > { };


    //////////////////////////////////////////////////////////////////////////
    // LessThanComparable
    //////////////////////////////////////////////////////////////////////////
    template <typename T, typename U = T, typename = void>
    struct LessThanComparable : std::false_type { };

    template <typename T>
    struct LessThanComparable<T, T, detail::void_t<
        decltype(static_cast<T&&>(*(T*)0) < static_cast<T&&>(*(T*)0) ? 0:0)
    >> : std::true_type { };

    template <typename T, typename U>
    struct LessThanComparable<T, U, std::enable_if_t<
        !std::is_same<T, U>::value,
        detail::void_t<
            decltype(static_cast<T&&>(*(T*)0) < static_cast<U&&>(*(U*)0) ? 0:0),
            decltype(static_cast<U&&>(*(U*)0) < static_cast<T&&>(*(T*)0) ? 0:0),
            typename detail::std_common_type<T, U>::type
        >
    >>
        : std::integral_constant<bool,
            LessThanComparable<T>::value &&
            LessThanComparable<U>::value &&
            LessThanComparable<typename detail::std_common_type<T, U>::type>::value
        >
    { };
    //! @endcond
} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_CONCEPTS_HPP

/* concepts.hpp
fN/pxrJi3crWurj2hbFJYl3KZq42eAlbTzGvsq+iN/exfa3WW3Vh3+UeG2p7V8yrbMSej1VtzW6SeVf25/fLLm6sx7Erzi73MjZYrFvZrjOmlWxdxPR6X+180gHGko591PuVxYylxXzKHhqx1mHGck7cBSMv2cr2oFiXsvseOmWOsalincq+nrWyzVlR6/VbuM8fzhtlrC5m6rmaPPZ+4fQ1bc0m/Hf27oU9ctyTZ9s+EzM5V5fHzCT/5bbPVFx/eZzy0GW2l4aI+ZTNq5/zne0lsS5lxx2wydG2ZmJeZVtsM3ZD22cqbo2Fz60T529tbKJjySNvWt9YScyrbMqm335ra+bEzdg0crKxGWKmZgv7pm+odoYxz83/nX2APH57wMW3GusW8yqrffr4WsY2EOtSlr1w5bSxsJhP2S7nDPjFWMzJ+dobw+38JRy7/I2LbV1STs5Zo0+8zdZTrEfZMjMGLmPsYcfuGTX/VGM1Z701P77bznvDqcsvv4/tZ/vsFpk/Zaet/diZdjbFdFz6tl2/sXUR0zWbP7R5u+0zx4YutdYsWxcxc/aFZ4lOOnAD22diZo7WlsenX5ydMDZOrEvZkC+3+tBYXsyrzP7sTN6KjhWW/s7upSzmUzbhk8ooW0/Hvmj1OdxY08m55sqH3GN78NZF7Ynb37V95hXTZ5h8/f3v2Vo7duG219m+Djk59+x861BjEW3O5/6Yk3NMrz4/23l3bN+dz9rL3oPO6bxuzTpxN044p9POu5i+vz2ePulNew+OHfjFTpsZm+rkvNOzYdRYVUzfwyaTxz1o+9qJmzd48hxjC5wz+FZdxWOsM79o3I4z5q5ozC+m1/vmhF+67T2I6Zzd5z9j6xJx4kZvHbGzEhfTZ+/Z+8q6vQcn7pZrzlhgbKxjH50xxNZlgrOXxOCrtjM2ybGfHjtrpK21c/Yzb3zrQFtrsQ5lx39x7fF2Hpy9tB456Fk7D07OPg+9ZGvW67ZF97L8gJ75xrocO7W8TF87D2I65zk7/3KtvQcxvc/zOzZY1VhYrFvXZdYBxxob5uTcYcQ2LxlLOnvZvPepm9t5cOylK3stbufBWe/dpZYM23sQk+c4+29Fn/HZUR/ZWjt26d1b2ZzzxLqUbd9rh6HGOm5f1K4eMruPsW7HLpy82hBjQcc++qXv7sYGi3mV2Z8ly9sQMZ+yges/NN/2rmNTVvrqIdu7znrXdj9znLGcs96tozM3GSs4cd+fslIv27uOTdxrr09sPZ29bHP3LwONNRZdT/0cSPpYxa2zcN57PeEz5r1D1lP2efmbN21/igWUPX1M9BxjezlxT14y7QJjcTGvshOe717J9qCY3suMr6dljGUWjVN/1kHqKdat7PIDvvvva1hnL+9fMH26sYpj1/xwp73bGc56uRuPtrM524k7KLlK2phn4qJxa16yT4+tp5iOe+Sqn1+19XTizjzruWnGBon5la17xwsV259Ozn16TRluLCGm67n2uS89ZWdarFPZmEsnHGVsnBN3Z/SJB41NdNb7KjDLzkrJsRGf9mxhbLpzvpfPXmJtW2vHvMe8cZSttWNXvXRRztgCx67dqft7Y513Lmq/zR+yorFuMb3Pyd+edpixoBNn//yLvIWVBRb20uX32vWiYl3Ktr1tv8nGhjuW/f68b4ylxHzKds1+voexrLPe5t8ea/sz7+RMl+YNtj3v2Mf3num3Pe/Ye4cnLrX34Kz305CuufYeHBu98dy37D2I9ah/TyO81Po3G/PfJespmzzsp2G2rx07ZsNcl7GImFfZ1nfMudpYzIkb/sluA42d6MQdk0h/bmy0WLeyzvNPnGksJ2buYT15bJz/yivGiio=
*/