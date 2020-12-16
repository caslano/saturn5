
#if !BOOST_PHOENIX_IS_ITERATING

#if !defined(BOOST_PHOENIX_DONT_USE_PREPROCESSED_FILES)

#include <boost/phoenix/operator/detail/cpp03/preprocessed/mem_fun_ptr_gen.hpp>

#else

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/mem_fun_ptr_gen_" BOOST_PHOENIX_LIMIT_STR ".hpp")
#endif

/*==============================================================================
    Copyright (c) 2001-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 1)
#endif

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

#define BOOST_PHOENIX_ITERATION_PARAMS                                          \
        (3, (1, BOOST_PHOENIX_MEMBER_LIMIT,                                     \
        <boost/phoenix/operator/detail/cpp03/mem_fun_ptr_gen.hpp>))             \

#include BOOST_PHOENIX_ITERATE()

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

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#endif // BOOST_PHOENIX_DONT_USE_PREPROCESSED_FILES

#else
            template <BOOST_PHOENIX_typename_A>
            typename phoenix::expression::mem_fun_ptr<
                Object
              , MemPtr
              , BOOST_PHOENIX_A
            >::type const
            operator()(BOOST_PHOENIX_A_const_ref_a) const
            {
                return phoenix::expression::mem_fun_ptr<
                    Object
                  , MemPtr
                  , BOOST_PHOENIX_A
                >::make(obj, ptr, BOOST_PHOENIX_a);
            }
#endif

/* mem_fun_ptr_gen.hpp
XltoCmwD5xmXnkhVKuL4bzA5Tsh37XF8znsnE+u9tyyQB3sZuKlzEg9t3J/Vo4hnFXnRp6Np6DoLNuBO8GK/zSWqfv2GfAjS8W9lpGIlOJR4i5BlJKErBaWaZJSajmWUziSUtvGBmG7m7p6ARaJ60D8CP6XUj1Wp4ViqtB5OoHQ0/hKxh6vMnwFI0lD9RQtgQptVDXG1hrjCbkKcryDu6mdexs4m06l8/13JaI9T2X8B2fEYbMykilyixsGiMvnhdzx4P6jBpAuYNwsYzJUARiZTzA4+UaeqA9Rq3Esalcepvt1m5dzo3LQ2aPtTLhIw0U/olNXzjPVU2hfgnHuazTcueuNpLXEwZy+nU+437cmtfiy51ccrdFG+HThMBH7rNTXp10ZKa8uNiLDpuurKdbbQGP8WTe0iC7XfmcyArnVju9fNMw681gv5NA/9JpmKaxU0rxtPlevnyZSQTaq5+bi3EKED9sMuDcEnEM5SEP6YgfVugoEOcj4XSErVFGIzpxDa78scIfRNmEKc8rr1TZ5AwEjAuxwnPlKm2YjCY0kv4aLvuaSXcNN3D+XxwHek3zuaflfYLfw/ifE9HvCV3qcpCEGH56e1CYdQoksSGVlKc6s0mSNpLHswEVoa04Plr7r6g5bhN15Vf386CbxEEbuP9g/7QNoETlZup4lsX/XiNW3AYNV8eIvMrQFJQBmspeRaI+MuCOLofA7iM0LOcPGaJijqCB3NBAsOBoiR+dEmkEaA9BogN8ROoQxjZAoFwkkHReYPUBkdmDELAEYAIPekA3qy9TxUPybalhSHKhNURlX7cbIPXRGteHCeNTtvHn5NfOpR0p6QB+h0IvbzapKcbQQLi0IRfMRbpzmCMK/WkYy3Ds7ctI7UxQZuL9nIS00d/jGLVDQ4UTpeB7UuLzOunWyKxfNMsbjm/wncHaPSjiTTagxXLOO1DEf827J5pJn9KeJWZlG9IEVux9R5xpXlqkkbqio34Mq+MN9fkJE0OQxSWNxD8rsN4uzbDLbSSMFWNiQqoBpJAaXlFRvKEtZSkgYYvyqjeYuO9hsgY2x8HwVlmj+B/WhjqfizmKY84M8o8ucX4Bfx1mjgreoD+cFhcKKH1yuA/2p9WiQDxnOcj4MowLpetZ+X8qjNMhLnpjWlkP6DhMBhZdfUhNBorxW011Lda2V7IqN4bk7TZKhoeunayqwEkWJsZ2yWGjw9yTD4bS990VjG+dpgRTlWaUT2obxnbk0T8FTrT0EJQmMRV5HgTSTndB5BzrmiYl1tVnzCpriETeUgiWNZ1Nav8cXNSzO0sHJ9uTF0HKWqXSRxwyZAlUSvy5+kTnwQvtXaEy8iOIKzQdIG4Dcy+JGvHGLDCHNlWZjM018cxzz9OMIT4Q5sNmhu2AKxCY9R8invd9Efkpz2hNbR1Zl4tYHzNoxTeZdcmiLfSp1vvc5XBLMXYLyM01fp9DE406C5i/Ks5KSO2lJufInWZx+clsb7b81IWievGxu3e27mGbpnDulFxLXPnG9TzHUNNNc1xMbLUnKHIORH/zh6/zeGlVdnYVsDnp4k12MFyl3JnXSXAjGYaHD+WFNsHfsaSNfEbchwnrppx3vcOMrk/7FAQ7YznhpNFCZqD2EwtPcueCNOuBZ97XPh2uefzz+f0seMfwpTMrpi5vAsTm8NBqpWKhRvzSX2uA0LHZSDSy2blW08g7qt+wfMhVOIjjQ6SfxhXSMiMppF/DfxVPK1kTzf5yrzw8psdveHSy5fixzBRojK7Jwmlld30fRQZtHtoHCDLURreZ1h2Rxu6BfrirfazIpfGcEVP6BdTaFTcBKs0TGhgI4GM8GQg6ya0lEp1C7+Cdo=
*/