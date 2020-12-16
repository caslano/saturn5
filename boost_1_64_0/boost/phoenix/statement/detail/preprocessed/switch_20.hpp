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
    
    
    
    
    
    
    
            template <typename Context, typename Cond, typename Cases>
            result_type
            evaluate(
                Context const & ctx
              , Cond const & cond
              , Cases const & cases
              , mpl::int_<11>
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
                typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 0 >::type >::type case0; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case0 , 0 >::type >::type >::type case_label0; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 1 >::type >::type case1; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case1 , 0 >::type >::type >::type case_label1; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 2 >::type >::type case2; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case2 , 0 >::type >::type >::type case_label2; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 3 >::type >::type case3; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case3 , 0 >::type >::type >::type case_label3; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 4 >::type >::type case4; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case4 , 0 >::type >::type >::type case_label4; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 5 >::type >::type case5; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case5 , 0 >::type >::type >::type case_label5; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 6 >::type >::type case6; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case6 , 0 >::type >::type >::type case_label6; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 7 >::type >::type case7; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case7 , 0 >::type >::type >::type case_label7; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 8 >::type >::type case8; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case8 , 0 >::type >::type >::type case_label8; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 9 >::type >::type case9; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case9 , 0 >::type >::type >::type case_label9; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 10 >::type >::type case10; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case10 , 0 >::type >::type >::type case_label10;
                switch(boost::phoenix::eval(cond, ctx))
                {
                    case case_label0::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 0>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label1::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 1>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label2::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 2>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label3::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 3>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label4::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 4>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label5::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 5>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label6::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 6>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label7::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 7>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label8::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 8>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label9::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 9>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label10::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 10>(fusion::begin(flat_view)) ) ) , ctx ); break;
                }
            }
            template <typename Context, typename Cond, typename Cases>
            result_type
            evaluate(
                Context const & ctx
              , Cond const & cond
              , Cases const & cases
              , mpl::int_<11>
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
                typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 0 >::type >::type case0; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case0 , 0 >::type >::type >::type case_label0; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 1 >::type >::type case1; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case1 , 0 >::type >::type >::type case_label1; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 2 >::type >::type case2; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case2 , 0 >::type >::type >::type case_label2; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 3 >::type >::type case3; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case3 , 0 >::type >::type >::type case_label3; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 4 >::type >::type case4; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case4 , 0 >::type >::type >::type case_label4; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 5 >::type >::type case5; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case5 , 0 >::type >::type >::type case_label5; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 6 >::type >::type case6; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case6 , 0 >::type >::type >::type case_label6; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 7 >::type >::type case7; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case7 , 0 >::type >::type >::type case_label7; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 8 >::type >::type case8; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case8 , 0 >::type >::type >::type case_label8; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 9 >::type >::type case9; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case9 , 0 >::type >::type >::type case_label9;
                switch(boost::phoenix::eval(cond, ctx))
                {
                    case case_label0::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 0>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label1::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 1>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label2::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 2>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label3::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 3>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label4::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 4>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label5::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 5>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label6::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 6>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label7::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 7>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label8::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 8>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label9::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 9>(fusion::begin(flat_view)) ) ) , ctx ); break;
                    default:
                        boost::phoenix::eval(
                            proto::child_c<0>(
                                fusion::deref(
                                    fusion::advance_c<
                                        10
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
              , mpl::int_<12>
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
                typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 0 >::type >::type case0; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case0 , 0 >::type >::type >::type case_label0; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 1 >::type >::type case1; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case1 , 0 >::type >::type >::type case_label1; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 2 >::type >::type case2; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case2 , 0 >::type >::type >::type case_label2; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 3 >::type >::type case3; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case3 , 0 >::type >::type >::type case_label3; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 4 >::type >::type case4; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case4 , 0 >::type >::type >::type case_label4; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 5 >::type >::type case5; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case5 , 0 >::type >::type >::type case_label5; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 6 >::type >::type case6; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case6 , 0 >::type >::type >::type case_label6; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 7 >::type >::type case7; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case7 , 0 >::type >::type >::type case_label7; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 8 >::type >::type case8; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case8 , 0 >::type >::type >::type case_label8; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 9 >::type >::type case9; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case9 , 0 >::type >::type >::type case_label9; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 10 >::type >::type case10; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case10 , 0 >::type >::type >::type case_label10; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 11 >::type >::type case11; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case11 , 0 >::type >::type >::type case_label11;
                switch(boost::phoenix::eval(cond, ctx))
                {
                    case case_label0::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 0>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label1::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 1>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label2::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 2>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label3::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 3>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label4::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 4>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label5::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 5>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label6::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 6>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label7::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 7>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label8::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 8>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label9::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 9>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label10::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 10>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label11::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 11>(fusion::begin(flat_view)) ) ) , ctx ); break;
                }
            }
            template <typename Context, typename Cond, typename Cases>
            result_type
            evaluate(
                Context const & ctx
              , Cond const & cond
              , Cases const & cases
              , mpl::int_<12>
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
                typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 0 >::type >::type case0; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case0 , 0 >::type >::type >::type case_label0; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 1 >::type >::type case1; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case1 , 0 >::type >::type >::type case_label1; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 2 >::type >::type case2; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case2 , 0 >::type >::type >::type case_label2; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 3 >::type >::type case3; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case3 , 0 >::type >::type >::type case_label3; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 4 >::type >::type case4; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case4 , 0 >::type >::type >::type case_label4; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 5 >::type >::type case5; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case5 , 0 >::type >::type >::type case_label5; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 6 >::type >::type case6; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case6 , 0 >::type >::type >::type case_label6; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 7 >::type >::type case7; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case7 , 0 >::type >::type >::type case_label7; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 8 >::type >::type case8; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case8 , 0 >::type >::type >::type case_label8; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 9 >::type >::type case9; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case9 , 0 >::type >::type >::type case_label9; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 10 >::type >::type case10; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case10 , 0 >::type >::type >::type case_label10;
                switch(boost::phoenix::eval(cond, ctx))
                {
                    case case_label0::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 0>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label1::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 1>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label2::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 2>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label3::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 3>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label4::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 4>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label5::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 5>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label6::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 6>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label7::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 7>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label8::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 8>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label9::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 9>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label10::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 10>(fusion::begin(flat_view)) ) ) , ctx ); break;
                    default:
                        boost::phoenix::eval(
                            proto::child_c<0>(
                                fusion::deref(
                                    fusion::advance_c<
                                        11
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
              , mpl::int_<13>
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
                typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 0 >::type >::type case0; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case0 , 0 >::type >::type >::type case_label0; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 1 >::type >::type case1; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case1 , 0 >::type >::type >::type case_label1; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 2 >::type >::type case2; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case2 , 0 >::type >::type >::type case_label2; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 3 >::type >::type case3; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case3 , 0 >::type >::type >::type case_label3; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 4 >::type >::type case4; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case4 , 0 >::type >::type >::type case_label4; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 5 >::type >::type case5; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case5 , 0 >::type >::type >::type case_label5; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 6 >::type >::type case6; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case6 , 0 >::type >::type >::type case_label6; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 7 >::type >::type case7; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case7 , 0 >::type >::type >::type case_label7; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 8 >::type >::type case8; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case8 , 0 >::type >::type >::type case_label8; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 9 >::type >::type case9; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case9 , 0 >::type >::type >::type case_label9; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 10 >::type >::type case10; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case10 , 0 >::type >::type >::type case_label10; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 11 >::type >::type case11; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case11 , 0 >::type >::type >::type case_label11; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 12 >::type >::type case12; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case12 , 0 >::type >::type >::type case_label12;
                switch(boost::phoenix::eval(cond, ctx))
                {
                    case case_label0::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 0>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label1::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 1>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label2::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 2>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label3::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 3>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label4::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 4>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label5::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 5>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label6::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 6>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label7::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 7>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label8::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 8>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label9::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 9>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label10::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 10>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label11::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 11>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label12::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 12>(fusion::begin(flat_view)) ) ) , ctx ); break;
                }
            }
            template <typename Context, typename Cond, typename Cases>
            result_type
            evaluate(
                Context const & ctx
              , Cond const & cond
              , Cases const & cases
              , mpl::int_<13>
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
                typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 0 >::type >::type case0; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case0 , 0 >::type >::type >::type case_label0; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 1 >::type >::type case1; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case1 , 0 >::type >::type >::type case_label1; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 2 >::type >::type case2; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case2 , 0 >::type >::type >::type case_label2; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 3 >::type >::type case3; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case3 , 0 >::type >::type >::type case_label3; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 4 >::type >::type case4; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case4 , 0 >::type >::type >::type case_label4; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 5 >::type >::type case5; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case5 , 0 >::type >::type >::type case_label5; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 6 >::type >::type case6; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case6 , 0 >::type >::type >::type case_label6; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 7 >::type >::type case7; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case7 , 0 >::type >::type >::type case_label7; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 8 >::type >::type case8; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case8 , 0 >::type >::type >::type case_label8; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 9 >::type >::type case9; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case9 , 0 >::type >::type >::type case_label9; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 10 >::type >::type case10; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case10 , 0 >::type >::type >::type case_label10; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 11 >::type >::type case11; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case11 , 0 >::type >::type >::type case_label11;
                switch(boost::phoenix::eval(cond, ctx))
                {
                    case case_label0::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 0>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label1::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 1>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label2::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 2>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label3::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 3>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label4::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 4>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label5::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 5>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label6::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 6>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label7::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 7>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label8::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 8>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label9::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 9>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label10::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 10>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label11::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 11>(fusion::begin(flat_view)) ) ) , ctx ); break;
                    default:
                        boost::phoenix::eval(
                            proto::child_c<0>(
                                fusion::deref(
                                    fusion::advance_c<
                                        12
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
              , mpl::int_<14>
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
                typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 0 >::type >::type case0; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case0 , 0 >::type >::type >::type case_label0; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 1 >::type >::type case1; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case1 , 0 >::type >::type >::type case_label1; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 2 >::type >::type case2; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case2 , 0 >::type >::type >::type case_label2; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 3 >::type >::type case3; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case3 , 0 >::type >::type >::type case_label3; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 4 >::type >::type case4; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case4 , 0 >::type >::type >::type case_label4; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 5 >::type >::type case5; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case5 , 0 >::type >::type >::type case_label5; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 6 >::type >::type case6; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case6 , 0 >::type >::type >::type case_label6; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 7 >::type >::type case7; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case7 , 0 >::type >::type >::type case_label7; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 8 >::type >::type case8; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case8 , 0 >::type >::type >::type case_label8; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 9 >::type >::type case9; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case9 , 0 >::type >::type >::type case_label9; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 10 >::type >::type case10; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case10 , 0 >::type >::type >::type case_label10; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 11 >::type >::type case11; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case11 , 0 >::type >::type >::type case_label11; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 12 >::type >::type case12; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case12 , 0 >::type >::type >::type case_label12; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 13 >::type >::type case13; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case13 , 0 >::type >::type >::type case_label13;
                switch(boost::phoenix::eval(cond, ctx))
                {
                    case case_label0::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 0>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label1::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 1>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label2::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 2>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label3::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 3>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label4::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 4>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label5::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 5>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label6::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 6>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label7::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 7>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label8::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 8>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label9::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 9>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label10::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 10>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label11::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 11>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label12::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 12>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label13::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 13>(fusion::begin(flat_view)) ) ) , ctx ); break;
                }
            }
            template <typename Context, typename Cond, typename Cases>
            result_type
            evaluate(
                Context const & ctx
              , Cond const & cond
              , Cases const & cases
              , mpl::int_<14>
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
                typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 0 >::type >::type case0; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case0 , 0 >::type >::type >::type case_label0; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 1 >::type >::type case1; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case1 , 0 >::type >::type >::type case_label1; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 2 >::type >::type case2; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case2 , 0 >::type >::type >::type case_label2; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 3 >::type >::type case3; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case3 , 0 >::type >::type >::type case_label3; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 4 >::type >::type case4; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case4 , 0 >::type >::type >::type case_label4; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 5 >::type >::type case5; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case5 , 0 >::type >::type >::type case_label5; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 6 >::type >::type case6; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case6 , 0 >::type >::type >::type case_label6; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 7 >::type >::type case7; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case7 , 0 >::type >::type >::type case_label7; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 8 >::type >::type case8; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case8 , 0 >::type >::type >::type case_label8; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 9 >::type >::type case9; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case9 , 0 >::type >::type >::type case_label9; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 10 >::type >::type case10; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case10 , 0 >::type >::type >::type case_label10; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 11 >::type >::type case11; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case11 , 0 >::type >::type >::type case_label11; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 12 >::type >::type case12; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case12 , 0 >::type >::type >::type case_label12;
                switch(boost::phoenix::eval(cond, ctx))
                {
                    case case_label0::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 0>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label1::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 1>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label2::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 2>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label3::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 3>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label4::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 4>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label5::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 5>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label6::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 6>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label7::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 7>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label8::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 8>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label9::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 9>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label10::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 10>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label11::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 11>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label12::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 12>(fusion::begin(flat_view)) ) ) , ctx ); break;
                    default:
                        boost::phoenix::eval(
                            proto::child_c<0>(
                                fusion::deref(
                                    fusion::advance_c<
                                        13
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
              , mpl::int_<15>
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
                typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 0 >::type >::type case0; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case0 , 0 >::type >::type >::type case_label0; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 1 >::type >::type case1; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case1 , 0 >::type >::type >::type case_label1; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 2 >::type >::type case2; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case2 , 0 >::type >::type >::type case_label2; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 3 >::type >::type case3; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case3 , 0 >::type >::type >::type case_label3; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 4 >::type >::type case4; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case4 , 0 >::type >::type >::type case_label4; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 5 >::type >::type case5; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case5 , 0 >::type >::type >::type case_label5; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 6 >::type >::type case6; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case6 , 0 >::type >::type >::type case_label6; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 7 >::type >::type case7; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case7 , 0 >::type >::type >::type case_label7; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 8 >::type >::type case8; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case8 , 0 >::type >::type >::type case_label8; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 9 >::type >::type case9; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case9 , 0 >::type >::type >::type case_label9; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 10 >::type >::type case10; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case10 , 0 >::type >::type >::type case_label10; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 11 >::type >::type case11; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case11 , 0 >::type >::type >::type case_label11; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 12 >::type >::type case12; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case12 , 0 >::type >::type >::type case_label12; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 13 >::type >::type case13; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case13 , 0 >::type >::type >::type case_label13; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 14 >::type >::type case14; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case14 , 0 >::type >::type >::type case_label14;
                switch(boost::phoenix::eval(cond, ctx))
                {
                    case case_label0::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 0>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label1::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 1>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label2::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 2>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label3::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 3>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label4::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 4>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label5::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 5>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label6::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 6>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label7::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 7>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label8::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 8>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label9::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 9>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label10::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 10>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label11::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 11>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label12::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 12>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label13::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 13>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label14::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 14>(fusion::begin(flat_view)) ) ) , ctx ); break;
                }
            }
            template <typename Context, typename Cond, typename Cases>
            result_type
            evaluate(
                Context const & ctx
              , Cond const & cond
              , Cases const & cases
              , mpl::int_<15>
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
                typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 0 >::type >::type case0; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case0 , 0 >::type >::type >::type case_label0; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 1 >::type >::type case1; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case1 , 0 >::type >::type >::type case_label1; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 2 >::type >::type case2; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case2 , 0 >::type >::type >::type case_label2; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 3 >::type >::type case3; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case3 , 0 >::type >::type >::type case_label3; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 4 >::type >::type case4; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case4 , 0 >::type >::type >::type case_label4; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 5 >::type >::type case5; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case5 , 0 >::type >::type >::type case_label5; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 6 >::type >::type case6; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case6 , 0 >::type >::type >::type case_label6; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 7 >::type >::type case7; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case7 , 0 >::type >::type >::type case_label7; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 8 >::type >::type case8; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case8 , 0 >::type >::type >::type case_label8; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 9 >::type >::type case9; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case9 , 0 >::type >::type >::type case_label9; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 10 >::type >::type case10; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case10 , 0 >::type >::type >::type case_label10; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 11 >::type >::type case11; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case11 , 0 >::type >::type >::type case_label11; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 12 >::type >::type case12; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case12 , 0 >::type >::type >::type case_label12; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 13 >::type >::type case13; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case13 , 0 >::type >::type >::type case_label13;
                switch(boost::phoenix::eval(cond, ctx))
                {
                    case case_label0::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 0>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label1::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 1>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label2::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 2>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label3::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 3>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label4::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 4>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label5::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 5>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label6::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 6>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label7::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 7>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label8::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 8>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label9::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 9>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label10::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 10>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label11::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 11>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label12::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 12>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label13::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 13>(fusion::begin(flat_view)) ) ) , ctx ); break;
                    default:
                        boost::phoenix::eval(
                            proto::child_c<0>(
                                fusion::deref(
                                    fusion::advance_c<
                                        14
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
              , mpl::int_<16>
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
                typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 0 >::type >::type case0; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case0 , 0 >::type >::type >::type case_label0; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 1 >::type >::type case1; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case1 , 0 >::type >::type >::type case_label1; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 2 >::type >::type case2; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case2 , 0 >::type >::type >::type case_label2; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 3 >::type >::type case3; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case3 , 0 >::type >::type >::type case_label3; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 4 >::type >::type case4; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case4 , 0 >::type >::type >::type case_label4; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 5 >::type >::type case5; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case5 , 0 >::type >::type >::type case_label5; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 6 >::type >::type case6; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case6 , 0 >::type >::type >::type case_label6; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 7 >::type >::type case7; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case7 , 0 >::type >::type >::type case_label7; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 8 >::type >::type case8; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case8 , 0 >::type >::type >::type case_label8; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 9 >::type >::type case9; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case9 , 0 >::type >::type >::type case_label9; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 10 >::type >::type case10; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case10 , 0 >::type >::type >::type case_label10; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 11 >::type >::type case11; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case11 , 0 >::type >::type >::type case_label11; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 12 >::type >::type case12; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case12 , 0 >::type >::type >::type case_label12; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 13 >::type >::type case13; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case13 , 0 >::type >::type >::type case_label13; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 14 >::type >::type case14; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case14 , 0 >::type >::type >::type case_label14; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 15 >::type >::type case15; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case15 , 0 >::type >::type >::type case_label15;
                switch(boost::phoenix::eval(cond, ctx))
                {
                    case case_label0::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 0>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label1::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 1>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label2::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 2>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label3::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 3>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label4::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 4>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label5::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 5>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label6::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 6>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label7::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 7>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label8::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 8>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label9::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 9>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label10::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 10>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label11::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 11>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label12::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 12>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label13::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 13>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label14::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 14>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label15::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 15>(fusion::begin(flat_view)) ) ) , ctx ); break;
                }
            }
            template <typename Context, typename Cond, typename Cases>
            result_type
            evaluate(
                Context const & ctx
              , Cond const & cond
              , Cases const & cases
              , mpl::int_<16>
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
                typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 0 >::type >::type case0; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case0 , 0 >::type >::type >::type case_label0; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 1 >::type >::type case1; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case1 , 0 >::type >::type >::type case_label1; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 2 >::type >::type case2; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case2 , 0 >::type >::type >::type case_label2; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 3 >::type >::type case3; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case3 , 0 >::type >::type >::type case_label3; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 4 >::type >::type case4; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case4 , 0 >::type >::type >::type case_label4; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 5 >::type >::type case5; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case5 , 0 >::type >::type >::type case_label5; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 6 >::type >::type case6; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case6 , 0 >::type >::type >::type case_label6; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 7 >::type >::type case7; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case7 , 0 >::type >::type >::type case_label7; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 8 >::type >::type case8; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case8 , 0 >::type >::type >::type case_label8; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 9 >::type >::type case9; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case9 , 0 >::type >::type >::type case_label9; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 10 >::type >::type case10; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case10 , 0 >::type >::type >::type case_label10; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 11 >::type >::type case11; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case11 , 0 >::type >::type >::type case_label11; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 12 >::type >::type case12; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case12 , 0 >::type >::type >::type case_label12; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 13 >::type >::type case13; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case13 , 0 >::type >::type >::type case_label13; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 14 >::type >::type case14; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case14 , 0 >::type >::type >::type case_label14;
                switch(boost::phoenix::eval(cond, ctx))
                {
                    case case_label0::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 0>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label1::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 1>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label2::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 2>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label3::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 3>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label4::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 4>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label5::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 5>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label6::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 6>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label7::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 7>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label8::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 8>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label9::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 9>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label10::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 10>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label11::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 11>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label12::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 12>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label13::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 13>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label14::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 14>(fusion::begin(flat_view)) ) ) , ctx ); break;
                    default:
                        boost::phoenix::eval(
                            proto::child_c<0>(
                                fusion::deref(
                                    fusion::advance_c<
                                        15
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
              , mpl::int_<17>
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
                typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 0 >::type >::type case0; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case0 , 0 >::type >::type >::type case_label0; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 1 >::type >::type case1; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case1 , 0 >::type >::type >::type case_label1; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 2 >::type >::type case2; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case2 , 0 >::type >::type >::type case_label2; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 3 >::type >::type case3; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case3 , 0 >::type >::type >::type case_label3; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 4 >::type >::type case4; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case4 , 0 >::type >::type >::type case_label4; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 5 >::type >::type case5; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case5 , 0 >::type >::type >::type case_label5; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 6 >::type >::type case6; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case6 , 0 >::type >::type >::type case_label6; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 7 >::type >::type case7; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case7 , 0 >::type >::type >::type case_label7; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 8 >::type >::type case8; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case8 , 0 >::type >::type >::type case_label8; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 9 >::type >::type case9; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case9 , 0 >::type >::type >::type case_label9; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 10 >::type >::type case10; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case10 , 0 >::type >::type >::type case_label10; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 11 >::type >::type case11; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case11 , 0 >::type >::type >::type case_label11; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 12 >::type >::type case12; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case12 , 0 >::type >::type >::type case_label12; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 13 >::type >::type case13; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case13 , 0 >::type >::type >::type case_label13; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 14 >::type >::type case14; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case14 , 0 >::type >::type >::type case_label14; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 15 >::type >::type case15; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case15 , 0 >::type >::type >::type case_label15; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 16 >::type >::type case16; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case16 , 0 >::type >::type >::type case_label16;
                switch(boost::phoenix::eval(cond, ctx))
                {
                    case case_label0::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 0>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label1::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 1>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label2::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 2>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label3::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 3>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label4::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 4>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label5::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 5>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label6::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 6>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label7::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 7>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label8::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 8>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label9::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 9>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label10::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 10>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label11::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 11>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label12::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 12>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label13::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 13>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label14::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 14>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label15::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 15>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label16::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 16>(fusion::begin(flat_view)) ) ) , ctx ); break;
                }
            }
            template <typename Context, typename Cond, typename Cases>
            result_type
            evaluate(
                Context const & ctx
              , Cond const & cond
              , Cases const & cases
              , mpl::int_<17>
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
                typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 0 >::type >::type case0; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case0 , 0 >::type >::type >::type case_label0; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 1 >::type >::type case1; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case1 , 0 >::type >::type >::type case_label1; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 2 >::type >::type case2; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case2 , 0 >::type >::type >::type case_label2; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 3 >::type >::type case3; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case3 , 0 >::type >::type >::type case_label3; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 4 >::type >::type case4; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case4 , 0 >::type >::type >::type case_label4; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 5 >::type >::type case5; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case5 , 0 >::type >::type >::type case_label5; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 6 >::type >::type case6; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case6 , 0 >::type >::type >::type case_label6; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 7 >::type >::type case7; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case7 , 0 >::type >::type >::type case_label7; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 8 >::type >::type case8; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case8 , 0 >::type >::type >::type case_label8; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 9 >::type >::type case9; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case9 , 0 >::type >::type >::type case_label9; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 10 >::type >::type case10; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case10 , 0 >::type >::type >::type case_label10; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 11 >::type >::type case11; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case11 , 0 >::type >::type >::type case_label11; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 12 >::type >::type case12; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case12 , 0 >::type >::type >::type case_label12; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 13 >::type >::type case13; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case13 , 0 >::type >::type >::type case_label13; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 14 >::type >::type case14; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case14 , 0 >::type >::type >::type case_label14; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 15 >::type >::type case15; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case15 , 0 >::type >::type >::type case_label15;
                switch(boost::phoenix::eval(cond, ctx))
                {
                    case case_label0::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 0>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label1::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 1>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label2::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 2>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label3::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 3>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label4::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 4>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label5::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 5>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label6::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 6>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label7::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 7>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label8::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 8>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label9::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 9>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label10::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 10>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label11::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 11>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label12::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 12>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label13::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 13>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label14::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 14>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label15::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 15>(fusion::begin(flat_view)) ) ) , ctx ); break;
                    default:
                        boost::phoenix::eval(
                            proto::child_c<0>(
                                fusion::deref(
                                    fusion::advance_c<
                                        16
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
              , mpl::int_<18>
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
                typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 0 >::type >::type case0; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case0 , 0 >::type >::type >::type case_label0; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 1 >::type >::type case1; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case1 , 0 >::type >::type >::type case_label1; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 2 >::type >::type case2; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case2 , 0 >::type >::type >::type case_label2; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 3 >::type >::type case3; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case3 , 0 >::type >::type >::type case_label3; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 4 >::type >::type case4; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case4 , 0 >::type >::type >::type case_label4; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 5 >::type >::type case5; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case5 , 0 >::type >::type >::type case_label5; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 6 >::type >::type case6; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case6 , 0 >::type >::type >::type case_label6; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 7 >::type >::type case7; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case7 , 0 >::type >::type >::type case_label7; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 8 >::type >::type case8; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case8 , 0 >::type >::type >::type case_label8; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 9 >::type >::type case9; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case9 , 0 >::type >::type >::type case_label9; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 10 >::type >::type case10; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case10 , 0 >::type >::type >::type case_label10; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 11 >::type >::type case11; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case11 , 0 >::type >::type >::type case_label11; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 12 >::type >::type case12; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case12 , 0 >::type >::type >::type case_label12; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 13 >::type >::type case13; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case13 , 0 >::type >::type >::type case_label13; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 14 >::type >::type case14; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case14 , 0 >::type >::type >::type case_label14; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 15 >::type >::type case15; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case15 , 0 >::type >::type >::type case_label15; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 16 >::type >::type case16; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case16 , 0 >::type >::type >::type case_label16; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 17 >::type >::type case17; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case17 , 0 >::type >::type >::type case_label17;
                switch(boost::phoenix::eval(cond, ctx))
                {
                    case case_label0::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 0>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label1::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 1>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label2::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 2>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label3::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 3>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label4::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 4>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label5::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 5>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label6::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 6>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label7::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 7>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label8::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 8>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label9::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 9>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label10::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 10>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label11::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 11>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label12::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 12>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label13::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 13>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label14::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 14>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label15::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 15>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label16::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 16>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label17::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 17>(fusion::begin(flat_view)) ) ) , ctx ); break;
                }
            }
            template <typename Context, typename Cond, typename Cases>
            result_type
            evaluate(
                Context const & ctx
              , Cond const & cond
              , Cases const & cases
              , mpl::int_<18>
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
                typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 0 >::type >::type case0; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case0 , 0 >::type >::type >::type case_label0; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 1 >::type >::type case1; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case1 , 0 >::type >::type >::type case_label1; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 2 >::type >::type case2; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case2 , 0 >::type >::type >::type case_label2; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 3 >::type >::type case3; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case3 , 0 >::type >::type >::type case_label3; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 4 >::type >::type case4; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case4 , 0 >::type >::type >::type case_label4; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 5 >::type >::type case5; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case5 , 0 >::type >::type >::type case_label5; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 6 >::type >::type case6; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case6 , 0 >::type >::type >::type case_label6; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 7 >::type >::type case7; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case7 , 0 >::type >::type >::type case_label7; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 8 >::type >::type case8; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case8 , 0 >::type >::type >::type case_label8; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 9 >::type >::type case9; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case9 , 0 >::type >::type >::type case_label9; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 10 >::type >::type case10; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case10 , 0 >::type >::type >::type case_label10; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 11 >::type >::type case11; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case11 , 0 >::type >::type >::type case_label11; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 12 >::type >::type case12; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case12 , 0 >::type >::type >::type case_label12; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 13 >::type >::type case13; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case13 , 0 >::type >::type >::type case_label13; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 14 >::type >::type case14; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case14 , 0 >::type >::type >::type case_label14; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 15 >::type >::type case15; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case15 , 0 >::type >::type >::type case_label15; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 16 >::type >::type case16; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case16 , 0 >::type >::type >::type case_label16;
                switch(boost::phoenix::eval(cond, ctx))
                {
                    case case_label0::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 0>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label1::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 1>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label2::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 2>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label3::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 3>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label4::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 4>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label5::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 5>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label6::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 6>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label7::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 7>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label8::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 8>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label9::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 9>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label10::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 10>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label11::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 11>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label12::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 12>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label13::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 13>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label14::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 14>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label15::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 15>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label16::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 16>(fusion::begin(flat_view)) ) ) , ctx ); break;
                    default:
                        boost::phoenix::eval(
                            proto::child_c<0>(
                                fusion::deref(
                                    fusion::advance_c<
                                        17
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
              , mpl::int_<19>
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
                typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 0 >::type >::type case0; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case0 , 0 >::type >::type >::type case_label0; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 1 >::type >::type case1; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case1 , 0 >::type >::type >::type case_label1; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 2 >::type >::type case2; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case2 , 0 >::type >::type >::type case_label2; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 3 >::type >::type case3; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case3 , 0 >::type >::type >::type case_label3; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 4 >::type >::type case4; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case4 , 0 >::type >::type >::type case_label4; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 5 >::type >::type case5; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case5 , 0 >::type >::type >::type case_label5; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 6 >::type >::type case6; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case6 , 0 >::type >::type >::type case_label6; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 7 >::type >::type case7; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case7 , 0 >::type >::type >::type case_label7; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 8 >::type >::type case8; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case8 , 0 >::type >::type >::type case_label8; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 9 >::type >::type case9; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case9 , 0 >::type >::type >::type case_label9; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 10 >::type >::type case10; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case10 , 0 >::type >::type >::type case_label10; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 11 >::type >::type case11; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case11 , 0 >::type >::type >::type case_label11; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 12 >::type >::type case12; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case12 , 0 >::type >::type >::type case_label12; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 13 >::type >::type case13; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case13 , 0 >::type >::type >::type case_label13; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 14 >::type >::type case14; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case14 , 0 >::type >::type >::type case_label14; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 15 >::type >::type case15; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case15 , 0 >::type >::type >::type case_label15; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 16 >::type >::type case16; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case16 , 0 >::type >::type >::type case_label16; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 17 >::type >::type case17; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case17 , 0 >::type >::type >::type case_label17; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 18 >::type >::type case18; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case18 , 0 >::type >::type >::type case_label18;
                switch(boost::phoenix::eval(cond, ctx))
                {
                    case case_label0::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 0>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label1::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 1>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label2::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 2>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label3::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 3>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label4::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 4>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label5::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 5>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label6::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 6>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label7::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 7>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label8::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 8>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label9::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 9>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label10::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 10>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label11::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 11>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label12::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 12>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label13::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 13>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label14::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 14>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label15::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 15>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label16::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 16>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label17::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 17>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label18::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 18>(fusion::begin(flat_view)) ) ) , ctx ); break;
                }
            }
            template <typename Context, typename Cond, typename Cases>
            result_type
            evaluate(
                Context const & ctx
              , Cond const & cond
              , Cases const & cases
              , mpl::int_<19>
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
                typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 0 >::type >::type case0; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case0 , 0 >::type >::type >::type case_label0; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 1 >::type >::type case1; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case1 , 0 >::type >::type >::type case_label1; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 2 >::type >::type case2; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case2 , 0 >::type >::type >::type case_label2; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 3 >::type >::type case3; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case3 , 0 >::type >::type >::type case_label3; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 4 >::type >::type case4; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case4 , 0 >::type >::type >::type case_label4; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 5 >::type >::type case5; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case5 , 0 >::type >::type >::type case_label5; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 6 >::type >::type case6; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case6 , 0 >::type >::type >::type case_label6; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 7 >::type >::type case7; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case7 , 0 >::type >::type >::type case_label7; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 8 >::type >::type case8; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case8 , 0 >::type >::type >::type case_label8; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 9 >::type >::type case9; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case9 , 0 >::type >::type >::type case_label9; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 10 >::type >::type case10; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case10 , 0 >::type >::type >::type case_label10; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 11 >::type >::type case11; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case11 , 0 >::type >::type >::type case_label11; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 12 >::type >::type case12; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case12 , 0 >::type >::type >::type case_label12; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 13 >::type >::type case13; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case13 , 0 >::type >::type >::type case_label13; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 14 >::type >::type case14; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case14 , 0 >::type >::type >::type case_label14; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 15 >::type >::type case15; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case15 , 0 >::type >::type >::type case_label15; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 16 >::type >::type case16; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case16 , 0 >::type >::type >::type case_label16; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 17 >::type >::type case17; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case17 , 0 >::type >::type >::type case_label17;
                switch(boost::phoenix::eval(cond, ctx))
                {
                    case case_label0::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 0>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label1::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 1>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label2::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 2>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label3::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 3>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label4::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 4>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label5::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 5>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label6::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 6>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label7::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 7>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label8::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 8>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label9::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 9>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label10::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 10>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label11::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 11>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label12::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 12>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label13::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 13>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label14::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 14>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label15::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 15>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label16::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 16>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label17::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 17>(fusion::begin(flat_view)) ) ) , ctx ); break;
                    default:
                        boost::phoenix::eval(
                            proto::child_c<0>(
                                fusion::deref(
                                    fusion::advance_c<
                                        18
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
              , mpl::int_<20>
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
                typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 0 >::type >::type case0; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case0 , 0 >::type >::type >::type case_label0; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 1 >::type >::type case1; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case1 , 0 >::type >::type >::type case_label1; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 2 >::type >::type case2; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case2 , 0 >::type >::type >::type case_label2; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 3 >::type >::type case3; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case3 , 0 >::type >::type >::type case_label3; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 4 >::type >::type case4; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case4 , 0 >::type >::type >::type case_label4; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 5 >::type >::type case5; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case5 , 0 >::type >::type >::type case_label5; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 6 >::type >::type case6; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case6 , 0 >::type >::type >::type case_label6; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 7 >::type >::type case7; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case7 , 0 >::type >::type >::type case_label7; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 8 >::type >::type case8; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case8 , 0 >::type >::type >::type case_label8; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 9 >::type >::type case9; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case9 , 0 >::type >::type >::type case_label9; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 10 >::type >::type case10; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case10 , 0 >::type >::type >::type case_label10; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 11 >::type >::type case11; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case11 , 0 >::type >::type >::type case_label11; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 12 >::type >::type case12; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case12 , 0 >::type >::type >::type case_label12; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 13 >::type >::type case13; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case13 , 0 >::type >::type >::type case_label13; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 14 >::type >::type case14; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case14 , 0 >::type >::type >::type case_label14; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 15 >::type >::type case15; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case15 , 0 >::type >::type >::type case_label15; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 16 >::type >::type case16; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case16 , 0 >::type >::type >::type case_label16; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 17 >::type >::type case17; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case17 , 0 >::type >::type >::type case_label17; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 18 >::type >::type case18; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case18 , 0 >::type >::type >::type case_label18; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 19 >::type >::type case19; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case19 , 0 >::type >::type >::type case_label19;
                switch(boost::phoenix::eval(cond, ctx))
                {
                    case case_label0::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 0>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label1::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 1>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label2::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 2>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label3::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 3>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label4::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 4>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label5::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 5>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label6::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 6>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label7::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 7>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label8::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 8>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label9::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 9>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label10::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 10>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label11::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 11>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label12::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 12>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label13::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 13>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label14::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 14>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label15::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 15>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label16::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 16>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label17::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 17>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label18::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 18>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label19::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 19>(fusion::begin(flat_view)) ) ) , ctx ); break;
                }
            }
            template <typename Context, typename Cond, typename Cases>
            result_type
            evaluate(
                Context const & ctx
              , Cond const & cond
              , Cases const & cases
              , mpl::int_<20>
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
                typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 0 >::type >::type case0; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case0 , 0 >::type >::type >::type case_label0; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 1 >::type >::type case1; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case1 , 0 >::type >::type >::type case_label1; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 2 >::type >::type case2; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case2 , 0 >::type >::type >::type case_label2; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 3 >::type >::type case3; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case3 , 0 >::type >::type >::type case_label3; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 4 >::type >::type case4; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case4 , 0 >::type >::type >::type case_label4; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 5 >::type >::type case5; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case5 , 0 >::type >::type >::type case_label5; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 6 >::type >::type case6; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case6 , 0 >::type >::type >::type case_label6; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 7 >::type >::type case7; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case7 , 0 >::type >::type >::type case_label7; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 8 >::type >::type case8; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case8 , 0 >::type >::type >::type case_label8; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 9 >::type >::type case9; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case9 , 0 >::type >::type >::type case_label9; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 10 >::type >::type case10; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case10 , 0 >::type >::type >::type case_label10; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 11 >::type >::type case11; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case11 , 0 >::type >::type >::type case_label11; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 12 >::type >::type case12; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case12 , 0 >::type >::type >::type case_label12; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 13 >::type >::type case13; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case13 , 0 >::type >::type >::type case_label13; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 14 >::type >::type case14; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case14 , 0 >::type >::type >::type case_label14; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 15 >::type >::type case15; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case15 , 0 >::type >::type >::type case_label15; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 16 >::type >::type case16; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case16 , 0 >::type >::type >::type case_label16; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 17 >::type >::type case17; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case17 , 0 >::type >::type >::type case_label17; typedef typename fusion::result_of::deref< typename fusion::result_of::advance_c< flat_view_begin , 18 >::type >::type case18; typedef typename proto::detail::uncvref< typename proto::result_of::value< typename proto::result_of::child_c< case18 , 0 >::type >::type >::type case_label18;
                switch(boost::phoenix::eval(cond, ctx))
                {
                    case case_label0::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 0>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label1::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 1>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label2::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 2>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label3::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 3>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label4::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 4>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label5::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 5>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label6::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 6>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label7::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 7>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label8::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 8>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label9::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 9>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label10::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 10>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label11::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 11>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label12::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 12>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label13::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 13>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label14::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 14>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label15::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 15>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label16::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 16>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label17::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 17>(fusion::begin(flat_view)) ) ) , ctx ); break; case case_label18::value : boost::phoenix::eval( proto::child_c<1>( fusion::deref( fusion::advance_c< 18>(fusion::begin(flat_view)) ) ) , ctx ); break;
                    default:
                        boost::phoenix::eval(
                            proto::child_c<0>(
                                fusion::deref(
                                    fusion::advance_c<
                                        19
                                    >(fusion::begin(flat_view))
                                )
                            )
                            , ctx
                        );
                }
            }

