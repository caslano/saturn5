    ///////////////////////////////////////////////////////////////////////////////
    // class_member_traits.hpp
    // Contains specializations of the class_member_traits\<\> class template.
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
    template<typename T, typename U >
    struct class_member_traits<T (U::*)()>
    {
        typedef U class_type;
        typedef T result_type;
    };
    template<typename T, typename U >
    struct class_member_traits<T (U::*)() const>
    {
        typedef U class_type;
        typedef T result_type;
    };
    template<typename T, typename U , typename A0>
    struct class_member_traits<T (U::*)(A0)>
    {
        typedef U class_type;
        typedef T result_type;
    };
    template<typename T, typename U , typename A0>
    struct class_member_traits<T (U::*)(A0) const>
    {
        typedef U class_type;
        typedef T result_type;
    };
    template<typename T, typename U , typename A0 , typename A1>
    struct class_member_traits<T (U::*)(A0 , A1)>
    {
        typedef U class_type;
        typedef T result_type;
    };
    template<typename T, typename U , typename A0 , typename A1>
    struct class_member_traits<T (U::*)(A0 , A1) const>
    {
        typedef U class_type;
        typedef T result_type;
    };
    template<typename T, typename U , typename A0 , typename A1 , typename A2>
    struct class_member_traits<T (U::*)(A0 , A1 , A2)>
    {
        typedef U class_type;
        typedef T result_type;
    };
    template<typename T, typename U , typename A0 , typename A1 , typename A2>
    struct class_member_traits<T (U::*)(A0 , A1 , A2) const>
    {
        typedef U class_type;
        typedef T result_type;
    };
    template<typename T, typename U , typename A0 , typename A1 , typename A2 , typename A3>
    struct class_member_traits<T (U::*)(A0 , A1 , A2 , A3)>
    {
        typedef U class_type;
        typedef T result_type;
    };
    template<typename T, typename U , typename A0 , typename A1 , typename A2 , typename A3>
    struct class_member_traits<T (U::*)(A0 , A1 , A2 , A3) const>
    {
        typedef U class_type;
        typedef T result_type;
    };
    template<typename T, typename U , typename A0 , typename A1 , typename A2 , typename A3 , typename A4>
    struct class_member_traits<T (U::*)(A0 , A1 , A2 , A3 , A4)>
    {
        typedef U class_type;
        typedef T result_type;
    };
    template<typename T, typename U , typename A0 , typename A1 , typename A2 , typename A3 , typename A4>
    struct class_member_traits<T (U::*)(A0 , A1 , A2 , A3 , A4) const>
    {
        typedef U class_type;
        typedef T result_type;
    };
    template<typename T, typename U , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5>
    struct class_member_traits<T (U::*)(A0 , A1 , A2 , A3 , A4 , A5)>
    {
        typedef U class_type;
        typedef T result_type;
    };
    template<typename T, typename U , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5>
    struct class_member_traits<T (U::*)(A0 , A1 , A2 , A3 , A4 , A5) const>
    {
        typedef U class_type;
        typedef T result_type;
    };
    template<typename T, typename U , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6>
    struct class_member_traits<T (U::*)(A0 , A1 , A2 , A3 , A4 , A5 , A6)>
    {
        typedef U class_type;
        typedef T result_type;
    };
    template<typename T, typename U , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6>
    struct class_member_traits<T (U::*)(A0 , A1 , A2 , A3 , A4 , A5 , A6) const>
    {
        typedef U class_type;
        typedef T result_type;
    };
    template<typename T, typename U , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7>
    struct class_member_traits<T (U::*)(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7)>
    {
        typedef U class_type;
        typedef T result_type;
    };
    template<typename T, typename U , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7>
    struct class_member_traits<T (U::*)(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7) const>
    {
        typedef U class_type;
        typedef T result_type;
    };
    template<typename T, typename U , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8>
    struct class_member_traits<T (U::*)(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8)>
    {
        typedef U class_type;
        typedef T result_type;
    };
    template<typename T, typename U , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8>
    struct class_member_traits<T (U::*)(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8) const>
    {
        typedef U class_type;
        typedef T result_type;
    };
    template<typename T, typename U , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9>
    struct class_member_traits<T (U::*)(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9)>
    {
        typedef U class_type;
        typedef T result_type;
    };
    template<typename T, typename U , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9>
    struct class_member_traits<T (U::*)(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9) const>
    {
        typedef U class_type;
        typedef T result_type;
    };

