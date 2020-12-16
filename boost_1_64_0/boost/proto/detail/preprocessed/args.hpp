    ///////////////////////////////////////////////////////////////////////////////
    /// \file args.hpp
    /// Contains definition of \c term\<\>, \c list1\<\>, \c list2\<\>, ...
    /// class templates.
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
    
    
    
    
    template< typename Arg0 >
    struct term
    {
        static const long arity = 0;
        typedef Arg0 child0;
        typedef mpl::void_ child1; typedef mpl::void_ child2; typedef mpl::void_ child3; typedef mpl::void_ child4; typedef mpl::void_ child5; typedef mpl::void_ child6; typedef mpl::void_ child7; typedef mpl::void_ child8; typedef mpl::void_ child9;
        
        
        typedef Arg0 back_;
    };
    
    
    
    
    template< typename Arg0 >
    struct list1
    {
        static const long arity = 1;
        typedef Arg0 child0;
        typedef mpl::void_ child1; typedef mpl::void_ child2; typedef mpl::void_ child3; typedef mpl::void_ child4; typedef mpl::void_ child5; typedef mpl::void_ child6; typedef mpl::void_ child7; typedef mpl::void_ child8; typedef mpl::void_ child9;
        
        
        typedef Arg0 back_;
    };
    
    
    
    
    template< typename Arg0 , typename Arg1 >
    struct list2
    {
        static const long arity = 2;
        typedef Arg0 child0; typedef Arg1 child1;
        typedef mpl::void_ child2; typedef mpl::void_ child3; typedef mpl::void_ child4; typedef mpl::void_ child5; typedef mpl::void_ child6; typedef mpl::void_ child7; typedef mpl::void_ child8; typedef mpl::void_ child9;
        
        
        typedef Arg1 back_;
    };
    
    
    
    
    template< typename Arg0 , typename Arg1 , typename Arg2 >
    struct list3
    {
        static const long arity = 3;
        typedef Arg0 child0; typedef Arg1 child1; typedef Arg2 child2;
        typedef mpl::void_ child3; typedef mpl::void_ child4; typedef mpl::void_ child5; typedef mpl::void_ child6; typedef mpl::void_ child7; typedef mpl::void_ child8; typedef mpl::void_ child9;
        
        
        typedef Arg2 back_;
    };
    
    
    
    
    template< typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 >
    struct list4
    {
        static const long arity = 4;
        typedef Arg0 child0; typedef Arg1 child1; typedef Arg2 child2; typedef Arg3 child3;
        typedef mpl::void_ child4; typedef mpl::void_ child5; typedef mpl::void_ child6; typedef mpl::void_ child7; typedef mpl::void_ child8; typedef mpl::void_ child9;
        
        
        typedef Arg3 back_;
    };
    
    
    
    
    template< typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 >
    struct list5
    {
        static const long arity = 5;
        typedef Arg0 child0; typedef Arg1 child1; typedef Arg2 child2; typedef Arg3 child3; typedef Arg4 child4;
        typedef mpl::void_ child5; typedef mpl::void_ child6; typedef mpl::void_ child7; typedef mpl::void_ child8; typedef mpl::void_ child9;
        
        
        typedef Arg4 back_;
    };
    
    
    
    
    template< typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 >
    struct list6
    {
        static const long arity = 6;
        typedef Arg0 child0; typedef Arg1 child1; typedef Arg2 child2; typedef Arg3 child3; typedef Arg4 child4; typedef Arg5 child5;
        typedef mpl::void_ child6; typedef mpl::void_ child7; typedef mpl::void_ child8; typedef mpl::void_ child9;
        
        
        typedef Arg5 back_;
    };
    
    
    
    
    template< typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 >
    struct list7
    {
        static const long arity = 7;
        typedef Arg0 child0; typedef Arg1 child1; typedef Arg2 child2; typedef Arg3 child3; typedef Arg4 child4; typedef Arg5 child5; typedef Arg6 child6;
        typedef mpl::void_ child7; typedef mpl::void_ child8; typedef mpl::void_ child9;
        
        
        typedef Arg6 back_;
    };
    
    
    
    
    template< typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7 >
    struct list8
    {
        static const long arity = 8;
        typedef Arg0 child0; typedef Arg1 child1; typedef Arg2 child2; typedef Arg3 child3; typedef Arg4 child4; typedef Arg5 child5; typedef Arg6 child6; typedef Arg7 child7;
        typedef mpl::void_ child8; typedef mpl::void_ child9;
        
        
        typedef Arg7 back_;
    };
    
    
    
    
    template< typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7 , typename Arg8 >
    struct list9
    {
        static const long arity = 9;
        typedef Arg0 child0; typedef Arg1 child1; typedef Arg2 child2; typedef Arg3 child3; typedef Arg4 child4; typedef Arg5 child5; typedef Arg6 child6; typedef Arg7 child7; typedef Arg8 child8;
        typedef mpl::void_ child9;
        
        
        typedef Arg8 back_;
    };
    
    
    
    
    template< typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7 , typename Arg8 , typename Arg9 >
    struct list10
    {
        static const long arity = 10;
        typedef Arg0 child0; typedef Arg1 child1; typedef Arg2 child2; typedef Arg3 child3; typedef Arg4 child4; typedef Arg5 child5; typedef Arg6 child6; typedef Arg7 child7; typedef Arg8 child8; typedef Arg9 child9;
        
        
        
        typedef Arg9 back_;
    };

