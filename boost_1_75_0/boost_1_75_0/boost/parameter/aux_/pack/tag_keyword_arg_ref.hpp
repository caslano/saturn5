// Copyright David Abrahams, Daniel Wallin 2003.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PACK_TAG_KEYWORD_ARG_REF_HPP
#define BOOST_PARAMETER_AUX_PACK_TAG_KEYWORD_ARG_REF_HPP

#include <boost/parameter/aux_/unwrap_cv_reference.hpp>
#include <boost/parameter/aux_/tagged_argument.hpp>
#include <boost/parameter/config.hpp>

namespace boost { namespace parameter { namespace aux { 

    template <
        typename Keyword
      , typename ActualArg
#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))
      , typename = typename ::boost::parameter::aux
        ::is_cv_reference_wrapper<ActualArg>::type
#endif
    >
    struct tag_ref
    {
        typedef ::boost::parameter::aux::tagged_argument<
            Keyword
          , typename ::boost::parameter::aux
            ::unwrap_cv_reference<ActualArg>::type
        > type;
    };
}}} // namespace boost::parameter::aux_

#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))

#include <boost/mpl/bool.hpp>

namespace boost { namespace parameter { namespace aux { 

    template <typename Keyword, typename ActualArg>
    struct tag_ref<Keyword,ActualArg,::boost::mpl::false_>
    {
        typedef ::boost::parameter::aux
        ::tagged_argument<Keyword,ActualArg> type;
    };
}}} // namespace boost::parameter::aux_

#endif  // Borland workarounds needed.

namespace boost { namespace parameter { namespace aux {

    struct tag_keyword_arg_ref
    {
        template <typename K, typename T>
        struct apply
        {
            typedef typename ::boost::parameter::aux::tag_ref<K,T>::type type;
        };

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
        template <typename K, typename T>
        using fn = typename ::boost::parameter::aux::tag_ref<K,T>::type;
#endif
    };
}}} // namespace boost::parameter::aux

#endif  // include guard


/* tag_keyword_arg_ref.hpp
1WHSZjDQjrxRnDaBN5MqDITTN6g9RuLzDUzaGKlDx9qtcxMCxO/uTFt1juj2K+MhDsTbPDgXOm0MyRFbWLzcO3S1QA6DkgjUslRLpgBDU6xWIa5ADfFSoqjUV9kKzZdJF5V0BTkVy8MaIscCBkySG1gaWkERTagPGjtrmNVitRm/LQlCEf02GLreSKYCbInVkU+oEieCbQZlWfupi13ii3JZgb7b6lsA7WfREmJtOybXUY3GlojayBavTG6cR+VUJg5BrhSkS15l5yujzDLr/R58u60UC9tnZyNoV6cq3JtbquZ3xLRyWsTFiKTOz17bPXB031H1gNcPzUVeTWxR9nAn+SGmxAkp4bw7HVN9nA0jhcUdnn47okvdTeKmUjif23mn4pBWpBfbyrfd6LnHt7TMThs085S9d1nSE+dkkJenrk3h500t6Rw9efR52xMWesXujPiTOi+9lF88EpCyBPfuBOJ4y/RgvhSSpHh/for6pPyqsyCwLVNvf7hsgtXLSl/rp7NVe4pjiuBIDdssmIC1tiM3ta1EX+6R4OBw5D7srK/l1GAQqvrSqN6rN6rKpB9jdFV3+gIAItxo9DsX1kPDygWHeBY0oqTyid8xtXtNA9x/nIUTNhYqCzblG9EDEsI+4T/5YPHAcQFpiJCucH44h3enrM/1I6e/eJFd+tb7qBgpNmsodRHOkoyUYN6E1K/EqW5rsuG3/oRo
*/