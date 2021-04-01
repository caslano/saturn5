/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_ITERATOR_BASE_05042005_1008)
#define FUSION_ITERATOR_BASE_05042005_1008

#include <boost/config.hpp>
#include <boost/fusion/support/config.hpp>

namespace boost { namespace fusion
{
    struct iterator_root {};

    template <typename Iterator>
    struct iterator_base : iterator_root
    {
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        Iterator const&
        cast() const BOOST_NOEXCEPT
        {
            return static_cast<Iterator const&>(*this);
        }

        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        Iterator&
        cast() BOOST_NOEXCEPT
        {
            return static_cast<Iterator&>(*this);
        }
    };
}}

#endif

/* iterator_base.hpp
Mk4ppLWZIcpBP/Vp0LsO3TsVbVrRtCVCyDXbZDG+fFOd+GsA6c2YHYDzu0nxjYVLHO/8Km1yzo2g7+RZolQnNN1NlFTM+T7OmfUaLbEZogCTfSl2z1Ch4WMyZkFwkUljwFIH6JbDOrP7ahPvplBaejP/8jImdRUFTwRKtIc6uqtFWz4A+RAPz2WAkgr34BlOtYKGmq5tqZio8dP3a5oeQYPUcPklsql9kLGKCch5Qg/+4m92s3HEmty/6fwRlK/ShjzPofRu46U9wJwNEBUA+PVU7I0mQG4sfBYsuNjlblOs4a8IpkTPklc58cZ310W712p1znI4TBeSEu/9ElB7/P43f3qYxQ/xXRcI3atraGDtcov8qihFk9QIvG8RwfAR8gXeo03xzEE6DKYTYwc0y+gZ0rFmxW8wVEOJarPj60kyt0DFIq8m1GkqeJaQ1nJYIGUACKatD12gMDwV5SKR/mn9WoeoRBZZH7hApqH3Jmy4Nox61JIxTRjn3dCnKmLeUfzbQ76EK4tI7mwBoBqiqKhm4pEHNAELprnHzbHsjAZwsCPgwKGB9J5UIg==
*/