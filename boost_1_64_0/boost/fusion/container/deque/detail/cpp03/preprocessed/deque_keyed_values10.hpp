/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    This is an auto-generated file. Do not edit!
==============================================================================*/
namespace boost { namespace fusion { namespace detail
{
    template<typename Key, typename Value, typename Rest>
    struct keyed_element;
    struct nil_keyed_element;
    template<typename N, typename T0 = void_ , typename T1 = void_ , typename T2 = void_ , typename T3 = void_ , typename T4 = void_ , typename T5 = void_ , typename T6 = void_ , typename T7 = void_ , typename T8 = void_ , typename T9 = void_>
    struct deque_keyed_values_impl;
    template<typename N>
    struct deque_keyed_values_impl<N, void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_>
    {
        typedef nil_keyed_element type;
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type construct()
        {
            return type();
        }
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type forward_()
        {
            return type();
        }
    };
    template<typename N, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9>
    struct deque_keyed_values_impl
    {
        typedef mpl::int_<mpl::plus<N, mpl::int_<1> >::value> next_index;
        typedef typename deque_keyed_values_impl<
            next_index,
            T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9>::type tail;
        typedef keyed_element<N, T0, tail> type;
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type construct(typename detail::call_param<T0 >::type t0)
        {
            return type(t0,
                        deque_keyed_values_impl<
                        next_index
                        >::construct());
        }
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        template <typename T_0>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type forward_(T_0 && t0)
        {
            return type(std::forward<T_0>( t0),
                        deque_keyed_values_impl<
                        next_index
                        >::forward_());
        }
# endif
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type construct(typename detail::call_param<T0 >::type t0 , typename detail::call_param<T1 >::type t1)
        {
            return type(t0,
                        deque_keyed_values_impl<
                        next_index
                        , T1
                        >::construct(t1));
        }
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        template <typename T_0 , typename T_1>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type forward_(T_0 && t0 , T_1 && t1)
        {
            return type(std::forward<T_0>( t0),
                        deque_keyed_values_impl<
                        next_index
                        , T_1
                        >::forward_(std::forward<T_1>( t1)));
        }
# endif
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type construct(typename detail::call_param<T0 >::type t0 , typename detail::call_param<T1 >::type t1 , typename detail::call_param<T2 >::type t2)
        {
            return type(t0,
                        deque_keyed_values_impl<
                        next_index
                        , T1 , T2
                        >::construct(t1 , t2));
        }
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        template <typename T_0 , typename T_1 , typename T_2>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type forward_(T_0 && t0 , T_1 && t1 , T_2 && t2)
        {
            return type(std::forward<T_0>( t0),
                        deque_keyed_values_impl<
                        next_index
                        , T_1 , T_2
                        >::forward_(std::forward<T_1>( t1) , std::forward<T_2>( t2)));
        }
# endif
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type construct(typename detail::call_param<T0 >::type t0 , typename detail::call_param<T1 >::type t1 , typename detail::call_param<T2 >::type t2 , typename detail::call_param<T3 >::type t3)
        {
            return type(t0,
                        deque_keyed_values_impl<
                        next_index
                        , T1 , T2 , T3
                        >::construct(t1 , t2 , t3));
        }
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        template <typename T_0 , typename T_1 , typename T_2 , typename T_3>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type forward_(T_0 && t0 , T_1 && t1 , T_2 && t2 , T_3 && t3)
        {
            return type(std::forward<T_0>( t0),
                        deque_keyed_values_impl<
                        next_index
                        , T_1 , T_2 , T_3
                        >::forward_(std::forward<T_1>( t1) , std::forward<T_2>( t2) , std::forward<T_3>( t3)));
        }
# endif
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type construct(typename detail::call_param<T0 >::type t0 , typename detail::call_param<T1 >::type t1 , typename detail::call_param<T2 >::type t2 , typename detail::call_param<T3 >::type t3 , typename detail::call_param<T4 >::type t4)
        {
            return type(t0,
                        deque_keyed_values_impl<
                        next_index
                        , T1 , T2 , T3 , T4
                        >::construct(t1 , t2 , t3 , t4));
        }
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        template <typename T_0 , typename T_1 , typename T_2 , typename T_3 , typename T_4>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type forward_(T_0 && t0 , T_1 && t1 , T_2 && t2 , T_3 && t3 , T_4 && t4)
        {
            return type(std::forward<T_0>( t0),
                        deque_keyed_values_impl<
                        next_index
                        , T_1 , T_2 , T_3 , T_4
                        >::forward_(std::forward<T_1>( t1) , std::forward<T_2>( t2) , std::forward<T_3>( t3) , std::forward<T_4>( t4)));
        }
# endif
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type construct(typename detail::call_param<T0 >::type t0 , typename detail::call_param<T1 >::type t1 , typename detail::call_param<T2 >::type t2 , typename detail::call_param<T3 >::type t3 , typename detail::call_param<T4 >::type t4 , typename detail::call_param<T5 >::type t5)
        {
            return type(t0,
                        deque_keyed_values_impl<
                        next_index
                        , T1 , T2 , T3 , T4 , T5
                        >::construct(t1 , t2 , t3 , t4 , t5));
        }
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        template <typename T_0 , typename T_1 , typename T_2 , typename T_3 , typename T_4 , typename T_5>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type forward_(T_0 && t0 , T_1 && t1 , T_2 && t2 , T_3 && t3 , T_4 && t4 , T_5 && t5)
        {
            return type(std::forward<T_0>( t0),
                        deque_keyed_values_impl<
                        next_index
                        , T_1 , T_2 , T_3 , T_4 , T_5
                        >::forward_(std::forward<T_1>( t1) , std::forward<T_2>( t2) , std::forward<T_3>( t3) , std::forward<T_4>( t4) , std::forward<T_5>( t5)));
        }
# endif
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type construct(typename detail::call_param<T0 >::type t0 , typename detail::call_param<T1 >::type t1 , typename detail::call_param<T2 >::type t2 , typename detail::call_param<T3 >::type t3 , typename detail::call_param<T4 >::type t4 , typename detail::call_param<T5 >::type t5 , typename detail::call_param<T6 >::type t6)
        {
            return type(t0,
                        deque_keyed_values_impl<
                        next_index
                        , T1 , T2 , T3 , T4 , T5 , T6
                        >::construct(t1 , t2 , t3 , t4 , t5 , t6));
        }
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        template <typename T_0 , typename T_1 , typename T_2 , typename T_3 , typename T_4 , typename T_5 , typename T_6>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type forward_(T_0 && t0 , T_1 && t1 , T_2 && t2 , T_3 && t3 , T_4 && t4 , T_5 && t5 , T_6 && t6)
        {
            return type(std::forward<T_0>( t0),
                        deque_keyed_values_impl<
                        next_index
                        , T_1 , T_2 , T_3 , T_4 , T_5 , T_6
                        >::forward_(std::forward<T_1>( t1) , std::forward<T_2>( t2) , std::forward<T_3>( t3) , std::forward<T_4>( t4) , std::forward<T_5>( t5) , std::forward<T_6>( t6)));
        }
# endif
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type construct(typename detail::call_param<T0 >::type t0 , typename detail::call_param<T1 >::type t1 , typename detail::call_param<T2 >::type t2 , typename detail::call_param<T3 >::type t3 , typename detail::call_param<T4 >::type t4 , typename detail::call_param<T5 >::type t5 , typename detail::call_param<T6 >::type t6 , typename detail::call_param<T7 >::type t7)
        {
            return type(t0,
                        deque_keyed_values_impl<
                        next_index
                        , T1 , T2 , T3 , T4 , T5 , T6 , T7
                        >::construct(t1 , t2 , t3 , t4 , t5 , t6 , t7));
        }
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        template <typename T_0 , typename T_1 , typename T_2 , typename T_3 , typename T_4 , typename T_5 , typename T_6 , typename T_7>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type forward_(T_0 && t0 , T_1 && t1 , T_2 && t2 , T_3 && t3 , T_4 && t4 , T_5 && t5 , T_6 && t6 , T_7 && t7)
        {
            return type(std::forward<T_0>( t0),
                        deque_keyed_values_impl<
                        next_index
                        , T_1 , T_2 , T_3 , T_4 , T_5 , T_6 , T_7
                        >::forward_(std::forward<T_1>( t1) , std::forward<T_2>( t2) , std::forward<T_3>( t3) , std::forward<T_4>( t4) , std::forward<T_5>( t5) , std::forward<T_6>( t6) , std::forward<T_7>( t7)));
        }
# endif
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type construct(typename detail::call_param<T0 >::type t0 , typename detail::call_param<T1 >::type t1 , typename detail::call_param<T2 >::type t2 , typename detail::call_param<T3 >::type t3 , typename detail::call_param<T4 >::type t4 , typename detail::call_param<T5 >::type t5 , typename detail::call_param<T6 >::type t6 , typename detail::call_param<T7 >::type t7 , typename detail::call_param<T8 >::type t8)
        {
            return type(t0,
                        deque_keyed_values_impl<
                        next_index
                        , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8
                        >::construct(t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8));
        }
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        template <typename T_0 , typename T_1 , typename T_2 , typename T_3 , typename T_4 , typename T_5 , typename T_6 , typename T_7 , typename T_8>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type forward_(T_0 && t0 , T_1 && t1 , T_2 && t2 , T_3 && t3 , T_4 && t4 , T_5 && t5 , T_6 && t6 , T_7 && t7 , T_8 && t8)
        {
            return type(std::forward<T_0>( t0),
                        deque_keyed_values_impl<
                        next_index
                        , T_1 , T_2 , T_3 , T_4 , T_5 , T_6 , T_7 , T_8
                        >::forward_(std::forward<T_1>( t1) , std::forward<T_2>( t2) , std::forward<T_3>( t3) , std::forward<T_4>( t4) , std::forward<T_5>( t5) , std::forward<T_6>( t6) , std::forward<T_7>( t7) , std::forward<T_8>( t8)));
        }
# endif
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type construct(typename detail::call_param<T0 >::type t0 , typename detail::call_param<T1 >::type t1 , typename detail::call_param<T2 >::type t2 , typename detail::call_param<T3 >::type t3 , typename detail::call_param<T4 >::type t4 , typename detail::call_param<T5 >::type t5 , typename detail::call_param<T6 >::type t6 , typename detail::call_param<T7 >::type t7 , typename detail::call_param<T8 >::type t8 , typename detail::call_param<T9 >::type t9)
        {
            return type(t0,
                        deque_keyed_values_impl<
                        next_index
                        , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9
                        >::construct(t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9));
        }
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        template <typename T_0 , typename T_1 , typename T_2 , typename T_3 , typename T_4 , typename T_5 , typename T_6 , typename T_7 , typename T_8 , typename T_9>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type forward_(T_0 && t0 , T_1 && t1 , T_2 && t2 , T_3 && t3 , T_4 && t4 , T_5 && t5 , T_6 && t6 , T_7 && t7 , T_8 && t8 , T_9 && t9)
        {
            return type(std::forward<T_0>( t0),
                        deque_keyed_values_impl<
                        next_index
                        , T_1 , T_2 , T_3 , T_4 , T_5 , T_6 , T_7 , T_8 , T_9
                        >::forward_(std::forward<T_1>( t1) , std::forward<T_2>( t2) , std::forward<T_3>( t3) , std::forward<T_4>( t4) , std::forward<T_5>( t5) , std::forward<T_6>( t6) , std::forward<T_7>( t7) , std::forward<T_8>( t8) , std::forward<T_9>( t9)));
        }
# endif
    };
    template<typename T0 = void_ , typename T1 = void_ , typename T2 = void_ , typename T3 = void_ , typename T4 = void_ , typename T5 = void_ , typename T6 = void_ , typename T7 = void_ , typename T8 = void_ , typename T9 = void_>
    struct deque_keyed_values
        : deque_keyed_values_impl<mpl::int_<0>, T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9>
    {};
}}}

