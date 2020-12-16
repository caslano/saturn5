    ///////////////////////////////////////////////////////////////////////////////
    // poly_function_traits.hpp
    // Contains specializations of poly_function_traits and as_mono_function
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
    
    template<typename PolyFun , typename A0>
    struct poly_function_traits<PolyFun, PolyFun(A0), mpl::size_t<sizeof(poly_function_t)> >
    {
        typedef typename PolyFun::template impl<const A0> function_type;
        typedef typename function_type::result_type result_type;
    };
    
    template<typename PolyFun , typename A0>
    struct as_mono_function_impl<PolyFun(A0), true>
    {
        typedef typename PolyFun::template impl<const A0> type;
    };
    
    template<typename PolyFun , typename A0>
    struct as_mono_function_impl<PolyFun(A0), false>
    {
        typedef PolyFun type;
    };
    
    template<typename PolyFun , typename A0>
    struct as_mono_function<PolyFun(A0)>
      : as_mono_function_impl<PolyFun(A0), is_poly_function<PolyFun>::value>
    {};
    
    template<typename PolyFun , typename A0 , typename A1>
    struct poly_function_traits<PolyFun, PolyFun(A0 , A1), mpl::size_t<sizeof(poly_function_t)> >
    {
        typedef typename PolyFun::template impl<const A0 , const A1> function_type;
        typedef typename function_type::result_type result_type;
    };
    
    template<typename PolyFun , typename A0 , typename A1>
    struct as_mono_function_impl<PolyFun(A0 , A1), true>
    {
        typedef typename PolyFun::template impl<const A0 , const A1> type;
    };
    
    template<typename PolyFun , typename A0 , typename A1>
    struct as_mono_function_impl<PolyFun(A0 , A1), false>
    {
        typedef PolyFun type;
    };
    
    template<typename PolyFun , typename A0 , typename A1>
    struct as_mono_function<PolyFun(A0 , A1)>
      : as_mono_function_impl<PolyFun(A0 , A1), is_poly_function<PolyFun>::value>
    {};
    
    template<typename PolyFun , typename A0 , typename A1 , typename A2>
    struct poly_function_traits<PolyFun, PolyFun(A0 , A1 , A2), mpl::size_t<sizeof(poly_function_t)> >
    {
        typedef typename PolyFun::template impl<const A0 , const A1 , const A2> function_type;
        typedef typename function_type::result_type result_type;
    };
    
    template<typename PolyFun , typename A0 , typename A1 , typename A2>
    struct as_mono_function_impl<PolyFun(A0 , A1 , A2), true>
    {
        typedef typename PolyFun::template impl<const A0 , const A1 , const A2> type;
    };
    
    template<typename PolyFun , typename A0 , typename A1 , typename A2>
    struct as_mono_function_impl<PolyFun(A0 , A1 , A2), false>
    {
        typedef PolyFun type;
    };
    
    template<typename PolyFun , typename A0 , typename A1 , typename A2>
    struct as_mono_function<PolyFun(A0 , A1 , A2)>
      : as_mono_function_impl<PolyFun(A0 , A1 , A2), is_poly_function<PolyFun>::value>
    {};
    
    template<typename PolyFun , typename A0 , typename A1 , typename A2 , typename A3>
    struct poly_function_traits<PolyFun, PolyFun(A0 , A1 , A2 , A3), mpl::size_t<sizeof(poly_function_t)> >
    {
        typedef typename PolyFun::template impl<const A0 , const A1 , const A2 , const A3> function_type;
        typedef typename function_type::result_type result_type;
    };
    
    template<typename PolyFun , typename A0 , typename A1 , typename A2 , typename A3>
    struct as_mono_function_impl<PolyFun(A0 , A1 , A2 , A3), true>
    {
        typedef typename PolyFun::template impl<const A0 , const A1 , const A2 , const A3> type;
    };
    
    template<typename PolyFun , typename A0 , typename A1 , typename A2 , typename A3>
    struct as_mono_function_impl<PolyFun(A0 , A1 , A2 , A3), false>
    {
        typedef PolyFun type;
    };
    
    template<typename PolyFun , typename A0 , typename A1 , typename A2 , typename A3>
    struct as_mono_function<PolyFun(A0 , A1 , A2 , A3)>
      : as_mono_function_impl<PolyFun(A0 , A1 , A2 , A3), is_poly_function<PolyFun>::value>
    {};
    
    template<typename PolyFun , typename A0 , typename A1 , typename A2 , typename A3 , typename A4>
    struct poly_function_traits<PolyFun, PolyFun(A0 , A1 , A2 , A3 , A4), mpl::size_t<sizeof(poly_function_t)> >
    {
        typedef typename PolyFun::template impl<const A0 , const A1 , const A2 , const A3 , const A4> function_type;
        typedef typename function_type::result_type result_type;
    };
    
    template<typename PolyFun , typename A0 , typename A1 , typename A2 , typename A3 , typename A4>
    struct as_mono_function_impl<PolyFun(A0 , A1 , A2 , A3 , A4), true>
    {
        typedef typename PolyFun::template impl<const A0 , const A1 , const A2 , const A3 , const A4> type;
    };
    
    template<typename PolyFun , typename A0 , typename A1 , typename A2 , typename A3 , typename A4>
    struct as_mono_function_impl<PolyFun(A0 , A1 , A2 , A3 , A4), false>
    {
        typedef PolyFun type;
    };
    
    template<typename PolyFun , typename A0 , typename A1 , typename A2 , typename A3 , typename A4>
    struct as_mono_function<PolyFun(A0 , A1 , A2 , A3 , A4)>
      : as_mono_function_impl<PolyFun(A0 , A1 , A2 , A3 , A4), is_poly_function<PolyFun>::value>
    {};
    
    template<typename PolyFun , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5>
    struct poly_function_traits<PolyFun, PolyFun(A0 , A1 , A2 , A3 , A4 , A5), mpl::size_t<sizeof(poly_function_t)> >
    {
        typedef typename PolyFun::template impl<const A0 , const A1 , const A2 , const A3 , const A4 , const A5> function_type;
        typedef typename function_type::result_type result_type;
    };
    
    template<typename PolyFun , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5>
    struct as_mono_function_impl<PolyFun(A0 , A1 , A2 , A3 , A4 , A5), true>
    {
        typedef typename PolyFun::template impl<const A0 , const A1 , const A2 , const A3 , const A4 , const A5> type;
    };
    
    template<typename PolyFun , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5>
    struct as_mono_function_impl<PolyFun(A0 , A1 , A2 , A3 , A4 , A5), false>
    {
        typedef PolyFun type;
    };
    
    template<typename PolyFun , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5>
    struct as_mono_function<PolyFun(A0 , A1 , A2 , A3 , A4 , A5)>
      : as_mono_function_impl<PolyFun(A0 , A1 , A2 , A3 , A4 , A5), is_poly_function<PolyFun>::value>
    {};
    
    template<typename PolyFun , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6>
    struct poly_function_traits<PolyFun, PolyFun(A0 , A1 , A2 , A3 , A4 , A5 , A6), mpl::size_t<sizeof(poly_function_t)> >
    {
        typedef typename PolyFun::template impl<const A0 , const A1 , const A2 , const A3 , const A4 , const A5 , const A6> function_type;
        typedef typename function_type::result_type result_type;
    };
    
    template<typename PolyFun , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6>
    struct as_mono_function_impl<PolyFun(A0 , A1 , A2 , A3 , A4 , A5 , A6), true>
    {
        typedef typename PolyFun::template impl<const A0 , const A1 , const A2 , const A3 , const A4 , const A5 , const A6> type;
    };
    
    template<typename PolyFun , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6>
    struct as_mono_function_impl<PolyFun(A0 , A1 , A2 , A3 , A4 , A5 , A6), false>
    {
        typedef PolyFun type;
    };
    
    template<typename PolyFun , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6>
    struct as_mono_function<PolyFun(A0 , A1 , A2 , A3 , A4 , A5 , A6)>
      : as_mono_function_impl<PolyFun(A0 , A1 , A2 , A3 , A4 , A5 , A6), is_poly_function<PolyFun>::value>
    {};
    
    template<typename PolyFun , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7>
    struct poly_function_traits<PolyFun, PolyFun(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7), mpl::size_t<sizeof(poly_function_t)> >
    {
        typedef typename PolyFun::template impl<const A0 , const A1 , const A2 , const A3 , const A4 , const A5 , const A6 , const A7> function_type;
        typedef typename function_type::result_type result_type;
    };
    
    template<typename PolyFun , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7>
    struct as_mono_function_impl<PolyFun(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7), true>
    {
        typedef typename PolyFun::template impl<const A0 , const A1 , const A2 , const A3 , const A4 , const A5 , const A6 , const A7> type;
    };
    
    template<typename PolyFun , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7>
    struct as_mono_function_impl<PolyFun(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7), false>
    {
        typedef PolyFun type;
    };
    
    template<typename PolyFun , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7>
    struct as_mono_function<PolyFun(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7)>
      : as_mono_function_impl<PolyFun(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7), is_poly_function<PolyFun>::value>
    {};
    
    template<typename PolyFun , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8>
    struct poly_function_traits<PolyFun, PolyFun(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8), mpl::size_t<sizeof(poly_function_t)> >
    {
        typedef typename PolyFun::template impl<const A0 , const A1 , const A2 , const A3 , const A4 , const A5 , const A6 , const A7 , const A8> function_type;
        typedef typename function_type::result_type result_type;
    };
    
    template<typename PolyFun , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8>
    struct as_mono_function_impl<PolyFun(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8), true>
    {
        typedef typename PolyFun::template impl<const A0 , const A1 , const A2 , const A3 , const A4 , const A5 , const A6 , const A7 , const A8> type;
    };
    
    template<typename PolyFun , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8>
    struct as_mono_function_impl<PolyFun(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8), false>
    {
        typedef PolyFun type;
    };
    
    template<typename PolyFun , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8>
    struct as_mono_function<PolyFun(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8)>
      : as_mono_function_impl<PolyFun(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8), is_poly_function<PolyFun>::value>
    {};
    
    template<typename PolyFun , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9>
    struct poly_function_traits<PolyFun, PolyFun(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9), mpl::size_t<sizeof(poly_function_t)> >
    {
        typedef typename PolyFun::template impl<const A0 , const A1 , const A2 , const A3 , const A4 , const A5 , const A6 , const A7 , const A8 , const A9> function_type;
        typedef typename function_type::result_type result_type;
    };
    
    template<typename PolyFun , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9>
    struct as_mono_function_impl<PolyFun(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9), true>
    {
        typedef typename PolyFun::template impl<const A0 , const A1 , const A2 , const A3 , const A4 , const A5 , const A6 , const A7 , const A8 , const A9> type;
    };
    
    template<typename PolyFun , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9>
    struct as_mono_function_impl<PolyFun(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9), false>
    {
        typedef PolyFun type;
    };
    
    template<typename PolyFun , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9>
    struct as_mono_function<PolyFun(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9)>
      : as_mono_function_impl<PolyFun(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9), is_poly_function<PolyFun>::value>
    {};

