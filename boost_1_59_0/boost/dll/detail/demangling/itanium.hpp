//  Copyright 2016 Klemens Morgenstern
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_DLL_DETAIL_DEMANGLING_ITANIUM_HPP_
#define BOOST_DLL_DETAIL_DEMANGLING_ITANIUM_HPP_

#include <boost/dll/detail/demangling/mangled_storage_base.hpp>
#include <iterator>
#include <algorithm>
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/is_volatile.hpp>
#include <boost/type_traits/is_rvalue_reference.hpp>
#include <boost/type_traits/is_lvalue_reference.hpp>
#include <boost/type_traits/function_traits.hpp>


namespace boost { namespace dll { namespace detail {



class mangled_storage_impl : public mangled_storage_base
{
    template<typename T>
    struct dummy {};

    template<typename Return, typename ...Args>
    std::vector<std::string> get_func_params(dummy<Return(Args...)>)  const
    {
        return {get_name<Args>()...};
    }
    template<typename Return, typename ...Args>
    std::string get_return_type(dummy<Return(Args...)>)  const
    {
        return get_name<Return>();
    }
public:
    using mangled_storage_base::mangled_storage_base;
    struct ctor_sym
    {
        std::string C1;
        std::string C2;
        std::string C3;

        bool empty() const
        {
            return C1.empty() && C2.empty() && C3.empty();
        }
    };

    struct dtor_sym
    {
        std::string D0;
        std::string D1;
        std::string D2;
        bool empty() const
        {
            return D0.empty() && D1.empty() && D2.empty();
        }
    };

    template<typename T>
    std::string get_variable(const std::string &name) const;

    template<typename Func>
    std::string get_function(const std::string &name) const;

    template<typename Class, typename Func>
    std::string get_mem_fn(const std::string &name) const;

    template<typename Signature>
    ctor_sym get_constructor() const;

    template<typename Class>
    dtor_sym get_destructor() const;

    template<typename T>
    std::string get_type_info() const;

    template<typename T>
    std::vector<std::string> get_related() const;

};



namespace parser
{
    //! declare
    template <typename... T>
    struct dummy;

    template <typename T>
    std::string parse_type_helper(const mangled_storage_impl & ms, dummy<T>*);

    template <typename... T, template <typename...> class Tn>
    std::string parse_type_helper(const mangled_storage_impl & ms, dummy<Tn<T...>>*);

    template <typename... T, template <typename...> class Tn>
    std::string parse_type(const mangled_storage_impl & ms, dummy<Tn<T...>>*);

    template <typename T>
    std::string parse_type(const mangled_storage_impl & ms, dummy<T>*);

    template <typename T1, typename T2, typename... T3>
    std::string parse_type(const mangled_storage_impl & ms, dummy<T1, T2, T3...>*);

    template <typename R, typename... Args>
    std::string parse_type(const mangled_storage_impl & ms, dummy<R(Args...)>*);

    std::string parse_type(const mangled_storage_impl & ms, dummy<>*);

    template<typename T>
    std::string
    type_name(const mangled_storage_impl &);


    //The purpose of this class template is to separate the pure type from the rule name from the target type
    template<typename T>
    struct pure_type
    {
        typedef T type;
        inline static std::string type_rule() { return ""; }
    };

    template<typename T>
    struct pure_type<T*>
    {
        typedef typename pure_type<T>::type type;
        inline static std::string type_rule()
        {
            return pure_type<T>::type_rule() + "*";
        }
    };

    template<typename T>
    struct pure_type<T const>
    {
        typedef typename pure_type<T>::type type;
        inline static std::string type_rule()
        {
            return pure_type<T>::type_rule() + " const";
        }
    };

    template<typename T>
    struct pure_type<T volatile>
    {
        typedef typename pure_type<T>::type type;
        inline static std::string type_rule()
        {
            return pure_type<T>::type_rule() + " volatile";
        }
    };

    template<typename T>
    struct pure_type<T const volatile>
    {
        typedef typename pure_type<T>::type type;
        inline static std::string type_rule()
        {
            return pure_type<T>::type_rule() + " const volatile";
        }
    };

    template<typename T>
    struct pure_type<T&>
    {
        typedef typename pure_type<T>::type type;
        inline static std::string type_rule()
        {
            return pure_type<T>::type_rule() + "&";
        }
    };

    template<typename T>
    struct pure_type<T&&>
    {
        typedef typename pure_type<T>::type type;
        inline static std::string type_rule()
        {
            return pure_type<T>::type_rule() + "&&";
        }
    };

    inline std::string const_rule_impl(true_type )  {return " const";}
    inline std::string const_rule_impl(false_type)  {return "";}
    template<typename T>
    std::string const_rule() {using t = is_const<typename remove_reference<T>::type>; return const_rule_impl(t());}

