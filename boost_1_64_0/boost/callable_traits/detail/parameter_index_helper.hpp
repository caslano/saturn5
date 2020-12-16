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
+R5Tb3k5qzcmb3npmIbSo/QoPUqPX/r4hfr/My/X+P+atvH/CU7tsNV+446Yl3nxqHiDvc2IvcR824lM32sjkWtglTf9/t6w1QO1FalfXMm2oYB+E83YgPri18KK0jbugUY+KkDfpmn7URmz7qUZv98pineui2qroT/Jr22mvV/bTJKxZ/i13Uw0/RS/CdIHPk/7wDM1/4djbvX0B/rnf+qUqTl0XNnKwPQB3CKyPaUMWiJh+gaDlwN+wcshL0A5RGk5LBa/flIOV1khpiwI4zNO4GrytjOmyy+Qx/b8ZAs1OdZiYjFzMWv4ccYnP3MLsnPGFgZp+1TZ5qY9M260xz46UD6qbJsS++lEecpTwmWKPdvI1rXnq2m3rCiyQzQ/vbLx6o+k+Iect66fsdf1IO2cVeBYiauM2u1xm3kZGQWpE03/SLz4p+vYlaL7ZhQmPpr2n4sYL3Gx5atzLi75HjquYzBGYKpheuma8ftHlyzzlkH02Gsi25hzh2s98IavHajc1a++r67S+vKK+LWyolQnJhv5uJLlp3n8O/HvgITqNxOmhtFZx38WnTXxgv3e35cpqaPuQzY+NUD+nkdPXZUaUE8RT1A9hV9wXdQ2taQuStYwRhdpvr2CSfoZ8s6eTy/p+IDvPOGV66iHWwPkk2ZTIP2j8nXMHK5nxP4n4ixj7cUEyCcN09T0Z70r9vXEkWrXTWa99KfE/20rmv653RjVURpPrRI6aqDxq2lFad/NIbH/xbqS/wcxkfb+xVS5TElPNC7uNNk/j7ajeHWjb1LCT7Gq4Ood/zFUx/1gGO/jW3ajKl78fK4L9aXYdc0wW3kG2u/yoPanbdJ3o5NptvIMvj8ycr59aBXSZY3xQOWHrG8fWg2RLQz0fEbWtw+tmsjeFKjMkPXtP6sqsvOC9p9FiH++79rhaRfXfxYrYbN9x41oHW4mfjcE6ztDr11839mU9H+978yvvIP1m2kdQE73/8vQZ8sgfbYcS7fXgYIp+UGeK+dErrX9uaJh6wWqB+rXKOBz5RPx68odqM8VI18j6HPlM/Hvbn+uaJg481zZI+PnLt+9Zc/bYefJ293lA397JGfY85a1/4PkbU5GiW8PwgZ9luAX9J0Xv+DfHmMzSnx7IH/hbw9kAn57JP0sz/FL//b4WvdTHKn5n6zfHvv98/88z/QXRbaTlEFDJMy7U9BywC94OeAX/Hn/gvj1kHJIMN8eGgZXe/52+gXyl7w0++gny390mOZlvuqJBDOOftIkcjNgHg4UmSHyvtjU1GVv2Nol9Hof49fA5pdp8qmP+KUTkhEuGM1bwgTWFZqP6h+nezFcDp0w0U8nZAbSCchcVWm39hPfFls6biHQuIUvZNxCyvYH/3r8rtfvuefsHe7VUTc1Lx238K+OW5B+VG/7ELwuQD9qnM5frgXrwDqwGawNO6q9p9q94w7yNL7MAOMOGmt8TTS+BI2vGeyk/Xw91X2A2lO032+4uGt/rfnWp50jwLiKxTrOYBm8Ci6HneFK7Udcpf2It2o/4hqN/zY4Bd4OZ8ONuj7sJliUX/pNCkcEyK/JyNWGedpPXAg7wALYS+2D1a75xbda8Pyarfk1R/NrgebXTZpf8zz5pe4D1J4C5+v14K7rhOu3i36ThfmtE75V498GG9j2d3gR9oX3wWT4AByr/erZ8EE4Hj4KF8LH4CL4OFwCD8LV8BBcC5+G2+Az8CGN9wA8Cl/Q8/1R++u/gvtMPuk7uMRZMp/6aLqv1/JN0XIdCrO0P34cHAGnaT/8Gu1/3wQz9TxJlvfdED89TwhM1POM03n82VoOuVqvJuj5sJt6kpwR/L5K1HJto/neXuNrBzuqvac=
*/