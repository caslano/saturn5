
// Copyright 2005-2009 Daniel James.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  Based on Peter Dimov's proposal
//  http://www.open-std.org/JTC1/SC22/WG21/docs/papers/2005/n1756.pdf
//  issue 6.18.

// This implements the extensions to the standard.
// It's undocumented, so you shouldn't use it....

#if !defined(BOOST_FUNCTIONAL_HASH_EXTENSIONS_HPP)
#define BOOST_FUNCTIONAL_HASH_EXTENSIONS_HPP

#include <boost/config.hpp>
#if defined(BOOST_HAS_PRAGMA_ONCE)
#pragma once
#endif

#include <boost/container_hash/hash.hpp>
#include <boost/detail/container_fwd.hpp>
#include <boost/core/enable_if.hpp>
#include <boost/static_assert.hpp>

#if !defined(BOOST_NO_CXX11_HDR_ARRAY)
#   include <array>
#endif

#if !defined(BOOST_NO_CXX11_HDR_TUPLE)
#   include <tuple>
#endif

#if !defined(BOOST_NO_CXX11_HDR_MEMORY)
#   include <memory>
#endif

#if defined(BOOST_NO_FUNCTION_TEMPLATE_ORDERING)
#include <boost/type_traits/is_array.hpp>
#endif

namespace boost
{
    template <class A, class B>
    std::size_t hash_value(std::pair<A, B> const&);
    template <class T, class A>
    std::size_t hash_value(std::vector<T, A> const&);
    template <class T, class A>
    std::size_t hash_value(std::list<T, A> const& v);
    template <class T, class A>
    std::size_t hash_value(std::deque<T, A> const& v);
    template <class K, class C, class A>
    std::size_t hash_value(std::set<K, C, A> const& v);
    template <class K, class C, class A>
    std::size_t hash_value(std::multiset<K, C, A> const& v);
    template <class K, class T, class C, class A>
    std::size_t hash_value(std::map<K, T, C, A> const& v);
    template <class K, class T, class C, class A>
    std::size_t hash_value(std::multimap<K, T, C, A> const& v);

    template <class T>
    std::size_t hash_value(std::complex<T> const&);

    template <class A, class B>
    std::size_t hash_value(std::pair<A, B> const& v)
    {
        std::size_t seed = 0;
        boost::hash_combine(seed, v.first);
        boost::hash_combine(seed, v.second);
        return seed;
    }

    template <class T, class A>
    std::size_t hash_value(std::vector<T, A> const& v)
    {
        return boost::hash_range(v.begin(), v.end());
    }

    template <class T, class A>
    std::size_t hash_value(std::list<T, A> const& v)
    {
        return boost::hash_range(v.begin(), v.end());
    }

    template <class T, class A>
    std::size_t hash_value(std::deque<T, A> const& v)
    {
        return boost::hash_range(v.begin(), v.end());
    }

    template <class K, class C, class A>
    std::size_t hash_value(std::set<K, C, A> const& v)
    {
        return boost::hash_range(v.begin(), v.end());
    }

    template <class K, class C, class A>
    std::size_t hash_value(std::multiset<K, C, A> const& v)
    {
        return boost::hash_range(v.begin(), v.end());
    }

    template <class K, class T, class C, class A>
    std::size_t hash_value(std::map<K, T, C, A> const& v)
    {
        return boost::hash_range(v.begin(), v.end());
    }

    template <class K, class T, class C, class A>
    std::size_t hash_value(std::multimap<K, T, C, A> const& v)
    {
        return boost::hash_range(v.begin(), v.end());
    }

    template <class T>
    std::size_t hash_value(std::complex<T> const& v)
    {
        boost::hash<T> hasher;
        std::size_t seed = hasher(v.imag());
        seed ^= hasher(v.real()) + (seed<<6) + (seed>>2);
        return seed;
    }

#if !defined(BOOST_NO_CXX11_HDR_ARRAY)
    template <class T, std::size_t N>
    std::size_t hash_value(std::array<T, N> const& v)
    {
        return boost::hash_range(v.begin(), v.end());
    }
#endif

#if !defined(BOOST_NO_CXX11_HDR_TUPLE)
    namespace hash_detail {
        template <std::size_t I, typename T>
        inline typename boost::enable_if_c<(I == std::tuple_size<T>::value),
                void>::type
            hash_combine_tuple(std::size_t&, T const&)
        {
        }

        template <std::size_t I, typename T>
        inline typename boost::enable_if_c<(I < std::tuple_size<T>::value),
                void>::type
            hash_combine_tuple(std::size_t& seed, T const& v)
        {
            boost::hash_combine(seed, std::get<I>(v));
            boost::hash_detail::hash_combine_tuple<I + 1>(seed, v);
        }

