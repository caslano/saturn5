#ifndef BOOST_METAPARSE_V1_TRANSFORM_ERROR_HPP
#define BOOST_METAPARSE_V1_TRANSFORM_ERROR_HPP

//    Copyright Abel Sinkovics (abel@sinkovics.hu) 2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/is_error.hpp>

#include <boost/mpl/eval_if.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P, class F>
      struct transform_error
      {
        template <class S, class Pos>
        struct apply :
          boost::mpl::eval_if<
            typename is_error<typename P::template apply<S, Pos> >::type,
            typename F::template apply<
              typename P::template apply<S, Pos>::type
            >,
            typename P::template apply<S, Pos>
          >
        {};
        
        typedef transform_error type;
      };
    }
  }
}

#endif


/* transform_error.hpp
RJbLYQm5cehYxbshoWeOxD3xYbYvTLptc5NmxrBsyFt+OyRP4Ece+NCeLj2Kd++1RISvGsXfs3icN/lI97jtfDbgSa9gfHThKd6BPwfhdXng1yn4DyJM+pLhKbwsT/5lKv95CLfmgW9V8B9HuDkPfLOCv8C1c/Q9NBYDdEAnDnbOhZAJeZfrIrSTvmv6qQi/6+23r38erXe6Se3wxwOMQaVG7zlrHO45vl0ReTYO0mpfPaUZlC2visN9BUMLa/k2fArzCnN5U3Ze8+U89P4V+uunbZ0Z3vSLy+mnfU98VsnfKYr/V1DY2vfCPvi80hlXyTwE9YUAJ9J0/7uG4lY460p8v8+0S4mHe/Fog1J/HPGYz0Pp7IC99Zrj9Zckr8eo80PvN+6F3gl02nW2DAZ9xgt8uV0vddoYbXOsIdn2wljk+nIzZcfe8g0Cf6mqd8LecGYiKkGNS3gjltr6NNHWX1P69MYI/ZSM3MT6DWk8P/oG5PE6JTPfVHrwFsCdpuB2K7hvAe42WS7g+7aa591u5GwMNsFY+GRo3hHCizsVzbtQvu/K/ofy3T0CnmxNxcth5L9ZjOVfV3TvofAPkY/w2nz3RiQvuB12I/3HCF+k5/msC51y/AzwFI+wi3+3wv8Lrhf81zL87pAx8Veo569D+PQbwEs+/VbI2EWK1u8ibl20vvk94BvVGLdLhNHn8D4NbGTcDSoLzqGizz0Skf6l2xva2p3LQTLCeY9vlmf9mVu9fSH90uq998fAk8fFvHidaC+MswgzP96l9O9flE7/g/Kh/teIMx+j8oT76/k7wa0fy9ibqF/TsLRpHV0Pam9Ya3lQCCDXn/4h6nmnapsBFV7IYZTRDZvy6zHyqYhvz+q91+fYFmZZpTDBq74BHKqPvhhx07cpHfByxF0HjdC5WxmuRHjXFL5bKXXmveXw8wT+LMunw7p30iQ41UU+B9cmaIIGzutorNFLnxlmGZEAzB/MoV+3425fss/kgA0z3jrHUuMqkIfRC2gtC86UL7A+F+xrCpRox+9XFxg6g8kgEmObfXeoFD5I+w0OnGEaL+hPKrLOR4avr2QGgskjfcq11JJogfMaY6y7GT/3j/L4ORE4td1WGnVl8oAo/PABfg94OMHWP6BCBYZees2213DCvmqMuAOjdt+ZnmvGIIb4dIl9+2Zj09K1jfWJNY3L6KPBk/tw9LbEsI8pgC8P5tmpbrEX15uiKnd0dyeGO3qHknI9piKHf0VUxldyfEyuDcz2zAP5Zu0B7z3T3dx5Ji7j2bY/0NyTFG2/QPLfLuEHLjxC4p1zULrtjQnPAoCwkYLR+9kY6FrfnlHWa2VRNUeEDFC8o1OmRFmfU5s7Oq4cslEGvBLPIQrPNIQJB3QZ63qKwxkRngdMga6fEQVewE0uc9f9K0T5ylT53oYwzaMBi/0nW17QF3gPRzm4nCXezCj6CMOJMuD+IcVj3o5+xHUxtPW8fa6o050YdyWv5nGdKF35PlV5hzw37wIuL8qq7+TTml3UHZuWynUD2C1GV46farBsiFVXR49OtKxbtqax3jNx43JxrY3rl7Y3mP5j4scj3hgYxzc0kaxPtLrS0I0RzWTXDrvKS28mWDE/MS5jSEifzzf3MQ+CpmOxOK0fJv1HbdBRwhLce2d67VljQBTnLVSGM2LVNWFl0Al6z16XYcBsmyO7CKOf1kI+jQ8an68tzY1N7Yn65qb1Da1tjc1N9Lm2pbWhra1huefzvmQkzLomAWVg9h8Js3LjstZGg2OFaKujib5fJDrjMEzryuQLLdEzMNgXNFt4oin+s09gfFgXYf/hhX3oAUdwVn2+GRM20yFo/42muqj1LTXUmWA=
*/