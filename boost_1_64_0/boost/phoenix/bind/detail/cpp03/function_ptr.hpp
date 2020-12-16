/*=============================================================================
    Copyright (c) 2001-2007 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !BOOST_PHOENIX_IS_ITERATING

#include <boost/phoenix/core/limits.hpp>
#include <boost/phoenix/support/iterate.hpp>

namespace boost { namespace phoenix { namespace detail
{
    template <int N, typename Dummy = void>
    struct function_ptr_impl
    {
        template <typename RT, typename FP>
        struct impl;
    };

    template <int N, typename RT, typename FP>
    struct function_ptr : function_ptr_impl<N>::template impl<RT, FP>
    {
        typedef typename function_ptr_impl<N>::template impl<RT, FP> base;

        function_ptr(FP fp_)
            : base(fp_) {}
        
        using base::fp;

        bool operator==(function_ptr const & rhs) const
        {
            return fp == rhs.fp;
        }

        template <int M, typename RhsRT, typename RhsFP>
        bool operator==(function_ptr<M, RhsRT, RhsFP> const & /*rhs*/) const
        {
            return false;
        }

    };

    template <typename Dummy>
    struct function_ptr_impl<0, Dummy>
    {
        template <typename RT, typename FP>
        struct impl
        {
            typedef RT result_type;

            impl(FP fp_)
                : fp(fp_) {}

            RT operator()() const
            {
                return fp();
            }

            FP fp;
        };
    };

    template <typename Dummy>
    struct function_ptr_impl<1, Dummy>
    {
        template <typename RT, typename FP>
        struct impl
        {
            typedef RT result_type;

            impl(FP fp_)
                : fp(fp_) {}

            template <typename A>
            RT operator()(A &a) const
            {
                return fp(a);
            }

            FP fp;
        };
    };

#if !defined(BOOST_PHOENIX_DONT_USE_PREPROCESSED_FILES)
    #include <boost/phoenix/bind/detail/cpp03/preprocessed/function_ptr.hpp>
#else

#if defined(__WAVE__) && defined (BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
    #pragma wave option(preserve: 2, line: 0, output: "preprocessed/function_ptr_" BOOST_PHOENIX_LIMIT_STR ".hpp")
#endif