/* switch_20.hpp
VF+Ah73cLPfNBsv3aweiOtGOGO/D+vZ9deU8ZdiQYWOGT46MTo/V3IvqvCb8bc4dj/BmPZ4l99HJ9QHmYjkPmy7nXbX3oBZJXvpIXnoRU5R7wLV5UW/ri55n1HPKs+r5aaA5Lyz3TjrNUw/J00Dzcx8lT8q87iJPeTZ5UuZU+byESl606RRWc7x/OZx0CmzS0c9Oj0pUz99XIZ16mn4YBmOqTXk5T2xzH3Ww3IffTcrbhZhGPgLLtPmITUmdG5Wq+x31L3lxWtf5knagpN2VGKVMZ5N2HKeUu1c53QbmdDXLXVvuUA/Hde9Ops2zT1td9X53+vW8rr/eDZX8eEkfjjRZH1KIsT7894N9fpgyjjuyeShAbEKGXid14/U78qZ8TkuPZpC134nkjRSs95DXtStDGcP2N1DvpdaWochFGbJvWIYe//YymNeLyTWdr5P+l+zLkEz0+N3rhav1sshJ+l6+tIlO0+/5u9NvLenbX2NMrOW4XdzDMsx1SJ9a5/73mFl64x9pl63Lz3H70NaL+cED62TdWk3cS77KbPKVpE/SpSuHg1VuMyU/PG/DyfbqYcqP0/VLm8eFkkc/qTsfoj7LLu9HbR6T0xMTTV+uVa4zbVoVklYnSasjMY7xjtukZdDrZ0V2r8ryCXW9ntp8d2dLf4eOkn57Ioxpvcrt06/6d3doFdtQ87rb4RbH5/xE+pAvhzxpdir+QL5utE9BXdnc6z9U8hUsyyrXIV9qo/JH6srV8gqUvgPhkoe7iIa+/PeT0zz0/CN5cNW2HLnVsW2L8mFahzxoGpc/kI/Kti29pM/CrZKvOsREps2zyVeqPimKzTY5rsr50aa1R9JKlnZsJqFT9vts0qIXSTIN2R9ox6J9nH+/BEo/BW8pqzKPRqwHYX8zpU8XHQ5AeAIURxJ6dj8rXdZ0gsRs9vei7dbBPEm7kaTdkPAhbYPztCODqrDsXaWvXf961XNM34/0s12kn5BsrFIejHZ5MDrJwzbJQ1PJQ2MllO8IZ3lISIucr09Nqcq2KPVgk2az29Qx60uayscmpFlynTQjg35fmuZlvcoxTcrJfz87STMpLfr3ltGcnr+X47Jt5stwZ+ml6RP1MTf+/m2gSY+uSrNAlq3t+ublYn3bK3NvJnlqopSRPAW7zFPl1jdzvvyd5MvfLl/+mnzdKX2V4vlf+flN2qBfiFJGNqj50tFZKdKUudR0chSvT0xMiZxDX8XYeZGpHJHq0yrxjConfZWkD5+cF7DdlzI9f+h1U/rcB1/f9vl1vRqoM54t+U0i/JVt5rI1v6lRc13ktPJ5lbzZfL/HpKTMStDTTlnrU4YpBzHW4wvTOpIWpwyUsknfKbu6z2nIf6brDpRFVOo++BdTWVI4ExQpp4DkWYTWJZGkT0uLitNXojye6r78r9Ut/fUHKL/b9Rn3lGHavuBXlXzY9QUvk2HavuBfyDBtX/APZZi5L3iBfDb3Bd8ln819wZ+Qz+a+4Kvls7kv+ELL514u16dWvnw22tbxTm95bgFRV2yttAVXXNVxUlSGuXZN3dcqs86odbzhirWOH7jiWCeLr9jWScYV2zqZfcW2TmZesa2TyCu2dRJ+pWp1Mk7qJKyR9MOROplEBPjyX4WrOqHvrZEj9JQY6kUqp1L14rxf5kA+zyVT9nnU9h01+qgzekK2DTTl0XD9PM5NSZ1ViXypy6viN+al+XzuN+vyO/yb4zbynAzT3kNxr3VYd/NydvvNdjnur7AspyrXidIWpki+2vra1lE+n5Wf3aY6QqmjzKsu6yhVb6qiyiw7tU683Gzv+ym7Zq2jj6451lHiNcd2ZPw1xzZj+DXH7aPtNdvt4furtus=
*/