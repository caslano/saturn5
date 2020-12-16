// Copyright 2005 Daniel Wallin.
// Copyright 2005 Joel de Guzman.
//
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// Modeled after range_ex, Copyright 2004 Eric Niebler
///////////////////////////////////////////////////////////////////////////////
//
// is_std_list.hpp
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_PHOENIX_IS_STD_LIST_EN_16_12_2004
#define BOOST_PHOENIX_IS_STD_LIST_EN_16_12_2004

#include <boost/mpl/bool.hpp>
#include <list>

namespace boost
{
    template<class T>
    struct is_std_list
        : boost::mpl::false_
    {};

    template<
        class Ty
      , class Alloc
    >
    struct is_std_list< ::std::list<Ty,Alloc> >
        : boost::mpl::true_
    {};
}

#endif

/* is_std_list.hpp
n6fwe7mGRZ9Tcpx7xIelng8xrGX6nWlaTuwHLqj2urmR/b6f5Tm2yrp1H/URQ/xBfHeKeNo7HD1ch9Nlvvs3ncOMbeVMnOlaZ5mHzvnqNPjeJpW4BRK3S5hpfk53F3xT6u6o1F2RFte1n/E/qbtypnnTdHfd/Tn/0nU3ZYFWd4b232qG9b7bswQrWqCbBvdZc6/ONenb3isLtLZn6Bf3eYhdbhs7PnHu3GzHIuWfXtzvq8+jabqWh2H9GzrTcq0uefA53TYPaUvV73fstqNiZ7l/+G+J+QPDVcwbpxZTrqjRXb1Qqxrnc5XrWodkuKYzhUMs1FRlHgcDZb/FuB/DekDWDbKuUHu7YDkHl8cgO0/ab0Plt+4TN/y28jo/+a5y/XLR9G7ZC/J5vu58sjIudcsmSPeu4JzcxNy8HOP22ZFZpj5b5ldxhlZ3sgplvuXleHWth939JiNnW+/TilDW3/p4uZGugxferCPM50W/5bOMw7j9MNvav3Unfnll/Bo/o0hysTyjSF8P4+e4CyZIHnOkHmplGvNY/BfUg4xDH5/tYfv7fgoM8f839/1odRDvHkGo5BDM0JM6KK7MwadnNMk1PZZnNOljl0vsPbJfvRt7EbtUH1u7XqL6+/Dm2NrzYWTZ/ZX/Z8PEdTzafL1ZTIJ7hNFSH0PkPqMypz4nue+Lpw1583xXu+uMziZYn1P1AP8TvlCN5/szqqQevH5GVW/JbXmie6TH5R0IrzP0UeaPMTdatjWnel4sG9JHSJ/teXlpMNf6jI9+Sj7Zaj6+PZfKlVM1n0ulzredkssmWd8Vqvfsabn4/rwlyadaz1vSzv8n2bfb4hx9PnLvkrvh+nzN2rUSsyRJfigxCxj6h1EHWsy/5vlOEtur5zupbSYy2T3C+gx1ZXg8hHrJNeToejOHL/Whv+9XRmJ8BkKy9VzsAOqoRItf8+cpSS62z1MaJ3mMcZjykHVumZbHX/csJbt1b55pWX7PYV2Wr1HajpaPb8/qaRRQ/Wf1aP1cintEa2VZXiX3DITnGXLhMEt11kH1A+/Os+zL2ubFCKs8DkMXaGhL9eZZ9y8GK/NQy7PmzxMyrzt/D7A+W6RwnnWbYQh5hC/S5+HabFFuB/Lq+aTm5SqPQUZi7O9Sre05OoxBl0NNzu2b66G+zTNWNqVat2OHk0OCloPvz1Qyx/8lwPqMtPA0a/yRxC/Q4v+1zwOSnCzPA9Iv13elmZ4HJPebFWs5+fYsIE/3CuuXjw7zrW3iWuqjXItd8+cASR6W5wDp83jUJo8xYfy1WM2j5s8AMufRyGZeRCwwL6fSr2l5+Pb8H2J7fP6Pfhndv8B0HkDWvdFa/Jo9+8cuD85eWO4h6Ztumh+SR4IuD1/Podv160scOYb1y1mJ/5YsE6+r96SZ4qckV2f9UuX6RLvHRNuGlvN+UeTwNcMMPh93xZV1j3FdY7zeMcPav4wLI+98Ne+aPy/JPB3pNs+vu2jJQ7bhtDxq9qwku3Yk4zDUR3Gm6VlJsq9WquVR8+ckSR/r9XOS1GU+PMt+mYtcUpmjL+dqq7usBTjdhUukrT/KMJ42E6OPrz9/68W1mpKDx2c0nTffF0tdnGVYp9TXEmOb/56yqSmVx/OUceVkVB5fvp/f65+LcHiJ/bHW7U5r25zI9EYuVae3Zs9+kvZgffaT/lnnC+37+RgtB9+e+2Q3z2UkxutAF1qffx5DHTi1+L4986mqNhesf+aT1Kq5LUZmm+tF+g0tL9+f+yS52T/3Sb8OzLaue6ZQN6W6HGpyLtzUPsjHun+TnmO//ik35rD4r17/ZOvWPweoh9Qc9/onYpnn9Y8+72a57sDvSt5vq+dTllU=
*/