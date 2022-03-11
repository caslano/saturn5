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
    
    
    
    
    
    
    
            template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9>
            typename phoenix::expression::mem_fun_ptr<
                Object
              , MemPtr
              , A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9
            >::type const
            operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9) const
            {
                return phoenix::expression::mem_fun_ptr<
                    Object
                  , MemPtr
                  , A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9
                >::make(obj, ptr, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9);
            }
    
    
    
    
    
    
    
            template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10>
            typename phoenix::expression::mem_fun_ptr<
                Object
              , MemPtr
              , A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10
            >::type const
            operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10) const
            {
                return phoenix::expression::mem_fun_ptr<
                    Object
                  , MemPtr
                  , A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10
                >::make(obj, ptr, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10);
            }
    
    
    
    
    
    
    
            template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11>
            typename phoenix::expression::mem_fun_ptr<
                Object
              , MemPtr
              , A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11
            >::type const
            operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11) const
            {
                return phoenix::expression::mem_fun_ptr<
                    Object
                  , MemPtr
                  , A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11
                >::make(obj, ptr, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11);
            }
    
    
    
    
    
    
    
            template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12>
            typename phoenix::expression::mem_fun_ptr<
                Object
              , MemPtr
              , A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12
            >::type const
            operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12) const
            {
                return phoenix::expression::mem_fun_ptr<
                    Object
                  , MemPtr
                  , A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12
                >::make(obj, ptr, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12);
            }
    
    
    
    
    
    
    
            template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13>
            typename phoenix::expression::mem_fun_ptr<
                Object
              , MemPtr
              , A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13
            >::type const
            operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13) const
            {
                return phoenix::expression::mem_fun_ptr<
                    Object
                  , MemPtr
                  , A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13
                >::make(obj, ptr, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13);
            }
    
    
    
    
    
    
    
            template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14>
            typename phoenix::expression::mem_fun_ptr<
                Object
              , MemPtr
              , A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14
            >::type const
            operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14) const
            {
                return phoenix::expression::mem_fun_ptr<
                    Object
                  , MemPtr
                  , A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14
                >::make(obj, ptr, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14);
            }
    
    
    
    
    
    
    
            template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15>
            typename phoenix::expression::mem_fun_ptr<
                Object
              , MemPtr
              , A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15
            >::type const
            operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15) const
            {
                return phoenix::expression::mem_fun_ptr<
                    Object
                  , MemPtr
                  , A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15
                >::make(obj, ptr, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15);
            }
    
    
    
    
    
    
    
            template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16>
            typename phoenix::expression::mem_fun_ptr<
                Object
              , MemPtr
              , A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16
            >::type const
            operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16) const
            {
                return phoenix::expression::mem_fun_ptr<
                    Object
                  , MemPtr
                  , A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16
                >::make(obj, ptr, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16);
            }
    
    
    
    
    
    
    
            template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17>
            typename phoenix::expression::mem_fun_ptr<
                Object
              , MemPtr
              , A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17
            >::type const
            operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17) const
            {
                return phoenix::expression::mem_fun_ptr<
                    Object
                  , MemPtr
                  , A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17
                >::make(obj, ptr, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17);
            }
    
    
    
    
    
    
    
            template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18>
            typename phoenix::expression::mem_fun_ptr<
                Object
              , MemPtr
              , A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18
            >::type const
            operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18) const
            {
                return phoenix::expression::mem_fun_ptr<
                    Object
                  , MemPtr
                  , A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18
                >::make(obj, ptr, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18);
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

/* mem_fun_ptr_gen_20.hpp
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
*/