/* poly_function_traits.hpp
MZ4DzFPYhLd/nlF2FVZDWMuNA/lOZJiKniVs3r9cK7KXwwKEJTavy3f9YJiZsIu1Ww1QFgKrJOzuxYrcQwzMXNhB71t2jAtM7q/XF/8TzE/tmnmVfuMszoKZCnuZ1Z7z6AisorC+O0uuYQ5qe584fpML6xYWKGzwaLdAzrFpxnsPnXrEj3MMVl2YldlZD9YmTO6995CRRX93BBYkbE1MFfbkJFhVYYFtl+Rz7+pZvP9nNtXOsL8cgdmIdTeGx+9hbcLKCZt8fdJC1h9MxqX8kkuM2XuYo7Bufnn1mUuYhAaZL9l+W5W5aDblxdnR7HUwK2H5u2ptYm3C5Nl+rDNrKmcOzFLYrZYX8pmfMGthv3duznVhmo2+FhisLBLmIMx20qTdrHdtD+nlW/P8YrV1q8dcPqtsGsxOmGHdb7msaW3vx7OnsPekw2Q9LFt7tinPFuYtrEmnZPbP27DSwrIGzv3EvNas7Q9Plysz+QU9WVjrB6nsIVawAGFj7tnm8RxgMp4tlj5kbYbA5N5dz+wtx1jDZB1Nq7j0H9aKZqd8ns5X1gUm89Puds02rCOYrLHgmYPm8vxglvKa9XObsV/DZFxm17vA+43X9vCt6oMU9iWYOqPysPI+RX8jORPmIqze2xMflJ2GmQnbvfxUdWXZMHW2/rC5rYNKsmfB/IUFP7rAHumIbKwirHrhPGfmPKycsEUTDwexJ8M8hfnuPXiF80hbFzzh3d/KNsPU+4sfbOSlq++4P1gJYdNbpPyhLBdmK6z/j/MylOVr68rOTGfdPoe5CusyaOBp9p5E1JGwauu+vGFcYNWFzV6/iPUQDrMWlvcxIYk5CPMUFv3qR3dlcTB7Ya+c53VkzGA+wrLe3eX9NsNChCXdr1dbWQFMxjP4Tu3bysxmGl9zUKcH5soCYPI5x2+LXcL9wbyETZ430JTnDnMQ1vra+kbMeZijsH+6+H9mzsP8hOUfMTuqbCdMntGULE++L+Voz/J6ydbZPFttf4PXfz7G88Nvu3vImFWY/5G9B+Yi7GGOZTnuXbP7zw4tUtYLVlbYg/pZd5QlwNTMKQcL6vfTa/ZymLOw4Te+HFK2FFZc2HTTBufZy2E+whKn72CfP66t6xcWW1RH2jqHnLPsZ4Ww6sJ29hnPbxJvRNZW2IxyYT8wZrBywg4tjS/NnIepGeALa3qn7yz2VpiLsPqG4adZDzAfYXMGvn7MGQfzE7Zr4M/VlGWJ5/SB9TO7GsM+CLMS9mFq+gb2EFgdYce9uvF9woAKNhNW/3Qec8kWZiPsTEUfa8YMZi7Md9u9v1hjsHLCLvxk4Hd4hLauk+W2XxhPmKuwzbb1f1MWCysprOz7oz+y/mByfwVVK7Nud8I8hT3+wZk9ORdmIcwzf2K6sjyYm7AxR9wHKXsPsxbWZ8HMAvaeXzGPhDUcXtdbmR9MxnPuzi3sE7VglYX1fNuX8ewFMwibPn5xPGcxLEhYxoXFf7DGYPI5XX5eVExZBqy6sJFP58Vw7zBHYZGzr09h74H5yj1cfHqcvWcO3guEDSrXoxP3DvOW1ssmgfMWJp/zgXPdSGWRMA9hd2PNErl37X4v2w9OZk7AaghrfckqTVkmzCDrKHIT45IFCxbW13xRc2WvtXXzcrK+KDNBp/EXVjPLdRrrAVZC2MNmU0N57rD6wioccuSzxMIaCevyNWYj9wALkHVkN2yxsqswGU+n21M4G/Nh7jIukzsP5x6SjZ/TdkPISfYJmDwHq7WNV3N/MFlHif5/MD+DYDJferxpeI/1DrMU9vTSpxbsnzDZQ1zyojk7EmDlhZ08s6A281q75i/z3H5lzLQ9WFZ62pH9Eyb7i8+jA98xnrA=
*/