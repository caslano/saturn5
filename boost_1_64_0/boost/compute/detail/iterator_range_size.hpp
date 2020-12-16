//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_DETAIL_ITERATOR_RANGE_SIZE_H
#define BOOST_COMPUTE_DETAIL_ITERATOR_RANGE_SIZE_H

#include <cstddef>
#include <algorithm>
#include <iterator>

namespace boost {
namespace compute {
namespace detail {

// This is a convenience function which returns the size of a range
// bounded by two iterators. This function has two differences from
// the std::distance() function: 1) the return type (size_t) is
// unsigned, and 2) the return value is always positive.
template<class Iterator>
inline size_t iterator_range_size(Iterator first, Iterator last)
{
    typedef typename
        std::iterator_traits<Iterator>::difference_type
        difference_type;

    difference_type difference = std::distance(first, last);

    return static_cast<size_t>(
        (std::max)(difference, static_cast<difference_type>(0))
    );
}

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_DETAIL_ITERATOR_RANGE_SIZE_H

/* iterator_range_size.hpp
2SPPOVqMXi+Hb/DcpM6AOfGSnN9FP/eRn/uK89XivaC8OzdhGjFHHg9dj7u+SoaY++5C9IPqzLX9d+es/RXi1s2hWHOX5HLyzYE1Gdn297jPDc+eK2/mcvwwf6M71/vvv8u2xj5Fdl1v0tb21p/lh11zeMrnz48JPLcm5vDwquboH+aCMvvmfHZxfVa0eS73X1tdx22CwHOHdbbIUabNlFX3Z6gQUi/JJlPP65J2WyQDr8HaT+h7jaNLmTMxzMyJr6n6u9r/+d9pYo63mf1effN7NqKuuU3IzdCcLVg3T3USR9YCm+y9zlqgbc5mYumGrXFl/NzWkOMsFaaccz9tb7rOgrTH22yE5J6O3M/omLMSEwrmcocGUz+Dzrq+qW6MVTKMxBF6nfY4Esc5H9Iuh1TpsyDV8NxijyItst/VF6tDx6R+oO3/7hVzSI0euz8XC6tea+ZyuGptR55qXTzZmAk9Rb5ZZ4sDynQYk3Jv7Lx+1pG7grlgzblNTou7zYiw+Jc5Q4b0G1xnl7t81DoT65AF8aHz35MbMQ9Ye6PXcxK/Fycbb/LzVqwDdh3HxVxzfaflOf8ArxHs0iG15r4biIvw1f3s/cMFgoM/XiAocxcWHq8o4+yQ/NMFggybhJk5N6DFyL2bBKzTJM+a+8rKfc7MLxAsM3Zu8ecLBA3HCWWW4tw5hqx53GJIif25tpXn/MX+Gn8VDxPH68qWMs/S4gJBiKZzSWPpB5FgYowH54oEkbPGeDIS7Dq3uGUomIUifp9x/bIR/z58JFhSVolSvqjji0WCfdZikWCHcxwPCTteuJ5x346yR9L5YSISzKj5DEjTPX2mYsleSB1C6Uhw5Fxauc8ZSkw49Y8L+Nmoz2gkOGZxIf1e0IYPzidJnF/czK6jP1JLkWBPWae17L5r41xTuaNMKAeMr64v5Qa714wE8esam/trjgsUnU9oY+HcMUvXUO9axuraKY+bjovM3HcX93Wd3/I47zjhesf9BfapkftXG+6JciCOFfdNlR0q3OUa2lVuue/Y8d5JudPeqvZPKVfMUcl67YvzQNlUhq8XCTaVZTYcz+UwG3V8A+3cULs3i/g30N3/Vet6Rel8mlOsOb+4nvZvFLFfvcc3drwqf0SYOXdM1nFZmSfD4U0iwbZzUW2Etd9QjtaMn9OuFV0bk9Ze/ObmTT+BMqqfPffcxbWudmYej8W0q/7QPQUiztdu6pgVotooud5Sp3tp7V1G7OxSpMWIIGG8lxX/RbVPP20czk1TkSCmXsHx4ZXNgeOG45bjiuP1hBw7XnG8nVDX8YbjmXKiTJ7LmC6ubRKscBS3tugy4uC3nuMs/856ZsVx+TeeZ792juqvPP65/YmYkfiF5yU7FGgyIvJLddkkR59Bz74wH/BzaXKB4OxXPd/H6o/sz/HDCwTpH5zPa7K22CN0rI32yeCMcv/7XiO+ow+ObuM7M8pdZVc5Y/69c9vLzGvDSshnirzeOe48xPtpyqXP+VtEOSc99JryTe1Tokv/PecJFsqDr4ublb6YWemJm9BX9W2Poo0veA06uoDP8rtOgTah18sL2xwxIPIG42CfKsdES86xT4MpqTdqiwIdFqy8SVuUOSb+Zq/N5GgwY6lsrxNKDIi+RdvsU2FI/K1iJk+X0NsuEJwiQ50Z6YqcUmVE/O32CyJLnRGJd2iHPB3mLL3T/FGkR6SqbfYoc0zsXXJNhhojYu/WPlkazEi/x1g4ok+kJt/sUaZP9L3GR4Y6E5Lv8/OFPD2C96tHliqTb5w3iNz8hL+hzE9du4/23xyVJU45Hiu3B+f1/Qc5oMqYpQ/qmwqj97hPufQhMVJiQKRhHORoE/qw13Q=
*/