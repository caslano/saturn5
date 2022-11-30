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
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
*/