// Boost.Assign library
//
//  Copyright Thorsten Ottosen 2003-2005. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/assign/
//

#ifndef BOOST_ASSIGN_PTR_LIST_INSERTER_HPP
#define BOOST_ASSIGN_PTR_LIST_INSERTER_HPP

#if defined(_MSC_VER)
# pragma once
#endif

#include <boost/assign/list_inserter.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/remove_pointer.hpp>
#include <boost/move/utility.hpp>

#if defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES) || defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/iteration/local.hpp>

#endif

namespace boost
{

namespace assign
{
    template< class Function, class Obj > 
    class ptr_list_inserter
    {
        typedef BOOST_DEDUCED_TYPENAME
                remove_pointer< BOOST_DEDUCED_TYPENAME 
                       remove_reference<Obj>::type >::type
           obj_type;
    public:
        
        ptr_list_inserter( Function fun ) : insert_( fun )
        {}
        
        template< class Function2, class Obj2 >
        ptr_list_inserter( const ptr_list_inserter<Function2,Obj2>& r ) 
        : insert_( r.fun_private() ) 
        {}

        ptr_list_inserter( const ptr_list_inserter& r ) : insert_( r.insert_ )
        {}


#if defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES) || defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        ptr_list_inserter& operator()()
        {
            insert_( new obj_type() );
            return *this;
        }
        
        template< class T >
        ptr_list_inserter& operator()( const T& t )
        {
            insert_( new obj_type(t) );
            return *this;
        }

#ifndef BOOST_ASSIGN_MAX_PARAMS // use user's value
#define BOOST_ASSIGN_MAX_PARAMS 5        
#endif
#define BOOST_ASSIGN_MAX_PARAMETERS (BOOST_ASSIGN_MAX_PARAMS - 1)
#define BOOST_ASSIGN_PARAMS1(n) BOOST_PP_ENUM_PARAMS(n, class T)
#define BOOST_ASSIGN_PARAMS2(n) BOOST_PP_ENUM_BINARY_PARAMS(n, T, const& t)
#define BOOST_ASSIGN_PARAMS3(n) BOOST_PP_ENUM_PARAMS(n, t)
        
#define BOOST_PP_LOCAL_LIMITS (1, BOOST_ASSIGN_MAX_PARAMETERS)
#define BOOST_PP_LOCAL_MACRO(n) \
    template< class T, BOOST_ASSIGN_PARAMS1(n) > \
    ptr_list_inserter& operator()( const T& t, BOOST_ASSIGN_PARAMS2(n) ) \
    { \
        insert_( new obj_type(t, BOOST_ASSIGN_PARAMS3(n) )); \
        return *this; \
    } \
    /**/
        
#include BOOST_PP_LOCAL_ITERATE()

#else

        template< class... Ts >
        ptr_list_inserter& operator()(Ts&&... ts)
        {
            insert_(new obj_type(boost::forward<Ts>(ts)...));
            return *this;
        }

#endif

    private:
        
        ptr_list_inserter& operator=( const ptr_list_inserter& );
        Function insert_;
    };
    
    template< class Obj, class Function >
    inline ptr_list_inserter< Function, Obj >
    make_ptr_list_inserter( Function fun )
    {
        return ptr_list_inserter< Function, Obj >( fun );
    }
    
    template< class C >
    inline ptr_list_inserter< assign_detail::call_push_back<C>, 
                              BOOST_DEDUCED_TYPENAME C::reference >
    ptr_push_back( C& c )
    {
        return make_ptr_list_inserter<BOOST_DEDUCED_TYPENAME C::reference>
                   ( assign_detail::call_push_back<C>( c ) ); 
    }

#ifndef BOOST_NO_FUNCTION_TEMPLATE_ORDERING

    template< class T, class C >
    inline ptr_list_inserter< assign_detail::call_push_back<C>, T >
    ptr_push_back( C& c )
    {
        return make_ptr_list_inserter<T>( 
                    assign_detail::call_push_back<C>( c ) );
    }

#endif
    
