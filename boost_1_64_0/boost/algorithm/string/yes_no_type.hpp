//  Boost string_algo library yes_no_type.hpp header file  ---------------------------//

//  Copyright Pavol Droba 2002-2003.
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/ for updates, documentation, and revision history.

#ifndef BOOST_STRING_YES_NO_TYPE_DETAIL_HPP
#define BOOST_STRING_YES_NO_TYPE_DETAIL_HPP

namespace boost {
    namespace algorithm {

        // taken from boost mailing-list
        // when yes_no_type will become officially
        // a part of boost distribution, this header
        // will be deprecated
        template<int I> struct size_descriptor 
        {
            typedef char (& type)[I];
        }; 

        typedef size_descriptor<1>::type yes_type;
        typedef size_descriptor<2>::type no_type;

    } // namespace algorithm
} // namespace boost


#endif  // BOOST_STRING_YES_NO_TYPE_DETAIL_HPP

/* yes_no_type.hpp
Kamal+0Lej73Sv996l9oD//e9vcTRcUR0WO9tFMoFIP7QfPd2UwKdAN8KaDZb7r46Tpen+tULla8vBLeiNOAGoibb1DSp93BtIEsXLxnVM9H2eW+zL90Ov8ZeKDVnuxfZ+njiua1zBgXoLnPK6b78/hqxDv+xMxxHC4/sgDFABSb0wUg1ZrkWkn5WfpiGxSs+htm0bIGFdM2r0vFBOyK2bwaFXMnxTnqV91XzJPPH3jFKP8/j0nuKB7vR5kBfwIp9VXO/s8eS+bPsUn8OZb5M4BYfNvgSUTxJQDznVCg+ZugeZ5TrtR90ZxwO9Ot9uOXX1Yr7DzgN+wBkV3XGkhfn5eBYHbYIBfIByhZytXcfj83QQ++EQ4Brb/m8tpJHnj97689/vLoZ/Lz6w93w8+D535Gs3lXWc32o9u6b7atfzrwZtvX/82jqe33Mloqxf/NIzaceJtxTnoQOPtJ74VHUtObOzs1vbv3gd8MHweffz/wZRIrZEwpxlY4Ol3TbrQGjfOL2POW+cADYB9Tn0tiVS5l3vpLrmWc3K2DuLpqZU4ahS64oY1vQKwwhhch+FoEo11oyxRBTzc4TimgxYD+LBV6BEPZhZTbv8ao/dLvjZX6qXqYS0oiwxcLyB6vdHDzfvwpJJ1IGiIxsfPeTzKpR9AwIZ/MM+/FxZu3a3TxJs1WqW7LqW4D8A13xzTqNxe6yAtfACJBXZXsNHa2DggYY120/aokYOSYO+9BIrchkaoCc8+szkiHcKQO7DLCBizZomhuL+TNgvCpf/c14inuqRn0RJZ80xBObPQEEyefqcEhaHjFGeS37m1OBbY8hcYEQtV6tEr+U5lplEvzi9yUc5jtk/G/tOMScwcz/4PX+YLxZvBCYhH7rwjvynL/YiPlO74GJNV+C9x3603Fz3qwu21RYqOfpqJPsPgCsvK4tMj8KRqi9VAGkmxjLYHC7wTzwgUu5FNllYizS++m+uK4CyHWeETOmNnZxQfXIpWqPIo8JleF6OEOR9WpFPSDvH2Rjs5ORvJQ0G0ZFlK0R2eyekP6Q9jI3xkwF9u4E/w24fbgM560CfjTUM4C/D39jDyb8dzxzJd/Dj1Zv7nsAekVdM37miAuEpxwt+LqyoHz71IS8zJxyepc1jliZJmDbmlLwFdKkn6CS4/INoBds8Sbxx6qFJzwQvDT/HTq3iNxBPeL6TL2/VMXy3j33O/U1ssWs+ha9mDJl11jABioz8v0qLEJotsal3ADbpa5nrWumXncO1ialF9aayAON9tcoi0JEO7IrGol6Y9L5pXjzMo6YqTJ3MlHVZ5LPTQxy+7WhxNydSV9A5ySyTxUJXgd6pK6RKgJR0X1uR6+Aff6toTA6wBn0GIGscPfSder9OZqyeR9WZ3ws85j2jd76fcrH/k7aNA1zi3y8wgRgP3M+EhGiOvvTR0hFptLI+Kp+FIwOx3jGhg6/er+lcfLgNGxNIcH1juvlpuYB8vNu44mBMdO6IFHa3/BPLRJMH+sMPMFs69g9scjZIwo4o68mIYSc/nNki9uuSaQ9PEVBKJkXlDQhjSmCi6WBa0/0mwFUcC2UG9RqPcLxkBgbEzFmMgYlTMAHQzo8lTouQK9HNByQOtSoQMEeg6gpPC/mArNF2gpoKMA/UMqtD3M0Ez9FVs44yaPzjOV4v3iX33xg8j3jN+IZIFbsGwSdC397iOGzhYHtgnom+hEMZqi4DnsWvte/+L59yuxc594rI69nkNHLCB0epivzk5xTTv4gMrJ/q0unhsgqq68z9Ihw0sxUdtiPvYjStFkj/1IMaBfSs6dQsoVJI8xVPML/yw8cQX7ThIgCmOehnKQvHCLaLcTGHoPidA=
*/