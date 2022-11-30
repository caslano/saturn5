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
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
*/