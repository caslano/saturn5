
// Copyright 2005-2012 Daniel James.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_FUNCTIONAL_HASH_DETAIL_HASH_FLOAT_HEADER)
#define BOOST_FUNCTIONAL_HASH_DETAIL_HASH_FLOAT_HEADER

#include <boost/config.hpp>
#if defined(BOOST_HAS_PRAGMA_ONCE)
#pragma once
#endif

#include <boost/container_hash/detail/float_functions.hpp>
#include <boost/container_hash/detail/limits.hpp>
#include <boost/core/enable_if.hpp>
#include <boost/integer/static_log2.hpp>
#include <boost/cstdint.hpp>
#include <boost/assert.hpp>
#include <boost/limits.hpp>
#include <cstring>

#if defined(BOOST_MSVC)
#pragma warning(push)
#if BOOST_MSVC >= 1400
#pragma warning(disable:6294) // Ill-defined for-loop: initial condition does
                              // not satisfy test. Loop body not executed
#endif
#endif

// Can we use fpclassify?

// STLport
#if defined(__SGI_STL_PORT) || defined(_STLPORT_VERSION)
#define BOOST_HASH_USE_FPCLASSIFY 0

// GNU libstdc++ 3
#elif defined(__GLIBCPP__) || defined(__GLIBCXX__)
#  if (defined(__USE_ISOC99) || defined(_GLIBCXX_USE_C99_MATH)) && \
      !(defined(macintosh) || defined(__APPLE__) || defined(__APPLE_CC__))
#    define BOOST_HASH_USE_FPCLASSIFY 1
#  else
#    define BOOST_HASH_USE_FPCLASSIFY 0
#  endif

// Everything else
#else
#  define BOOST_HASH_USE_FPCLASSIFY 0
#endif

namespace boost
{
    namespace hash_detail
    {
        inline void hash_float_combine(std::size_t& seed, std::size_t value)
        {
            seed ^= value + (seed<<6) + (seed>>2);
        }

        ////////////////////////////////////////////////////////////////////////
        // Binary hash function
        //
        // Only used for floats with known iec559 floats, and certain values in
        // numeric_limits

        inline std::size_t hash_binary(char* ptr, std::size_t length)
        {
            std::size_t seed = 0;

            if (length >= sizeof(std::size_t)) {
                std::memcpy(&seed, ptr, sizeof(std::size_t));
                length -= sizeof(std::size_t);
                ptr += sizeof(std::size_t);

                while(length >= sizeof(std::size_t)) {
                    std::size_t buffer = 0;
                    std::memcpy(&buffer, ptr, sizeof(std::size_t));
                    hash_float_combine(seed, buffer);
                    length -= sizeof(std::size_t);
                    ptr += sizeof(std::size_t);
                }
            }

            if (length > 0) {
                std::size_t buffer = 0;
                std::memcpy(&buffer, ptr, length);
                hash_float_combine(seed, buffer);
            }

            return seed;
        }

        template <typename Float, unsigned digits, unsigned max_exponent>
        struct enable_binary_hash
        {
            BOOST_STATIC_CONSTANT(bool, value =
                std::numeric_limits<Float>::is_iec559 &&
                std::numeric_limits<Float>::digits == digits &&
                std::numeric_limits<Float>::radix == 2 &&
                std::numeric_limits<Float>::max_exponent == max_exponent);
        };

        template <typename Float>
        inline std::size_t float_hash_impl(Float v,
            BOOST_DEDUCED_TYPENAME boost::enable_if_c<
                enable_binary_hash<Float, 24, 128>::value,
                std::size_t>::type)
        {
            return hash_binary((char*) &v, 4);
        }


        template <typename Float>
        inline std::size_t float_hash_impl(Float v,
            BOOST_DEDUCED_TYPENAME boost::enable_if_c<
                enable_binary_hash<Float, 53, 1024>::value,
                std::size_t>::type)
        {
            return hash_binary((char*) &v, 8);
        }

        template <typename Float>
        inline std::size_t float_hash_impl(Float v,
            BOOST_DEDUCED_TYPENAME boost::enable_if_c<
                enable_binary_hash<Float, 64, 16384>::value,
                std::size_t>::type)
        {
            return hash_binary((char*) &v, 10);
        }