        template <typename T>
        inline std::size_t hash_tuple(T const& v)
        {
            std::size_t seed = 0;
            boost::hash_detail::hash_combine_tuple<0>(seed, v);
            return seed;
        }
    }

#if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)
    template <typename... T>
    inline std::size_t hash_value(std::tuple<T...> const& v)
    {
        return boost::hash_detail::hash_tuple(v);
    }
#else

    inline std::size_t hash_value(std::tuple<> const& v)
    {
        return boost::hash_detail::hash_tuple(v);
    }

    template<typename A0>
    inline std::size_t hash_value(std::tuple<A0> const& v)
    {
        return boost::hash_detail::hash_tuple(v);
    }

    template<typename A0, typename A1>
    inline std::size_t hash_value(std::tuple<A0, A1> const& v)
    {
        return boost::hash_detail::hash_tuple(v);
    }

    template<typename A0, typename A1, typename A2>
    inline std::size_t hash_value(std::tuple<A0, A1, A2> const& v)
    {
        return boost::hash_detail::hash_tuple(v);
    }

    template<typename A0, typename A1, typename A2, typename A3>
    inline std::size_t hash_value(std::tuple<A0, A1, A2, A3> const& v)
    {
        return boost::hash_detail::hash_tuple(v);
    }

    template<typename A0, typename A1, typename A2, typename A3, typename A4>
    inline std::size_t hash_value(std::tuple<A0, A1, A2, A3, A4> const& v)
    {
        return boost::hash_detail::hash_tuple(v);
    }

    template<typename A0, typename A1, typename A2, typename A3, typename A4, typename A5>
    inline std::size_t hash_value(std::tuple<A0, A1, A2, A3, A4, A5> const& v)
    {
        return boost::hash_detail::hash_tuple(v);
    }

    template<typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
    inline std::size_t hash_value(std::tuple<A0, A1, A2, A3, A4, A5, A6> const& v)
    {
        return boost::hash_detail::hash_tuple(v);
    }

    template<typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
    inline std::size_t hash_value(std::tuple<A0, A1, A2, A3, A4, A5, A6, A7> const& v)
    {
        return boost::hash_detail::hash_tuple(v);
    }

    template<typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8>
    inline std::size_t hash_value(std::tuple<A0, A1, A2, A3, A4, A5, A6, A7, A8> const& v)
    {
        return boost::hash_detail::hash_tuple(v);
    }

    template<typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9>
    inline std::size_t hash_value(std::tuple<A0, A1, A2, A3, A4, A5, A6, A7, A8, A9> const& v)
    {
        return boost::hash_detail::hash_tuple(v);
    }

#endif

#endif

#if !defined(BOOST_NO_CXX11_SMART_PTR)
    template <typename T>
    inline std::size_t hash_value(std::shared_ptr<T> const& x) {
        return boost::hash_value(x.get());
    }

    template <typename T, typename Deleter>
    inline std::size_t hash_value(std::unique_ptr<T, Deleter> const& x) {
        return boost::hash_value(x.get());
    }
#endif

    //
    // call_hash_impl
    //

    // On compilers without function template ordering, this deals with arrays.

#if defined(BOOST_NO_FUNCTION_TEMPLATE_ORDERING)
    namespace hash_detail
    {
        template <bool IsArray>
        struct call_hash_impl
        {
            template <class T>
            struct inner
            {
                static std::size_t call(T const& v)
                {
                    using namespace boost;
                    return hash_value(v);
                }
            };
        };

        template <>
        struct call_hash_impl<true>
        {
            template <class Array>
            struct inner
            {
                static std::size_t call(Array const& v)
                {
                    const int size = sizeof(v) / sizeof(*v);
                    return boost::hash_range(v, v + size);
                }
            };
        };

        template <class T>
        struct call_hash
            : public call_hash_impl<boost::is_array<T>::value>
                ::BOOST_NESTED_TEMPLATE inner<T>
        {
        };
    }
#endif // BOOST_NO_FUNCTION_TEMPLATE_ORDERING

    //
    // boost::hash
    //


#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

    template <class T> struct hash
        : boost::hash_detail::hash_base<T>
    {
#if !defined(BOOST_NO_FUNCTION_TEMPLATE_ORDERING)
        std::size_t operator()(T const& val) const
        {
            return hash_value(val);
        }
#else
        std::size_t operator()(T const& val) const
        {
            return hash_detail::call_hash<T>::call(val);
        }
#endif
    };

#if BOOST_WORKAROUND(__DMC__, <= 0x848)
    template <class T, unsigned int n> struct hash<T[n]>
        : boost::hash_detail::hash_base<T[n]>
    {
        std::size_t operator()(const T* val) const
        {
            return boost::hash_range(val, val+n);
        }
    };
#endif

#else // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

    // On compilers without partial specialization, boost::hash<T>
    // has already been declared to deal with pointers, so just
    // need to supply the non-pointer version of hash_impl.

    namespace hash_detail
    {
        template <bool IsPointer>
        struct hash_impl;