    template< class C >
    inline ptr_list_inserter< assign_detail::call_push_front<C>,
                              BOOST_DEDUCED_TYPENAME C::reference >
    ptr_push_front( C& c )
    {
        return make_ptr_list_inserter<BOOST_DEDUCED_TYPENAME C::reference>
                 ( assign_detail::call_push_front<C>( c ) );
    }

#ifndef BOOST_NO_FUNCTION_TEMPLATE_ORDERING

    template< class T, class C >
    inline ptr_list_inserter< assign_detail::call_push_front<C>, T >
    ptr_push_front( C& c )
    {
        return make_ptr_list_inserter<T>( 
                    assign_detail::call_push_front<C>( c ) );
    }

#endif
    
    template< class C >
    inline ptr_list_inserter< assign_detail::call_insert<C>, 
                          BOOST_DEDUCED_TYPENAME C::reference>
    ptr_insert( C& c )
    {
        return make_ptr_list_inserter<BOOST_DEDUCED_TYPENAME C::reference>
                    ( assign_detail::call_insert<C>( c ) );
    }

#ifndef BOOST_NO_FUNCTION_TEMPLATE_ORDERING

    template< class T, class C >
    inline ptr_list_inserter< assign_detail::call_insert<C>, T >
    ptr_insert( C& c )
    {
        return make_ptr_list_inserter<T>( assign_detail::call_insert<C>( c ) );
    }

#endif
    
    
} // namespace 'assign'
} // namespace 'boost'

#if defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES) || defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

#undef BOOST_ASSIGN_PARAMS1
#undef BOOST_ASSIGN_PARAMS2
#undef BOOST_ASSIGN_PARAMS3
#undef BOOST_ASSIGN_MAX_PARAMETERS

#endif

#endif

