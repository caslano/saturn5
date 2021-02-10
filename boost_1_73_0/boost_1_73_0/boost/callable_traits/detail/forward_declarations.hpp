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
FMT8MDK0r/evHsWuHU/RdALpGqQvqNBQwMESF8d2KqJOKiK+TX+ESZ5KgUlvQQYwIQPPp1EEnSVbw0fm5aZ2duIHWd+gZVAxQ2Bkf+WkGK6cO3hycCyFE2J7VfIlQV7ESygE4c/11zn+QSCMgznEIa1PIGlU2WUiPNOjCjSI1SQPuRFSJ1mfYbQVdUawGURYl9thlGhAuDhpfxLkK+crCE6Q3TfJGjpJTVGjIapLx0WY5VPfg0OOPScKNeHQl0okG4Hg1wja2OYtjpaw4gwDgvBP1VwwlFoXHn+D8+kDyf3tLiLLHK5GcaBpQ9dDH0F4dxQ4KyQ4LhEX9iZ3QMojswVDgAuBORCnrqrgW1AM8iN5EkEncdg5hUrMCBmEFMcrpECLYYeYVbhIStuZmTzAKt25IPquSlFsv0GhwxK6HmFJqcya513oGCc+8f85r2WGF0Xy89moBl8pRStPqj5KptEp1yrtacKTI06kBFPvTVOA87a18avtTilUzWgftEkpErla+iDFzqYLyMQ4MgtkKnfkqQijMkQCHvI5eIcvCQ/oUYcIIKzaAVbe8aof3NJzrVHfq9cbjZ/re429/Q+1JEZE86qIKDqYzBEha8QOMuAazJWyy1fh/qn+od74ab/eeCVubSqKAIFchPYt
*/