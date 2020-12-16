//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_TYPE_TRAITS_TYPE_NAME_HPP
#define BOOST_COMPUTE_TYPE_TRAITS_TYPE_NAME_HPP

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/stringize.hpp>

#include <boost/compute/types/fundamental.hpp>

namespace boost {
namespace compute {
namespace detail {

template<class T>
struct type_name_trait;

/// \internal_
#define BOOST_COMPUTE_DEFINE_SCALAR_TYPE_NAME_FUNCTION(type) \
    template<> \
    struct type_name_trait<BOOST_PP_CAT(type, _)> \
    { \
        static const char* value() \
        { \
            return BOOST_PP_STRINGIZE(type); \
        } \
    };

/// \internal_
#define BOOST_COMPUTE_DEFINE_VECTOR_TYPE_NAME_FUNCTION(scalar, n) \
    template<> \
    struct type_name_trait<BOOST_PP_CAT(BOOST_PP_CAT(scalar, n), _)> \
    { \
        static const char* value() \
        { \
            return BOOST_PP_STRINGIZE(BOOST_PP_CAT(scalar, n)); \
        } \
    };

/// \internal_
#define BOOST_COMPUTE_DEFINE_TYPE_NAME_FUNCTIONS(scalar) \
    BOOST_COMPUTE_DEFINE_SCALAR_TYPE_NAME_FUNCTION(scalar) \
    BOOST_COMPUTE_DEFINE_VECTOR_TYPE_NAME_FUNCTION(scalar, 2) \
    BOOST_COMPUTE_DEFINE_VECTOR_TYPE_NAME_FUNCTION(scalar, 4) \
    BOOST_COMPUTE_DEFINE_VECTOR_TYPE_NAME_FUNCTION(scalar, 8) \
    BOOST_COMPUTE_DEFINE_VECTOR_TYPE_NAME_FUNCTION(scalar, 16)

BOOST_COMPUTE_DEFINE_TYPE_NAME_FUNCTIONS(char)
BOOST_COMPUTE_DEFINE_TYPE_NAME_FUNCTIONS(uchar)
BOOST_COMPUTE_DEFINE_TYPE_NAME_FUNCTIONS(short)
BOOST_COMPUTE_DEFINE_TYPE_NAME_FUNCTIONS(ushort)
BOOST_COMPUTE_DEFINE_TYPE_NAME_FUNCTIONS(int)
BOOST_COMPUTE_DEFINE_TYPE_NAME_FUNCTIONS(uint)
BOOST_COMPUTE_DEFINE_TYPE_NAME_FUNCTIONS(long)
BOOST_COMPUTE_DEFINE_TYPE_NAME_FUNCTIONS(ulong)
BOOST_COMPUTE_DEFINE_TYPE_NAME_FUNCTIONS(float)
BOOST_COMPUTE_DEFINE_TYPE_NAME_FUNCTIONS(double)

/// \internal_
#define BOOST_COMPUTE_DEFINE_BUILTIN_TYPE_NAME_FUNCTION(type) \
    template<> \
    struct type_name_trait<type> \
    { \
        static const char* value() \
        { \
            return #type; \
        } \
    };

BOOST_COMPUTE_DEFINE_BUILTIN_TYPE_NAME_FUNCTION(bool)
BOOST_COMPUTE_DEFINE_BUILTIN_TYPE_NAME_FUNCTION(char)
BOOST_COMPUTE_DEFINE_BUILTIN_TYPE_NAME_FUNCTION(void)

} // end detail namespace

/// Returns the OpenCL type name for the type \c T as a string.
///
/// \return a string containing the type name for \c T
///
/// For example:
/// \code
/// type_name<float>() == "float"
/// type_name<float4_>() == "float4"
/// \endcode
///
/// \see type_definition<T>()
template<class T>
inline const char* type_name()
{
    return detail::type_name_trait<T>::value();
}

} // end compute namespace
} // end boost namespace

/// Registers the OpenCL type for the C++ \p type to \p name.
///
/// For example, the following will allow Eigen's \c Vector2f type
/// to be used with Boost.Compute algorithms and containers as the
/// built-in \c float2 type.
/// \code
/// BOOST_COMPUTE_TYPE_NAME(Eigen::Vector2f, float2)
/// \endcode
///
/// This macro should be invoked in the global namespace.
///
/// \see type_name()
#define BOOST_COMPUTE_TYPE_NAME(type, name) \
    namespace boost { namespace compute { \
    template<> \
    inline const char* type_name<type>() \
    { \
        return #name; \
    }}}

