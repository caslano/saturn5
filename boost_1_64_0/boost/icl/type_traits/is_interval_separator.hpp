/*-----------------------------------------------------------------------------+    
Copyright (c) 2008-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_IS_INTERVAL_SEPARATOR_HPP_JOFA_081004
#define BOOST_ICL_TYPE_TRAITS_IS_INTERVAL_SEPARATOR_HPP_JOFA_081004

#include <boost/config.hpp>

namespace boost{ namespace icl
{
    template <class Type> struct is_interval_separator
    { 
        typedef is_interval_separator<Type> type;
        BOOST_STATIC_CONSTANT(bool, value = false); 
    };

}} // namespace boost icl

#endif



/* is_interval_separator.hpp
Ex+IlFbEBmCdphBjWyGaTuyHyQzYehfEZQ5YdCHEZUuw606IrIx+GBhDFLRE83weoq8Jqu6F5piAoNqXgH1fgrjIAWttQVU3GoTBeAIG4qiicSkYFEJUbYFotYGdd6CpUrNqDBHSFOyWiabiRDW3ACvvgei9EmJmCcSREyx7FdhnO5pJFkTpCxDZTlT7PLDpXlT55RB1CyBarrBjgN8IA3I0kTZo4hkQDwlgx+cgcve2xgQGomUZmv2lENvjIXazIYrmo7lf0o0mfhhMQxzlQMzvhKi8Cmy/FGyYAPHRCuLmJDSRyyG2csHSyyA+x6ViQgYRM38AJiporlkQpZkQ03shKpqhee9BNzAaTd2FJpQ3CJMCiHEbuowmEGHpYP2c5piAoTtIh8h9HqJ2IZrEbojAEyA6x0KsngBx9yKa62iI5sYOTELRPVwJlm+GJrYb3UQjNJnNNOhF88rtjUkvmuZYdGtp6PoWQVw2hahZgq7hCojfeRBzz0McZKK5ZHXEJAXd3V50fSc1xqQDorMRuqulaFInojnmoXlnoMtMT8VgHd1m6x6YNKPbyNPXgDDg74uBP5pmJrqFMehe9kCs5kKU7UbXswui/wWIThu6t0UQBy6Iv1aDMflEE99GE2WI+Wx0AyfZMUEdhgkORG/zVEyQIToXohvIao9J4RBMvNC97ehOE2FMaCBK96B7SUPXkICu4DJ0gbsgdrObYPKLbngZxOyLEFknJmCCMgSTW9vx5/hz/Gnws7L/5WOuTh8y66VfNz92x9uPfXrO1knDDrU9NHXt/LOvef28LvetvLfF/kbnLGi3aVFK9+fmtpoYPXdT5LeH35t3V/N3bo4eunnLFv/NH1+asenr7bdsabP3tlbdQ0mf9r13YXTcO/esm/7W4p+rCiaMWlmxPeXunT2brNtx8dRnvz3xwPaMq+96fULJ7uZlvXt3WJTwRM+hp3fud7giKad966HuQi3B93TC+VX9dm29ZFFS5JrbPnn29vGlp94dvmL81jUTAjs6fXLNy92b3/jGokEnfRdefb79lC1rO7UMDDkte3Zmz8c2rhv4SKsuw8bduz83b/eqc74N9Sv/av6yaKjkjuoO1TsXtmy8Y+kvv29a/nkgf+2Pa37e9E31rO22Y3y6PtjrTSq7F3xfd6Py639WzhdUhhvfXnIJlePQxzK/pbLstK/Z41SeN+d1eojKNPGSireoXMc0brKGynZTKOyi8l26/uNcKuMPH/39dSrn0JILv6Gyfvj6U86i8h7UbkcPKvMVZ/hfonJ/ZdyhW6nsP+qRN5TK/7HXl15BdeBbdf9sqofKxmdOpbpY8PGdQaqP1351PkN18pi77QKql/veL/2K6sae+mhfqp+zT/91JdXRxyd9vYnqaeuyu0dSXfW4K+Faqq/Q/CYHqM7CwZMSqN4O939lLNXdGbvOmE7192WfbdOoDt9/5LpbqB7fK3noCqrLu9fPHkH1+dcHv8ygOj1r0PwOVK/eJoeyqW4bJY/ZSPV79Q0/7aM6Tt5U2JzqObHg6zeoru33+CZSffdxzJpMdb7h5adTqd537ntlA9W9+z7nBKr/Gz+/6n3igbszb/6A+KBk2q7niRf2XO78iPhB+6hkNvHEmg3r3yC+OLz+63OJN2b075hG/BG57+BtxCNfDPOeSnzS67SSbsQrnz4z/z3il5Nrtq8nnjnTHfmI+GaV54zPXhzVc3eLrZtP37Hh0pdP+/zAC2/Mfeuz6peDX12cN/f7p0IdI/eWHWx+58qdtz8/tyThwdY/b2q68uy2nTO6tB904qzOC+c27fb97Ld7Xdt9x+gL79udunHTrpMTNt06Iru1fdW2sj+kPT4=
*/