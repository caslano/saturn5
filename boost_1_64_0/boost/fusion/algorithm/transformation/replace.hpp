/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_REPLACE_08182005_0830)
#define FUSION_REPLACE_08182005_0830

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/view/transform_view/transform_view.hpp>
#include <boost/fusion/algorithm/transformation/detail/replace.hpp>
#include <boost/fusion/support/is_sequence.hpp>
#include <boost/utility/enable_if.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence, typename T>
        struct replace
        {
            typedef transform_view<Sequence, detail::replacer<T> > type;
        };
    }

    template <typename Sequence, typename T>
    BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename
        enable_if<
            traits::is_sequence<Sequence>
          , typename result_of::replace<Sequence const, T>::type
        >::type
    replace(Sequence const& seq, T const& old_value, T const& new_value)
    {
        typedef typename result_of::replace<Sequence const, T>::type result;
        detail::replacer<T> f(old_value, new_value);
        return result(seq, f);
    }
}}

#endif


/* replace.hpp
duia6cri0sIQ8s57jdEOVefLjeVxsvke/IL49VZ24N8djN91lNjR090/FvCqxtugQe9zFnqfQG9ElVlvqP7ej+vyb/TzN5b5k1ybaqXTWeYM1c9fX+5RUu6XustAS2hlZWmBfxm8d4p1Hai2tKeyoqiJtjRWBxxdzG3iaeIfsbAjVB/4x1MabxNjvW1Ctw7gZMSG9NAqh2cMzFWeW1DiDGLdY7g8n7sTl/7P/TtC/V7h13+ndZX3MamHDmQz/xHn0SkfBu6a0Oi7TrjkWcrZT89romeG1PWpyHv8y4kS0cMzIje+rLgwiHfm7n563FFlfYv/cyLV/zkhz2S55+HW9uww2pNfuj7sO7bJW0Zfi015YtNZYlNmqc4md3fS+Htnc+z5lN91TViT0VJjy9ZzB4HXWFivyQg8Fm09lxF4LNp6zuL/b03GD7X2ou8ULXxv9OI/XPvNjR9/PWD9S7U9t3/dtLUXcW1k7ELGNLYYzuXbIL7wF8NRcBNMgpfC6XALnAO3whJ4OdwJr4C74ZVwH7wK7ofb4QPwavgkvAa+DXfBCHReBxPh9XAi3AvT4Y1wBfwJLIE3w/NhDbwc3gJvgPvgfrgfPg8PwL/Dg/ATeDvsTB7vgGPgnXAsvAcmwXvhZHgfXArvh6XwQeiED6n9AmWcA8YhWwz7BT4laxuehjb4Kzga/hqqfZZdsi++xNevFVgmcznLYW94FuwPc+BQeDY8DZ4DF8Fc3b6K1ZJuN2SLYV/FF2TtRR0Mh0clnhOpkXhrJZ5+X/kVYo9d6sNKOAKuguNgEZwIi2EqXA2XwDUwBzpgASyBDliqfLplPAEmiV69T/ciKcfFsBfMggPhEhgHz9TnW9IJt8j3s5Lv30p6z+ni1Ui8rhbxXpZ4r8Au8FX9GhyJl29x/9bKGoJyGA0rYBp0wXS4Di6F50r5VOnLQ74tEyzKY5L4uE+GA+AUOBJOhbHwdEknD3FKOjslnZNglvehKL77Z8AhMA1OgXPhXDgPLoTpcBWcDythBtwGF4ieI4h82/LNix7D+TT/FD3/gmPgv+FM+C10QCKy5gTAnbAdrIUd4M9hR3gYngRfgifDf8JT5Dy9LnAgDIdTYAScCSPhbGiD8+FQmA2jYS4cCZ1wFBRfevnOlH1UDPvr9mqr8+GX60Y2cl2NXDcaeQ3RX1eqX2Og9DZ8XURVcNelVgWntzrI647IdSMbuC4OCVsv9hnbkaw1ORkmQxtM0a3Jiluv63cMa7Iekfr+c9gXPgr7w8NwNPwFnAQfg0vg49ABn1D9tLxTwxkW/fT7kt5f4Aj4EZwKP9bF39FA/Nclfr3Ef0fiv6vWCMn7KsyT+Po1Qick/j/gWPgJnA8/hWfCz+FZ8AtYqFvLcZCB46eQeqSB+VjZ29Szn2T6QeLu95ubDXp9x8v7Q1/j0cD6jqDXdhzf/8Ot7/gxrO0Idq/SUPcpbe7+pIY1Ho3uS2pY6xHSOo9Q9iINdh9S3ToPq7nrFtl39Pvac/THts7DuMYjFQbYWzSofUX16zy+pL/r/TF7XiI5SDWyD3kG+QiJ4GCWOCQbqUJ2IA8gryFfI/3/RlykENmC3Ik8hdQjXyO9T/z3zc9/13/f0/x/hb2F/P+njiYN71xTG/Oc7nXaWOYqNdfkmc1lCxvsLS4rbXyO0TueeFjGjfTzizss9P2el556o77SMte0lS4sDn780kofPyz1hRWZ9U23rywrtzdPn9NC3/WUp82oz7WiIreieFW+Y1WT9CWLvvbt5ELROQ3Zg75Uo77K4sKKJpRldxkLHtlH++0sJhl3WG9fWAVhfmXgsvAT2ItNNf42eUbJM5dMnzdrWch26edvj4u+cTI=
*/