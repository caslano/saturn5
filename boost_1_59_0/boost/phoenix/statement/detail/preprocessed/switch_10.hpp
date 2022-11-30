/*==============================================================================
    Copyright (c) 2005-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
    
    
    
    
    
    
    
            template <typename Context, typename Cond, typename Cases>
            result_type
            evaluate(
                Context const & ctx
              , Cond const & cond
              , Cases const & cases
              , mpl::int_<2>
              , mpl::false_
            ) const
            {
                typedef 
                    typename proto::result_of::flatten<Cases const&>::type
                    flat_view_type;
                typedef
                    typename fusion::result_of::begin<flat_view_type>::type
                    flat_view_begin;
                flat_view_type flat_view(proto::flatten(cases));
                typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 0 >::type >::type case0; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case0 , 0 >::type >::type >::type case_label0; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 1 >::type >::type case1; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case1 , 0 >::type >::type >::type case_label1;
                switch(boost::phoenix::eval(cond, ctx))
                {
                    case case_label0::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 0>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label1::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 1>(fusion::begin(flat_view)) ) ) , ctx ); break;
                }
            }
            template <typename Context, typename Cond, typename Cases>
            result_type
            evaluate(
                Context const & ctx
              , Cond const & cond
              , Cases const & cases
              , mpl::int_<2>
              , mpl::true_
            ) const
            {
                typedef 
                    typename proto::result_of::flatten<Cases const&>::type
                    flat_view_type;
                typedef
                    typename fusion::result_of::begin<flat_view_type>::type
                    flat_view_begin;
                flat_view_type flat_view(proto::flatten(cases));
                typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 0 >::type >::type case0; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case0 , 0 >::type >::type >::type case_label0;
                switch(boost::phoenix::eval(cond, ctx))
                {
                    case case_label0::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 0>(fusion::begin(flat_view)) ) ) , ctx ); break;
                    default:
                        boost::phoenix::eval(
                            proto::child_c<0>(
                                fusion::deref(
                                    fusion::advance_c<
                                        1
                                    >(fusion::begin(flat_view))
                                )
                            )
                            , ctx
                        );
                }
            }
    
    
    
    
    
    
    
            template <typename Context, typename Cond, typename Cases>
            result_type
            evaluate(
                Context const & ctx
              , Cond const & cond
              , Cases const & cases
              , mpl::int_<3>
              , mpl::false_
            ) const
            {
                typedef 
                    typename proto::result_of::flatten<Cases const&>::type
                    flat_view_type;
                typedef
                    typename fusion::result_of::begin<flat_view_type>::type
                    flat_view_begin;
                flat_view_type flat_view(proto::flatten(cases));
                typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 0 >::type >::type case0; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case0 , 0 >::type >::type >::type case_label0; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 1 >::type >::type case1; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case1 , 0 >::type >::type >::type case_label1; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 2 >::type >::type case2; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case2 , 0 >::type >::type >::type case_label2;
                switch(boost::phoenix::eval(cond, ctx))
                {
                    case case_label0::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 0>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label1::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 1>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label2::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 2>(fusion::begin(flat_view)) ) ) , ctx ); break;
                }
            }
            template <typename Context, typename Cond, typename Cases>
            result_type
            evaluate(
                Context const & ctx
              , Cond const & cond
              , Cases const & cases
              , mpl::int_<3>
              , mpl::true_
            ) const
            {
                typedef 
                    typename proto::result_of::flatten<Cases const&>::type
                    flat_view_type;
                typedef
                    typename fusion::result_of::begin<flat_view_type>::type
                    flat_view_begin;
                flat_view_type flat_view(proto::flatten(cases));
                typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 0 >::type >::type case0; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case0 , 0 >::type >::type >::type case_label0; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 1 >::type >::type case1; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case1 , 0 >::type >::type >::type case_label1;
                switch(boost::phoenix::eval(cond, ctx))
                {
                    case case_label0::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 0>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label1::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 1>(fusion::begin(flat_view)) ) ) , ctx ); break;
                    default:
                        boost::phoenix::eval(
                            proto::child_c<0>(
                                fusion::deref(
                                    fusion::advance_c<
                                        2
                                    >(fusion::begin(flat_view))
                                )
                            )
                            , ctx
                        );
                }
            }
    
    
    
    
    
    
    
            template <typename Context, typename Cond, typename Cases>
            result_type
            evaluate(
                Context const & ctx
              , Cond const & cond
              , Cases const & cases
              , mpl::int_<4>
              , mpl::false_
            ) const
            {
                typedef 
                    typename proto::result_of::flatten<Cases const&>::type
                    flat_view_type;
                typedef
                    typename fusion::result_of::begin<flat_view_type>::type
                    flat_view_begin;
                flat_view_type flat_view(proto::flatten(cases));
                typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 0 >::type >::type case0; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case0 , 0 >::type >::type >::type case_label0; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 1 >::type >::type case1; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case1 , 0 >::type >::type >::type case_label1; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 2 >::type >::type case2; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case2 , 0 >::type >::type >::type case_label2; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 3 >::type >::type case3; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case3 , 0 >::type >::type >::type case_label3;
                switch(boost::phoenix::eval(cond, ctx))
                {
                    case case_label0::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 0>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label1::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 1>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label2::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 2>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label3::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 3>(fusion::begin(flat_view)) ) ) , ctx ); break;
                }
            }
            template <typename Context, typename Cond, typename Cases>
            result_type
            evaluate(
                Context const & ctx
              , Cond const & cond
              , Cases const & cases
              , mpl::int_<4>
              , mpl::true_
            ) const
            {
                typedef 
                    typename proto::result_of::flatten<Cases const&>::type
                    flat_view_type;
                typedef
                    typename fusion::result_of::begin<flat_view_type>::type
                    flat_view_begin;
                flat_view_type flat_view(proto::flatten(cases));
                typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 0 >::type >::type case0; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case0 , 0 >::type >::type >::type case_label0; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 1 >::type >::type case1; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case1 , 0 >::type >::type >::type case_label1; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 2 >::type >::type case2; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case2 , 0 >::type >::type >::type case_label2;
                switch(boost::phoenix::eval(cond, ctx))
                {
                    case case_label0::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 0>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label1::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 1>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label2::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 2>(fusion::begin(flat_view)) ) ) , ctx ); break;
                    default:
                        boost::phoenix::eval(
                            proto::child_c<0>(
                                fusion::deref(
                                    fusion::advance_c<
                                        3
                                    >(fusion::begin(flat_view))
                                )
                            )
                            , ctx
                        );
                }
            }
    
    
    
    
    
    
    
            template <typename Context, typename Cond, typename Cases>
            result_type
            evaluate(
                Context const & ctx
              , Cond const & cond
              , Cases const & cases
              , mpl::int_<5>
              , mpl::false_
            ) const
            {
                typedef 
                    typename proto::result_of::flatten<Cases const&>::type
                    flat_view_type;
                typedef
                    typename fusion::result_of::begin<flat_view_type>::type
                    flat_view_begin;
                flat_view_type flat_view(proto::flatten(cases));
                typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 0 >::type >::type case0; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case0 , 0 >::type >::type >::type case_label0; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 1 >::type >::type case1; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case1 , 0 >::type >::type >::type case_label1; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 2 >::type >::type case2; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case2 , 0 >::type >::type >::type case_label2; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 3 >::type >::type case3; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case3 , 0 >::type >::type >::type case_label3; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 4 >::type >::type case4; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case4 , 0 >::type >::type >::type case_label4;
                switch(boost::phoenix::eval(cond, ctx))
                {
                    case case_label0::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 0>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label1::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 1>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label2::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 2>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label3::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 3>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label4::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 4>(fusion::begin(flat_view)) ) ) , ctx ); break;
                }
            }
            template <typename Context, typename Cond, typename Cases>
            result_type
            evaluate(
                Context const & ctx
              , Cond const & cond
              , Cases const & cases
              , mpl::int_<5>
              , mpl::true_
            ) const
            {
                typedef 
                    typename proto::result_of::flatten<Cases const&>::type
                    flat_view_type;
                typedef
                    typename fusion::result_of::begin<flat_view_type>::type
                    flat_view_begin;
                flat_view_type flat_view(proto::flatten(cases));
                typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 0 >::type >::type case0; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case0 , 0 >::type >::type >::type case_label0; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 1 >::type >::type case1; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case1 , 0 >::type >::type >::type case_label1; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 2 >::type >::type case2; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case2 , 0 >::type >::type >::type case_label2; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 3 >::type >::type case3; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case3 , 0 >::type >::type >::type case_label3;
                switch(boost::phoenix::eval(cond, ctx))
                {
                    case case_label0::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 0>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label1::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 1>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label2::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 2>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label3::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 3>(fusion::begin(flat_view)) ) ) , ctx ); break;
                    default:
                        boost::phoenix::eval(
                            proto::child_c<0>(
                                fusion::deref(
                                    fusion::advance_c<
                                        4
                                    >(fusion::begin(flat_view))
                                )
                            )
                            , ctx
                        );
                }
            }
    
    
    
    
    
    
    
            template <typename Context, typename Cond, typename Cases>
            result_type
            evaluate(
                Context const & ctx
              , Cond const & cond
              , Cases const & cases
              , mpl::int_<6>
              , mpl::false_
            ) const
            {
                typedef 
                    typename proto::result_of::flatten<Cases const&>::type
                    flat_view_type;
                typedef
                    typename fusion::result_of::begin<flat_view_type>::type
                    flat_view_begin;
                flat_view_type flat_view(proto::flatten(cases));
                typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 0 >::type >::type case0; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case0 , 0 >::type >::type >::type case_label0; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 1 >::type >::type case1; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case1 , 0 >::type >::type >::type case_label1; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 2 >::type >::type case2; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case2 , 0 >::type >::type >::type case_label2; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 3 >::type >::type case3; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case3 , 0 >::type >::type >::type case_label3; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 4 >::type >::type case4; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case4 , 0 >::type >::type >::type case_label4; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 5 >::type >::type case5; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case5 , 0 >::type >::type >::type case_label5;
                switch(boost::phoenix::eval(cond, ctx))
                {
                    case case_label0::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 0>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label1::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 1>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label2::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 2>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label3::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 3>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label4::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 4>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label5::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 5>(fusion::begin(flat_view)) ) ) , ctx ); break;
                }
            }
            template <typename Context, typename Cond, typename Cases>
            result_type
            evaluate(
                Context const & ctx
              , Cond const & cond
              , Cases const & cases
              , mpl::int_<6>
              , mpl::true_
            ) const
            {
                typedef 
                    typename proto::result_of::flatten<Cases const&>::type
                    flat_view_type;
                typedef
                    typename fusion::result_of::begin<flat_view_type>::type
                    flat_view_begin;
                flat_view_type flat_view(proto::flatten(cases));
                typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 0 >::type >::type case0; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case0 , 0 >::type >::type >::type case_label0; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 1 >::type >::type case1; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case1 , 0 >::type >::type >::type case_label1; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 2 >::type >::type case2; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case2 , 0 >::type >::type >::type case_label2; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 3 >::type >::type case3; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case3 , 0 >::type >::type >::type case_label3; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 4 >::type >::type case4; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case4 , 0 >::type >::type >::type case_label4;
                switch(boost::phoenix::eval(cond, ctx))
                {
                    case case_label0::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 0>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label1::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 1>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label2::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 2>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label3::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 3>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label4::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 4>(fusion::begin(flat_view)) ) ) , ctx ); break;
                    default:
                        boost::phoenix::eval(
                            proto::child_c<0>(
                                fusion::deref(
                                    fusion::advance_c<
                                        5
                                    >(fusion::begin(flat_view))
                                )
                            )
                            , ctx
                        );
                }
            }
    
    
    
    
    
    
    
            template <typename Context, typename Cond, typename Cases>
            result_type
            evaluate(
                Context const & ctx
              , Cond const & cond
              , Cases const & cases
              , mpl::int_<7>
              , mpl::false_
            ) const
            {
                typedef 
                    typename proto::result_of::flatten<Cases const&>::type
                    flat_view_type;
                typedef
                    typename fusion::result_of::begin<flat_view_type>::type
                    flat_view_begin;
                flat_view_type flat_view(proto::flatten(cases));
                typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 0 >::type >::type case0; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case0 , 0 >::type >::type >::type case_label0; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 1 >::type >::type case1; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case1 , 0 >::type >::type >::type case_label1; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 2 >::type >::type case2; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case2 , 0 >::type >::type >::type case_label2; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 3 >::type >::type case3; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case3 , 0 >::type >::type >::type case_label3; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 4 >::type >::type case4; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case4 , 0 >::type >::type >::type case_label4; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 5 >::type >::type case5; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case5 , 0 >::type >::type >::type case_label5; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 6 >::type >::type case6; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case6 , 0 >::type >::type >::type case_label6;
                switch(boost::phoenix::eval(cond, ctx))
                {
                    case case_label0::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 0>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label1::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 1>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label2::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 2>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label3::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 3>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label4::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 4>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label5::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 5>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label6::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 6>(fusion::begin(flat_view)) ) ) , ctx ); break;
                }
            }
            template <typename Context, typename Cond, typename Cases>
            result_type
            evaluate(
                Context const & ctx
              , Cond const & cond
              , Cases const & cases
              , mpl::int_<7>
              , mpl::true_
            ) const
            {
                typedef 
                    typename proto::result_of::flatten<Cases const&>::type
                    flat_view_type;
                typedef
                    typename fusion::result_of::begin<flat_view_type>::type
                    flat_view_begin;
                flat_view_type flat_view(proto::flatten(cases));
                typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 0 >::type >::type case0; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case0 , 0 >::type >::type >::type case_label0; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 1 >::type >::type case1; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case1 , 0 >::type >::type >::type case_label1; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 2 >::type >::type case2; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case2 , 0 >::type >::type >::type case_label2; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 3 >::type >::type case3; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case3 , 0 >::type >::type >::type case_label3; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 4 >::type >::type case4; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case4 , 0 >::type >::type >::type case_label4; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 5 >::type >::type case5; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case5 , 0 >::type >::type >::type case_label5;
                switch(boost::phoenix::eval(cond, ctx))
                {
                    case case_label0::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 0>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label1::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 1>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label2::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 2>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label3::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 3>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label4::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 4>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label5::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 5>(fusion::begin(flat_view)) ) ) , ctx ); break;
                    default:
                        boost::phoenix::eval(
                            proto::child_c<0>(
                                fusion::deref(
                                    fusion::advance_c<
                                        6
                                    >(fusion::begin(flat_view))
                                )
                            )
                            , ctx
                        );
                }
            }
    
    
    
    
    
    
    
            template <typename Context, typename Cond, typename Cases>
            result_type
            evaluate(
                Context const & ctx
              , Cond const & cond
              , Cases const & cases
              , mpl::int_<8>
              , mpl::false_
            ) const
            {
                typedef 
                    typename proto::result_of::flatten<Cases const&>::type
                    flat_view_type;
                typedef
                    typename fusion::result_of::begin<flat_view_type>::type
                    flat_view_begin;
                flat_view_type flat_view(proto::flatten(cases));
                typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 0 >::type >::type case0; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case0 , 0 >::type >::type >::type case_label0; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 1 >::type >::type case1; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case1 , 0 >::type >::type >::type case_label1; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 2 >::type >::type case2; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case2 , 0 >::type >::type >::type case_label2; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 3 >::type >::type case3; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case3 , 0 >::type >::type >::type case_label3; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 4 >::type >::type case4; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case4 , 0 >::type >::type >::type case_label4; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 5 >::type >::type case5; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case5 , 0 >::type >::type >::type case_label5; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 6 >::type >::type case6; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case6 , 0 >::type >::type >::type case_label6; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 7 >::type >::type case7; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case7 , 0 >::type >::type >::type case_label7;
                switch(boost::phoenix::eval(cond, ctx))
                {
                    case case_label0::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 0>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label1::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 1>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label2::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 2>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label3::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 3>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label4::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 4>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label5::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 5>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label6::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 6>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label7::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 7>(fusion::begin(flat_view)) ) ) , ctx ); break;
                }
            }
            template <typename Context, typename Cond, typename Cases>
            result_type
            evaluate(
                Context const & ctx
              , Cond const & cond
              , Cases const & cases
              , mpl::int_<8>
              , mpl::true_
            ) const
            {
                typedef 
                    typename proto::result_of::flatten<Cases const&>::type
                    flat_view_type;
                typedef
                    typename fusion::result_of::begin<flat_view_type>::type
                    flat_view_begin;
                flat_view_type flat_view(proto::flatten(cases));
                typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 0 >::type >::type case0; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case0 , 0 >::type >::type >::type case_label0; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 1 >::type >::type case1; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case1 , 0 >::type >::type >::type case_label1; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 2 >::type >::type case2; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case2 , 0 >::type >::type >::type case_label2; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 3 >::type >::type case3; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case3 , 0 >::type >::type >::type case_label3; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 4 >::type >::type case4; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case4 , 0 >::type >::type >::type case_label4; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 5 >::type >::type case5; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case5 , 0 >::type >::type >::type case_label5; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 6 >::type >::type case6; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case6 , 0 >::type >::type >::type case_label6;
                switch(boost::phoenix::eval(cond, ctx))
                {
                    case case_label0::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 0>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label1::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 1>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label2::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 2>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label3::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 3>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label4::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 4>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label5::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 5>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label6::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 6>(fusion::begin(flat_view)) ) ) , ctx ); break;
                    default:
                        boost::phoenix::eval(
                            proto::child_c<0>(
                                fusion::deref(
                                    fusion::advance_c<
                                        7
                                    >(fusion::begin(flat_view))
                                )
                            )
                            , ctx
                        );
                }
            }
    
    
    
    
    
    
    
            template <typename Context, typename Cond, typename Cases>
            result_type
            evaluate(
                Context const & ctx
              , Cond const & cond
              , Cases const & cases
              , mpl::int_<9>
              , mpl::false_
            ) const
            {
                typedef 
                    typename proto::result_of::flatten<Cases const&>::type
                    flat_view_type;
                typedef
                    typename fusion::result_of::begin<flat_view_type>::type
                    flat_view_begin;
                flat_view_type flat_view(proto::flatten(cases));
                typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 0 >::type >::type case0; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case0 , 0 >::type >::type >::type case_label0; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 1 >::type >::type case1; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case1 , 0 >::type >::type >::type case_label1; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 2 >::type >::type case2; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case2 , 0 >::type >::type >::type case_label2; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 3 >::type >::type case3; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case3 , 0 >::type >::type >::type case_label3; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 4 >::type >::type case4; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case4 , 0 >::type >::type >::type case_label4; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 5 >::type >::type case5; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case5 , 0 >::type >::type >::type case_label5; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 6 >::type >::type case6; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case6 , 0 >::type >::type >::type case_label6; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 7 >::type >::type case7; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case7 , 0 >::type >::type >::type case_label7; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 8 >::type >::type case8; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case8 , 0 >::type >::type >::type case_label8;
                switch(boost::phoenix::eval(cond, ctx))
                {
                    case case_label0::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 0>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label1::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 1>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label2::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 2>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label3::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 3>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label4::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 4>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label5::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 5>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label6::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 6>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label7::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 7>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label8::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 8>(fusion::begin(flat_view)) ) ) , ctx ); break;
                }
            }
            template <typename Context, typename Cond, typename Cases>
            result_type
            evaluate(
                Context const & ctx
              , Cond const & cond
              , Cases const & cases
              , mpl::int_<9>
              , mpl::true_
            ) const
            {
                typedef 
                    typename proto::result_of::flatten<Cases const&>::type
                    flat_view_type;
                typedef
                    typename fusion::result_of::begin<flat_view_type>::type
                    flat_view_begin;
                flat_view_type flat_view(proto::flatten(cases));
                typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 0 >::type >::type case0; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case0 , 0 >::type >::type >::type case_label0; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 1 >::type >::type case1; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case1 , 0 >::type >::type >::type case_label1; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 2 >::type >::type case2; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case2 , 0 >::type >::type >::type case_label2; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 3 >::type >::type case3; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case3 , 0 >::type >::type >::type case_label3; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 4 >::type >::type case4; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case4 , 0 >::type >::type >::type case_label4; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 5 >::type >::type case5; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case5 , 0 >::type >::type >::type case_label5; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 6 >::type >::type case6; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case6 , 0 >::type >::type >::type case_label6; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 7 >::type >::type case7; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case7 , 0 >::type >::type >::type case_label7;
                switch(boost::phoenix::eval(cond, ctx))
                {
                    case case_label0::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 0>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label1::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 1>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label2::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 2>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label3::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 3>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label4::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 4>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label5::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 5>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label6::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 6>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label7::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 7>(fusion::begin(flat_view)) ) ) , ctx ); break;
                    default:
                        boost::phoenix::eval(
                            proto::child_c<0>(
                                fusion::deref(
                                    fusion::advance_c<
                                        8
                                    >(fusion::begin(flat_view))
                                )
                            )
                            , ctx
                        );
                }
            }
    
    
    
    
    
    
    
            template <typename Context, typename Cond, typename Cases>
            result_type
            evaluate(
                Context const & ctx
              , Cond const & cond
              , Cases const & cases
              , mpl::int_<10>
              , mpl::false_
            ) const
            {
                typedef 
                    typename proto::result_of::flatten<Cases const&>::type
                    flat_view_type;
                typedef
                    typename fusion::result_of::begin<flat_view_type>::type
                    flat_view_begin;
                flat_view_type flat_view(proto::flatten(cases));
                typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 0 >::type >::type case0; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case0 , 0 >::type >::type >::type case_label0; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 1 >::type >::type case1; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case1 , 0 >::type >::type >::type case_label1; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 2 >::type >::type case2; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case2 , 0 >::type >::type >::type case_label2; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 3 >::type >::type case3; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case3 , 0 >::type >::type >::type case_label3; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 4 >::type >::type case4; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case4 , 0 >::type >::type >::type case_label4; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 5 >::type >::type case5; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case5 , 0 >::type >::type >::type case_label5; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 6 >::type >::type case6; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case6 , 0 >::type >::type >::type case_label6; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 7 >::type >::type case7; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case7 , 0 >::type >::type >::type case_label7; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 8 >::type >::type case8; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case8 , 0 >::type >::type >::type case_label8; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 9 >::type >::type case9; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case9 , 0 >::type >::type >::type case_label9;
                switch(boost::phoenix::eval(cond, ctx))
                {
                    case case_label0::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 0>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label1::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 1>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label2::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 2>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label3::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 3>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label4::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 4>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label5::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 5>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label6::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 6>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label7::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 7>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label8::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 8>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label9::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 9>(fusion::begin(flat_view)) ) ) , ctx ); break;
                }
            }
            template <typename Context, typename Cond, typename Cases>
            result_type
            evaluate(
                Context const & ctx
              , Cond const & cond
              , Cases const & cases
              , mpl::int_<10>
              , mpl::true_
            ) const
            {
                typedef 
                    typename proto::result_of::flatten<Cases const&>::type
                    flat_view_type;
                typedef
                    typename fusion::result_of::begin<flat_view_type>::type
                    flat_view_begin;
                flat_view_type flat_view(proto::flatten(cases));
                typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 0 >::type >::type case0; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case0 , 0 >::type >::type >::type case_label0; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 1 >::type >::type case1; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case1 , 0 >::type >::type >::type case_label1; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 2 >::type >::type case2; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case2 , 0 >::type >::type >::type case_label2; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 3 >::type >::type case3; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case3 , 0 >::type >::type >::type case_label3; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 4 >::type >::type case4; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case4 , 0 >::type >::type >::type case_label4; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 5 >::type >::type case5; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case5 , 0 >::type >::type >::type case_label5; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 6 >::type >::type case6; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case6 , 0 >::type >::type >::type case_label6; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 7 >::type >::type case7; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case7 , 0 >::type >::type >::type case_label7; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 8 >::type >::type case8; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case8 , 0 >::type >::type >::type case_label8;
                switch(boost::phoenix::eval(cond, ctx))
                {
                    case case_label0::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 0>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label1::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 1>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label2::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 2>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label3::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 3>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label4::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 4>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label5::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 5>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label6::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 6>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label7::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 7>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label8::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 8>(fusion::begin(flat_view)) ) ) , ctx ); break;
                    default:
                        boost::phoenix::eval(
                            proto::child_c<0>(
                                fusion::deref(
                                    fusion::advance_c<
                                        9
                                    >(fusion::begin(flat_view))
                                )
                            )
                            , ctx
                        );
                }
            }

/* switch_10.hpp
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
*/