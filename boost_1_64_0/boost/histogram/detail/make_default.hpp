// Copyright 2015-2019 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_DETAIL_MAKE_DEFAULT_HPP
#define BOOST_HISTOGRAM_DETAIL_MAKE_DEFAULT_HPP

#include <boost/histogram/detail/detect.hpp>
#include <boost/histogram/detail/static_if.hpp>

namespace boost {
namespace histogram {
namespace detail {

template <class T>
auto make_default(const T& t) {
  return static_if<has_allocator<T>>([](const auto& t) { return T(t.get_allocator()); },
                                     [](const auto&) { return T{}; }, t);
}

} // namespace detail
} // namespace histogram
} // namespace boost

#endif

/* make_default.hpp
SG5vyJicskZTNtdbbi96GbFANuEDoStYrryGGucRgyfpZbWCmjfcMuKF1WJSnwt0fefjdyXpXv6JCSUdUThC5JQ1vIkoko6YoUqb0v8tY2dT33iJmbnKJRybqi/C+UoC593ExXmBzOR0lkykzBHWAfva31ERPDhXOuuzr96CV55OiZ9KLy8k2j+TgbkNNXBX9ddEOB01hA8X3ARYg6v5azhsNaXnRsfCHqGWekgB9YnbWEfN9JFzYjF8NRdB6yzIKbUOMeVOvUyW2ETVBC4SHoXFIwvRNfnFe1Lx0296dkCNpR5A9L8zqSgzEY+vcnlOXgPnF89FWBCdYopXv6yPivjsXv7/dR+pf1wPPvlWZ7oS00whb95O1aH6RvxxDp9dIqsWL6SqJE8h/OJbtUr20jCgkKKhzyTCNil4rQOoH33dL9JAQjol3GvMFnbMN0rSKTbXJAnleaksMj93fVrPj8hX+bAl5+PkYra/zokPFdlSgyPOeiboyXl+P0a3+aF0WW08BWNgA07KTaNTCa9MUEKRhrHelhp61rXp/NjV70P57Spu/zxgyXWUHLF3LXgUrgN86NET7BU4xdfD+kVZDXNM7csi2yCM3ZOboF9k1xhN8LBsgg6gpFFVZRP8VLWCr95E3Tfg8NEUvogL379CLdw4Wl2RU+3hazi4AsHP0nzaW3hUjIJCbWny0nAkxkFfqkUxfD8tbI1PRpkfullvevNo2cAZGiS+QY2zmhwcTkdaaFWXMoMUMI4S9wkafWTAML56qxrN3GRWYZdwIYjnP4G2CJ0nxMVuLPzsR9AGORs9QO0rZKNVHVrD4Tnbi9P0yelHeW+K+jDFX8sSxMkF5L33OJY1a9SMnsfMLLlF80TO/8azerGU85dHkCCfm2ARwVKbJ4pijI4QUw1KYRu71cIhHo8YmaDfV3xurF4bHqjIUyVdbtei7CEuzksXKSkeKm4BcjSNHDTypA3331LbHHq73jZHiIIqbpmuTVEkAb84nNACN92YmVWrXwc8Ms3+IDTKCzpPxPNRtVKGdZOlXqnCEB/h1vhiq1iDmQi8vs1jYp21QEO/HIcWDv1tVFL00KWB7xg6Jakwga9JtebQQjX5RGya214a+IGB+OUkxCcMRCT92nTiI3cq/X9mmpqS5QZ+YkR9KCnqp1TU8ywTyg+fofI3W/gKlAVWkTmfaK7GipLSJC11uBheW0JqbU9UjUVrnoMQFN+o6UnF92cqvuoHKXINIiOqwjw/+mPnUhLWc6H/lKcz/aYvUOTmW8+RvpfXJlxvgcigwNOYwnCvfkWFFLXnUdWPxOq02GyQB4DXTX0iTYKp+3vKLE8c5apJ4hV1xiTxa1RTv+dp0cvXGzE+i1CNmkDPeDF0U6C3ZgSOMtZPE1g3A0un9nAidBJCFaFn5hiESijY2kRJzJfISoHSamgUHEuUTHUGxEr42YxfnsA/ot+EoljbBQKtFwVygdfaI1DE6L0S6L81GRy2jTkeN/LPbDk5/4QxmeO9DAyVfxOxRb1uOq1wr+T8z2Wsnyqs+lv1lL+WlPILs9XUsiawgPFXGPjDtZpMPcX1MsW1jDHbwOijpzhJhrACNXNOnbblHzpu9U//SP+sdmw9eEjicjG9hJi/5E5a3b0i0GbusLr7FdkFLLmTywfeh2bSMTk/K8Y+8WXc0pOYEbYbUR9Milouo7YMlTPCfJoRXnQmrvtI5MrsJ2eEXz0alzNcdX1zO1XnVJsXp+qGTROWClIqaKR8a2lBwGHM8r6YRGzXHZJYI16fcbI08ODgFltYunhxOC8w0IisJUX+vB75M1JYi4g1Shzal4+vBQL7xaKfW4nKzbSmZkwV+VLtmWM=
*/