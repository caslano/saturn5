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