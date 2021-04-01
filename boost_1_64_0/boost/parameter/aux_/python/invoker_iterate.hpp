// Copyright Daniel Wallin 2005. Use, modification and distribution is
// subject to the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/dec.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>

#define N BOOST_PP_ITERATION()

#define BOOST_PARAMETER_PY_ARG_TYPES(z, n, _) \
    typedef typename mpl::next< \
        BOOST_PP_CAT(iter,BOOST_PP_DEC(n)) \
    >::type BOOST_PP_CAT(iter,n); \
    \
    typedef typename mpl::deref<BOOST_PP_CAT(iter,n)>::type BOOST_PP_CAT(spec,n); \
    typedef typename mpl::if_< \
        mpl::and_< \
            mpl::not_<typename BOOST_PP_CAT(spec,n)::required> \
          , typename BOOST_PP_CAT(spec,n)::optimized_default \
        > \
      , parameter::aux::maybe<typename BOOST_PP_CAT(spec,n)::type> \
      , typename BOOST_PP_CAT(spec,n)::type \
    >::type BOOST_PP_CAT(arg,n); \
    typedef typename BOOST_PP_CAT(spec,n)::keyword BOOST_PP_CAT(kw,n);

#if BOOST_PP_ITERATION_FLAGS() == 1
template <class M, class R, class Args>
struct invoker<N, M, R, Args>
#elif BOOST_PP_ITERATION_FLAGS() == 2
template <class T, class R, class Args>
struct call_invoker<N, T, R, Args>
#elif BOOST_PP_ITERATION_FLAGS() == 3
template <class T, class Args>
struct init_invoker<N, T, Args>
#elif BOOST_PP_ITERATION_FLAGS() == 4
template <class M, class R, class T, class Args>
struct member_invoker<N, M, R, T, Args>
#endif
{
    typedef typename mpl::begin<Args>::type iter0;
    typedef typename mpl::deref<iter0>::type spec0;
    typedef typename mpl::if_<
        mpl::and_<
            mpl::not_<typename spec0::required>
          , typename spec0::optimized_default
        >
      , parameter::aux::maybe<typename spec0::type>
      , typename spec0::type
    >::type arg0;
    typedef typename spec0::keyword kw0;

    BOOST_PP_REPEAT_FROM_TO(1, N, BOOST_PARAMETER_PY_ARG_TYPES, ~)

    static
#if BOOST_PP_ITERATION_FLAGS() == 3
    T*
#else
    R
#endif 
    execute(
#if BOOST_PP_ITERATION_FLAGS() == 2 || BOOST_PP_ITERATION_FLAGS() == 4
        T& self
      ,
#endif
        BOOST_PP_ENUM_BINARY_PARAMS(N, arg, a)
    )
    {
        return
#if BOOST_PP_ITERATION_FLAGS() == 1 || BOOST_PP_ITERATION_FLAGS() == 4
         M()(
              boost::type<R>()
# if BOOST_PP_ITERATION_FLAGS() == 4
            , self
# endif
            , BOOST_PP_ENUM_BINARY_PARAMS(N, parameter::keyword<kw, >::get() = a)
         );
#elif BOOST_PP_ITERATION_FLAGS() == 2
         self(
            BOOST_PP_ENUM_BINARY_PARAMS(N, parameter::keyword<kw, >::get() = a)
         );
#elif BOOST_PP_ITERATION_FLAGS() == 3
         new T(
             BOOST_PP_ENUM_BINARY_PARAMS(N, parameter::keyword<kw, >::get() = a)
         );
#endif
    }
};

#undef BOOST_PARAMETER_PY_ARG_TYPES
#undef N


/* invoker_iterate.hpp
6TEj7WfVhZ0wKlgGdZlsTs79EqRhowB5e27P4dLY0IxKHlRBnr6EPU5O2h9qSTiv9GpsJEIGzG3VVjKbVLdBkOW77FGb4UtNHlq0kLmXjh4I63/mzbe9TKnc9Y3L9wpbB09sikawQxLkzohVUzk9wbBbg7WnIod/uEW/C7M0TkfU0LqifHIIutw0ChEvdqmfr4UyAVAamOSB5WHj9ESCIcEcdMtB3FSruUt+8sxI383/V8qF8j0YzS1STTMUuE1dZWZ4uNQFgl6n02EudEiyNiAXXMLeHA//vLoTNdKMxg/2dQVpNdyzANSrH0bngAcThbM5i0mxn9MmVpD4O4Cv5Z7L09EKS93JJKveeqbe6g/IOjHgbfwrwIidZEtlCVIqEdzXCz89PqBMP0mwNBTrdp5peVuNsazyit9wN8gGo1lVPm5VjPcGOVMdHmuMaYKeY12MULqsM/pFn/jIvjGCiCP6wPg9cUM1HfU3UUf0Liu8OnJDpzPI5bP9WqZSQE2hwwK8CYV7ZEK7Fwt9pi8VNy/khGj1Lw8/+6SYipH4eF+xEAuCemuktOY+Sg==
*/