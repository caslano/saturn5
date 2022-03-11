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
DxYGSrcvIFXJo+pI/mpcjiNTgqSmQ9rgmKxcybUhC5jO59xtRo03OZRwAyhrdWt+RHZu/dwILFukTUk/PtesMy+f6aIV8TSYa3aUDxfIjLMJXcxYZMsG2RHcHz9uZVgoRxw8oIAZ83cQB71jsbzrVQRvZW+Qj9MGyUiAS1UOYU0+iz3EOt5XWX3eGjBguBNw1xFsLE/k0iAqYFQ4a3R3cK933UFrTgHC9exNXWzHbqd7jWGv4saZxQqGdeYEhh44JFvxgpnFCHGaZa/hEWIM7pBFi/IYy/l5vFxUgTdxU1vZcvWH97qsMglmPUosiYw3GOrU+zfyrgQSMyFX1ZPr6cktZVrBqtlj6VLxFpf5M9cRxcik3+gmqdmNJR467V17vWEYCxfMz3JqnhM7ziREe2Kp6YBj8FfgSSyxacnEdfHWcjIen/V3yJuOfGEAJF2diMoAH/eSCp+eKYfS6WD78mO9rbFvlF+bfLXYaTcZd8i58guDKCL5IxxzWJ/VmWlZRHXNmQsRlUo6seipnXFt1W+EtSd/BJGuNwX9sUezkknOATlCHEDCHdiITrA7ZSAE3rO6R6xYRP/kyb9N7+T62My4QieCu639qEX1+oA6OmILmXTHAKhRw5bTGGd+QnT1xcc8eIMDVSc0j30pVXXCWLIoVXVSbalVUv5wCtHfkkWiWa375+kwucdHAsC3xMy7kzKHoYBO+veFUxUnOXKzkyM3vzQbTrb/x9q0oAUjc6dFVl5iRVgMZHWwJU7r4mRmigiddoVa8LOEvmqCekylzOljxMz7xOy76SK9n94u7bfHXfMzs5O7IP0gZINvK8+MUBJvcseOQTjv4/P3l98GOKMKmRkoZt4vZs8tp89QnxSm9vzHZ6gm1bOpt8o5/oV/b9g0CFHyiqb8xyMRdutL0ldhRM9R7rAUz2FrwC48zrU8WJCjKbk6K/V34Z+he00hdiyvu9EMuxkunkaeMgfg8ItSq3CczaZKvm3FC0TTP+O+DKK1P1x2f/QFhxDSf76s+sllJK5OX0RjeVdUhbXGTKyPE3+i13+A18fkT28wfcDjEN4jmnG9Addjcr15iVQBYlDzFy4wXm1m78IFov9AyA2NLMBijQVmLtL855KFvOyMYWZriZlZC2dm78IxMx9u+Za9XiqB2jlYTHdHxGjffQx366F/Sn4Zg+lpnifYvtIjnswVj3pKzgQ/WTHQ+g03/CcloW6WtZ7M9e8j8bFJ7C3ZrU7AFjzPXfsxMcM5uQqZGP49VyfkupAn5vowPMcYNvZtDrc2Y0DFo8VR+diDnxsYk6Hh6Lsb8mmRRH9zFn5rV5kC+7NiFOc8VeCoRjU9Odl/fozizTQSsmCZjclsKQkdxGfYdn8PBE9tNEvbH33vgvL7fLhDaUOo+oHaNGypP836Ai7d8gMUZW4wjybRUeYq4x3WEQ7JKzajaPJb6qCIDxrUwQA6oBcLJ+lGbhNNsGjHDVAslz2pwgwhYI9U25A2lGjWG9gIoYHNEm8SBXzAUOgJBS/UC4XeIsU7nAg/mK4pT1mL/JhOZRrFTC1Z0WbAq4igBTGawcLdYrHb31DbQQoVLVxstCheLmaO9bMeWKy54mUL/wfbkeZKHspRg9CuGCOdKKYuAm3cDFCkzl4XWAderrmIOo0lE4BAdUJFIv8MQtKw5m2DfY2hFnS/db4dMMgoCybkZuikqnbxLAZr5gQGZH9lFAOy30P0Lnh8Yd4gmbbQ3qH7p0Pt4ah0PZRHW2t78pCPeQfejVhcPV+9OQuhfPxoUn2LKiurHW7sxtaNg9SNNCI181ABICGZj8rWj4Bl/7/BToOH3n8cI3vn28iPaSM1QRsQ4eCAYdXYntTA0xTIKN1Bgu7ypTYpEhVOgcsw5KalQOKH4MRsM/gFnxwqRNLfDqRahtOzJ8j7RwD03UR4hkBBBFMIgvkqCOb2J0AwoqKQhGU2WwRWhPXB1Lp/n//jlDsVzm19BJa6RHtglyl+sjKn3WH+O4TkvYLXjtCaz3zlNSBdZ66mMwMRliWfSkJzynjAweUjOCijvaQ9UPoeyZhanovWW3vykfacQGlbNYIKO/F+btZb08bTV1yKCIDHBpS2n6KTzxxlySDeD9/1dVabl47nqi04cWZmF5u/+ODikTBXnbBKrS+jQxmPmej51wyli7MX2V4ovVDePL3TiqqY+hXw1YxXjEZMbO1xfYD8/FSn0rTLSS5myP0lxfIfy5mzjAr3OuTC1rWDfE27SHX10PWdXIVm8Wk6CsvPcFghrb59ejHMhqTP9pCam0pI0rddqtoFKfTjaAME0jmi3nziYCQsx9QgGEo6xBQezRPAI5dK+x9HwoGS6pdOtGPAqlT3EBGR3OkeqKQUbVYWnNDi4/j2+58Z6pNlE83t5irg9fhiUbYNtlVaQb+061e48d7puanB4sPM3GSi0EEzmeAs8HZn6IR4hxXDDmR8+4QjvbwgP3O5XP3PbO1YPZSeOivTj+aIC8aeABBuxYnUlFR5rkzrBQ4LfAWQjDG2WnTJr69nxhFrnFnkoZc0zhyV6/A5zswai11NK6DjQuuYGE5ucvYoZ3XD/iG+9GyfvKeQWMAH6Jtjx1t0jpbIJvqHiKVQlhZCaS1TeOeWjW6iZmmuP1h+Ac31yR8g8bVIKa80Q0p/xZpkFZbGTWmxnPXJ5Sy+TJkd283K7AaNfVfVeHpHB3owAj0IeRDh0yGOpdidgjgctr8nlxX3pBJrU7X30YHK55GXttEov823KduH8gSuZUfgnUqnmDNR3cHOxLhjc6r2TgRaf4FVZBbxoSdEfvKRtpysmivzJ8THoiam8fhpWDIQrhKuNt6+02LB4YmWj671oBfp/IXemjOsO5HyCXaMgxTb6En1TL1dTv8quZbbkI3XKIjtdG0YrobU24txdtTizw2w0hCihHYx8XprwOWy4ht+3mxT7zPXqEC4FrzwBYyINwO6i3MtgKaI8Ry0atQcSNWifW2C/Nc/eocsncbJSmvkiCOvZaMR1w1OrDW4T2bFJDRY0RIR7diFVeAWG+XDE1sPkix6ZgbToLemHz3SWIvPBqtp5cJR6w542I39WPJd2K4d2sNyUqthpGrLVebavSI/nS5DV/wGp+8Y9RNRIc8dSGNwoB6mkf6r55Kw0k+8j5OpihaRxvP41pY0F8+KkUh3Iz3H7SpCEcuK5WNPnqW7Yunyu2Vgz1kD+ZpnUPpYzCguXX4LtJzSxC2QFWifZYVs4BTig7Q/vA+PCCwBgWW5uicsf/phDzVbzVNaLB9YA09bjVnzSK5InDUCbHEg4WPnJodqsIgzNZ5sRekYjvf3Zc9MqvZ+zPq9rRazgCigQEtrNdQwShRp4UCiWL9D3tDnHiTXystbs6fy/i+dyuRmtOUQPJ1+g6eK2Mdo+WdptfkWt0lKN7+WB2FGcep9PBBs1CZAULlKmWH0S4JntJGBusM0pfpQUbFWOHnVgHMzjVmrrZ611ZWyj5UwVC8f6XPGxeSf1utdofp0gvbHDfxYuTzna2+ymm3g6+P4OtYn7mlmT8kJZ6hBhE4iPj7UNh7xDxtSoabMIIXI0GAqyn4jUDqBlEltJuYw9AEXxrjJtg5NvNqMGLoqK/607He2euSzrheQGlv+qy8wRfowueHvXUZg6VJtgL9jZuptIMlm+vk7Uu/j10yxXwb6czDp/ECiRo+KGR5xR27qcU/q8dzAsimJQall9O+kRH5qhid1B/3M1a5/7QBJDAEmYe0K0a6YBo38RTFU21XkjtCb6yeBy+C2VGJN6v2pvPqmGFYtsvowMXC7FBnOy3XF1NX3Mc1aEUhrKKI/i3iAiGb2y788DnCCFh0lhJ/px+vTHXgfb9AHUPe9NX9BsgCT5nWBRKF+tXz5b/j4xVpxoHQNUYJeFCitwb8+prQ8R2MIMcUQcRNriGDS3L+wvKoIbt5XSkLrRUV9SS0WOJesp3krYar4qKfkQ4YCFjPGfgTxOsehj1CytS+ZGOXQ+mNf9daw2zG0Pl2Yn5p30vUCGkrnek02Ma/N1UmCXegECRqBeTUmSNcL1byJIG1cJNYfk66eVAWxhObAsJPAx3H/Ma8Fkl3OsYY/tH56omPPrcu0wLDDEOIWCX1DySmRZuYyfa5iB6THTQ9bml1DZugFLjhDzWJ6OFX7oHl2bu/tw+iCuG2ufe1DvoRuB+atIdoMNc8KRHK1PHHHlIxL3DGp2oD03xCOO8PhcKXqSgzVgPS1cuSdtN4fac5JfpZDj78AlqP1D8wbpeWh6nqOv0O1NAMtzVAtGUyvyFGNVkL9aG5lUfSFsBpH12EWVta79pKm4eJpSs2TpK2gtkiNNtzQazj8gYnnWLthtCKuPsCfr40Q7FU2b5D79jsdrWyhDq3RYgBrBIkq335yGc3rhb+R3m5+pmsvHdS7Grm16+5AtXeUIay34Q7q/Q303bz/eF/4ZWBG1se69PVZ3+vqgo49J+4Iw9GyVjUvW253WOQKRnESUTT9Aok13tqfYEzuWBQ8RLJzzg227Oy40pSdJ3M+2Rm9QO76G0m77VGVSXbiCpNfFIJd1Vcqxmw8h6jTzD1RlVC280tuQqhtZlJU5ZW9aN6kD46qvLJa66lhwvf/AQAA//+sfQ94VNWx+G52kyywsAsGjBo1VbRoqMUuKNuFCg13SYXFDYEElARfRV5MbR9P7kUsbEQ3qzmeXEtbVOwDi6/Q0j4sqQSIFXBDIkkkQlCqiWxotLx64kYMGskikfubmXM3CWj73vu+3/dB9t7zd86cmTkzc+acqwfW5xcYWhVvMn7RY7VYmFLJA1VFYuHl5wyeO54psd9bLFaL+oh3v2oYhvp9byhTzRDvf3DO8Naus1gsavpjc8ZbLOss4k1I4+4ya7jbzft1Lbpt2zbZ8jbjF5VQkisxljveY3hDldoy8WsobezageluQ8uE8lRvaKWtkBmf6g1la1OgjjoJu84x4bhelMjuUv5Rdx6jqMyqK+uDxtgHd492hwMV2LMrcg67zM3+VnYPAD8pLNzqdWExSc34VhQyXJH34G+jUmHHvq+Ah1R8cMNDGj6kw4MNHnRtvR7qhC63iXfeBzh6xFH8SfA0fsRY35oCXfTwdH5UPvedLOxrC+pKpwmL56xXy9au8u6moVxWZkUEKNEggn9Y/MdPoH2lLeiJenc/CAWY1uZ6Jsq0mGxBq4BiYsmq84ZXy1RvwZZuMlv6hvjB+/8cKXz3aiioh6oJ9KuoNE49QhkOZVp4oEmf5UhhSrWr4mdQXiQ6k0U2wmskqt3blzseKQIaNzGgjfAqlVpaOFRhqOlcqc5jSiePYD98hgNehNgFjYRD2TDT2i26fi/k5JsAdg4FcD1iOAsLquPEo9RxAfa8AdJZBKvx3IkwYUFxdkTCCEfdi4FaDyn9VvHnvIQR1PVSKCJ+ak8YZZayYfqciZCXIkqfxYmJGKsLi3QFcBioFH23nzPwAfJt4kpnwuCBWLiuh4qvgdfZsuSciaLBfy7ZMOTaxccjLio8D+uGqoyHHcbYmmogMqXaFl6TAdDifLgibwPkpe6iMW5dn4WwfS89ge2kcqUyvLrXUu7TI5gOE1sZxC7FbwEyrtWG9bWQbM3RqsMNzqAeWYSF+FHx5NZzUD9s9U561A6/lrMRKqeOQZi24fMFAE3sBSjXhcIWGKL6HeiLz+jNg/YrguLL2wZGniayaTAVcjCp4jF47fohYpmAMlb0BsVProciBHtyyPcg6qdvWTLObdFuC0+vKcGHbxlTelaPcx+YVD/GXYgYrs49Z5TdiE/PvvGFUSiz8fU5yADyJ8JW5wEFaz8QG06CMFmhqneA5DGmZN0zzs2tRnCSrlUThZVZtyEjdwa3GWMb9ox244CCvVCW31o2HkoUzQ8ahaU4DbuJRpDtgpN4oJLP7OWXQxGtujCYD4nzS3kEZxJR76p4nkRSbU5kPHEEUmJY2ML7ETLLNiBbNYgcod0pejuAfFerlq8C2KmHWgcAbB0A8BnshX/fhPFGKFQUnI8wakkYUUwAjAQOz+vl47BUZ1F+ENIBzAvhNdmGOi78KrKERRsZfnU7PrgqrgIRzdNLlwD6cZQTPM2RqOuZOhDTvA6YM1U8PgEmjJicz3lQD20hPt+eds4AMT7DUtt7eIxbS63tgR8gayQY8Qfgl/CrNdg+THC6esWBbsgtFJ/8MN2yOFhollKBcrmNHzbWd5McUO8xewlU6a+2QdK2bToR47YkuW4T7S8CMfNOyMxx6LuwEBslfhcDuU/TT3KfNw0V+yAEcKCcWkK8gGQg1GxJosbQYhJ5EzgBliTLBgfAdyG8fwXOnjrS2L1igBQmGCQdk3Sh58FLpFl16pGJCKdYfhn0qM+9JDVIqaWyC3E/Nh+oxMe74TEc6Dd0fSpkNkbwb8/fR7vFVRsShnAvS7cczLJwYyHvDncveLH7hnFuz+tM6eeKo4ApbVxxFnLNzduL+PQmoBWmHNfDTTDmINN2GO/qYURT0HgXlslXUe6pVxcZ2njAu5YF2Co0tOOG1iasnxhG1yZYiMSiE4DjGQ8ypdX7arVcju8Dgr4Aa12WNoJmLLgCpsvmic7g2vGiIDTRBovMbaW4yDQFheXfYCGZvg/YWAXOarJFmdLElRb8bdFDMaQf4NeVeepY0f0eimQ9UJuPUnkakGJ8GNNqmbZPV2q5g8+wswBUa/Ad0ey+Q+p1z+ccPJYIv2HktPK6+fKl2chpykdJJxdCgEgPdWMfuhbTX20iOgKCffy9oQsTD2T0tV/V3Hfs+qa+9nzzjZ51pTu5pAK+kFnUe7yhDHUW16I4mEM3Kb1c6Z2hc2yaWX19Wqo31KDexpUGAMjz1rHE93Na5/NDQ17yJRPHx4SbjBylxaokuJJg4RZSG0AhavCGWtVhhOV+Iz7Z++ommiZQKXyNwLIJQx3tJXbVZKEvjbjL+2rVoKqUYsEZXTnL0LIBfphYnN3MxtxZgFDIyjC0HUGc5D8/BCCvnCXH5aqwQjatvTZYHgEGbXSZFcSOJB4JM875aCqTYtEcZqdrJWQaQrbChKxU34XVpB7giW7zKhnqCB6oDtelsEBtfBgP1NDjPph6JUsbluzX5jnr94ZxwNr1oqMNOFnL4O5CczGvllzcRot5FalgqLJdI6nwXqDCLGgPpudKE4wxnua4hNduUU9B2/H3Pc0zkSw9UV8fKD1Bc3j5iI8HfnzegHkDHRJadUU2Q8bvESrtG3Kk2hUwfldFRKaPtWjl4rsAYllK/B5E113mTM2W+JiB+PCZgHgMpVeMbLtId+oeOhrUnUT3u9CaVaIuPlx00CuQMHcPkWGD5Xmgf2mJ5817xPT56Zbmg9lSKOQX6ooD5tfBz+jzssVN/jSUpkoBL3YU8ZAzYqhTwt+0cL+7r+0qYCaHeqOugAqg9Aexnj7PLtIBD95ip+oIhxwW7f04aBP9LH0pr7+npPmgw1LmrP11HoijX5WkW/gZHnCIyiv7De6fKBvsVmcLfgeqS4EeMe98nxG+vx8kgYDme4LITwjVrf9uBfAdmCReugpqB3pQ5KH4u8cG4i/UbdFeEe6lIOvsltq8ljHuem4U8jPiajAJGtMehAR+qKS+0YpPXUsfs1jK7LW8x+0WdoCqdCswtfhwXMJYzJtYoMcDYPX7mtRUsReXmlegSD3hClqUjYksaOKs4rCq6YWigyoeKinGvquOUt8kbTMGpS3qet38jMcIGquyWaibhXpYqJeFEsbY/r0gd56eigup0pvz9CR4yFG6fXXq2DJrEZQ2xvZACXroxaIwi543S8TqIE6i3ZxERBpMZD8/Ax3YReUrDpxFG/M7YDJKmuu/tlTp15caUmLu/6qdiV9bCgS7k58BwsIiLlkkFYrEUzxRwJXjEsiDuPhC8YzGNNU2BpZi+OeE2qKz1mGRLTO/HdDcfDDDkpwN0fI28rxZ1Fg1wRjbCWovPyI6IQN6cVr4yNJHxrlhJR3JQTwZ7vAN+G5OaIfiaD/9XtdfO882zFqTDW/5sZEbYQbzO4od8NaRNV4cfiHdEtMcixcX17eLYrNa6hYoFCt2YMXUn2Z0pEbPj06+WzU7Fmw/bRZuPw0ttR2TRVPaO9uFfJmppXW8d7KrAAMs/NO4vqOto+1/LJvR8V57tK0udoPjw9HutuaTzSfr/mlNCVKythtKtrdHTzbHvrUdIIeaqVNvGuNue0tmj+o40d588oP2Omi2WTb7z0Bql7WuxCbbms2emk++cbIrlho1m6+F32TvY3CcWBT6n1ItCwx2kJ/ffjq20CGLItYBeMB+Kg50IH18R3t+LOTIxxn5/gXD6ChOmPMzGd5igcTixc3QqEl6Z1MFzLG1I1WkjnNro8Mj6bU92jG2Ex7iaR2p+PuVkQGEMLr3ZI/+jvc6UhHY2OH2htjILa+Ndnek9sA7oPGD9ua2/25vONly8nD76zCoGwSkn2xoPww4qGt/IxYFTL5/8uDJcwOYMBv9IcxifWyk+6PR7vZ6s/nm9jdOvt9e33b4ZHP7621vtL8eG9mJzdVB8/XYdRt2Cr+tmNp18o127ORwbGQTpr8RG5n5MqQfxNSTZ6DDGADe3tGO2C0AFvGc8JY41FuLYO0rsa+6gvsduj3hzVw1zFhhF9eNAdE121duf+hDY5VDXIavrMTBSuxLS+6pBzloZTOdbKabzcxgMzPZzCw2M5vNnMBm2tlMhynmHsm2lKfyme54Op85IWemO8+1c6aT52fYFEfkLXWYa88Pxrt2vmGrK04KK6rh5DMzeb5bn+U2YHnHiplQ959UfbEapqyQT1kA/A2SZHjQeCd8A6ZZXtyBDJ5MwhdLSVdqP2jY2FtBYRGsOv4FpT+0GJZwNCXI/UH88ZwoKDCmYAPG2A1oKpc7skHneAKdPLAUa6kvZoBdFTSm7KAiy/4EYsUf5NOn4UOTa2fAUZptabEU5JslVi0IDjT4Li6Hi6VldmkDsuoTltP/sKpbvYYGy+ctKD1kqbQUFARn5vN58AcVLNDFYW5IsslVJhMmmT9RKb0haeHldkv8Kj0g8ssyQQu790+ErS6udD/fVx4ECZoUz6D/e5p99jcdrWPcqmNm+Jx97Zn4feGQ06LOLSjUJ7/phIwi47ZXLWheHhb6zSBpb6sTDteeKD8MioBYQymuPYm6Dx0=
*/