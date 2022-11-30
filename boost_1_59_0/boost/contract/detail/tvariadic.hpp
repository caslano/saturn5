
#ifndef BOOST_CONTRACT_DETAIL_TVARIADIC_HPP_
#define BOOST_CONTRACT_DETAIL_TVARIADIC_HPP_

// Copyright (C) 2008-2018 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#include <boost/config.hpp>
#ifdef BOOST_NO_CXX11_VARIADIC_TEMPLATES
    #define BOOST_CONTRACT_DETAIL_TVARIADIC 0
#else
    #define BOOST_CONTRACT_DETAIL_TVARIADIC 1
#endif

#if BOOST_CONTRACT_DETAIL_TVARIADIC
    #include <tuple>

    /* CODE */

    namespace boost { namespace contract { namespace detail {
            namespace tvariadic_ {
        template<int...> struct indexes {};

        template<int N, int... I> struct indexes_of :
                indexes_of<N - 1, N - 1, I...> {};
        template<int... I> struct indexes_of<0, I...>
                { typedef indexes<I...> type; };
    } } } } // namespace

#else
    #include <boost/preprocessor/repetition/enum.hpp>
    #include <boost/preprocessor/repetition/repeat.hpp>
    #include <boost/preprocessor/tuple/elem.hpp>
    #include <boost/preprocessor/punctuation/comma_if.hpp>
    #include <boost/preprocessor/cat.hpp>

    /* PRIVATE */

    #define BOOST_CONTRACT_DETAIL_TVARIADIC_TUPLE_ELEM_(z, n, tuple) \
        BOOST_PP_CAT(tuple, n)
    
    #define BOOST_CONTRACT_DETAIL_TVARIADIC_TUPLE_INIT_(z, n, tuplevar_values) \
        BOOST_PP_CAT(BOOST_PP_TUPLE_ELEM(2, 0, tuplevar_values), n)( \
                BOOST_PP_CAT(BOOST_PP_TUPLE_ELEM(2, 1, tuplevar_values), n))

    #define BOOST_CONTRACT_DETAIL_TVARIADIC_TUPLE_(z, n, type_qualifier_name) \
        BOOST_PP_CAT(BOOST_PP_TUPLE_ELEM(3, 0, type_qualifier_name), n) \
            BOOST_PP_TUPLE_ELEM(3, 1, type_qualifier_name) \
            BOOST_PP_CAT(BOOST_PP_TUPLE_ELEM(3, 2, type_qualifier_name), n) \
        ;

    #define BOOST_CONTRACT_DETAIL_NO_TVARIADIC_ENUM_(z, n, tokens) \
        tokens
     
    #define BOOST_CONTRACT_DETAIL_TVARIADIC_ARG_(z, n, name) \
        BOOST_PP_CAT(name, n)
    
    #define BOOST_CONTRACT_DETAIL_TVARIADIC_FPARAM_(z, n, type_qualifier_name) \
        BOOST_PP_CAT(BOOST_PP_TUPLE_ELEM(3, 0, type_qualifier_name), n) \
        BOOST_PP_TUPLE_ELEM(3, 1, type_qualifier_name) \
        BOOST_PP_CAT(BOOST_PP_TUPLE_ELEM(3, 2, type_qualifier_name), n)
    
    #define BOOST_CONTRACT_DETAIL_TVARIADIC_TPARAM_(z, n, name) \
        typename BOOST_PP_CAT(name, n)
#endif

/* PUBLIC */

#if BOOST_CONTRACT_DETAIL_TVARIADIC
    #define BOOST_CONTRACT_DETAIL_TVARIADIC_COMMA(arity) \
        ,
#else
    #define BOOST_CONTRACT_DETAIL_TVARIADIC_COMMA(arity) \
        BOOST_PP_COMMA_IF(arity)
#endif

#if BOOST_CONTRACT_DETAIL_TVARIADIC
    #define BOOST_CONTRACT_DETAIL_NO_TVARIADIC_COMMA(arity) /* nothing */
#else
    #define BOOST_CONTRACT_DETAIL_NO_TVARIADIC_COMMA(arity) \
        BOOST_PP_COMMA_IF(arity)
#endif

#if BOOST_CONTRACT_DETAIL_TVARIADIC
    #define BOOST_CONTRACT_DETAIL_TVARIADIC_SIZEOF(arity, name) sizeof...(name)
#else
    #define BOOST_CONTRACT_DETAIL_TVARIADIC_SIZEOF(arity, name) arity
#endif

#if BOOST_CONTRACT_DETAIL_TVARIADIC
    #define BOOST_CONTRACT_DETAIL_TVARIADIC_TPARAMS_Z(z, arity, name) \
        typename... name
#else
    #define BOOST_CONTRACT_DETAIL_TVARIADIC_TPARAMS_Z(z, arity, name) \
        BOOST_PP_ENUM_ ## z(arity, BOOST_CONTRACT_DETAIL_TVARIADIC_TPARAM_, \
                name)