    inline std::string volatile_rule_impl(true_type )  {return " volatile";}
    inline std::string volatile_rule_impl(false_type)  {return "";}
    template<typename T>
    std::string volatile_rule() {using t = is_volatile<typename remove_reference<T>::type>; return volatile_rule_impl(t());}

    inline std::string reference_rule_impl(false_type, false_type) {return "";}
    inline std::string reference_rule_impl(true_type,  false_type) {return "&" ;}
    inline std::string reference_rule_impl(false_type, true_type ) {return "&&";}

    template<typename T>
    std::string reference_rule() {using t_l = is_lvalue_reference<T>; using t_r = is_rvalue_reference<T>; return reference_rule_impl(t_l(), t_r());}

    //it takes a string, because it may be overloaded.
    template<typename Return, typename Arg>
    std::string arg_list(const mangled_storage_impl & ms, Return (*)(Arg))
    {
        using namespace std;
        return type_name<Arg>(ms);
    }

    template<typename Return, typename First, typename Second, typename ...Args>
    std::string arg_list(const mangled_storage_impl & ms, Return (*)(First, Second, Args...))
    {
        using next_type = Return (*)(Second, Args...);
        return type_name<First>(ms) + ", " + arg_list(ms, next_type());
    }

    template<typename Return>
    std::string arg_list(const mangled_storage_impl &, Return (*)())
    {
        return "";
    }

    //! implement
    template <typename T>
    inline std::string parse_type_helper(const mangled_storage_impl & ms, dummy<T>*) {
        return  ms.get_name<T>();
    }

    template <typename... T, template <typename...> class Tn>
    inline std::string parse_type_helper(const mangled_storage_impl & ms, dummy<Tn<T...>>*) {
        using type = dummy<Tn<T...>>*;
        return parse_type(ms, type());
    }

    template <typename R, typename... Args>
    inline std::string parse_type(const mangled_storage_impl & ms, dummy<R(*)(Args...)>*) {
        using args_type = dummy<Args...>*;
        using return_type = dummy<R>*;
        return parse_type(ms, return_type()) + " (*)(" + parse_type(ms, args_type()) + ")";
    }

    template <typename R, typename... Args>
    inline std::string parse_type(const mangled_storage_impl & ms, dummy<R(Args...)>*) {
        using args_type = dummy<Args...>*;
        using return_type = dummy<R>*;
        return parse_type(ms, return_type()) + " (" + parse_type(ms, args_type()) + ")";
    }

    template <typename T>
    inline std::string parse_type(const mangled_storage_impl & ms, dummy<T>*) {
        using type = dummy<typename pure_type<T>::type>*;
        auto str = parse_type_helper(ms, type());
        return str + pure_type<T>::type_rule();
    }

    template <typename T1, typename T2, typename... T3>
    inline std::string parse_type(const mangled_storage_impl & ms, dummy<T1, T2, T3...>*) {
        using first_type = dummy<T1>*;
        using next_type = dummy<T2, T3...>*;
        return parse_type(ms, first_type()) + ", " + parse_type(ms, next_type());
    }

    template <typename... T, template <typename...> class Tn>
    inline std::string parse_type(const mangled_storage_impl & ms, dummy<Tn<T...>>*) {
        using next_type = dummy<T...>*;
        std::string str = ms.get_name<Tn<T...>>();
        auto frist = str.find_first_of("<");
        std::string template_name = str.substr(0, frist);
        std::string args_name = parse_type(ms, next_type());
        char last_ch = args_name[args_name.size() - 1];
        return template_name + "<" + args_name + (last_ch == '>' ? " >" : ">");
    }

    inline std::string parse_type(const mangled_storage_impl &, dummy<>*) {
        return "";
    }

