
#ifndef BOOST_CONTRACT_DETAIL_MEMBER_FUNCTION_TYPES_HPP_
#define BOOST_CONTRACT_DETAIL_MEMBER_FUNCTION_TYPES_HPP_

// Copyright (C) 2008-2018 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#include <boost/contract/detail/none.hpp>
#include <boost/function_types/parameter_types.hpp>
#include <boost/function_types/result_type.hpp>
#include <boost/function_types/property_tags.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/is_volatile.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/pop_front.hpp>
#include <boost/mpl/push_back.hpp>
#include <boost/mpl/back.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/identity.hpp>

namespace boost {
    namespace contract {
        class virtual_;
    }
}

namespace boost { namespace contract { namespace detail {

template<class C, typename F>
struct member_function_types {
    typedef typename boost::function_types::result_type<F>::type result_type;

    // Never include leading class type.
    typedef typename boost::mpl::pop_front<typename boost::function_types::
            parameter_types<F>::type>::type argument_types;

    // Always include trailing virtual_* type.
    typedef typename boost::mpl::if_<boost::is_same<typename boost::
            mpl::back<argument_types>::type, boost::contract::virtual_*>,
        boost::mpl::identity<argument_types>
    ,
        boost::mpl::push_back<argument_types, boost::contract::virtual_*>
    >::type::type virtual_argument_types;

    typedef typename boost::mpl::if_<boost::mpl::and_<boost::is_const<C>,
            boost::is_volatile<C> >,
        boost::function_types::cv_qualified
    , typename boost::mpl::if_<boost::is_const<C>,
        boost::function_types::const_non_volatile
    , typename boost::mpl::if_<boost::is_volatile<C>,
        boost::function_types::volatile_non_const
    ,
        boost::function_types::null_tag
    >::type>::type>::type property_tag;
};

// Also handles none type.
template<class C>
struct member_function_types<C, none> {
    typedef none result_type;
    typedef none argument_types;
    typedef none virtual_argument_types;
    typedef none property_tag;
};

} } } // namespace

#endif // #include guard


/* member_function_types.hpp
843ZOmes6D6v8Tv6fE3UV/wR43yTXnadS2ruGXM72zWkiWgOb8qHz+CgPM06V/+TjutuHdr6t2ryLN0qWgqudfTzFmr08nkxnwyjbxpDyB6qHu6GPnQ2LIj8xN9lMd4j8h/WFPxHLdi/b16aB1ilxh7wb7C70D4aYos6vSj2NPVg8/jxN1qOFq6rrid9i8t7eH6mrHi4Zy2eqS8P0ZQOCM5/5YNTq8/ok+TlC/XAssPlPdNxV309OLWVemHI+xaNiza50gzm3dIH+Mh19O1f+V8EuTvnUNh60A2XO+CWSiFn7s21AL5priaDc02teY3xavt42F6CvZQ9eqk16A95uvVRJEn7/SCGJWfqVSSjL+j5FtZh4TnjovW2N6HXaY5Tw9UivXXooj8nyy310xdGvqVnPl+MD4pLITpra3U/a6J+1Mtx12iu3jbkkAt4ceU7MKyM85aZabaltDg8/HsJLMYjUXA6Dva8UEYcOxsbvzQspX4IfT+dR9uRjCbaZL33Wldarj4/+nzOSJIPLct/3IRVe2mWisXp0rBnBN7l8X/WN6IJVvF5dRvTpfuM0/5LTjGrqeai1P1X8Pg19VDrIj+o5/GhezZXd/+rRMuK4Vdj9IVj4O1p5xffwVti/6G8bjgbp8jF9XGRpL2l/nJ15FFcPdLY5OPDRr6/HU7K5VTF+BY+exiuu60fUGCUOMK9KPc+4D6XhrlucM7vms+dgkOfiSEvVJ1Hj5ZnlZfSIa+qgyI87k4aSQ/1UBdYWEo+RtObT6ldGFGTHl17AD5FeBt65GiYH1e3Ddr4O4/3YlGYUQxPqP1s+jzn8VyqXCHPb0YlvZMn7xO48grePi/n+PjIUhiYXEzVz+BvaUtruTA456FmTy/iR+/Shb3V0zM+CwviosULp0zlEZ9qRi8sda/V9vc76+3cNvcc+LWOP+mt1NYpVo6camEOuDwR1j9HVwd7G9MG0yD6YX/g4guX7KelcI2asMVeStvb9OYhPbYf1KhaKVWLxscrX3RV58/xtH+Kg5rNfQAWl+L9rsI9fnHLR/bS4f1zYvL2azxrb/mZSn+0OA3vmoMu05sPg3e1G0MDXkIssge/n2Gw3JEno9PzOWVw9N9q9At1JD8/z6QndEeuZ6B93rbHrW7abOcf4O6eI3jpojmJcdEudB7sGGoMsfC/tu/e9p3v5+lD2/NOaY7rRuNFfHbrazpyPz3/ifXPCDtw+tPGODF4Hp4+i8CZ9Z1pYlge6k8n6D81GmXtBtpPodeSx9BEDen7FnAqngfaDR/mBL9Hixbmnz5607ob49vOGF6fKf/pixhYeWKZ6+Os02rhN9dNzafdpkmLXZVncHL6XzTkQr73A/2PZTS3sf+S3H7oHpj9njyjx/PVdM8ccNO6r7UmaWBVwkG8fhiO5OPfKuvPhsyPPyit1z6ENq7Im5T6AseUCHrf+mHFzaeV/KfL0uov36CBPh9AO+POzBPkJS1QIHiGebUebDn4QhMn2ruLsW+QLPD+1v9WTnmmt75rVfB7s/BlaTwPk0fWkqcbXDeiBl9QezXgbDPY6B4LR8DfYfY0+eu78n2//Hu+vvX6lX8sRWtNgstyOODY+XzZ7L4+21i/nzZ4fpc+Nl1UVI+yw9OwJDM/RVvPvid34/TJ4ftdOJ6V5jyc3D7yYGvSUn+2PB8UPIdxRW7J5eoP3OcCTzWDxy9ueSuZe154+Qysq6fuaIYsT+C9l+B8bTqpnJyzPg+WuscNHO/8ZD1rPzKKDvvp8XsmEirr46rjohlwPk4K+soFQ/Qf3J+dAq/yO69s1B92n4vGW3madX+e1kqjvoP3VDbWS4tT/9OjaGO9igQaphPcFcM=
*/