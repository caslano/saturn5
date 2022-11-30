//  Copyright 2016 Klemens Morgenstern
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_DLL_DETAIL_DEMANGLING_MSVC_HPP_
#define BOOST_DLL_DETAIL_DEMANGLING_MSVC_HPP_

#include <boost/dll/detail/demangling/mangled_storage_base.hpp>
#include <iterator>
#include <algorithm>
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/is_volatile.hpp>
#include <boost/type_traits/is_lvalue_reference.hpp>
#include <boost/type_traits/is_rvalue_reference.hpp>
#include <boost/type_traits/function_traits.hpp>
#include <boost/type_traits/remove_reference.hpp>

#include <boost/spirit/home/x3.hpp>

namespace boost { namespace dll { namespace detail {

class mangled_storage_impl  : public mangled_storage_base
{
    template<typename T>
    struct dummy {};

    template<typename Return, typename ...Args>
    std::vector<std::string> get_func_params(dummy<Return(Args...)>) const
    {
        return {get_name<Args>()...};
    }
    template<typename Return, typename ...Args>
    std::string get_return_type(dummy<Return(Args...)>) const
    {
        return get_name<Return>();
    }
    //function to remove preceding 'class ' or 'struct ' if the are given in this format.

    inline static void trim_typename(std::string & val);
public:
    using ctor_sym = std::string;
    using dtor_sym = std::string;

    using mangled_storage_base::mangled_storage_base;

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

    template<typename T> //overload, does not need to virtual.
    std::string get_name() const
    {
        auto nm = mangled_storage_base::get_name<T>();
        trim_typename(nm);
        return nm;
    }

    template<typename T>
    std::string get_vtable() const;

    template<typename T>
    std::vector<std::string> get_related() const;

};

void mangled_storage_impl::trim_typename(std::string & val)
{
    //remove preceding class or struct, because you might want to use a struct as class, et vice versa
    if (val.size() >= 6)
    {
        using namespace std;
        static constexpr char class_ [7] = "class ";
        static constexpr char struct_[8] = "struct ";

        if (equal(begin(class_), end(class_)-1, val.begin())) //aklright, starts with 'class '
            val.erase(0, 6);
        else if (val.size() >= 7)
            if (equal(begin(struct_), end(struct_)-1, val.begin()))
                val.erase(0, 7);
    }
}


namespace parser
{
    namespace x3 = spirit::x3;

    inline auto ptr_rule_impl(std::integral_constant<std::size_t, 32>)
    {
        return -((-x3::space) >> "__ptr32");
    }
    inline auto ptr_rule_impl(std::integral_constant<std::size_t, 64>)
    {
        return -((-x3::space) >> "__ptr64");
    }

    inline auto ptr_rule() {
        return ptr_rule_impl(std::integral_constant<std::size_t, sizeof(std::size_t)*8>());
    }

    auto const visibility = ("public:" | x3::lit("protected:") | "private:");
    auto const virtual_ = x3::space >> "virtual";
    auto const static_     = x3::space >> x3::lit("static") ;

    inline auto const_rule_impl(true_type )  {return x3::space >> "const";};
    inline auto const_rule_impl(false_type)  {return x3::eps;};
    template<typename T>
    auto const_rule() {using t = is_const<typename remove_reference<T>::type>; return const_rule_impl(t());}

    inline auto volatile_rule_impl(true_type )  {return x3::space >> "volatile";};
    inline auto volatile_rule_impl(false_type)  {return x3::eps;};
    template<typename T>
    auto volatile_rule() {using t = is_volatile<typename remove_reference<T>::type>; return volatile_rule_impl(t());}


    inline auto inv_const_rule_impl(true_type )  {return "const" >>  x3::space ;};
    inline auto inv_const_rule_impl(false_type)  {return x3::eps;};
    template<typename T>
    auto inv_const_rule() {using t = is_const<typename remove_reference<T>::type>; return inv_const_rule_impl(t());}

    inline auto inv_volatile_rule_impl(true_type )  {return "volatile" >> x3::space;};
    inline auto inv_volatile_rule_impl(false_type)  {return x3::eps;};
    template<typename T>
    auto inv_volatile_rule() {using t = is_volatile<typename remove_reference<T>::type>; return inv_volatile_rule_impl(t());}


