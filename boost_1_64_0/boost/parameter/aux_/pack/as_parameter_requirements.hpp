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
lxN6EPc98Lklc/dX3c1tu4HMOZSNe/qxevpZVzALH7C9BYBYVCjap5BdxQnwKKG9MOVIjT3l5BkHTvyfAPjjRbeCVJAA7H5zYCLdMjdQsVndEz35PFjjnkZFOLkWF12nKhzaGKt+bLEKARsAaQ1G7jPIlmiVkZozlfq3gkC5Karm24dAFMwscJ6aGiT5St9dPNBvi34Js45ihldo1CEEcd3cKWcwPHH0yedR4qEdY+XcfZD5Db2Tp9eFeKuT7+Zt4iZkU5yKDIqSXvaSU99A6h0P8yYPQe6ZaivMHrMcqk/t0SxYT5ynkeBeA6sJvcIX1hJ4kzc1jcUV5mcBQiW+WUkSioRf+g7PQkwwPP2Iw3IxfnMq4//baj4z3j3hoqzIAafiKLAPbO+2E20nsIW7O7crzpTp7QrfSRF3LEOqKq7wX3RINefYpfMzHOjFB3mWXxlrlxgM7RnYfgk0OgM98UMs4a475/BvsF0cSbLFTREIw3pTb0W8IJ24jDB69YxJdnOzRYBTv1riYlpyivS2XAitbB8Wn1EnT6+tzAXH677wbXVgUGQI3hHv3A==
*/