#endif

#if BOOST_CONTRACT_DETAIL_TVARIADIC
    #define BOOST_CONTRACT_DETAIL_TVARIADIC_FPARAMS_Z( \
            z, arity, type, qualifier, name) \
        type qualifier ... name
#else
    #define BOOST_CONTRACT_DETAIL_TVARIADIC_FPARAMS_Z( \
            z, arity, type, qualifier, name) \
        BOOST_PP_ENUM_ ## z(arity, BOOST_CONTRACT_DETAIL_TVARIADIC_FPARAM_, \
                (type, qualifier, name))
#endif

#if BOOST_CONTRACT_DETAIL_TVARIADIC
    #define BOOST_CONTRACT_DETAIL_TVARIADIC_ARGS_Z(z, arity, name) \
        name...
#else
    #define BOOST_CONTRACT_DETAIL_TVARIADIC_ARGS_Z(z, arity, name) \
        BOOST_PP_ENUM_ ## z(arity, BOOST_CONTRACT_DETAIL_TVARIADIC_ARG_, name)
#endif

#if BOOST_CONTRACT_DETAIL_TVARIADIC
    #define BOOST_CONTRACT_DETAIL_NO_TVARIADIC_ENUM_Z(z, arity, tokens) \
        /* nothing */
#else
    #define BOOST_CONTRACT_DETAIL_NO_TVARIADIC_ENUM_Z(z, arity, tokens) \
        BOOST_PP_ENUM_ ## z(arity, BOOST_CONTRACT_DETAIL_NO_TVARIADIC_ENUM_, \
                tokens)
#endif

// Tuple.

#if BOOST_CONTRACT_DETAIL_TVARIADIC
    #define BOOST_CONTRACT_DETAIL_TVARIADIC_TUPLE_Z( \
            z, arity, type, qualifier, name) \
        std::tuple<type qualifier ...> name;
#else
    #define BOOST_CONTRACT_DETAIL_TVARIADIC_TUPLE_Z( \
            z, arity, type, qualifier, name) \
        BOOST_PP_REPEAT_ ## z(arity, BOOST_CONTRACT_DETAIL_TVARIADIC_TUPLE_, \
                (type, qualifier, name))
#endif

#if BOOST_CONTRACT_DETAIL_TVARIADIC
    #define BOOST_CONTRACT_DETAIL_TVARIADIC_TUPLE_INIT_Z(z, \
            arity, tuple, values) \
        tuple(values...)
#else
    #define BOOST_CONTRACT_DETAIL_TVARIADIC_TUPLE_INIT_Z(z, \
            arity, tuple, values) \
        BOOST_PP_ENUM_ ## z(arity, BOOST_CONTRACT_DETAIL_TVARIADIC_TUPLE_INIT_,\
                (tuple, values))
#endif

#if BOOST_CONTRACT_DETAIL_TVARIADIC
    #define BOOST_CONTRACT_DETAIL_TVARIADIC_TUPLE_INDEXES_TPARAM(indexes) \
        int... indexes
#else
    #define BOOST_CONTRACT_DETAIL_TVARIADIC_TUPLE_INDEXES_TPARAM(indexes) \
        /* nothing */
#endif

#if BOOST_CONTRACT_DETAIL_TVARIADIC
    #define BOOST_CONTRACT_DETAIL_TVARIADIC_TUPLE_INDEXES_FPARAM(_indexes) \
        boost::contract::detail::tvariadic_::indexes<_indexes...>
#else
    #define BOOST_CONTRACT_DETAIL_TVARIADIC_TUPLE_INDEXES_FPARAM(_indexes) \
        /* nothing */
#endif

#if BOOST_CONTRACT_DETAIL_TVARIADIC
    #define BOOST_CONTRACT_DETAIL_TVARIADIC_TUPLE_INDEXES_OF(tuple_type) \
        typename boost::contract::detail::tvariadic_::indexes_of< \
                sizeof...(tuple_type)>::type()
#else
    #define BOOST_CONTRACT_DETAIL_TVARIADIC_TUPLE_INDEXES_OF(unused) \
        /* nothing */
#endif

#if BOOST_CONTRACT_DETAIL_TVARIADIC
    #define BOOST_CONTRACT_DETAIL_TVARIADIC_TUPLE_ELEMS_Z( \
            z, arity, indexes, tuple) \
        std::get<indexes>(tuple)...
#else
    #define BOOST_CONTRACT_DETAIL_TVARIADIC_TUPLE_ELEMS_Z( \
            z, arity, indexes, tuple) \
        BOOST_PP_ENUM_ ## z(arity, BOOST_CONTRACT_DETAIL_TVARIADIC_TUPLE_ELEM_,\
                tuple)
#endif

#endif // #include guard


/* tvariadic.hpp
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
*/