    inline auto reference_rule_impl(false_type, false_type) {return x3::eps;}
    inline auto reference_rule_impl(true_type,  false_type) {return x3::space >>"&"  ;}
    inline auto reference_rule_impl(false_type, true_type ) {return x3::space >>"&&" ;}


    template<typename T>
    auto reference_rule() {using t_l = is_lvalue_reference<T>; using t_r = is_rvalue_reference<T>; return reference_rule_impl(t_l(), t_r());}

    auto const class_ = ("class" | x3::lit("struct"));

    //it takes a string, because it may be overloaded.
    template<typename T>
    auto type_rule(const std::string & type_name)
    {
        using namespace std;

        return -(class_ >> x3::space)>> x3::string(type_name) >>
                const_rule<T>() >>
                volatile_rule<T>() >>
                reference_rule<T>() >>
                ptr_rule();
    }
    template<>
    inline auto type_rule<void>(const std::string &) { return x3::string("void"); };

    auto const cdecl_   = "__cdecl"     >> x3::space;
    auto const stdcall  = "__stdcall"     >> x3::space;
#if defined(_WIN64)//seems to be necessary by msvc 14-x64
    auto const thiscall = "__cdecl"     >> x3::space;
#else
    auto const thiscall = "__thiscall"     >> x3::space;
#endif

    template<typename Return, typename Arg>
    auto arg_list(const mangled_storage_impl & ms, Return (*)(Arg))
    {
        using namespace std;

        return type_rule<Arg>(ms.get_name<Arg>());
    }

    template<typename Return, typename First, typename Second, typename ...Args>
    auto arg_list(const mangled_storage_impl & ms, Return (*)(First, Second, Args...))
    {

        using next_type = Return (*)(Second, Args...);
        return type_rule<First>(ms.get_name<First>()) >> x3::char_(',') >> arg_list(ms, next_type());
    }

