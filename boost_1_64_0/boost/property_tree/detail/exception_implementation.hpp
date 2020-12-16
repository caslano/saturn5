// ----------------------------------------------------------------------------
// Copyright (C) 2002-2006 Marcin Kalicinski
// Copyright (C) 2009 Sebastian Redl
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see www.boost.org
// ----------------------------------------------------------------------------
#ifndef BOOST_PROPERTY_TREE_DETAIL_EXCEPTIONS_IMPLEMENTATION_HPP_INCLUDED
#define BOOST_PROPERTY_TREE_DETAIL_EXCEPTIONS_IMPLEMENTATION_HPP_INCLUDED

namespace boost { namespace property_tree
{

    namespace detail
    {

        // Helper for preparing what string in ptree_bad_path exception
        template<class P> inline
        std::string prepare_bad_path_what(const std::string &what,
                                          const P &path)
        {
            return what + " (" + path.dump() + ")";
        }

    }

    ///////////////////////////////////////////////////////////////////////////
    // ptree_error

    inline ptree_error::ptree_error(const std::string &w): 
        std::runtime_error(w) 
    {
    }

    inline ptree_error::~ptree_error() throw()
    {
    }

    ///////////////////////////////////////////////////////////////////////////
    // ptree_bad_data

    template<class D> inline
    ptree_bad_data::ptree_bad_data(const std::string &w, const D &d):
        ptree_error(w), m_data(d)
    {
    }

    inline ptree_bad_data::~ptree_bad_data() throw()
    {
    }

    template<class D> inline
    D ptree_bad_data::data() const
    {
        return boost::any_cast<D>(m_data);
    }

    ///////////////////////////////////////////////////////////////////////////
    // ptree_bad_path

    template<class P> inline
    ptree_bad_path::ptree_bad_path(const std::string &w, const P &p):
        ptree_error(detail::prepare_bad_path_what(w, p)), m_path(p)
    {

    }

    inline ptree_bad_path::~ptree_bad_path() throw()
    {
    }

    template<class P> inline
    P ptree_bad_path::path() const
    {
        return boost::any_cast<P>(m_path);
    }

}}

#endif

/* exception_implementation.hpp
0WdK6I+uEZvskCJLiSoNegR/Uhs2iBAlxgHH5ChSoc6Atbn5wTa7xDmkxojQn/XNNdhihz2SpMiSp0SVBm16DJlz5i9yIsoxFbqMmbH2V9eHs8Q5oUCHEVNCC+Nnhz2SpMjSoMeQCcHf9MkGEWIc02JM+O/64yzbHHJEhz4LVv9h3GyxR4oMJdr0mDAnWOqPdRIc0GLAkvA/jZHrsM0ucY44oUyTDn1GLFj9lxzYZIckKbKUmDBn5d/6JkaOCi26jJmxZC04R3AdzrLNLvsccUKZDiOmbJ3jHMEeSVJkyVOiQY85G+c8RxDlgDQ5itRp0WXMjPC5zhFcketwljhHnFCgw5QFq6FzBJtssUeSDHlKDFk59zmCM2wQIUqCA47JUaROiy4Dxiy54nnkwTZxDjmhRpM+IX/P6RokyZAlT5s5QVgerBMhSowEx+So0GLAjCXh850jWOM67BJnnyMKlKnRpEOfKaHzqwtb7LBHhixVGvSYEFxAbqyzQZQYaYp0mbEkvKIeXIdtdomzzxEnlGkyZfWC8mCHJBmy5CnRoE2POWcuJAeiJEhTpEKdFmNmLLniheXCLnEOKVCmRp8RoVW5cA022WGPFFnylBgyIbiImrBOhARpjslRpEWXAWPWLioPDjmhTJM+I6YsuOzF9M8eKTLkqdJjTmTNNSBHkToDxiy54sXVn132OaRMjSYjFoQuoT+uwR4pMmTJU6VBmx5DJswJLqkGnGGdCAmK1GnRZcyS8Bn3CdvEKdNkxJQFoUvJh2uwyRZ7JMmQJU+JBm2GBJeWBxFiHHBMkQotuoxZcsXLyIVtdolzyBEFytRoMiJ0WfODa7DJFkmy5KnSZsic4HJqwwYRosQ4IE2ROi0GzFhyxcubr+xyRIEmI6YsWL2CGrHJHkky5ClRpcec4IrqwjobJDggR4X1Da83Va+rYvk0/vucQeJt5qfHU3+z8thzoRt5rbmh15fAsafP+1szu/6OcsjfMM36fw7VjdPXFee7lzz9n+SG/w1TFrOn3io35xt+0WveadsvSXQck3a+se+hBLYFOa9Htuc9V+WK+ou8Tc38bvXEvknbktpn7Re2/ah8rv/+DOX0Bl5XxYJ9G4xta9m34piyGLFt/YZeZ+V34Lkt7Q4teV0251gCf/fpioSuGQquQVx+Zz2uPe3cQfwJ5w5WDs8d7FF/0rmDmOcPOKZMxt8caolD5qz5hZDrUAjUUSw/VW3F1X8Yt7gv1sUeTX8Paypu+XuJcc7Iv+BxWHudK6rtwQ28n4u439TtitrXcG12/H2Ovvbs9HoF5pZ2jDANdv7lOlPSXrH/sdhR55bfS4z7XcAjOpT9vlhFHLhWMX/Lo/c5jz99zuDgY67t++zr/6TsV+z3CufgUC0Pz+kaaq88yzYP9t7uGr3DPBTLYl1MikdvR1yey/Flc/U+5rnHwTvdR+I1GLFmv6ntHQb2LXh8rD0UT/7lOTW5zgP1Qc/c2oraHnHu/78eJxkG5v2PvNc5nV9Vc8M1vWxafIL3pzf63+8MXZF1/0crxjF1JrT/7V6KWQeIkXn96WtKKKhon5zjnEFLvMa93Ytvcm04tq3G2ae7xubJtm0Z16NIm8nr5OscE8Yeh/0u23XY45i1ontT7LHgindyPUlRoEn3jcYkLrnGnT1+s9zEQ/I0GLHkOndxnSi8xvxn77Vq+m9rGmcK6sahdpE5S4/XA/3Kc4f0aQyc47SuxOSdMuaOeCKG3mD/O3mOfftliRhDTewz58w55O25iJikxZoxLMQz57SP86zcWz3eaP1Xww3OntO8E+Nimn3bhxy8Wb/MKZ3T2Fmcsi1ZkiMVelzWfNkiSZah8YeMf4M=
*/