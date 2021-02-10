//Copyright (c) 2006-2009 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_EXCEPTION_7E83C166200811DE885E826156D89593
#define BOOST_EXCEPTION_7E83C166200811DE885E826156D89593

#ifndef BOOST_EXCEPTION_ENABLE_WARNINGS
#if __GNUC__*100+__GNUC_MINOR__>301
#pragma GCC system_header
#endif
#ifdef __clang__
#pragma clang system_header
#endif
#ifdef _MSC_VER
#pragma warning(push,1)
#endif
#endif

namespace
boost
    {
    template <class E>
    inline
    E *
    current_exception_cast()
        {
        try
            {
            throw;
            }
        catch(
        E & e )
            {
            return &e;
            }
        catch(
        ...)
            {
            return 0;
            }
        }
    }

#if defined(_MSC_VER) && !defined(BOOST_EXCEPTION_ENABLE_WARNINGS)
#pragma warning(pop)
#endif
#endif

/* current_exception_cast.hpp
6rvaOmH7lFyY1lsU+Pv7a1nnCTUVzyW21fyNqjQPGypZB38BGMfyFuwOkHnAnTXygltkwVur5mnhdImzW+E064eDaR4KJmTX2u5DYexMfUETNWiULyw3V01NHY/N3gjbVfRe2XYtTu2D774Ko9mB798wjr4ddsRRDSOPEIK38qtoQYyoOaZydNiHj1xtwcka4/yhszBP1OW409UaN1K/GrdbY12ESwp6hq1KKbUEkGdG3mj3JTkj5eM1tpZ1hFkjG5RBq5lowh2SMioeEDsM1+FxwHptvSOs6XA6WY4mZ8lOATKOjO76CX3gPDqpGpS/G5HhWYrmmkIUBcd22G9nnTMMZO7d0UriRvvdXmn1nAhvS9SNmbT3CPPuYe+eoUbgkc632u0BajPq5j9J4+PpfJmcpMcX6TAej4/j4QdsqB0pe2M/mF47CLPGFGSrkwXPRNSGtOPNh4TygZyzUMcggZ36kRpjCRQx0KiKLq2u08S3KmL02kjudlmxHTzVjZCwAer9SNhW/TpdwxNBKFjYQ7omCF18RF81/yLuxc4z12AUW4bqFJqwH7bL0/hsvGTH266I0Y5w1CU61O02l7uHFTpEc/erBYPHQZyUDVfOyyrzG2ILj9Eup8PpeMFiOtXik+Rz/HE2Ttj9s3Vw
*/