/* deque_keyed_values10.hpp
l/26HzNHo33zIbGZtw9N8KHK5UPdj4/PavFhgMx3OSk+3IRYZFz8U+HUwz7XfJfZ6T7YDfeIafDMSSanrLxcl/0nw7X1NlIwuY/PEscxW6h8Q0hyL1mLSb2kfP/efC6GcczA7Lvm/ufxMY5VmMU8zL+XvzpYWx9a2WJFZsSRkWf+EPtU+5zxc/2fi2E858I8RmI8B8f/2Inx9+n9n9vi7xycnyovVZk9VvRhq9aT769eOvdgsxN/m9e48GWzuTm1z3mxvxPAiw2+uztFYktJMFKZI2JBSkQvRPQawHaip87tKK1h/xNk/xNl/5OU/VfWsP8YZbsqZf/67ca4tkOeNd/fKGW7KNmuRy37S33W3O4wZbuyGuxeqmxXrrNrtr8q2W6EwXaXq+V4zny7cWo76rYzK2+lbjtj/+ReDQfV4l+qbjsz/8p025n5V6Xbzsi/4iC5f8CbZDvX3Crd3K6LYDiMhR3gZbAjHAs7wUmwM5wOu8BU2BVmw26wAPaAxdACP+DAZ05HrfM+dnRibD5yHGnROTgoCpmByDena/zedOQTP903p/9bvjed8ETt35x+qXkjYnv+fXP6A3S0+SiLaas+Y5Q8Z358ezrjCf+/P12MzjJt+yfO/TvUazoH/yy+RV1843/+e9S7KesB5DjSoktwUH8kCSlENiD7kMOIlozAgsQjGcgKZAeyHzmOhHULxFcDS2AJLIElsASWwBJYAsv/13J+4v851sK52gCAc4v/a7Hyxrzcx0g/8x6JlefyGtQTZsEjWtyozBELyUvBuJZGLdcRs05mm5rG4q99QBmLL2PfN9rzcKUTZ5dvt7viAcWS18rVP52Z6fWNemwvcOdVYmws6/iSoGwX6zFeX9/fnZOXkUKcRclhFYkv6Dvy8EkdWBp650Ac15Y62GQvC0XXKsG32LIzhl7OD3zXJiB42FplYCsOW6UbVVu+5cty2urZ1m1LzZkVL7HzEolz3YgM08q13m4rLzvD2bgLtExyeRnW2nNmSR41pXzuPGpzHOsyOMx0edRYpTWD4RgDT5/3i88DJfbSFxnJtpUGPltz8dmHOLVBPanxF/FZ4mDixySJxxdLOxUgf42mTh90xV/Ssufk5acU5qXkZPheb4l2e6gqfu1po61jL7oY0J7Gupi9HCsVG50++Jab06j8almHS0y7fyOxA9/pTp+iu6yzcwo8c0OuqOU6cPwhz+tAaRB63e1tnuU8DmyufHzZaenWbPnOh7OOMGmvJmkr17GUm5Uh69wxvbw0q81dx7+ScjKrR45NtY71OQPzFwDJpee0nZNWMC8xrWCuY/1w2Vb85EiW49u93zmZ0Y59azn09tJucZSrgt9Xbace3HE02b+NHTnaQG2HComXv92Q7eHr0N4OD6vtwGHvRzvcs6v2dij2bAdXnV3qiE0WOOsnTs2LmJLDuWfeDnMN6jxR1zaG7WBc33IvUc4f2dZm0gbxlGdfE8e17/md7jZIcpUrm4JJGyjX5xKJwTdvwPbwArirB/edR9Q24Po8J7fW+6HDZ2iv7wLqW+5PJvUY71Hnctwb1Fmirh7kGPKI32+Xa0YZovlfsdvD/wXW/KxMLgN1KoO0udf5GKuui5EyGfgfV4P/MyTubZFzoAv8VBvT9huX/+xGu+raCqgkn+YH3v6Ybn6gcZ3KcUTT5mTojhXaw6vtuDoVcmjqyy7HsZRd4v34KuuSlXsnfxpfR3R1sqe5jEegED3hADgN/8u3uuokq9Ca4zgo/WjTyW095z7ONYj921yxfwagyrpitf0on9Spe520/QpX/eGZD8e+2ibaOZzcjDI2dxzLsfe7z+E4pV2i5XyfwXa7kQn8zlS2TVQ=
*/