
//          Copyright Oliver Kowalke 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_CONTEXT_DETAIL_INDEX_SEQUENCE_H
#define BOOST_CONTEXT_DETAIL_INDEX_SEQUENCE_H

#include <cstddef>

#include <boost/config.hpp>

#include <boost/context/detail/config.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
# include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace context {
namespace detail {

#if ! defined(BOOST_CONTEXT_NO_CXX14_INTEGER_SEQUENCE)
template< std::size_t ... I >
using index_sequence = std::index_sequence< I ... >;
template< std::size_t I >
using make_index_sequence = std::make_index_sequence< I >;
template< typename ... T >
using index_sequence_for = std::index_sequence_for< T ... >;
#else
//http://stackoverflow.com/questions/17424477/implementation-c14-make-integer-sequence

template< std::size_t ... I >
struct index_sequence {
    using type = index_sequence;
    using value_type = std::size_t;
    static constexpr std::size_t size() {
        return sizeof ... (I);
    }
};

template< typename Seq1, typename Seq2 >
struct concat_sequence;

template< std::size_t ... I1, std::size_t ... I2 >
struct concat_sequence< index_sequence< I1 ... >, index_sequence< I2 ... > > : public index_sequence< I1 ..., (sizeof ... (I1)+I2) ... > {
};

template< std::size_t I >
struct make_index_sequence : public concat_sequence< typename make_index_sequence< I/2 >::type,
                                                     typename make_index_sequence< I-I/2 >::type > {
};

template<>
struct make_index_sequence< 0 > : public index_sequence<> {
};
template<>
struct make_index_sequence< 1 > : public index_sequence< 0 > {
};

template< typename ... T >
using index_sequence_for = make_index_sequence< sizeof ... (T) >;
#endif

}}}

#ifdef BOOST_HAS_ABI_HEADERS
#include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_CONTEXT_DETAIL_INDEX_SEQUENCE_H

/* index_sequence.hpp
08hd4OpErgpvs/AjW4J5hM63jmo5tO/u3JbwOsvRLfjdrWD647NY9r+bUs/yRs+i30H1qxJs78SlgjKtDB8qFHOpWL1cEuR7Smsp+WhITftuudhULi/6ujLQV94rWuPtYH1V/e0T/dUYWjUgt80HZD+r2D6onaprCc6yzGsJ7yPNb/F/uM9wjNiOYwW3f+rvXmi8MGPls0s2LCH0J6f0aUYyO+iKdT4fshicX9/i+jqH9PMsc/k+JmK+j93i3zS0WP+mQ+qx37hoTtm3WA5Sv12fNUKfNUGfNZs+a2mhn+mzVumzhZX67BDX+B39xUJ/yzR9+6n2cY737U+pUmfwT5W3dU84RDt0otgh3Xt5MtohI4uAr94cSKQiksqlW/dedI7NaoZ7H65YYc9GA68huWSzJGaBr5C53Uktdm43MD6US42WxlYY5PMwjf5Gu2Fz0Pd6ivTxTyuMy1NYtpkQBRp3U47JXv6+7xgawXGs9rfC3GVJzDgObPBQsTAu9ldku9zVATZ/JdnpEpasdRzuzt2BrNewvNoJi6rgEWrNQDRzGmuCT4iOuX55mvTL8AHYY/Rpubap0Ur1nSb1XVNBD5YaPQivlRW37/Cw3yv7fm0t4uNFeWL90e/kEvlO6pmCpZ5LPlzy+05Hv+8JWf+v4vmI2uYzje+9TGzxo+L3P11s8XLB07UptecrjD1/Zgv9jD0/S2g8S3C1XqVxjqGxsoV+hka70FgluK/8H4zne/kbW3kdqzVuHUvu7ndCXy2R9ZKdqYlM1ow9m4H73jrf9crMd+fIfFfX/7vxO3AQNnJF6IzC9tBHbaqzCbp+twZt/EHsFw4fwF7Xwa5p8blD0R1t87nMt8zptK1mvqb+bo34u3oeYz22+QmYm8euMxzAOgXHhm6pMDc/CH3k+/9Cc1UczQNcR3P0+qfB44Gs/XKs6pYKe4KH8B3kdzun5PfA/GxHc7PQ/C6MPTyb2su6lS/1sNqnZzM8hV3FY3SA4aOBvIXORsFXsSn+eQwfCpoNeedz3kiIczwLpPNriZ+jaUYjX9f5IdVbpunrnjjFXtZzxOddJbbuuRFbV2YNusy687/gu7XVfHOSlE6ab84F8s0ZMt/Iu8z63YjgjcL3rc6UGRPaM1r8MtukzLjB+6ehfaHgbQfajfB3kyk/KfXskHoyUj4reG+dcn5KZq6TZj47h4xfc+jrXv4eYpa2+L1gD5HT/vtUm2StNgf9vPQJOTcg8bHNumJBZFNsCd/9v5j4p3ZyO2wshF2EG2sLD0If9xgd3Evpt5r7qs8XHh1PiPuCFh8fcS+RNNHQstpePXOp5XkNemVduPyLW4L8pvogn/wezr+sRc5/Snl8k9/eAX2Zwa2vLY97ueJKvYKrZ0KVB8Z9paG7pKY83VcbuoRblu4VLSibIH+ltH0f5FOZSP6VlC/6g+3FtzFZf96geEynPN6btD7xyW19V0H+CfXR/Le26PlaLR+9//12xQEaFuedho7yizhXGzpxOO8BXdV5BY9LKYN57zeynFtGRh8QmnvF1q2Zr+lo3Ke9Zux/WHmGcWd5/ijgvHEe47BdQJyPGxy9R4M4n4RxqXVj+rxaaa/wclut3FcwtuezgVxorlIe7/MqW8HDur4Q6I2c9TZviBqZflLOjrPvIbyjvZphbNCNKg/It3K9Wco8ME/3d/ROiY+/ivQhX+v/riOcB+eH74t/TetgfJWBibWrfArOL2vNG6OQPzsm/9tidwkefBuEViPJ5FbhE+V+m5S5KVqG2/I9+RfL3A59OrsC3g9Mm6nfIm2+w7T5TtOmH0Nfqdz1DuNe6Selq/+urPXHX10t+i+He3cJrcU6nudBrK4=
*/