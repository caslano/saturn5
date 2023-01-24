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
0bEju658wE9WEa9+k5d5qT8y62X87uPsVOn40Tk/+/0QL7IQrp39EK/N6q9i9pB8pd+2EumdU6KydgWn8OmMxGOwKRUQz4AAsC9Xz5mvDaftikew5UZMPLVKgDkLyG69QN4uHKjPWXhxAhSl6Ma9fpfvkkvYy1VCWc4J5Q7OnctxElwezbkzBdoJzzlNWFaZcYmRGT8bpitGzLiG0/ryAGZsKQIgWpUh57An6weAYy+bMdWi6doCVKV0tTcaoCQ1emqUEdcir4Ox6P/H3JuAR1FsDaA9WQcCTFgmEwQkQNAgKsGgJICSQAIzEjAgSBSUKBjjgkRINChqMIkSxlyicBGVi6iouF5cWUQJi7ITBGR1QUXtMQq4gCDCvDpLVVdPEvD/3/+97/l9Munu6q6qU6fOXudIELrK88PJDlDIPqJCa/f+KB4Fisi7BR/AMXAdLmbwNczgk81x3zFfogEcionHZSGyPY3elEko4Qu5tDZ+JsHVkqYcdRAbRNnK/WBL4O+uih0OLcnnQl6nJYalaAXdj8QwQ6vifA9Yzoofs0JdgkyqRmGGW/SemfYGtndhUWbJpRYilxLSM7KoJcirWmZjpbVvdrflPJqzLrfq8+U0wJxSmTWtahqPME4F1rQ4TAE8mtKl6MbtJ1kdxzMJl3gFe0UX+8VY77XIA3ke3YXNmVjSQWJqXOwSzzDdudlLDKvu9qC7NApIpM+/
*/