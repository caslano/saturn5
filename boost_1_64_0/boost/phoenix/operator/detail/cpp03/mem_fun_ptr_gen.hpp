
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
/73JmhqcnqHBVRgCK4dyCkFlHHmixylhnT7BiENw1YqvMi1tGxAPMyeB4oGewz3Tm1VwUhM+ObH0BlDoCLpmVB3Y5xdnqsXkqEGnveUNFPsjKYSPpuv4IzMIAvxqwQ0vOWgS5aDpXUUNoZ20AF9hgSl2x3/tBuzn13sshfdgPR2xPYRWKV+Tbak93AEPDB7UXxny95CJP2Syp3R1DfY2weM6IUZs1+2MjEFQVTGqjXvcYN8XMl6fyk4Car+WnNj9TFwKDJAi+OuUpvGggVHs9KbNGR8/wmZHD8Xo9X1uHZJNQaPKfkwbQQVTKzp/94ozze7g7yHmmnjToDtsY+19rGe64V3mxMSlxVIyu/yRXvBaQSXJ27yPy5alc6ymZFYsg2gW7ktkmwFq3ONCHHJrrkBZ5O4TyvSbs3868rHOzs16Z6ffgkaD/zSOy3ecwGT5ZFVyKp5bQBSpmusvX60j5qGb021BJqKnNo18WpoerJWX/IqVeBcnObczWjdgg9FesFkaRhcb857CPFpI2iThcR7emxQBIbcsrtGnUGUNKQzfZMM0RU3PVUkvHw==
*/