    template<typename T>
    inline  std::string
    type_name(const mangled_storage_impl &ms)
    {
        using namespace parser;
        using type = dummy<T>*;
        return  parse_type(ms, type());
    }
}



template<typename T> std::string mangled_storage_impl::get_variable(const std::string &name) const
{
    auto found = std::find_if(storage_.begin(), storage_.end(),
            [&](const entry& e) {return e.demangled == name;});

    if (found != storage_.end())
        return found->mangled;
    else
        return "";
}

template<typename Func> std::string mangled_storage_impl::get_function(const std::string &name) const
{
    using func_type = Func*;

    auto matcher = name + '(' + parser::arg_list(*this, func_type()) + ')';

    auto found = std::find_if(storage_.begin(), storage_.end(), [&](const entry& e) {return e.demangled == matcher;});
    if (found != storage_.end())
        return found->mangled;
    else
        return "";

}

template<typename Class, typename Func>
std::string mangled_storage_impl::get_mem_fn(const std::string &name) const
{
    using namespace parser;

    using func_type = Func*;

    std::string cname = get_name<Class>();

    const auto matcher = cname + "::" + name +
             '(' + parser::arg_list(*this, func_type()) + ')'
             + const_rule<Class>() + volatile_rule<Class>();

    // Linux export table contains int MyClass::Func<float>(), but expected in import_mangled MyClass::Func<float>() without returned type.
    auto found = std::find_if(storage_.begin(), storage_.end(), [&matcher](const entry& e) {
        if (e.demangled == matcher) {
          return true;
        }

        const auto pos = e.demangled.rfind(matcher);
        if (pos == std::string::npos) {
          // Not found.
          return false;
        }

        if (pos + matcher.size() != e.demangled.size()) {
          // There are some characters after the `matcher` string.
          return false;
        }

        // Double checking that we matched a full function name
        return e.demangled[pos - 1] == ' '; // `if (e.demangled == matcher)` makes sure that `pos > 0`
    });

    if (found != storage_.end())
        return found->mangled;
    else
        return "";

}


template<typename Signature>
auto mangled_storage_impl::get_constructor() const -> ctor_sym
{
    using namespace parser;

    using func_type = Signature*;

    std::string ctor_name; // = class_name + "::" + name;
    std::string unscoped_cname; //the unscoped class-name
    {
        auto class_name = get_return_type(dummy<Signature>());
        auto pos = class_name.rfind("::");
        if (pos == std::string::npos)
        {
            ctor_name = class_name+ "::" +class_name ;
            unscoped_cname = class_name;
        }
        else
        {
            unscoped_cname = class_name.substr(pos+2) ;
            ctor_name = class_name+ "::" + unscoped_cname;
        }
    }

    auto matcher =
                ctor_name + '(' + parser::arg_list(*this, func_type()) + ')';


    std::vector<entry> findings;
    std::copy_if(storage_.begin(), storage_.end(),
            std::back_inserter(findings), [&](const entry& e) {return e.demangled == matcher;});

    ctor_sym ct;

    for (auto & e : findings)
    {

        if (e.mangled.find(unscoped_cname +"C1E") != std::string::npos)
            ct.C1 = e.mangled;
        else if (e.mangled.find(unscoped_cname +"C2E") != std::string::npos)
            ct.C2 = e.mangled;
        else if (e.mangled.find(unscoped_cname +"C3E") != std::string::npos)
            ct.C3 = e.mangled;
    }
    return ct;
}

template<typename Class>
auto mangled_storage_impl::get_destructor() const -> dtor_sym
{
    std::string dtor_name; // = class_name + "::" + name;
    std::string unscoped_cname; //the unscoped class-name
    {
        auto class_name = get_name<Class>();
        auto pos = class_name.rfind("::");
        if (pos == std::string::npos)
        {
            dtor_name = class_name+ "::~" + class_name  + "()";
            unscoped_cname = class_name;
        }
        else
        {
            unscoped_cname = class_name.substr(pos+2) ;
            dtor_name = class_name+ "::~" + unscoped_cname + "()";
        }
    }

    auto d0 = unscoped_cname + "D0Ev";
    auto d1 = unscoped_cname + "D1Ev";
    auto d2 = unscoped_cname + "D2Ev";

    dtor_sym dt;
    //this is so simple, i don#t need a predicate
    for (auto & s : storage_)
    {
        //alright, name fits
        if (s.demangled == dtor_name)
        {
            if (s.mangled.find(d0) != std::string::npos)
                dt.D0 = s.mangled;
            else if (s.mangled.find(d1) != std::string::npos)
                dt.D1 = s.mangled;
            else if (s.mangled.find(d2) != std::string::npos)
                dt.D2 = s.mangled;

        }
    }
    return dt;

}

template<typename T>
std::string mangled_storage_impl::get_type_info() const
{
    std::string id = "typeinfo for " + get_name<T>();


    auto predicate = [&](const mangled_storage_base::entry & e)
                {
                    return e.demangled == id;
                };

    auto found = std::find_if(storage_.begin(), storage_.end(), predicate);


    if (found != storage_.end())
        return found->mangled;
    else
        return "";
}

template<typename T>
std::vector<std::string> mangled_storage_impl::get_related()  const
{
    std::vector<std::string> ret;
    auto name = get_name<T>();

    for (auto & c : storage_)
    {
        if (c.demangled.find(name) != std::string::npos)
            ret.push_back(c.demangled);
    }

    return ret;
}

}}}


#endif /* BOOST_DLL_DETAIL_DEMANGLING_ITANIUM_HPP_ */

/* itanium.hpp
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
*/