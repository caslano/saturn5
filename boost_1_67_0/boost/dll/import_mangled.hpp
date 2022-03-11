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
uwp4kv6qJ1f2vPUhEI5ICd1LVvUs+ypnUFu+XO4fvW40yoVHPtS0SFIox6Ikq8nDMiEP2cZ5zrW+ULzBtb5Uuja0aLpXFwJvtkF/kVT1Tiu2eBs7oWma+6L0LyCEYFVAnK21+KrPid9Vc6zq1jBSb6xf/bt6i1d7CGGsDleMBYb0+1hOghUQNgTPTHJwyCQex9+7pVH4ls2BIaOYs5gCGfUXysc62NVrgByCVf3AG7rdosjdJuT/rYBAGTsB9CSq2ZkAZDcACXdzQveDSO+qqwtodQET0qlOS7/3VRgAlQfSebryiO17DxoP6bYPbuVD+01IgalqYsjTmaee0LxTtBmqik/lNUMmdjAZKdcpN/Yy1ygQclYALoY8H/FzbTmS7vqfWkyhlWL1GfFaeUOmSbwykqYdMCHfnShgjz9pMWm1eCc34K+p8h+cvex/rEkj3kSezmpZLDc0JSBfeYakyeqB1cj2DvWYekvIM5Sn5lpZaxcwyDkpCiqtgd6OV5vV2zgIVOC6i1BAk3rUAxu/UXmLXhmmvi5j5Ogdw5MTJm6BXxG6AfdOTT3rbgaBMGYqMHeZzV79OtI3uVnYb46TwPvz/KVjxunoRKGCCgVk4kiNMoRoF+r53JbDFxUPc7dUJioCU4N9WcGoT71iM5ArkK69k9Uv/yvJFWTBNKzQoFdw91eOV/sjdl48Vk49qTRkIOp/DmMGMteguPKSSEZK0wXS2KndrcKoPEPKbJqANfmoyK2mgKW+fRLw2+J7gN/Ols4GDRMSer2vmUBvsZZ5QHdiAVTdaSByJYcm2WAmlO59A+X9ztdhxnl6gTHUXjY5BW6OsfehpSMOQ6aeVWtwygKLXqN6HNWt4iR1cSb8SVc3Hh5mZHejveos3Pr5zGaXfZwCiEZRo22rwqnuseryq1/+KsX+YBPif0pob3qSIzdyc3ZkuvxbfGuKXM9FWOTyLJJgwBm1+DexRakl8TkK6KvokhB/q1sfsDjfjiSob/GKvFo2CPvR9CociQlKd7MIwo/kHxvzxiBqosEhTcsiuczxbv8jUcvr9QdQt3kaoJQx/LTSJNK9cngOJ8/MA6h/isC02dadluT4FP4Nwr9EGNN4/d9ncP9v+KdLKec5mBKuWU0imBu3ul5GeCu+a39TsHlZtHa0aXmg7PHl579yH6u4wuc8U+KSbH77zqNqPxC9oMDH/g8Y5E7py+K7QRGDqHEYmml6PPNbfeoHzreBK10P40jsVb2A1QJXvk2c5tqGWBcz1X341/2lOIFQMbcTtN0BfASz6nMV+Fkl1UQ25mmwMRfXuTwd5XbV0+VWUXXZa59AuRKeo/ZyI9QL061OF7ezECtvIqb8KMZgIt2fqb2nythkrkvoCNpcQld5ijMMNknkRlXGBuFJRSq8q7QGyLaJpKtCx+PnD+EAAqYsGenjDVjUE6z0gkbmnpa+4lUUm9J4MI5RfZT5kcG7qbPilYAwNEN+tIxPEcPy/Eo7iLQs3ffDcQ42eSJMjd7ly0H2F/hQNexCEQ34cA9omqvIerc4Rk0pAGN321ozSnxQH1PVmv2c5a8gWaGLbodai49pRjGPeYjbNt5pcUYrt4JcNSgWxRywWQNmv0J33Cpge8HecVVkite7SHSKKQDIyoF4M4m4z+8fwXmW2Oy/feVoUwkAmSgly0GHSfSoShPNDnGB/EChSUyWHyg1id9TzaH83mWgHVShV1vbh4IBcFm6n3CZxC6YURpkKGYuElhq4qCmW36sEXo4kmYKTKlfkAod/hX8CPUr9uH3BzVvyBNlzw4MoGmGLRKBJBt75DjMLika8rSzkj1IN+Z1nindtgYFVPsC7+aiIaWIsYutZGGO1iQGBp/vY01jv+aN9jIPNIpc1Ost9WI1T/sxYSiB5e8h+2ISDEIu6zOJ473sg80wfarDZVYvNPKTL7C3bm9pBu/LqxR1s0d5P2mlaIOXotkO/AKFr/1I0+Q1XaRySztW8wqsNAZVF5SZfREb7PSWblttNNjJBF5kDDBPJ5R54SyW6fCW3hUr08GuijXTAUWsX2i6sGWvAKb5cEzsq2fxcRQf7zQjwlk+IBf4tnQHsFV9CaL79ApA9wdOzf2hveo2nDIbwNa8BS58Ic8WVog2vbDFq55QgkPsvb+DGSk8ExL2ABm2a+lV+1Bz7ZHDYIbglMKRwkRRDjnQRAx2KcFusABB23El5zpUj5O86s84HWSuvKAmFlZlNONBpVoDY2EKYru9aiKYG6RJ/QXqLFSfgRk4O94DSZIldAXStFeo6gkv4jsREOrXnZoWFtSA3+QM6iJBqV4Fphk211y9Aq7iVHQI7/P8b9pAS/vjGldPyOHRRr0RZWF+UbmAJWL2D4MIfa6/iD7EM5q0TUs//DKaUghe6BCK/5AEBlhdnZmklVNzHTqMczFbVfvhr/yVJs5CL7s9K7+7+u2K61WSsO7jlQnq8awjWUK3QuXcLeBnNF5Pkk2R8Qno+nS0DdQToGRf+jeo+TTXIRL+11z/CrkpJFezSO6qMj7JK9BewTtvxOLH/0IquhvsDgAexODCczBgdQc5GeKlIP+2bedyaQx/ShLREBj36wJD9gCTALNUgk/FUu4ebToamFO/C5lr/Q+QuZj6JjV+HfQBLOLUiEm+hT0IKXeqgiOLxigzC/iNOP9gsJXTqL9ucia73kRUO7BNsNma5TsANKRqTzuSQnC4qb59ayPd2rKIE7JkMoDYmQe/pcVaatEGLVb+HVvMNVqswLHirKP+UPrI0KXa62x1v4IYCZjtjzQWKFKH4mmB2i6Y9O7z9qpF2DNBkUU0l4+BzqtHHlA9TVmew6rUAXOusWIU8PYJtqUf/cL2LPD3LkKnufYqRn+qEQZXxSp71XmcM2CD2/IKkOXKyYGwV3Whd9iASsJedRrZWnKEcuYAlCB8HfWkRH6pJoc8p/NQcUyBSaxugDHvAarBZEvW0uvREoSRJePgocgcLN3GS2szoCIIEjNbtwbFdxv0+IjwIYgTki6LLwxoG4MfmoA3EgmotWSOnUZxcyO8i+S4gi3iJVzR7OBs5Bzuq9SMTqA3O3JlfP+rIg5n2FWxQj1p3x72soF3QGrvLwShZTOMkknxQRpw5G7iBlfrIDJX1HmGDOyiqFLUqxT1UYiJmGsXMVcWMldNjLnaqzkr2Gu/MHHGqeGM86GJM04NMQ63nNmzsdLoI/l9qAkQ9pPIFT8FtlH7nWF3g8EVYT9Y4AJj14Fr6R60V/0aKvngGduFk0zozhV/liuVoXZKwVZOofnsLXUVrxJ/5Cpi0kqkhC3Pj9jj5BZvdz2NpBYXIJkXjSCzdLOagiaFjuersMUUxOmpUouO59ThZ5p3dTGYMhRSeWwx2jI28Pbr38E5e7QA5myRTfF0sru/h2Tv9LLJ/x7QUAFXn7HX/gF6KCEfyNm6qEQROkoUz19LoE8bKim27y5AEtjiqPjWmwvAuSQOquwlHwRKFICgZsW3jwaEPg/NQvvqv+1/PC83pRWwR/uhH80sjQcXust+0OTzsiZwq+UmW+QqtaX6TMXlznC1VjFOze8qUdPmlyhj5caEbHdz+Re3S59ASwVsO7QAdAHDT7RC32wRDkHoZGsLSPGBVbPhEhiklI8+jSL1NiefRlVeezgRgxZDozB2Yc7ohiILa4ChyHF80waKF0ZhVVzsnpXgxlIwAh6kwIM8etCVQA+Sm83TTkFdK9RVa08jm/U4WCYYG2ptu343Du54KA4qJLKrV2p61IwskMr3UqA5C781s1Efwu1Skebb7s0WE4pa4KD7ToKrrcAYjoY2YdmjAUf9F4MOB3vqLhyXmuoFHw3UTAMG1aRkNTUDY4019agP+zVpnKuhBWcDeE470fUBrQLOix+trZ9aoYMiK0U+SecHU+AB+ZGJDTgNFAFqkc3t9eMEAOlVApapdgAnjnrCz/4CE1F300M15dR/qAYRppZZwP5eZFUnqLd5fcDWD23hbG0Bh/xTNJRPMDv0xtVJtFmITkM6HK6CseK4YmGFPAwjk/+4D5oFmxcDlDeAXdfPEqxoGQ6FwPHR7rdo6ftBOcLzZqGfaLoW2opcXd+CsVmOm6T6bXCjrbWMqCILDstub1yp3YhArxcLAZQ1+4cAtzjPxTsDQwHeHY+p1OxHHMMIEKYxKjDyCW3ZDHSgarn+lKMOdSgk2UAT+Oo0b6YcHNKkUWpiQMPgygyMPaAxXFr/B+TTW3w0GTHc81Xo/ukFSnCvIrxoOCn2arsF2nyMXB3fDHR+embhkwWz3Q8ijexbvsBOHwAJLPbTJPI9iOSTPTth3irCNtfWFjLGapFOQbJOXLcXSna30BVMArEVscIUjJxDr02Kum4vhcEcA0skUejCwIRnr/oacUOwy/0ydl+eqORH3f3B+WqjunlvIjdqLGpjJFndiDwG1Olgq5OROp1oJqowirUxAnU0Cx1EoFO/AubZsMokjVU9L2qzZiDbgskBCNxphLHqnOE614JCcZxrQamUqkp7XTWFSKPLIolwwy2ynVwKJqvCNoDW2Qojs1ehTHfVYllxiasWRy/Nh4FJc0EWg30WCrZD49l1inBaFfYmHaZgqDjalWsRkwDUSLI2qwnAQVMgHnjAEmAjcROZs2v2mGItQUOAKhjZM73/hGKbSOmgEyO1h4JhwrfQCWgT2kJCGNhnIxi9gKVn2OREDKm9GBKe8bJjF0CQJBLPaNKLUBUNiBPANxl8ljyjN88e3QScvSR+9NKc/zoucYxcZjH9j2Ex4AR7bSMF+jpBNnZgP9QeAY+4JmWpRy5dQvSbg+lgeQkwmOCLKPjBTzk/NIjc59kDBBGnIfKvCdWg7HQ3SrQSoGZb3F+JieqdFm8et6IVYY+OAN2GVqUX0drwOuTgHpM4FrzsRHWdRZP2FPAKHDEdOsAsuBEVwDZ5zQ5TjIMQGV3NwnYijLBX3djHTfRQcB+8hQGh8KrTR3Q4JOwbHtF2VmnWybPdy6YOxchjQBd80Y/QpYXun1MQCyZMGKahQcBJUDJgApz8A+Sldv9swKd2gFwFdLdOsbFD/PEp7QCa7WzdOZgZwZ0aunw7Sdd7Z/ChbtdHwh6qBGguyhtWmKRR8pskgcXr1CcpTD1Ru9+qXgr9q5dDVV3y2qtOQCfVZ6SP0Q/33MlVZHb9P1D0HFo6GjwV9QMleNh1CM1hezXOGdehO+gazSmMcwv7MW4m1IeE/RSRSe+nOCc4gq+gMT7SzDfVo7UJZbs0ab9uu6izMg/yaAevob2Hgq0IjZbYvTSaWuSBoPsNA/aYYcCCL4KmO6gQ9s/TaJwrUth9HmwklUKGh06mmHpsHN6RrkD7Bm7RVbzrqrjLXs2wdMlNFCNoYdd/NqD7kIkyl3VDZMW3cy4MOzUl2OQSrMENropCMR3s90RyahWhHZ7aa6vIdr/XXvURTo9DYdS4V6BRFybzulCFqXMYp84x4ZTJVdYnWeDCfA6egaz1hNGM/udZNLFPgZh+itRplYkkaQsrghc9CrZbsVb8cXzjTdT4Cmo84VsaT8DGm7BxRW9cnDpcbwq2TpbHYC/aZk2Gsb/irIEMVaVlLykcWmg1w1ibhSYzWcst0I2uT1CYnGDvfoVTr8sttINuF7rdwmmxolmeDbUtCHmwSUx3VYgiOH5tZI2EZBQFkRSoWvcY2MzNMZmAwdUZOjvogfQWrz7tkByc0HXsjVMppjin7rWXQSiO0bng1bYU8E5acORbYWxs5R2c3W31mXZg9x/dTpZTreHlTsPp8Rtac+OPQvlRjG/RqsfkG2BkuRbmc3KvkYqgBWNG3KEXFavElumeVJTsu+mFaFIz9KSOctyamQnAqToD/H9gR2wNdC0tIPybcL/o40EjjPPuvwDybbdzyOfUywj5OIQc174t6tnX0Bp0nnE3rl8orp27G/3CXzXD79xn4WfdyrnP4ZOaV/FJHT65Y+5v6Qk+n7sXn9w6F31O0dmzDe5eM5FsFgV7zSYskQC36zLmJuKf++cm4Z/RSV9dAAu937z+Hr+vNGV4hZjTiQftVx9PMUXmf8t7V7FVugHjd0oRA6dNS59OxGU8Do65AZoURQeLsdWA6k2VFoROukGutI6Sprh2kQ02iUfSVYfaoj20l6t+K0i0ns4kkwmqIE7s1X9DWi6yyv3TxFFy/1R7NcpFXtN91F7VgCxZCJ42Iudc9rQEe9XvscAEnxdNVcPhfmwER4SRuErREEudxhli/nfQ8KfXLvm4ph5Z5iWO8MdxxGGDI8LEERMLkLqHybc+ZbDE558PaLOLTn2TJzYXDYU8p9jMLqxEMuIIFO25BANVfsumAULPjYCeVGkq79J9QrzCtbxQzHAtv0saD8718hXkWj/dpGk9713UtGEc7LEgDu6yVz1p0ZHxEFzwRu3VZ9G991vV43JPqr2qAw2DnkvsVW/SxRgxa/FiceoyV+FqmA8tOIPu6im7aMSZX4S65zsuD5/v6FkETcr1e6CWucKtbqzHFYOjYprPV+o3xy2VgdC/wsCZ820Y0HX2R44sg5YwKHNlDGx1435qwBAVwwuf9ipkTG29jRfU1lt52VJTfDc9py8gjD5jOaknBaV2oddeVY2UbolRGawCXEZi11zHKV1487dR2jKC0tF4SiexGXfRPI6ntIUlRv8LpdE77HHgQA0c+b+JI3HBSDSALVSYOSzEcn3D2IgMxXC2GQuzxz4b1Hrexadxy2mAdmtAg3mINuDJyF+B+Ogm/OpEAjLCJXj94JtkpTTBnG1SilqMOds0PGd5N64dhykutQsXbIu6lKJuPsn58l5s1ZmWPzlcSzP5u0BCKL9rGX/tIBnQQiZD03BU6w5j3IdHkh+Xs5vyOChY1X5QaLEf9DQ1djnGNHqRCXRusPCqPV9eGIkWxRNGHh6l3QcttNDI0DIOK0XtStFppahDKeochjsnE2D1tOdhiZHgto8A92oQQyg1pcvgpaEumpBEC9HauRNk27fUykDhhbXsOkYLV9urrvnWsvZqihAusszFsJp4Gcl+cdxcrC6OmZuChKvmEcIWHQVSEy04Gg1UPTRCtB3WmR4TkthN13Cm/9F01HctGK1rUk9iBETbttEcX63eYPnDGDBhc/OQ5evjWT6FOXr+C8uDZMMgCis4QyKx54rBrzOnvWrKgKZhEO2TBwc19sRCHhYoCqsL/jfpgehgHPSAe4VrT0cCjvoO1J8/WYCa33nGteteWteklBgBFMV19gczyEd+E9fp2FUBc7G96ja4zhUrcvmqNPzZZKZILRpFuHYxEybOa6aNJlNJdaM4XaUAosyS1F0r0AtWTzbXrNBDyyy9RdMUet6z0GIg0X3CXnUnyqDl4LLm0MUKe9VcuPCxaAOI7Mssw2pLus61i1b1gEE28iepbH0yri1T9sO/Auae67CNXbh2Lc73edlVHyO/p/HcCnyqPoptJc6foS6Z6fct9oIdyJ5pBfPrqDjOj6kxJcc1zecLJPb0oIrk/U1Va6qoP3Gbmm117UDOkiZS8e/x4ik9lBJRU4pwvO8qXCF+pG5sR1fkuAG9uFiHax7ApXwEcD3K4XqU4OI8NW+muniGP+u4Ly8XW0/mkNmpq7ZW6iohskwHa6yBBnvVf0By+iM36Ij43ECu5NaLZg0XPU75EepJGImXlfE2gSfZXR8Cun+Hxi5v5B0OjNyT0PMziiBPVeciue1VXuKBqo3EJwvsVel4n8tDDjJLtlcfH2FrHDZsjVd0C2PYvtgdm4Tn5qENkpXA51WvYWk8dyWfih3T/relEbM9e8nS2OeJ2Z7CGMPSkD/ByTjm2ybjGDA22PH3jTwOVghFe57gyXn1daA8as3xXLvR4Nr1Btf+jC7AsVqDmnUOStpY6WVG6cV66epso/T34CIyAybT+7GJdIk+kcJJPX8aGm5GHIuWjQ2qSynA6mfgFbcJpbGczPaqbCAuqdHAuOH2uFKSg9Zp9urt37TxDV3/vckc1/dO/d+6vjvezk9iC+9AtHXH49rCLu3+77imYHDRe2Qh9NReNMZILDdbbkwImPUZYDmGCw3uQXF8wIyCsBnuaVlh0d81jYm30VoJyLZEB8i20PdRtp1L6vzFBIf5zQ74la6UU+mOBYGTMNIw78yAVjr5KShd4wR3OJQjggMBXEpLItmZePkPvPTYXGZ7dQf5d91ers4N5d89rPx9PlzSAJO9my3/M4DagtR+lviffGlaTHEJ3cHrXMvvFa2uXeS7egwmLwSQkM83fIz+Z29kmmv52lipqQaJVkApPfDE8qhklIKuwKV/gtvdOFJXYZ94I0CtzLMBdnwKCo6YR+lDhzLOEQF3IZLgDLOZ3+f4s9T/EfHnmauvE7DO7YOaUwstFZXgEF80YL9da4mP1V/SnGKKi+SvbsDbWJx/J9RvptTOObm0mmBhQ1dgpIEWBtjhDwY0YpxP+UNcO2DPw0OloRuDbBQlw7WF0C6KRbiVDRZlg1XZYFMapmHQoWE6/c6g35m4BDWar1MoDbPpdw79ZtPvQvhlfzsAk2K0np7XDjdKQxhXQWowRIjRWLkW15g1n3oFxl0AutFKQydlllioFSuVxjV9pIPScJgAxeBZIt3zLBQMGmnvhGoQSi/PSMNbBMqrvaNQWpTzzILSHT/GdZh2qkP5A5S/YmS48mzVHfTrpV/sRCG2UBpy6QkGptjDyM1bqC3CoQz3gemFJUpNB8rsFk2peQZL1+yh3730+yL97qPf/fRbTy3eRX0U0u8KetJG/WEGzOaVU9RjzDJntOmokdDGnvpE084JVrOYUsBu6hvQlqvHKJmmfg8AdDRgrf8rMlX/rchUPKnGh0k1kof1Xq5nprzyPl9qw9wUYNvcN0j8qvP6wDJPLy38v3EOLf3e/Zg4y7NpIosxUqon2nzGtv8dJkMNZeiExVu0fVVkakfZ4b8OYCK/trZPnzax7BzxhN4UBRjEDwcwT+RGN8/JMdWP1hwOlnOrngQkUhKQlKJKGcOZ/UV8KOn0yh4Ho5IcuY1vLYBuZhnAZLCbCZiMb8kTevdvOJczABIlmbG/Eyy7byVY6tugXZ4XzMYWYna3UuNNQVrdRb+F9FtKvyvodzX93gu/zclRqNxcsyqF8yqQ5WizGZ/1uJebjJXl7JHpbgWqZFOEFj9GtNUPFKmftQkXtVCws64=
*/