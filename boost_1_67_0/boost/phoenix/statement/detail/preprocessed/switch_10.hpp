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