// Boost.Geometry Index
//
// Copyright (c) 2011-2013 Adam Wulkiewicz, Lodz, Poland.
//
// This file was modified by Oracle on 2019, 2020.
// Modifications copyright (c) 2019-2020 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_UTIL_TUPLES_HPP
#define BOOST_GEOMETRY_UTIL_TUPLES_HPP

#include <boost/geometry/core/config.hpp>

#include <boost/mpl/if.hpp>
#include <boost/mpl/not.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/type_traits/integral_constant.hpp>
#include <boost/type_traits/is_same.hpp>

#include <utility>

#ifdef BOOST_GEOMETRY_CXX11_TUPLE

#include <tuple>

#endif // BOOST_GEOMETRY_CXX11_TUPLE

namespace boost { namespace geometry { namespace tuples {


using boost::tuples::null_type;


template <int I, typename Tuple>
struct element
    : boost::tuples::element<I, Tuple>
{};

template <typename Tuple>
struct size
    : boost::tuples::length<Tuple>
{};

template <int I, typename HT, typename TT>
inline typename boost::tuples::access_traits
    <
        typename boost::tuples::element<I, boost::tuples::cons<HT, TT> >::type
    >::non_const_type
get(boost::tuples::cons<HT, TT> & tup)
{
    return boost::tuples::get<I>(tup);
}

template <int I, typename HT, typename TT>
inline typename boost::tuples::access_traits
    <
        typename boost::tuples::element<I, boost::tuples::cons<HT, TT> >::type
    >::const_type
get(boost::tuples::cons<HT, TT> const& tup)
{
    return boost::tuples::get<I>(tup);
}


template <int I, typename F, typename S>
struct element<I, std::pair<F, S> >
{};

template <typename F, typename S>
struct element<0, std::pair<F, S> >
{
    typedef F type;
};

template <typename F, typename S>
struct element<1, std::pair<F, S> >
{
    typedef S type;
};

template <typename F, typename S>
struct size<std::pair<F, S> >
    : boost::integral_constant<int, 2>
{};

template <int I, typename Pair>
struct get_pair;

template <typename F, typename S>
struct get_pair<0, std::pair<F, S> >
{
    typedef F type;

    static inline F& apply(std::pair<F, S> & p)
    {
        return p.first;
    }

    static inline F const& apply(std::pair<F, S> const& p)
    {
        return p.first;
    }
};

template <typename F, typename S>
struct get_pair<1, std::pair<F, S> >
{
    typedef S type;

    static inline S& apply(std::pair<F, S> & p)
    {
        return p.second;
    }

