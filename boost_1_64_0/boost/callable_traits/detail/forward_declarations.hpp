#ifndef BOOST_CLBL_TRTS_DETAIL_FORWARD_DECLARATIONS
#define BOOST_CLBL_TRTS_DETAIL_FORWARD_DECLARATIONS
#include <boost/callable_traits/detail/config.hpp>
#include <boost/callable_traits/detail/default_callable_traits.hpp>

namespace boost { namespace callable_traits { namespace detail {

template<typename T>
struct function;

template<typename T>
struct has_normal_call_operator
{
    template<typename N, N Value>
    struct check { check(std::nullptr_t) {} };

    template<typename U>
    static std::int8_t test(
        check<decltype(&U::operator()), &U::operator()>);

    template<typename>
    static std::int16_t test(...);

    static constexpr bool value =
        sizeof(test<T>(nullptr)) == sizeof(std::int8_t);
};

struct callable_dummy {
    void operator()() {}
};

template<typename T>
using default_to_function_object = typename std::conditional<
    has_normal_call_operator<T>::value,
    T, callable_dummy>::type;

template<typename T>
struct pmf;

template<typename T>
struct pmd;

template<typename F, typename T = typename std::remove_reference<F>::type>
using function_object_base = typename std::conditional<
    has_normal_call_operator<T>::value,
    pmf<decltype(&default_to_function_object<T>::operator())>,
    default_callable_traits<T>>::type;

template<typename T, typename Base = function_object_base<T>>
struct function_object;

}}} // namespace boost::callable_traits::detail

#endif // #ifndef BOOST_CLBL_TRTS_DETAIL_FORWARD_DECLARATIONS

/* forward_declarations.hpp
8Z6wxWvTh2b8eqSURRWrvurTdXKOo+7raDHZSX12OCpYyY4wa7pjozXVXdvkeewSaQ8x+TlG7WZNXr90nLSlI9j7b6ac2+XbVqR+yxZJXI4I9EeUvt92FrcyjsbWSN4O+8l5euPeUdzvd/rtryfrVLcSv3hHe2sY62rm2985J9n3vdy/xHcs4u/EXj3gO/BROELSvixE85gjz+TxTzfruEPNq/6Shrm8+45lZtvLrFc2hrUOs0xdfEHk62remnObNcM/EP8fnba0+OSjJf5OK1KvuUDs+xxRrGjmXYv9IXE7Qwm/at7TP1/scTttdeDZ6f8uX191ZlO5zp0h46zr6MccbMU6+lA3kqynHJ1cP7h76Pt3UTtRtJqOFzD6Hi5hEm2mDQY3aN67cfd9vm69iPfvU0uK379vW2jeoRMtdetQ7Gbev/+8wLi18rotL3aTPLG/T5txxH7P78N+729Hi3Ws6Nxjxi56Q9xO2Nwy9DwngzzjaY+Wg2U3rVrKu3Dbf4tNL5//nU9lW5tn/HtiHxES4F1PZcu4GzFXc6prme6NQPupuD/LOgUhSLcK2N4g32wmDpf7KnZLneJaaEVpvf9Y3NdZHv06UOPYX/LdzzyDPxD5ISGqizXetvY2L6OLK0H3cvk2cMVx1/0B/eB9D/iDhHvZrps1Lm1nMPbVIfa4M2z33IxVRWOR4zTOUXKu+c5E3pWeZGXOPAd3rnO8edc5KfF9a9Pbvuc8ajtnoPfYN5fhxyWddrltOtc3jmN+caiuMGn+VtLMbG7vXrKS5gP0DzR1bHUk0npZxqriHMSYpPJGt56T+PpKPkyV+GZl5U/m2aTvbIMljsPO3uR6mjWUN+29rON8tVUZbXylsy/jdmQfPblPXpZrKHAHex68Lv6c2/jrs1XT+5WkZTNa+gpqbzcrUvcc+U7ce4Z84vpVUP1e+VaPTDWj35uIvaol1+Wn39PgC8uK2oFs+t3sYVJP8jFFduqJ1Pj/urJorf7GtjU3ysk5aqvddk5N9wcSZoTDfr3UMfPs+lGuK096U9rx5wnXF3enpK1LSLB9XLeL/4+Ox7mrujtaG31/VNI9xvOk0HrpTVNFo8f7RAXW5ddFCQMa/DCENcau1/3bVHTuxkXo8aRbi/V4wQqji9ta6lZ9RUnd/sjyknp8T7GbaVv5YZlxS8DpkttSdF6s/dvMrz0l0+j3o8VuRr8fC9LGcrSW7veqfRnltC/j5Gqvfi+YmnERfRkRa+R7w6H1n/BB+zLw81vfSMIuM3PBP1xboi/DtBe4RPY7kU02cdUN2m9hifw5kc8R+cD9FlHSbwFF/jXHQe7dax1Xmr3FUyVNMdiRM2msRjj8sR+TcC0c1WjDedgaY9f1nDNov4e5n7tL+LaOm+lli1GdkSRuT9HfsZKn1n2MUU42YcM4R4x+j1QXuV6OA2iq961KrMcdTrz42dJVw1pFWruTVkuOH8W9PdI1zd653S/yW/Dn6uvQORZBxv4Hm0sRbO7Cpe9hcKlj9i91zsHlmluQtkLk753+wPCXnENjplX6+KXtzSsFmxsRbI5IsDkrwea4XPqcksBzXC59jsilzokJNqdEx/PqeAQZd8GXmu943s4u1rqH/WA92B8mwmTYA6bAAXAIHA2Hwmw4Ek6Ew+B8OBougulwCZwAV8BcuBVOhgdgHjwEp8JX4DT4JpwN34Fz4MfwRvgZvAl+A+fDUAfphrXhItgYLoGJcDUcANfCcfA2uAZugJvh7XArXAqfgsvgW3AFDHEWyVWAHrlK8FnYAL4Au8LfwZ7wJTgYvgzHw2OwAP4eLoXH4TL4BrwDDoTb4CB4n7pTLsy89fYP04ao5XI1v90=
*/