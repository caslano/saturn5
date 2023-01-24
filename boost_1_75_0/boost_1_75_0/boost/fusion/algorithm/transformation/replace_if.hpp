/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_REPLACE_IF_08182005_0939)
#define FUSION_REPLACE_IF_08182005_0939

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/view/transform_view/transform_view.hpp>
#include <boost/fusion/algorithm/transformation/detail/replace_if.hpp>
#include <boost/fusion/support/is_sequence.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_same.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence, typename F, typename T>
        struct replace_if
        {
            typedef transform_view<Sequence, detail::replacer_if<F, T> > type;
        };
    }

    template <typename Sequence, typename F, typename T>
    BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename
        enable_if<
            traits::is_sequence<Sequence>
          , typename result_of::replace_if<Sequence const, F, T>::type
        >::type
    replace_if(Sequence const& seq, F pred, T const& new_value)
    {
        typedef typename result_of::replace_if<Sequence const, F, T>::type result;
        detail::replacer_if<F, T> f(pred, new_value);
        return result(seq, f);
    }
}}

#endif


/* replace_if.hpp
8YTA6U/qfAyJdF7ZpiWds+noYNiQelb1b0g9HGlvGmDvAzQhrw5BNA1kxLTMEzHFfdCQmLZriOlhP4ipTX9/iGlJjFthb8TJgTye+2uiqmcm+zew0jhECtjUZn6t2tQyQdgfb0VhH8QKW1+NWDEHY5ajZl5pBmJF0/2oETvypRAr5DRFrGhrVcSKS10jhTcvpFSClxp4n9ZKZ0Ur3Qw7Q+5ELllSTq0ctqt/baaBa6WI9A7UXUKJYje7TPJqksBLYQyIqXUZ0Ww5R8f7EYoLr/AEnr7PTUjF9aWd1tW3LkapJZNE1y1F1wIgnDeM/aB4XrYEoYD6jYGE59sgDJKESpFCkzalgetaKFdp6/KugYtRHdDzXuinmuMZX6ki6eU5NVwgakDERWdodaoazwsb1Z2werYIzohWLYLoeJwlTYpHPwxOKe8/jHF81XIWZ7yWCRT7MMGLDSVri08bykSrdxsKSIeGwizYiAw2rXkeZk6eA9PqJFj9ofVPo7zZU34dJ3jAkXEq3DFauF/ZrMJtWtMA7i/vbQzu9DzHGgAZ7T/3+mX/4fDmNLT/jPNqiz29ySd+oxuFU8HvWyp+9/TzB97Bkd7wWzJW4Pe5sV7w22OTT/w+0M8f/L7F8RvnF7xvRXjD74GHPNvXyqt0yIU6sqgcTlD5fzqp6hNUVX2CJWnDTFwBXhRi1UsGUtWLeNTh510Yh4rwMpl3Ljro
*/