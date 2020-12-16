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
    template<typename T>
    std::string type_rule(const std::string & type_name)
    {
        using namespace std;

        return  type_name +
                const_rule<T>() +
                volatile_rule<T>() +
                reference_rule<T>();
    }


    template<typename Return, typename Arg>
    std::string arg_list(const mangled_storage_impl & ms, Return (*)(Arg))
    {
        using namespace std;
        auto str = ms.get_name<Arg>();
        return type_rule<Arg>(str);
    }

    template<typename Return, typename First, typename Second, typename ...Args>
    std::string arg_list(const mangled_storage_impl & ms, Return (*)(First, Second, Args...))
    {
        auto st = ms.get_name<First>();

        using next_type = Return (*)(Second, Args...);
        return type_rule<First>(st) + ", " + arg_list(ms, next_type());
    }

    template<typename Return>
    std::string arg_list(const mangled_storage_impl &, Return (*)())
    {
        return "";
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
NAP/pEQH4J/UaCg2lcbOmiHiUQtrMGWB1hnH0hLidbE8im4B0aJp5cYSD6X0AVARY14nymAeIcpFVLkWgzbuoWFLYvlofJ5TPrqC5aOQTT56qZNNPjr6CJq+ycmgQ4Y3QSY605KJJlClD43SZaIRnWwy0YMjCaOk5NBVw35NOage+efIvSb/xOvKP59Y8s9wm/wTssk/He3yzwiiW5NkoFWddRno7Pb7Tgb6ah/KQPW8f36Etp+tal7vfbE798J9sdOoprVH6ffFHhtGPbgnd8Y8g2Gnu2CPd7oN8ZtdI5z85kbmN4cM1fnNae1s/ObVodTGZPdky/+k78l2NGUPfJLFf6YSmPKAzn+eaGvjPwMkhknuy747Vt+X5bb5NfkR+ocPOPy/H05hTh/iOM+QYU535K/R0zX5b7joX3TcNKykRZU4ZB4XG4vhUggHMTw8NnQBhPHECaJyMCon1huFtVn02tPFATSvngGBDeeyefW63mhendwKqK3gxcMEQvmoBANJZUMKX2I9tVUsDnhkzSc8hiEe2bEeuKoHIVyK4faxthjOgfBKDHtjKcngkFg+3jVUk49nH6oLxF8OqeO//tCWyQnBifdPM636cs2rhrDTsRA52gxjLd9TLe4bKN7vOfr/rxRO3N6JJ1GLPw9YHJJs0CzGVXKIVMsJTTGYLI9sgRGYnubzkob73rYyivR3FVVTMaHiQUxfPxm9PN5pS96YIHnr/Kw0coTCFD39tIaHUtL0hvYKDhc/XMn6nw2Xsj6vw/sdpppPGAuUiMXDMMuJR7uwXbNa9oQziZl82vbACHpuZhS0gcqU2NbFHEk9pAIQFcPX8gO4G/poZ1G4nPgXvsFXUIbSQhztZCtGu4YLzvIbGmBeZ0otY/Ox0Gy3fphq74ccfY3HnOidzat7Z+sASDZQ1ztDZJZ8BEbHafj2i2zmQT5YynroGahpep40yFOTBkSsP9u7sKITmf0LH4M4B3UJMcx4em8H1tvpNG3gkKTIgsWYCnx22DIB0HdgGDmJ6Sja96davH6CRvaHx7J0tGX/M+ar4CTHdYawd9HvQNjAZanJ0+V399P3ezx9yUAlOFhN3/4BPgCar9sxjB0gtRpk7cGPDHb0L7xQPgDYCR6ZvhDmrHJKSvcRB0734zHPRpQw5o2nDmQ2t6U1yo4LMZXGPEwMSFOubbZhzT/gGaBebDsBfhEPhrpRaVsJSn5kmt/gE5OW2NXxjZY6Y3dwVkf8Am9A3mDZF0NwnIKjmGDsDQeG2a212lXb6FkeSD0NcEu6krPrVDJVVvJ0OlcytW4l34P2YkOQG3ZSM/XqVRv5Xvo25UZU0rm10m98AYFyok+ZmRJeLoRH6YRH2tXFnw1PeVZcemA/PNnc6YHDhWYjAr2bnaGsI1YgUMhFR+zZ+FltKnBlNSkKHniWlnXHt3HVE7LxaWksQ929ZAHOPp7WOa5LmXOEbKQRImox/4lHfBm6jxnaaeEcHoT7TrK7+R+Yxvg+6c7OybzHMDNXl38OYbclAfMjsNVI1v9/Pf4vchOf33kPs/m/aGb3f3FIsud35g+1jd+7aOd3J1CFswfrexejmW3vUtIPuQ8sJuTpHVGSz23x2/2MT8EPtb/iVqUB/clth+41/ckvdfUnMdaf3Hawrj8ZNkjXnzzjtelPhvZF2pG+w+XxQoiKaIS0q0+e7aOrT/qm7jv1ydf7UH1Sj/5kRz9td1D6be0+8rdz1gBdfzLnoD3zt3NM+j7zt3Nb38Tn2Z/20fnNASk2fnNNTvLn2cNb6LqT64wm6E608+wpBOa4Pjr/me+x8Z9v+kj+AxMHsjTAgVb4dNXJN/FfnR+hfeZBDvtLGeY=
*/