        template <typename Float>
        inline std::size_t float_hash_impl(Float v,
            BOOST_DEDUCED_TYPENAME boost::enable_if_c<
                enable_binary_hash<Float, 113, 16384>::value,
                std::size_t>::type)
        {
            return hash_binary((char*) &v, 16);
        }

        ////////////////////////////////////////////////////////////////////////
        // Portable hash function
        //
        // Used as a fallback when the binary hash function isn't supported.

        template <class T>
        inline std::size_t float_hash_impl2(T v)
        {
            boost::hash_detail::call_frexp<T> frexp;
            boost::hash_detail::call_ldexp<T> ldexp;

            int exp = 0;

            v = frexp(v, &exp);

            // A postive value is easier to hash, so combine the
            // sign with the exponent and use the absolute value.
            if(v < 0) {
                v = -v;
                exp += limits<T>::max_exponent -
                    limits<T>::min_exponent;
            }

            v = ldexp(v, limits<std::size_t>::digits);
            std::size_t seed = static_cast<std::size_t>(v);
            v -= static_cast<T>(seed);

            // ceiling(digits(T) * log2(radix(T))/ digits(size_t)) - 1;
            std::size_t const length
                = (limits<T>::digits *
                        boost::static_log2<limits<T>::radix>::value
                        + limits<std::size_t>::digits - 1)
                / limits<std::size_t>::digits;

            for(std::size_t i = 0; i != length; ++i)
            {
                v = ldexp(v, limits<std::size_t>::digits);
                std::size_t part = static_cast<std::size_t>(v);
                v -= static_cast<T>(part);
                hash_float_combine(seed, part);
            }

            hash_float_combine(seed, static_cast<std::size_t>(exp));

            return seed;
        }

#if !defined(BOOST_HASH_DETAIL_TEST_WITHOUT_GENERIC)
        template <class T>
        inline std::size_t float_hash_impl(T v, ...)
        {
            typedef BOOST_DEDUCED_TYPENAME select_hash_type<T>::type type;
            return float_hash_impl2(static_cast<type>(v));
        }
#endif
    }
}

#if BOOST_HASH_USE_FPCLASSIFY

#include <boost/config/no_tr1/cmath.hpp>

namespace boost
{
    namespace hash_detail
    {
        template <class T>
        inline std::size_t float_hash_value(T v)
        {
#if defined(fpclassify)
            switch (fpclassify(v))
#elif BOOST_HASH_CONFORMANT_FLOATS
            switch (std::fpclassify(v))
#else
            using namespace std;
            switch (fpclassify(v))
#endif
            {
            case FP_ZERO:
                return 0;
            case FP_INFINITE:
                return (std::size_t)(v > 0 ? -1 : -2);
            case FP_NAN:
                return (std::size_t)(-3);
            case FP_NORMAL:
            case FP_SUBNORMAL:
                return float_hash_impl(v, 0);
            default:
                BOOST_ASSERT(0);
                return 0;
            }
        }
    }
}

#else // !BOOST_HASH_USE_FPCLASSIFY

namespace boost
{
    namespace hash_detail
    {
        template <class T>
        inline bool is_zero(T v)
        {
#if !defined(__GNUC__) && !defined(__clang__)
            return v == 0;
#else
            // GCC's '-Wfloat-equal' will complain about comparing
            // v to 0, but because it disables warnings for system
            // headers it won't complain if you use std::equal_to to
            // compare with 0. Resulting in this silliness:
            return std::equal_to<T>()(v, 0);
#endif
        }

        template <class T>
        inline std::size_t float_hash_value(T v)
        {
            return boost::hash_detail::is_zero(v) ? 0 : float_hash_impl(v, 0);
        }
    }
}

#endif // BOOST_HASH_USE_FPCLASSIFY

#undef BOOST_HASH_USE_FPCLASSIFY

#if defined(BOOST_MSVC)
#pragma warning(pop)
#endif

#endif

