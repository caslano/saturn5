
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
3h6TZMP5UwSoYhETrcOYJTJKicEeOP6xxTW1MPbTmqnJ/vEYWjyyeyzxHLSLkuST8Mj7dXgaxN9458ggaDBsFIsL8xQeZzStN9xI2AaqsczYklStcKJwHhlBpDPhuHOkObqMIKgp4Xswuyn0tchTZzkUKLaY01DgUBe4UimQZwK0QUL8RNNjRwFgHKn87yVgKwNsbj/DxBAB4mPnCMRIE78RA4LfrkriZbSinu800tdFLr6au7BBaELx2wu9D+C3VlhvJYgPpG85PKJE0wYeqWGV2gY2eVDBJnGywJFQSE+FoZlRcAJdkfjACRutMre94BUnQPugzEFbjJemGvDuvtbce5iXR3pnzkJDsmCgDLEA85YCypZ5rqfIXgNUtY6N4oT+gO0WLHaO8tkIRU5T710Ar6tBKr8G07NGMQDA+Laq1CSm2Dni/SxlDIBV5i9u6g5QVQ3G21SA2ESiwQTSB6SAsXgrrIkJVl7sS7OVphCx+xI7hwpQy36GBH3iPnEGTzal/bSYwVvEB2fBQhzLgcz1ELWiaIlQvND0gR9Pnlgmm1LkhXUFZYWWPhSPf4sfN8ya8QWXaCZB/pzg0oDlCF/UgMGkwtwCt9G+3chPVSNYwkUr26iw7bNI7Zcq9Jy5Mw+4n4KeoKhb5lFR
*/