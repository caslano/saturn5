/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    This is an auto-generated file. Do not edit!
==============================================================================*/
namespace boost { namespace fusion
{
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9>
    struct tuple : vector<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9>
    {
        typedef vector<
            T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9>
        base_type;
        BOOST_FUSION_GPU_ENABLED tuple()
            : base_type() {}
        BOOST_FUSION_GPU_ENABLED tuple(tuple const& rhs)
            : base_type(static_cast<base_type const&>(rhs)) {}
        template <typename U1, typename U2>
        BOOST_FUSION_GPU_ENABLED
        tuple(std::pair<U1, U2> const& rhs)
            : base_type(rhs) {}
    BOOST_FUSION_GPU_ENABLED
    explicit
    tuple(typename detail::call_param<T0 >::type arg0)
        : base_type(arg0) {}
    template <typename U0>
    BOOST_FUSION_GPU_ENABLED
    tuple(tuple<U0> const& rhs)
        : base_type(rhs) {}
    template <typename U0>
    BOOST_FUSION_GPU_ENABLED
    tuple& operator=(tuple<U0> const& rhs)
    {
        base_type::operator=(rhs);
        return *this;
    }
    BOOST_FUSION_GPU_ENABLED
    tuple(typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1)
        : base_type(arg0 , arg1) {}
    template <typename U0 , typename U1>
    BOOST_FUSION_GPU_ENABLED
    tuple(tuple<U0 , U1> const& rhs)
        : base_type(rhs) {}
    template <typename U0 , typename U1>
    BOOST_FUSION_GPU_ENABLED
    tuple& operator=(tuple<U0 , U1> const& rhs)
    {
        base_type::operator=(rhs);
        return *this;
    }
    BOOST_FUSION_GPU_ENABLED
    tuple(typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2)
        : base_type(arg0 , arg1 , arg2) {}
    template <typename U0 , typename U1 , typename U2>
    BOOST_FUSION_GPU_ENABLED
    tuple(tuple<U0 , U1 , U2> const& rhs)
        : base_type(rhs) {}
    template <typename U0 , typename U1 , typename U2>
    BOOST_FUSION_GPU_ENABLED
    tuple& operator=(tuple<U0 , U1 , U2> const& rhs)
    {
        base_type::operator=(rhs);
        return *this;
    }
    BOOST_FUSION_GPU_ENABLED
    tuple(typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2 , typename detail::call_param<T3 >::type arg3)
        : base_type(arg0 , arg1 , arg2 , arg3) {}
    template <typename U0 , typename U1 , typename U2 , typename U3>
    BOOST_FUSION_GPU_ENABLED
    tuple(tuple<U0 , U1 , U2 , U3> const& rhs)
        : base_type(rhs) {}
    template <typename U0 , typename U1 , typename U2 , typename U3>
    BOOST_FUSION_GPU_ENABLED
    tuple& operator=(tuple<U0 , U1 , U2 , U3> const& rhs)
    {
        base_type::operator=(rhs);
        return *this;
    }
    BOOST_FUSION_GPU_ENABLED
    tuple(typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2 , typename detail::call_param<T3 >::type arg3 , typename detail::call_param<T4 >::type arg4)
        : base_type(arg0 , arg1 , arg2 , arg3 , arg4) {}
    template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4>
    BOOST_FUSION_GPU_ENABLED
    tuple(tuple<U0 , U1 , U2 , U3 , U4> const& rhs)
        : base_type(rhs) {}
    template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4>
    BOOST_FUSION_GPU_ENABLED
    tuple& operator=(tuple<U0 , U1 , U2 , U3 , U4> const& rhs)
    {
        base_type::operator=(rhs);
        return *this;
    }
    BOOST_FUSION_GPU_ENABLED
    tuple(typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2 , typename detail::call_param<T3 >::type arg3 , typename detail::call_param<T4 >::type arg4 , typename detail::call_param<T5 >::type arg5)
        : base_type(arg0 , arg1 , arg2 , arg3 , arg4 , arg5) {}
    template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5>
    BOOST_FUSION_GPU_ENABLED
    tuple(tuple<U0 , U1 , U2 , U3 , U4 , U5> const& rhs)
        : base_type(rhs) {}
    template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5>
    BOOST_FUSION_GPU_ENABLED
    tuple& operator=(tuple<U0 , U1 , U2 , U3 , U4 , U5> const& rhs)
    {
        base_type::operator=(rhs);
        return *this;
    }
    BOOST_FUSION_GPU_ENABLED
    tuple(typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2 , typename detail::call_param<T3 >::type arg3 , typename detail::call_param<T4 >::type arg4 , typename detail::call_param<T5 >::type arg5 , typename detail::call_param<T6 >::type arg6)
        : base_type(arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6) {}
    template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6>
    BOOST_FUSION_GPU_ENABLED
    tuple(tuple<U0 , U1 , U2 , U3 , U4 , U5 , U6> const& rhs)
        : base_type(rhs) {}
    template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6>
    BOOST_FUSION_GPU_ENABLED
    tuple& operator=(tuple<U0 , U1 , U2 , U3 , U4 , U5 , U6> const& rhs)
    {
        base_type::operator=(rhs);
        return *this;
    }
    BOOST_FUSION_GPU_ENABLED
    tuple(typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2 , typename detail::call_param<T3 >::type arg3 , typename detail::call_param<T4 >::type arg4 , typename detail::call_param<T5 >::type arg5 , typename detail::call_param<T6 >::type arg6 , typename detail::call_param<T7 >::type arg7)
        : base_type(arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7) {}
    template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7>
    BOOST_FUSION_GPU_ENABLED
    tuple(tuple<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7> const& rhs)
        : base_type(rhs) {}
    template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7>
    BOOST_FUSION_GPU_ENABLED
    tuple& operator=(tuple<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7> const& rhs)
    {
        base_type::operator=(rhs);
        return *this;
    }
    BOOST_FUSION_GPU_ENABLED
    tuple(typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2 , typename detail::call_param<T3 >::type arg3 , typename detail::call_param<T4 >::type arg4 , typename detail::call_param<T5 >::type arg5 , typename detail::call_param<T6 >::type arg6 , typename detail::call_param<T7 >::type arg7 , typename detail::call_param<T8 >::type arg8)
        : base_type(arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8) {}
    template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8>
    BOOST_FUSION_GPU_ENABLED
    tuple(tuple<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8> const& rhs)
        : base_type(rhs) {}
    template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8>
    BOOST_FUSION_GPU_ENABLED
    tuple& operator=(tuple<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8> const& rhs)
    {
        base_type::operator=(rhs);
        return *this;
    }
    BOOST_FUSION_GPU_ENABLED
    tuple(typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2 , typename detail::call_param<T3 >::type arg3 , typename detail::call_param<T4 >::type arg4 , typename detail::call_param<T5 >::type arg5 , typename detail::call_param<T6 >::type arg6 , typename detail::call_param<T7 >::type arg7 , typename detail::call_param<T8 >::type arg8 , typename detail::call_param<T9 >::type arg9)
        : base_type(arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9) {}
    template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9>
    BOOST_FUSION_GPU_ENABLED
    tuple(tuple<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9> const& rhs)
        : base_type(rhs) {}
    template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9>
    BOOST_FUSION_GPU_ENABLED
    tuple& operator=(tuple<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9> const& rhs)
    {
        base_type::operator=(rhs);
        return *this;
    }
        template <typename T>
        BOOST_FUSION_GPU_ENABLED
        tuple& operator=(T const& rhs)
        {
            base_type::operator=(rhs);
            return *this;
        }
        BOOST_FUSION_GPU_ENABLED
        tuple& operator=(tuple const& rhs)
        {
            base_type::operator=(static_cast<base_type const&>(rhs));
            return *this;
        }
        template <typename U1, typename U2>
        BOOST_FUSION_GPU_ENABLED
        tuple& operator=(std::pair<U1, U2> const& rhs)
        {
            base_type::operator=(rhs);
            return *this;
        }
    };
    template <typename Tuple>
    struct tuple_size : result_of::size<Tuple> {};
    template <int N, typename Tuple>
    struct tuple_element : result_of::value_at_c<Tuple, N> {};
    template <int N, typename Tuple>
    BOOST_FUSION_GPU_ENABLED
    inline typename
        lazy_disable_if<
            is_const<Tuple>
          , result_of::at_c<Tuple, N>
        >::type
    get(Tuple& tup)
    {
        return at_c<N>(tup);
    }
    template <int N, typename Tuple>
    BOOST_FUSION_GPU_ENABLED
    inline typename result_of::at_c<Tuple const, N>::type
    get(Tuple const& tup)
    {
        return at_c<N>(tup);
    }
}}

