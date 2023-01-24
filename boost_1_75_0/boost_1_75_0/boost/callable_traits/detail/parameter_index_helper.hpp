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
uT0EnV5OcztDm1s8PVJ2rsG5bRRzO8gJfzC/g9KlwCA3XJPhD/aXQZkVY2G6x0rwB/M7FuZ3LNrO/Pc2BHg83K2mu0Fk/zKgE4U9Z7iTRt6vw/2wfnw7LFl1xQ/Rjm8PeRHuzbPrNbg3l6t4fBuvReYFtpKBPshtlY95A1foQF+WF6H7jwC6wZ2vWtUu0HMzdvjkDWRpgrFUcipuSsOjsNB2VFDIMbmZhWmOcgxMkifbvfDCl10Nv8kSx+NEhVmnHCwyZx09kpxS9oaSPK/ckCevwL4MILuxwAAnXaF4vBRw+uROvkAiKlIxMok3MMQOMk12vr0EXkp2PJ6CegLX2X1QR6CTp8adZqXA4facihvT0ApG5lAvl1AwGIkzYqSSMOcB7AExQfQt1hewYCqNgBX/NRrzZbsjGvMFPM7QblKIV/vPwwGVpIhWWzUOgl+oyiIabj1Y6PgAvf0/MFjnyQfrlwi40Mi1CEkYpA7RPzBI+A4mEfqX3eAo74uHAnjmh02u0mIyFBhRGUpx/9uiq8/ygKajhAbMUIgigAPK3BRjsUzKyTrHMSdfi78zmKOZPRkTT5jrGpzPCrKLKeP8FvKSv3tQLNxf6wvmVmG+B4yOVUH+8cn0uiIXOJbsXXQ+etSqhzbblhOY2AB/Ciy5PbdS7II6rcb/OPR4DXVK8gCO11AlZPJ5Qyi4Q+5xG3vwV5gLhz2Rhcdx4WSt
*/