/* Copyright 2006-2008 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/flyweight for library home page.
 */

#ifndef BOOST_FLYWEIGHT_HOLDER_TAG_HPP
#define BOOST_FLYWEIGHT_HOLDER_TAG_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/parameter/parameters.hpp>
#include <boost/type_traits/is_base_and_derived.hpp>

namespace boost{

namespace flyweights{

/* Three ways to indicate that a given class T is a holder specifier:
 *   1. Make it derived from holder_marker.
 *   2. Specialize is_holder to evaluate to boost::mpl::true_.
 *   3. Pass it as holder<T> when defining a flyweight type.
 */

struct holder_marker{};

template<typename T>
struct is_holder:is_base_and_derived<holder_marker,T>
{};

template<typename T=parameter::void_>
struct holder:parameter::template_keyword<holder<>,T>
{};

} /* namespace flyweights */

} /* namespace boost */

#endif

/* holder_tag.hpp
axwPT6J05gIUk1tAZM5fpczMKGobciS1cs/q24PS/MJdPlWHTKVFm/xaZKzeJpdwbTwAxFLhYczWx8SH9MsR3HfaNXLLlrdeBpGEeXbeuq58VctWSPP0oe2UxMeXUtmL+Mdvq0tYAzlYThwp+7MMlLFUpLNHcrzk48n9HOW8YNKvIrD8hb+m/WdeP15OpRyHFFrs6Mz9iTWnf38Uhg8ZAwbVVdUsnFjeW+gOaftZXMWrydHWj2VyiYFMPBfiZ8ye4q2OjZ0SiuFSLCJ/N07CIS2ra1JcktqLi0tujqKotaCIqFg1hTRBPlz9NoPqgx10H4smN43I1QlMtyRwPc6Eq8WCLacaKJKYv3EUrVlpA6g03sa7EPLYynEjUKWkX9rLQPe/ixW63YLuv0XTfXEho9trIFM2IpE3AqzgrgOij8Vyfcx/BU3ya8+MlcedANkj8KjaxNhLK0yZ0cVQNJEX7YDraidDlptnHZH3q5ALo7tnC91WDIXgTTR2YwyUWWSOu4AWVWP2tZBtjJLKhbHXkwnbhYwWxWE4vpLzYtRoy4Aoezuw4idJCnNCo7NCjp5b2ERe6KRFa1jjpTQeFZRtVZQszk9bJIUm4fFTFdjST7Olad9F7NOS534hzCzUNg5WhGnlI5i1sZ57/2AWjpd9ud284ynno+7E37Q/j69t4VRpb2Sso0grMtQxlOqQucN4HXj6mYEVUPJcXsGac7k8U9V9k8Ajk4s0efcKTahbkXR2lZbTPm2tj03q4292Ytn/l16oMKXPt1N3BHaPuawnric0XpoQroZnWM4TuaKt7MoX6XOg0Ur6xq6GWDm5ibCwbaK1DhPY/t3hGtXEJDH8wC9wTcq2xmpj8ydcYGQyM9fCDKsGWUQVk7Gl4h9nsGP4NGCrhbyz5zjuQPZcen8rC3BQNgy8KTyTHcwTW7GDeY9/p8LowyVi/TR5MA/nsoP5KDY6yt2qp5VUAgt/jWB5RrA1BOZh6zzT4rrjDx1oa3wwp6OnFwinbb0KpdO2A1ysiApl1f0G80vgJPkv/zuZ/w3gX1VAXMxmjLh0rVgfF4gMn4OuwXkAkpQYpa3E4CtNosFXSiwrkcKP8PMZRHka9grcV8MS3HlJP5l6VKaGCtjFtp5bpO0LG3iZ3RgzFDT5PSAPBML4OdzKEDaqAHRCm1DqTqVQcpBZ8zcSwxfqqD8+UTnA+EDrz5xELVyUPZ8NwDoAx6c3D/QEGplM6W5Rcjh0cHCgeJPXWsUWSCGWMW+0CxWLmWsT3Shm5QB+J8AXBW+WryiCzqud0oopaCsOpXJpsx94DrxoUJy5djzF/HE78UAGpqyKDwNhY6VBni0qwkQ42TIEs5ssixbNNyY1PgiaTwkAaYHM+XdAt8gkIUcGeMSTyv5L3BJYKMTWSCm/s1+MJuoysgrsuzV0c1bmK6zxIgJnzDTYbI0vCEEZ4TbhsiK2HmXgOGWt/zuNjPF0uWJ4nidzwQs8KT9kVFLO0s6enYAnsQV3UYkrxYevlh++mn149JlBOoACLMGGVlmaHMQVl7JHoBQH+sIAiTaIArDiyKu9i77oqi9SHbq3z2tRZkxv9EGhrJeecVkB9hGYw34gUM+rvZ/gpwE8Nbs/wKJRNRY/wF2LfXoJcy12+P9d7N7in6K7PnSeyRVupyKTlY54yZIviicFHzk/iOEgStnWqvT6CoWFQa7Z0stH/MclgJjr0wvFUC3Uvvwhomgz+3EeJtMgVqEhSQdnxhs4JG/g5LyBkK1Jg20yXAF16Wf9GiJk9XVDICT31uqPIhFhWA3leHXcXUB7KrOyXpZ5rqnwC7iq8wtd5BTdKbJQdj6HjM9Ojw0KCSanSuGzqT0=
*/