/* class_member_traits.hpp
7V38icHt7edvXHCxb8ptiVNYU+37rDPPPT1owXMi2Q1s+5Xit5xmor2LThnZ3upCWgZ9i0v7pn4eoTBnJnJfzXP3G+ZdKZJ5sXJtcoLqViJ3MyNzp1sMuvy07lj6HgtRmJOW2YNnHlna/juh3syLf4eLefjFtWdoYZWRmdV/ZtB3uPbP6o9r/CWbeVr2a3j2r7bf+a5QHxY6SPx2rB1jatO7GXl8pydkWgwKbt0zHdsd9GuxLjzzsPaud4pUPdW5e8W1mHbekn/SwD6elmnUxZh1z5S50p1/b2vfX9fyzDnpPYeJVL7qesbi/LyJGMfz9xvYznyaeMMuu637lnKX8pd7OjmJ3J489wMHB3QTyfxYUAvtzEUbx8+fMLCtedmMO02z7tz22D7SQmGVWj+/jme/I/vik0L9Wbyzdm3iJNq8dp+xbZ5oYJsn1mvzaFf9O6yreo5qOntWJOvFDmnXJYVOYkyLNzI3f32Mv+lqTG7rvuVz818Ze0vLfT3Pbbnp7H0iWQArbKtlbC5yV+41MnfaxElpBl2ES/um7+9aRu3dzaa9b2R9te/vla7iGLcYeYxPSEswKnRC/WP7K37+6SIyd+eZf+iXvE9ooLrWtxjXLhOZq6uNzJxg4JW3vHOm9/PP+Xil3TfvwbOXX+l0SGhvdlG7b16r3TePNza7UbFt+rfvAXWNCZH3Bp53zciYHJEoiO3V8npo98urvjYwLx9oDWxsee96W+/lKbXsXjz7yY1JH4h0fViAlr1Qa+tog7MbFrv+fXOeMEcbz7x55pQ9d64SGszOavdYirRzlp3HjcycbGRzi53Xvx7ZyteluExk9+HZW38+NVDoTaxcG8tDm4vsoYZmn5hp0AUo7ZmuR8rVKexE5p488z3Pv7NMpOrLcrU+fkzr42VG3ltKyEj1txh0c0naN91b2sDvKjQTuX157oFb1+8UyW5mTldozwG1fr7ymLG5DQtdr39XFqlnYyKzH89cO3XMDKEhrDBMu3/aUZyThxp5jpYwJdOgzGLH8rkKv8GwXbv29OeZTVfuuCD0FhapjWfFzuK8tPRjIzPXreZoVG6x8/rnKrfx+8IeInsvnv3XLSNfExrKyjLFbzHdRR9f/KWRfdygry91v/JY1p//XZv2bD+A511vuaCNYP1YmJv4bbR2TLsZmXdcZpqfZZxRjS3vXX8WyK+1B2n3ym/k2U+kxC4W6fqzam1EL7qRn5erz7t/9DSun/P/GJXbumdrZjGvpMgcyDP/9GrAHpFqAFusXWvna/fScr4wsr0tljjjnnfT3uXso9LN2nWnR3xvnp3Rz0A2byiz+3PbFHXe7eDUSeP5Jw8J80lMTXVoiWnH/BfrZ/76q/X/4jfxX2oNVsns//yTBVXrtTBXr9c+NvV6K2u3X/kT9SrWFjOmxGLfotB/pm4HqffX7f7804VV6zdsjl6/N9nU723sImuw34r10+pKOyA4NjojXV312kOdjD3ToxsvTffY2yelJaZPz/QYPCkrM9bPVy0I/5+Pr49fQK8+vXx8Y6dNieX/MHZ6prontWx/oh7DWQEom2GF0upMXbvtmbqx3S3+Zl5nB8v3RAiNYAF83Lf+nWvdrZesD6lcScGx4yeljcuYNCEz9rY09e+XJyROGpc1ITY7ISs9PTUzdkqmOtGOj5g6yZKRnhLn5+fbq1dgH3//WD7YZNSVKS7BMi0ucVKmJc46vCVOyI7VmnnUgNiYul0NGcF/9Qvw4an8b9Q6gLp5HQyPsekD6vphNzCRJ0R97lPtv16UeDA7qx1i1YqY26R6R4Di4DzqH1GrE/k4LI+6/tadah6P6PhbbPp0JNuqld46T3tZkhdTHJs=
*/