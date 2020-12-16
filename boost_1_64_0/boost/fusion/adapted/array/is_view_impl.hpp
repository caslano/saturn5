/*=============================================================================
    Copyright (c) 2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_ARRAY_IS_VIEW_IMPL_HPP
#define BOOST_FUSION_ADAPTED_ARRAY_IS_VIEW_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace fusion { namespace extension
{
    template<typename>
    struct is_view_impl;

    template<>
    struct is_view_impl<po_array_tag>
    {
        template<typename Seq>
        struct apply
          : mpl::false_
        {};
    };
}}}

#endif

/* is_view_impl.hpp
4wN35QK76EdQ4jtspaO7S00w4EEpccNjGfXyyMn+o0P+LQQz4z/JE6GYVPPqflYoM4jLqTg++44CykUNo89TMHfCOpCK9ateMC6lzWW+Yh6mqm0eT7kH/Ylb951zL+bY77DZxzYCdWzCw6CR6RQ2ZGcRxVMkhsV/yXs4NO5jvHJx8PA42pZMEz42w8yYh4ao7CZ38TbffbetcLoeiTxC51WGDb2NEjj0No5NxDuzMptk5TbNXgGZMfD9kjkTDnGRoR5ntcozSSpsLdtjZPD3iEfY5L/KzHGT6lEe29MWA3zfq6HkNrCcMu9a4BdKskYohGvtsNVuc/gwYywGGfHo9ejw0RJ9D5nqvegrVEW0/fIuSHNcjpsHmCp928DCXU+T15gY8VKL8bitHhagaFfpTUW0kaiMbiLdZpjIcNj+TR4xI8MRskrOYJcuAl3f1BaIQXmjwDvRbfCYHofcidEGcCjLrGmiPUcdaLmyu9NK1/NNztVIejvdTBYpOrF4G2HxaiaTvB6Ml/UZBl3UjgyGcmx0CsallSk05LzPncCZzVUabhSYIV9DzVxxpWoiKg4aphzp9WA+g2GMUKVgezjWHUJMiqfmvNF6lxltlIUP7saatKX1wdRmVRHqNkv6lrQA1tAmNX9ll80eu2yGu4wmzWh+3H6nnbbbvSb1YqeevniQHL6HR63TmYndwiaawNgcpwMmI8L1BDzX6wviZCDgEdGh+qgv4kqIJySFaY6Mj82+/qoQcW4o/4K1y95pD0mt1kVSqx2+E6v0oESz0pho/SQ2WEdJTPVUkiInmrR7qvXaXTO3Ozmm4emYnGbVlpiszhJTWmFyRDTiITHeK4+DJoQVjOyY9U2NKpwnS8OjoWS7Mg1Xo6yAGZMV0ExjdhzLWJJ1it4cYfFdUJP8lo7aWB7vk6fc/PLZqPRYjnsZSY4QplpHEfe24kNmvoCamxWyajEtxxY9wzSxPjQRzgRmkpL57N5hl89vdndkNBOOFn5XkP9MwdgztB3y/yR23GnLoP7kzQm2lidIwWKuJgIeeAnkuq1muzduRpttJlvZpbbTrsUoCgUL3E00pwLFjteh3MzqxYQ+lJXzK1iNB3J2I3LZqRlmtRqQiyN2gIqkepTH6lEU+x+ojGSjMmeRrpOx2ExlluSMOdXtdE9sCALcc7Vya9RMmOlCj4N5jo8nOLCdBPsIa4o9cPwAf1/ZU3R71/rhcnMw0PbzOmNoMG9NSas3/mBvarDuYnpQvGYPW6SnBU3PvM2kk4k3FqKnH0z0OlvYz2yaMBT/YuWghinNXyldM1OKZk9XmzlXpcBG0fk0H6WY/W2CfwrNCC2IahPLrCEU2XtTfbwRCuydpsShZ2JEyH1g8bjslvuPZdbmSeaOxSdgEnPqVBpjpjbrqWbLx5ppBuvNZopiTjPUo4zSuUJB2jhfA2bPVID8+7hX10JFTQV0uCNxwv02B3bdbaddtvLvQkaybd80ezlyzoAn3fKW8dFROfWSij3sV+wWosdZ7AiZt8i6NgoiM28Cj/UoDu50Zi3jRxQHr+GhyGrvumnmLNl6cK/Bya7Su+DBWVFqFSd61SoOR79qxG6HetpZd73t1nMzeaxjJSbrEPm+hFuePQ0yITXGRhKz3XXKmxpSmPpY70LJn1VmxtS7kQ478shDxxvWJfL2bPPz81a9Oxtjw1/vCDbL97DIM1WR0UJp03LTQ2N8tHFkc1iyyz3HZA2cvlrBIsPQ/kcMJwYbzjkLq0HGpbwUJ5fDqipr5cPlQ7lhaA/hpfqvd0q7TpYz5Ttk0zpyD0Pv9fId2R7myBnYUpHJHmxJdVR2YujZn5o9+pO9ZivWRg+LJI4FT40=
*/