/*=============================================================================
    Copyright (c) 2001-2007 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
    
    
    
    
    
    
    
    template <typename Dummy>
    struct function_ptr_impl<2, Dummy>
    {
        template <typename RT, typename FP>
        struct impl
        {
            typedef RT result_type;
            impl(FP fp_)
                : fp(fp_) {}
            template <typename A0 , typename A1>
            RT operator()(A0 & a0 , A1 & a1) const
            {
                return fp(a0 , a1);
            }
            FP fp;
        };
    };
    
    
    
    
    
    
    
    template <typename Dummy>
    struct function_ptr_impl<3, Dummy>
    {
        template <typename RT, typename FP>
        struct impl
        {
            typedef RT result_type;
            impl(FP fp_)
                : fp(fp_) {}
            template <typename A0 , typename A1 , typename A2>
            RT operator()(A0 & a0 , A1 & a1 , A2 & a2) const
            {
                return fp(a0 , a1 , a2);
            }
            FP fp;
        };
    };
    
    
    
    
    
    
    
    template <typename Dummy>
    struct function_ptr_impl<4, Dummy>
    {
        template <typename RT, typename FP>
        struct impl
        {
            typedef RT result_type;
            impl(FP fp_)
                : fp(fp_) {}
            template <typename A0 , typename A1 , typename A2 , typename A3>
            RT operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3) const
            {
                return fp(a0 , a1 , a2 , a3);
            }
            FP fp;
        };
    };
    
    
    
    
    
    
    
    template <typename Dummy>
    struct function_ptr_impl<5, Dummy>
    {
        template <typename RT, typename FP>
        struct impl
        {
            typedef RT result_type;
            impl(FP fp_)
                : fp(fp_) {}
            template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4>
            RT operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4) const
            {
                return fp(a0 , a1 , a2 , a3 , a4);
            }
            FP fp;
        };
    };
    
    
    
    
    
    
    
    template <typename Dummy>
    struct function_ptr_impl<6, Dummy>
    {
        template <typename RT, typename FP>
        struct impl
        {
            typedef RT result_type;
            impl(FP fp_)
                : fp(fp_) {}
            template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5>
            RT operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5) const
            {
                return fp(a0 , a1 , a2 , a3 , a4 , a5);
            }
            FP fp;
        };
    };
    
    
    
    
    
    
    
    template <typename Dummy>
    struct function_ptr_impl<7, Dummy>
    {
        template <typename RT, typename FP>
        struct impl
        {
            typedef RT result_type;
            impl(FP fp_)
                : fp(fp_) {}
            template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6>
            RT operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6) const
            {
                return fp(a0 , a1 , a2 , a3 , a4 , a5 , a6);
            }
            FP fp;
        };
    };
    
    
    
    
    
    
    
    template <typename Dummy>
    struct function_ptr_impl<8, Dummy>
    {
        template <typename RT, typename FP>
        struct impl
        {
            typedef RT result_type;
            impl(FP fp_)
                : fp(fp_) {}
            template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7>
            RT operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7) const
            {
                return fp(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7);
            }
            FP fp;
        };
    };
    
    
    
    
    
    
    
    template <typename Dummy>
    struct function_ptr_impl<9, Dummy>
    {
        template <typename RT, typename FP>
        struct impl
        {
            typedef RT result_type;
            impl(FP fp_)
                : fp(fp_) {}
            template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8>
            RT operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8) const
            {
                return fp(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8);
            }
            FP fp;
        };
    };
    
    
    
    
    
    
    
    template <typename Dummy>
    struct function_ptr_impl<10, Dummy>
    {
        template <typename RT, typename FP>
        struct impl
        {
            typedef RT result_type;
            impl(FP fp_)
                : fp(fp_) {}
            template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9>
            RT operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9) const
            {
                return fp(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9);
            }
            FP fp;
        };
    };

/* function_ptr_10.hpp
zwjugaLdpmnYeUqakrv5VyaNJCve7YqO3aqUe1rR7qhpcLguaUrubotGch+h9OxvG/rqqUXZtVTTD1f7fUxR7ZbW369+0cJLoGRLpVa1r5Xvcxye06E5+0OFw9u6QTMFnLo7f0+RP7wU4Rmndyn03ahmenfz43vY80KZ3S7yC5WNzgvIO58X8mpeMOcZP5OuFQpeph7W4ycG7gSi310dcuecENPQNru72/NLPpfxi5lqvJhJ2wayYOYBxwK5UsWvlsJ8PLPhf7TbXmF50Hdj70k+Yg8dXvt/gDcV3xWD73Bz7f8xPvZu7vfYO6Bz8VCp7O8/4m80Gvub7x9uCjo6H//Ev/0a32RHxzfSwy/xMYqXrJgvV4R+2Wg/2/BDsSmO3phNmXE/x6KYM22ScWA8js5kEKa/JYqBW83ntgc98kOxNYrpjigfs9ui9OXhKZ3GN6N0+fCf9hY3tydheH5Jv78dwyUNSfLZee1eDLfuUNd5vHUfw2MIT8Hp26PkujJoPsesq0v31hjokFMEIgzuXJsYNDuhNObKfU0MuouFeaC6lwhM/JSi3qu9wfQ5B31kucfVszup9WFwneK2KP987hpyjjCQ3odSqRDkQ+yFtIbInam11uh5+9UGTu57umqO+4SrH/E3qamGyscVd51iIU6dterma1KW/aOxQnaMyWeK942sVpVv3OVmX8/9lw269oEINxyn2wNLyVD4b54jvPYA4zIY9zdPniG8hCnQ4KFqnn+dzr+ksXe7q1Db2vDQh3m2Tdj00630AWaJ9rvN82qPQ9grJyJYWXwpFlh9z/QtHMvMHPLhqN5brypMOoKBVICGbWPNi2Kgp7DycLPGSMcter95b0aP1KGiX30v0Vs93U11vU5esuirKxpBdqj0e+x1mvUsqU+tPEjl473u2s9GCwwZLf5QdqRwEx9Xa/lULE639zui/UkVTpftrYQxCx+o8bvXjvmT9au5eqW8sZjhQtbRaSOG2zdNeTOlbJgvFYo4evcXjqpD/qMK+30T+6hqWC6XqzjFCOvzCkzYqxY2rJUrXljKwXyd8SLY61YevBzAxWI6PEZZIOxNS245i6OUAHJz7N6/ym+gzkadusJOplIIM4VkfYHNTixRr8aDvzzKP84SLyufBfdwfLRVPT+XK/jx8la4oLoQpAKiHVeyQkdWsVSu1LP1BFmjNWX1LV0PZ/blIn8FHC8LneDoY5g07LzPQDUCMZ06HqizKksWC6BZqudy+WJCnbViqixMS7vpXbH27WdtIO0+mH1h7SDagk2bNu0NN3nY7MiUQ76INhPdnm5o3d85ZmPs6cbwOzzOcMl61cO3xNGZCQoyyAZqYVy96uI2oifpVd/ZTpgkveoNO2yMq1fdcjub7upVM7cnepJetbAzCSPLrGx9d2A4d6qi/ejzdxHdnu7IxrVvN8OYTzlJ/mv3Mlpkitbt+7F7Ez067UIO6UXAucsF5fP6/YhuLxdkl9z7AI3B2kuyTzxIf6cqID9J8N2i6JLGHEcLJ3nPaXZGyCj11z8+gmGTlhHKy6cOaRzyQt/DI+q7qEntt/dNtO5mj+Xz/pxavwlzM4rBYOEZ1ZgrEYwadKT3Td7ivklhWpfUbgz98KaLE6YzCSRc+s2Ek4lZEpU+8+IozpFIvkdv3N1ZQwt+reIXs//tGqp9KfJnYFb1WnPVyU1Ed6pNY3ZvJoxd/dQ/To4xTFJVEG77uI2zq4LydY3jqAkk3fI9fnGLjbFSNG17W22cnSLZlvJkK+WVJM2Zd1L2jh8TnaVE/cD1W2LVEO0nJl9K/UB5NNHnlkSTxTg/ag9pPzHxRqI7PlGa+ty1wTEeAp0amVFNTu+cRnc=
*/