// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2004-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

// Inspired by Daryle Walker's nullbuf from his More I/O submission.

#ifndef BOOST_IOSTREAMS_NULL_HPP_INCLUDED
#define BOOST_IOSTREAMS_NULL_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif

#include <boost/iostreams/categories.hpp>
#include <boost/iostreams/detail/ios.hpp> // openmode, streamsize.
#include <boost/iostreams/positioning.hpp>

namespace boost { namespace iostreams {

template<typename Ch, typename Mode>
class basic_null_device {
public:
    typedef Ch char_type;
    struct category
        : public Mode,
          public device_tag,
          public closable_tag
        { };
    std::streamsize read(Ch*, std::streamsize) { return -1; }
    std::streamsize write(const Ch*, std::streamsize n) { return n; }
    std::streampos seek( stream_offset, BOOST_IOS::seekdir,
                         BOOST_IOS::openmode = 
                             BOOST_IOS::in | BOOST_IOS::out ) 
    { return -1; }
    void close() { }
    void close(BOOST_IOS::openmode) { }
};

template<typename Ch>
struct basic_null_source : private basic_null_device<Ch, input> {
    typedef Ch          char_type;
    typedef source_tag  category;
    using basic_null_device<Ch, input>::read;
    using basic_null_device<Ch, input>::close;
};

typedef basic_null_source<char>     null_source;
typedef basic_null_source<wchar_t>  wnull_source;

template<typename Ch>
struct basic_null_sink : private basic_null_device<Ch, output> {
    typedef Ch        char_type;
    typedef sink_tag  category;
    using basic_null_device<Ch, output>::write;
    using basic_null_device<Ch, output>::close;
};

typedef basic_null_sink<char>     null_sink;
typedef basic_null_sink<wchar_t>  wnull_sink;

} } // End namespaces iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_NULL_HPP_INCLUDED

/* null.hpp
OillDQx97yxOfBzi626wv6OWcIG/c2Ir31GrjxM/gY51Ye8BD5V7JE782OLXdrfLjR/tT05opdzkePEr67h2fKRvr41u0hmidVw+qc9imM8ij6QE//4bYvMkdb64V1DykX+QfjLFm48ZdgvzMbP7aS/pp12bvbN6ldLxt+AfdlACEJ6gPWnwMVhO3sKhzeMC8nIXzpDBYRwbvWGtyrM9fo9lHhuUqcfGZY6xYW+3Uq3b7PuBlazee58c0qdmX/N1j9PjRC03jxMpi8ar7znEzbT+Zho7Or/T55lm6bExU+UfqcfCcyqd61ttHXB/u0x/d+gGVeZt8Qafa+13eYYqZ7YvmKaGI+x0d1XmlExV5lLn92yuVGV+3vcEe8yUR3yuS1c76r5KbeMyU92d84DexvvD7PW94rJN9ZL98FelMyzOMe61z+s9qo7d4s60ruZ9aIt8IV8XC59H57x5ldK7M/5BapFm+/nE0/eSeOah3uOf4+/tt9RckM+yA8jH9vK42Z1HdJ7QuZwvUcZ3CPa7Farf4Pjo+L7V/XbZ5E6Xuak22Ebt8/dttX6U9h8dIttPoMxX09XccLM/saM/viN/rfEnJ0eeH1S+keR7LV2N/f167Lt05oZ0/GvrTXMTOtzMD81N1y5Rc9MZzE2tbHtHh9C8c21dpG0faNKpdOt8lfQw0k+x887toeYm9fczCEdc9bfVV89bKv0T2rEnJZh+hTRUc5ivL3+Hlkt5ca5lQuY9Nd/B8Hkvvm/r38iy577kEd7mvss8zn3HJJ5lhGzoNOQbg9j2SD33qcAfiWQBVfrYxzN93b9Slf5Q05wnZflU325ItmNopG8n0L07dh5B1+6InrFvq2/eqPwD6Ns+d99W9ein1vf35BuHfaR+yheAcejvXsU284sTyF9st7KgZumKZjbq09lso4DTRlUrCoIRDcpERhvltGCjgMNGJ7DPgU7R2Wh2Kza68BRs1BcbVbPNMmUjaSVGcsfXBfxmO1WONPgRttKfalqwVaXDVv3ZNyc6R2erK1ux1VXebDUnUn+qYZsZQVvp/uT0odkjjr2nyzO2TKTCPhcP2qlkVUFN0dIVpeOxDcfPZn1Jn2d8T+n2Y47oYD4HFxtFssHDaj21dXxH8IdqWaLxvNxZXq2qC1/ecfiU71DrR5jP09U6s63vVeuGtxqr57Kz9t+hbaRV2/RcV6t0qJ/L93GSxAF8W+z+ALKc/I0j9Tdm1FxXXqIvgdznefo85g8qz7eMtm8MtVf70Bfpa4DUUfa6WpONyeeOyeNjN6VSDzmHeFPp3G2ys84/luNbJ0sfgziuKXIMa87fyXJlew/fyzMcZ8THvsgV8yX1dtn/SDezn+y+UafmJ7tvVNt9+SL5yTakmP1kG0admp9swyjvvm4No9ru6+bFT1Z8VnFQMH+Hp3HUqX+Hp/EU9k2k7/BU9jB/h+fYqFP/Ds+xKPbPsVPYP9F8hye1p9n31cpsm++rldn2fRLp+zEne5r9QlMy2+4XmpLpfV+kZLZ9X0TjF2r2w4zeX9Tstxm9n2G0fpJmf9To/RV9/7SXH1r6eu1fDt7+15e6PH3blHXPbIzsv2r2z4z+Wybt5c9p9reM3k/V7O8a2Z/W7CccyR84ev9bs19oRL9f5ReqXhYR2f9T3R/YGKe/j6L/fl/9HfIL1X+rc/Fk9sco/v6n/H2O+H826vu2ci8aSVfv21c/9T2PePgZqO5zwRFwKRwLi+FMWArnwWWwFJbBy+Fn4Q1wBdwGV8Jvw1XwEVgJD8n6o7AWxlOHNbADvBJ2h5+HQ+BVcDy8Gk6T5RfBL8LL4DpYANfCpSot77f3yT02ua9IO5kr6V/Qku8=
*/