//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_IMPL_STATIC_BUFFER_HPP
#define BOOST_BEAST_IMPL_STATIC_BUFFER_HPP

#include <boost/asio/buffer.hpp>
#include <stdexcept>

namespace boost {
namespace beast {

template<std::size_t N>
static_buffer<N>::
static_buffer(static_buffer const& other) noexcept
    : static_buffer_base(buf_, N)
{
    this->commit(net::buffer_copy(
        this->prepare(other.size()), other.data()));
}

template<std::size_t N>
auto
static_buffer<N>::
operator=(static_buffer const& other) noexcept ->
    static_buffer<N>&
{
    if(this == &other)
        return *this;
    this->consume(this->size());
    this->commit(net::buffer_copy(
        this->prepare(other.size()), other.data()));
    return *this;
}

} // beast
} // boost

#endif

/* static_buffer.hpp
9Tijzcs/v+6+/AO9v76pT9tWD9rxY+34zHZyz6HLN4fKl1Zyu3n2crQRmPQ6tgBGASNpD7CVekfJe1vokhC+9jzMlB+dCBxFuw1jgVOBF9JOWQHtlC0AlgFrgOW0y1ZBu2wu4C20y3c37fI9ClwKbIfKlwETgSuA/YEraV9tFXAcsJp+DW+mnYhbgMtol+1KYB2wlvbZ3gbeDvyU9tminJhDwGjgncBE4N3AVOC9wNOB91GeNsGzBvOdU0ubtjHcNz1A+xYPUp73t7Q38XvgEtoLXA58nPb/ngDeSHuCv6IdwR3Ap3j/e4AHaEfwKO0IOnSdIN7/n2lX7jngJcB9wFLg88AfAf8CvBr4IvAG4AHgNuCrwDrga8DtwH8Afwd8A/g4sAH4JPAt4B+BbwP3Ad8DfgR8X78/3P9B4FnAj5X8NNcgrq2+8tN9aV+wH7AXsD/t+A0ETgYOAmbTrsjLwKHATAfoPrGXQd5rI3tcnRZ5SmSPq4uimpI/Pmm5Y3uZ48DyxlnotzKEWoSdn4Rli8O/8O9Efqfo/H9oc5z/U2cfL2Lo7OO7nx/TSv+/wXN9aDqT3HyAX6Vg/Q3AB9g518gHCE3fvtamzN2mMtEqLdhyzbYGs7iXH0G9wmy1lw+se4281v7WuL9fbNivT1H5U2x1asslfaDEs1X+JFsd2oWS3l9952WzPqP+5qSTtENn5fPC9/s70183VvVzIe0PTGM/n8lvpoYc1c/qU8nuO+kbyZvCfvfQJtnZ/WN6V9VPX0l8kN13EvIH951kzId7pr8G+QaSvp5ykn19orqyYZt/p1Zm5zb5tmso3rD1xy+v+urLx9Jm1hYWaXbfaj98m3+yvnONLnGYvxFHU9dyDDCKNvQ8dLuboBtHuvGkm2CgyyZdlgXdVNr6nkZdzemKjs+vpPnTnc9vjEzgmbQpuAX3vR/738OfRAUl4xSsvqO9nT/5/vhe2PqzsfMXtvHXjDb+Wn0K+34IoxFyPg1/h4V/4V/4F/59X36n6Ps/ozm//11j9O98FOo2/6eu16vrsEw2fKi6nn42r4tlOm/+WnVdTP9pSbze6L6ekTt8qNHunErPPofpQ9OZ7uU13GCQObjHhi9QO8fAF/CUEiRvwFN2KxtbfHWmsnEHIZSdwbLzbMreaS4bBQdXrqfNu2zK3W0ql4MXYps7RtjYafSWzYEOrdwym3IbTOViYgVZrsdmlBbJFPqReIu8ncYZUi77NzB/B/nNZ/sX6vG/2MmGIL/Z5mFXyb/fzmYU8pttHiZI/r/a2ozqJOnPkd9Dehubhzem+MT/RzYPPWPSitvXwwjxRjuUMzkmnJscFbsxQX6zvcOLJP4H7W57e4egMds7nCPxp7Sd9vYOQWO2dzhzJm0kNmHvcKrk2ac9puwdspwm7B1eqtpvtnc4ZWbT9g4XS/pPbe0d3vQds3c4iPNgKx/2LeQHLtfcsjdjvc+miNy09o4/x555wAeMJ780X+KXacn4fziCr8wNfb6TrgRP2ll+cjbxlGO5VPJkwZtItHYGAuVtSJuk5Ft2SjzGV/5G+ZO9WNIXopUtxZ8x5wHL6UqeoUd2Ijg/IW3NPEPyC/3lXMZayLlkGuVcfJ7JnNaa/LbT9uTVfCbzZslYcE0PvE4iv8n25EaJl9g9j8hvtq131Syz7clDs5q2PXmFpM/ms8rylO1J0jdhe/JySV/NsSF9E7Ynr5P0xZa2J28OUu6luW1PemSS6ujvfZgDbaKsQWfUszNbjeGCoiq45C0fnKvPlNz8chijXGb1fJEmXfVTg8QjxHdR+zizLNsUlb+fGvdXJR7tzu9ds5Q/5MHT9fRarMSThIeebuFTWV8TXpE=
*/