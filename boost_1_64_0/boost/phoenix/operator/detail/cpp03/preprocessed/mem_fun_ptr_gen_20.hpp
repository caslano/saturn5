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
+h+wEdKiVwlbRJGihbmxA0V/sLP8A72V368aT8bj65OfxjjyJMbRPkt2a6NmP4qJ7lMZg9cb6szzpTMHaZcQpC0WT3x5skOYtNGcmWC0WIadDpJhx0fwa9wzS4zXfwbxRTGkP/Y6uaGSoTfF2Qcur1YO2yqJ80i9gIqSwTLd0iwIUFKypuS0F39yRJT5/2uzgM+9dwEfdVAbAj6to8zdfGIC4SMLU4kMyvtGjTir8XyJ3cDPhTZExVFSHdsKzXA2Y5TfWab8jsqDZog86NqAQx5U7jUW16KIyCFYC6mrbqHc6c5vQPRfqjcQvxuvq2C4ZS3DL69h+MMow4duJHj9xi3b8FW3CV9fXomv6gi+7lmBr29fS1/b7qzeTF8HUQYLIGuLffG6jRRUV+aLb9nKP4r+yd6VwEdxVvHJSUqLbGmgwVKZatGgBBOOighISBYTm8skUNTqutmdJFs2u+sekNSqYKuCFUWt94Xnz6Pe94039UStWs/iXc+i1qtq6/+9b97ONzszm00oHj/3S97Md7z3vve97z7mW9zO+4/DRw7BftUQXQZyDHeVLLC/sz22FBdzfT78+hrOLPqtpruXtmKESD8nri2oPKv/7kP9d4EUF2ypBKGwyALuEdzgqhZw5XDPEhTKu9AYLIQ2Nj/rzkp/ZPwMDJefnqu6kT669WOxSt+R/g9CsktD1KT+lG6AP2fxB8K3HQ6rsrwQaR6XTPfyW3+cvfXySSk2wU2VTDWUitM1XR9oOvi34iBqWC2V1e3YooaCBx9aHD49RA0EW5xh0yoaUM3k77WfHC0fbuJ7o+9FntfUTBuFuY+snPH815YZIZVDvul7FF/AoOY3BzfHclOnMEdHwqbxO0gbaVoz02w2vGB5/lIKv7r5ErK3AOHgdPN9yX6ewjG2v5SmdeFGOk1Ec8T6SvYtEP/nG7p5HcR3DLH7461TmCx9bmtrqhG/k3/F9duefjd+COyrt/XfgK7j29d+rv7gXRSU/Xnk8UztoW9PM317xk2/yKFHUBA964dUQzNGY2iBTNv0cPVjkKHibxBPfuoiIzRJfedt763nw5Kl5We7cxB4ZPfnG3rs5L/mFvhee6LmdfS+auFtIVDbS4SHaotX3Lnnwoqaa+0iJr+p9jBbjhROYQfnpsWvPdx4+PH1hweaDu8+z76N3Li+r+EUfl6zeJd699JTGx9hpQrFW9L7lp46+PtEyuo995OM9LUfK69U3kqe+0lvZ/qsXTcf2nUrouQpZ0msxbXl0UWncK0buqZb0Uo+ER/iHPzR6Yffvfjg34434ochoL9bDv6YPe58QiN+IGI7Ov9V5N6aIWeHRjDUWIfLgnQC8ljsEMBZWHz9or66BdBIzWG22KmvK+4PdEML3UtP27fOO9pYxN747cIF1wxSmhZ402RfDW/Y2hEa8aakqt/Pyy96DQtxovZ19NYQTgPBoF/LfUsxG2udQlDPhaAU3WjKP1W2g5CJp3lgFMrvhXQ1J3E8/PCuL11Pvzb4pWt/3HjtKdxAe/xwGL/feryx0EMnrQs7VDx1WnFpUsVFEkIJP2XmlyvEBg3RVIjrj2M8xIezL3juPb7a/+83qI/yGYW2HvZ9JJTPpatfswq+TE7aB/YW98Gt1FJ0rzBCs7PAqQM+Q1jPzyZ+nsfPED+b+dnCzxX87Obndn5u4ecmfm7gp8HPNfxs5eel/DT5+RJ+HuDndfw8xM9n8/MoP2/g5yv4eVsLPX/Dz9P8vIOff+XnP/hpLGf5+dnEz/P4GeJnMz9b+LmCnyY/L+VnKz/X8LOdnxv4uYmfW/CEPl3D13vAvf74/3iZrZqqqZqqqZqqqZqqqZqqqZqqqZqqqZo=
*/