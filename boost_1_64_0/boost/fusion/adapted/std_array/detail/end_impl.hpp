/*=============================================================================
    Copyright (c) 2013 Mateusz Loskot
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_STD_ARRAY_END_OF_IMPL_01062013_1700)
#define BOOST_FUSION_STD_ARRAY_END_OF_IMPL_01062013_1700

#include <boost/fusion/adapted/std_array/std_array_iterator.hpp>
#include <boost/fusion/adapted/std_array/detail/array_size.hpp>
#include <boost/type_traits/remove_const.hpp>

namespace boost { namespace fusion {

    struct std_array_tag;

    namespace extension
    {
        template <typename Tag>
        struct end_impl;

        template <>
        struct end_impl<std_array_tag>
        {
            template <typename Sequence>
            struct apply 
            {
                typedef typename remove_const<Sequence>::type seq_type;
                static int const size = std_array_size<seq_type>::value;
                typedef std_array_iterator<Sequence, size> type;

                static type
                call(Sequence& v)
                {
                    return type(v);
                }
            };
        };
    }
}}

#endif

/* end_impl.hpp
Ydxqh9+4K0jamvBNrA81IHQSAswICa1sysp2yJMAt89w3e42dVSAan+IC6NVbL8O2cIp/l0XgIV3Awqz7CWFwZwpl3hG+XAPuruqYTjlDlxPzUeX/+ngd91pRJAWKrTxlJAoX7GU+vG2v6uPSGVe4v5FEmj6jxvQdKOvYmds18f7HHl7SWmER+WXfe98DTX3IGvHydSzqLfxXPFjWo322K1zeeyy93oGW6mS/y4cwu6u55FV6Qr45GLzBZmDEKXTHlpygwSIlD2kvziQGHhEA8JKpS/ngh1fDPh14hAhBq4R7aTBkDws2g38lh65rxDE4rNaCB4gbId0QMOF98/jelY3LpNfGFsthh/vXh0gWj9dSbsvPGgoeYokMyF8ZrxVUkM/1u+vtnDQbPfieheRAryGH6L+xuO1zQ5nRhJdJprPNz2AmWzMu7NLkKy7q6qA8rgWQ0sHHS0NL/BPtRZCei00S2AqFcMJu6iAAVElEyEv5xxbOpdTESWGp8gFmWVfLtE0HzvDd4mtvz1VbGP44Ob6MlYXurc0jui9WdMCZZQo2YmRk536ChUUtQ==
*/