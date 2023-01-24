// Copyright David Abrahams, Daniel Wallin 2003.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PACK_AS_PARAMETER_REQUIREMENTS_HPP
#define BOOST_PARAMETER_AUX_PACK_AS_PARAMETER_REQUIREMENTS_HPP

#include <boost/parameter/aux_/pack/parameter_requirements.hpp>
#include <boost/parameter/aux_/pack/tag_type.hpp>
#include <boost/parameter/aux_/pack/predicate.hpp>
#include <boost/parameter/deduced.hpp>

namespace boost { namespace parameter { namespace aux {

    // Converts a ParameterSpec into a specialization of
    // parameter_requirements.  We need to do this in order to get the
    // tag_type into the type in a way that can be conveniently matched
    // by a satisfies(...) member function in arg_list.
    template <typename ParameterSpec>
    struct as_parameter_requirements
    {
        typedef ::boost::parameter::aux::parameter_requirements<
            typename ::boost::parameter::aux::tag_type<ParameterSpec>::type
          , typename ::boost::parameter::aux::predicate<ParameterSpec>::type
          , ::boost::parameter::aux::has_default<ParameterSpec>
        > type;
    };
}}} // namespace boost::parameter::aux

#endif  // include guard


/* as_parameter_requirements.hpp
LljLOFAe+wYKOBvu1dxWOyvQCJ3NWFxslCXFvFnSmbNojb+HtdrSj6GoiBQGSagLwQU0D6jOJUxYxo6/OiCsClkKwzgPHBx3YrF20j8GwBvqmzndFsRNI03966bTxEXUIGZsDjgKY31GzKsYkaQeuJV9P+8SXNjGbQdm491pDvriMJ8E2SW36H6NDgjp3RzClkNHCuAZSCQOfcrdirPFlEhYZWxSdQIsvv63ySop9yc9wDQ81VTqfTkvOFr27GL9xNNV5BOQ8Pbei+Q9vc5XTTWz74I6HjqdvDoZLGo6ZSxaOmhPd/bkvny18ir73I0mYQXi8WRFWDe31H6rmlmXn6mDyDKNXg/VIc/IBDVEQ1AApLLNun3AqOZgdsvICC/OrT/hQFVCNfqYOoZufa4izXC+Lr6ghJCMPEQcKTcov08SIQkc7uhBo9F7F+1TGElL5kVeuq6403hd6S4suvIF41viYqeyICGNE3m1tIENMDsD28aIm91gtD3hYPT2ajN+9Nf1mqAJy0YqusnoC7RrUuEFagMdTTUeahqexb+y8zynTbDdoF/U2Cver7ULTjyBsuWVRE7F8ygab1neuFHvH3SqY6ufZeJdEVQpRUIeoQSKVcZLr5CdPI11mA6HJqrRaN4HVSiOiGrQfZdJh4D8j79pXyIzNtFC9nAse99lLn21/N1aVAWea8A+CDDV/rEIApW/0LwJekcCdY6h
*/