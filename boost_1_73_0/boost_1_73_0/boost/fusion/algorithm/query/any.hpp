/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005 Eric Niebler
    Copyright (c) 2007 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_ANY_05052005_1230)
#define FUSION_ANY_05052005_1230

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/category_of.hpp>
#include <boost/fusion/algorithm/query/detail/any.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence, typename F>
        struct any
        {
            typedef bool type;
        };
    }

    template <typename Sequence, typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline bool
    any(Sequence const& seq, F f)
    {
        return detail::any(seq, f, typename traits::category_of<Sequence>::type());
    }
}}

#endif


/* any.hpp
zuMgHgexThJ9vKwPH/X0qUxmfXhP1ac4INJTx4RPgH4C9A8lXZDKCvhIu4ArFHCFAq5QUJyzj6g9isKTUHgSCg/a5sxTIJ4CscWW+BGIH4F4ypbYBmIbiGckoaw0NCQYxI9B/BjEzyxpDFTS2A5iO4idlrJSiadBPA3iV5JQ+kZ1zPYMiGdAvGpL/ATET0C8LgkxCk7no2AfC26Qo+AjCrkD5A6Qe3okP1PIZ0E+C/LPPZK9lfreBbIL5HuW88s=
*/