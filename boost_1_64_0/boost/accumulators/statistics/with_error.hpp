///////////////////////////////////////////////////////////////////////////////
// with_error.hpp
//
//  Copyright 2005 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACCUMULATORS_STATISTICS_WITH_ERROR_HPP_EAN_01_11_2005
#define BOOST_ACCUMULATORS_STATISTICS_WITH_ERROR_HPP_EAN_01_11_2005

#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/transform_view.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/accumulators/statistics_fwd.hpp>
#include <boost/accumulators/statistics/error_of.hpp>

namespace boost { namespace accumulators
{

namespace detail
{
    template<typename Feature>
    struct error_of_tag
    {
        typedef tag::error_of<Feature> type;
    };
}

///////////////////////////////////////////////////////////////////////////////
// with_error
//
template<BOOST_PP_ENUM_PARAMS(BOOST_ACCUMULATORS_MAX_FEATURES, typename Feature)>
struct with_error
  : mpl::transform_view<
        mpl::vector<BOOST_PP_ENUM_PARAMS(BOOST_ACCUMULATORS_MAX_FEATURES, Feature)>
      , detail::error_of_tag<mpl::_1>
    >
{
};

}} // namespace boost::accumulators

#endif

/* with_error.hpp
Z2dheHi1lLAzPMPFBPp9qwIa+v+T4vbg/bHEPIA9346LjaObakxAWr1MMnT/OGTfd6s8z3in8jxD/mrh/BWeQGiMXzrYPsd02ZWRuV6acbF139WGPnw2cTQOMKxDXxa60vpl7EmA40VLl+R1bS7ZSZd8Crb4yf218LLPfNrnWhMRzMn6w9P4DIfVmIkViJv6t06Uk9Nd1tX36H13pNTRuNVQUbjmPBH99V56pUESpwhJOCN0erKET08eAt00/txIccsQlhyjFbfdkZkQqk5UqvLo05Q6/U8nWMvEbKCoxnfC2JfXd1ea67tRwNZUCqfTfsPp9Go+RALvG8AnPfoHE7khc/iCWSg/oz42rXM314lVnzz+xsCUjVg3TEBOygtnGfZ/k7Ef0JYf+OqWw0utHdPHuAst+njqogPQR03ZAelD9B+EIMSs8+uJ5gFQ458tuye01m9Z96dgCx336jIEWHC6IyheYE7RZ/y4JanIZZwjyixPCX9BMhzBEdEs/JjP2MUK4m5TMYDgX+DazK2n95yBYvNI71l41xD7qn7GCIb4S5AkqXRUkc21JaA3gpzgnoUfzz0zmBfD/eAUuxKxZVrGcEP5wIPrWPUkcPJwMtD8IIYZoRb78xWuordn12vLm9JIlp4kwxbsbRodUvzlCstOUvr5+zrS5v7g3qAdgn7dBWZvXPynFsYCOKVlYwHuE/ZQq4Sz+AbXXXJ6GxCu0ctQ6F8jCv1P5srA/Zi0safoCSOtgUX74EfCMrBO4oF1rTmw9oxg9ZEabpCNRFV9TiYzA5pvW9oLjM6leILYh50dJo86ciO6ZBBf5QqCDNNEHKO4x4KWfcLldAR2+7HcqRNpJG6GHJYPvn2RUQ7RNye2BTkgYX75eobsaxkhUBEKeSAHRLX8ukEMkaEhnm/nhnt8ih+HlFqt3SzhzSncrYu5Ww+L/96D/bXq79njzf6+9g+t+nu3X2tearcUQm9zV2NlM6l3e5297BTp7HXS2T0CLTp7x0+ls7O5s68zOztV4c5+LN7ZQ09sv7OnnGJ2trevdDaxnNdCa2P6ynOt3r2AevfLC7lHRlLvfnt1vHcTpXdNriXdt/VaBj7e6mBYmEj3Snm0Xma+t1/bukOTf/Qv7tD2z8OeHcfdKG6yVHNp5lmwJUFMeUwrdDVU9XgCX+8epYvbYV+SSBZgS6cajbLcuFfpJzRnPow5s59+9XA+7GuEqTqZlySWTyU9X/2sATzG0LcnRUZPpbR1crxGApHBPxHXbGcM5yXYHDLkQaE9kXMcTdPUIZ4ZOVaOdZJjkpVjgb73bE5VytY00DwLaj345max+WHvKD+nWjT1trBEBcvLC00sffWngYXWuIflFK/rP3O+PHms/f5LRTqhfIjZAeX9ahVufKyWl8hquSI1MsIhUydtoG4baAjsJWrpz4yqPilVfX1B/EQzQ39lmFHZg5Yn2dafUvBrxnDBW9LRMY44HXVzMB1VCR0lOJiO+HraQUsfMC2JRILcz1bI/foJw5iSjP7Aski6gojKs+AXgGLCer+fSVgDLHR9BN22kKnhkaavP4uIpDUuIrQjhdDafALZDWyN8c5QvICJ+tz2cWpOkJ/wplbf1NgSagYLa7ZgLQzZDahygZXTcQdx4u+ZBtujx3tGdUSPVXF6dDE9PtUlevylUed1Qo++2+3XbA0s+k70aJDiO+e1lHfgbgcbHT5lo8OKLLwt5rducR53J2t+L6oWAYVnwVyEYegYmZ+Akv0h9m0sJm5A5n+V4CT4vni337CcyJIMz53XIz7UDCLdJ+dnXpKr5S/9ldECzdICI+bHWyCmDxgaJ3bpbi0Fh8nxVPskVYYt1Sr92yE=
*/