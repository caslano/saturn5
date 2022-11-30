
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
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
*/