
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
xxFlmf8n86bSeUPjQYahGZTge9LvyNHrB32GWwzix8aEhcIFg9nZUfC4Bes7p7ku40pEi1SxRs24h/4AKp9vpI3/6AN896VZZ2m8aDKiUKUGM9tEhr9O+bYNE/iFLWMq0jOsVLyScHSnDdL/m7Up4ODi+9YdfLd63msRx4mNvIFl7yabbefoek2/7Dan/TrIYQmWVTMlZoAH1YvJGh9yTe7qP1K7f3EElnvIZYfUjN/4l9DyT5VcK8Gr72ECAo6dtNPAH3BYUo1ctn+iTWoZs7NSRunoDMn968F5T3NnGTC3cVqNbNeXjzDJVVI/DxyhPysWpCSVETFq1J4KM8LJNTFtIquJ166+D8C8oIbgoEqFA1caqgSrjXKH6aYDvgOwzIBpm10mbFcle4qm2XAs3dtA+5Y+KNa3AY+M7ZBE9U2nJEaf5k9Lwd1r87F7Qn2IEjWpnFoQfqVtaGw+aa68KIuuf/4nNKW811A7pOamvrtBzst2GeEl8NQjxzWKhIteNSZu0/nCunHnCXPxem8T3s/Zx8nO9y4owsQ1hvrhgStgnlEsZLDt8xuq73XGpPpcNEP81s9nmkfbvrx5NSTUQJWkoxU0l/myYSIWkD6aCzOajwWAXNpJh5Y4vK0nWYSh+XlAlVBxSyymkT3wj3YbbZbEk5GlGqC104JVjKDw9lJZG4FiNV8GeiKzzWjti3OqIdxG0oYfO+mXs1K4
*/