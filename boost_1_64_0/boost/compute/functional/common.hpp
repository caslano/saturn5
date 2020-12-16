//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_FUNCTIONAL_COMMON_HPP
#define BOOST_COMPUTE_FUNCTIONAL_COMMON_HPP

#include <boost/compute/functional/detail/macros.hpp>

namespace boost {
namespace compute {

BOOST_COMPUTE_DECLARE_BUILTIN_FUNCTION(clamp, T (T, T, T), class T)
BOOST_COMPUTE_DECLARE_BUILTIN_FUNCTION(degrees, T (T), class T)
BOOST_COMPUTE_DECLARE_BUILTIN_FUNCTION(radians, T (T), class T)
BOOST_COMPUTE_DECLARE_BUILTIN_FUNCTION(sign, T (T), class T)
BOOST_COMPUTE_DECLARE_BUILTIN_FUNCTION(smoothstep, T (T, T, T), class T)
BOOST_COMPUTE_DECLARE_BUILTIN_FUNCTION(step, T (T, T), class T)

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_FUNCTIONAL_COMMON_HPP

/* common.hpp
yU/X6Iq5fALfgO79Lmxcz+ZUjfL1XZcY56d7wWXd/+wITygoncwQs4zo+8wH51l90PNfC+ccnI9C6jmtWw7KDc7GTi7K40Ib0T1ejXyOVtOfh5TacXWMK5wYczjnnz6QOCXuM56rE/XLsaJev52h57fE91Q5nnWolQTv822KeK1xyWqyv7/vXh4PXaWPB0W+/jjZ1Cc3mFtxkJGMh720JeAGEzhdc+7vinjBGovqQbIh4sXCoWwZY32ZEAVwqSLl+Tqi+oF3IEd0SeJ3z3cz8dtDTMOIguP25u7JBbkcnKhyak/I4eC0/XwKg3mcptP21tuGczmU5a0NnpvH4X3htN7qiy9oyyM/5ZkL2/Gov7/OMtiGl7ZB10yH2/Io1+hZxjva8HTAnhCdPKYtlxC6eaChcjvOb8PVQWbC2WL/1jbcrFM5Q3x06WD3iA8akX7Ia6e2cVz6YVUOT9qnvLm89knb9HmM2ZbDy7RLn0nP5bUrapPElycG3PHJfTrHqHn6yWwliC+Tx8cYKsHzHrn3wgAP4svCUIQ11Y57JXYtx3iat8RWfSGuXaDPpDo6Qo7GhSr/YsiJ48KK+A2vP/21uiDGCWSVHzvOBDKLY0ctbzaQXX7s2BHIMI4d1X92ldvx0jLFX/fl81S2ql9du9pwNfYbkXn5tjbc7Fh/huTff5B7UrrK9Nh8rptmSZ5xX2djY53/xu3Tdk3IHD3KT2Na9V8zMScb0+p8OOBmY9bZAI9i1uN8LBuzSiy30ee1jUkrjr8Q8NvGpJV1rh6bcvjtgyL1B3H9m7Gs6ibCjvCs7kxJ34W6k6szxaCecWyldljw5kC8iutFFcpZeHwbDuYl+VyUz8Gc9eyYoVyONWctr15uw6M8WfPsy+U4U9Y18V25PFF32Q/Qm8vLdIPM5frb81Oq7pudOUm5bs1e1iF3t7Dt21nkYdv21NSkOxlU36vu2JPl7GuS4Mh7OyOWky7Jpyx/zXTU4iniXIc+X8nFSxN+PYpjjtPU7zAj21ZGJ8choE8p2tYsxrGiTFn4iN5O5nOsUKoy/ic+j4mfkgenBqaI01X+vRdbrkxGvLPJphzGjWGTBmWsuu4Qx8HYWz8/ZzmqZ4V/LQo5u7ZuciRfho2n3cXnbezZJizV/1sWB5ytQlFO/7+WBJydZ2TzKbx1qc/hAOksZ4bzk30OBykLSco6L+RwmGum/bP7A44eLtRk+br8rJDXp5w9omdXL/M4uKI8zlcDDq7IkZSTHL085GzLcgrsKVAO7sorS3zN0St8jjXkbNsKlYDHH9ny+p+7MuCc25vl9E4d5nPYJ53l1CcO9zmcO57l1K4MOZt2ZPt2diHg9HZv0YZJDP/ZIwLO2Zt2rO702i/z62Ih5p2aZwMLjw14TfefqVfjhpDj9a/q5eajfE6fqrdyuuoBZ2ePcnSM6DzW55y/tnjauWsy/ctn89Exz7H0bK1pXwccrOt6HfscnpTLe52b1hh7JoOrkxQ5X5LlqJPU+s7sD3is3jmPrHu95rMcv9ADEucdOBgvfI+9dqlwJxMe//BwZ2qv/zuvzxEc6dh8Kt4zwFycs2h8OT0vl7M78fb6LDxJONOu5bLmcpnDpjirkueggevXPei1pyivOXFMhw+de8zGeHWEDIdTGvmIvQqPYCwc53U//uU+pyk0XWuZcxjBRqBZ/hh/XEvXd/BbhfyWZKlnc/qYvCJtyeA8bKEtorsZnIUq48WBgvfs2LGze3tpR/f2Ho6xohSds90/l5OW5MmjN58XnHk2IxzextjKO9tpvShO7bueywnP2V3I51CUUbtN/TLueOMBnmr2TfJjgP7zuPmrHb6pp/cs6svZXelBl+k=
*/