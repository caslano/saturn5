//
// detail/string_view.hpp
// ~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_STRING_VIEW_HPP
#define BOOST_ASIO_DETAIL_STRING_VIEW_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_STRING_VIEW)

#if defined(BOOST_ASIO_HAS_STD_STRING_VIEW)
# include <string_view>
#elif defined(BOOST_ASIO_HAS_STD_EXPERIMENTAL_STRING_VIEW)
# include <experimental/string_view>
#else // defined(BOOST_ASIO_HAS_STD_EXPERIMENTAL_STRING_VIEW)
# error BOOST_ASIO_HAS_STRING_VIEW is set but no string_view is available
#endif // defined(BOOST_ASIO_HAS_STD_EXPERIMENTAL_STRING_VIEW)

namespace boost {
namespace asio {

#if defined(BOOST_ASIO_HAS_STD_STRING_VIEW)
using std::basic_string_view;
using std::string_view;
#elif defined(BOOST_ASIO_HAS_STD_EXPERIMENTAL_STRING_VIEW)
using std::experimental::basic_string_view;
using std::experimental::string_view;
#endif // defined(BOOST_ASIO_HAS_STD_EXPERIMENTAL_STRING_VIEW)

} // namespace asio
} // namespace boost

# define BOOST_ASIO_STRING_VIEW_PARAM boost::asio::string_view
#else // defined(BOOST_ASIO_HAS_STRING_VIEW)
# define BOOST_ASIO_STRING_VIEW_PARAM const std::string&
#endif // defined(BOOST_ASIO_HAS_STRING_VIEW)

#endif // BOOST_ASIO_DETAIL_STRING_VIEW_HPP

/* string_view.hpp
GsUP63OjHOrha9t7QJ6xv+yjz78o3wQij6agN8f8z06xa5E0+ikZyroJ72qZzmnpsvGVe3YN37PlqqToRqFrE9fBH2P589+6qSqD8vt8Zc+R57LG8CzIfcFxfV/oY4XGFpq2L3KL7LbQcqzI3NO01yD7nCL9P7pL6e8uw82ikR59wNirB/d3Zd3PEq4jfu/3VTPdV7cNWa99kJFNM3WXrGXTLbd7uqk+3037M0z49q73dEMtf57c0z75lqbdX9QaF8a3h9g5Oa7x3h/KGu9ixxlaJ6OD6sRuq7kkxZvQzbhTcDNxuWp+98O6/HPGZ07IsWzv9h55t5fyFrmGYleH7lH7p9Jz8WWC84cbx8gNeZE+5i/IccxK5Vr64aROJL5UKSPia65c+evg+947SIt8co1yrKM5ptIPzPuWU7wRjJfn7BW4q8h74SP+vOdb9n5D/JJ35KQ+5bzkUfIi52uZ9rJU+3tZKWKbamn5PPMsHY7MHVqmr02GNLWIP97lWqZbuc95KROxmyMef5nIMblevo5f13Ey3tAysIyWqueDrPt7Om6flJH1qK+MJk4bOyXbVgYTp2X7y0jk2hr73Lbav96tzES+mXnONtP+p7hu9cwLKjNpS021zCNBMmML7PduXy1zr02G65RyTZG0Z2mZ/uT+AjOm00IfW4yNSGc5xleCPjbCOlfVrT0+kvT1O+nIIBlWu+1u6oM45Fh/hzpqr+PEzv4Ur79vkJ/rlzr0+tfht9trP/Oocx1fV9d7QYtwsbhCqeO03/vqWJ6XDs9P6ljkUtzqVM4vknkLgXWYIu2+jZbpw/dfohzzWJfpY0M40olj5rs6N79A7Nblvmqm5PiOPU/CZoSElXT5Zs2fKm3H992p5Voig9+EG0w5dJdwvjR1ONN/tRA51c+1lnQHmPADed50lmv25dd/zSmwrZYbzXrfiXIs4JrlXbnsdhNv2gj1IceS5ZhTf5eW6o2gtpqrJRyn+npTz/qb3ozXeWS8TupZ5JqY8aRj2v819ihRbmNQEqaN3DucWK/n12DrkuA43tlLn1+t+n++95t7j3NkmD5+K2EuQZcQFzoOIc/c73V6f7Fes2q5jjWk6rjuoOyb8aXfQOpe0iB20nAcf/pRxz0fCf84wz/1sVc4sttK1XI8/XQ813Ksuh45nWDVkHGG0HPT8ak9KpQh3OD6vvfkM5NiE7xvy45jASKfV9/3Htg95B3QF+dqX5xVCx9KiumpBxjKinOvL87Ewi3BcQaNK5XVtw20921jtX2wbksO46ayToa00SMNvBG8J8/kg7i57ekfNgS00cx8NDbZE62QttpIt1WRJ3RvyngkbhJuKamIvPRRXvlBRv5VqzupDsONw92AhWArct+E+2YW1zVKjdXN5LOjt/oKqRqXwCDc2XqSUmxSXFxScoLDu0KKtLlHdPypvGPFhvaT0o+t0TKDynw/2KBlepX5frBZy3QL+Ba4hGu/FHcxbnTr8tcFkXeHkLrrKMfsz6XDG5yeK7LwP79kTp4CY6F6rmRs9NXljOlTAspM/N46FLlGbs8VOZ9q5gZeqf3fWrfzfwnuM5zTe0Oq9EWTtfw31q1c86u4T3AOzxkzjvGBlo8yfdJH2p9Jy0q2+tLfJJi08kxfM1PLfEibqsvMnVyTt5RNOi7T9+zXcrWxc40VGXKuZapKHpyfQw/pcGv0U+M2nLrvj9JWjzX02vJGFySeoybQJZQxfrNXx9GAOJVf8sW1nk7KXa2GruM6b2i5WBnjDsiDbnvhvPv430+p+zLeT6/aGPiusy7I/1SQ//RN5t0noH85epr3AjycrAeP4KbRJrdskrm4DBll6jeesRP4VnL8FqQ=
*/