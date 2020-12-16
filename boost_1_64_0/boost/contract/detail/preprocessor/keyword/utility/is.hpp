
#ifndef BOOST_CONTRACT_DETAIL_PP_KEYWORD_UTILITY_IS_HPP_
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_UTILITY_IS_HPP_

// Copyright (C) 2008-2018 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/variadic/size.hpp>

/* PRIVATE */

#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_UTILITY_IS_1 0
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_UTILITY_IS_2 1

/* PUBLIC */

// Precondition: A macro named `cat_to_comma_prefix ## token-to-check` must be
//               #defined to expand to `,`.
// Precondition: tokens must start with a token concatenable to a macro name
//               (e.g., a literal or integral token).
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_UTILITY_IS( \
        cat_to_comma_prefix, tokens) \
    BOOST_PP_CAT(BOOST_CONTRACT_DETAIL_PP_KEYWORD_UTILITY_IS_, \
            BOOST_PP_VARIADIC_SIZE(BOOST_PP_CAT(cat_to_comma_prefix, tokens)))

#endif // #include guard


/* is.hpp
e+rw2p/ZeTZrNSObudwQ13PWU53W4S9esy5pW/JBUep6P0+qjp+z51qwoX7/TrE376Y03oxUuJKOTvekHmLIPo9e1PiQz/3F8/yqv/GCnkvQc/TnNDgxNjUt20gPswUc28aPXxFjPdUveqnhevAW75S9yq+Z39clzCkr7/Oa76alLxfTWDi3PzwYIVcGVIzABFzZMqxf4dmgIfp9Ubi/A32Ria6wtm4T+mSGnIt1z620kppuLXfXfUt3Zxfz1NZtP36RNz/npqMiei581/11ekN/hJz5kEeVzL+VnDD+rO1xxSocME/tweZzdeCLGBeHX7MvRh6fJQh+DwBc3Ec/N6EDuxfHozV5mAS4sgc2f06n0TZF6agwLb17pWfzLuEKHjD8PW2FCxe0NS/6qKW87FONLnOPhsFz80PtWeShi/Pw0d3o8trmKr8r02+ZjbNMDv5jRVQSR29rKLd7RCX1aAbvgs08za3gPSrF1GNzPd1yaqy0WsYptdVtIt79iW+LV/cdcVnLjFH6BfbQYGDnwjCCf8ixUW0+CyteUavbfH4Y7XxOvdEKPV5TK1c802I8F3BEYg8+zTjv4IPE/P5u7vFzxD/YwylJv9yUv+aWQS7+xp/u+SDszCesexfGvBRyFtS1q0S5Ju7rTwfqvXWDE+X4poJ/Bu86DHnvgZ5pDnpBHtd6lhY5Jf+60XURHJFWPnzhXvYec4zUE7tlberJf/UcfdGfmfkCWmlpb/N/Wkz10XNOohVz8c7w8BavMJQuezkX3GuAz4P3mxXEvRP0q/VDh1qHzlNgCC0ymjbJK2da5sCb+q39OrimPu9K3nZ5Y/3jTRF4hg/zGBcu3dKF95vvfvIu1vhT1g7eweUZ72DfsQstsJyuoEUm1OU56/ClE2i6heb8jJ6PvsXl962Hs6m15XRP/dLTM+XRXecT6I75/lsu7hVTqj3rsBDuPP2en09Rj4fo5Zz6WyUinmOjeSuqPbV16g/1EpI7jeHCKPe7oA88WRzd8wQdM8K1esKWWXg1/ge10YLmwqXladc+n7peUEfy4OfOcOQ63u4oNpXU7rtqxdy73ucL7sr/X+nHJ8TB3qrSCu0/QGs+EQWjzPVrZ6LVU1eecbl9pqXu8/0ePSS1kWwlTHwYvF8fvztfHFUveH+i65a0Pvrh+eR6ipk4YD+fdUSNjgx71so+DW32IU01TL4X7uM6P+JXa/BHduuUO3i+3T7NGPXvGlmeNBb6cHEr2mYEHmxvTeXr1/K9bE1cCGetR9IZ/jLX5Udlc33JePrxyRVoJ/etiHvmlIXdamOJ8X+6Rm7Saec/V4PwewD/2D34nRe76dMLsPsp3N3XeYbq+i7T6MOVcGMJ/5sgpl/KZ7qlxia8UIF+36qu/1W36rXVK/qhhXjxjnyifJzyDg3jvqFrOFcORdE6rTybNDAT7MHf0bRd2Y5BP03vOSXO5bE8f5f0TrRFwe9LoEGyNYAhr4fs5+Ak/Zk5tFNMcdyXQCPfp13UT6Y4+gamLVZHR+Vis9quywvkCt7XekXf1th3jqV3v6Djady6s3G+WH0Oz0fC8eCc7upxeCY4vzRPPyEGLuoTFOilRtXPKVjQHW+MS1RnOLNeRxh0lkd7Uh1ks89UjEZ8g/Z6IUrfFC/4fLRYfBcvJ2FbqTzGNRLPLQwnPWtSGre0sKc0j154tC0C0+H5ddosUS/c/V63xi+Osn4F+Go9yz7teZiRtEtB+kQ+HGuEl37RMwvhrsqeTWmKv1LjLBrsG+fZ8jU1j2fg2EYcB7uyllHbxrGUlnxK/Z9uRIfB0of6fg3ShT0vHPJOFf6Ilvirib6d52wapcGnA+lXn1tubn8OVrM=
*/