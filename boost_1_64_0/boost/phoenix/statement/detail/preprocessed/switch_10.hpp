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
v5Sb5/aYfprKc2B8sJQMZD9gKTflNKYbNAtGKa+/9tjCyXa/Jcvld41lOWiXywW7fcty7feA9A2Ma2Dbhpdec96Gl5nbcJn2nDKtpg6ayHbJtPbtsabvias+IK76ULjq4+Cqb4WrPhSu+gi46jPiqu+Dqz4prvp0uOpb4aoPhas+Jq761LjqO1P1PiDO+2K46gvjqk+Qq745rvp0uOoz4qqPkqs+R677mDxp6jOyYeLo58tv6/Nwbr1JnzybWfSWq75OrvoEuepD5LpvziVTXxI5rpbjbQN5bKo+Z036oMvzs7EZ9sU22A9vx/4YiAOxDw7CcTgYp+AQjMMQPIzD8QiOxFIchT/gaGxE+ndiExyDgzAUg3Es6nAcxuJ4XIlhuAon4lachM/iZHwep+JrGI75OM38XDt3Od6U408DoXz3d5b97KnynMRw7Ip3Y2+MwME4HUfjDJyE0Xgv6jAOY3E2xuM8nIn3YyKuxmTchAZ8ClNxBxrxZZyD+ZiBh3E+HsWF+CEuwlOYiZ/jUvwKl+FFfADLMQuv4EqsRtlWYR1cg16Yjb64HlvgBmyLj2BnzMGe+Bj2wc1o6iPiIcctcjyj1N9ypY+IfCkkyHPbFmArvA974iIcjotxKi7BBFyG6bgcl+AD+Chm4Qu4EgvxITyNq7EM12IFZmNtMrMOO+F67IGbMARzcBI+ikn4GM7BP+ECfBxX4xP4GD6JWzAXD+BTeBSfxgu4FS/iDryKO9GLOngeO+AL2Bd34UDMw1H4Is7A3ZiOL+ND+Ao+jXvxVXwNi3AfluDrWJ12JR9r4370xQPYAd/AnliAA/EgDsFDGIaHcSIWYiK+ien4Fs7Hd3AVHsVH8V18Go/hfnwP38H38Twex1I8ib/hKbyNZf8JtsdPsQ+ewcH4GY7DEpyBZ3Epfomb8BxuwfOYjxfwCH6NZ/EbvIilWI226yLWw++xNZZhL/wBR+AlnI4/ogHLMQt/wtX4N3wUf8YdeBkP4y/4Mf6KF/EKXsMKrK+8nwvbops77RK643D0wGisiQuxFm7BW/BDvBVL0BOvYF1UHtB5G96GTbADNsO52BzXYwvchC1xM/rja9gGP8AAPI3t8K/YCbNq047hFuyC27AbbsdAPI3d8W/YA69gXxxSh7YQI7A/TsexmILjMBPH4xoMw804AbfgJDyAU/ADvAtLcCp+h+FYgdPwKt5tfp6NuxxzyrGogeiktKPSDteSdrg2emMdbIr1MQAb4O3YEPuiD4ahL96FfngPNsZobILzsCkuxWaYi83xOWyBb2NLPI6t8C/YGr/BNvgjBqAHeWyLdbEdNsb2GIjdcST2wFDshTHYG+OxLy7GIFyC/TEHB+BjeAe+iINwNwZjBY7GqzgGybtbKLbBsdgWx2MwhuFInIhROAl1ONnyPF45xpRjT4Pd83hfd5f3kmBHLMBAPITDsRDH4Js4Ht/GP+FRfBLfxV14DPfge6g+T1aO/zBV0tU+TzZC9jem4yzUYzLGouRbjs2Udd4x3x9Kvj/CbvgpDsHTOBqLMQ7P4g78Gg/iN3gYv8WGysypJz90R/U5Z3JsJMdMBrvnnN3LdPUwBpuhDttgLPbAOByICWjAWbgGE3EjpuBWNOBunI2HMBU/xDT8EY14BedgLdLOwHY4D4fgfByB9+EUXIQ63IQLMQeX4BbMxW2Yh9vxEO7Ak7gTz+MurMA89FS+r7Ahvoo+uBc9PW7cr66IMD+fJ5PYQOQN+9f0tzsmfe7KCaWvXeh/aX+7qvS1+0/uZ5dH5PyP97PThf9n9a/7R/atMzxBfohtxHGigvB/kjIRxifdbv78B/14EMn/lOv/pmtTSUJkWuqc1H8=
*/