
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