/*=============================================================================
    Copyright (c) 2001-2007 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
    #pragma wave option(preserve: 1)
#endif

#define BOOST_PHOENIX_ITERATION_PARAMS                                          \
    (3, (2, BOOST_PHOENIX_COMPOSITE_LIMIT,                                      \
    <boost/phoenix/bind/detail/cpp03/function_ptr.hpp>))
#include BOOST_PHOENIX_ITERATE()

#if defined(__WAVE__) && defined (BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
    #pragma wave option(output: null)
#endif

#endif

}}} // namespace boost::phoenix::detail

///////////////////////////////////////////////////////////////////////////////
//
//  Preprocessor vertical repetition code
//
///////////////////////////////////////////////////////////////////////////////
#else // defined(BOOST_PP_IS_ITERATING)

    template <typename Dummy>
    struct function_ptr_impl<BOOST_PHOENIX_ITERATION, Dummy>
    {
        template <typename RT, typename FP>
        struct impl
        {
            typedef RT result_type;

            impl(FP fp_)
                : fp(fp_) {}

            template <BOOST_PHOENIX_typename_A>
            RT operator()(BOOST_PHOENIX_A_ref_a) const
            {
                return fp(BOOST_PHOENIX_a);
            }

            FP fp;
        };
    };

#endif // defined(BOOST_PP_IS_ITERATING)

/* function_ptr.hpp
NBaa02gvvGwptKj0eOKzQq5trq9lCvVUsVZKkqhOTZIQWtY1Mu2mUqaE/c1UNXmw1bZxXRLXU8HiqVqseMmJSSq9bu+11jorlazUi6jVNI91ubi3j3n0dMeBquTZmysUKl4xn/LjxVNVYItW9wGJrSWzxZpXQQskrSE2SDSu579hmQbXmsqIzVmtY5h3hjhq55a2QU/id5Vvf9NpaWACGHvwtsVRdFjpU+L+zNJoDHaPxiYx6es6OPFaGeO+Usmgb+eSviWh5eL+Aax8+xpezykvjfkU2dywaftGfxCASYc2ELtIaAi1CZZkPudea/ePci5dLXnZisUHpphKi7059BLfbNHymHHy0mvtMaBRLZbKlWwx6a91kBj8MNrCSB2FK9LzBjtoKK0DWpbVr5NlKiSLlXSxlC4UIAvSkuVKbr60CEKBZobU9lFS1E1R8knXk17GK2bz+VJUmYKdRIz+sM6pVIbPmMWnlqyUU5lUHp04XMfBxppgI+U58jq7reoYfwrVTC6Wj2wzIc+nXmfbhOVUutEo5wvz8KGny9UOJY+td1h8KqjnVCabyf/f8qx+veSTT2aztUq+lkvF85HTEsuTfb2tg+lqpZ7PFYrz8FHrp1CfGH69XT+FWqmUqWMEi293Lpgo1xGLD+b8Si1VK1bn1R+uaC7XLbY8sJ1L5XSxEsHH6aQo4qiQ54LDJwu7uVxqRJYr2IvGXzJb21Nsy6w8Ys9FtQZuDDSq+TAf7mBUyZu1LL1HbF3OlMvopbVwm0eJ0mJZdluylJI1L1Op5KphPiFREm0ty4Ejdv8s5eulYrFQC/OgZorpn++0+DSSGZihmFAaEfVCDDbT4YBts5w+Yo879Uamnitm6mE+kQMG90+nXNVGupArQY/n1Ztwf1j2Bkse6HE6ky/XI+Uh/aU2s+VZT3yoP2C9ValmM/XUZeQJagl8tO26y5IHd2BS9Vo9l4vk49qvbtlmLV4wArJ1DzdgCrF1TYOGO+fc9AZbn4ulqoeJNxWvQ3IsZD5n3+Cs19OpfK1eaMTziR6bLzny1KuNcqkUHgojRox9KJep66432jZawSvUq9UyKgosNgY8SPso9UFHq8V8avFKw9ZQt6yKGeJF1RzNDHWU0nbb4VdYexDpUipdzOE60MzEsydw7dg3TkiNjU00JfPekqnVSsV01ddg7DgH0EGNPSCxvfm8l89X843kQF/doyIxdtbCpjPVMlbr1eTAU/oHQthDFjaXrjfgalgDNtMfwh6xsMVCKlWu1pQMEdhjFjaTLxQrGHmAjZDhuIUtZFQfLCgZIsp2wqqzcsHzaulaNumpowqypk39nrKwuXqpijEio+q3UXGxn7JkaJQapUoKPQ71UNQyGOxpC1vLplNeFkMHyhbG3mrXQ6qRy1QwuwGbCWFvk9jN1SzWculsVWErOQIb7Dm7zjzYFZWSp9qiL8T3vIOt5Ku4/qb4Zg324YS9YGGr6Rqmi7qqhoxdX3OWrFhMpTPlek4Bw7JesnjCkCqXvWpZYXeGZE28SfLNlr1KDX3bF6Df5bvMwnq1uocRNwssDmVc7Aobm05XcpmaqtsIvqttGXJZL1/NZoGN4Nslsb0IcaM2q5TuFsPtsM7C1r0strZgmUKGsN50W1gvV2uksmmljxE6ttXCpovZCowo1WgROpa0ylasFkpFGhvC7Va0y1aqqZ07xTdCxzwHW6zmalgqgW82hN0FrNQHKCM0QtVDWN49lryNbDmNm6V+nZG8QndHCEu6C3PJK/lNvNMZdy2eiKvUyFe9XDKLdiAk53/AwsKIg8txCdinRGBnJXZLNZXP54uVQnJHvfKUujveHJLYx+EVEgRGKlSTcCE=
*/