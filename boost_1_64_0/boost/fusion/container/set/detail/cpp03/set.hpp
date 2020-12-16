/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_SET_09162005_1104)
#define FUSION_SET_09162005_1104

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/void.hpp>
#include <boost/fusion/support/detail/enabler.hpp>
#include <boost/fusion/support/is_sequence.hpp>
#include <boost/fusion/support/sequence_base.hpp>
#include <boost/fusion/support/category_of.hpp>
#include <boost/fusion/support/detail/access.hpp>
#include <boost/fusion/container/set/set_fwd.hpp>
#include <boost/fusion/container/set/detail/begin_impl.hpp>
#include <boost/fusion/container/set/detail/end_impl.hpp>
#include <boost/fusion/container/set/detail/value_of_impl.hpp>
#include <boost/fusion/container/set/detail/deref_data_impl.hpp>
#include <boost/fusion/container/set/detail/deref_impl.hpp>
#include <boost/fusion/container/set/detail/key_of_impl.hpp>
#include <boost/fusion/container/set/detail/value_of_data_impl.hpp>
#include <boost/fusion/container/vector/vector.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/core/enable_if.hpp>

#if !defined(BOOST_FUSION_DONT_USE_PREPROCESSED_FILES)
#include <boost/fusion/container/set/detail/cpp03/preprocessed/set.hpp>
#else
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/set" FUSION_MAX_SET_SIZE_STR ".hpp")
#endif

/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    This is an auto-generated file. Do not edit!
==============================================================================*/

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 1)
#endif

namespace boost { namespace fusion
{
    struct fusion_sequence_tag;

    template <BOOST_PP_ENUM_PARAMS(FUSION_MAX_SET_SIZE, typename T)>
    struct set : sequence_base<set<BOOST_PP_ENUM_PARAMS(FUSION_MAX_SET_SIZE, T)> >
    {
        struct category : forward_traversal_tag, associative_tag {};

        typedef set_tag fusion_tag;
        typedef fusion_sequence_tag tag; // this gets picked up by MPL
        typedef mpl::false_ is_view;

        typedef vector<
            BOOST_PP_ENUM_PARAMS(FUSION_MAX_SET_SIZE, T)>
        storage_type;

        typedef typename storage_type::size size;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        set()
            : data() {}

        template <typename Sequence>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        set(Sequence const& rhs
            , typename enable_if<traits::is_sequence<Sequence>, detail::enabler_>::type = detail::enabler)
            : data(rhs) {}

        #include <boost/fusion/container/set/detail/cpp03/set_forward_ctor.hpp>

        template <typename T>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        set&
        operator=(T const& rhs)
        {
            data = rhs;
            return *this;
        }

        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        storage_type& get_data() { return data; }
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        storage_type const& get_data() const { return data; }

    private:

        storage_type data;
    };
}}

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#endif // BOOST_FUSION_DONT_USE_PREPROCESSED_FILES

#endif

/* set.hpp
7uwM9fBX5rov5RitK1ea9NOfJ+fCs0h3K+tjtMtyZWl3zWWJg2h2/iu/DSVu5JRp2vg0s51lzeKr6bUG6e8v06fYjjtt7b9xLdt9nP0yQyq77m9n3p/PdT888/6drvu9mfcLdN3f0byf3J/XT7S8/TXN+63+9f0Lzft3lr8fZ2SaMjxhV8yx0E93D7gR6f3sCc/Ws1z1Q3XZf1T6Kcq1bnQjXa+kf56pFYupOA5roDwXR78ZuVYt17CV6WjLtD15blKei3sGO+JWDMRtOAyfxwQswFR8AafhTnwQd+FmfBG34Uu4G/fiYXwZz+I+/BT342U8iD/hIemP+Co2w8Poh0ewPx7F0fgaJuIxnIHHcQm+jg/jCXwMT+EGfAMP4N/xCL6J57EQi/At/Azflvf3vYNN8V3sgO9hKL6PQ/EMJuAHmIJnMRU/xNV4DvPxPL6EF/BNvIin8WO8jJ/gt1iEHVmBn6IffoYT8XOMx0t4D/4TF+MX+Df8EjfgZdyHX+Eh/Bpfw2/wc7yCyg2fb7EaXsWb8Tv0xO9xGP6AEfgjJuN1TMefcQ3+guvxBu7BX/EV/A0/wt/xY6ws70Wvgr9jVQyivVXDXlgdR2ENjEQ3TEN3nII34TqshflYG7dgXdyFnngA6+FhrI/y/KZcr7ddx6f8+uc350j/s7nYEedhIC7AYXgPzsNFuBLvwycxF1/BJdiUeS7DdvgA9sEHMQwfwlH4CEbjozgVl+O9uAJX4GO4GR/H53El7sQnsAhX42e4BpX2uBYb4zqMwvUYj0+iFZ/CWbgB5+JGtO8n5Fo8DjXZT3hLfTTDUGyuTifXxnG4yXRXZbrvMAyvqdPJdWmMMJmuSKb7VOr7M810hTLdYJPpvpTpLmN//EqmO26R67P4o0zXEPfJdD/L88y/YAv8FX3xd/RHJmS5AcOxMlqxKmZiDZyDbrgU3fFRrIkrsBbuxptxL9bD41gfT2BDfBub4Fn0wiJsil+jN17FZqLVItdh8agsz02YQJLzovmeOJ//WuIC7Ir3YDDei6NwISbjIpyL9+FyXIzPYC4exCUo/VXk2qtt30C++v4qeVKPD2M3fAR74aM4FpfjXbgCZ+JjOB8fx424Ek/gKvwGn8D6SjvHnrgGJ+JafBj/hiswH4/jk3gKn8KzuAEv4Ub8SvN8ewjJX+qvv9Sftp9yttTfNKm/6VJ/M6T+clD618r1V/KW+aj9a6X/Ris8jR3wPQzA93EonsHh+CGOwXOYjh9hBl7AGXgRH8KP8WH8FFfhJVyL/9Q+zy7tvL3J9nFFlutbbI1MI+1Jrm/iSpP2FCvTxUl9xEt9JEh9JGEMTsIpmIxzMAXvx8n4IKbho5iutie5tgmLTdrTVqm/56T+CrA/voCDcTum4Q6chTtxHe7Cp3APvoZ78STuw99wPyqZvoK18RAG4KvYDY9gEh7FZHwNp+NxnIsn8B48qfZ/kmuVuETqT/s8eivpb9ga+6MPhmE7jMH2mIC+uBA7oLo+Zb4dTdZnV+l/54dt0V+mC6sk1wGhpxzf2tnjDMg1Q3lfPPpgb+yC/TEEB+BtGIoTcRBmYhjejUNxMQ7DRzAcn8bhuBNH4Cs4Ek/iKPwIR+M3GIn/Yu8+4KOo8gCOb0JQQMBQBBSQUE2o6UVa6JEiQVqo6Q1SlhQIIBKKGAUhCCgKaBTFqKiRIhyiIKKiKGI7EBE5BcRygsghKOD9Zve/u2/GWQh3cnefz+18eJ8vO5mdefPmzZu3M++9+QWH43kcJ/0bx2NzjMfbMQGHYiLmYhIWYDI+jim4GlNxG6bh65iORzADj2EmXsQJaCE9JmJtzMYbMQfbYC4GohVDcZKkJwkp9/s=
*/