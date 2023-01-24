/*-----------------------------------------------------------------------------+
Copyright (c) 2010-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_PREDICATES_STD_EQUAL_HPP_JOFA_101102
#define BOOST_ICL_PREDICATES_STD_EQUAL_HPP_JOFA_101102

#include <boost/icl/type_traits/predicate.hpp>
#include <boost/icl/type_traits/type_to_string.hpp>

namespace boost{namespace icl
{
    template <class Type> struct std_equal : public relation<Type,Type>
    {
        bool operator()(const Type& lhs, const Type& rhs)const
        {
            return lhs == rhs;
        }
    };

    //-----------------------------------------------------------------------------

    template<>         
    inline std::string unary_template_to_string<icl::std_equal>::apply()
    { return "=="; }

}} // namespace icl boost

#endif


/* std_equal.hpp
7DuprvrzaqxtaB0QeJztTFHOaawlXnVPmPFuonNGfUUjUZzzwj1deBfwbP1h1JIWbx9xnth4x1nV9nHQn9mLybfrLR8N+71EPauTCS11EvYvzG1esqS1pam5sam22XN+i6e5trpB++U5n5jVlLccNozjtyrhbGnyLGlxNzTV16qMdnwk1hhcEU7THl7SUlvjcTcuUnE+dhPq1PmPz9y14TBiQCuwFkvwiXmwyVtrq30+SqG+5HCMtavnhyKXotzUogb+0ATUVVVhiEwD/pC7e3kP+07ce5+oZI9EXAB8oWTYYttP6+jo1L5bl5E6Fv7KrXcz0TqJ0jYVIa6+YnLI9GB1B0KvjMc1Gu0y/dxQXyQUCbE9Gu3D0C86Hwv1ecPa+AN+C7VLfLtDwkejvMGJ4A/c03JJIOTpqe3G/IF2XI01TWXLEq19WWMxWcWwwZSF5VoD4mzxyQmYU99839K+xDYEHXcTJynT2+nygbYWPR5yUqZqRQVuMuYtpXBr5NL6QDe1+ti8DRm7JoE2t5/KaLm0OjKX9BAu6+gk1MVv2yOXsq8Gf1kB1En/4rnE0+g29A01r/DMnikYF4VnRi416t1Rinrf834oFOtLGI9nDOrsDE/IR1RwzyUBPy/f4Smwi+Z+l9Si6W3G3pVUZfgvtMdovdHY0sCb84gt0cnrPpSDsfX9k2wMsZfj2ZPleO+4+4XiUH7XRMh4pZbq
*/