#endif // BOOST_COMPUTE_TYPE_TRAITS_TYPE_NAME_HPP

/* type_name.hpp
sI33htbVnTa3s65+8lSbZ9fVV9/T5th1lb+3zbHr6sCRNseuqz+3Oa26+v77ujjD6+rF97f4Q+tq6QMtbmddPTNp8Gic0QMi9mwMXKcBbOmogSkxw67Mmtv6Tu16TpA+6NwW5yEsvlIkfhjlfuh0z0MvyoKYU1GVR0eYd15YfLkoar9KQscbEt/ypXZ0Z4XeD/op7Yn8Rq0d1+WZ14b2gjCwH6D5tNKT+4IcWs+sSvsVsw5e3dbgytL7SzP9aAbtbXuDk58DSdAJMPvyHd0caRFw0Uzr9s6G1zPTgr3O5cjQSy08vw7jNEnE7ELv4nL/8l7jLBEyV02ZUlRunEZJ7JGMJTECmes8nTAo0yoqfZKhp9n0VI374H3VlHEdUcVxGiZeqIQ2jttpjTZytyw5PynoP4fklMMIpMbl7lhyue+nbh7mQi7HtZc9laYtNxJzH52e71eul4RiTh7NrMhXZXlOcd/5AJOLRVY4uV/FQj6nKv+fmpRr0ZUXjh6bPKHGLK6baSbrCt8LMi/OxNyFlZUO3Rxq0qyZXCiqMKh9JwrEvNTNwvzCsbaCUIdrMavDxM2TMA48wU8peD5ftHQTVlUURF4tqEliq4SurXLdXGdygQi8JImyIpByfDm3utaUEbKvWrK1m7lJ4jmWLLRKsm7TdphsJfIgqcq8Ci1Z6k3G9Jbn/Z6Vvu9kderoOPy+RYA6EUKpRz6Ht0oTrq8kLvwqynJTtu88gev5sCVXumnoyYxLueaYqVPPIrH07Ph+FieZkgsuvm5ez1pp1qUT5klcQRZ55WmuMTlfVFURxmHmKLnCR70iSZnmVNOeTNlCimZZkqkk8cVq2RdeS9h4FcviFV7ukwwsLRv7wqZs302ssSCuosQLcmFt0Wk5+Ou9yeRCUYRhFcVOIbq29vrCn4OfYEsvSRFWeVi6or212NLLPVO2FlEWpWXq6OzihiwfxydSJlM6eRWGTi34zjeXOcxlorByi8zJBN8NVzLwnyxMGTcVdVTGZRbmELLNHfvih5q6OJdabTupk8rPXMijN/N2dpnJRSKJvSgrQ2SWX8vk/ekak3WFW1d1FJUxk6U1i5XXG5ZcHMaOHzuJsE2CtFyT119Yea3CyHfKIG3JGWNsI3uHyYYi9tLMCdxYdJkh9UVRzvGMt/MsT8qqijzIMrfUI06T5sHMaue1m6VFFthyRnYH7YHJpsILvLrw/Rqytvm+3R6YvCvyvCwjPyqEberVl1tAe2BykQjSKI6dwuNy3Tq+Zpc3c8lGmaU5TMevWvl1vTIuytwRtrltX87BPIbJecL3Ii+M0sCWO+1Y7cHKa1o5eV7Elegyz+2LQnY852NQGjqJE7mJaJvlaslBOQ/mPL9B7DphVcaiZfJrzWVya74W06gS5MK6dmN/5+vcavdlWgdu4tlyqE5zLmPKlqKIHbeI/ECY1rJaZLnJ5xWrfInrxqVfxKJ1bYePf9eYXCyqLPbD0ncsOZ5TOWebatqPKV8JN0jKushcwW6Z9KWWMZ5Y9Vgnlef5RcGEeHqiKedtqz4yNy3TMkuEdY3E/vbds+qj9uvCS8LIljNSFY2ODhSmbEJnvqFfuWLIzRXoyG3aEJMvReHHbhgHybAIutrEuYLp2XOKukqTVLAbJX2ZObwTUnBdRXmeV0EaCevai05qHfMYU64QSV06aR5VwrhxiLchMAYVvE5dr3bCtIpE23SukUV7uMFkI+EHTurnkSfaZo2t9nuLyaaiLErPcZJA2OaOXNxp5O9a8qHvxWGROpDXsxNbHvOUktVL7oVBnoehYJbIfZkXMBaVvK9WuVtVie+KdbIYmf3c8hztKdNGiRKErcC0KTftZ3nkh0E=
*/