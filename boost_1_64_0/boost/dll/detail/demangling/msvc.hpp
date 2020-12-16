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
W0OQQ7SC0MjR0UB9qbNJCqrerD1AFFcrTU9UMwbQYzRn+7UhBKfNY8QwivYSXc6KJJcOOWCs7HPEksSNQpI89p5e6bf6LYb5hrtIn9rEeh+IxzJEDMya8zoRg3ba2/+9g5ibYKUEM+wgiMF1IBPfUlQXAJKQXwqE/XsHzStU/FD2CkXyJhD/I1a/oowo3/DpRtZXR2ai9dUqCGx4kK2vAh7xhg9eM3R7bld6kYTUoRDyV3xNZyEyvsIjT2XxvT6ALhXnYZ95yRg/bvjPF2pfOpdbBI2FKIFRL8Lo3k6I0Ro7RncZAqOlxLkGG/NysEQulZgrSqy2l4iKErHTYydgzsMo53iRc6095zGQUyIZzBBLI+Q8PCeDMM8vD/qgJcMhvN6L2R8CRVzN57/Ef201dDLy5vx22oHnJzvd5USHuJtPZSw59+BsOeAaHm9iaW1FAOQ9i1bS/VhAjqszUmhcdURKn4+UvoMpvROUr9CL5UA4WarUZ0RH0jeOkIA2HIoI0LcdEFBvO6AbCNBRHmXed7C4i0+qVfatujbk53rw5eBV1tkZvLWTCzHXaDHAW+Fd2ZkpYsmb34EuOU99E2iKwNQzWEF6Butw+iZGiNhGCduwwDbPjm3NzwLbax2VIXOkYKTYej3tP0f7OReMx16GV/CUE1VcPmIDXIMfyQjHI2Gg2WAnRhcTRuva86NkFkYnCYwar6r5VX5O+xwWX27PsHRW1gALUbvebYftKsN2XcTtuuQnQekrLbnBgP4KGyWCXYylkneKkgvtJUeJkrETqRiRuSiEyxTfaAc6K+ufOAGMEMATBMBFdoD/+REB0t2WPVvetLlb6dfm+xBxK78/yWgvt1U7zbN7NbB+EKhRfrnfPIgALAUA64VCv+wftcnyA4QE6l/uplw1aFPEoBUujwM4WIEkaiP8Xm08diC92RUpolVg6e5a5SQ2LZkdd0L6FEtUsI/4KfK1fJKMG4DTxCcNjBwjmslBxC4eyYGphHjMoXic7NG+9E1MI9qNQjSHQVqkIE7dR3fVQoccSPQ8og10CCe9DupXFfKZ+3+HGVcKazGiijeYnK4hmZ+DXU9uzd0TpO5RckpneWUrvMHDdtKHvQvdc6Z6GD88NFxU0pw0u8cLfj+vlwaobKcPwLTj3EvC9OIY2XcPotlxWAbOjktxdvyFZ8cbu2uTtu9O2D5ACF5d7Uiqj+AM/4YvhBjvW5I3I9beijU5ViBXp0JXU6Le6dagFo+7Zkozal42PwKjmljHWHtn/Ovd5PxLdr8q6lvXqqH6fkp3r+/jN+V0bZQ+XAyNPKqUev7jLHFZr5CUg/xeOnI+mMHasno2NBx7rlH7UfJ/0FLUJ61y4iVtaB8QzJAq61g2u8JvtZWiPGrbKo1kloQzRJBEh770jfNaPEtaZNBoLJQTuqjcGOopSauZBkOR0v0Le+I3FxsgUZhhWSu8C/cw3aoUV83CM8K05xlO1gmXZVoSy+kkZIZa84o7lwf8h9+IlWm8F1qJzQbUfOZl8k5JsYQ5hRIyCHQX4BJ1xPbzqI6d6S51LKA6Pk2V+g7eHhbKk9ywL9aawluDPlYIyANfHwUklztfhFgsmkdM7ax0EosKX6t1fR30cPq2hJAFhO4AgW6eHd1X/iPQPQLQtdAqtqNVPtYHTEX1UdlOj6gVprKIUlwoCFzoWHU5lTrx3LdxSamLUAUhtLKVC/3yCKF7UwChIVSQpY6rqVyRKFdmL9eCypVAOYuGXk/0SC3kw5HGoYxoz7yqFUTTDq2EdmU0/DGHZgjtSoBU9uogSGs+NGksNXDojlrhY+Zz+Ct8zIxMMTwS2VsJ2cdbIrJ325Gd/LVAdhtUIR8=
*/