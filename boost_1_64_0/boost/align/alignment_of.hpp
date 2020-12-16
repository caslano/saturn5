/*
Copyright 2014-2016 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_ALIGNMENT_OF_HPP
#define BOOST_ALIGN_ALIGNMENT_OF_HPP

#include <boost/align/detail/element_type.hpp>
#include <boost/align/alignment_of_forward.hpp>

#if defined(_MSC_VER) && defined(__clang__)
#include <boost/align/detail/alignment_of_cxx11.hpp>
#elif defined(BOOST_MSVC)
#include <boost/align/detail/alignment_of_msvc.hpp>
#elif defined(__GNUC__) && defined(__unix__) && !defined(__LP64__)
#include <boost/align/detail/alignment_of.hpp>
#elif defined(BOOST_CLANG) && !defined(__x86_64__)
#include <boost/align/detail/alignment_of.hpp>
#elif !defined(BOOST_NO_CXX11_HDR_TYPE_TRAITS)
#include <boost/align/detail/alignment_of_cxx11.hpp>
#elif defined(__ghs__) && (__GHS_VERSION_NUMBER >= 600)
#include <boost/align/detail/alignment_of_gcc.hpp>
#elif defined(__CODEGEARC__)
#include <boost/align/detail/alignment_of_codegear.hpp>
#elif defined(BOOST_CLANG)
#include <boost/align/detail/alignment_of_clang.hpp>
#elif __GNUC__ > 4
#include <boost/align/detail/alignment_of_gcc.hpp>
#elif (__GNUC__ == 4) && (__GNUC_MINOR__ >= 3)
#include <boost/align/detail/alignment_of_gcc.hpp>
#else
#include <boost/align/detail/alignment_of.hpp>
#endif

namespace boost {
namespace alignment {

template<class T>
struct alignment_of
    : detail::alignment_of<typename
        detail::element_type<T>::type>::type { };

#if !defined(BOOST_NO_CXX14_VARIABLE_TEMPLATES)
template<class T>
constexpr std::size_t alignment_of_v = alignment_of<T>::value;
#endif

} /* alignment */
} /* boost */

#endif

/* alignment_of.hpp
jyY+Vfs68s9tVh2ehiZjehcq+VD0H5R/m1/Dn+1E/lDyeXKzgHzeCP+pu5tSEw86wzx9sUOcGEsisY9F4jxSW+foo4TdAL/qtLFSPBqvahg4NxFHJZ7iEg9RifZUTWPeQYqgTOlPc/oM8vaaJwL8Tw+SAP+Mev8I2UVOWqQuTOH+N5XewDnpHiA5hpiy9vkYgwmu+n9t6j28aUUEA8FytwDwJgHg7o4dxD7VDUDg03p8QjWf4Q9quAA1+K5xqNewott8N1LwtJT+ngy4Wt8hY/BuE1OqiSiIwkkO9dY2y8wUL9ufZIpiqEZ8Y4GfUPSMBr+ngF9B0PWbx+DfV0X51quwdgzpqajYAufPbwjEumgggGYk++ls2uyoMJcBv4TD6thWoEsOf41Sb/6dGld8LNcEng7mjgOlsYFrn8v4Sl28gz3PbmbTLeyr4m76FACmjhux7CdHfuUvV6DugqvEr/T4dvYyAzJQqiKh6FmNgxzBwQ/3Ew7mAgd71d28NMbFfo8/qHlCuMQmqGwrKvXB2tw+zIxkUW/N+on9axlXO6NNJ7zkXYAjcVYUNsNbAuMKNztrXBuDbK1x/aPu0zDpU0vu01Pcp7mHZFwT0Qk2W5/i4OJHt5PEs774+kHWMQeeQ2cL4MmVoPz24Grpxq/pxvfpRmW6cRCnK1XjL0SDey1BHh9pxi3yXln0Bw35GIF8yGRAni0TatdBnlDriOsZm1HzWE50qCEQJ8r36NgnYzFCbA8wDqqWmAN0WIfOwRN9bKXR83DH6Si4Qnns68lrQp+nb+KAa81lWRF+qK9IS1VJvlikVr3RH/fOdS3Qj6qKLJQsmqwPO4+MJB1WKzNbkj9uFmf7uqIzsr2ss/16F2cbbWaDKnAYZ1MAyL9c3bsVJLkv5tGhfombSdbuDGNthvEZHe88GkXqikXh1ImMcj6r6DbEqLwNvIj6tON4pZznSzFPSeCMRDAum04iKniacfk4vCQ4vg++T/EyhzoHyYscNHqNII5U/GHNf/xXw998VUMhK/QZZ2KKja+yKYoDYG/rwsxYuFOIqgMR1aIO1sF+jM4Gmr6PQ1DHa9QSHelkYbwE/HgO3hfMiI2yk3M5rTFfuzQ0I5XRGbDBybsA2rsg1wLmFUdVMaYFIG5A7xWNiIPkHWswqaPwrS0/VBJ4OZaiWiJl8LSsMZYub2AsSw/wvLia58U2NDnYa47kVcACVyU2YvfJz/FQ632fBrqbqHSnOQSHPVgbk3fIEPSnIbgF3glI7BMMe74nsEg2FNiLPOacfg5PAnte+4AGjnFy0ut5kL+YHqT8KB3+JNMo5y4cMI5RJ3LQ+rPUidHbxbR/VbXVncA1VYylE5Ataz+DfheDvhWFv8FXAX3FWZhAlwlffiBG2A0qbGnDhFRY8TbT5lrGlTXHdxB/bv03QIHFxWLPFIrut40fr8c6qN60SB3ejJxttkLM6wvo4W7W0u1fell6cz94Wt5Rp7fS1/sImhfKuYUcTN0ctajdOmsVygLxUtwgKd8YnmqXpUf7vWe5845EofyAWzn4TLrP9QtWcvSMN7xFfj8GFC+VPzPVN1zMfvUXFz2pMfSB5v/jic6fB64q1a69JCGUoq0P8XVRBEdpw2LPdUbSX0BmLLfA/Y2rca3xCNMd5izn9W0egDF+zUK8kp5bhXB610o4j4wD4bREP/B8C8plMuH8BV+FcB4/EyuZD09EOWHgS7VTznzqdo8NjL1v2K0OH4wvVAf+NNUl8hDyzGxJqHHHsncDHpxqz7d69dWMcbIEiGgpp5i+XM/y0dJPLT4EjI/eKVLDWEiFTIki+bjtsRGD5/nzYwM8qsMe7vM948w+f4RE6fM=
*/