/* args.hpp
vHRZBuBvCZ4/dog1pdAG5zPKbG5eJTlzBHzAYDlacbu+xh00LH5m5g2JU6feqD4v8P0uPJPy5s1avE59C8zf+Qxc6J1PJZKppf43ecezolhjX0gfU+Zis3V1hSZZVenWWnDZHXUQZ1VcjJrKFtR3GtaZo268RLtdOh/1dQuHOTwOm68pO412ef28FP4CoSd/YzSguEIn3qWxW12HwQJdtbopziDegeHkfZDOwjn8IobHAMz53J9Jp47h/bVErw3eB9rqOgXo1s6J79JJ5ER2CRSTguDfDTz2TYrjjUD64A8I+V2VTTh4o7CPWWFFdRf0cf2wJISBPqTW5bH7mT4PP4IfZpLzOVFXq9DXRRrXqJ5Ud4Wyl0XYl2UY1kuR0mpQ/WFiazx/0O+Yi7VX9n//Jv7OPpyMEQhNWyx1IYZYQjyG6vSCnP/Mz0oLbnj132Lr0nxZ/pD5XYbHZ8A2uH+0VizjnlCN0dJaVeH0HTrxQRmvVH5br9au0pShcqoy1Sb2rzINuqprsc+hvijlylKo/1TBTeJGPyy5XsMim1Qf3w7JazbiKowL2omKJPfmJ6z6UJtnVfIKDBzob2KO9st9e60Bb25R/T405EGv6pHmp1gltUh/1EJz0Jj8rLFeWi11uqAWUPaTpKcyxiR2EJyhoyLJ+KHoy+L7UaI++xPRZ2GhA8EU9y6ekW+Uao3ZpUIe20rFpbP1edqfb9aKJdWf6PeC+P0d4vdX8e9lg0+K34GfIjuPX8i1JfXCRkldCeeuA//fVXdHYE3w4mdRnjBLIIN+pzxBluj3lzyL8oRZkr8n+Xfkp9Tvk8+iPG0lS6gj+/zT1V4mlqWGXrEsegn4lcPwHIY3O2p8rjUNBJj4jHVGy2i1JAL7EHVG/NJnxX0xzpVaKzbrVeytT+yHbcOwtV4NfkedMqRdzKXnTsbfpueivbTay76JyodK/bgDwIclEtzFHcC5eS5BX4ZvaJ/7B3Ci7BIiWU/eRQyVTVBCp/2RmLO6I7QZ2ZRzP2oVS+L30+L3d4jfz/DvXYOviN+Bhz5x2u5b9Hugb73Z7lv0u9G3JE/5h2ya/Gn+XfKUf8imyVf4d+TZNk6OJ+q0cgoW7KVvuSzsq6D26ZbBM619Q/GcOQ+SHshk7Lka7OeROY1MaIbm/c+K9W0kalX5GqA+Q/Pbep+FVPGLGVWdPJWcfJe9jJnvMn3Dp/A71M9G1AC90JlnQS76dkHw3YTlIIwfNR5XVNihfp42Spu1DXUHs4VacXo3VJUVdWPUZuEmQ7Yn2izcZDifwKHBr2O5tY4uNnzfOsBHz1FMReXxVsygX4r+wqPUFe3x4j73Ex9XVKsBpdkReDTVT/vOYLkyS7GOZfVZrGPJ0jI9/9KpOGxdhyUX8xhIdkZvVWEYNJfOpCgM9cF1CkPzJVa2qeBwmv11fwPmgnRW2cVkZ1PIx+1tZ4NkvU2FYatQc+DyG/Lxdo63GJ9MJDL9yKp8kBbUV3/QrDSb9XjefqeKozJVSB/DefwQnIUee0MhBfmjeZ1GTr+879blyadmISXOpEiHkkG55yEOJqRk4Fz9CfV9eHMUu1xvVcnPiDj7uLIdwgcsCcXeNbdDsObiDfai9H4kM+GlG+z96awb+K0uZXW+uyMUL7A8FfqJid2CtZedYm8/MwocZlX+fmsP/F7q4s9S/2KsE7u9FfAx585OU1vgZbYU2tdLDNerSR3AW6KhWWH+4GOAH54VftNbfovwotQaqFfUIVCsQZffrQlDR9BJ9mGywpyQZ0YHrTOqhXiWmY9X26+f0XZgP8e66wr7sh7V68gnZb2G1+ozR6heqTzh4sAYA04daIAtPozLWP9wXY2x2VI=
*/