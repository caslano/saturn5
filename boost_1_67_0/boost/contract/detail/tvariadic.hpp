
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