/* tuple10.hpp
jNZRt7LeUcn8oM7yQpxU7eopj+zKHoKeYrKOyOqwLkJfxfmIhY6ggL9vJpeIqKiz2qsjIf39bW2O/YySZ2PpCNf2Gb3N5EPh+lJ1BKR7jlfwdd1N9wD+vpl8IJIi9uukqMTu+uaQAthd3tye1HbeZeW5KGIvDTNf0PYJsW2xQ7BNm3KVyNNEmllqUXnHa1tIy1wxZSh3leNFdZmLJyfdzMHWxOMp/Dp0Cy8RYVIfnxTPNVOmFAXphNCthFcwCR7P4NYsntpNiyCKIhEXjjcpnoO35ramJAizysmFd8KSMMfQW/OxMA+DIolq4Rx/Wul1xVDei7dmeXKDzEuDKBeZH9pSsOvGpszRMMzqvKxTcUYub9oIhppbm9xHZ07ill5cSU14loYOnu9TvKzKLE+jOMmFXIIPd553+gVnyQhmpeXwBwfm/hUNr2lNdTIiW8uwDX5Th7/Ny7V264o6fyTWt+gpfkhwG/Z5U+ZIWZdpWRS1IE9jq5r7RNjxb83s+JXv51keiI310a4uGHAvMC517CLwMrG8sjLcxvtqD9NzAJObC9KLZRB6kXjqcYf64A49WMH3E97FyryqnSqtKkfI6lld3+HcD/G6jOvKSX1XnJGzbLstX+blV7hJ7aSVL+uHjI470rSG8kPf5DIllV9eZ5GUkbXJZB6m43n/wMyvl8U0gHqFIEuCrKUtXUKaf4nzfSoc34tCioPz0fd5mipfvrCZe5ov09XJxzXeNqnjU7Jqlfe1rdFub9sc3Mas40xOeZKwFGfObOyN1qy2ecDk5qIMiyQM/cycy3ba5h1Z+J60pLp1ItxS0XkZ3dPkPrrO3Txy6lzQ+1L9YT+EhZ26nhPFZS38uCfsRRa2G5dxFoXqxSYetubHPC3yFRiqMuE+Oeznn2T8PC5yz88TUblpP3+N8Yus9pzKUVPNfv45xg/cog6TMBY0yennv9rkL/pRnvuJF6iZgCkg0H8ZP3ZCGoO9lFRz+QiTj7J/Oyv7sEydtJAvSnlgG22fpT2unKD2PUdOgfrTftnkH6tDJ3N9t9bTH0iAf4W3yyqm0ch3VV7lnAcC6FucXwZREjtRLoIySsqgP03XWJrCpMrdIqoov6wGjLcEbsvfh0hrx6vlu580VCnH5Wqezh/Ewbt2t7Xfw/Pcssor/c4ChLdG3XMKpuzR0JFPNKSkK5d38WbVCHM+k1sLt8qdyqVy2JQu0Ve671CEerw05bxIpGHieE7tiBUSVHlrndqrFcQLtvZoHra2tbfRPB40nvudZ/lM5Pwrz6pQbJONSQXTPEJhPCvB528XefrzOgmiMnbF+lmi0rE6q3h3dfo/Zsr5gUjdsnSyqu5P/+7aMk1An788knsBo+XT43b9FzOcY1GV1VHlBuqlFFV4+m2xUuvP2/Fyy4lexuH1Oyzc2VH21/vp+jPDW0h9+Y5m5IvSaeLF26fC5C3WYVx5YZwK1Wi9pDE20b+p/WZqbcodS5wyLHNqjrJo+gSfiDdTb8fH4LLwQz8PROPhvjfOI7CJ3o6vB5Isd+OANLWqysb6dXhx42SfcUyvs+UdmB/SudiDT1H+9Z/0JOVfv7G0rA9HA4n/iHBxEnjHP/+PCd9+GnDmn1/eoby1bL8flTglTJ3NauTuLXUpvu+uqde8N7aoZRHeyr0CeGNrasUVPrOP2rWNy125Fv8ppevVCoeFbmltebSmzh8RLsO55zPGuM73C5aahZjO388onEsqnONPO27l70FtOBcUTuflxklpj/FuUQslgd2lwb1b7uuRZuJzjrLz/prikyV5/IRzIjD2WMQ0XUWdAqK3uMZ+2IHT9K3Nr/SKbHL8mS7neS0JdwRmNUeeKdxpWKY=
*/