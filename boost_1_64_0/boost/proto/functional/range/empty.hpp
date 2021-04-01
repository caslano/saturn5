///////////////////////////////////////////////////////////////////////////////
/// \file empty.hpp
/// Proto callables for boost::empty()
//
//  Copyright 2012 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_FUNCTIONAL_RANGE_EMPTY_HPP_EAN_27_08_2012
#define BOOST_PROTO_FUNCTIONAL_RANGE_EMPTY_HPP_EAN_27_08_2012

#include <boost/range/empty.hpp>
#include <boost/proto/proto_fwd.hpp>

namespace boost { namespace proto { namespace functional
{

    // A PolymorphicFunctionObject that wraps boost::empty()
    struct empty
    {
        BOOST_PROTO_CALLABLE()

        typedef bool result_type;

        template<typename Rng>
        bool operator()(Rng const &rng) const
        {
            return boost::empty(rng);
        }
    };

}}}

#endif

/* empty.hpp
td21u8lEtdmyGNJd6y9V0pu5YH5NcnchxfHWDZeNupbsILrc+nkW5rUEyFCHnszekX/AYqYXmlYXBDqMSwpn4YxXxRuruAw7tXEQ/ymcxgpYrT65nGjx5/r6Gt51aGWA1DWSJ1FE+lomKgiSPeLOF7obHItz6cAvX+c7+OYraQkOLRCWHUBdgIzUD7XOxeDpvZEvt4E5PmZpgL4ZbTONW1c425wAXTwhKvrOFokrQgNFkei1zeUZv3RJzHpLZgePA+mKt18zTx4UGX+aV6nWTSBsg5uVeeN2dDg7p1DWYT3Hm/t5+qOJ3xQRQnbbsNwQi6VGne1/Tn4U/mDZUNQR4zaeDrq9JvHVaaFuvoV4116vybj4097rL2o4Zqj/M6FZbPZKqLfVxKACSDXKysOZBgc8aqGnFUcII136UVyAbVSobaDJo3AF9O209ImGvILKecULRwE7TYnHDTtMvGxNcJXoqbenGMWz7dxuqq11lNImfxb6hgnvUSaQf/LmeU0PljAEjuP90aqfocaNpiNKyosK8dQ7AY6Kf6JMUmHDi09d+uG11dLmKtwNYw==
*/