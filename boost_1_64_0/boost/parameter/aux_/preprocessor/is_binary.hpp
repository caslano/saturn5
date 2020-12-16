// Copyright Daniel Wallin 2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PREPROCESSOR_IS_BINARY_HPP
#define BOOST_PARAMETER_AUX_PREPROCESSOR_IS_BINARY_HPP

#include <boost/config.hpp>
#include <boost/config/workaround.hpp>

#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))
// From Paul Mensonides
#include <boost/preprocessor/punctuation/comma.hpp>
#include <boost/preprocessor/detail/split.hpp>
#define BOOST_PARAMETER_IS_BINARY(x) \
    BOOST_PP_SPLIT(1, BOOST_PARAMETER_IS_BINARY_C x BOOST_PP_COMMA() 0)
/**/
#include <boost/preprocessor/punctuation/paren.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#define BOOST_PARAMETER_IS_BINARY_C(x,y) \
    ~, 1 BOOST_PP_RPAREN() \
    BOOST_PP_TUPLE_EAT(2) BOOST_PP_LPAREN() ~
/**/
#else
#include <boost/preprocessor/detail/is_binary.hpp>
#define BOOST_PARAMETER_IS_BINARY(x) BOOST_PP_IS_BINARY(x)
#endif

#endif  // include guard


/* is_binary.hpp
ej9XE1WgQmHPheF6b6ZNOuNYuqyE+jRR4vrtuj6goP26bqahvzbibhqhCPflcL1OSANlL2nYm1APpa1KXMd1BdGTWN8YVzPSf5OEh9pNc9SWe12ua/uyncu5Ni4f4e/WUyvj2vbLeEYqZdzUMb4ud9Z0Ncana0WtS5/RBTapjRzSqXo8rusSvUvCc1K2r2tdzdF1OVVI9oamrrbE5YP1DFPso1vc0q394i4Jzzf7FK5jDXa+Phmpc6edr/+VscFaGRv8V923x31k8qfunnDrsSfv90x5MTM2mBkbbDs2ONR+piAduNaEb/j66FzivrAL7AftveRV7mKVM7/d7KJyhSrXFXaDJbA77A4HwmJ4AewNL4Ilqr8yeq8Lr1b9HXEzVX+V6l8Kc+EdsDOshqVwORyix2NgDRwHG+BVGl/zz72he/4v0PMM0XxcqHJ7o/dNev/XqvIPq9xwlRsFg/AiWACvh4VwrKbzbfBWOAnWwCtgLRwHb4fXwHfCy2AjnAY3qJ6N8Eq4WY+3wEtgM5wMt8EpcIfKtcDr7XzrPQvs4JDvOzX9d8Es2GjaS+UKHOQGqtwgmG984zotet2H3VTO3PNwvbFHdC7cpPbeqva6BxbBrUY6apOk/wbVN1vTP8eYy96ocnkqZ85lv1nl5qrc22EOrICd4Xw7P3q9gj0c8vNe1fM+6If3wWz4fphnfKP4YbjPl9rYr+M4r+sYr47t/ofGdZ3GdE9u8KY0rttmTPcsjuemO5bbgHs4hfHbt8K47dkas42N1+pYrTlOmzhGexbHZ9uMzf4H5oxHx2Wz3+W1+uPG4+bgGnDNuN24A7hjOD8fDZbekxm3zfwyv8wv88v8Mr/ML/PL/DK/N+L3Rr7/X17VsGTFwvqzMuf/aKFlrxs61BN792DpWMPK7vLsZO9htaB6KetSVkSSYLX/rmagFcr/AoMjpZzHa7VVIbv0JYzV73JJR14sHSrd/vlL9PyH8uzzx52Y88by73U+b6lxXt6P3lZVl37+JxXo+RNUaDLi1v/d5pKOobF03DasYnjaZWG+Vzzhco5J8edI2c5m+mf6nHWXx+tO25ZmWT3qco5K8xzxFkpJf9Q+eX5n/bVx+lVxmmmvddHdaOpW66ST9qj+ky76myP6Y20wjfRH6zGL33Mul2ac0I5rA87paLHTkXrZR9vxtBw9v3nixPy7nHe3fV417mnkf3BIz+/UjBPawdws53S02umgmIelXxZmPd3rco6DcedI3c5xe3F2cNZ9JE53+rY0z9Hoco4T5jmGn5mNDrucw7rRPMfp2WhStsu1Kk736dkoWp9bXM5RapxDLZRWfz082l5c9A819J9OPzSno8s1xtCrlkkr3Zeq/hMu+stvtL+Xq5jPzjvoT/taOUTb+1Cc13JS5X79bsxxuTbF0pXu9XuGvJ/SNO3SNKkax/SY9d8KulzLYulJ9Vov6eir6ajMM9NhJiDeHs0u52+MnT/d+4E4e+znwGs5qXG+PnQPuVwfY+lJ595hhnl92FsQS4tTyZjlst0lHS2xdKR6jxFXLsc6G2kwT55gh9JOLtfJ2PnTuQ+Js0O5USZOJWLWj90u6WiNpAMdaV8n4+rHSblncVBj2sXc0yvX5Zpqpyfla2pcuYwOmulw7z9aXc5/xD5/2tfdOHt072SkI4X7mPLOLtdoOz1pX6Pj0tNolM/wFMrnoEt6rJui6Un5eh5XPq05Zjrcy4d+z/mab58/7Wt+nD1a5B7TSY1zOz7mkp5SOz1p3R/EteNa6Uucu7PE+eeV+S73EXY6UrqPmGHe7++OtRnzxPH5dznvJPu8ad1nxOW/WduKczd2Zns/pDsHzXkunvvcug8=
*/