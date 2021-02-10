/*=============================================================================
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_VIEW_FILTER_VIEW_DETAIL_KEY_OF_IMPL_HPP
#define BOOST_FUSION_VIEW_FILTER_VIEW_DETAIL_KEY_OF_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/key_of.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct key_of_impl;

    template <>
    struct key_of_impl<filter_view_iterator_tag>
    {
        template <typename It>
        struct apply
          : result_of::key_of<typename It::first_type>
        {};
    };
}}}

#endif

/* key_of_impl.hpp
CkRG2jKykeHBEKNilxQho0yXtocijGtHz/j5iU1bsqf68XOs3iaCTS/8Uwz0Zs7KSv+OS+kGG/T1hliYQipXhviADQhKuWBVbEktKXFL2fs5aQ61jbmUC5LanNJ6iK1eWfCV1wiZ5sU2v+bmydeTvaUDUZ3lvaWf0GHQNB/K8doWe+spUN3pX+ImhB3DlzQ6tmHHNvzW4iHwI4A+hk2YMuq+4R5/2B4/nFK9Qt1Iu6OidwL7RYvlzkmCV+E+ReMbhwBtyMcf8mU1OT7YwUUS5eE5A5ecxfknLIAbDzEryyS6DDm3vfbTRkc4c3pAn1pOrjLlvOYH0KlCOCC+DEPWNcHFNx2FF5RXBc0NQPgAl6L8v4XFhqlHbIPQeYEnzFltCzHXWqOb7tCnUwtGLVKN4MRt9QjyvXAt7IBp1KRNR8o68dBJ4wEP7Kht50zcgoarqDdLMdLQ/ZLCJndTMKjWd9MxqCXpefmRavVFKq0NsmswSnhmrfKWAioZ9fsxAf42ef4otZGUSobka8t3DCma7wtq3Fr+GgyOPlMUuqIxeJddM7Wn53WkvM2UNT2Pi3lol50jDI4eKrZflNx3a4RaPFqHeBWqwQq1g+swwSxQhFm1g7VXsE5RaxwOGbeG3fTXjYON/Y0O5i/9i/by
*/