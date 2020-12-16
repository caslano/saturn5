// Boost.Geometry

// Copyright (c) 2017, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_SRS_PROJECTIONS_EPSG_PARAMS_HPP
#define BOOST_GEOMETRY_SRS_PROJECTIONS_EPSG_PARAMS_HPP


#include <string>

#include <boost/geometry/srs/spheroid.hpp>


namespace boost { namespace geometry
{
    
namespace srs
{


struct epsg
{
    explicit epsg(int c)
        : code(c)
    {}

    int code;
};


template <int Code>
struct static_epsg
{
    static const int code = Code;
};


} // namespace srs


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_SRS_PROJECTIONS_EPSG_PARAMS_HPP

/* epsg_params.hpp
hYxfM12uvvfXPHLrMnqXrAizQWNjjuDsIePx7Uzr2x1njzSuz6p/otG7ZLxfLFPOjMT9gcyO2bgNhT9ib5LpmdXesBH7Nl2ykteGIy/mK9T79oOZvQfOHjI+zrqa/hT2pmRdHroVEBZMxnvQP6G2HXqXjPeZfdSslagfGc/Z2TjjO0kyWXFmb6MCcO4qK9U90SL4DnrCQMbXcsr+w3b0pzSu8ZJo1CiQjNeoRqkNeMcLJbNmVnjSudLoTzLV17KUf+pg/5Hx+LIOn1mI/pTWOfHt11GIL4L6gK+lfx3sW2sy3i82Hd7+EuZJZsWswL65t9CfZHzfum6N9MX+I+O1jc9v1QDxkZVm9nNbi4+Ij4zn7IrFOeP9nYznelreRuMR3yp1D47Zu7wI9hiZ6lnx25vH6EEyC2ZfYhZNQ/2kcaH3a1XDHiNzYvbX+Toh2GOSjW37b+P3nJDx/bfDM58f7n9kjsxS/rH/hBqtVq9z9MTMUPQnGc9LdOxk48+yJHNgZrn0zU/ER1aKr/P6Sh3iI+P1m9FjsvH5hawss0nNCn9BfGS8tjVL1NyFGq1R91ml8oNGoEZkfFxys1XG76sk42v55rQuAucEWWFmXpvmfcU5QcbroDS1e4JzQpqzUv+amYiBzMBs4InELMSwVl2j8beKbEEdyHgMHz7t2IS9QsZjb7TsxSPEQMbr9/VU3puIgYzH97JMGtYZrZ6T9tzB/yAGaVxUgQa2uFeROfDebRqBXOvXqXtiSe1XD9BLZPx6J582xjNDEJlqb3os6YpeIivDTF/+ZGnUgYznzLZ/W3fsd2ktyuX2R3HPWa+ubesDxs9YPMj4nPnC11vimYFM9XnPo7YuOLPI7HgP7liVD3WQrndk9HFbxEBmy+swPQnnUhIZj2Hpgtv+qAOZFY9hbaN3iG+DelyNjKjJiI+Mr7OMbgd63pesKLNL4/IZv8+YTPV9JV/z9UONyHj9/tOwxWjsdzI9s5nOI43fp0PGc+3WqPkPnGdk9sz+VbtRHcQXqe5Bz3kTluMsILNhNqfhfjwv+ZDx+i0oHtEW5xmZNbMiJ5ZeQm3JSjCz8P/cDs+7ZIWYvfDbMhe1JeO9u7rk4aJ4JiLjuW5SzHoz4tuo3iv69l37oX5kvF/yuE23Qf3IDLxfuu/BHgsm43k5vqhdRdSPTPX1gHYfFdSPjNfhZd5+xp/9LY2rWveH8WdVk/H+7PWhSU3UVorvYnqc8X3l3+qcldmWxxgfGV/LoIEp+VA/Mt5L408Pz0R8ZIV5L52wHo74yHjvmq9YYXyfJuN99rTJy/aon2S2Zz3foH5/q+/9/356ozjqR8ZzFldzv58wPzJ7XqNXe02x/6RxDhYxkxGfNO7X2cJv0Z/SuOJv9vujfmS8DuufvIOlk/F+CU93wP1B2aQ+C9LdL+IZ2kBmzaz5g++f8TxIZmDWeXL/WNSPjO/NQt+34B4QSsZz/THk3/8gPjJe2413ljoiPmmdR+u1Wor+JNMxe/Q8qSf6k4znZV2n68bvg9isXueUntuWID7Jvn4+5Y17B5nq+6jjvupwvpDx69WpsPM/iE8a5xLt/xTxkfHa1gstGYf4yGyZ1d4613gPJyvC4+tufQzxbVFf72Jy75qIj4z3mU+3/sbnLDILZrfaxu5Cbcl4jQ7Wi+uE2pKVYlauT3lL7E0yvo8ejp8JS5LWcuPTLtQ2nYzv6dDg4xWxN7ca15k9PqnHd0/ETmbJzKpePuTTVRo3MamjL/JCVoDZkYqxyTizyFyYKe2GdEfdyarn/iyo7Jz/2tELPRizFe9HOVZ4qDIa8ZHVZrZr9s2COF+iaJ3MfpxshfcVH7J6zDq/15fCM0o=
*/