/* hash_float.hpp
gQycMdWzBFmwarKxUNX98RsAuBLZ6uF7bcFby/CUEi8hAHL8FtdiWEGlT9fxzwd73oJRcbQUw6rEmBv97k9euYZg1GHwG2AOye75TYMViV5XVBXCwYsN88QYgHO6fqUv3r0zbLAJtkdireqEENZdYcLw0XqXOeQkHnKXAiL7plQDvQpaQMV2PMgGJkB84ChZ2pPNm+uCd/pgziliqlm9tJTFJkoj5lWq7SafX9WPZzC58s5mzOxOtcjVnPrV5AmnHad3hnWZ+DxBNPqpXndnO0AAumtBkFDKmqYuT2mO5o0IwMN6TnCizW9cnvJyvZGThDSh2F5ImCsZFiVrp4p/bl+D/FouStaSkbJy5V0PaF5QnvAsGGb/55XHKfD+pbX8sbnRdynHmfTS2CU2kwIE4OzSN9Ucvv6seOLo5LOoPAciQ72SpOVlBZbbAOjKJ90KVxOtelDhMnJa8tE+3CZZnfXfzWdsZ5PVTLE20JAjn+NZ2cvOqaVIoCq/j10FjqAXCVoe/M4qb8iWq04WAkiHLv4a7jVVgCu3fhzZBu/GFleLTKhwKDjEEjH9hMWM/jaSC5Sx1JWJRcOT59B2H8GR8ElYexRyJHn8sK3KHYa5eOgJ6PERCWrpoqxLdursy7gc0HRbr67T0MVouzbPfljsJ17T8HFJrN8I6DND7PKFeeG35ZM/yozS0eUGdW5czC+H6BlOZ5qRNB5IokioMvahNVZy45h4PG/X2+EKfEbczChMlJEdAGOoqY05SwKNYegJL+0NtkK1086dljduUkod4/eCw1fYjhFv1Wrp9+oIcvNHluIyl3+18Gw7bZ+TpdlmKgpkm1p6ViTDWgZMyfkjCGhcXhtc+W8K6yl3SNotCjvIKQ7F+B4K2B3va2JkQzX2Aun3uf4nUHB43ffjEvBbDr8t/gHd9J7U6C0MGvHAFtvrpzDR60XnnEKphD6Pjt3SKFMtTxfHo5YpOrIACwSOpqRG9sTM1VnmDsCu24X356ZWWxCVH6R/6NK4b9r9Iklfl/jXuHoabz/LJAV9Kv+ypPgb4RgmyTqnCzzxGUZHgFA0I7Xfu3CXuUwDGPcdQ1KMz86jKoDt9hJ+exD01tggqnqs4HbsOJM47phczix2JMrSIm0bPDVGAoDuOTmC526AHoYhITV7cZjIgwpEZXT5tAAbJfXQlrZ6fZJjE4pofDa4uBjc6SAMJKa+FA1WggyMj63k7jO+e8A50yOGfggygTb1lO3F88j+9xsMcMKeZZllXTolGB4Zut/goCdy19hUCoUh2haaAc0Vd4Js79A+7O0p1vyB8sVUWT2xfP3tMAeSAjytMgltN/g/D7Yphq0rSAk/jGeU/IkrwkQkn2BcxVHUQhBEDEOwmk0cQjFMG1DKKwm6bxuhPFlC02YZ1M75WrRwkSeVtJCJxc7k1FaFVx2Sk7fKN4SkKF2qWCgQ6VmAAaxmhGzRrcH0rNV4o8tEdc40g36G2056LwZGeA6MbQz3pUBXnKME4OfqbUUimcygJ71WzwmqgiKI+rwLhxBpXv5M5pJz1HBUopR2kvr1j7RtvRvyDUjg6oIJ2pqHMIcYoaaGagfB/DkA6PAiS4l52nr6Ej/Wc+4fYd0wiwTqNgkwGqQ8PaDBOo+ZzChQTsWpeKK7pq7KEGTPUH8C32GpzmLh5kg0Ir/F0OILdfXJHvpxDz9yd+EshYAlZkbi3iLNbmh0lOBYCRDjRomAm0itzmKVsNDjRPB30lCZIHqba4bOSjHwgrfmBLLkyBFw9yDPhPfMkPLnXlGg/5qj92JU2UUwMotWcVO9fIMgUyenuE6XAk3WvO+d85aEyRQRB8drcM24bJBX0RZNxVmi1cdtXR7jWCJb0eeMSRgXnCdvBu+BYyr48eC4EqrbpsDmrRkCX22OgsLH6ZJKm6NMvyE4hHaGZ0uOdeM+QVCJUQUkYTHNaxyO9YA/mFvFQOFE0GE+Ux2CmkH7PMSPdksdoF0i/OxBIwojpTND+tqAMhuP/RWh0GM+J3MjZnAqE/wyA1ic/KxPJVLJDomMQWlDigasSuHSCMxQIOrMsMyLQ/fFyaMsZJJPC9BB9j3Qm3IiWEw8uYRRGM4mRFU8UbtQ640kwRvFKHdO693QlAlREWNRIeUkS8w9epSHkhmttvaS7u5P0EWOkpms6JKSyuaI0RJRmnhNy1xREL033AKkhEvRy8fCXMJND7OTQMCDMYxTVwJNAednhnMkJ3DM3cfVGlkjoakVFwAft3G4pCaBkWNJixzmMB4U9+zJJnBYHgKnFJmoKQ0JhvsIFP1XKBN4h5e4FhN4Jr0SmTKJlawHKR/Mh204I/7pUUquJmRsKhUzV1SwiLDvDrZ1VGCRKE3QMm4xVGzQBgszLeptV3hSaBvbAx6tVoSYi1htKi64W5LuEm2OSrYzWp7wQpkbS9VOSZ2wVAYFIhlNW7Y4F2bNNoJwWb4wgMTqEareXci2gBDSzhVwUcm2XDjhTkIqQ9lyWMH3Q0E8S+YwWT2CPzbMQvHuXvgmox/JoHyfr5gRonhpMAuKCt9kqyo7swyY0UN6lwwKrQByOkeasmDxlkTeOF8w7FqJMjyO7F7ickXqFmWEm0uJMTtKEWYQEFn6ZrNsyx5dSTIzSq7guJI2aK6sdpxGqKM57S1vGzES7zUHWCpHKLN424AfG7N976kB3SlPerOyKKE0OjZd2ag0ezZVuKkSWapaCqkW9LAV7DfLyDJba7QgnRtHqbQiuaglardoq7DQaBxz9i0vejU11qq1qzYAACz/013mJP/LbYauYdPuawaba3kSUrb0aG0WaRbVUpWSTRHzdmYWZN2UaCb1WQrwWSmdX7J0LzUzUbvcc4O5bxEed20SaVUUccGWbkaWdjkVbDkTciW9P1LMZWFVSuk0c4aVYvWUczZSNmNV7Xs+Mll+dHeBP3cNNVqBMnlO0naeGVMdyV2d6VUpMSxKqnArdmupV30K6m1dznWrtWK9nnvS0HDR0XguV3ZpVXke32PrumPWc0lmPWvZUUri9HLl1Uh1c30ZynErwn3B6HNxnHsJHncuUHoS+J1CL6ryFyLP/bxavCGXGLpcKsXQprP6B49t/xsbrCguUAUnO+4sPPTLYuPCKT6AeNpzW4fHnPi6G4TEMimZi4WP7QvEpAgUKEj87VtcHUJ4X6T3Eu+TtC1Y/ktlw5JOdG3KqFW+0/ShZ0Elv7bkbBLRlpL3W1QdMzLmGKTImFq2PHGYXu1WypUxtTmdeudrzJn5S5tMVTq/YRz0WP3FZRN8yC6JdNTRwfUotyG5aoBiKcCPlSa4lSvq29I5SGFADyT2Vdr5+O7II/LVShc7Onn9I4+iX7NZ+vj8410u6TvbjPRK1waSv85nUSknECpK6BnIf0uHDzHh8+uhscivbJ0oUAfA3vL4jY/QpAAhTviX4iFIM8XoJMMPO9AzXclLGo4zzTtxcxytiLJIbuQWC/0nmWZSDhGyZD9lfxf2yT7VCAwNKvayrTcsOIGMNKxgSJ5FKljgTVskWtCcRjIvamdHroDMQTJSQED0GULI3HhVpqCOSUIcb2z6jziAWrR8s3wsEOdeYwVi2DTcNVoZpZ22EHtk/SXx1mQdsNNXApobkXHSseuOa/Ixi5+RJmIwnZLmASiZl1qye56NwsnxuY5KarHegDbCCYqOmvKhqKqMMkISEC95+T4y0ZcKG64dSgR6AZZfHhMTDP8ilKDKBmvkN50ra+RHG2H5OYke7UibIjYUTUCwpyL3Q8hpuSV6wGe5J7dDJJQywCuVQp5s02XdhW0iG6GL3cJn81H0X4U0zU2NxRo0iIRXabWHpza6Yk9cz7SkXBRcIASl7KY+MIMzmGkP63cIuzGxmwvfSiFnN9PBciMWJvT4gz/71IcJ9yA9cQPz8C6oMgaxfA4ee6xfnwM6+Ci28CczHl5/o1FfiDkSqCT2ljbVxHQC02yeKPl7U4G/5cfRHdTWXpMlgmknisOBnxkAyB6Bx3oTpmL5q4hdodf2yhpw6hA+j5qI6c/q8u/tEAoDEvUu2TU3kPmA4iMg+h7E2+ob9/bn/ZOLMpJx3GMyECX/QU80LcZ7+HERO+yugq1Vb4mMMvgFZAztXWujkuv5Rq5cZkDvNEMpRsPUHdK2Rr8doY7b7kWSvVezHoEtSfsVYyQMta7ket243ulRikTRQrxY0+PTXlbVo4KSxcMHzXmcQzjegvMyeW8f0ENCb0zD1Qe3EPsn79OpfoZ/EDoMcaft0Ceb3JkPIYbvuJ/BXULhNij7vPQtd9ZKS8gkMq6ajLAtr72Qx45D8NanUG3pvp4vevqNz8mgfFp9rX1OveEZSp9Ex/OtdmhaIIYt1EmHXz7mCjjj4D9BoCYSkPC628HGPPg8pJHQcTp9CqiFV9//kALBiM0Ime3Dm7OGwS14bgthwsLiv/NF0xmRy4pq4OpXRoYfBrENrwojVbVm/R1Ib422C4noyRZG33jjmtnjoesAkQ4FO/XjJamHhzDmINcgwiHv9cTeiBOQFYthw89JR9mnkJEFtaMl3tXEigYSEnE8o8ePOcWOJpAVYXqiKZ4HQ5NGEpSI26PLr9fBl2SRF5w9G+t57E37svotzOZiz2uVEnzTBkqmzw6DevHidBtIzDSJx8vHi4/uIJjNfvKGzvL/odXHdk+ygmOb/JvMstkALxEMJT/d8qlujEkah4jhPYEKVMyDEwM48SazCPjMnQDx0+m/uwdzTHKYDIZTXqc1z4Xaq1kU3clDJ0ScgP6vOSlyG4xmyJ0Xcgdk6v1egkZ0v9FvfRq63/h1lti1wd7XXW1Mu5DWxPrnwYoJZ+BTQmJkyYd62wwHHyZFk9YcBoAooS4g4QwebYiFPNWpXV76XJtWRI5CTbVYlfZOuZhUuVqRq1z5alK7Zt6pXNWgeiEuWs8Cxqemqbp9TtNP49pcutz1qHtJZwOGbpTs67jVKTyoGgEg4F0Rj1bLJoihmTfCFoAwyw70OLuWUaJnIY3dqDBpAIHb9nkh6clGCC6/miHlfQGHkso6qrF2PahXb75TonD/ECgISt3WxoW+uKU5e2PDlNHaSqp8Hm5t4aZH3AbbvcTJvm5nh8jWqtX53SjXv9EJaFG1vcLzULm/26X6daPnSecyS63ZKTVjhYfpcbRx1Oq1zbX6U3VpxgRY7Bcv/ynD8NR1t/hXZjrjjUGmHMAjGTToY0VurCEnhLkbfkG5X5hz1446fcLvXOgt8lYHB2SKG8lrHa+SSo+PPC8R9eS1PBNSDX/T0kj5ohHxwPkjJK9Xk4vR67POCWBK3hCL3Lhxmq+W/j90NJDzj0lExu5ggj0coOOyHeQtFgYwdufDSDwq6T7cIIgv+VwMKoP7RaggP02MlkUqvgh6o9kYObncmt8OoLikJGi/mNlcR9j4Rul1dVHmTWGBPpBDIL+cN6HJGAvZWY83rQwoITBofkjfcX52CGIkGDDdOR9qzTDx0wC10US2XYQleJZUeA7Dt3geRFXxIygrhddvGswWeDjYXJKc0To/aEVqTw5lWUW4TNc5QtW3Tjsj5Z0C35bz2OO+AFpjXwUIOkZp23D/ewNfk+aOppPbPF4LZIzACLkzBs1JUQ1mQ6fVKD8PDK2V9S2CBTbtGVUyDJb2t226FeM2hkI2NWCIMJCP8J3qWlZ0eVPSNdQuQnkn9Pdo/LErvpQkXU1oKfAQM8RwJmub/TXcRtftG8tvlyS69wWm5MBscJlbSYg1qtvVHWlU8vUcUUqls+VUr6r63RmTbC+13oj6yfej/b20tPPXRCdarBletORb5S+nQ/mBbmQh788e5ZfEpIIvn/6pd4Zt+s+ssTingsgzkgPcy62440FK8v9a6kP81CgSfGx22XpciV8vCDacjhlHabR1PjekjCRsXjea4WefOP0GyY5aXh3s6T85gSrdMCd/iq3oEL6INrysBlRUxXw/N1BhgSwG8NdmNE6vsDjigEUWGhXo3wwC4Z1Vy3cTm7KvLFkzvJATABxnzvea/7FWzKrXOnMheY0UH3+a7rw65vLfMbqDPxlbH3zu7b0B0ma7KRjdEJW2vjqPT3+2M2yDuEePCW1LQLnzdBwf0A5AbdEt/v7wI/0Ebt89T+Q+3iv8t+RJc+vomgktDy+EKsAIkgueYOQHdGDfL3WfavUYKuUm6v6I3g/Bz+H2UYzYd47mR7EftI3L34zm93vCPzShHISIMYzmbokRJlIOIQfRpIQwJrkPXxfqjBKIHwjVACvSzPy47+dorAN5ICVGEwpDmgdzEg8BZig2SCl/oqFgS2diCA8P5jqgFiRYjx+ibuiwjAFDyi6sVAyj4aP/aC08qljqBEsshHJoigrVLEhAgQUFS40SJw/VHEDIYl0qvw/RWAzT6FZ6pw7vhFf6JOcGAExqpYcKJwERaw0fqwsfC9r1fU9Huid7720NY9cJLycXa69E7CaY721fvAeAKIIgeiBPqIZWcABO1A8ZUyRHXGl5Wk0RqwwcTekTCSMVRZ0YVnEcZjkYdaEea4kZS2kRy2gYYbsUBhcfRisbi2sVy0sZUTMShesbmdMflU4XqwkZe94YtoMVuxMftg4da/kvloMzlsM/gieQMN8RCOk2VkRacFMIkMZ7uYMz9hgRgIs0BhhiSMcpr7tklKfHwqczsLuHYMdohC93dDt6UcBmaFtzaNBmKEB9pF9wcUCKFF+DNM94iMhz6PArGvw38w41h1/bH4IGk64BXtQSnsIFHNA3dcwveWgofaggfUgVkBr8LNTPXezoAv8oW/ygRjyAv8RFGChYEJCARxLpSjwlgRmcQzzERjqJUfyDzCY4mfhfrjNt0YOHLawGPJ0i/H9vftY+tYz9YCbsgCfi4lRLhpqPJYbr8ZZMuR/vKZYCyRfk6aLHSRf08VDF8Sf/4k8+2VjyCFkgOL83eGiSmKZriWgMiWg0GXliKHkICLd1GQcXGWl4iYiIiWhKCIm+eYhGiXhWiIgsCYnGiRrpiZhSKQudiZiaCbt1mRoVGJl6CRtVmahEGKkqiRpnGCvLiCqjmazCItDGqN9SQA+pCYYeESAvObAR2c3QqMzSmcxcgC0YCM2KCc2qB20u7WZiwC9w/Shf+wKfQKSggAifKFheAy5ml0Vv1C3mkt2HskvaNTqojSGTqkRzrCg5Lgl62sBawpEUBbijeikgXrvmU0uyvxXzNBBZVZDMpwoRD6EPnLmhq5L8eEHQ9g2pywja+CmRUhswVU0AvyBPNPkYiJFwAMrprXFVzVFYQ9bTVKoRbBnlu8g/SwnRnvrqJncyuseYQ4IG30AZlGHCxdbeJqvMB9rjIqEjXkEdxgB061BbwCEqNgFW2CBEiRcQMTG+vJvSuBsgGJBzW/CGgqKBH/ouEgueiusBThFildoQJOPJTsuWbgowwsoRpOumeBqnhibOouulD4uvaOao+yqyGv/F4vJr4J5b6AvgXN2pyxKiFVBDuGbCcxNo5B9F+MODfMOEX0FP7JtdAVziV7BqMshTG0IHSlMFDxnv+cX0G6oot2NFVMBfa8SFB7nAnE5eeb4jLGxQ9JefPVKkC5EZf44pV5uRpq5qBCf1JTLC9yrZMWZTuNlW8USrBPr4kV0qd51YjHjcKvAr
*/