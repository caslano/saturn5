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
HErrIN+VXXLCo+lii3XQnEX5hHwERyeOy/v28hmvSthPkeV+5tGxP3uQNnLSRT2448cRveahHREt8fIi4KFQuJqDdfcver1DaQIGHjp7G1nfq2ygPzgetGFiez0hS8PHpDTn/gqmZu6PFdcTffxeo0oqMisaY/lQ+5eXzGiIOlhJWSV/FDRSqBXivx8sBVhZSUWz/ScpK5VUwc+GvGQyoLwDSVh4TKHgznjwtzI5Ru0mQuRLogkjUziZpuZ9m7bxg9wrg2ney1PjNW24mg6vuK0Rnfi4DYqCJYAdJOeLXQ9W1Hy8eRJGzofs4MkV1BISnB1ddo5xhKl1oH4XIZctbvMtB0rmCCcnuw9/rltJT7NPhCBYG1Ev/6MElTreZiP5eUT6/Voe0TOqyHKc18uz5ISX3CUveURe7vrgvGlZN8x4gUdzHr0DtL2caLRbfZnA0enAGgH3YDi6MTSgrQNUEL9vHSTDOQoIEc9iX3B3tc0vnYuXX0LDtORpHHpCHp/EY4qWgENRVDYH4ClxVSFQZoO4E4O7n9LWhKKugnYmszN6BzLFk85GIDB6F85NgoGulFu5HKVCvErELV8oIwnwgweZ9Cg+0hZHlg/lGvaS3S1txyvRjR3cTrW/x/3d9Y3coggOjMn4IGKSlIK4
*/