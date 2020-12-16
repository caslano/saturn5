
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
T5+RGH2M15XMGvelufcpVYb772Nw9lXnK9sTJ4PUFSX9S4sr9F6Uycr+mOlxWWz+LIjDlRqVla3PCjr3xaURRYsvcOzQVGWHYrLRKFlqY59hb64mrwv7TIqkxlK5To3+9YC10Nw9Vt2Wyuul9y+mhVNOOO+mlubL690qg3sVovXeBTmXp7Ir/g1jLpOORXs1l8cm7FzqUvOn/53kPLpTyoydoEZi9ElMNWdrDdl09p9JOr6l6WjU7NBR5QlRJvmRp2Zhb/Nco/rjOGl+hG7K35oV7tDspNr7t9At1D0uhrXkTO6EkFLuznXrmvXH0TXvhNA1g7WuedfUNf9CP0aIE56t7J8sP8Du3rx6/CKBNZeN2vaFPpctLW9GcqyqUP/WOvB9x2Zqfn2PZ2Pvljpp5+iT2kLdNKH31zn7elVaSj63SJi6p5m878J/yUdG/ihh6KTE/FH+HXHGvSOGLlTllJ4qHZVPwLCUGLivVF9U469nk/KVOVedyxk5vWf9A2Oeeh1jvFW/YzCuorhc1af3XJdyM0fw/uOPqvqoBTn54zUW0r+pb4xjN0yskp6gNkFqZOKWkUH5ZdkBQXWnR4eswo8/z7XMs5PqaLHSyx8b+sRsgrLkyb7LZ2Ov2HHudXLu9EnLmlBlfhoF7wnSWcbebSPPx/7lLNfdQ62C+fLkc5Ha6G3cYxERuFfEeN04h982kG++HuxzuxD3DCVq2/KJMYcdXfPjwpMhyd6jig5Pzassy892CGf2QTg0leQjHb6Q+xPCPpP6+9/MF+2ryO1g30TN03XU3Af3pI7QfP25ifP+JP3jyFVDQ66c59parpzv62yr2n6BIVjOg6rTpk513lneT2HqYO0X5uLQeH3+S3O9RRUFBSXlpbqe4xRQdQf3lhhxIUvHhfrKvSUag38Z9NP8vqtXzonpnpnpaj5C30/1B3hP6uadWjc7vp4ZK96l9/is0PubdstnHUv0tmK/Z7j+9pre0/QN+UWBcSsKKQNVVCz/Vsg1nLKAj2TkVxT55GZ/iPj7crZRLkSp/T0Mn3dvX7NVyObQ0UzTNJT9/lbPufltI5lm3sf3nd7XFCGqxlIP9FU0UGW/VvXwPR1VVtNUf79MUsKk6Y+6/i66/p94Dn0/QaizDdwloOdL1vGL0X+nTvd4vnK1d6SvvvPRdS/O66S31XuRzfsMf+PZucuPcWifxqRFqPeQrH4i9Lcrqun7y3ZqUoe5TzqMZ3NuavHs5MnxmeM8hTzzuZtzx6ORz7syX+0DdMbSxaxLj+U0o53SFv48/qo3w8lT76r+6XzzO9Eq39NYpis50ftxpaw5z+Y+eGc+zL1+Tfr556CppodT3uK5f3PNU8a9Rs2NPlFG5Zt9ammMp56LpmcYbTnzfabxW47D3NvYhjz536y/rdE+ukP9N++bbEe+U6/Dy+37GbxrBXSIlyiKN2ZoTHKKOvk4vFePgC515xFWidRxsVB53SKFiq+78/g13InNu/NwHBIxRv11fs1Q7+o2xe/z0gYNzhCh+zo4Ychgs6/uPPlyj27q/iQjXtMRGhllk1OSMy71azh3qhN3t5Ru9sj98lbV7x/I/OB9TQUlzi59Mz2c9Hhf2djy4hLhpDUjLYPb8qt+YyJnwnATL/F8qfHcUeZr3OKknS/LuNK6yHLqeJTEW2XGvXmUDZHei3R5aiUYAjbvzTO/seLctzAhPa94wjD1FQkjPRZ6BE4pGPefJxl0iTT8hlSRl17OqaeSinLjbLNMG1JRTqLpo4xU6eqeJ3VmtQFzeR7z6PzLEzLWlpaRmSqPZA3za0MzRfl1oWIPCUmu0y9RUQlJxvFGWZOZEP27F6R/vuJ/6Dym9DU=
*/