    static inline S const& apply(std::pair<F, S> const& p)
    {
        return p.second;
    }
};

template <int I, typename F, typename S>
inline typename get_pair<I, std::pair<F, S> >::type&
get(std::pair<F, S> & p)
{
    return get_pair<I, std::pair<F, S> >::apply(p);
}

template <int I, typename F, typename S>
inline typename get_pair<I, std::pair<F, S> >::type const&
get(std::pair<F, S> const& p)
{
    return get_pair<I, std::pair<F, S> >::apply(p);
}

#ifdef BOOST_GEOMETRY_CXX11_TUPLE

template <int I, typename ...Ts>
struct element<I, std::tuple<Ts...> >
    : std::tuple_element<I, std::tuple<Ts...> >
{};

template <typename ...Ts>
struct size<std::tuple<Ts...> >
    : std::tuple_size<std::tuple<Ts...> >
{};

template <int I, typename ...Ts>
inline typename std::tuple_element<I, std::tuple<Ts...> >::type&
get(std::tuple<Ts...> & tup)
{
    return std::get<I>(tup);
}

template <int I, typename ...Ts>
inline typename std::tuple_element<I, std::tuple<Ts...> >::type const&
get(std::tuple<Ts...> const& tup)
{
    return std::get<I>(tup);
}

#endif // BOOST_GEOMETRY_CXX11_TUPLE


// find_index_if
// Searches for the index of an element for which UnaryPredicate returns true
// If such element is not found the result is N

template
<
    typename Tuple,
    template <typename> class UnaryPred,
    int I = 0,
    int N = size<Tuple>::value
>
struct find_index_if
    : boost::mpl::if_c
        <
            UnaryPred<typename element<I, Tuple>::type>::value,
            boost::integral_constant<int, I>,
            typename find_index_if<Tuple, UnaryPred, I+1, N>::type
        >::type
{};

template
<
    typename Tuple,
    template <typename> class UnaryPred,
    int N
>
struct find_index_if<Tuple, UnaryPred, N, N>
    : boost::integral_constant<int, N>
{};


// find_if
// Searches for an element for which UnaryPredicate returns true
// If such element is not found the result is boost::tuples::null_type

template
<
    typename Tuple,
    template <typename> class UnaryPred,
    int I = 0,
    int N = size<Tuple>::value
>
struct find_if
    : boost::mpl::if_c
        <
            UnaryPred<typename element<I, Tuple>::type>::value,
            element<I, Tuple>,
            find_if<Tuple, UnaryPred, I+1, N>
        >::type
{};

template
<
    typename Tuple,
    template <typename> class UnaryPred,
    int N
>
struct find_if<Tuple, UnaryPred, N, N>
{
    typedef boost::tuples::null_type type;
};


// is_found
// Returns true if a type T (the result of find_if) was found.

template <typename T>
struct is_found
    : boost::mpl::not_<boost::is_same<T, boost::tuples::null_type> >
{};


// is_not_found
// Returns true if a type T (the result of find_if) was not found.

template <typename T>
struct is_not_found
    : boost::is_same<T, boost::tuples::null_type>
{};


// exists_if
// Returns true if search for element meeting UnaryPred can be found.

template <typename Tuple, template <typename> class UnaryPred>
struct exists_if
    : is_found<typename find_if<Tuple, UnaryPred>::type>
{};


// push_back
// A utility used to create a type/object of a Tuple containing
//   all types/objects stored in another Tuple plus additional one.

template <typename Tuple,
          typename T,
          size_t I = 0,
          size_t N = size<Tuple>::value>
struct push_back_bt
{
    typedef
    boost::tuples::cons<
        typename element<I, Tuple>::type,
        typename push_back_bt<Tuple, T, I+1, N>::type
    > type;

    static type apply(Tuple const& tup, T const& t)
    {
        return
        type(
            geometry::tuples::get<I>(tup),
            push_back_bt<Tuple, T, I+1, N>::apply(tup, t)
        );
    }
};

template <typename Tuple, typename T, size_t N>
struct push_back_bt<Tuple, T, N, N>
{
    typedef boost::tuples::cons<T, boost::tuples::null_type> type;

    static type apply(Tuple const&, T const& t)
    {
        return type(t, boost::tuples::null_type());
    }
};

template <typename Tuple, typename T>
struct push_back
    : push_back_bt<Tuple, T>
{};

template <typename F, typename S, typename T>
struct push_back<std::pair<F, S>, T>
{
#ifdef BOOST_GEOMETRY_CXX11_TUPLE
    typedef std::tuple<F, S, T> type;
#else
    typedef boost::tuple<F, S, T> type;
#endif // BOOST_GEOMETRY_CXX11_TUPLE

    static type apply(std::pair<F, S> const& p, T const& t)
    {
        return type(p.first, p.second, t);
    }

#ifdef BOOST_GEOMETRY_CXX11_TUPLE
#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

    static type apply(std::pair<F, S> && p, T const& t)
    {
        return type(std::move(p.first), std::move(p.second), t);
    }

