// Copyright 2015-2018 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_DLL_IMPORT_MANGLED_HPP_
#define BOOST_DLL_IMPORT_MANGLED_HPP_

#include <boost/dll/config.hpp>
#include <boost/make_shared.hpp>
#include <boost/move/move.hpp>
#include <boost/dll/smart_library.hpp>
#include <boost/dll/detail/import_mangled_helpers.hpp>
#include <boost/core/addressof.hpp>
#include <boost/core/enable_if.hpp>
#include <boost/type_traits/conditional.hpp>
#include <boost/type_traits/is_object.hpp>



#ifdef BOOST_HAS_PRAGMA_ONCE
# pragma once
#endif

namespace boost { namespace dll { namespace experimental {

namespace detail
{



template <class ... Ts>
class mangled_library_function {
    // Copying of `boost::dll::shared_library` is very expensive, so we use a `shared_ptr` to make it faster.
    boost::shared_ptr<shared_library> lib_;
    function_tuple<Ts...>   f_;
public:
    constexpr mangled_library_function(const boost::shared_ptr<shared_library>& lib, Ts*... func_ptr) BOOST_NOEXCEPT
        : lib_(lib)
        , f_(func_ptr...)
    {}


    // Compilation error at this point means that imported function
    // was called with unmatching parameters.
    //
    // Example:
    // auto f = dll::import_mangled<void(int), void(double)>("function", "lib.so");
    // f("Hello");  // error: invalid conversion from 'const char*' to 'int'
    // f(1, 2);     // error: too many arguments to function
    // f();         // error: too few arguments to function
    template <class... Args>
    auto operator()(Args&&... args) const
        -> decltype( f_(static_cast<Args&&>(args)...) )
    {
        return f_(static_cast<Args&&>(args)...);
    }
};


template<class Class, class Sequence>
class mangled_library_mem_fn;

template <class Class, class ... Ts>
class mangled_library_mem_fn<Class, sequence<Ts...>> {
    // Copying of `boost::dll::shared_library` is very expensive, so we use a `shared_ptr` to make it faster.
    typedef mem_fn_tuple<Ts...> call_tuple_t;
    boost::shared_ptr<shared_library>   lib_;
    call_tuple_t f_;

public:
    constexpr mangled_library_mem_fn(const boost::shared_ptr<shared_library>& lib, typename Ts::mem_fn... func_ptr) BOOST_NOEXCEPT
        : lib_(lib)
        , f_(func_ptr...)
    {}

    template <class ClassIn, class... Args>
    auto operator()(ClassIn *cl, Args&&... args) const
        -> decltype( f_(cl, static_cast<Args&&>(args)...) )
    {
        return f_(cl, static_cast<Args&&>(args)...);
    }
};




// simple enough to be here
template<class Seq>  struct is_variable : boost::false_type {};
template<typename T> struct is_variable<sequence<T>> : boost::is_object<T> {};

template <class Sequence,
          bool isFunction = is_function_seq<Sequence>::value,
          bool isMemFn    = is_mem_fn_seq  <Sequence>::value,
          bool isVariable = is_variable    <Sequence>::value>
struct mangled_import_type;

template <class ...Args>
struct mangled_import_type<sequence<Args...>, true,false,false> //is function
{
    typedef boost::dll::experimental::detail::mangled_library_function<Args...> type;
    static type make(
           const boost::dll::experimental::smart_library& p,
           const std::string& name)
    {
        return type(
                boost::make_shared<shared_library>(p.shared_lib()),
                boost::addressof(p.get_function<Args>(name))...);
    }
};

template <class Class, class ...Args>
struct mangled_import_type<sequence<Class, Args...>, false, true, false> //is member-function
{
    typedef typename boost::dll::experimental::detail::make_mem_fn_seq<Class, Args...>::type actual_sequence;
    typedef typename boost::dll::experimental::detail::mangled_library_mem_fn<Class, actual_sequence> type;


