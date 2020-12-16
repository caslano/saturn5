/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_STRICTEST_TRAVERSAL_20060123_2101)
#define FUSION_STRICTEST_TRAVERSAL_20060123_2101

#include <boost/fusion/support/config.hpp>
#include <boost/config.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/if.hpp>
#include <boost/fusion/support/category_of.hpp>
#include <boost/fusion/mpl.hpp>
#include <boost/fusion/algorithm/iteration/fold.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/is_convertible.hpp>

namespace boost { namespace fusion
{
    struct forward_traversal_tag;
    struct bidirectional_traversal_tag;
    struct random_access_traversal_tag;

    namespace detail
    {
        template<typename Tag1, typename Tag2,
            bool Tag1Stricter = boost::is_convertible<Tag2,Tag1>::value>
        struct stricter_traversal
        {
            typedef Tag1 type;
        };

        template<typename Tag1, typename Tag2>
        struct stricter_traversal<Tag1,Tag2,false>
        {
            typedef Tag2 type;
        };

        struct strictest_traversal_impl
        {
            template<typename Sig>
            struct result;

            template<typename StrictestSoFar, typename Next>
            struct result<strictest_traversal_impl(StrictestSoFar, Next)>
            {
                typedef typename remove_reference<Next>::type next_value;
                typedef typename remove_reference<StrictestSoFar>::type strictest_so_far;

                typedef strictest_so_far tag1;
                typedef typename traits::category_of<next_value>::type tag2;

                typedef typename stricter_traversal<tag1,tag2>::type type;
            };

            // never called, but needed for decltype-based result_of (C++0x)
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
            template<typename StrictestSoFar, typename Next>
            BOOST_FUSION_GPU_ENABLED
            typename result<strictest_traversal_impl(StrictestSoFar, Next)>::type
            operator()(StrictestSoFar&&, Next&&) const;
#endif
        };

        template<typename Sequence>
        struct strictest_traversal
            : result_of::fold<
            Sequence, fusion::random_access_traversal_tag,
            strictest_traversal_impl>
        {};

    }
}}

#endif

/* strictest_traversal.hpp
UiR57QeO6JoZd/ZZc4y3EFRJaZ2GkZhoMtYt9xEmwxERZSAqo0KwZwtIfB3ntSdsX51ZFOZ1LsZef/HxcYrx5iIN3LCo0kJMvp5E34TfNqve6rTOwpAav3vN1zmr+OYJay5Noyjy01p0zCTGzw8XLf64kO5g8y67NcuFWv98lslfiyTLMj8qHHFpswv0HZzzmnI8Ga+0dJzUd8RlzFxaQVifjjA5gagCt3SKXFzOmsWUcZLJcAWNHT91vUJczrzFWCfPMhm+vB+Kgtz3xeVMXsSoTi5YdVKFZZ4XeTKubvuPJyFcYXHQRs/mcrw8jqqkLCbI4Y1ktpElJ4x9qt4sQ5ksOdrQqXP39WzeZ8LAqbIg9ibJaU2BOn3mhJWfKg5CN0rrcXLodgC2WnZ+zlj5KZ1cng+Nrechq2aen/OWHLdy3azwirFyeDXz8wJWLlcUTuqkSepOKheeWhpr5t7n8LusggalV8YT6wbTo7nuPoevRUHiFkXoJuJSTySstfs4k5GLyMvdoq5yMf5ph6k/CNydsLI4wq39OKvqYpIMe5+KuxOWF2LP06Dw/WCiHGTG8BfMZLii8jKvTrJY2E/fGsZ53Gk+l+1NqrKsUpe6vGmhbJ+PzJo8tcgjvyrKXHDDZUu3vv1z+XyelVGSJK6Y+Kqu4Uf5Ysbviqj0qsytK2GbsVsxHh5t8h2siKv281Jopw04d8CaS3h2l+TIyLSOJ8Y967P2IKcYbyHqwHeoDQpxieeV9h3POSYjEK7nBo508zvm+a4dA/g8441EGrllkSSlxcuWbJ33PzPeXIRhliVp6omJ7h2688Ps8/i+IvLrsvK8CenrauB7qIPPs/pxmqVuVDvCcrPRsi3qdq5NvpzQpZMFfiRG9m9WPHsTXwvqFUGYEp576+A683GeRhmHoRcUseTRdQrftX+/Ga2T9LO9R1TuckzR/0G0P98KdMPlGPc59i7D5xgBEUQONtYZ3jpN2rjhrdNcekks3uCdgF0z38QQBH4XTgFje5EimPkWCzjmaYiB4WcC2I6HLYlD3JhvbnIbwDAoqyAP/u/3VaYPnnf2Jm36RrjVKYmbqMAC96/xOJj23gUxw8bibHcCwO/aDvxkpcbAz05fCt+1Y/4tw09QUgz88R3AT178Ddvq+CqT8dYLddhU3non57EXZYIAe2EiFibYaKONmbFY/T4IuIvAdQ+tTdyZqwHXPRg2cVfXOFlgnvjAsIPcv0viFvoDvNMkmwmUlWiKPvmgwXxfc2a3xF5GOTfwF6/B8bYSbuNnZyfgh0w88He61iQ8Ez96d37tyXhVYDNe3HU01nqTot92X9ekU89QOxy1tOHlP/y2Xs/GAgJ7zrPAjDmsMePPXV/j+IED8/kETMefIfL/iBsQ5grfYf1CYq/gXZUuy8Yewk/2kQTcReAmvBPWfpFvOAmHpJHXmRsR9v94n3Xysnj+Tn0Da4v1fth4K37KWld8302r4v+It6/WFR5T7R29yQeSPfY2l7CT12bI9LdNxuHNNPy62djuHIF396gfdtDN3jUfYfWTisx1vDJO/u/3FfDPQz9vv5TvUbxb4jjb9yjqcBvD2cVl76lPy7JqhV5N2dJSb9R295mahJk/+uT5MvGNuXhm26WwlZsa2B9dEjs8bq4V79zOsdqRtcqpIXNumuPUFKNmIaSPsv9hDFYLhM+CHV2MVXRgb3KVSVgkjfJ8dSJ2kUyZh8CJnRq3tcZriZf7uxNxyCqwb56ZhEVWgV296kQsWgl5vRrH2q2EvDLc+FZCLNmrMyxrpTvAJ+EkDIoO7BcnYlF0YJd3c2y3lXqjOEA59x1d5L4XxIlYZ745+b5LcJ4iztI6dAI=
*/