    static type apply(std::pair<F, S> && p, T && t)
    {
        return type(std::move(p.first), std::move(p.second), std::move(t));
    }

#endif
#endif // BOOST_GEOMETRY_CXX11_TUPLE

};

#ifdef BOOST_GEOMETRY_CXX11_TUPLE

// NOTE: In C++14 std::integer_sequence and std::make_integer_sequence could be used

template <int... Is>
struct int_sequence {};

template <int N, int ...Is>
struct make_int_sequence
{
    typedef typename make_int_sequence<N - 1, N - 1, Is...>::type type;
};

template <int ...Is>
struct make_int_sequence<0, Is...>
{
    typedef int_sequence<Is...> type;
};

template <typename Is, typename Tuple, typename T>
struct push_back_st;

template <int ...Is, typename ...Ts, typename T>
struct push_back_st<int_sequence<Is...>, std::tuple<Ts...>, T>
{
    typedef std::tuple<Ts..., T> type;

    static type apply(std::tuple<Ts...> const& tup, T const& t)
    {
        return type(std::get<Is>(tup)..., t);
    }

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

    static type apply(std::tuple<Ts...> && tup, T const& t)
    {
        return type(std::move(std::get<Is>(tup))..., t);
    }

    static type apply(std::tuple<Ts...> && tup, T && t)
    {
        return type(std::move(std::get<Is>(tup))..., std::move(t));
    }

#endif
};

template <typename ...Ts, typename T>
struct push_back<std::tuple<Ts...>, T>
    : push_back_st
        <
            typename make_int_sequence<sizeof...(Ts)>::type,
            std::tuple<Ts...>,
            T
        >
{};

#endif // BOOST_GEOMETRY_CXX11_TUPLE


}}} // namespace boost::geometry::tuples

#endif // BOOST_GEOMETRY_UTIL_TUPLES_HPP