    template<typename Return>
    auto arg_list(const mangled_storage_impl& /*ms*/, Return (*)())
    {
        return x3::string("void");
    }
}


template<typename T> std::string mangled_storage_impl::get_variable(const std::string &name) const
{
    using namespace std;
    using namespace boost;

    namespace x3 = spirit::x3;
    using namespace parser;

    auto type_name = get_name<T>();

    auto matcher =
            -(visibility >> static_ >> x3::space) >> //it may be a static class-member
            parser::type_rule<T>(type_name) >> x3::space >>
            name;

    auto predicate = [&](const mangled_storage_base::entry & e)
        {
            if (e.demangled == name)//maybe not mangled,
                return true;

            auto itr = e.demangled.begin();
            auto end = e.demangled.end();
            auto res = x3::parse(itr, end, matcher);
            return res && (itr == end);
        };

    auto found = std::find_if(storage_.begin(), storage_.end(), predicate);

    if (found != storage_.end())
        return found->mangled;
    else
        return "";
}

template<typename Func> std::string mangled_storage_impl::get_function(const std::string &name) const
{
    namespace x3 = spirit::x3;
    using namespace parser;
    using func_type = Func*;
    using return_type = typename function_traits<Func>::result_type;
    std::string return_type_name = get_name<return_type>();


    auto matcher =
                -(visibility >> static_ >> x3::space) >> //it may be a static class-member, which does however not have the static attribute.
                parser::type_rule<return_type>(return_type_name) >>  x3::space >>
                cdecl_ >> //cdecl declaration for methods. stdcall cannot be
                name >> x3::lit('(') >> parser::arg_list(*this, func_type()) >> x3::lit(')') >>  parser::ptr_rule();


    auto predicate = [&](const mangled_storage_base::entry & e)
            {
                if (e.demangled == name)//maybe not mangled,
                    return true;

                auto itr = e.demangled.begin();
                auto end = e.demangled.end();
                auto res = x3::parse(itr, end, matcher);

                return res && (itr == end);
            };

    auto found = std::find_if(storage_.begin(), storage_.end(), predicate);

    if (found != storage_.end())
        return found->mangled;
    else
        return "";

}

template<typename Class, typename Func>
std::string mangled_storage_impl::get_mem_fn(const std::string &name) const
{
    namespace x3 = spirit::x3;
    using namespace parser;
    using func_type = Func*;
    using return_type = typename function_traits<Func>::result_type;
    auto return_type_name = get_name<return_type>();


    auto cname = get_name<Class>();

    auto matcher =
                visibility >> -virtual_ >> x3::space >>
                parser::type_rule<return_type>(return_type_name) >>  x3::space >>
                thiscall >> //cdecl declaration for methods. stdcall cannot be
                cname >> "::" >> name >>
                x3::lit('(') >> parser::arg_list(*this, func_type()) >> x3::lit(')') >>
                inv_const_rule<Class>() >> inv_volatile_rule<Class>() >> parser::ptr_rule();

    auto predicate = [&](const mangled_storage_base::entry & e)
            {
                auto itr = e.demangled.begin();
                auto end = e.demangled.end();
                auto res = x3::parse(itr, end, matcher);

                return res && (itr == end);
            };

    auto found = std::find_if(storage_.begin(), storage_.end(), predicate);

    if (found != storage_.end())
        return found->mangled;
    else
        return "";
}


template<typename Signature>
auto mangled_storage_impl::get_constructor() const -> ctor_sym
{
    namespace x3 = spirit::x3;
    using namespace parser;

    using func_type = Signature*;


    std::string ctor_name; // = class_name + "::" + name;
    std::string unscoped_cname; //the unscoped class-name
    {
        auto class_name = get_return_type(dummy<Signature>());
        auto pos = class_name.rfind("::");
        if (pos == std::string::npos)
        {
            ctor_name = class_name+ "::" + class_name ;
            unscoped_cname = class_name;
        }
        else
        {
            unscoped_cname = class_name.substr(pos+2) ;
            ctor_name = class_name+ "::" + unscoped_cname;
        }
    }

    auto matcher =
                visibility >> x3::space >>
                thiscall >> //cdecl declaration for methods. stdcall cannot be
                ctor_name >>
                x3::lit('(') >> parser::arg_list(*this, func_type()) >> x3::lit(')') >> parser::ptr_rule();


    auto predicate = [&](const mangled_storage_base::entry & e)
            {
                auto itr = e.demangled.begin();
                auto end = e.demangled.end();
                auto res = x3::parse(itr, end, matcher);

                return res && (itr == end);
            };

    auto f = std::find_if(storage_.begin(), storage_.end(), predicate);

    if (f != storage_.end())
        return f->mangled;
    else
        return "";
}

template<typename Class>
auto mangled_storage_impl::get_destructor() const -> dtor_sym
{
    namespace x3 = spirit::x3;
    using namespace parser;
    std::string dtor_name; // = class_name + "::" + name;
    std::string unscoped_cname; //the unscoped class-name
    {
        auto class_name = get_name<Class>();
        auto pos = class_name.rfind("::");
        if (pos == std::string::npos)
        {
            dtor_name = class_name+ "::~" + class_name  + "(void)";
            unscoped_cname = class_name;
        }
        else
        {
            unscoped_cname = class_name.substr(pos+2) ;
            dtor_name = class_name+ "::~" + unscoped_cname + "(void)";
        }
    }

    auto matcher =
                visibility >> -virtual_ >> x3::space >>
                thiscall >> //cdecl declaration for methods. stdcall cannot be
                dtor_name >> parser::ptr_rule();


    auto predicate = [&](const mangled_storage_base::entry & e)
                {
                    auto itr = e.demangled.begin();
                    auto end = e.demangled.end();
                    auto res = x3::parse(itr, end, matcher);

                    return res && (itr == end);
                };

    auto found = std::find_if(storage_.begin(), storage_.end(), predicate);


    if (found != storage_.end())
        return found->mangled;
    else
        return "";
}

template<typename T>
std::string mangled_storage_impl::get_vtable() const
{
    std::string id = "const " + get_name<T>() + "::`vftable'";

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
std::vector<std::string> mangled_storage_impl::get_related() const
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



#endif /* BOOST_DLL_DETAIL_DEMANGLING_MSVC_HPP_ */

/* msvc.hpp
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
*/