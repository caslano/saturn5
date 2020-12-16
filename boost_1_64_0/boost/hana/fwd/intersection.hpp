/*!
@file
Forward declares `boost::hana::intersection`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_INTERSECTION_HPP
#define BOOST_HANA_FWD_INTERSECTION_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    // Note: This function is documented per datatype/concept only.
    //! @cond
    template <typename S, typename = void>
    struct intersection_impl : intersection_impl<S, when<true>> { };
    //! @endcond

    struct intersection_t {
        template <typename Xs, typename Ys>
        constexpr auto operator()(Xs&&, Ys&&) const;
    };

    constexpr intersection_t intersection{};
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_INTERSECTION_HPP

/* intersection.hpp
bsSbyLAIpSg4F4b0G0EN0WaWWUx/+vPcb4o7c+V38h3p+Z18VyK/KcSwyYP+j1soz5LOLPmFOP4T+S3gmXkk+Ax9JSrmYuiJtsibvnztACYM9VjV8B106w3CRbear458k5o88AQNFPCfS++/kTVaw60cJhnCeCusB6rNCYq3UVmgv8z8Gb3iT9SwVNIC/QN+rlbcvTryayvT2znT799oDiRv5UwxH5m1IKzf8zIzfHg6JGUpTS3DIf22d1hTqjsxlMOTJXiST8uWnngTP2q4lQWKsyITBFYn/QZmb7X6T14OYdBrabE+/Vt0faoWXyMu1L+Ia8I9lYqBHXEaeTzAjoqqjerRlzPlfA92jBgAmwr/BJ2f8a6+A2eaWn4Q5wX6w+UD8dde5XCsvHtsTWzbsYo/Uf+ZpC9CLPDvGAxUevdGAv2/FnXNYj2yCMU0gSiMBr7EaTyUZiKlQRSYwwjqjn5M1CposbYZzrJt91S2zRiD9H8qtCqjdwxUyyxKEWsfU7btkz6R16WspTcrcZvvtT4tr6A8ewNtlU5k0JrI4CfIAG9br6FDio8o1FG7J+3Cuqt1dFPkEaHUpG2FbXRDI+tkJ++Xh89O2wp/xqmq3ZM6cK+cPwodJ5b7B2guHfuXs/klyCnABgTMgO7t1/BL5M1uK1wPevBGSYjH7/+YaJFVMIan2E307SlCJ4LkNjLjDYsmUagEwkadriomwEeO4ArubvhVo38zkc8Op1GfzRVtoLQ2pF9VYDxsudowUITi12Ow/AX0Jfo8GY3VNWPAycYOPFTJTAstCsJxwTd46uai70Zb0U1nDMxbs50+OfbO3Eu2V0jL587j7WXrRb64Y6BsV/PY2J547/saHYuC7flb54f02reR4HWBEaqRvqW0ro73F7t4CeASUdE/6fQVeCZ2g5cpZfs+VnxXXhksCHcWuc7NKzv3sVdOor0Wt8Z6HBSbixR773rqY0rZ4bsIe6eRLaKW1AZsDKV6QSXzNI32yMXNkHiJpuRT34npioZT/K1g/N73IBESYIqGLjXRrJR5bLN5Eg9ZfKNj4i6qAbKlnVCozWJY6tTJ1ua3edeo6JQovyqsj5vFung5dft49BpkV0MNieDGOo++lnvkAp+RKWpxsYebJ+rhOV53Nfc67oF3FyQiwBcbOoIfLCmwdDXftQkfo0eOIz61feBVqr5aaj60zqsidCOkP4WZTqT4hVepjQ69Zz63HbdKWsVL//VbMHhnOzBAwlzAWe+70USHwsbSSJ0OEJjR+AmAwLemmyCAx51s0QvULtL/Bsijng46ynCKKmVbm69YpD+uMmmLRL/+kLwUh0g7/4K/TPGu/hHOhJ0L9KkzLRXwRdwM62/FUCqsQU/oZTeYtHgoba1+BdL2uhudWPT69eajJX8Ggxz8tOL6RQsW6D9YYH56Uh1mOL/6tWZSFWq+Vq+6yuwor60uw2ut2zn0sCs6HjrnR1VmYjctZU1ZL9K/pjKPfnCx+NZbGi6/O4YN87V6WbmJye9hCz5/fgNTqLN5cmyFx9E8ieC8+u0muheKPDZDBGoXxEvprL/7Wh44NdyyuNN8EuYHR95kPSAtUkv/mH/696S12r57wVjf+vEZWda3Nj6vX4Cv8x+Sa3hvDOi8+W6t2MxXDDOr+cP7RiVE2z+TSiVdTRu60xIUaI0aFtCwJRSFoLacB5jTFtA/+spa5ur4XxSa/jz/NrN3XBWpRENKYV6G2bJL33edIczHv4S0PEL7o7QFGUOL8lq9yKr9V3HlFbOg6a+V4iS2Hq/Dq41OljH1tdIK5z5+k0IyvGMeZFjveamU5IC+96U0HA+DsSX6gy9l+SPonQ6c9q4+65I=
*/