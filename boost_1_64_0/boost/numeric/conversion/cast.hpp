//  (c) Copyright Fernando Luis Cacciola Carballal 2000-2004
//  Use, modification, and distribution is subject to the Boost Software
//  License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

//  See library home page at http://www.boost.org/libs/numeric/conversion
//
// Contact the author at: fernando_cacciola@hotmail.com
//
//
//  Revision History
//
//    19 Nov 2001 Syntatic changes as suggested by Darin Adler (Fernando Cacciola)
//    08 Nov 2001 Fixes to accommodate MSVC (Fernando Cacciola)
//    04 Nov 2001 Fixes to accommodate gcc2.92 (Fernando Cacciola)
//    30 Oct 2001 Some fixes suggested by Daryle Walker (Fernando Cacciola)
//    25 Oct 2001 Initial boostification (Fernando Cacciola)
//    23 Jan 2004 Inital add to cvs (post review)s
//    22 Jun 2011 Added support for specializing cast policies via numeric_cast_traits (Brandon Kohn).
//
#ifndef BOOST_NUMERIC_CONVERSION_CAST_25OCT2001_HPP
#define BOOST_NUMERIC_CONVERSION_CAST_25OCT2001_HPP

#include <boost/detail/workaround.hpp>

#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x582))

#  include<boost/numeric/conversion/detail/old_numeric_cast.hpp>

#else

#include <boost/type.hpp>
#include <boost/numeric/conversion/converter.hpp>
#include <boost/numeric/conversion/numeric_cast_traits.hpp>

namespace boost
{
    template <typename Target, typename Source> 
    inline Target numeric_cast( Source arg )
    {
        typedef numeric::conversion_traits<Target, Source>   conv_traits;
        typedef numeric::numeric_cast_traits<Target, Source> cast_traits;
        typedef boost::numeric::converter
            <
                Target,
                Source, 
                conv_traits,
                typename cast_traits::overflow_policy, 
                typename cast_traits::rounding_policy, 
                boost::numeric::raw_converter< conv_traits >,
                typename cast_traits::range_checking_policy
            > converter;
        return converter::convert(arg);
    }
    
    using numeric::bad_numeric_cast;
} // namespace boost

#endif

#endif

/* cast.hpp
UPzhD5hnTxxiM2tnx9HdUJ/nH8qBxa2v/Rz5RT+l34iYrQvdPRv9QtaMmS2VqS7GPUnf1ymPtt6G+shSw/THdV6yPsyqz2+F/ox+RtdtmD3/OKcVxpaM11fzcQf23Aurz3Bs6ifLCtM/y51EloHZP4Pm98D68Dx4mU6yCJj+nCSarCizcc3iZiIHgyW93b4QOSjK9JNFMtvQobUFY2SwDAk9q2N+vtDbiLfu/sjBYIfSfb6A7ZnBFsdY5L0HBks91bkB2zOyzMzexKbLg/wM9njKACtyMFi2014TxuGl3gb5ipZHOw02MeleEfS1waZ8O0++Y4IsPUx/T6Kf7Bwz7/uc47DevqL7qEOkdVr3PCVyf+sQaRGnf27eQ5aFWdXQHj1QH5kVpt+nBsjcrL7fc2dOh7H9KO9JJKPru4Mxl2LIZjFbdCj7GMR9cojKJmnpLzxYhH757BCHeZl3enyAfXGIdczuPK6aFbmLKNGc2YpmzeR1N7IImOG6mylKWGCG+4zJMM+Mv2EqzKUwN9kuLfcGye00f1yK+RkaJdoIaf53w55inQ6LEtuZDelX5k+0MzxKtGb2yMzOucgiYIZ7hsiqMEu4WgX1mVPorUYfxwDMazIvsx8q762JfkkZJbYx6/l6Q1/k8FWUSBkmbeLJ7zojLm0UbeelWZ69aox2kqWF6ee1P63sl1haTru7oD3i0kWJ0cymP7x1C2OUntqi2fe0PDrojdxGkrXK8K/Vp/8rLfjPbcylQlG4vlSPli0n/boDY1s4SowKk2ZrdrU7ci8eRdfEpZn+ee+ClYyi/QOz4q+boJ1kfZiFt8sr33VFtkuzurQ83ivNHKy3paLEWmYJY2fIfXjpKNGW2b1FBZthHMpECVMKabsflZPflY3BXCIz3ENHlj5EWsemx9KhX6pGiZosrsGlnfMQR1aM2dS+uWthXleLEhl43OgQef2TDG0xXvcms8AM173JImGGY32F+RSWqLAkRVvM1YPHRSssVmHxCvMozEeWX5ufyedsr2vW7IG21ERfk+nHPYasCYtL+C9f9wElVZGFAbh6GECG1BM7DKFJkmHIGZogkh1yliZJhgHJIA4ZkTAEBVmEJmdogpKhAQEljkiOjSCSHRUliLqX3Z7/3a5z3t1z9vQy396qulX16oV+/d7qpVWRewOb2sns3u/lMmJsG9vUEWbDLMuOY843RZ+RaecrZLEw7XxFMD/ZweD8bPRmjXxc9z/Ir7lNjVaG9VX7jPcDkUXCtO80yGJhofVZW9jwW5OG9Jmrg3Uv6iNzZzLsUtNZxvNbO9jUCBb3jfc/Z5EfWSRMuzZDFgvTzscEUx1t6mqwX95seHPWn+mF+fK+Tf1hMaz6V8NKIL+uyI9My49sXCbDfirb/Snmbh+b+pjF9Yr+LhX9SWZWprWvTf3KLPPwsd9iDvazqTRm705+dgLbQ3/qM5j2myayWJi2PZDlCdq79Jl1wG2F/iQbxey8/R/jPZMDaF4zq7frn3DYQJuaxiyfzedGnw2yqR7Mvo3fmYi2kMUwczTOWBDzkyw/sxtD1/TB2CbZ1EqLYRM6fTEP/TnEpjqyuC+ytC+NfiG7wOxCm38xDt4PbaoDs2PXKzZBmUPNLVmwNLIGzGrkjDSu0w6zqQXMLOUKP0d9w22qMrO1vx5thjWErDazl/7ixjveySYym9F7oXEtaATNF5g2XwTzkcXCtP2DYGmCWUea15dAFgHTvg8X4jxkZvUlC+Yleydo9enz/udLLmGejbKpeGaNmp8yrpWQ5Wa27UqPNWgL2Upmdb78aCviRtvUZmYjUh5sM+5Ns6kMFsMuzRs+B2WOpeNBZuVuVZ2G8RtnU70=
*/