/* tuples.hpp
cqPyCzfw6Mc51PSu4EA3zhXYC7OvuuEB1D6z1ANmRIZxjSDsdaZkpJfiRKgB3Chx4/tGTMOMkkAUn4ZDaX9247g2PNRkeCfw4PFwVyNm3uHjbWYezjqcfREzj3ihdC/uRuwGaXyDZXeyRtEjNL1cWpU2EMDlwk3+cCxi82Fn1cjOO+mczpliX7eoALHsSr/oTl683pm5eK00D8kRZvFf+U3zJ7+gibAZGUpsVXsbnP9o3cayYzjjemnwSR3RrMweoP0j0GZwPDetfStJs+n9qow7NSaZV04ylNlB1JtPLB1v4lzEtqFLrPthXGfSOP9ZtJwY0CAycAKqCEZSBdLnSoD8teMccjbzCM3eH9sMx8Gj2nBoPIFGJY1N4pyhIfxJ+/Dno1rv6Usof7dWo5oWHIzEPrcVsU8DaAw6NOWHdZmVQpPO5DTPsvXadwyOqI192Bq5PSBXEE9/Xj+mM58+XLas0BKwIEwZZj3equDXNHTQ/MJqjTmn4ohe+7y9ES2saoWZgRosA1vDsrEK/dGr0u2t5mNnzlUxw1OQQbF060Pbhs0lzEqzpTu7orFLO0oYTsgU7M++rv43lh9L+R1ohGiiemye/ItSPFHXzw5glYZAVDOCLaXYiQGuMvEVyY7U8w2QAGw2VyG91HuHKWWOfqXj8Goyd4tjR+XhP3C3NTaKZ4nVsiyBLn29G+8so2dQcvtBX7JKvLMRjTBR/nxcH7mViDS7hq3mqvCakRY5pPcROdq6HaWTUfpCurZZMLYBjH6N7c+jVhxZpd6Z1EXcfx3Wj1Jj2F1HteH0UBA90oVeO6zbY+RWkXZpdSI3QMlfZDYYNPsPSArMMpM841QuQSPrvscF3Kn84Fh3A6UZFGXyr+wmJ5QvlwAoDsF1pL+BQpd/hzM6v9LnKYc5WEtTUEbT5kqoRzmhSTDxVLDh1G3F+SV0Unj4CEj096Evpwdb5+zSNuczmDMVcw5rnbNrZM5uqAs7opN/EtKPDVEWrw3ZCpSbXkCzWqhoAVR0wqGUrTuHNa27pjdag1V5e6RXQlJXXJ3LQqnSMGjgd0e06ZpwqH1m/uLnnNjScDrSZ8g8Jhk1SGnCQCBCeXU5wLEEPX1ahNuRbjvw1b+Qo+wbuhYBIiNMnXXNOHc4vgVXCfBCYOu2/oc1GF4+2D4MVh0GahDKSlaoCeO6JWLfp8ALsB8pHn6jMcg1/EbxJcO2+3Ot7oxb1P3OZ5F1Kxb3bdiFGN6FP2MXipUT684VU6hmu/ByMTQPVNGIHAHHUoQGglMQv7mclNKLkcKIOopD3cScnTFnUnpl/jHK5cq/GJkDgf3qMw1YpbJ9YNVDrRHxHS6Rf+wdXiJtPr0K8RZVfNyqChC545cNgXIOvVz8Lcrl6eXgfUzrYye7Q0hdVgd/VtZG+mR55GZ7zSTdDkCxfNeLtpuwZY9bdpewpw41SnXpx3yWQ/CBnU/E7cCQvfAcB6t4HRmuDqN44ZZNkLhjwkbr2INCfieTPuNXQGpGPCxBajH89CN1RB5d5rPMhU9BzTDs3l6kXvReCb4JO1zcSNMut/d5mF3J+i53MIJQfk63h+Y73SNBUhJXGRRvjSQA4josg31akr5PSzIoh0sCgnzWiGbWPk/CGty8V/EzLMVyMkE7pn/PoB3Tv6nbeHMP3atr4SNGccod90UCF5brJA9ZGftn1pZZ9mEiqgLqWFMlv/+SQCbCdVAbmcVJ91On+3EznTpd+SLEW+HXUxdEeGqpBhjvq5UmA/vsUMgMok63/qtjf64kSZzeqqCziidBmZlEzgrI4DhG2HOpg89b4yjCbSM6L3B0qoN3+irkRaso0iIDvSLkN/GrOqd7cqVuIuqqblIoPSSqlt2QIz/uCPyVBucf86Y68utgEOVFtYZ1i5h2mF5L/SuoC+k9BgX7cDPAQ+x5tF7vklfp/UvozsJ9Jfy+zIp2rTFan4njefibGSpFciym8WiljLOPqIfduj3jd1Yhv6eZqNDaUxvQGLM2oC1oQjWuZ09kRXG54wR8EPIWYHY80VuIup4KnGV+9KDF3jig64uqQ/qiPhVhO35UN4IE4kc2uuNhlnEgJExU67PSzi6Vc62EHSDkJ1CWZ3vQaYCQnxGaG3N6kOGHHEgR8i5qjmQKyLNMbx6TXg6YhLzVdMBrlZ4CqOyw3r9N1OFHtsbNMz/8lJsh4yJc+bH+fJw9Vc5Bm79jgEY3z6TMZ99WRBiRQgJX+o0r50q/QCkpti0lNpKa5vM59jQ/dM/dMVdDSS57tYIK5HKL52rSpLEGEKbtO9Hutzjwe374soIqEo25mfO89+euME3wekRf3GO8+iR+uPbLN7rVro7ybeydMkL5Ng17w22aLDGAw5cM74Hb+JRKY+nNVMF0jo+/l/J+T48QKqezh8u4UDmdbOPIZPWZlCXsC0KS5yX8tETryEtsKGVe/FLgA27btKM7wWtA3fMJqt4WU0aceQl7rlQ3Z64O6cAvHQjbwIlK3ILuXDW9GKaFgX29D+bEY6IaN4dq9b/Erw8Dns0/hsTh6jCLf/0AJ6Y0vDfkiedZyS6Wq8mqw4aEzx0Ia8PQGtgQ+JbffbvSjc/0HjjTf9P2wtaDOBNCquMjrGEvKuexMfa3T6i3cw9oCrdwW3eWaxd5dDC4rQ376dPwBZ9huCIVG9saQrT1Jd1mzrfR1nH3apah3fCyjpsuTmYkePv57zfSAbTpE1StnSCTLy6dLgEIAs9E4fwfvcqSm5G5JiE3Y57UTVfh+3rheVRgCppa7E3jt13kSjXH/Kl8aTTMy0+7wnC1DPTemZEg9YYc9GEcfPgnfYha1UNuiQkKDuWLwO9VVAivsMgt5jUm5UrWFa9upyD6+pA+8DszireLLwvxJqfSgvIu3juQfzSJvrk/On2LL5M1lJAXz21tfiklsurJ+pQQc63GM2iNrmLYH0tpNPt1pSUmBjOS3gIAdbASujXnaeDat63F/Pw6rH2LYQ+UElnH6PVi2RjmgNT008FEvJby4UfttJrEW323C29Va1HIm6CZtuWjV1a6BzO3Af6hXdm6Lnhpa3MX9KqyMCVJrp3v9lsW3mWmvmXPJ+N3Ia8EEJ/sUpNdghvghnZjWC0KoqmLqVs/2uvLomAva5kG9aCyw5H3qZD3DV+gY9iQQGR/t+/jBgnh/vZkT+yn/vbUekSV9mT3aqnUD2XuGcVyOT6i/vf0+j/cH8JFz1CV3SMLB96kDgjQBzeiGrbtDG1OcldfNgt54wErzoxFfYRNI1U84nD1caQfgN2kM53huAfu4LbHPRHv4/bwtgKjbmh2FdPQwGz1GajnQapnvlXYNA2eAGBSzujaoDOBbK0eFrWfF5G6Y/Y1nVvnc6Vf9GQOlcZh33aksrV72+nd6BIdYZ6e/DJJT7Yjssdce/K0oGlPXvuQh9EFQTneueFJq6Y5cftSg+Yc5SraHYjKCVbNV6UY9ni5NmS0+7/+yc1D9kHxzRCk8YHoSRYs/1VMKs5sgVScQFioU0OpvzvXsUCWJTxLL8xSErQSjhuOu/K+krqxXzgE1bhYisXo0YKdLdfQ1pPQ1kXxnIlUf3nOoJ1XV5DSqvF6jBDvGQC/QrBzyCBpGEx0M3K6lwxtj7ft7RxvR/I7svnTYzz5n3wL2B06QU6vFwYuqcC41Z3RKOHcHpwvHiWQPLOcHLJ499k3gNhuxytUd0TjLEzxDnUqnrXotgCtyJ+FPm5nKnY207tdQmF9Ownrr0LuPdxo1PJVHJoxeAvg33aQQ4p6kMfNeqffPkhpcoytcAie4uSZuwY1Js/crNgOxuH09xYo5TKLEvLwlpBaIXnlRrOQX4XbzP26vnkBvDUco4Yni8q4d/eYDPX76Yyp3ARo3I5xWUiX7LrMZnA2hSY/l7Xl9wg7xIngCL5tD2B4DigvKrYFUFPgvCGyLQSj4Ri6A70bmpoS2RRUK1AzXoFd5NxB5VdnBKxYZQupGa8qDPQWuBVvAV3B4y0ZoSL9UMxTwB7fi1pCbwH2P7hSb11arewvYV3ocanWYRdA8cHumzt8hnf4DFuwL6TGW3xGXzXTWM0+TecViEEHvQTEM7sjgNjOzsJ0UWyTYoGqixx8Tewda9FkyfhYC1HB4LZUsJU1HSAq2Crkn0fHjjZjZA01nSyG3TjwThCa92bAkFcMagok8P3BR53QnDJNigGJazs8y2ofYf1/kqDtxboLcHI/x1lXgd6pfVqPzn9MG7PtYR13AXo2QUVVkpblAc6Dtt+ko/rXxxFa+QIc3YiSsNlliXtbNRouKbUq6Uqvt9eXxwt5PTB6T6Z3bcRl5nS6i/oiLs8ZoyUvrL0rPqa1dyv76+7I2kOCWMLHhJW/d7QYNPWkZys1g5cCYR39Gc9f+bnP4g+4EbpeiVbDiY8ioQvi/ewHOvJLhS5q+cZPyIs2myUbqSEFUkN6NhMvGu7aDPkHQH7yAtOdD3xPeM9tsktjAn1VKsuvxBXoV+I2v0eUX4AM7/0PtL1zAYdS+BA1pFc68NXvTaNSLo2Ta2OzY73zEFlC/hF+x2MrKznbLkaiW/dnIC/cl4psOqt1pRt1JY54qmsz7wiMikkaDjjfpuN8WFG7LfxtT2QLUMxIxebqxRp3tVtscati+wza8Av56JSCrlqucuSvSrF67/Fkeg2SiHXtSGK/2dXeKUbSnlb6aJ16//sjFDy/iFS+O9u7v1kQdGnVd9pFJYLdqdFhWurVnXQ2HKGUR4X8P3eHj+MK2JbdGFRqc6cjPs9mZwawfski7Fm8OQ64S0GgHwh+IRcBnKwx7ifw/K2BGPhGHf9vigkKHZcIG7z39+ZkDpfcEefUH3Jq2RqCx7WVJe8mbryVg4sI3cq27OFpuNvP4ZeWrxWRnwfIxKv6zXsh45jgV9hO7/C3e96L6LI5WMxTM95Du4hXU7QwAPoySmqscHjB9u10lojyokJuU0LCZbKrKNmFK6gaTbcShLwNpOGZ4P3dRtiNNtm940XZchI+mkjbU0f3e2yJe8KWI1s+vNlyxFbEtRzBMXiZ4k6uHGPLqrGrqcLAxYW5q4tMXjwrWB9NbgJXRFv43ZaCC6E8dB0dc5rJ6/Tn/L6ZSerTYHk0WlMaxkIV2dFcKRbD7VTQX85wXl0x+2IX8aKBvHfedFGBfXjIsyVwhgUVPks3/CqXxIjy2UbV9qGFIKq38GsaDzoVy08WXh0yh46FdPhdbeHXGZVDecXSwB1JY/d7u+eopRu6iGpJEC80OjK6SY1B3StaKbeXPgk/kKJY/oQ1KtotWvnTJXPbj9VLezzdwkqx3GfBvR0IODla8KAruL940RCxhbOg5+Z7EJU5ylFmBE6GEW6BqDL7SB3wZpCRsEbfv2CLd+Ka10eK5YNZzebsJD5Rhzd9X7wC+8N8EnYO4ncKoFlNEbserYfNWe5qw12YV3i5lDvcYQcPAm3PCt8x2vQvrmbBs507ijRQQo3XfcgbT6TkTnR5W+ctHJrDH5ITB9SfRmuuGzCSCHr9lrTQSG3sIVvFa9GkxBzlJPfx5lbOejQX5ujrZTf6EWN/2dyMsSOC/C33TxiAxJdYaMbxyUuh7abP8ha+yv13m1G1Kfd/PfJX2JWXgtcnyYk+XThyKkfceDP6C86iXnpHtztYSlqGGrdimQ0lPeibXFTiZpjJTHYm/nBr0y6izzYeXh1qFeQdDE/Bag7fF3/EmCel+vRvoyxoE1vl38RFSQgXf/xjJC6kzRwXfzO1wsUWE+HiXRPHwSuRv5ArSUeFwtFCsW7aYGTNP3WMzG/WMXK3KYyRiSbCyCRTK4wMNukY6W0KY2T/K/8eRkI4mZGCITJ1dkjXZK8ZQYDbONyeVy/knSaNJzDJdYuK+E2iEruws0w+hJ43jkLGMleaQW68Z+0iIW8VXReaJLw4jh5ca0S5cfKasXJjzprBcuPUNXfIjR4hP4mOOG1vfcitPJn9fZhXj/DEFyExGEDdKj7U4v1zfMDbXnPx4bDcOE3Ii8Ld/qYauupwv7Cpgh5mC3nvG7VrL5+gTfTOXgCrUgpg3gVgys0eoQD1cnKjW/BvpYfJa5+XG+9e/TSgeYrcmCIly8UfywANLPLTjUZh/Smuvzv3gQbilh0A4l6uN6xipfwOycf8azEy/Te304XZwD7S0lZqN3Xi3jNYeAVfwQgHVnNdzSooF3xTbhRXPYeY6QyYWfsMpM/BdIxTMhUf0JxnBDwEVuI92sZ7hLxKgnmatFBuvE+6X258QJooF0M9xuVDuU3xJN5aLfvPE7SGCgNdhSBKFxqEfLzGTFZiQzieq96HmpNV3g98tvHnbfiMepmP8O4L+ieIGHpyTiE3twj5j1N4yriDCWb4cRVr5rlVH6EI02FuBfk1yp9b40XTyKP/1JwdDX6fu6AJLONtDca2tnBczimE50sY+rVG/tYcnMI7tFSN4qtgyZetO+QdERjKK7mtUBuia4X0fmSH9r53B47IzFS5WRXy0yHzxrl4C3iSZIe/Lmk4/J0sDYK/OVJ/+DtV6gN/53mn5za7pO65zZMlIbc5R+qY2zxVsuQ2e7xjoPKN2zUrz0d3aFdPC98NGSdXhVb7AYVhO9FCUZmbSh7BBmsMfdy7N8sHV7eHjm4KGdvOnVkEptL1obEGr6O+1CgNgHa/fk/rXSw0UV9qosSP9cRD7+GhMiYj3l/Rk2u3o3wUN+ptU3iwlCPsdYwymRxenK68wREWoRF9ZLt2717TUcDCfPM5YPg+8PwI10C7bkRxzz/8+qFyzZnsqXGhQPU6ipEyS5GWwd9EaaxDrUAH24fYM8D7An/lc6SmUCOaftu1K1SdyGVEEnuokOxMH4D6oVPut0wgsMJGswS6VgskM+EGkgydIvHzsj2LmZV92ABVi9zHUHaKdDv6GcIwk21dDPWnw6ISE1RUfz0KdrZd0GMn3uwn90XoCAvdFr1Nv9Kz8vnO0iPwMAL+9VUPegv5dfvThXTd/gOoAfv1Is599BbPjWG3QHLwBdTZbtf6OOFfbfr4HOE9btl16uPIN2FuoIM5QCGjQzRaVanPnlq33zLJhh6L45zXowy6pFB1kd/6/VsLcWw9Fn01ZEvUwBqyH8afvDJQcrSW/A+8hk0+jDhZnPo71oSXojWxm4nv8nvR+kkchjKb3ybGozUcevIk9bHb30lM3NYcZUgvdmSYhTyFwldkTZCmwN/ZdCOSzv7+DlwgUIBLF/mp+C2UEDNdVXR7fNQ7JgIy823y9+e3vfOOdnt8AKbkaKeLWJKjJrW72aCfiUJlyViZz1VL8e3euRB2phVcF+4x+5u+Ca/Sr4LPfCfkMK11b29h006Xb/HEAdWd6P/+WpSBvbkt5OD6JpsxE/oTIxeMe3VXTeGR1n2+VCW7apJdDLp1bzfqFj9C5b4CWvt8GfluyFte2OdLwT/DBuS6qf4tjlfaxj5Dq/IchXHHwOSam3VYivFUJyUoK7uL5rutkNLwO1VNr8xXpXS3co/VDd+m+rsbxQWmHHOJmMVWdcSA3vutWUeWBjE+n9+h5vi7F09UnB2jgma5Qvc8iQHDQZ61R/qedCumwJNqRDxc+UKqZ4F4O2xbPEqVQ4kyyo0t3k6QLUc5yFCFHuml/7PPchZMx7xOX6ypHX/bDqXJzW2uatgdv8FRskLPbkfPpvasVdaoNVE++Htrv9+hwmefal1YcUKx1t6C9f8ef1zok4f2SgaKDYDRplAWy8DgqLC36SoqJeynLTDyVey21yjYIYZeykBfwkXow599uUULkycqUSmiLxzsIGAGkS0UK+AfjVEGX9w2+HuTHvnJkO8CCpqapIx7HrKlX4R9FEYwwz3PdaMeG9GbStawn6u2hS+YDMq4eyCr07+FoSIs64xDCTqEyRccWRe8FREjCFxCjPQfHBI/bwlDuko0FkAAaBadEJXPmaNzCIy7Mi3HG6IMz/VVjqi2k/kmAGIrByLxI0h3KM0AyHVH1nVv8b8DyK/CUk+eLQIcGdUIyFexIUCGYWhcgMbFoTms2qYSNK9p0AwhaH4GaH5xZP3i3ftvQdNezEEOSg5uU8475M+BjZ7loY8x0OR/dbwJoA/qdYD25EUC9Gq9DtBVR9ZV70cIkIgATddgoRnXJh5tW3/+J0W5qXb5qn20nuRXioILNwxPQdXIFZLYBJC3dt+B9Hk0F55UigG6CrckcU7IBICnH1NtxvUmLUaqd3CmRb0ahRaYwNdXL6INV1zwn+y+yma13IDX2Njk0CNG7erKHoBcbEQokUeRu9lTOG6VxvD5qZSgfyJoBht/EegXGu7JLlcgXDWqraMMFF3BCuDdZ77ZJzL6bgoKCN/XCwk+DGXBzrZw77o/8rsjimUO1K8ttP7EHzeYDI68Ym+moxN5rcUoKP0gg88y6iou05Y1GAMR5vps5nwUeXWccQVKDYktv8BSceN5koJ++kWPT/jOApJu3zukRTDkgcK7vhDmiJwnwpShOx7pleXOlDTkE6rtg3zy7HEAK8MNpWr7M6RkRy/rDUjZ/gvKGJCXO7VH/EjwtcjYOggnj18Stw5yq7ansUK5/zJ4aR2T2PLoL2E2o/FGui+DLdjZyjCt3pYJCZKNPVPeTEjsxB6DJwzb5rO2vYAUWN4S6magT3Pbe7yt1ijRP1HF8B/5+6XuTChHEsFTCrbCi3QSfBzjqFrErJPLzu2jwDXKz2JWtShMviY2fCP/AHLkEdH/zHir6I8aKGZVPBfHDpXpZBbch/6Sg+E4atsxrGFDtWguFfuVi4NKkUUPOuz2Pdj4KwtZq3WHApVcw4nTgz1WFgL2EIbEhfUwOAw1cKKS08ieiTYYdhPE5fubcHXLagKoj4gNp+VvYzA856DjGD3vphWKxg3mQVyoph+ut10btTtjgDmOtpoDIUgcEqFt8kfUdNZxaPMUxtj1OztZOX7+eSCEH/InfaiZ8JNejLEohBy/8zar2HBc7Aei3OzGm+NdxOP4JZAxYWSgvTQXMrwrgBwPrnskcXQjjclRlJFM6IoKfYii//XuovwtdG1qI+t0HaO3Bu7hUdXUHBijrqxjuDfLlgGU3/Dwf1k/LfsOlthPrKTPuyTKtY3urANuZX5jjjAZ5JySnEGf5jR8DSyWFDai+rlD/j6GfRdFS3EOLBkw4OYK6OA4QMwRt39VqpVGBBby1Jws9bk=
*/