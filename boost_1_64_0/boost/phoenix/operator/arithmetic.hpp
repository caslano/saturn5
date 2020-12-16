/*==============================================================================
    Copyright (c) 2005-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_OPERATOR_ARITHMETIC_HPP
#define BOOST_PHOENIX_OPERATOR_ARITHMETIC_HPP

#include <boost/phoenix/operator/detail/define_operator.hpp>
#include <boost/phoenix/core/expression.hpp>
#include <boost/proto/operators.hpp>

namespace boost { namespace phoenix
{
    BOOST_PHOENIX_UNARY_OPERATORS(
        (negate)
        (unary_plus)
        (pre_inc)
        (pre_dec)
        (post_inc)
        (post_dec)
    )
    
    BOOST_PHOENIX_BINARY_OPERATORS(
        (plus_assign)
        (minus_assign)
        (multiplies_assign)
        (divides_assign)
        (modulus_assign)
        (plus)
        (minus)
        (multiplies)
        (divides)
        (modulus)
    )

    using proto::exprns_::operator++;
    using proto::exprns_::operator--;
    using proto::exprns_::operator+=;
    using proto::exprns_::operator-=;
    using proto::exprns_::operator*=;
    using proto::exprns_::operator/=;
    using proto::exprns_::operator%=;
    using proto::exprns_::operator+;
    using proto::exprns_::operator-;
    using proto::exprns_::operator*;
    using proto::exprns_::operator/;
    using proto::exprns_::operator%;
}}

#include <boost/phoenix/operator/detail/undef_operator.hpp>

#endif

/* arithmetic.hpp
t4TGYl+sf7pkFEnaLIpv8uZnmNmrEgmJCL2SlEspZbZhnyT+CgGmt2qJKXu9wJN0QjyCb2VuEe3ELmzuhAtd+HstscjrFSPshS7C13vAI1O+Cj2BvGim9vNR1GNchbDLVMxFSVSSFwHCThqOZuo8D01dGYOHVNpZSUPY0HgRlVlM733+7+v3K7CiKm47mEjw+waqk+nYuav/9+iYli9teBTPC122E4IVnclhdzLPbrXxsDDHtsxu5Wn+ZNzJPBnfo0uW684y1EGwC68rmeUuxVABsGv6ArtEAyswCI9CB9IvyYjOsMwHKI/2al7gD1trT+AcQnksOggA/+xU2CHvDIdC6zwYx/ksb5JmO7zLRMm2aXCMGgN8rgBscXZylvAnHJS+dgIZYfZXuzrbKgcc1PJzPsVicos6OI6OVd+X7ph3IJ5q2dbcrAjQ+cmc4hK2Jd+/wjo3SSNL/kmN7Gwl+WU3na8by021AAmC2wbhVg3hSoHQu4Mh/IQgoBupiEHl1lEb3Twt2FCAWnYqnY6aP+lDMGL1XgPf2V80b4cpBC+AOsWg58DEHuqgfiF+iEU/ZHmJHIv87I7UW+zKaP8jgrW00LyLmu0jPIfGnV/x6Wvvf8Q/Ch7D5EBgRah7zvHlyzY8EmXrB1SZh47GwoZGD/bfZTsH3MYzZ0OPLNQwrtC7+/XdiDpoI0qnjF7/yoQccZKBHrojcZOKYBk72YGfFLjyHuu0JghMZgT23Iz5C38s+e9D8V679toI9ROHRAMsRYKHdWLKTOsB0WoV+9+0iR9/wI2Y/zE1Qksq93sIs/ONru/8Wl/1/3yCJcR3LNn/Poj0vcMi5RyBTXu6iZS3UU0tv6CaxK/Cwf41BmPKfuVmM64v/4NpxTK3cqZxbAPAyuF2PvVz1U5Ux3SHrypyoGa/WyyIvEhCm+rpeUiADX5W/Eq6Jq3zeLes/7QH2Zl0spHeBBXcFuRb4gEqBmdB9iCSf8VQoAyuslj2Gk/d74L9RI5rRF+LZqiCRHQPCOTj0ChlzaaViAF7h1vrUqzWDKWdKJndMM3tmlrEoxmpbqUupL3jEw/uC5nasSLNX3wjJ7t4vU87vsIadcM45sbiAyWeQnh9PovZw3PzHRbe2dYqKi1i1eOS6p76HF0jNWY6/M2fl+/Pcul5JWM16iMeqw6DJXF6V4YoeIyDS+Pgqu4BHJJtx+ZRZ1xUuxYZfPzOyfcP7lvRM91c0Y/lyHkRQFxC7p3qDd0HysaeDOwr+QdjUXMAYyE2+C7KAiVUVCGXFuvT/HKz+Pj1DjLyl6v9w/35ghgFnhPcDla4vUl7dE/zDg+PTxMRy400Trl46z9hy6JkL4+fgbhLDxEeT94hPhwG6vvw4bXLxIVnFw3f/jZlD76qMiNvKuswoPRdMITIczi1DzNLN1fWAy/ZGBQUZzXjSWqeDGwmAfOgW1Oce+1Lcup9emZEnwTYEKyQgQvaD61UaM8f7j9Jd9Z2q7PAdxR31qOQxq502mrXo8W5JbV/4Ze0XITvOhzutsodiXPvYw3LtL4z5HYGHJ0JeBWUt0bKt8LNUg58bTdyPr53C0uID9OeCforoJV9gZ7MQEV3zRftD3ngS7ic8f8P7Se5tP/dYz8v9MKnr33ITmhoDDYDZcJ5EF6mJDdOold+/W9W2Lw6Jym0yXOP2lw7UTynTCIO4cJxq/C4D63CUyGj0j50124z4BcUgCUk1zr5+kmHVWAIFvgN0ezukYsclB/IZSOx4TGe9j97R+cnl9TI8DA6vuDwPuicbVq5n8C5OYNakw9ZkxFx/8PKeh1mpanPjt5W8dR/xcZ4ncdTf/r7PPXPRnJZ3qWYjYBv9+vp6ZU=
*/