//
// Copyright 2012 Christian Henning, Andreas Pokorny, Lubomir Bourdev
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_TOOLBOX_METAFUNCTIONS_IS_SIMILAR_HPP
#define BOOST_GIL_EXTENSION_TOOLBOX_METAFUNCTIONS_IS_SIMILAR_HPP

#include <boost/gil/channel.hpp>

#include <type_traits>

namespace boost{ namespace gil {

/// is_similar metafunctions
/// \brief Determines if two pixel types are similar.

template<typename A, typename B>
struct is_similar : std::false_type {};

template<typename A>
struct is_similar<A, A> : std::true_type {};

template<typename B,int I, int S, bool M, int I2>
struct is_similar
    <
        packed_channel_reference<B,  I, S, M>,
        packed_channel_reference<B, I2, S, M>
    > : std::true_type {};

}} // namespace boost::gil

#endif

/* is_similar.hpp
svwZeSC0IRK/sxtCXsSPhOo/sp4LLFYkV70mLjyC3ilvv7GIzJ6ikdMinrsQ8uEvZPMO1e+8Hr+tQ/Xb8jdue2PcpGLy/dQEfoqK00PZrpzzLXy3ytbtTSry4ewI3a+UbqDGHPeCZamTm6HP27EaOJ3WCNV/U8Nquxf0RKssC9XPE0D2IW9eMx0FUWx1JvDKiUTH8QMWwaHKfa/3t+V3rZVm33tE9fQlKgpbiC+YVBgTh5fDcTtzCk7hRXBkqd6pKrRXuRL3aEWWk/wr1ituALRylym3l+wxmHp/12Ws+ICeaLLM4fd5nEGnpuA404jvIxpjxZPkKBRupcc+0Ae16/LvciKCjxEiN5o7ACY0VBR5Oun8UwUIulvTPiK60J1M2+4DPa3whkZzvqtBgEsXQ+T+HjEqrxGpNOrzM3UV6J/XI17v8n1t9etst8rnt+aLbXqXnCHys67gQugFCtpjPhNhbdjz31cmhRRH9qUIuEMDzLsAVz09kVLCI56MItApG8i2cxrROYs68j0Kqc2A9wlGFJhailLqiunwiXUiY7HDCJGiDlN0QAq14cm4zrlSxNZWSeoRHTkYvrj4oc4eMBe1p9KfCksaLLJXstdqh41IZCEEs4VallZ4/HtTRW+/+XQmd2ODbXPSl5EiX+Lxnzfn33WGn3JW63k39kSE0tLGOk3JLCmhf5vZAx8PxRTEKufX3CDhxebj9+VXniEsXSovACQ3SJ4V8F59XK9b45BC00630g68MG1PScuHBOG9moW0Jg3Ru7YLYMH21VcEd80KE19e+9gmvnSfReKLeypV5lHHi5VtNMBcqg6+rRTqFHBJAy71nqT1voO57JjJXHKYi4syGjXSVSNtJ2TAC873711Q2Hffq1TYy4lm+kyNPvnC6E9Ujh7F6I8hurxfVePXvTO1rDveKe8bNjsbq99M7QaLI+nkMa1ea4C1n7pbEZ4P06jaA6J5SzGIJciWYxlwH0tJxBLlq3eB/fXWtv11JmIe/QWPUzOeeE75a3oCqA2/7F2hevmDbt4PrXJNAxATnt57oRPD8h6GF9L20PJpCTq1eUe15Oy0vm/Q70kl1neXd2xVL744lv8uoKURq0gM4TSxfZBpZXgpQmht+cVpknS1cSApwh8jCyifXBnpLGBIiGv1/bIxpeU/EfJvYn9FvRu+AMwO3xeqW7iXSSlWy3TeyPn7IqKkJp0fyxo7rEjvIlKoKBVX6s87HQS871ltqOcBF23RrM8Tb+nQhyYi2xZq+zcV5ANIs10sDLErhYsJiZEnk/qgN4K/p4EiV/REIRrv9Pxxp61j9MaIzjgbZ4Rr8zC9RHbabHnTzmGh5LCWSfZjXlABQgu2wlSdkabz52xmxvwYMRmtANH0rJ8u9PgM88sMqxyfnxO9k8Yp7xhLSH+xEvnf1uJ0ekt+KTpxDbxgmnirh9gkBIFD9Q40BZhm9Jdp+UZbCG7hpEWcGl5qKZGGKlU1XsOsGK3f5uWgYV2cCajbzSPNLGqHzDszWAnXn3XUXqGV4NRbhCKe3DMYb+LbFYb3+6e114YAWBldf6DjnsLgkV1oDxIYzScXoOtYEV0vC11TAGWe/3EEiUZoe5gOQMmhXSfDz8gHEMbIva3gAwzWZS4ZXoI2EcQJ0sYpXD8bsfjjHa+pHsvWWQjqAgG40RYjENCtFvT8m9Ie942MInSbBd0PKOTZFLiTpQv+woNk3BimptjCOrBpQLG0L0Hvkxfq4s4Y4IpGev8SMr7IygEPz8j8bY1i605/3XRpC+vJIpf87rdafPLmwTfZjQXZuMSOu9br31HOX8EjSCSibW6g5b0OMUMg8t3rTGr3MuKP2YHA3y3F5I0=
*/