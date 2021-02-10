// Copyright Daniel Wallin, David Abrahams 2005.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PACK_PARAMETER_REQUIREMENTS_HPP
#define BOOST_PARAMETER_AUX_PACK_PARAMETER_REQUIREMENTS_HPP

namespace boost { namespace parameter { namespace aux {

    // Used to pass static information about parameter requirements through
    // the satisfies() overload set (below).  The matched function is never
    // invoked, but its type indicates whether a parameter matches at
    // compile-time.
    template <typename Keyword, typename Predicate, typename HasDefault>
    struct parameter_requirements
    {
        typedef Keyword keyword;
        typedef Predicate predicate;
        typedef HasDefault has_default;
    };
}}} // namespace boost::parameter::aux

#endif  // include guard


/* parameter_requirements.hpp
6yiIVPPxbTxZ1eCj0nXV9U7IiGEUigVaOQbsJE/9ZiZlaPgCaudREIG79bv3Qbf/U2846Ncbu8Ee4yR5EmAkuALA9v1oL6kyxMYU3llfRv1A0SGxglHzVGSzuR7nuV4qiBq8pVlA1bLyXp1fvKlyx9iK2CSbefUeD8XCGeGKvEghvPB1QxjIGOVk6zOOa5v3UpekLxtYS2kCW6thidXQlVAmTYfaEi45Er3MVTP/hs7w2Z8MC7V9ZVIsTfVgciyLspUk3QNZYgluBiRIeRHywe8XVGE2bGFG3IsXWCO635sKryAWi/gxzXNkn+Q6PyUsnAu0/oSGu9S9KY6O1IhVRPFxIV96jS0RNx2oQuygvBi7KJX2xgratojljKBDCvK1t4GTI7EvIYNyujfopqlIr7aCwnwHH4HAMDBkDsVxlGGp4tSGgbqRdiEziQk2YzYH9gdBv/sOFHZuqodxezi2I6/0yH3v9hZ+XJgfA10fvdY/rgfw+sa+6vHLWp5tgwCTWRDoPNgkKlyWkq7WBAwBCvxfHYZ1TqEz6h9GuoKqzhKG4mQNkbMnkQ8hXRsAE6ywxjVN/kfllLIrcAFFwboqC81fQcVLFwb9ivSzBfRx2C4YerBw42JQQJv17gpqq0k2nZZAd0pmYVoahKYp
*/