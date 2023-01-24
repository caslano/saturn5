// Copyright (c) 2009-2016 Vladimir Batov.
// Use, modification and distribution are subject to the Boost Software License,
// Version 1.0. See http://www.boost.org/LICENSE_1_0.txt.

#ifndef BOOST_CONVERT_IS_FUNCTION_HPP
#define BOOST_CONVERT_IS_FUNCTION_HPP

#include <boost/convert/detail/config.hpp>
#include <boost/convert/detail/has_member.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits.hpp>
#include <boost/function_types/is_function_pointer.hpp>
#include <boost/function_types/function_arity.hpp>
#include <boost/function_types/result_type.hpp>

namespace boost { namespace cnv
{
    typedef ::boost::type_traits::yes_type yes_type;
    typedef ::boost::type_traits:: no_type  no_type;

    template <bool has_operator, typename Functor, typename TypeOut>
    struct check_functor { BOOST_STATIC_CONSTANT(bool, value = false); };

    template<typename Func, typename TypeOut, class Enable =void>
    struct is_fun { BOOST_STATIC_CONSTANT(bool, value = false); };

    template <typename Functor, typename TypeOut>
    struct check_functor<true, Functor, TypeOut>
    {
        static yes_type test (TypeOut const&);
        static no_type  test (...);

        static const bool value = sizeof(yes_type) == sizeof(test(((Functor*) 0)->operator()()));
    };

    template<typename Functor, typename TypeOut>
    struct is_fun<Functor, TypeOut,
        typename enable_if_c<is_class<Functor>::value && !is_convertible<Functor, TypeOut>::value, void>::type>
    {
        BOOST_DECLARE_HAS_MEMBER(has_funop, operator());

        BOOST_STATIC_CONSTANT(bool, value = (check_functor<has_funop<Functor>::value, Functor, TypeOut>::value));
    };

    template<typename Function, typename TypeOut>
    struct is_fun<Function, TypeOut,
        typename enable_if_c<
            function_types::is_function_pointer<Function>::value &&
            function_types::function_arity<Function>::value == 0 &&
            !is_same<Function, TypeOut>::value,
        void>::type>
    {
        typedef TypeOut                                                   out_type;
        typedef typename function_types::result_type<Function>::type func_out_type;

        BOOST_STATIC_CONSTANT(bool, value = (is_convertible<func_out_type, out_type>::value));
    };
}}

#endif // BOOST_CONVERT_IS_FUNCTION_HPP


/* is_fun.hpp
5fhNvweHQJ2u4aaTUI4EERaJsvnBH/JJg7YL4GVQyEvIz46EsYkoO1ZEJzN8cIgdMa2FD5Cfg46WvDvaoFEAIbK9sN/SFo3qFmjYk30boO6hbu/bWWg42aBRzdPIbZGGtAUabciojVzlXBHRcLRBYxlPw4vv4PtEOI7G4BZoOJAXG7l6yCYWGjZm7MhOnoaSR15pRiOoBRptycNGpg9Zmz6KxhGexkM7Dh8pivQoGt1DHIl0Exf/jIiGvQ0ad/i/CW1aag9fRqMTo9PGDA8KdiInN3E/LiWuK1tUhDxL21h/i98dbMC7hzgTr82ta48gHni2BRp2xMtmObqHuJA0oFELoBMiuWprg4aUpxHWtqW6CrJJY3CIK1m8heA4yfTTo9qj1I5rc+yrtmmEtiBXbuTeFq4PFjymf9TyNGKdWqLRUv9wJ+7bOLm6IypH819IBF3O03BwbolGRAuy60FOAg38xcNS8ug238cDX3S25GtNw3abDw5pR/y3Q/9y4MacR7X5Cb4cSpeWyiFpoa48iT8oiUY7Tg89qs2v8DRmtkjDdpsHBXuRW0BjMMH1HXEfbF5b93nQVv721ALRIPOoPhgU3J74P8+VQyxXxMaKhZD2iov19+No9Az2JgG7LN+2xj/h8eIr8KDro2nsbKIrg4J9GA3UhzhmW2g0pybkc/YxNJrCB4f4klosB6Q739aSs6eNcoTZc+N5rUdL
*/