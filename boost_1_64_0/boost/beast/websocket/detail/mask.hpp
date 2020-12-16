//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_WEBSOCKET_DETAIL_MASK_HPP
#define BOOST_BEAST_WEBSOCKET_DETAIL_MASK_HPP

#include <boost/beast/core/detail/config.hpp>
#include <boost/beast/core/buffers_range.hpp>
#include <boost/asio/buffer.hpp>
#include <array>
#include <climits>
#include <cstdint>
#include <random>
#include <type_traits>

namespace boost {
namespace beast {
namespace websocket {
namespace detail {

using prepared_key = std::array<unsigned char, 4>;

BOOST_BEAST_DECL
void
prepare_key(prepared_key& prepared, std::uint32_t key);

// Apply mask in place
//
BOOST_BEAST_DECL
void
mask_inplace(net::mutable_buffer const& b, prepared_key& key);

// Apply mask in place
//
template<class MutableBufferSequence>
void
mask_inplace(
    MutableBufferSequence const& buffers,
    prepared_key& key)
{
    for(net::mutable_buffer b :
            beast::buffers_range_ref(buffers))
        detail::mask_inplace(b, key);
}

} // detail
} // websocket
} // beast
} // boost


#if BOOST_BEAST_HEADER_ONLY
#include <boost/beast/websocket/detail/mask.ipp>
#endif


#endif

/* mask.hpp
N1QJv7iZeDrLcz9WS7/TuNYM5kh6fgu714cSv1kfulfzrIbsxz+rk6Xn4YyGNZ+2/WWHXe5t+MesP35O4r4l7Hfu4AzcjzyDu+bBDNI6QtLawn2/9s79dsBDEt9y9/3airvmwxfP2u7jiz474e2EvS7h73aH78g/Zl34zN22+4U0wKG+cfTHbyV55rywXS4tKnvPZLniKV2vqWWdJuk5YtbObRT3hCJlTNyyDuBqcf8unEjcLzWUWYjsrBmT0mfORb9DzxBchB/iFD+vuvzknZtr0rFE/JQz51ItE/tR93O3c/I1FR4Q91XEKXWEn324hNYTXVMUED9LYlxxdOAf86wJ8qypvs+2G39hybf88K1812uE/Wc2KXiyVoH5O2YpDfhyzCXFmFERpmG1AvNMQoG5MKkg3m/5uw7XMUX818NAMRu51h3zCsYOuxhjy6T8YteQxVSSZ0PkZc2aJN8ZN3EdmcJ3RpUpXNtil6dcyxX7Duy0Y7PubLexT5A49mIn77GT73qGTKbkmWVRzmK/SO0vqf3WCPv2CHvcM97wrbC73c+IsM9Uu4lvt9f+XoT96G5v/LWe9dpTsbv9Pxxh3xdh/8HYvXJ+o67bfjDIdyC4Cu7ET9o/fOQ8qxKLkfMapqWRGeeLfUnQLatVvqvfZuZcq/PE3jOYGGxqzrV65HVZ3+eV0ypb/yT+/xxUGa/xNS4qi7UNzRb3a4Mq59X/yb7ntlaCm8Q9xqyjyhf7oGAbrmVbsWYd+deSxiq6HjhgfSb+KgZjrbcCiXJOq3OtKtd+CxS28TkzWQ1iZM+G12RNg9o5BVTszQJOfzBU7Ju94dsVypnx4r5O3FsY93Rznm4FSefjlH1Yz/hinZ5cS7Z8ZaKWyxXip6mJJ07uExsIBoKR5RQZr5G9tSTMp4Hi5Gqi+KmidnqFgvuYvqGa2L/0Pl/b9KL5ZfJn7IR27YlX83eeuKdZHZw8NulsYGR5nvi5OlCcrJ4jZbk86LpPJvcx/WC2xHFzQM/rQwYXmheSxESTx+rulZc5x5CXPINHXq7ykZfrIuTjpgj5uMVHPv71Na+82YzdLU/einD/JcK93+te+6QI+9UR9rux+8mnBjqKtc8VSIJN4EP4+fp5H/k0acKMYuSThmlpZE7tPba9bJi1ln5jUPVfw9ShcuK/WrgrMiBSpqUZ/8g0HbMmi/8Xg41svTU9W/GfL8q5mpFyyui6VZMw8eFW5ILKKo23sRVtLHivhMkMFRnbaToukXtOLpoGlR0vSfjh7vBt3eOPR8X9jJBnXKYyfqS47Qz5yhDN97PFT021s5pM7HFGPswS+8Oh4uTDJPFTxTxTqjzDaeruxFnd5xm1XYr7NvcztnPn0WcviH5P0fAqf56R8OeEosmGNFhF/FQKz6LtJ2vb/zYhenuvp+MojI6fvNdGqZ8U19gqRYlROXFsfRBbTvA8BXIiN1fPai4qJ1ZEjKtWueSGnsVXRE58uccrB077u9d+E3Z3O38hwj3pBa+9VYR9EHZ3+Jsj7C9F+D8c4d7vRa/7ggj702pXuWPO0t+mC1hbYyrqWr29/LP/PR+5Y6p8NNmj4YilvNY/5Ixpv0dtN2wqd9RvLUvbm0vGqJvqDA3D/qPYk9Sv511W/Sbqekvqothre2WPR39Rw+j7KXWq8Oy2pJKvo/fUK10ryDObepWGnbSa/mi02p3+KMNTz7zlEl9ZdfZ1DWVtzCvcL2W/b7moGIlaLhqudpFyOcO4VTb5117tnnJR+dRG3JK0nJywCUXyWstG3RuZ/K1f7dg6NrrOvUj+donI31RX/upazSL5OdLJT12vfSqJaAzrwNV2//qYT35OyZqTPjAnd/Y=
*/