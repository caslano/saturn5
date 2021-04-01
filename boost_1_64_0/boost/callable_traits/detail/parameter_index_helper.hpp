#ifndef BOOST_CLBL_TRTS_PARAMETER_INDEX_HELPER_HPP
#define BOOST_CLBL_TRTS_PARAMETER_INDEX_HELPER_HPP

#include <boost/callable_traits/detail/config.hpp>

namespace boost { namespace callable_traits { namespace detail {

template<std::size_t I, typename T, bool IgnoreThisPointer = false,
    bool AllowPlus1 = false, std::size_t Count = 0>
struct parameter_index_helper {

    using error_t = error_type<T>;

    using args_tuple = typename std::conditional<IgnoreThisPointer,
        typename detail::traits<T>::non_invoke_arg_types,
        typename detail::traits<T>::arg_types>::type;

    static constexpr bool has_parameter_list =
        !std::is_same<args_tuple, invalid_type>::value
        && !std::is_same<args_tuple, reference_error>::value;

    using temp_tuple = typename std::conditional<has_parameter_list,
        args_tuple, std::tuple<error_t>>::type;

    static constexpr std::size_t parameter_list_size =
        std::tuple_size<temp_tuple>::value;

    static constexpr bool is_out_of_range = has_parameter_list &&
        I >= parameter_list_size + static_cast<std::size_t>(AllowPlus1);

    static constexpr bool is_count_out_of_range = has_parameter_list &&
        I + Count > parameter_list_size + static_cast<std::size_t>(AllowPlus1);

    static constexpr std::size_t index =
        has_parameter_list && !is_out_of_range ? I : 0;

    static constexpr std::size_t count =
        has_parameter_list && !is_count_out_of_range ? Count : 0;

    using permissive_tuple = typename std::conditional<
        has_parameter_list && !is_out_of_range,
        args_tuple, std::tuple<error_t>>::type;

    using permissive_function = typename std::conditional<
        has_parameter_list && !is_out_of_range,
        T, error_t(error_t)>::type;
};

}}} // namespace boost::callable_traits::detail

#endif // #ifndef BOOST_CLBL_TRTS_PARAMETER_INDEX_HELPER_HPP

/* parameter_index_helper.hpp
GnGOPuA6w/ZsTmSI6C0GCrui2WnFgY1W7cbCObyxcojki0lZ0apsoMrqlCtnWGPWyXAT65WxLMD0pw0+lofhhYRa4aPB+Ke3nRyO8qswqrFqh4EpTRU+KxQ9CmyF1fINZmEGYXgUDRPLwl52QuNVYsufRxvByvJfzFpnoZwJijGi9PJRbVo5+GGpZfDYe7+2vGmVw1CvBcrzZXpCsEW0n+OR4b40ZzM62z7zG8AWVm5I0ZBMiEF6Aszl2MOGAlKUvP+bvlicmictw1V1CqDtdQLvTts0EJAlEwu7om6duCs84/QqGl28/gxjR6DKJbdlS+IivsNwVvLqMRnCCyOhiZVoE+ikBt0Mo7GiXmUG446oWTbvtORpAPURcLuIzBClSsnc0L7OHNw6OofrFFSzWEurrFCzVd23sJJIDHfUWWi01oTX+Vqf0z4o/eSn9OdIACStwIIBq+uvuSF/pv1HIbus7GyHqfCeyIGRDqKrodeAK5nhWp68SZp/jfHGUcXpAYQIm1TC+iob0VXvSZUof3RsJiuUJKl4HY96S4tj+M7ZCs2H2Tay6x9azA==
*/