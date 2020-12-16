//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_HTTP_DYNAMIC_BODY_HPP
#define BOOST_BEAST_HTTP_DYNAMIC_BODY_HPP

#include <boost/beast/core/multi_buffer.hpp>
#include <boost/beast/http/basic_dynamic_body.hpp>

namespace boost {
namespace beast {
namespace http {

/** A dynamic message body represented by a @ref multi_buffer

    Meets the requirements of <em>Body</em>.
*/
using dynamic_body = basic_dynamic_body<multi_buffer>;

} // http
} // beast
} // boost

#endif

/* dynamic_body.hpp
oKH2gIbaAprSDhBrJEZj2Rox/5+K+5YHGg8KgM4BLQOtBG0AJZmJRnSLbtEtukW36Bbdolt0i27RLbpFt6bZYkHT/377/7SKqVMPn9QEPgB2fH9SD7HbU/EhOf0LmFef9YGweuaEZ/3K8PoZhznqs7PC9Tvrqzzrc1T9Bs/6AlVf0jO8HgGXqr4mpH5Qf/f1JfUKrXdfXyCs3n19K8Pry1zX3zu03n19VWH17uvbEFbvvr6SPq76/vkD3NdXE1bvvr6kvqH17usLhNeXua4/rN59fdn9Quvd11flUY/rE/+RvEz0cfpK3N1Ms15BivKVCO3EvvwlkGeC/hKadQt0+nGRfn0y7GPM0xyjUH8MQMOOsVZzjBL9MQr8XofdFoVxmpwcmmOgQRukf7FGf0CjHx26Qfrxp7cvkkb/jMMapr9Uo78qRD8HdIP76hMa/Yu99Teqr2YlaHyTvI/RqL56juYYK7yP0ai+ul5zjJXex2hwXy1O1KxV462/wX11mUb/Bm/9De6rLZp76zdS3fr5cG5wXw1o9Cd5629UX12tOUaG9zEa1VcLttH8Pngfo1F9tVpzjELvYzS4r27S6C/x1t/gvjphW83vgrf+BvRV5rxhDoN19Jl62V6voZXoV7rRRyOv2dDK7XOzRMqP6NdsaOX2ubmB/No1G1q5fW6ulfIT4bkJ6HNztdTfQ58bytPnpsaZG52+HjVSf5vyeyzqpPzeFLZMCmKrpC3pR4Pr4jo/n8o5Inasl7sdq5nLvorrbgTsXBRtXO0o4zSS7xRkXDlLOra1yhN0a7GA3+2fmi785bq1WMDv9k9NFf4yU5djop3UH2SyHSnfLbwd2S/6Cf8eppdvVSFwZ6kfjtxZzxk6nirh2YB1aPcL978iT/N24EH9LugvrdhfNrrWb3H/3Q734kfPfcz1s0V8KeXehqx5getqwD5nv5vNpGI1oEzQ+Xx+JIX3u4II/Y4yfVW/GCrlk3TPD/L3Uv1kJynP0z0/yN9D9ZOBUj5D+/zIa+Pyq6R817D+QN8vj/5I30ORO4b+tNJPXH0gZSvqA862LWnj3bbZyWFtG/G3ATKutj0IZW3bkt/ZtgegrG1b8jvbdr/k+tt2vNSzbUW+cW07Jbn+tm2zlbZtdrvgwb8A9ZBcCvy9aOduW7wPRWzboEyuuidd2lvlW3VtS/5s9XuRIfz369oW/O6+s4PwL/ds2z0Vfy/VF9KE/yHhn+OzbeV5InIXGnauth/oR/sN2/YX0JKUf7Z952jaNyMlePAzQemgo9i+NUnu9q0oizx2gzI9VPu+IeU2uvYlf1fVXqul3JNleOO21vjD02d3lfDvwva39WWy3paP0+akekn4j2B/sOU7asfwF1I/Ltxfns+KD6V+d5XX6asUqx/489dtGj/5uve/beTa8e6R5G7vFtsHD/wGaAfQY7a/dEtXe0f0mUZ7U6a7up+XSHlpuM802+siqb+e7W/Ld9H5TLO+t4w/XLc2Z12V8C2T8uGUUzklmfdrNmNkWgPvlfr+OPNYbVtfIzw3OHRMm1FegXrq+IE6nM9z+GhjjkbyMkqsxMZUf+/+nm3v4atd4uGrPcHDV5ttjfXkGOfC/nEqx3Zpa3dbz/DxuxyU2VE9K8+X8izd2CZ/H3U/z5FyIHwsc+ycKfWHs+1t+Z7asXu61B/FsWvzd2/Q77LVJy8Xud2NNLRjHNvRjoUY04Df5KZZk6/+3+SN9I319rnW+bbrfLcb7out83lfnWLt3+fZdl+NOfCH5x65rvuBS8+ccJPOJ73hPv4N9ZFvaExAQ332v7PaVX4763y9q0AmyI6dOxwDzObL9slX6JOvxCdfqU++gE++Sp8=
*/