    template<class ... ArgsIn>
    static type make_impl(
            const boost::dll::experimental::smart_library& p,
            const std::string & name,
            sequence<ArgsIn...> * )
    {
        return type(boost::make_shared<shared_library>(p.shared_lib()),
                    p.get_mem_fn<typename ArgsIn::class_type, typename ArgsIn::func_type>(name)...);
    }

    static type make(
           const boost::dll::experimental::smart_library& p,
           const std::string& name)
    {
        return make_impl(p, name, static_cast<actual_sequence*>(nullptr));
    }

};

template <class T>
struct mangled_import_type<sequence<T>, false, false, true> //is variable
{
    typedef boost::shared_ptr<T> type;

    static type make(
           const boost::dll::experimental::smart_library& p,
           const std::string& name)
    {
        return type(
                boost::make_shared<shared_library>(p.shared_lib()),
                boost::addressof(p.get_variable<T>(name)));
    }

};


} // namespace detail


#ifndef BOOST_DLL_DOXYGEN
#   define BOOST_DLL_MANGLED_IMPORT_RESULT_TYPE inline typename \
    boost::dll::experimental::detail::mangled_import_type<boost::dll::experimental::detail::sequence<Args...>>::type
#endif

/*
 * Variants:
 * import_mangled<int>("Stuff");
 * import_mangled<thingy(xyz)>("Function");
 * import mangled<thingy, void(int)>("Function");
 */

/*!
* Returns callable object or boost::shared_ptr<T> that holds the symbol imported
* from the loaded library. Returned value refcounts usage
* of the loaded shared library, so that it won't get unload until all copies of return value
* are not destroyed.
*
* For importing symbols by \b alias names use \forcedlink{import_alias} method.
*
* \b Examples:
*
* \code
* boost::function<int(int)> f = import_mangled<int(int)>("test_lib.so", "integer_func_name");
*
* auto f_cpp11 = import_mangled<int(int)>("test_lib.so", "integer_func_name");
* \endcode
*
* \code
* boost::shared_ptr<int> i = import_mangled<int>("test_lib.so", "integer_name");
* \endcode
*
* Additionally you can also import overloaded symbols, including member-functions.
*
* \code
* auto fp = import_mangled<void(int), void(double)>("test_lib.so", "func");
* \endcode
*
* \code
* auto fp = import_mangled<my_class, void(int), void(double)>("test_lib.so", "func");
* \endcode
*
* If qualified member-functions are needed, this can be set by repeating the class name with const or volatile.
* All following signatures after the redifintion will use this, i.e. the latest.
*
* * * \code
* auto fp = import_mangled<my_class, void(int), void(double),
*                          const my_class, void(int), void(double)>("test_lib.so", "func");
* \endcode
*
* \b Template \b parameter \b T:    Type of the symbol that we are going to import. Must be explicitly specified.
*
* \param lib Path to shared library or shared library to load function from.
* \param name Null-terminated C or C++ mangled name of the function to import. Can handle std::string, char*, const char*.
* \param mode An mode that will be used on library load.
*
* \return callable object if T is a function type, or boost::shared_ptr<T> if T is an object type.
*
* \throw \forcedlinkfs{system_error} if symbol does not exist or if the DLL/DSO was not loaded.
*       Overload that accepts path also throws std::bad_alloc in case of insufficient memory.
*/


template <class ...Args>
BOOST_DLL_MANGLED_IMPORT_RESULT_TYPE import_mangled(const boost::dll::fs::path& lib, const char* name,
    load_mode::type mode = load_mode::default_mode)
{
    typedef typename boost::dll::experimental::detail::mangled_import_type<
                     boost::dll::experimental::detail::sequence<Args...>> type;

    boost::dll::experimental::smart_library p(lib, mode);
    //the load
    return type::make(p, name);
}



//! \overload boost::dll::import(const boost::dll::fs::path& lib, const char* name, load_mode::type mode)
template <class ...Args>
BOOST_DLL_MANGLED_IMPORT_RESULT_TYPE import_mangled(const boost::dll::fs::path& lib, const std::string& name,
    load_mode::type mode = load_mode::default_mode)
{
    return import_mangled<Args...>(lib, name.c_str(), mode);
}

//! \overload boost::dll::import(const boost::dll::fs::path& lib, const char* name, load_mode::type mode)
template <class ...Args>
BOOST_DLL_MANGLED_IMPORT_RESULT_TYPE import_mangled(const smart_library& lib, const char* name) {
    typedef typename boost::dll::experimental::detail::mangled_import_type<detail::sequence<Args...>> type;

    return type::make(lib, name);
}

//! \overload boost::dll::import(const boost::dll::fs::path& lib, const char* name, load_mode::type mode)
template <class ...Args>
BOOST_DLL_MANGLED_IMPORT_RESULT_TYPE import_mangled(const smart_library& lib, const std::string& name) {
    return import_mangled<Args...>(lib, name.c_str());
}

//! \overload boost::dll::import(const boost::dll::fs::path& lib, const char* name, load_mode::type mode)
template <class ...Args>
BOOST_DLL_MANGLED_IMPORT_RESULT_TYPE import_mangled(BOOST_RV_REF(smart_library) lib, const char* name) {
    typedef typename boost::dll::experimental::detail::mangled_import_type<detail::sequence<Args...>> type;

    return type::make(lib, name);
}

//! \overload boost::dll::import(const boost::dll::fs::path& lib, const char* name, load_mode::type mode)
template <class ...Args>
BOOST_DLL_MANGLED_IMPORT_RESULT_TYPE import_mangled(BOOST_RV_REF(smart_library) lib, const std::string& name) {
    return import_mangled<Args...>(boost::move(lib), name.c_str());
}

//! \overload boost::dll::import(const boost::dll::fs::path& lib, const char* name, load_mode::type mode)
template <class ...Args>
BOOST_DLL_MANGLED_IMPORT_RESULT_TYPE import_mangled(const shared_library& lib, const char* name) {
    typedef typename boost::dll::experimental::detail::mangled_import_type<detail::sequence<Args...>> type;

    boost::shared_ptr<boost::dll::experimental::smart_library> p = boost::make_shared<boost::dll::experimental::smart_library>(lib);
    return type::make(p, name);
}

//! \overload boost::dll::import(const boost::dll::fs::path& lib, const char* name, load_mode::type mode)
template <class ...Args>
BOOST_DLL_MANGLED_IMPORT_RESULT_TYPE import_mangled(const shared_library& lib, const std::string& name) {
    return import_mangled<Args...>(lib, name.c_str());
}

//! \overload boost::dll::import(const boost::dll::fs::path& lib, const char* name, load_mode::type mode)
template <class ...Args>
BOOST_DLL_MANGLED_IMPORT_RESULT_TYPE import_mangled(BOOST_RV_REF(shared_library) lib, const char* name) {
    typedef typename boost::dll::experimental::detail::mangled_import_type<detail::sequence<Args...>> type;

    boost::dll::experimental::smart_library p(boost::move(lib));

    return type::make(p, name);
}

//! \overload boost::dll::import(const boost::dll::fs::path& lib, const char* name, load_mode::type mode)
template <class ...Args>
BOOST_DLL_MANGLED_IMPORT_RESULT_TYPE import_mangled(BOOST_RV_REF(shared_library) lib, const std::string& name) {
    return import_mangled<Args...>(boost::move(lib), name.c_str());
}

#undef BOOST_DLL_MANGLED_IMPORT_RESULT_TYPE

}}}


