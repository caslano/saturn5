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
sObvWu+TjvDil58/MlbfDG5ySs9mYu4+AdLV7GuDcZ3NWdHOLJM4I8rbDC9eUCGmkMpX3uHmLaL+5RClAlb2hR7L6P+3/Y6ssL3dAzLa/XuTjipZy7G811jLlh6OfBdHdJNTQR2dfVQpoeLZAl0NSLeTL71mLJfEUVK5DpIXVniTu5gWYtdPd3TXqQtLwShRzzce9KHzN9VZPTCfrOhkwjXtwO8v3HJoT/m5UuUbu7V9zGaL18NJ5Aqz3aWmFrIWMGqgpc11rwk3V7kxbfD9FLkvqp8WRIHAjwaYqCrU+xXuqbb8/FNyOkIwtdIc/fdAH2r91n+XyoyKlI96XJfGXwA7YQwp/IeUsEi65ZYJdk/vk7WAMLZvq9G9JMflQ+Emei/mxLnHf2pzUnrKvbrlvTMIJtN2fh6ODCXU9xGEmfxT2w+iVgOTQ4MX8CThiX6jMck21isJM9L5ShyY1IwkExvOvhycrAw8TWVZlD4K50P4oHmEkmYvEVLuSZOUKnVZVc1a1XV/wTuqlbNJmPTOmch74buHkogEgSj2dzWuruE6nrElAFp/gvIALA==
*/