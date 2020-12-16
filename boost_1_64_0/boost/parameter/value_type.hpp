// Copyright Daniel Wallin 2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_VALUE_TYPE_060921_HPP
#define BOOST_PARAMETER_VALUE_TYPE_060921_HPP

#include <boost/parameter/aux_/void.hpp>
#include <boost/parameter/config.hpp>

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
#include <boost/mp11/integral.hpp>
#include <boost/mp11/list.hpp>
#include <boost/mp11/utility.hpp>
#include <type_traits>
#else
#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/apply_wrap.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_same.hpp>
#endif

namespace boost { namespace parameter { 

    // A metafunction that, given an argument pack, returns the value type
    // of the parameter identified by the given keyword.  If no such parameter
    // has been specified, returns Default

    template <typename Parameters, typename Keyword, typename Default>
    struct value_type0
    {
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
        using type = ::boost::mp11::mp_apply_q<
            typename Parameters::binding
          , ::boost::mp11::mp_list<Keyword,Default,::boost::mp11::mp_false>
        >;

        static_assert(
            ::boost::mp11::mp_if<
                ::std::is_same<Default,::boost::parameter::void_>
              , ::boost::mp11::mp_if<
                    ::std::is_same<type,::boost::parameter::void_>
                  , ::boost::mp11::mp_false
                  , ::boost::mp11::mp_true
                >
              , ::boost::mp11::mp_true
            >::value
          , "required parameters must not result in void_ type"
        );
#else   // !defined(BOOST_PARAMETER_CAN_USE_MP11)
        typedef typename ::boost::mpl::apply_wrap3<
            typename Parameters::binding
          , Keyword
          , Default
          , ::boost::mpl::false_
        >::type type;

        BOOST_MPL_ASSERT((
            typename ::boost::mpl::eval_if<
                ::boost::is_same<Default,::boost::parameter::void_>
              , ::boost::mpl::if_<
                    ::boost::is_same<type,::boost::parameter::void_>
                  , ::boost::mpl::false_
                  , ::boost::mpl::true_
                >
              , ::boost::mpl::true_
            >::type
        ));
#endif  // BOOST_PARAMETER_CAN_USE_MP11
    };

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
    template <typename Placeholder, typename Keyword, typename Default>
    struct value_type1
    {
        using type = ::boost::mp11::mp_apply_q<
            Placeholder
          , ::boost::mp11::mp_list<Keyword,Default,::boost::mp11::mp_false>
        >;

        static_assert(
            ::boost::mp11::mp_if<
                ::std::is_same<Default,::boost::parameter::void_>
              , ::boost::mp11::mp_if<
                    ::std::is_same<type,::boost::parameter::void_>
                  , ::boost::mp11::mp_false
                  , ::boost::mp11::mp_true
                >
              , ::boost::mp11::mp_true
            >::value
          , "required parameters must not result in void_ type"
        );
    };
#endif  // BOOST_PARAMETER_CAN_USE_MP11
}} // namespace boost::parameter

#include <boost/parameter/aux_/is_placeholder.hpp>

namespace boost { namespace parameter { 

    template <
        typename Parameters
      , typename Keyword
      , typename Default = ::boost::parameter::void_
    >
    struct value_type
#if !defined(BOOST_PARAMETER_CAN_USE_MP11)
      : ::boost::mpl::eval_if<
            ::boost::parameter::aux::is_mpl_placeholder<Parameters>
          , ::boost::mpl::identity<int>
          , ::boost::parameter::value_type0<Parameters,Keyword,Default>
        >
#endif
    {
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
        using type = typename ::boost::mp11::mp_if<
            ::boost::parameter::aux::is_mpl_placeholder<Parameters>
          , ::boost::mp11::mp_identity<int>
          , ::boost::mp11::mp_if<
                ::boost::parameter::aux::is_mp11_placeholder<Parameters>
              , ::boost::parameter::value_type1<Parameters,Keyword,Default>
              , ::boost::parameter::value_type0<Parameters,Keyword,Default>
            >
        >::type;
#endif
    };
}} // namespace boost::parameter

#include <boost/parameter/aux_/result_of0.hpp>

namespace boost { namespace parameter { 

    // A metafunction that, given an argument pack, returns the value type
    // of the parameter identified by the given keyword.  If no such parameter
    // has been specified, returns the type returned by invoking DefaultFn
    template <typename Parameters, typename Keyword, typename DefaultFn>
    struct lazy_value_type
    {
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
        using type = ::boost::mp11::mp_apply_q<
            typename Parameters::binding
          , ::boost::mp11::mp_list<
                Keyword
              , typename ::boost::parameter::aux::result_of0<DefaultFn>::type
              , ::boost::mp11::mp_false
            >
        >;
#else
        typedef typename ::boost::mpl::apply_wrap3<
            typename Parameters::binding
          , Keyword
          , typename ::boost::parameter::aux::result_of0<DefaultFn>::type
          , ::boost::mpl::false_
        >::type type;
#endif  // BOOST_PARAMETER_CAN_USE_MP11
    };
}} // namespace boost::parameter

