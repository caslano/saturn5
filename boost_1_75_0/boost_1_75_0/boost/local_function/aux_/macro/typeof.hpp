
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

#ifndef BOOST_LOCAL_FUNCTION_AUX_TYPEOF_HPP_
#define BOOST_LOCAL_FUNCTION_AUX_TYPEOF_HPP_

#include <boost/local_function/aux_/symbol.hpp>

// PUBLIC //

// Actual type-name for specified symbol name.
#define BOOST_LOCAL_FUNCTION_AUX_TYPEOF_TYPE(name) \
    /* cannot prefix in front of name because it could start with non */ \
    /* alphanumeric symbols (e.g., & for binding by reference) */ \
    BOOST_LOCAL_FUNCTION_AUX_SYMBOL_POSTFIX( (name)(typeof_type) )

#endif // #include guard


/* typeof.hpp
Jha+nBg7NS0VPEYREDWbOpmtNDBMkusu/oD/c/QIm3K1zwKzBEOOhw/z8zxVlXC5pKWQ0rQI7/JuCeVPQi7NPApPfV6y0BIDLjJ/WiooBwB6wRWZtr+qeqQLae2BLgMELayNSN9twHMZDjQwUIvuGkAhgOrDAiXfh0UWaLatQRTgkAaXgguXQPS8JKKwoUP5zQCYgtKhzo6k9PE8WDeMMoZSjgpHX2iVe5kcyOlOpnwU8oYlQSaRKabQozSY7DTwI+Tmed8f6Chbi3ER8LIt7I7nCsRs16cI0sfCEEaT69WY1kf7nIutqU9jHYKoT8+HcD6NLC+ElW+PFdPPkhngZE+eMH16Axot4xHYQq/9k/jaizlVmsyrQ6RRQWzKeoB2JnUHoRPZrlctjsSe0EIXwCnAbJm9iOCVrJlwCdpfQ2kkr33LJEz5jDmfOzFgfpm4vpi6zaYdwNyL+s33c1hn7TM48j7sbYSwRhz1D2+3P9etnZsBJfoe15oOGGoQb8VqB5fmkZfVVDXTZGDCZQb9pIftdPmdtgqKroKTJRPv7fQ4CZkd40M7wguTpBfjT0E3RreqsBeUUWY8s6mJA9O6c3QDUc/VN9AUEh1IbR39wEEtnf4Av1AgaSbF7RLD1mshN1o3VNBfUMxdn6AbjjkfXTdQbcep97HcoI36QWDUrcXcwEt4GcKmhGG6/en3gG++cpFQgWSkNq7HlPc5
*/