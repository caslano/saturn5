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
5DS7FHbcs3YiQ3ob8zcn22zpFLIK+tuOKKS92Z5JyUsetR4fr3ggQZ0ixAD8AQS5YBTBARxNO2uvBs0SEQlUEitA5CNCeZ7I1iDFmDJPvJXSRd5mumfvlVAn7W3olaPMfn8kUbK14Rw240x3Vl4sYC6AGjkkaVQNL7yvdlG2mVm22Rc4C2AXET8oMcDPVxy5WwjFVmgwPVXxKP0iv+8XfDDza78e7oiy+hdfPnUsw7Hv9e+Z9yywf4w/nVPfZwfaN0WudykYBe9vVelTjYf06g38TGDb+9W7FxlsOExYJ6jTTVhDc+qbdCk7N+pV+yofnTC5eN/SuKR6rztvb/NE4B7j9boAlmdpizP0zWLQnNw70iKto9Y/rs0y2R0UOqSSC7Ibf1c5BwSc8Vu8aY51emtbGZpap+3IM6sv0paxHv2bNjDeqWds4ZNpfHuUEwV4+3vk85XgJuMm2O2ynuzJG3tjrNtQgB61OscRtc1LdoyWzXN0uVEt9gkOUPi82LOiT1eT4Vm7qv+B0Fmo7VsjZ21nYHkb36rp3cZYU50Tkr8e32owUFOka04Az/DuL5b+oaonRBQnuHvFrBiqUF5lNgSK9819G8kI/OipT/lij6u8wmVdwOix1T3V4yScLSAC0qxtf70RD0F9oR0W6h6U33gNTNo13taV36B7Sd/NsSBP9o46U9ogf5vRLibctduxJaK0wUVhdQ28slS6
*/