/*-----------------------------------------------------------------------------+
Copyright (c) 2010-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_PREDICATES_ELEMENT_EQUAL_HPP_JOFA_101102
#define BOOST_ICL_PREDICATES_ELEMENT_EQUAL_HPP_JOFA_101102

#include <boost/icl/type_traits/predicate.hpp>
#include <boost/icl/type_traits/type_to_string.hpp>

namespace boost{namespace icl
{
    template <class Type> 
    struct element_equal : public relation<Type,Type>
    {
        bool operator()(const Type& lhs, const Type& rhs)const
        {
            return is_element_equal(lhs, rhs);
        }
    };

    template<>
    inline std::string unary_template_to_string<icl::element_equal>::apply()  
    { return "="; }

}} // namespace icl boost

#endif


/* element_equal.hpp
Da92LySd77OtDoABXoeF8tyFoEKmPZuFTxkz0zwm0MSNEH9RdiCoosJkxLRayAdSj6vOs/p63Th1ISJwZmEk7Uv4/lP/af4tjXE0SPVcpov8OP3/JsRki+MylVHk2YDzurX1GY2ewVuGW2Xf/GFcLRQgDgFYIqgOTfJ3mb14vxPdQSYTfeMOYtrMMNluUN4kKK6UtJoknBR6x9s+fsIekIe+U1G+o/fPDvUjU8KY6eEKQu43ZaQ9xj3HjC7K6UOFfioG9BrIJleyyv1dYTwcskISpheOnKFP/A9GhUlSdMPvlqIMktfGUseOMR0YFU/nDpc7XblUTbJXp70vNFPFqKtCE4FmqsF1bMIfKXmMbudJ73QaHI1hM5B/+zjRHO8o35dWN5RZdPJSkAvmj05nWizwQz+jg9ovc+kCtMFa0RTzezNxbAOedRMmvic1b6ul7xUHByBP3sHcDa4NIENQ2wD3wezKKy+AEofYvsfWRYQPkMR3dzMEG1whYYx0EV16FtuRi/cnvs2AL0QJ9VbMcDPAV13w8zricEYoICjkEEeJ9QBpyNfmF+w4uQ==
*/