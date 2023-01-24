/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_MAKE_CONS_07172005_0918)
#define FUSION_MAKE_CONS_07172005_0918

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/detail/as_fusion_element.hpp>
#include <boost/fusion/container/list/cons.hpp>

namespace boost { namespace fusion
{
    struct nil_;

    namespace result_of
    {
        template <typename Car, typename Cdr = nil_>
        struct make_cons
        {
            typedef cons<typename detail::as_fusion_element<Car>::type, Cdr> type;
        };
    }

    template <typename Car>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline cons<typename detail::as_fusion_element<Car>::type>
    make_cons(Car const& car)
    {
        return cons<typename detail::as_fusion_element<Car>::type>(car);
    }

    template <typename Car, typename Cdr>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline cons<typename detail::as_fusion_element<Car>::type, Cdr>
    make_cons(Car const& car, Cdr const& cdr)
    {
        return cons<typename detail::as_fusion_element<Car>::type, Cdr>(car, cdr);
    }
}}

#endif


/* make_cons.hpp
iCHr+Xd+9mMrNcY9lTnwndd4wc/wO4sKd3JSTg6kXsQKFxqb5Dvmu7cshK7lq8aDY5Tirrt0sxJ60/wm/7lfJdwybtbbocnF1FnRpHU3DfVlpW+rcw7Hmg65QNodO5LqWJm+PmANUzZ9PTf6VFDsxm9aN1Zy3vZ9H9PlQ62p+wXTYfMkhy1r6AZb2fUIjdbOI3e/GfnTxNLRz+0PUlcEvbvow4bH7CwOwewdThN8qTvib2Lc11Kb6/8usXrerllyci5N+brUkiTpUlRistFzUidTvwnfAW2faIkc+NcF4nlZWrAve3+1i+BcRFKGU80Wbmf1hl+YY3QVUujQZpiBONrBOG2XxpWOmzf9eUxcorlTYnXMETzaG9bVoh2QNzvcWpWyr1thhhvdYNEYb54UP2jNCQSrgM9VHjrjq564Ik3xhWwfdqRUHsQxeEM9QcOHYn8k7UlqFzsScT5+Ybxv5q0HLQjWwuk4b9JTgPtUOF5nuOv6cV+4r8jVuuGji3KoubJn8bvbUpq8vpW/laAuvHnd4QqxpmnHxFME9Gt/UbGQmMbaAOoYqbrjwfVomdjx+GNZrGTysTAimi0miaDn1zi50xTQHmFTrLXxToYl99yhoouv6rJMLneTr0zT5WMGS1dI/JS1cdUa3aBFRIzs+Jrk/d7LvDpk3lHoI0CrA/eM1hSkpoW0ewBv37F4x4KMM65EFn58V+7UjEBP
*/