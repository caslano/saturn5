/*==============================================================================
    Copyright (c) 2001-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
    namespace detail {
        template <typename Object, typename MemPtr>
        struct mem_fun_ptr_gen
        {
            mem_fun_ptr_gen(Object const& obj_, MemPtr ptr_)
              : obj(obj_)
              , ptr(ptr_)
            {}
            typename phoenix::expression::mem_fun_ptr<Object, MemPtr>::type const
            operator()() const
            {
                return phoenix::expression::mem_fun_ptr<Object, MemPtr>::make(obj, ptr);
            }
    
    
    
    
    
    
    
            template <typename A0>
            typename phoenix::expression::mem_fun_ptr<
                Object
              , MemPtr
              , A0
            >::type const
            operator()(A0 const& a0) const
            {
                return phoenix::expression::mem_fun_ptr<
                    Object
                  , MemPtr
                  , A0
                >::make(obj, ptr, a0);
            }
    
    
    
    
    
    
    
            template <typename A0 , typename A1>
            typename phoenix::expression::mem_fun_ptr<
                Object
              , MemPtr
              , A0 , A1
            >::type const
            operator()(A0 const& a0 , A1 const& a1) const
            {
                return phoenix::expression::mem_fun_ptr<
                    Object
                  , MemPtr
                  , A0 , A1
                >::make(obj, ptr, a0 , a1);
            }
    
    
    
    
    
    
    
            template <typename A0 , typename A1 , typename A2>
            typename phoenix::expression::mem_fun_ptr<
                Object
              , MemPtr
              , A0 , A1 , A2
            >::type const
            operator()(A0 const& a0 , A1 const& a1 , A2 const& a2) const
            {
                return phoenix::expression::mem_fun_ptr<
                    Object
                  , MemPtr
                  , A0 , A1 , A2
                >::make(obj, ptr, a0 , a1 , a2);
            }
    
    
    
    
    
    
    
            template <typename A0 , typename A1 , typename A2 , typename A3>
            typename phoenix::expression::mem_fun_ptr<
                Object
              , MemPtr
              , A0 , A1 , A2 , A3
            >::type const
            operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3) const
            {
                return phoenix::expression::mem_fun_ptr<
                    Object
                  , MemPtr
                  , A0 , A1 , A2 , A3
                >::make(obj, ptr, a0 , a1 , a2 , a3);
            }
    
    
    
    
    
    
    
            template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4>
            typename phoenix::expression::mem_fun_ptr<
                Object
              , MemPtr
              , A0 , A1 , A2 , A3 , A4
            >::type const
            operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4) const
            {
                return phoenix::expression::mem_fun_ptr<
                    Object
                  , MemPtr
                  , A0 , A1 , A2 , A3 , A4
                >::make(obj, ptr, a0 , a1 , a2 , a3 , a4);
            }
    
    
    
    
    
    
    
            template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5>
            typename phoenix::expression::mem_fun_ptr<
                Object
              , MemPtr
              , A0 , A1 , A2 , A3 , A4 , A5
            >::type const
            operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5) const
            {
                return phoenix::expression::mem_fun_ptr<
                    Object
                  , MemPtr
                  , A0 , A1 , A2 , A3 , A4 , A5
                >::make(obj, ptr, a0 , a1 , a2 , a3 , a4 , a5);
            }
    
    
    
    
    
    
    
            template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6>
            typename phoenix::expression::mem_fun_ptr<
                Object
              , MemPtr
              , A0 , A1 , A2 , A3 , A4 , A5 , A6
            >::type const
            operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6) const
            {
                return phoenix::expression::mem_fun_ptr<
                    Object
                  , MemPtr
                  , A0 , A1 , A2 , A3 , A4 , A5 , A6
                >::make(obj, ptr, a0 , a1 , a2 , a3 , a4 , a5 , a6);
            }
    
    
    
    
    
    
    
            template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7>
            typename phoenix::expression::mem_fun_ptr<
                Object
              , MemPtr
              , A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7
            >::type const
            operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7) const
            {
                return phoenix::expression::mem_fun_ptr<
                    Object
                  , MemPtr
                  , A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7
                >::make(obj, ptr, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7);
            }
    
    
    
    
    
    
    
            template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8>
            typename phoenix::expression::mem_fun_ptr<
                Object
              , MemPtr
              , A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8
            >::type const
            operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8) const
            {
                return phoenix::expression::mem_fun_ptr<
                    Object
                  , MemPtr
                  , A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8
                >::make(obj, ptr, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8);
            }
            Object obj;
            MemPtr ptr;
        };
        struct make_mem_fun_ptr_gen
            : proto::callable
        {
            template<typename Sig>
            struct result;
            template<typename This, typename Object, typename MemPtr>
            struct result<This(Object, MemPtr)>
            {
                typedef
                    mem_fun_ptr_gen<
                        typename remove_const<typename remove_reference<Object>::type>::type
                      , typename remove_const<typename remove_reference<MemPtr>::type>::type
                    >
                type;
            };
            template<typename Object, typename MemPtr>
            mem_fun_ptr_gen<Object, MemPtr> operator()(Object const & obj, MemPtr ptr) const
            {
                return mem_fun_ptr_gen<Object, MemPtr>(obj, ptr);
            }
        };
    }

/* mem_fun_ptr_gen_10.hpp
ml2bn+dNp/qkl6cbs7f10uzCz4yuMf2bjH1z9aMkPisz1nylt9945G4CD1EDRIKP+EORwD5/yFin6opkY+1C46df40SHq49SovyIby/FcjVRrFKJhewxBREOLOfmm1cGDgPGkKOtZ0qMiTuB+CNE1WerH8U9iKXG62hY4Yy/vepydotbRPZjrvwmIgLD6GTqZ6apiFoyXpDNDgCK24w6okJ/WdvXujzpIepgd/O3qeHYvSKeyQR49zXvf+9p7k7DtN/yQe3XM0T7SaMwoq7b1JyR4G8I/sbMe7kRn01pQA8a8KYvUvOs5zaa/XUCb92u7UnxUok9zniOcmEalxo7vyEUL6eeDG/VX+XnALqOKIWebpIJPdYMokf3MPSIX2fAqFvISRi+eWHeHbdNCLrZREHQE3tD6n0WiFM7WJNETyScr18kZW37dXzg6+lEUHrNucdmI9IF/F7tMNFbh5ft71FeDs/YHrdMkkDLG5uVknG1o1w2Je5896gLKJuNlpjP0ucA9+t2OUxpL42EdHbSqz83bOeGy32k9jqDCONoczqKOI2td+ofau/SqvlNNHtbFg3Octb2a/xKZn/jya/zkO2TyXL4/FKINY+SSHTrPVrLbzxNs1ZK1EoxhaqxHfN/WE5E9Aykcj53xLc/s+BH0bPQJ6fSQVg/3Z3DXuL5I3EwSp1fpKh1ME48B9xlj1RjNvtr6uvPmUuBs4v64kX0e571m4zmUoIFSNA3u6hL03SL5eU6CjwsTum4fFw9fgf9SEymWJXHGI/Y2Fp6/1j2W/jufmh0WZ9YyLqbcaNIit5pamel5zhtxAxho10hczpVctrxI900UPtzZgzJVut7429yqJ4aQ85DXF5Jqc8hfbbWa2MvdRUiHS4aVz3qozv99DMeiJf4jD9s41dJNimYTdb8ydI1/Yxnx+n76SHxkVPzo3vy2cXMX5dSX5kN3nip8ZUvYTrUVEPGh/ek6ftkGH5UEsz2cxRNNrj/8pWpx5vpPZ6Nhs/09pcY8wYTROubS0nEwgudmHlL58FoWZdUMuuBUpo+kuQNJxd2oSlgYdoNzdO83KUMOuii7mFyWdOUyzKiU8QDaOHC4E3jcW4TpBjeksBlZcFV8OHvSxx6WVpdwDcEFWDfxU2Jslr1oJn1QHZlb/F7SFOAw+fXItC7eF4clRLnE5VzS4rMCHmwmCFV6s56wDN/tNt846k/FQfWhM+Kr+WqHovVf67/bG9/dRNQvNj4Jj3QjUHB88F8L43Vpu6s72WYR4jRMTBAl4z56tlI7m8uHsFfqjEKmUfTjT99rpeMBhgbv8TPQD7deC/pKdS7T5SeWLiaLzpYOFRakgxd3leox9tRJxgPbVHubZTxd+pbI6U/9/PEMRyiiIg0eP425n4G1DobM8EkewVky7VlmLrP+rJM3UV5JdBF+ojoKIzcUFz+r+8CfbIiBUR6YwmS+hJjjO9tQ7F+420UpBkNSa/sLaCXMZ5qkhrR0kc/4J9PuZNre4pqTPmCk2J5RuWdSrExlNuPtyI3i2wj9ve8rPv98yh3bvR6d+ePTSu20Uw28Ezsmd94fBOV+tdNqOclQGim1HapqBlwyotNA5azOPxyK5zxuDFxXXm/8altwEv6qeUTkDonZoLueCbnyIMpZxr/KErePYO+EbcDcQ3E7WL92kwuhfVzc+Ygbtfdc+n7AKrhPqURNmL7Er+3dRC/1zo8v4cp47AY7glZNiHbSo3tcrNO9hjjHLuIO4qe7fwWeLfD04vayO9PLekckX4vmbbsNX3TtEIdl/xVPWMneiaxppZ0dhcX8MLqqojS26ftt08n3nOAeEzruSNxpbJkV8BFGZvOaq5c10w=
*/