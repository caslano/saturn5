// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2005-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_DETAIL_NEWLINE_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_NEWLINE_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif

namespace boost { namespace iostreams { namespace detail {

template<typename Ch>
struct newline;

template<>
struct newline<char> {
    BOOST_STATIC_CONSTANT(char, value = '\n');
};

template<>
struct newline<wchar_t> {
    BOOST_STATIC_CONSTANT(wchar_t, value = L'\n');
};

} } } // End namespaces detaill, iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_NEWLINE_HPP_INCLUDED

/* newline.hpp
Vc2Xt/1U9x+V+8st5Q+hrRu3OkP500mOfdYB5V4Ku4afp8bNkGp6Dk+2zE3Yigzm71UZhJMwXQIr0BvYMXRtNcffE3Jd6V4q4/hbmNd70+P78N9j3q6kmZzD9pzTttf7+2YGOS+25JyKO/bgnLJHxJjKEnT5kQ/r+O8s2iAtCYNzbs+C8vLSpQtXlhdFzusmROZxMi3j38dWdDmn97EtL1XDrszj151uB9T4dTWQwDh+XXT1t9bLElgDTtlcxdG83216xH63Osx6/HhApYMKW8QclENJZptXE9bo+VRO08dn++oEbF+doO2rE7B99f+Q7cNjNkpkLYPbkHCf0EX2uCGxvV7vsG73Zse6nCVcqZv70KuVfU9n4mqcz4ab7vE5zO3ySAetq/esX8jWw3Xl5V/V9XVWvug4ykFdXloqPN3lmBGo6rilNRD7t+Ty5bLPubM8m2cfh/c3j2vsJuMtW7nLJ1lDVNnHPUaIOLvG2R4RH9rREZ4BW8MW3F/ZSqdBaMzy+KJFKwqLosZE9pB31g6l7/dP4426EvmlNYZ+2UVqj37CJO619b9jjeT7YQ7fKEY604frxrmmev7onLb29cnMi2pmSjN9f6pj7Uo77zjTpFeKWtvD+Cxxv3vMiD3zzPgsaV39Div6DsW+9udedX2YNVTeiWcm28d5wel88Wrmn2Cd7W9lFfqDVstAW6trYLxVyAPyGyQ8vnR2O1t/LiEN8t5LUmGo4b1h8x2Yqv0tx0b47Ihjqro3Tb37D6J7QIXl+aRUPaeRZXzmR85r/FjZNlm/gx9rLXtbi+2XqeMx1kDZZ/sUFZ8aQl/EXkxX8z0ri297Xa2/+UZYPfznWKv8S3z4r95/1cr/N5Pcz9IYiesP1PVDSfOI5TXIDt8sa7j/OOtB/2SrR2CudRW+PByYYaUEe1uPB1tZzwfzrcuSFlo91P0+se204FR6x6/zn+kLBAdZOcEUx7NbpPyzw3OA8Nyv/Dui7JHWTV1fVcJksfD4tf3omOai5igbtNTrFVW34Zgdm2aTPt+x+tE31kbn1TdUmN7CMrl6XujPlY17cr/bhqk+7MeeanP8df5epP1NbyNzYHX6rV7gzNPt2oTnpI5VdYuQu4XBRdYUhw3U2qnK73T4oNh8mtQvP/AlkffUfBaxh57zoexWi7u71T3vJ7nn0PaQPPNDdb2NfxZ2uAy5mV7P39ITGrbX71S4zgocx9etZ9n57EM6LVLte7Utvot1l8szQMmpntUreIoGWRdYKSochwjHXuXPn0k/Ve5KeFXZq98FWcomN3As+7VrP1q611zQdrywrbKzTsO3lRtLrK6ONJuk3Jjv91O/3Up+f813rdSXw89iXT04v53S5XoL6xypw79K+F9S4X/F8TxQSDnCsUrFO6DnG0xTx/0lbuH8PinY3uoeVDr63FTlx2H82KX8+AAbydhztQbx/IUrCi/V/jyh8nM7K13Sr0QdvxZsZz0Q3Bdsqc534Hx/5fbjVgdsud4KYgvOa3uei2YnX47vQf+/AgutdCnry5Vbg5JGUo+/ykp1rM9QqgbLDRQb7VThXJY0FXfLkbt49u8ItLLeQ74IJFFvWOyrs28Rt5K2kj6Tlf/Tg9MYHdCCsuJcfzNrMSmzPxB6/7+BHXowD7qcOsaGtuE52GsnJ7cIJAeXJbdMsjz245d7drQNz8NeO9s9Dzvsbg06Vyh3rxliu+vLYXJ3Pe5iYOtK5e41Ew3zu5XO4Hba3cO2i6IX5VZenVv73W79leMTrYi5mrquMSsj8u+r5LhZekj3TWjLe+2dErvOcrW6Jv5lhLgGNmuvqXTX8vc1yDppk10rf69H8BM9pSNhCLmdh8w=
*/