/* ptr_list_inserter.hpp
PwOkrHOgb3KwI91/rZJjX4BPFvkxzDc9BGl8LVAZL55+rpYm7dW2/16baAH7sYw5mHn+bgW1xNmMREpmoSmWjkRi4XNBZmSu+9F9P7G6U21U2nNWR/N/AXS7EnhfPOggiRF1ABzOS1wg+CinA5ZN4J1X5q3W097rd9tH5sMSZ0vQOsfh8yoZ4Ws4Z2PekJLpiVDfh5yCFJHRfC9a46x3Ar4qsfKid+zXdlUPtUeTh72IpRGCfIg8s3Qlp2i39gTDo+DW7F4HZ27RWkDJ3LdjhzL0Yj2MDTryRxL0bEcwh6/QHU28qNkRfK1CiSmZRyLGFYgVMBPB6hGnK3c4943QZwXDg2yUlaHZjCSHjTi11FhtKZi8W8vUfFoIEiGiUZvP/Xulr/O0NnnXz044/RxFo7ponGqVqicCV5asLtlGTzy9DUZGMbTOFJSdQ0sGM7GwgoFSFWleDtJAcXUez2rQJNfAO6ZyVTmxdFCmOUHPJ63xD20w1UY2UbptyBZzbjZf7UTF9g8+lmQjta6QTasy0eiihXjGTI4uaP1Grtc6pu7Vq5DMpOJoWvLNejIrDlhw1p8+Kuw8M7IxDSL30z/7k/haS4KEIyrYE7hyqsIJ+IVkEyVAd00dlNztfw6Z/64ZHgXuFlyFab2EAiNTdkKaTMC/JqF9kjBujM4KZyd0yHh0/nNovqa1WBI9sXguycDz937NqntYg+L6ltmsCPV8Bk6lq6Pe+jGisf0+Q9/Ho4mnoOGTATgmUUr1w8GQ0czU9OP5Q3CLZi+pKKnliOH3ECi3tDgQJLeOdqpH2EOW30M27x6ZDjWsXExK09tQZJUW2rr9eXf12dM08mTi0SMasjOFqaQZpbV9uFOuh1LnaKfM5ITU1OJU2+Lx4ECzm1lb5yJvR8dAb4TC6NTARK+UjPKW8RMeVv593eXzYEVIiGZtLQI7Ad/LBU1WkFhW1BYEbbv9ebZVA11z4evCgDSP1Mv2gObje+kESQDlGxwY6B/oG+zv7+/nFxwkKugbEhAwIsIvLDAw8oe4d6RvgIjQIJeYMI9oaKBgv7DYQN/YwICo8PD4RH/PQNfIwK0CBAQMDAwPDg8aEDAiCCMm9cjn7WEdlC8YbBTAto/vH0DuKIHuKEFNF8DjTvs7PL5pLtbVFq8FoI16rE+Z8HfNujAAFwZELSqdoS8BQccFvsSXjs83es7ed05uzNvVAOQglTLL9A/E+2oYE5XfUzvnD+Ntl5dvLTiOznOPymMPnOek5A+I5+TkD+hr60+0xz7OvuTkfubkZCUSjiUVUiaf4sGuvgHinj46cpLuMRrYfnYgBkJYWtrqWqvfK1kfVKJQmxqxapua8OqaUGsb+4/opoHBB7wtfC0YAGAXqD4+wguBqd9I/0+g3qTlJs4POj8GJWvsN3SgGMdaB0fnUOAOEFTB5U0YVEF5QlxWwwB2cprr9/aoTXKv6wN87oto0Q82X0zG246vtqB+yxYSsqdp86zZ9HFmaaQ9YZJ3YZUsFcjnkqJ7IaIy1/44UR6ME4Ob3kd+456xwM5FtdfP2RjUYJPes13X9/0D6aBCpQ8Rm1Ff6fLMzbz5nzv4uARHReJk9uO3AdPpAt0kLKO2CkHT8Ojh80RiEjBKeXvInObGrIidIM9pMsepvgTvdcoyJyf1hr9NkvLJ/zrUxEk4KVOX7ZWb7DU0p4s1Pbn292Kybis5wp6ubZvJXAoqUDO1Slj8JBeN7b1VlqoS4o1VCaovEjMPUg3QAqA4kUO+EZ2Yyi/42/+oZLeX9ubdkzU9Z4aW/XiWXU1ejuFLiZFVENXjwuseYZq03aqO4HjqNDs+z6zrMOfsvDxiugTPnPuSEDCLRfHvKRBq4C5RLkHH+CTbgfRyeqawHU5V2pbEVduic+WKCwfVdERXdxbWl8VAOhJotFw2JtJN2Psdhp7F0SqvO7BXcXbuQyupq7rSTa0f9bzpXdak2bVsrb1jCeTWZtcbi5M/JflVbe+Eb1SHu5PiKnrlW9z7oU2K70ncTBIcTG3JeRhssHoMD2/x1HwkJEqLneX83QA4Bi4P3a2FwBSKdmiZ6/T6U/TeDyWDQk+jJNzYqjU4FeNHo3MCTumg2NFgVAfLoV/u1ZCSJ4mNO/+9I5gHMtviRwF53NO38SNh+0l0ucqA/IVWuF3fq3onqllvRKL/bcBtPSEyOPnOC1AWGtdwppGDobS0M0FhsQDFqYa1NloGZDe/BmJqZXhyr3xeOfA5YojWAszRVZTFXvAIvutY73hXmKKfyFrPDKo9t2P3asVCT1++XrGm1j2FQGgczUu2pmHl4xz48YOQ31Ol4iPqqHzd84eDroTQ5NBSanDy+eP1E3RbBiC0Rw9kd+CG7qUHdNNnwEgcgAQDoJWVH8z/GLtUH9AO8xB/Dw0FCAlKVeAdrtUBEBQw4LUBBAQFBhMHCBQpKTVNeHX0jvXRawBQFgDBy4Z2hfTThzVA5gCnU6OT/MeN0JiPRBzR60/vnLbzwRemw+uWbLeMpWOTksdy8qvwv3o0nx7OYN9HjPEtdSyjh9fhXgSXbMDrolXq5/pjbpKMy+IcYW0QgBgDqU67U4BuwgEtuBjjwdYfvQum+IlmonkWPTCNiAviKAnqNtp3d1PYAb0xdIOw+sCjigOoDEF2L+JrPQHwrVodb3YwDcfJXBC18dTsLv4Tl/OQVKgpcjht/UpXYOcV5x4VAM87QJmqsMV+udq6xpnLzacD5BNWh7X06iIKJ8o3DTOQ64XXsoWy04TFMiLS6IHCxsBncjm3m6r35QrPG8IUZddAmw1j0BIauwW1l0eYGUXRUC1RH0y5Wp86hDfK5h+fCw9NnJ/+l++fQ2s2vhegD1EXYPB2jNMN9dhLXIBTa91dXQKfd2wAGBzMoDWIqFSlVKEytCd87uv7syt8+kaI8HTLKCyWIMkybEuetVgswZbzEFqiCDOarZbVbYp7HRAWVCqqkr4GbRZzZuhQvVC6UL59XhBTMD7xkYBUwF3kVQrKj9kQaeevv/FY6Q/qrykyHibYWHN05BqMNwwp3M5bkK0mZIQ8kcXDQKo4oQRHfYCGF8+vbywel6QQLz4SkPdVSQQPqcs8JWowP4fahkkDy3mHSX+nSrbWm2afXo9aMRluNVAtHx+fCMSBiXjx5uni0fOqcWirQcLjGSqATFuvuyCS0lOytkFTrOBmmXLgN+7I9yi8O9Ee6/7sjYJy3m7U/+mD+Ny36MHBvdQitKkn3Jd09X0fQjVOJHMF1xnEpE/hlKQ/8AjrJP/QK8WjdmqimehO1tRJOVPc6rnnPf4R/B4ZH370ifnR6wniBFjV+YKHQQH5pN5GBNqCfwUEfrPoFAQjEtEDC+Yo8nnsfPj8hiTMpay4CVCR7jtFMWW0ERK/JVeDEdoMDSLCfkk6GHkshX+R417IP9JZSjjUkTqO4D/grAOpEZ+cPqmDsfW2tt2C5sFf6V+ajZEroXw6XK4k2llnwZMZcy+M4QvjmCtd6d1Nti3R8iyGH5iQ+VfZbF20wO0uesixObD9qCCefxeHpu41RcWBC+CLrmfDJFJd6YGunzGtB3zJvNfTvkH1E3LNwol88jM1B/ZIvQ6wbc36tnEFBhj0KfFm07KBCIoKG2q9WylOLPKDYv33WvGSzGXfK9UK/3Wacza5GoVTUWZI4DiE8SV+t1ppXc4eT/6EF6H8Fkf4HoAx3hwm8oOp0IgcoyjcdqM+rpxkyir4Nqs9Sjey4RGQaIVIRBGWphDjrE31ifKdRCrh2c1iv7kGQInuR+1x+Pg+KMIBl3iMB9uP5an6KuQKy7pHHlsogALX8oj1pe4xBkv82DqCJsVLfzuKuOIgObW8cBonTbaqnG3uhcKR2cU9TmH7L+8TVNjgRMzOs3tj3sLmsERellPL3gFFsI2Cdb01MyXnSl8aCF6IFwvSPp4GeU/tHOsBrD+v6eC/j75QsdjZ5tQTqVATUFWrJJ2+5llfZTMi5XwE04S7JYkhiYQMELenvSVnfMtB0+oappNNTsUCRIZcGyF7YEbbvnMjxdTZpPJw19F7xnDDm+8l7cy0p59YBQaHhu+dg0QMgFifb/eDlqflnneKQ/zPG9F1lycfqhEqh6R3G2V0y5+52XHMttZUJMCXt0mbj88fw1ySrEiunyGaxxuDr5vgdYO5QQRoQl7f8oh0fSb/QgtXw7+tj1+LsQx8mqUq9KiSJEqDRGxlLBVV1BUUdezsFdREw3xs4OkDj9pX6Zrq7bSZAX3323N18DlLZh3J7Z+B7oXz684g7rPXujPx3vkcYFa5lfqe2dnJzQ25hfVNRYnG0c5ckGWfFUnD8n0l/iGzs7Odg3/LNoTAzbD9Tm2PxdhM1/6wEZfVQbiywg2mtgLCdERE9JbUKMdqK/xd/1pHx86VHuB5E0w2vZ0F4HMEIrrzwTV/9unJQExCU7hzdKZv8voYBzMt2X3sW4Rsjfizb3BwrHuge4JwAmKNyLbG1paWCoKRJDVF7WflCiSR5leEhEOFc2njjqoCDo6tsPEDboEbObbp9t8/clVfoLbEE/EkMNDq1Ma/LVl9cnJSkvq/flH//4PfRnKs89L9YrxzOX09afI8oek9HyMqImzkrlQUohb442SC0Y3UUiOddDVIHGgE4/0tyvLo4v2gcn2oe/dQI0Y57DNJ+3lR7ZN1rxLQQ+h/1jMegvEzowZOqpz8Y7zMT+Y8zhAKqEeXsRuud9pPYOnUJ0IwKnvhnu7zjdS407qNL/EXybNiIRQiBjqPlXRputFh5M0Z96B/p0Up/47NRSyRscCVjxACblOEe8rH+blcR7+53ro0+K7Lh+k7WNves2G/JCRfPtSikFa01pKj1lKBsoy6Pamm6xYvz28cYHzgs26ynpJojhmQ1YNNt2ncslljr1iQMfSYLFndUuAGSjH10kY3StHN6E1a2Ci1NAXlvXO+ISA1ZxwTOq4I8sN3bx56RvbJa1ejJC9R9sWbsjH9CLtb6+TPKcNDDltoOUZfn9faOuagMmcet0NI/ipXyvLhLGiFa03ukt511o8J06cGKc2tCtTFYxIBY+0cdGvq14FB3/jwP1rD2wedhfZIyx9JpywI07Q01Z/2YeNoECqfHfS+nuJY07VV1R9nRDp6OrrPrbTpne2aDP37JPufrOEfqc8ssB8bP7I9Q10rPWJdC2Mrgd7bJzuXj5POe5WSR3Gdu1Lx3r67HqA9H1C4rnde8NHx0Tebvb47n0DwB5Vdhu8FXeJdQ32j9xvSMprtvq7YIWv23Ut1z9EqDYlZunnYgawDpc9PyeF7vDgIVSA9ekK9MwQUEn9E4ziTPzIEYu5IYt58qK1QAmoECI6DYOSU8p2SRuFA9gZjJXj4O5zV2jkdt1/q8qzLy8rzjD3fLLEBsSB1+1ABSNJ84ERlO9niMveQ0a2gKitqMEVnaawMKEGDK4QQV9rDOWJ5Z9uVU6dDXkZDgmipc+jqNZU6vCAgOo6DgmqaaMDK1k+vNKPpd1sGCNYCyrJFkgV4tm5GIS0xBCbEMUgJSJy8gKL2EJJJsw+ia7mpDFfInPhTJHUpVMY86GV/hgLmeGulbTgbUVQv/BtV6OsdMe6M70bO2HFBkexdvECw8QMAUgruZkhN2v82+7nwgtatNh0qJbbCDzC0QWxIIuKA2feiSeZatNRiM5aQzxAY14+hbVBFqTkVvh/IHNB/uOGSZPbRtW2oV93Jt4VXCaspNKGgNBGTBqBkLccILlyMic2GprmGxzGojRr2DxOD1vNhUb1DUkERUHcTkYcAoSY7JPz7+zjcgEAEa5C5b992qGsSZJWnYxI2I75ZzIA/h/xPKxOVhw3d/SL1tKyK2k9CPiadRGgpSl4CtqCrm60to3Wh3cbZ2fycogyitZKK+/hUsFr17C5ArHRYWSuzbydaLDpKkXtTRY1lItCN7Kiw3VU7Zj3whUrVmANy3D/8UlIxMYslRyTliqVlv7TKES57arfUT1lYLHbGmCfs4g8iVFQpYxHpsCC5uBRSPhnx1W8ytQSGzig03VmmV8cLoW9nX6CJuYdTOpkQnvbpAJYZbJwDbDBXizEbBvPArXt02q82Exr7VTPqwepxXG9j5wCfjX/AzYt9iGxMeU6M5ewGk5xNqJ0GhD7gXLTKikwrfQGz9P4ZQvzTU9A2sJTx17TfPxWC/d1KOUMhnLFQ21s+KjqXkJ6QXkBzgngJcCFftUNfy9Er8bbXUvm0/BGCnLTiFYL+g+gB2CWQO0IrpdckxjEGZSxsqcjPV/YK3WkXt80+OAl0fKgWHT6JyQAALP/TLyowK//1JRDToFDRb8BVArwRDQRJZTm51l7gVRUeINhDvaNV4vOADt+X8V7QRshPXHuU7P6Eca+hr4GbhTdOayoqxENtcc0vCv/7ReGfpTeWdwR33Zf+hbNWzlKfh68E7WzSDlfdJ/SxDk0F7cqcTvUULXrjJ/R+Q6ir8CjV13hCX8OYio1WsMeLL0PzOEpX71pDAIkA6mt/1XkGj++lDk8ELT7u83xqVu8YtPgq25/Gb7YvD1TI3LsvBO9DihFXBcNDTcdCbuJt3J+wkMEV+NtIWwA+HGY/fOa8lE1WcZxjCZxnMRwwaRxSG5RjZMiH96DHSEEogITNFHEcZQuUaxTYByghdxEiJz4C0F3x6573YViFpeKqiD3uiKCutz92YH+4ieKBYkleppBCzrCDvIT6t7312PVjt+0l8PrJok1Y4bpBgdmAATL34DJ7cNgK4vrB/vF7w5KGQF3/IS+1QOZnjjvkXw2RwzBHDiooDESCjTuW80wryeENLUZKFlmPPBt6aQKYnEGULEpM17G6lReA/RB7SHeJQ6kF+/cAxRSLYtzj3v/OEUMiKb4KREnimBwMV1cbhFInK5Txz75SjY2+3i02X59Vm98hlKmnO1h4EYiTxBjtWhfuhuDPpF6hncIaj04GpWgGpUyHcjaNw8oepo55TxXfKn/2XwW/f6LZ/0T9TAWzS4vkWpl1VolEV4lkVolUMAhkAkuEhUjX8P0cH4zIEd6Iw13IIohiCSGDt8KCtyCFsoQGHaSpvp/z/n3l/gMVSzzOHajkyWmx3Add8jN+Rs9l8I1fMWFMsUcYwS5G+0wCYB+t8kGKK53doFslrTZw3lZlQP4ILWkNdAMt18+6h1K0R4O0YRR/Ci1tBcnsGiV45CO0xUmwmEyAKlmPy/yTHHmFmXPHN3yWVacjw6u/h817IiNPhZ7TR/aQAAkX+ARuxPehZHlxuGAsx7aH6toXIg+So3hwV2UnVOJ6cLeK/o8FL8erbyXmO90OBKdsOUuuCuIHnW05nI5LdZTfCFFNypQwZrmc7CEfHA8XSNnRZ/abwAsoYxOkDcqPLNSzRQlIKnXmj95RrG9VntDmpS8O4HyFmOtOjrvsuXqyR4PkW2qug062sIfuMX0tRget6ioDYh3oNYdQJax1yBan/8jupzVRrVyMF+/BgVCugW5PLO6m+YaqPQqvDzTmNiAX7cByL9VcnPqugPq8ITdUbKCXKUpZxro17pVnYlWWTUKtZXxdzBJJdtQl3QGr6WoIg9Xq1zbLN9aU0IdH3r8jnEpWl5xz/txmCB49bcl+eRpv5i5fGeU7Zu/vgMG2jtFXjix2lI2C8E/SPORh6MWgj3WH3dmADWR5e4N6DbGeyNsupgbqKuDiIssgz8IkGSGDV835oCdXmAlQ3rmJGJXUI8B+xtLc4YK5nlzp4fS1fPQZ0yqPm9I5S9zibxWu0fUkRYWOlo0ASwcpR2EC9I7YD8PkvEwfVKF1WRI2snxop43+/FmbE/zqo9LYCSyaWau+JxEpZov9bJ/IVtFjJcd/OzeU2rvfhh+iGxqFHHLLZQImlVktMFi3z73rNDvQfN5CU6IWRWOo4ikgNBD2Rck3gCZRjVoWNqSFNTJzNwU74tzsjmCnUYpXNFv6vFKudc7ClrB7NzncT2531k4H+KbclF163r6vpFpXG1uWnZBedN5gb8+OuJZbmtwjnWlLQlQXt6OZCz9YBPrESLgIq0stNsezg3kpwhRwJtc6a0dlcVSiQjF0EWxQCVi+eKEYsVhsq0H1tI6Ujha2FbYXpsmWKaboZilzxVVCnQKDor2iHNipq1sbRh1+jTYe467hPuIeFO7i3uWe9zZoGiUvfx7ynv785L7mvhMMCjIJiNMn/0ujxlBUpCDPXGkM7Gn/d4w0Qp2oFJmNzk7iIH0X6xijgi0FKTtIeyYgBkeLkeZEEUeTpccr1YPvT4/6YzTenxjMj932Vx3FpD4mD9mM8nzdpDFGKlWnKDfGHxfDjO6vteL06sOGeroWAxQF2m11VwIXGmt/ZsSMEyfmYc5pasSNXVRJzEwDDXEmsxP2skxPVHRs+YqMDAjJd1giON1df6Ybg5vBeEeRt8DVy4YlnI23fTZc5LhcA0ltqrGxjO393vW4IbsjqK0EwcesS1EtiInbYD2ItXl4EeTQrbjFd2k5QckUt35EEPs1QkIuz3XZX92uDSUK364NE5rcLs5Amt4n2GskzS4jn35S/mfX3K2vprY/A0/A2yqZErHbKu0sJan4q+eAl4y9r8vXYVnEID74mv2Xr2/iQFtkKDn/TtSuozzRmnnA3UEkj1Wbmfs9chsIDNWuNSeJcCYRXgNRqLlSQbqzVWPJQmT76HAce3vwOaLOXhbgq3QgtRd6TN73mNMaur9siSOI6HLkRYD8pJBvQ0svVv6G7vGpGN3hxVaGzRAoRKn+HbVGW0HzDqODZowATqvuRB3RrSsu/BTZQIvY1ykkkko0SECyYdvy5AMqWkMBAGbKI7nj3uUX3e/4cdFKu/EzbZfv+Rx1PPIGrVVCevoiaCY6R85tJiL+7rMUlaTqrUrOjU2wYLbk4b5gj6Tnhuep5OnCYJik77rsC1S56Z8sOyC5QiXX0soh/LryEnRGglghU3/nrJFJZaqNlklkSm2R8WcyLZYJZHpH20f7c3Z9cV1x93IgykVqSEbrLU63PTM6SNdF18UWpeWH7a+ozkX8yjat9a71DnTFmtUyaVfr4t03QCciIkfhlZkj+RoAOK8IxjUCKhvQr4rF5+EWiYUg8pZI0mNtvH8yRAmlCK1IPYYdmoWp2LYvjIHStn/+ePFicAHzngUR0/6TGSoNNjJlZOx7gp7gsB8xfmAmWzQ=
*/