#endif /* BOOST_DLL_IMPORT_MANGLED_HPP_ */

/* import_mangled.hpp
DAwJHYF+5ddWvTTxYnFdImB5ErHsmFzBAW1SjNbf4lQeTIIOiECKXwZXA3pa9kgtQ46EOX4fnKz6bHhj0RSHnwKqzn1KNcXnT4Vuiuscxi+PVzHgpqJWuhM5lhtBDlCfOUBT1AAl95m6DFC5/zFJ1WVFrKhLc6zLLdNUXU6rpi4BgBrWUVxNeEkc3Ut5gXjrRG+PdUqScW2TIcGY34jOb01TqQ0htcZlYrj60/6JpLgmj+RgTs1MlWlh4xrj80j9d2IN8gqq93kck1yNfLpyYhjyCbDNjAuvAULLp4MTwpJPUFYKlxWy/hOqrb84EQiIPmtcI9F2KntMqLE9FPb8mrFX1x67x4fRHqqshHDK0vZ/CLfRXyqwyRysPrmwABcL3afgCiJuwkDAT98GiUUEZYnKx8UPLjucPqsllD2dV1L2D5YFVUD/nFb0EwnW9/rGU15eV61Ck6wdEy+vHMvXV1lI/dDKSmcUfncoFPZ1V+UJiaJQZKoso5vv8gkCF5lFIj0vTrzRSiwOtcTHANKx1Ukq+Zxb/QTROEhkFxYOiIVUd+lz6n+Cn9PVpUImN0fmE8ftz2eOM1utZO74z+Mi3xp/IK7dW9YG5OaJEs2DqXlnS9CoEKCQHpIpccxoemVA0yvhNYNeG5VWbeX0x/xVcMIXHJozgV8cSoSPWQUzgV9qyfEPkSVh3xV2jt8w69Rw/G/KKKa+4R6rh6MWdaz0iMl6cEESjOcparK+t8BpsqYzHOjmqeseym4GCwdWRFK0Dm5NPaqvGi6Ksa4aWqDuQvCc57SYX39lEbq9dFQBW4JtklgxmobVxDHwl72caVjxgb480ZBxNRux1pKwzbrcbsS6bMbJGbHwhDkOlHEWCEiFRIA6hdJLzv+jpP1vtJQ2tZa0Ze5TI2kDVjF4fKRSVCMjyRd1EvD+6omK94dMCq2oPoLn1zH7ELH92CsVnl251xBHBjAUFtslxFHTVArFcKYu87BSEM67EZiJxWOBW54EjQ1OBMzPNgAOXwVv3+Hb0vyTv/5IP/8w8jc4/0BbzbNGqFPN7bEiPcHUOL7XCykYZrAJJJ6Oie+MAyv1TrUZ5GAbHhv35Dxl8y8LPA12fC90WHACrEYjYZ4v1cYbzjvR5gGDvHQNKBmA1jyuA/nSirBrxUYRghrn+UX/N9ad/wM6Pq94BkRHpzRx4bfyq0GSb/PsOIfv+7oM6DK+H1ury6DD+En7xyPm/XFx4BxlvDVI3B+3Y7y4aGnr+DpftCT3v4br98dlAzpe4Tjmf2M475eNR0ZNFxEO/Pg85VoRm8s3vubYXGb97pLlXwz1tMazTey8B0r59FG8DmO4imn78CGeRkPs/xI+AbsYYTc+yDt6jvV/mMrfIOo/GCCqj9/2BuXHe5hPiJPj52IhQ/KVGGn7qLMYiQh2hHZKxMwpt4g2+zYfj+x5xO1xh/KZm77D5KWja79fZ1vPxjysBuLziPH1m4XkGoMF5Z0B5L9CO64figWPRwSrvgM+Qp6B+Zp0SxXSjedbJd18JN18unRLNaVbKkm3VCg9Fkv3eaR0Ox3f3hlV82nt8Paja4zvI+XfMGoLuiYbBBuINaXHFMa07gxUw5/S8hjSWTqjzhLVeQ9kj1rbDPL88E3hW/eVxEKJUZg3HGnI68sq+vjQPN7YdOF7+jCpQNCkcReZy2+laFi0PZABHbXvZpQ/0QG68riRWJxuc/FtVDJnFuT8s5kzW+bMppxF6bj+8cC0yvIuRZuVSdE74lZ3DjaxqTTBFiLBQf/Hr5p2ActN1AipQmeZghoKcdzgo6qOlHUbauaAHQlaEua1Vu0wpGd8iHYIXsSAGWTvK5zwFkLjXEvZEzk=
*/