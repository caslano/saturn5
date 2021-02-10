// Copyright (c) 2009-2016 Vladimir Batov.
// Use, modification and distribution are subject to the Boost Software License,
// Version 1.0. See http://www.boost.org/LICENSE_1_0.txt.

#ifndef BOOST_CONVERT_IS_CONVERTER_HPP
#define BOOST_CONVERT_IS_CONVERTER_HPP

#include <boost/convert/detail/config.hpp>
#include <boost/convert/detail/is_callable.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits.hpp>
#include <boost/ref.hpp>

namespace boost { namespace cnv
{
    template<typename, typename, typename, typename =void>
    struct is_cnv { BOOST_STATIC_CONSTANT(bool, value = false); };

    template<typename Class, typename TypeIn, typename TypeOut>
    struct is_cnv<Class, TypeIn, TypeOut, typename enable_if<is_class<Class>, void>::type>
    {
        typedef typename ::boost::unwrap_reference<Class>::type class_type;
        typedef void signature_type(TypeIn const&, optional<TypeOut>&);

        BOOST_DECLARE_IS_CALLABLE(is_callable, operator());

        BOOST_STATIC_CONSTANT(bool, value = (is_callable<class_type, signature_type>::value));
    };

    template<typename Function, typename TypeIn, typename TypeOut>
    struct is_cnv<Function, TypeIn, TypeOut,
        typename enable_if_c<is_function<Function>::value && function_types::function_arity<Function>::value == 2,
        void>::type>
    {
        typedef TypeIn                                              in_type;
        typedef optional<TypeOut>&                                 out_type;
        typedef typename function_traits<Function>::arg1_type  func_in_type;
        typedef typename function_traits<Function>::arg2_type func_out_type;

        BOOST_STATIC_CONSTANT(bool,  in_good = (is_convertible<in_type, func_in_type>::value));
        BOOST_STATIC_CONSTANT(bool, out_good = (is_same<out_type, func_out_type>::value));
        BOOST_STATIC_CONSTANT(bool,    value = (in_good && out_good));
    };
}}

#endif // BOOST_CONVERT_IS_CONVERTER_HPP


/* is_converter.hpp
cdRTWw97/1puwUyP/C9+OPUvwmmYLC3fyEBrEx6buAiSm8UMvvjTm8BaUIV/CdKEGaTRtbGw4yAAfxpHeJZdLF5IAezR6RjzONgalq3/AFBLAwQKAAAACAAtZ0pSBNEyFAsFAABmCwAANgAJAGN1cmwtbWFzdGVyL2RvY3MvbGliY3VybC9vcHRzL0NVUkxPUFRfQ09QWVBPU1RGSUVMRFMuM1VUBQABtkgkYK1WUW/bNhB+1684eC9OoMpJWiBr0xZTE6fR6liGJbfz5kGgJSpiK5MaScXx1v33HUm5ToJ0yUOd2JLou+/uPn53dLDowf4Pe3mBgYNHX5l9Z/jC69ZpIsVnmuuHHbLsK7g/dFzg9QmhBrDz+prtwZO8vkLfemVdrNfmPsueEG5hkjQfA+O8yMwtrjjPzv9UNBvJrioN/dM9OHz58md4BkcHRwc+nBHOaA2JpnxJ5ZUPrwu78ktFbm4CRd/6QDWQOrgDmFZMgRKlXhNJAe9rllOuaAFEQUFVLtkSHxgHXVEoWU3hNJ7Mo/F7H9YVy6sOZyNaUJVo6wIqck1B0pyyawfTEKlBlIiA+AVTGjFbzQQPMDwFTeVKdTAmCVIrAeSasJosMRzRUGndqFeDQd7KGisZFCJXg3xLRVDp1b2q5pjN
*/