        template <>
        struct hash_impl<false>
        {
            template <class T>
            struct inner
                : boost::hash_detail::hash_base<T>
            {
#if !defined(BOOST_NO_FUNCTION_TEMPLATE_ORDERING)
                std::size_t operator()(T const& val) const
                {
                    return hash_value(val);
                }
#else
                std::size_t operator()(T const& val) const
                {
                    return hash_detail::call_hash<T>::call(val);
                }
#endif
            };
        };
    }
#endif  // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
}

#endif

/* extensions.hpp
lccySZu4VoO/7bLxuRN9c1/itiSMBZdVn49X5aF3g6vrB/K9a1+2hdoK8EPsJdCl2ka2stOF6qW5zbxuONZ6beo7v8zeJzUSL4XzrTr8d5aJX2OQ5NW0fqviXL/M+GPUAGP3lPdFR+FtOMF4c0yADd9fOh4DeES2F1oXumFpyjFoHwHSRe9JOHhp/R6vTZaOHj+0RN4HvZaKvn9DyH1VNy8oR3oRPdlR5bHRUj7tS0vy/Gts7jbnUrKxke5d6JcuGcYjfu+mdJ9NYcmxMXmNJbG+zfqxOJy/Fh2LNWsCLElbUNvB60uYxcWI/VaR95DnKk0+/lFNNO4bO+6/aonw/TznBfWLfYeKwedUaH9BZYmx49WOxdRzYDCfQmzVt/yyxI/y7Q2WQHreB6IMPJ9UfQ11i3yGF3Di9460LJHuurJu/uejxc3W4JX4DvLbYyMWyX/TCH78+n/b1PSxa5OIvZ4lNsUU4KGNK1hGjWFNY+o42Zrlj812upNcry1m5m9jdE8J+xJLbBubO4ulZ3Ob5zaeXRT7F7O9/I9qxsUXLhq1B5Gf9Rx9zvPAosg//qxnkInrTr/D31heia2s3yDdid83i3B8vfwoz+Ig13FTxr7L/4FFovdD0xj8rEWi+zvkteciJOfY+aslI2lnPBvt6Hn1cw8/LOzb4q0p6GfIK/xciUEl91H32aPvzWqwnxJleWhhxKP536i9lByT+7fdeSA0zlf7r1MXjh9LJhmbhOHuPUm4y1vgJp1nRNxfFjKLnSr20fPK14tIV+Tz2BjciVs3On2hiX22ei8LvKh12baFzPcd7z2VzkKW+8WPC8r2WdngqpiPLIh+JbeXbf2QP56SQNfzBG2OzzXuvqD58+cSvMdm0+EF9lzQfI+XBFPnP98vMH42VbEeWIBybvQ92T6IqP6R+8gJC5g9Z5Bm36iz6y4L2Mfro+c11/fr+Ulfwkqm92ILyHRX9b53fpTffs1fgq2z+zHzj58/a/fxTjDeQuOIp2J9Od/4xnidfnfNZ6/fdvPR+3zj+zQd9tEJsM8T2BZjP8X6BRnm0fPaxfy9fV1BZzN8xP5qXpSDcM37G5R5MOQ9/8gPed0zL5//Q9zoZ1aaWuJzUspHd2By7x6Six49L49rNL6SzdfxPVtchoXH4oPs5nYzxdbh3tIq3/8txeQ5Cc9HhlsDHxWuGaaBvfkIttn8eNvU+Dl/zqMFeH8/p9JXJXimQIL97jzp4H4/pxz72knELs+Trs2pjO4Z1rXmQTrKrxFX8xyrcI/AzCnbzs+Dk51F9PLcKIt5bMC2hjLtbREjVOyLJhG7zxI7CWb73LIxTOO5SSpv/z6GP+dCeex0TsPeT84lxz0rob3PmMve3gou0JvnGXuN4sr3Syu2hrZup/vSc01eXd8/px12Eszj5pTVdcP26ei8/ZzyHOuslOy9oCV2EswvWsxyK2pPDV3T0fnOlon3scNa7H0sCe6WQlzf7jJc8h/ERyxVhtfm0I1XVD9Ots9Lxbx8Dnu9+TklREs5HvIbnCP+jJI0/LRzDrmPJm2b/8xOmGbjrRHclNvnc7NPfEw6b3Z7f0mCmxXiphUXVkqAm0Yd/zqbXQxuxGEmu+H7klQZTp0N+Zo/Lytdz6Scbo/ZmK0j8zryKzWvC1/zIxsuM1v0uh/fx0a4qq0QB3Xg6wa/BzrxPSM0t8b36j05FW3jy/nTyH2z91+e0Yw8+X5Teu8l8SZZaT8h/ha+p/C5JuTjy/JTk3+O23FTfDneEp7l9vYs8mcYrjs5k5kDrg3hOgiuBU8BHidCLIdrygmZzFpwOXB5x2cy75zEywI+/gbXC3CflyX62eEe0uH39qf4/yY=
*/