#endif  // include guard


/* value_type.hpp
WAlj4DmYBn+Ay+AFeD/8CW6GF+F2+Ct8QbZflO098De4D7p5YIcB3eFHsDY8Bb3gL9AHav1NQ9gI+sF20B862kfxc/byHmDSPr6WejsNPeA3sDH8Fl4Dv4Mt4FkYDr+H6n4JXifb+rz6dufz+RvkuvsgrAMfkutvPvKVcLMkXEO0UsLZ8FcLzoM+cAFsDxfCrnCR9GuLoZafJXAIXArHw5vhjTAXThL3qeIeL+4zYQ5M0bYlX0Va3iRfqyRf/mij5Gul5OtWydcqydft8Fp4B+wD75R85Um+7oKj4d1wArxH8pMPE+G9cA68D2bD++FiuBbmwnXSP6+Gt8m2/ry7xJ7fNib3eTlSzwuhL1wMg7VykOcOS2Fr2dbv80qc1+eLUp8vSX3ugo7511wJN9pk/vVIQ/v5fRQ2gMdgL1gOB8K/w+HwIzgCHoejZFt/TlzifDzeXPIVBhvCFlBvn887v289I/M2/5Tntmeh/txHwnmbzZ80lPkTeS49UPK5Uwv7/OXjigD5ruY75XnEWugJ74dest0Nrod94AaolceD8nziIZgMN8I0uAla4cPQBgvgLRLuPrgFroN/hQ/AR8Vu7DG4RdyL4ANwq2zr940vOD/uXnL/11vu//oY7v/CJFyQST/xgNznr4dauAdhA7gJNtSOC+rt+QXn9ifbxX6jROw3nhf7k51ix7EDNpZtR77iq8nXo5KvxyRfhZKvIsnXFsmXFeVKPGNM7JFelHrdI/W5Dyp7FtgGlsLe8DUYAV+HQ+EbMFL8j4SvwijZdpRHhaTb1qQ8bpZ0cyXd5dAfroCt4CpJf7UhPt8d9vhamsR3p8SXB4Pg3bAZvAc2h3fBFtq2xBeNIiS+vhJfHTRU4tsm7eUp6AWflvm07TI//SzsCZ+DfcTdcT+QL/GGmNwPvCPt4BhU79eCwfB9qD9nlvDBJu347xL+OGwKKwzhKqoJd0LCfSbhvjSEs+x0dt7AemJPB+vBtlA/36oJ10HCdZRwnaBujyfhfEzud16Rdl0q7Tcej+Hiv5fcT3ZAMTL+SvS2X59TYV2YBtUaKlgfZsIgaIXdxL0nnA8j4AI4HObAkXAhjIWL4Sx4G5wP74VL4Dp4M3wA5sP1cJ3E+wDcIPdHm+DT4v4MfBi+DB+BB2AB/Bt8FB4Tf+/Bx+Ap2f4SFsFK2T4Ht8Kf4DZYy83u7g6fhl7wGegr7n5wO2wMS2Ab+ALsDHfCnuLPUS+lLzq3kzwm58O7xucy4j/CpP6TxN4mGV4PU6Cjvw17yfnzzlc9xE4PesN9MATuh9fCg7A7fAv2kO1esq2PA15y3i43yXE8LP3AI4bjyXUaDjaU8wCq8wDqdm8SLvSK6xKU9jwQ+sORMAiOgk1lO0S2HePfUomvq8n4t5PE1xU2gt0knh5i195b5p37yjxjP9gR9oRdZNtRD5ZdzuvhsNTDUamHY1IP70k9lEs9fAB7yHYv2XaUS/Qu5/aMu+R6tFv6wz3SD5aKPeMrMFC29ec7u5yXc98GMi8M/eF1MEjbD5vC/jBEth3xFVQTXzeJr7vE11Pi6wVVecMQ2dbPh13Ox5+h0u6uEbvJZkY7wmrCTZB6iIFauImGdn5ml/P2Wk/aibeMD3yk3qNVoct5a9Lvpcl5Oxc2gBmwLcyEHaEVXgdvkvM6y5Cf6N3Ox6ufS3l+IePVU8bn0NWEe1/ClUu4D6DjOPJ3O++/X5Dy3iH9907pv/dI/71L+u/d0n/jrp8XFRLvtSbnRUu5L2kF62j5hHVhe6iuC7CdbLeX7a6y7Wh3YXvs8XcwaXedJP4usKWWB7nP6QbbwHCJt5vEV4biJb7DEl8TtNdh3ynjIg5CnafusC8=
*/