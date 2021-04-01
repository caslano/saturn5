// Copyright 2016 Klemens Morgenstern
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

// For more information, see http://www.boost.org

#ifndef BOOST_DLL_DETAIL_GET_MEM_FN_TYPE_HPP_
#define BOOST_DLL_DETAIL_GET_MEM_FN_TYPE_HPP_

namespace boost { namespace dll { namespace detail {

template<typename Class, typename Func>
struct get_mem_fn_type;

template<typename Class, typename Return, typename ...Args>
struct get_mem_fn_type<Class, Return(Args...)> {
    typedef Return (Class::*mem_fn)(Args...);
};

template<typename Class, typename Return, typename ...Args>
struct get_mem_fn_type<const Class, Return(Args...)> {
    typedef Return (Class::*mem_fn)(Args...) const ;
};

template<typename Class, typename Return, typename ...Args>
struct get_mem_fn_type<volatile Class, Return(Args...)> {
    typedef Return (Class::*mem_fn)(Args...) volatile;
};

template<typename Class, typename Return, typename ...Args>
struct get_mem_fn_type<const volatile Class, Return(Args...)> {
    typedef Return (Class::*mem_fn)(Args...) const volatile ;
};

}}} // namespace boost::dll::detail


#endif /* BOOST_DLL_SMART_LIBRARY_HPP_ */

/* get_mem_fn_type.hpp
wTy3VcWLOaeKrtlpy/GMJoeyJFs0L4ku53GwYpgp39ayCCQrToa4Ckm4lG7kFfPhdGUBnPZ2NgK+UsSlCmX6TfwkPssaDj4uzsGQklT9xbfeZpIPkvaMyYse16pcklYRrO5cvteJYG3rLkPnqeAbZXHTGmsQ0VV6WfVixgv7DzdYnQfLZrs0JqmR6VSzXLM1IdOQYyCXbVej4t0Jr8ZSLHOQQUe9vQIpVHglkvjovlIMUNUYK84MUSIg17wYp23lHRT96lMZZMylFTM2sN76HPyv3vUZwXCxHYvZYmKIZMsTXC+3zJV97v00F7yze58KRdZPb0HwBWMyFTCOhU5lsg+lttrdthaMBPyJ91ywAUYMoL1Kb+Q9i5VZKlrKqRZ5JNZdUXhlsCvjWBnvEJVJFN5m+LAqtW4Z+cQC58iQdHp/Wg9D2OJB4t6TeNnW8ujTIuE8yQYzBnm25zMVWsRv2ZU/Fvt37wFoHKA2Twwc+DdLyvanor5LUuHKFHPII0bQlRCFOMt0UL31qLYC1h4wQXQtJFX/XwkkI+kyz4uo2yczW/Kr5mOZsLd7AQ==
*/