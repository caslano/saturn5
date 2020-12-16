// Copyright 2020 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_DETAIL_REDUCE_COMMAND_HPP
#define BOOST_HISTOGRAM_DETAIL_REDUCE_COMMAND_HPP

#include <boost/histogram/fwd.hpp>

namespace boost {
namespace histogram {
namespace detail {

struct reduce_command {
  static constexpr unsigned unset = static_cast<unsigned>(-1);
  unsigned iaxis;
  enum class range_t : char {
    none,
    indices,
    values,
  } range = range_t::none;
  union {
    axis::index_type index;
    double value;
  } begin, end;
  unsigned merge = 0; // default value indicates unset option
  bool crop = false;
  // for internal use by the reduce algorithm
  bool is_ordered = true;
  bool use_underflow_bin = true;
  bool use_overflow_bin = true;
};

} // namespace detail
} // namespace histogram
} // namespace boost

#endif

/* reduce_command.hpp
HJcmjscb/m7J5rqPNJKP1E/GERJChXHcqWP64UetfjIsFav9YmqaLpGkYIX6NZsofxy9HwO0ZrDSjDDSStxGSteplNxavZvQ/9RXoZ+7rZayl3GyD5yGmnfK9tUPCA4IlL/CRjrzMQznXaU2nmc2ki+mwjO+hgXmyNsWf5PJ1JRqrg7Eaf9M3Byxmrhfxvke3MJuwt63qEEYCpNr7Kx2NB3sd7y0Mdsw7p0yAX6WK37uAD8PDNH5ma1b8BQejLRaPLfBj0RKpCnFJw4PUPPKVGk2Cx0Z/vsuWznGFO4Pe5KgGf5RFU79lQgOvVlTjV2NQ7ya0ZRqqvaJhk8njI34oBeb4J5jDjp+NOyDU8FhdevdjOVWzGmZb2fZ3vAVK0tNDbV0un4cZ1F6Bl6AXP64IOGnewpKtGy3fc2TtFluriw329f8CI9TaA+8PvP+lSPj4fyxlWV7l72DJMuDN8vSupvTuTUpnZUjTWFLZeurwRkS4zbGGJeEEXnXtnwA1kUZPI/B+Ulg/CvcbDlahjaFWrlDot3BaO9fmUDzTWOvERNXcRGymeEkiRtk3D0G7vkJ6jl+5NnVXWh7PD1yvQUNciSmRvb188zSbIOMCGbqXpuKyhrt9/XGS+RMhn29DQ8BMphgfj1idGnCPPGywOMKAA31bmTEJjOS0STnrrZGmgMVxij7BZZGt6hdacUNuzXmZ6EL4MEeOZqCpDpswSVtnGA3LuZ6vm0f3V9NO22QkEP1w2j/zjqmbU+XjTtskexs212dJ3DrNmJkbKN4ZSewXzodPizHm7UT2rbCo4U7tSbXZtdO7OqNP5mxBXdIb5G7hBNq87augUPVcA8UT2ufhhqzz7JFOpn83AquuMBRlV3YPHF7yYy0x8MDAydUODtt5ZJov5xLYiaM7WVJsGPa2efnqPCf9DnrfhXOc0ib7SYcQ9yJ0tmWEXM1AbO2gzye8/7WB6bXtk8l+FHuhwWLA38jmSwS9w3nWuLD8RQLgwaOnjdXOMwm+skhLw3RSmdkky1ambuRAyvzU862BepLELhmuGFfbF9NGzoalXO1rTmVCVVLQtU6oVzq9aJ3O3Uifu0ep5YWTZUOybC2NFqfpFfT+zitBodLyDk8DnXiSDoOfJI7jdB1wSlMnc4kXZGN+chU+bqkAK4xRIucikb5GEUP9hOv1RTg+GbduXgSOLcP1ZdPW+CETfV15F5uwzXg4jadqVzxuf54nWfw+Gl6DeCVzz/hBYfZP5wF6oVsNJMbZ9MWOamQ5KnWFcgBXJEXGQvqZSKUF1zMSQfuoza4Qe5wr7pM9wU9m5xB0/Kq+PLV+sJoXbgYZ2vN4T/62b8lDXC8jkf+RisMD55VZq5KZ8vl9FANjy89wvfGF9nEE+j/Gm4wE/HYoiy2PpWycE/rKlhb7OnD7jN5LWadAats+bjuTyWfCmjsvVYT8ZQKntxiEK3OTskN9vDTXGutdQi6KmChs7yUy6qFtvDJo+vQThxTEo1FnC1Yg400eF9rkry3zoeDVfuak5A9cDZCcYZzmwjhk6DZ8ixqEcihR0sx7CoagYDzpUSJQaWlkkorKtTBwWpqKL4lNyE07CsspVM5WoyVopyoNK2+0CPh/9SPft8CDsNM5dnWFewEkOrUvmavSTpAgqPmmbrI2sTu6/RSPXSNNKqvoRl1ah0P0JgLBXvAfb50wJPPy8WF5bIbcEbazctK4TNnihhSSJVbkQXA1FwUvP3JzKFlW0O5gU2GWNwSaJDyumcwFyK3VkQWE4ZIlw1H4fJtC6MrCVcxHhmsdFDjbpuF5PrCLf58jzT9+ARExr5mAmoaDIPdBmApo1aWIVrBmiY+fZWe1ddHG6Y=
*/