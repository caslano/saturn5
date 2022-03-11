///////////////////////////////////////////////////////////////////////////////
/// \file deduce_domain.hpp
/// Contains definition of deduce_domain\<\> class templates 
/// for finding the domain that is common among the specified
/// domains
//
//  Copyright 2010 Daniel Wallin, Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Many thanks to Daniel Wallin who first implemented this code. Thanks
// also to Jeremiah Willcock, John Bytheway and Krishna Achuthan who
// offered alternate solutions to this tricky programming problem.

#ifndef BOOST_PROTO_DEDUCE_DOMAIN_HPP_EAN_05_22_2010
#define BOOST_PROTO_DEDUCE_DOMAIN_HPP_EAN_05_22_2010

#include <boost/config.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/facilities/intercept.hpp>
#include <boost/preprocessor/iteration/local.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/proto/proto_fwd.hpp>

#ifndef BOOST_PROTO_ASSERT_VALID_DOMAIN
# define BOOST_PROTO_ASSERT_VALID_DOMAIN(DOM) BOOST_MPL_ASSERT_NOT((boost::is_same<DOM, boost::proto::detail::not_a_domain>))
#endif

namespace boost
{
    namespace proto
    {
        namespace detail
        {
            template<typename Domain>
            struct domain_
              : domain_<typename Domain::proto_super_domain>
            {
                typedef Domain type;
                typedef domain_<typename Domain::proto_super_domain> base;
            #ifdef BOOST_NO_CXX11_DECLTYPE
                using base::deduce98;
                static int const index = base::index + 1;
                static typename sized_type<index>::type deduce98(domain_<Domain>*);
            #else
                using base::deduce0x;
                static Domain deduce0x(domain_<Domain>*);
            #endif
            };

            template<>
            struct domain_<not_a_domain>
            {
                typedef not_a_domain type;
            #ifdef BOOST_NO_CXX11_DECLTYPE
                static int const index = 1;
                static sized_type<1>::type deduce98(void*);
            #else
                static not_a_domain deduce0x(void*);
            #endif
            };

            template<>
            struct domain_<default_domain>
              : domain_<not_a_domain>
            {};

            template<>
            struct domain_<basic_default_domain>
              : domain_<not_a_domain>
            {};

            sized_type<1>::type default_test(void*, void*);
            sized_type<2>::type default_test(domain_<default_domain>*, void*);
            sized_type<2>::type default_test(domain_<basic_default_domain>*, void*);
            sized_type<3>::type default_test(void*, domain_<default_domain>*);
            sized_type<3>::type default_test(void*, domain_<basic_default_domain>*);
            sized_type<4>::type default_test(domain_<default_domain>*, domain_<default_domain>*);
            sized_type<4>::type default_test(domain_<basic_default_domain>*, domain_<default_domain>*);
            sized_type<4>::type default_test(domain_<default_domain>*, domain_<basic_default_domain>*);
            sized_type<4>::type default_test(domain_<basic_default_domain>*, domain_<basic_default_domain>*);

        #ifdef BOOST_NO_CXX11_DECLTYPE
            template<int N, typename Domain>
            struct nth_domain
              : nth_domain<N - 1, typename Domain::base>
            {};

            template<typename Domain>
            struct nth_domain<0, Domain>
              : Domain
            {};
        #endif

            template<typename D0>
            struct common_domain1
            {
                typedef D0 type;
            };

            template<typename E0>
            struct deduce_domain1
              : domain_of<E0>
            {};

            template<
                typename D0
              , typename D1
              , int DefaultCase = sizeof(proto::detail::default_test((domain_<D0>*)0, (domain_<D1>*)0))
            >
            struct common_domain2
            {
            #ifdef BOOST_NO_CXX11_DECLTYPE
                static int const index = domain_<D0>::index - sizeof(domain_<D0>::deduce98((domain_<D1>*)0));
                typedef typename nth_domain<index, domain_<D0> >::type type;
            #else
                typedef decltype(domain_<D0>::deduce0x((domain_<D1>*)0)) type;
            #endif
            };

            template<typename D0, typename D1>
            struct common_domain2<D0, D1, 2>
            {
                typedef D1 type;
            };

            template<typename D0, typename D1>
            struct common_domain2<D0, D1, 3>
            {
                typedef D0 type;
            };

            template<typename D0>
            struct common_domain2<D0, default_domain, 4>
            {
                typedef D0 type;
            };

            template<typename D0>
            struct common_domain2<D0, basic_default_domain, 4>
            {
                typedef D0 type;
            };

            template<typename D1>
            struct common_domain2<default_domain, D1, 4>
            {
                typedef D1 type;
            };

            template<typename D1>
            struct common_domain2<basic_default_domain, D1, 4>
            {
                typedef D1 type;
            };

            template<>
            struct common_domain2<default_domain, default_domain, 4>
            {
                typedef default_domain type;
            };

            template<>
            struct common_domain2<basic_default_domain, default_domain, 4>
            {
                typedef default_domain type;
            };

            template<>
            struct common_domain2<default_domain, basic_default_domain, 4>
            {
                typedef default_domain type;
            };

            template<>
            struct common_domain2<basic_default_domain, basic_default_domain, 4>
            {
                typedef basic_default_domain type;
            };

            template<typename E0, typename E1>
            struct deduce_domain2
              : common_domain2<
                    typename domain_of<E0>::type
                  , typename domain_of<E1>::type
                >
            {};

            #include <boost/proto/detail/deduce_domain_n.hpp>
        }
    }
}

#endif // BOOST_PROTO_DEDUCE_DOMAIN_HPP_EAN_05_22_2010

/* deduce_domain.hpp
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
*/