
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
XHzNMihvQVvKVf9ugWgjGjuPm06JpLOTe48NIHgm4DTNykJJpnrKCiGh2S5oyPsaQDnOLhwHuAsT91TG2uXDeas+5+b/vrXjIIVHyM/M2Z381vq+qZVpS4bJ5yr449L6h8rNVsDY7yXjTJtJ1mt+wOc9UJ+LFQgzgH6ij71vwhMUwoPFs7wAJI/mvXV5HqMfUMy/b27CwmmdPhnswY6KnjXHwGF6R/NQjRv+ZkXyM1RIeBkZzYncwXCLs8RF+uVm5NMLrYA/sBcynwl2FwZ9f/Bg4g8g9E1tHkIdnBN2DwQKEklaPdhs+UUK+UOrK6Q9AVgYnkR/P3Po+BoWxJlZiTVezUerv0mkmwXBzMZ2PzcPhpRM4441bwVHX/hoQ0QxLiQdCUvkCG20DqBwSc3pPdxukP1T6AQLROmelOzZxaN3GKhvhp3TJ813kIbBhCAmcZUH52jBR1+/QoN/Xbm+ABox2C/eN+1WltLpxsZV26XIcg0/3WOwjlD+TVZytOg8DdbUgjY5CHN8bqy1hLKjC9Yr5bhwqr4HWHP3B7HPfYZYkpwVRc5WM/w2jP7BhrDD7X4EZFJ+SHm49wFSb0XYTAxc3BOzGk8qIEIIKBh1Fyc35CMgbFqFxlObijE0oi+2F6e2lFFwxThWk+nCPhiXNkn2+e/lz6k4ujWLG7n5YjGBImImD4+7EnTyLFMLUxLyvug8SuG3W5490C/RLdIqMp2DlwS9u2druNYO4wtZIRHc4bLnWSiubY3TOPtEgVBw3hkvMlv4ZdHu+x0XQb3zNAgpuD/v9kZkd6gAnXs7kme0ZTaQwKZdbL50YlfczPng5jkZ9yfrdMV4dovlP46zpXwnc6OvrYKRqvIB6Tw/mdD17/IU+cMWv28bhykHFWgyGJy5bw+lCDx/bzRrHD1JCEqyNJQ83l1qeLn3da3t3ALdZenCcze4UTKKj6bL8tx/fXm8M/Hx6TeuFzE2o/miKxRL80++1r2UBRGKHMlisyUSl1Qe9vAj8FmS3eTAPMn4Ke8E693kSaT+HPX+boZFiAPqIscK5PoG7oqUZp7HX370+fBI/GIMOVaif1VR0vAuCIaRt+QgRcy5pSHlUKTmaeChyp4DtqF4ASSufyB1IKutz6UOcQtHDiI5OV1tnT00hEdc8CmDnjhyppC61P8Y3PY8jUjN5/SY0ZA+HRViW8DPD2pcilPXEH4Po33J4mGcjlZpfucwe6qr8qovClaJX+uRu17fHk2PJ62P/2gg7Lgy7cgH/pMvAKiF6T0xq/w0EYRBpzKo8bt+WH0Wn1A7/J0ns+aHD+YU3sZXIn4R80qilYRGMxgbZzo096VJxk7lDKkNjARBlQix0j4RE7OzZcXww6OoeZ5PthJG9Tp6riOmPlspTaxhiWVG8DrTaXvg5ivbM8tALMrmAg/0xsWH5/gnrp0IPO9L6whCEL9NFE9juoi9OG15KxYJYwnuOG6tna2BS9InvkH+J7524Af34fRpBFB+u1Tnxiv7dsmfMSNhcrvcJW76hSGg7GgxSSlFdGkfu/ZnomuHkoLUVmazwjz0F/V0JjApHGbs/8apem9namA303t/8l36UmYpji3ZA5fmrfnvQ5wtWd5VeSTN7MmOIYk3L7sW5F7BRFOk8ieDRi15SjppSG/dBws2H0jxq7iUOCIlD5fHOy9+SXtMyocPC4BbNPQ8Z/VfEz0Jsg1FCGJ1VGy/gBk23Z2XxCiqzGMvfLl7vZ5zGz6wYLNyOIyFpVIyqPSZ5N53n60iKduh/HVNpUHBwtsbvyyNw0CD9Mu9qJ8j7+4rCymthDmZR1+jz3XifCKnDCjNj6519K4uAu5vjHQ/3F5pB2Ld6ph9VZTFZq+WW9GzwmJY/HApuM2A9gnG4mumHyMveHHlqFMgPYgWD4rIsz6bIi2mtoNC3mqbUNnCY/afALimFWx0z7QJXdMLeu6egWiRmNkKwviMLltMcttI5UBOBWZaoQj5W2UIxfTjIAlIFAGmDSQpHcJF/SPMzDMFxCscFKYxCXcJxKemk4sQcsKOJYZvKQrmkguQ2KphCW3JHJZkqlewxmMtFVy5APjEDjDmd0TbMEwulQgAmkCqWwgnzBiUl/RIIHFkZWUaGlQx9UgkLmVlF1Ad0njjkeShiiU3vR6ub8rKT/LQjltUbziofpqUDsmGsM1AIm2x4M3JRPy+S+TEMUjY5+xhsAKXqq2TcMaAgf2DjCsNnbeJSXkxu8wFfbEwtPkMfGF0V0YsHXjhVAff+LMr1rE09pI5JPuAd1ByLFLTnbsvZ0v6uXS3yYTHNNn7q2SOx0uqKN/zVx/Q9Cqy6icsT1ifsVTo4PNEHQN6wLoyNKNEHqE3FZ6ITUXmpaGUlq/pB1UAeGgO5PFNx5GdZDncxI5Sd0N6b78+KLo259I0A0+mLYsUH46Wyjof6rvak1E+0IzQiYwCCu7JS1epy/QIE2ezziNKlQMODXLUgJJf5OVPYp2eEBzOhQUawm34uI0aJIFa/oZS3Z+DhUEYUd2GCtRoFVzeQ0mjJjAWZS5+kDKh8EKQT32VFwO+1bfWhU5T2+rgVzzmV4dGkbzeaJj/T8hTjtB5pKy3wKNpFxVZ03FYn6gZ24a6o7LfkwY9r3JnRVfT8uHlT5mijdXE5S7O6is1y2JNzXw8L/X9DOuXKSmr9iGZYX7sm2HnTAOGg+4pI6shEgvNfa4vPD5Gr27yp7VONVR519ys/mRWaP1a+cI7j+frr/dNsC1DAcQi3dezYqrOXym/X39Shw5PnzF9sWKQI3+z3HH/rCqE4kimetokiJPcDIvgKBArJgWLh5LSp8hZGOayfie3/TnAqfrt3J/JAahtVeAcg0VQ7kLb++06OoNfMtRqiVu1ch13O1W+eyPr16lU7edsL2NfV2zdXEsM7jcIxa9EbzFjtQwooO9rUGmjipzKJsP6xR4plf52vM9NRsx2PdI6bu0Ew01Gn7G/yhjztxf5aDLmbP8qa+3WXmLAZPxV8aucn/7PpfdMJvx2X324u30ui2c6GczumUcc4KDAYToVbe9ZwHDnoKJsOp1U7FnEF+Co8dx0JmvX8+OjO0edcNPZAnavUs0AJ4OPpnPl9l7lFndOxgOm83XFXpWuAc7me6YLbbtenwLunK3wzBZ72cXef5RqTqQ0Wxqx967LqXw089hseabYu6EywNXludmK3+Nz2cQOV7dws9Ut9ovwfIsXnh/N1r7bv25bu3vh86FkBX3p3f4z4KX/ntk32ocXnXd3LwPxzNexOHzIuj8++v2GznyD8LlPr/Wa5iiuJOz/e04aHPj/lpNaA8b//85JNbcGk3iMfj25ONmbdE7kZvdZL3vXXO2MHiDmGIchqpjQ2PE5BitxzDnf7j6+tXnz58dGU9rl49a7G4d/2vR6mtwED48nmPAgKgmBuJTJuQr4lPjQQAJXiJVcSDXyWyi1Hk6IXjDRbJ5s6S0ZszI8rlk3kjDgSDuc+21zfjgzpYEND3cmJyQKJ7QWIKX5O9KXxeVidVq6Y/mKELyksOERavTok1FW4JqE4RE57qQY9//Zhkha9m7LiZKHRFlz2zvuZnioXmmnoP0zdARYGrpBCBL8+mBZ3tmDlFiHc0c2/mpW/SVjt1997Aq9+IXP9CubD/YKEJRDM0nglsUEIqW1UiDL/6S+JBQVxn2oaKOiymWDeXsag9i+3erKLuhHczsbWYMN9mXac6Gxso23LMHvcR3B5ZZdwiKxBXXs5T/kA8FqGEqjt1iDMtOLcoTvvUDlpeVe+cK7soyySA3tJkuDX2axakIonJHG72YJytDkLhlV7tk+mcMnPFOl6P3TmfzMhs1PIb8os9moQI/kRxpIj9uoOEBXK1z6drQuNSlmYBFiJQxn7GN+HFe6Kf4pEoXSXnyK8kQWilCPMSVlA//j0RpRQnU+1g7eBBI6i7oa2XYHz0+ykjdm06Lw/B9Tn0ABhMKI2zLV09n+bj+A9OEsj/7kntqfekXtQyIoOTZytV+bjZDVSx6EZsGbczNb5fl3Y78tdfvTtPsF+udrC5o6z0oR8DGf4eg7jl8ZYxKk5L2y0owkDRtcB4tCSslS9ZXDhHdEujxkPPytz57QhXh1/JVIHuaZj8/kpGsVjcm8+n08sYAdYGawW3Dxq03BhnT7U58vzd3NMc7v3L1yvDliO57osB4pRCNdvy3B4HN02tjE2y891eBjqGe+gKi7wObyx98fC/HGys828MsF0LeJO4EclwUHi+CQPxe/P1u43nzAmAJFxcqSqt2CGS1mRfBHKrftFnymE3Gb02Aaz4WobCNwSgu6ifhtg6m31/EelQCAt04IG6u1nIaEHHmVTii+tTXYglqeOqgQw31fhR58FE90pAOLfaaCiwYSe+k9CiPouzdkYgZRTPesxFY0+eR+xgBH3EAYbsIGoaOPIr89JBpnyoa4g1pJEKoQY0EABiz505RHq63SLabGavni/wNOioqxfbnLMqQ2LSSROlpIz1U6pHVPmvSeyA4twTWsZ0+aXKyxc6xSOvzkOi6l6v+Akw6NvbjvD2IeIuHtOKj6TVTo90Ntz3v8AACRY8Vtx3y0PDmKx/aHYZ72mD5+VY3WTl+v+0CEOaCMfQgJElZQvKBXYdxNCQwlCcn7M4o/v62KeKD3Jz8SyaEknpluextMwmyiZNPXVQjt0ACHlMsJuCyItsKiCyZdGIqCMGuVyaP8UZgWPLMUCum706quermVL8KlkgRVHbtsvq6+EE85uJq1WC0ZDwgq5izqGy3VNkxVRlyTJkyH6IUvY2VXTyVYAdsuj62Rv0ryWSrszyrJ4Xj361FTRUpW8BehEUUVVjjO9HZUsHIKC0KaOYRoDAxRh7Nh61b5pOGQKSurfAhXuBvW4FUtsuKkwrIpidc3DuelXi4wDzcBM4/SEDqrqAu9whb6o/BRmu8nWriRbRrNve0ofYP/oHiHW0rTVuN15aCprs1KqCzWR98U102wX6J+w7lihNDyiOle0iajgtdwQ7p9mynKz7SMfWqwUk3LcDbuR+y/DrworzpC1YSHCo7hHgQmzm4YOWxpHZdnBD2BCd/MhJsCEraG30ROSyaYBJdRb6wiwqia77lftFne4QX+MimerXzhhRUW6Vck99iCYLtOy7c0OINGNINhGCz2CFtfedQmenKzBg3DiyGuhes3XGai76Kof4klJ2Ucdoozsoa03ZBm7BRpLdgYo9LaoQs9u1hSO0xJH6XJIfot2nbpEcdKJ2wwlsIResw6TJnNHeeookfP79dlJ9vtRcP70GPHXNZZO7f2kgO+oa/6X+Wc+e9R7y5N+OF6fhg43YuX/m4yOxRHRcgJCFOGSDIqqghRV+qGSI9UU7Z4yjks6gel4019yR3njkISghRoOZdUcTnddKNtPN+wbGNqvykmM0Sm47E23StXwRPtpeoeTobgelMSPnKxDk9YHBA7p0nocLHbu1oI5veu/6Tx08nsZnlxvLGxaeznC7+blXWSpuYBzV8eWTer+1pNrQtjv7zbbtaO4pra/wcndd0Cn//8X5zU+rztf3FSupN1kv/mpPQvgM//Hun73W4NDkkMKmud/LuYzhEzqP/fhkRfnSf8p5krt7sSEy3jELnTnJvbPVnS1km6r6d52nXzSr/Zny2meFbP7jH1cOolOPElfpdQZpXc6Of2doW8c+77ToMppdT3FlL7uuPAv5QImqECcModw0wFbbAm32swlqrDXk8gAgl6gn2XfrNIN0t1YvcUYBDew3IuVTYf1V6G43Ye6XHeyjBz4HRzOFpi03yRtQKmYi/vmN7hPdrACXrUusBGyhTBGS/Zl08VwInpx0RANCxyw4yXjlf/MU02hr4gfLvTsp2UQe7tZ7/gEJWTxKZH254fwKMcqs6iPbeIx5N5FweMlxRbHQccLHM/zWa+XSOm0bIl3++scLu/RXB+vl549+E8WfXSy12f87D4yvoHotp36vFNQRBhv0EubL6JimSGcEqQqL2acLPuXbOnAaPNE38vmkqdN2BO1oVJSTyrJ3NbNMq5pNrCJFBBJFUtJ0mgPg9CjKmfj0SHo7eHMBAldvyFUwc36FKIaF6H8/KjLXuN2PnpI7ASYMtGUeqGHc4RrIEA7+GB08XoJXUs1Y8xaZRC5DcYLhDCwXihP6Fs2tNwkknCJ0ek3KkQWDH5IwfDJ5fkd0YAmoPsnIzdOogY/5y0V5HyKwhSpx/WIxLm7QPHPMdHV5tGwY240sN/TXOreFtoG0PMntiqCxH16oQHoR2YsmbMCK1FnFmeqsMt4/eplSIIVTiBAyPITL7AtOAzPeSTih0BvdRI3cUAMusn2HCsB2LPkNThClNguQYIa0nU0DFJ5gCwzQGMd5kBNUinB6atxuTPVQBHY+1WIwm0rMXBDlASaGVnz0RnHDuwT24zQ7zWJU0wFcSzS9W7jjETGCtlbbd0SQFhFXvFbIJG4TcehYUIiVynAU+DBOsHoX3pcQ7IUFe92PBLYLuacAYagWrAugiE0BsDxg3WdMfRPhyQZVkuG1TErQ/1/X78+17gWi+QsxskFYgi37DzWYRg+gK+rxLsaiJz0qG8M9TWvYFsCBK2IQGO0sRydHoIrfWza5gpV/eDdivCq8VnaEELNiEOjVOgKCjJVpf9rBkqvWXEgym4G2Fk756k4QgdkgBGJN4IIyKw4PHseSyG+VjzR8FsmAmmNfEmkXTRiZbSlGRNJ6zCS6l/tmyJTMiaHNIytuP8S9XMvDGMSymyjtL4uhNVqQM1rZNCEvhUTSQMHdP54aHYyEfpHAEGNcmm8FQokgvXBI8Yrp/AlSGa4FdRJym/YWIyRdjhFnhMTSEiDHyQzeSrSQHVxPwq8Pv4MJ1H6Jm8I7mcSaJ6d1Z9Br3MKVwUhfxypULhAFQchO8zA4ko0MgVzVvHlLxuAROdnAwhDi7O7PoHb/PQEOZb+ZxVVShvJGUKBjmNSeQeF01yhp17DZavHCGJ1QeJ9GAZsczfV1S/lal9T0ivlj40W2ehJ1PGmqkWoOZoq6iPctnY11J560llNXavqPI+bNgC19T3IG5qJ1WNxCgmWtXbh/lYCe/JkXGMCDOdRAivU5xAGUCjZMHrlB8B/yALh2PXQSSXIY8OgZpwQGa4AF1dQKfIuKYvx5xQyFNfSLtdyIRdpHZNqkErr7dcaHBdaEJbZCZZZCjJaORUZBFV9DRT0Rpc/Oya7LEsIB8IfGoEnCUB1zfAyzLAnRt45QR4ZQKvlwHIbqQHAkODo6T1nJQ8EEomCES+AdLQ60WmpsXWnsX2mcUO4NLnrKUJaqVJTqXOYaVpZaUZw6XwjdKczOJmWbCiHCO+e1npIX2FZBnBcdmPjbIScHm5aXkdbXlzWRkevLzdCehUK68sK+99U/5lubyNu6IxqmIAXDGkBl1IYJDQdVRiJnqODVYO8sIJqdRNAyQ2Xi4kVM5Bqnow1A2NKo2fs6J1iNYygXlJYAlSNXjOiMAAn5mSbynQ1jZ+Mv3oNZoK+UMLTW4ButUqRg4rxkwBHOcKvPLqieHqFnDN58NqAnWAcKSC2LmGNLoG4lzAeFMDo6tllqplNatl96vlzKrlbqvlXanlv6kVpKsTlqoTMasTQ/vVSWT9NycdSVa8qPs3J92irFf6Nyf9bqWy8l+c9OufegN10YO8sgduDeYrDZbOlBVHpFVHDf/mpA7OaSZZ5GZZjS9uGt3oyKylGt3Nmrz9/nJSjqZG0FTjm384Ka5QU5BZc5hfc0RW80Z/E3q9KeqmGSXVEELXkmzWkurXkp6lGfO9OWOl5T1dXdJNS75Ua6FZazGPapZfa1lbKxNta8VNazVdW61UW35Sa71fW3N5dFXWf4/0y+kb6f5yUvmm/5uTBgi1j9N1TN+4D0p1fEr4NJ/VsRz9UhXZwU5n6IkeYQDBufTxCFWM5J47hDBtdHj3Q36MPP/V1qlOSPiMx/kY0tjaD27r98JPcFbt/gzN+3zZBgGtQnBGIXgaXYWCXbQJXTpSNfjuBE4YEDLzkhVnqm1IY6wpBsgN+MFMgGWtSAgvY+r2BHV7s9wCnBUAqzTAkw1kO/U8gPQa0OFAQTCpMl8UDNCjxGHDhBkAfWgr+GuOPjMMeAdnH8i6kNS9D5TQd9vbR7LRh8b4glVTwN6FK8trLS/tK0bfh8GMvKz96+qFyuEGL0TjTUVLceczX5OOBz/y+JFnUM5ck8YqmS96fYTJnZ9OiymY+BxkBwUzoVj9ibBKC/w60IMDZO6Dkdms0bfJBBuDvuZf2hYGmLpY/CuGIs19QomwxoyYCVDgXKJh5qAMsGNmMO+QmrP26GudChdIhrRvXbZ/kvLIe3MfAqtBJlmiGg2gwXykzdy243YECzLaOjrSqeFTLe5bLT5Sx+HLyTwcEcP8lghaJw0u4uhVyMKD2wyMNQ9ju4/R/SP6DfEfzwMKQ/wDDBUBjqXxiYvxTQLIyWpMGpbg9Y8UXGtQkQsLkyxXcQxQqsM+3utHogDkbTFjwHLEpbTwG/Ko2ikRbp0g9zwyYlqM7Klca+87l4dOQ1PMlcq/pabZA6Y3z6s296gaOYFGara8Lvb+1XZVNNKRe3rcb4pNkQsw7GFp7NXjsJh2w0wIhz3pwBDObqHC567bnA3Apy30+/cMq5qnDSpSgvGe05UyeVqSv44duwaemEcK/dlG4okRbBXlBsqJwHw3/T2isXaewIdmu6XjlAOYSxLjO87SySPFW5//HJ2mPw31sgr6XPs+cT8WR5eNrXWO7zTmiDeSbyoJ69jktR4BSbV12zqRPiRkSj2oqdaAvxsUkcMXscbTQ03xvqN9vppnEoMjEAM/m+E9F1I4JVfKlJiCxYNQIqtKkoue0SRGA3NRcIQYiKGHyQf5EZBP19V14DK0u5m7jZJT+tZVu61REVO1aJK19hJpoCXIR3KatUH/OhESYN0Lwt0gG4vEbxTkGsww6ZsVwWNWJjfS3klC68RZMmuUGnweH5Eng1gV4ZmlRwpPgYjZ4eu8SLBa8Vd93TWRldkXNbO08EXSbiJHlmXY1CKtdRAAeYPo3lD4bmu2+T4eMzXujiYjZzMLEUXzUzpAwkAShtWYuwERynWY4iZRBcTedwgLspfAsIRRKPCxiQLjUsCxCHvnXC80dqKEOK9ayG6Noq16i4uEaE8=
*/