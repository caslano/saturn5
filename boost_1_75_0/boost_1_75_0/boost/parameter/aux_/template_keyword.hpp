// Copyright Daniel Wallin 2006.
// Copyright Cromwell D. Enage 2017.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_TEMPLATE_KEYWORD_060203_HPP
#define BOOST_PARAMETER_TEMPLATE_KEYWORD_060203_HPP

namespace boost { namespace parameter { namespace aux {

    struct template_keyword_base
    {
    };
}}} // namespace boost::parameter::aux

#include <boost/parameter/config.hpp>

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
#include <type_traits>

namespace boost { namespace parameter { namespace aux {

    template <typename T>
    using is_template_keyword = ::std::is_base_of<
        ::boost::parameter::aux::template_keyword_base
      , typename ::std::remove_const<
            typename ::std::remove_reference<T>::type
        >::type
    >;
}}} // namespace boost::parameter::aux

#else   // !defined(BOOST_PARAMETER_CAN_USE_MP11)
#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/remove_const.hpp>

#if defined(BOOST_PARAMETER_HAS_PERFECT_FORWARDING)
#include <boost/type_traits/is_base_of.hpp>
#include <boost/type_traits/remove_reference.hpp>
#else
#include <boost/type_traits/is_convertible.hpp>
#include <boost/type_traits/is_lvalue_reference.hpp>
#endif

namespace boost { namespace parameter { namespace aux {

#if !defined(BOOST_PARAMETER_HAS_PERFECT_FORWARDING)
    template <typename T>
    struct is_template_keyword_aux
      : ::boost::mpl::if_<
            ::boost::is_convertible<
                T*
              , ::boost::parameter::aux::template_keyword_base const*
            >
          , ::boost::mpl::true_
          , ::boost::mpl::false_
        >::type
    {
    };
#endif  // BOOST_PARAMETER_HAS_PERFECT_FORWARDING

    template <typename T>
    struct is_template_keyword
      : ::boost::mpl::if_<
#if defined(BOOST_PARAMETER_HAS_PERFECT_FORWARDING)
            // Cannot use is_convertible<> to check if T is derived from
            // template_keyword_base. -- Cromwell D. Enage
            ::boost::is_base_of<
                ::boost::parameter::aux::template_keyword_base
              , typename ::boost::remove_const<
                    typename ::boost::remove_reference<T>::type
                >::type
            >
          , ::boost::mpl::true_
          , ::boost::mpl::false_
#else
            ::boost::is_lvalue_reference<T>
          , ::boost::mpl::false_
          , ::boost::parameter::aux::is_template_keyword_aux<T>
#endif  // BOOST_PARAMETER_HAS_PERFECT_FORWARDING
        >::type
    {
    };
}}} // namespace boost::parameter::aux

#endif  // BOOST_PARAMETER_CAN_USE_MP11
#endif  // include guard


/* template_keyword.hpp
HvwCdzwHKCjwBn6v3J8FLI7mhLht9zm6ssmIXF2NFKiSa20d19qer8X0JBfd03iMLB/xedcOIe40XyapdidIxFUlPQ4vWDWFUMI8eZLGmXrax6GLjKuhYtyjGw+bbnvup1ZiNaSgXv29AVZvyBtS/JEbWYPDdPct+RD6wtKSmrTZG11TVYS0i+TZpnd/8i0uVBnm23le/Euy8VeiWq7JgdMNAgBqVeo//0P0nOXq68HsWxr3dAmGVblCY722a3HoGo+fd6n0qDnz+nwSO+0BSOmrW21Cb0Nten07DVz5XrzHTc45XZTILVlRRB7SzJ1UkNHYkl7vSTMjfU1kiFmL5lZc21A8ZxoqxcdZAE3Hfy/PRdrbgk6dxntZ8rksVmdcqovjxCivb+xS+/gxD14q1V81h1iZc2PUuTD9leuoJoKZH1kXXq/ZR3Hl6LLpQa2iI545aww9UJsUwzm3I1PDxCqRGzr/GPR7avf8A6yReOzKgAp40RPCLDKYZAl1T/g5/QTnphz9RvqALTShWsys1syTimALjMy3OvoFcn69kVQCzn+H2HBOqoeInUtDVJyVoJPHi2YNCGvESMjJnzIt8hVGzlpaU7jTc92gxtUVzmYaBwRvmjO2kXHeEe/FF1AeWPaQcVaV0wSRLAUosTcxtlZyaHQasmTmBULdxNr3GGcTU+jaWHSgWEqndLekxPvDtyL08fRKu+9NKd77
*/