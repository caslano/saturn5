/*==============================================================================
    Copyright (c) 2005-2010 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_CORE_NOTHING_HPP
#define BOOST_PHOENIX_CORE_NOTHING_HPP

#include <boost/phoenix/core/limits.hpp>
#include <boost/mpl/void.hpp>
#include <boost/phoenix/core/actor.hpp>
#include <boost/phoenix/core/call.hpp>
#include <boost/phoenix/core/expression.hpp>
#include <boost/phoenix/core/value.hpp>

namespace boost { namespace phoenix
{
    /////////////////////////////////////////////////////////////////////////////
    //
    //  null_actor
    //
    //      An actor that does nothing (a "bum", if you will :-).
    //
    /////////////////////////////////////////////////////////////////////////////
    
    namespace detail
    {
        struct nothing {};
    }
    
    namespace expression
    {
        struct null
            : expression::value<detail::nothing>
        {};
    }
    
    template<typename Dummy>
    struct is_custom_terminal<detail::nothing, Dummy>
      : mpl::true_
    {};

    template<typename Dummy>
    struct custom_terminal<detail::nothing, Dummy>
    {
        typedef void result_type;
        template <typename Context>
        void operator()(detail::nothing, Context &) const
        {
        }
    };

    typedef expression::null::type nothing_type BOOST_ATTRIBUTE_UNUSED;
#ifndef BOOST_PHOENIX_NO_PREDEFINED_TERMINALS
    nothing_type const BOOST_ATTRIBUTE_UNUSED nothing = {{{}}};
#endif
}}

#endif

/* nothing.hpp
Tqc6bTjFOe20LmCshWSgDRHSh9Hq+GzOZz2792to1R7ZU6n7tNFnYGXbLrmS4evXMMTRFI5ng2gNGoeJVMJtzXEatBKsedNfoMGoV3zpd2lAl1gFjhmmq1kazjKWj1S+//H8LqS02Zvdk7eth/O29Sfkbes75M30YmNIVm511kep41MMGx7FabfRn9m2QVM20NtdMPgxNFhpC4i4BxXfExn/6eq/E8D6GNfqaxah88CyN7XhwXVvSJqlfuFqgeg+cH0DwB4sDraIfRvKlgSqDlV5t1us+SDQjEbFMx4nhZpycyCr2XYHCxfTFhSrBWmbn8Zc9//4/L343HoEn1v/Lfjc+jPwufU78fl5QdCpOUFTJv5ZIG84aFSSzEkZ4a+/vWpI95tANETNeJTRiNOyS4d5z2nliVo558Oc5WhEnj9PLcw2IXJH8tHRO/4INwty/R8T9ylqyluyxdTy9vHSuG2/8Wzw551/A1BLAwQKAAAACAAtZ0pSFguiZHcPAAB+MwAAIgAJAGN1cmwtbWFzdGVyL3Rlc3RzL3NlcnZlci9nZXRwYXJ0LmNVVAUAAbZIJGDtWnlz28YV/5+fYi1PTIKiRVlxM4lpOZEl2tVYh0dHHE+cwYDAkkQMAiwOUUrs7953LbAgQUnxuO20
*/